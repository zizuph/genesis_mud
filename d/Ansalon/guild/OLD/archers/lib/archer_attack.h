
/* File name: archer_attack.h
 * 
 * The basic special ability of the Elven Archers. It allows them to
 * aim at the less protected bodyparts of their enemies.
 *
 * This file is included in the guild soul.
 *
 * 14.11.2003, Blizzard
 *
 */

#define DEBUG(x)      find_player("blizzard")->catch_msg("DEBUG: " + x + "\n")
#define ONE_OFX(x)    ((x)[random(sizeof(x))])

public void           prepare_aimed_shot(object target);
public void           shoot_at_target(object target, object weapon);
public int            query_archer_attack();
public int            query_aiming();

static private int    attack_alarm_id = 0;
static private int    aiming          = 0;


/* Function name: filter_bow
 * Description  : It checks if given object is a missile weapon.
 * Returns      : True if yes, 0 if it's not a missile weapon.
 */
public int
filter_bow(object ob)
{
    return ( IS_WEAPON_OBJECT(ob) && (ob->query_wt() == W_MISSILE) );        
}

/* Function name: find_arrows
 * Description  : Searches the inventory of the archer for arrows.
 *                If that fails it tries to find quivers containing
 *                suitable projectiles in the wielders inventory.
 *                ( Function based on find_projectiles, but without
 *                printing messeges to the player )
 * Arguments    : archer   - the archer
 *                bow      - the wielded bow.
 * Returns      : int - 1  - if arrows are found, 
 *                      0  - otherwise.
 */
public int
find_arrows(object archer, object bow)
{
    object *arrows, *quivers;
    int    i;
    
    arrows = bow->query_valid_projectiles(archer);
    
    if ( !sizeof(arrows) )
    {
        quivers = filter(all_inventory(archer),
                         &->query_prop(CONT_I_IS_QUIVER));
                    
        if ( !sizeof(quivers) )
        {
            return 0;
        }
        
        for (i = 0; i < sizeof(quivers); i++)
        {
            arrows = query_valid_projectiles(quivers[i]);
            
            if ( sizeof(arrows) )
            {
                break;
            }
        }
        
        if ( !sizeof(arrows) )
            return 0;
    }
    
    bow->set_projectile_stack(arrows[0]);
    
    return 1;
}

/* Function name: can_attack_ranged
 * Decription   : Determines if we are allowed to shoot at someone
 * Arguments    : object target  - our target
 *                string attack  - special name
 * Returns      : string         - Why aren't we allowed
 *                0              - We are allowed to attack
 */
public mixed
can_attack_ranged(object target, string attack)
{
    mixed  why;
    object archer = this_player();
    object bow, *weapons;
    
    weapons = archer->query_weapon(-1);
    weapons = filter(weapons, filter_bow);
    
    if ( !sizeof(weapons) )
    {
        notify_fail("You should wield a bow first.\n");
        return 0;
    }

    if ( !target )
    {
        return "Who are you trying to shoot at?\n";
    }
    
    if ( !living(target) )
    {
        return "You cannot target that!\n";
    }

    if ( !P(target, E(archer)) )
    {
        return "But you don't see you target here!\n";
    }
        
    if ( stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
        stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)) )
    {
        return why;
    }
    else if ( why )
    {
        return "Something stops you from shooting at " + 
            target->query_the_name(archer) + ".\n";
    }
    
    if ( archer->query_prop(LIVE_I_ATTACK_DELAY) ||
        archer->query_prop(LIVE_I_STUNNED) )
    {
        return "You are too stunned to shoot anyone.\n";
    }

    bow  = weapons[0];
 
 /* The bow is not loaded and we do not have more arrows! 
  */
    if ( !bow->query_projectile() && !find_arrows(archer, bow) )
    {
        return "You curse when you realize you have no arrows.\n";
    }
        
    if ( !bow->query_stringed() )
    {
        return "Your bow is not stringed!\n";
    }

  /* Someone might try defining this to block all special attacks 
   */
    if ( target->query_not_attack_me(archer, -1) )
    {
        /* A message should be given by query_not_attack_me(), so
         * no need to specify one here.
         */
        return "";
    }
  
  /* Check only if we are not already fighting the target 
   */
    if ( member_array(target, archer->query_enemy(-1)) == - 1 )
    {
        /* Confirm attack on introduced person 
         */
        if ( !archer->query_npc() && archer->query_met(target) &&
            ( archer->query_prop(LIVE_O_LAST_KILL) != target ) )
        {
            archer->add_prop(LIVE_O_LAST_KILL, target);
            
            return "Shoot at " + target->query_the_name(archer) + 
                "?! Please confirm by trying again.\n";
        }
    }
    
    return 0;
}

/* Function name: archer_attack
 * Description  : Initial part of the special attack.
 * Arguments    : string str   
 * Returns      : 0           - we can not attack
 *                1           - we can attack, let's continue...
 */
public int
archer_attack(string str)
{
    object ob, *obj;
    object archer = this_player();
    string how;
    
    if ( !str )
        ob = archer->query_attack();
    else
    {
        obj = parse_this(str, "[at] [the] %l");
        
        if ( sizeof(obj) > 0 )
            ob = obj[0];
        
        if ( sizeof(obj) > 1 )
        {
            notify_fail("Precisely who are you going to shoot at?\n");
            return 0;
        }
    }
 
 /* Let's check if the player is not currently 
  * performing some other attack. 
  */
    if ( query_archer_attack() )
    {
        notify_fail("Patience, you can't shoot that fast!\n");
        return 0;
    }
    
    if ( query_aiming() )
    {
        notify_fail("You are aiming at your target already.\n");
        return 0;
    }
    
    how = can_attack_ranged(ob, query_verb());        
    
    if ( stringp(how) )
    {
        notify_fail(how);
        return 0;
    }
    
    if ( !TP->query_skill(SS_SHARPSHOOTING) )
    {
        notify_fail("You should improve your sharpshooting skill first.\n");
        return 0;
    }
    
    if ( archer->query_prop(LIVE_O_LAST_KILL) != ob )
        archer->add_prop(LIVE_O_LAST_KILL, ob);
 
  /* Let's prepare the special then... 
   */       
    prepare_aimed_shot(ob);
    
    return 1;
    
}

/* Function name: query_attack_aim_time
 * Decription   : It returns the aiming time.
 */
public float
query_attack_aim_time(object archer)
{
    float delay;
    delay = archer->query_speed(5);
    return delay;
}

/* Function name: query_attack_relax_time
 * Description  : It returns the relax time after a shot.
 */
public float
query_attack_relax_time(object archer)
{
    float delay;
    delay = archer->query_speed(5);
    return delay;
}

/* Function name: reset_archer_attack
 * Description  : It resets the special attack.
 */
public void
reset_archer_attack(object archer)
{
    archer->catch_msg("Your are ready to focus on your target again.\n");

    attack_alarm_id = 0;
    
}

/* Function name: ranged_attack_aim
 * Description  : This function produces some random messages for
 *                aiming at enemy, to make them look realistic and
 *                to fit in the regular combat routine. Also takes 
 *                care for loading the bow if needed.
 */
public void
ranged_attack_aim(object archer, object target, object bow)
{
  /* We are already in combat with someone. 
   */
    if ( archer->query_attack() )
    {  
      /* The bow has been already loaded with an arrow, possibly the 
       * archer is aiming at the target (regular combat)... so let's 
       * make it look like we get distracted and have to aim again.  
       */
        if ( bow->query_projectile() )
        {
            switch ( random(4) )
            {
            case 0:
                archer->catch_msg("\nYou lose your concentration, " +
                    "but quickly draw the " + bow->query_short() + 
                    " and carefully aim at your target again...\n\n");
            break;
            case 1:
                archer->catch_msg("\nSomething distracts you, however " +
                    "you quickly find your previous " +
                    "target and carefully aim at " + HIM(target) + "...\n\n");
            break;
            case 2:
                archer->catch_msg("\nYou focus on your enemy and try to " +
                    "find the weakest spot on " + HIS(target) + 
                    " body to aim at...\n\n");
            break;
            default:
                archer->catch_msg("\nYour hold your breath for " +
                    "a moment and search for your enemy's weakest spot" +
                    "...\n\n");
            break;
            }
        }
      /* The bow has not been loaded yet.   We have to load it  before we 
       * shoot, but while we prepare the special,  regular combat routine
       * may be used to load it, so let's make it look like we only track 
       * our enemy,  thinking where to aim... We will load it just before
       * shooting if neccessary. 
       */
        else
        {
            switch ( random(4) )
            {
            case 0:
                archer->catch_msg("\nYou take a quick glance at your " +
                    "enemy, trying to find the least protected part of " +
                    HIS(target) + " body...\n\n");
            break;
            case 1:
                archer->catch_msg("\nYou study your enemy as you avoid " +
                    "being attacked, looking for the best spot to aim at...\n\n");
            break;
            case 2:
                archer->catch_msg("\nBeing too close to your enemy, you " +
                    "fall back several steps to gain some distance and time " +
                    "for a more precise shot...\n\n");
            break;
            default:
                archer->catch_msg("\nYou make a few quick steps backwards " +
                    "in an attempt to gain some distance and time to aim " +
                    "at your enemy...\n\n");
            break;
            }
        }
    }
  /* We are not in combat yet. 
   */
    else
    {
     /* The bow has been already loaded. 
      */
        if ( bow->query_projectile() )
        {
            switch ( random(3) )
            {
            case 0:
                archer->catch_msg("\nYou hold you breath while drawing your " +
                    bow->short() + " and aiming at " + 
                    target->query_the_name(archer) + " carefully...\n\n"); 
            break;
            case 1:
                archer->catch_msg("\nYou slowly draw your " + bow->short() +
                    " and carefully aim at " + target->query_the_name(archer) +
                    ".\n\n");
            break;
            default:
                archer->catch_msg("\nYou draw your " + bow->short() +
                    " and focus your eyes on " + 
                    target->query_the_name(archer) + ", trying to make a " +
                    "precise shot...\n\n");
            break;
            }
        }
     /* We need to load our bow first...
      */
        else
        {
         /* Let's try to load it.
          */
//            bow->try_load();
         
            switch ( random(3) )
            {
            case 0:
                archer->catch_msg("\nYou set an arrow to the string, " +
                    "bend your " + bow->short() + " and " +
                    "carefully aim at " + target->query_the_name(archer) +
                    ".\n\n");
               
            break;
            case 1:
                archer->catch_msg("\nYou pick an arrow and draw the " +
                    bow->short() + " quickly. Holding your breath you " +
                    "calmly aim at " + target->query_the_name(archer) + 
                    ".\n\n");
            break;
            default:
                archer->catch_msg("\nYou slowly load your " + bow->short() +
                    " with an arrow and focus your eyes on " +
                    target->query_The_name(archer) + ", carefully searching " +
                    "for " + HIS(target) + " weakest spot.\n\n"); 
            break;
            }
        }
    }    
}

/* Function name: prepare_aimed_shot
 * Decription   : It prepares the archer for shooting and makes a check for 
 *                a bow once again.
 */
public void
prepare_aimed_shot(object target)
{
    object bow, *weapons;
    object archer = this_player();
    string why;

    weapons = archer->query_weapon(-1);    
    weapons = filter(weapons, filter_bow);

    if ( !sizeof(weapons) )
    {
        write("But you are not wielding a bow!\n");
        return;
    }
    
    bow     = weapons[0];
    
     /* Let's check if we have arrows to start the fight...
      */
    if ( !archer->query_attack() && !bow->query_projectile() )
    {
        bow->find_projectiles();
        bow->try_load();
        
        if ( !bow->query_projectile() )
        {
            write("You realize you have no arrows.\n");
            return;
        }
    }
    
    ranged_attack_aim(archer, target, bow);

    aiming          = 1;
    attack_alarm_id = set_alarm(query_attack_aim_time(archer), 0.0, 
                                &shoot_at_target(target, bow));

        
}

/* Function name: reduce_stack_and_do_miss
 * Description  : This function takes care of reducing missile stack
 *                and moving arrow to the enviroment of our target
 *                when we miss.
 */
public void
reduce_stack_and_do_miss(object target, object bow)
{
    object arrow, arrow_stack, env;
 
    if ( !(arrow_stack = bow->query_projectile_stack()) )
    {
        bow->find_projectiles();
        arrow_stack = bow->query_projectile_stack();
    }

    env         = environment(arrow_stack);
  
  /* Let's pick one arrow from the stack
   */
    arrow_stack->split_heap(1);
    arrow       = arrow_stack;
    arrow_stack = arrow_stack->make_leftover_heap();
 
  /* Move the stack back to the archer...
   */
    arrow_stack->move(env, 1);
    bow->set_projectile_stack(arrow_stack);
    
 /* Let's hide arrows in the bushes, grass etc. 
  */
    if ( random(3) )
    {
        arrow->add_prop(OBJ_I_HIDE, 33 * random(3));
        arrow->move(environment(target), 1);
    }
    else
        arrow->move(environment(target), 1);
        
}

/* Function name: reduce_stack_and_do_hit
 * Description  : This function takes care of reducing missile stack
 *                and moving arrow to the target.
 */
public void
reduce_stack_and_do_hit(object target, object bow)
{
    object arrow, arrow_stack, env;
     
    if ( !(arrow_stack = bow->query_projectile_stack()) )
    {
        bow->find_projectiles();
        arrow_stack = bow->query_projectile_stack();
    }

    env         = environment(arrow_stack);
    
  /* Let's pick one arrow from the stack
   */
    arrow_stack->split_heap(1);
    arrow       = arrow_stack;
    arrow_stack = arrow_stack->make_leftover_heap();
 
  /* Move the stack back to the archer...
   */
    arrow_stack->move(env, 1);
     
    bow->set_projectile_stack(arrow_stack);
    
 /* Let's move an arrow to the target. 
  */
    arrow->move(target, 1);
         
}

/* Function name: ranged_attack_miss
 * Description  : This function produces some random messeges while
 *                shooting, to be exact - when we miss. It also makes
 *                it work with the regular combat routines.
 */
public void
ranged_attack_miss(object archer, object target, object bow)
{
    string  my_str     = "";
    string  target_str = "";
    string  others_str = "";
    object  arrow      = bow->query_projectile();
    
    if ( archer->query_attack() )
    {
      /* The bow is loaded with arrow (due to regular combat routines
       * or just because we loaded it while preparing the special).
       * We just shoot and miss...
       */
        if ( arrow )
        {
            reduce_stack_and_do_miss(target, bow);
                   
            if ( bow->query_projectile() )
                DEBUG("Bow is still loaded.");
            else
                DEBUG("Bow is not loaded now.");
                
         /* Let's generate some random messages. More fun ;) 
          */
            switch ( random(3) )
            {
            case 1:
                my_str     = ", but it misses the target badly";
                target_str = QCTNAME(archer) + " shoots an arrow " +
                             "at you, but it misses you badly. " +
                             capitalize(HE(archer)) + " quickly draws " +
                             HIS(archer) + " bow again";
                others_str = QCTNAME(archer) + " shoots an arrow " +
                             "at " + QTNAME(target) + ", but it misses " +
                             HIM(target) + " badly. " + QCTNAME(archer) +
                             " draws " + HIS(archer) + " bow again";
            break;
            case 2:
                my_str     = ". It flies past your target, missing " + 
                             HIM(target);
                target_str = QCTNAME(archer) + " shoots an arrow " +
                             "at you, but it just flies past, missing you. " +
                             capitalize(HE(archer)) + " quickly loads and " +
                             "draws " + HIS(archer) + " bow again";
                others_str = QCTNAME(archer) + " shoots an arrow " +
                             "at " + QTNAME(target) + ", but it just " +
                             "flies past " + HIM(target) + ", barely " +
                             "missing the target. " + QCTNAME(archer) +
                             " quickly loads and draws " + HIS(archer) +
                             " bow again";
            break;
            default:
                my_str     = ", but it hisses past, missing " + HIM(target);
                target_str = "You hear the hiss of an arrow flying through " +
                             "the air as " + QTNAME(archer) + " shoots " +
                             "at you. " + capitalize(HE(archer)) + 
                             "quickly prepares for another shot";
                others_str = "You hear the hiss of an arrow flying through " +
                             "the air as " + QTNAME(archer) + " shoots " +
                             "at " + QTNAME(target) + ". " + 
                             capitalize(HE(archer)) + " quickly prepares " +
                             "for another shot";
            break;
            }
            
            archer->catch_msg("You shoot an arrow at " + QTNAME(target) +
                my_str + ". You swiftly nock another arrow and draw " +
                "your " + bow->short() + " again...\n");
            target->catch_msg(target_str + ".\n");
            archer->tell_watcher(others_str + ".\n", target);
            
        }
      /* The bow is not loaded with arrow (due to regular combat routines)
       * so I make it look like i quickly load the bow and shoot...
       */
        else
        {
          /* Reduce stack and miss... 
           */
            reduce_stack_and_do_miss(target, bow);
            
            if ( bow->query_projectile() )
                DEBUG("Bow is still loaded.");
            else
                DEBUG("Bow is not loaded now.");
                
            switch ( random(2) )
            {
            case 0:
                my_str     = "You swiftly pull an arrow out of the " +
                             "quiver and almost without aiming shoot at " +
                             QTNAME(target) + ", barely missing " +
                             HIM(target);
                target_str = QCTNAME(archer) + " swiftly pulls an arrow " +
                             "out of the quiver and almost without aiming " +
                             "shoots at you, barely missing";
                others_str = QCTNAME(archer) + " swiftly pulls an arrow " +
                             "out of the quiver and almost without aiming " +
                             "shoots at " + QTNAME(target) + ", barely " +
                             "missing " + HIM(target);  
            break;
            default:
                my_str     = "Moving swiftly, you load the " + bow->short() +
                             " with an arrow and shoot blindly at " +
                             QTNAME(target) + ", barely missing " + 
                             HIM(target);
                target_str = "Moving swiftly, " + QTNAME(archer) + " loads " +
                             HIS(archer) + " " + bow->short() + " with an " +
                             "arrow and shoots blindly at you, but " +
                             "misses";
                others_str = "Moving swiftly, " + QTNAME(archer) + " loads " +
                             HIS(archer) + " " + bow->short() + " with an " +
                             "arrow and shoots blindly at " + QTNAME(target) +
                             ", barely missing " + HIM(target);
            break;
            }
            
            archer->catch_msg(my_str + ".\n");
            target->catch_msg(target_str + ".\n");
            archer->tell_watcher(others_str + ".\n", target);
        }
    }
    else
    {
        if ( arrow )
        {
          /* Uhm...a miss 
           */
            reduce_stack_and_do_miss(target, bow);
            
            if ( bow->query_projectile() )
                DEBUG("Bow is still loaded.");
            else
                DEBUG("Bow is not loaded now.");

            archer->catch_msg("As you shoot at " + QTNAME(target) + 
                              " your aim wavers slightly and a moment " +
                              "later the arrow misses " + HIM(target) + 
                              " with a hiss. You quickly load your " +
                              bow->query_short() + " with another arrow " +
                              "and aim at " + QTNAME(target) + " again.\n");
            target->catch_msg(QCTNAME(archer) + " shoots at you, but " +
                              "the arrow just misses you with a hiss. " +
                              "You see " + HIM(archer) + " drawing the " +
                              "bow again...\n");
            archer->tell_watcher(QCTNAME(archer) + " shoots at " +
                              QTNAME(target) + ", but the arrow just " +
                              "misses " + HIM(target) + " with a hiss. " +
                              "You see " + QTNAME(archer) + " drawing the " +
                              "bow again...\n",
                              target);
        }
        else
        {
          /* Let's miss! 
           */
            reduce_stack_and_do_miss(target, bow);

            if ( bow->query_projectile() )
                DEBUG("Bow is still loaded.");
            else
                DEBUG("Bow is not loaded now.");

            archer->catch_msg("You shoot at " + QTNAME(target) + 
                              ", but the arrow misses " + HIM(target) +
                              ". You curse silently.\n");
            target->catch_msg("Suddenly, an arrow flies out of nowhere, " +
                              "but luckily it misses you.\n");
            archer->tell_watcher("An arrow flies out of nowhere and " +
                              "barely misses " + QTNAME(target) + ".\n",
                              target);
        }
    }

}

/* Function name: shoot_at_target
 * Decription   : This is the main code of our special; damaging part,
 *                as well as calling neccessary messeges.
 */
public void
shoot_at_target(object target, object weapon)
{
    object    bow, *weapons, bow_loaded;    
    object    new_target, archer = this_player();
    int       reset_alarm_id, to_hit, penet, phurt;
    mixed     hitresult;
    string    hdesc, rnd_desc, why;
    string    *archer_msg, *target_msg, *others_msg, *quick_load;
         
    reset_alarm_id = set_alarm(query_attack_relax_time(archer), 0.0,
                               &reset_archer_attack(archer));
 
    aiming  = 0;
      
    weapons = archer->query_weapon(-1);
    weapons = filter(weapons, filter_bow);
    
    if ( !sizeof(weapons) )
    {
        write("But you are not wielding a bow!\n");
        return;
    }
    
    bow     = weapons[0];

    if ( bow != weapon )
    {
        archer->catch_msg("You broke your concentration while " +
            "switching bows.\n");
        return;
    }
 
    bow_loaded = bow->query_projectile();
    
 /* Let's check if our target is still present, if now we
  * try to find another one, not to waste a shot.
  */
    if ( !target || (E(target) != E(archer)) )
    {
        if ( new_target = archer->query_attack() )
        {
            if ( E(new_target) == E(archer) )
            {
                archer->catch_msg("Your victim is no longer present so you " +
                    "target " + QTNAME(new_target) + " instead.\n");
                target = new_target;
            }
            else
            {
                archer->catch_msg("You look around but can't see your " +
                    "target any more.\n");
                return;
            }
        }
        else
        {
            archer->catch_msg("You look around but can't see your " +
                "target any more.\n");
            return;                    
        }
    }
    
  /* Let's check if we are able to shoot; do we still have arrows?
   * is our bow stringed? etc.
   */
    if ( stringp(why = can_attack_ranged(target, "aimed shot")) )
    {
        archer->catch_msg(why);
        return;
    }        
    
  /* Initiate battle with the target.
   */
    archer->attack_object(target);

  /* Reveal the player if he is hiding (maybe make some tests here).
   */
    archer->reveal_me(0);
  
  /* To hit value of our special - add modifiers here, later. 
   */   
    to_hit = 95;
    
  /* Penet value of our special - add modifiers here, later.
   */
    penet  = 700;
    
  /* Test to see if the attacker hits.  cb_tohit() is the routine
   * used by the combat system to determine if a regular attack
   * hits, but it also works nicely for our purposes.
   */
    if ( archer->query_combat_object()->cb_tohit(-1, to_hit, target) != 1 )
    {
      /* Special misses. 
       */
        
        ranged_attack_miss(archer, target, bow);
        
        hitresult = target->hit_me(0, W_IMPALE, archer, -1);  
        
        return;
    }
    else
    {
        hitresult = target->hit_me(penet, W_IMPALE, archer, -1);
    }
    
    phurt = hitresult[0];
    hdesc = hitresult[1];
    
       /* I place messeges for each person in arrays:
        *      ({ msg_WITHOUT_loading, msg_WITH_loading }).
        */
  
    switch ( phurt )
    {
    case 0:
        ranged_attack_miss(archer, target, bow);
        return;
    break;
    case 1..2:
        
        reduce_stack_and_do_miss(target, bow);
        
        archer_msg = ({ 
            "You shoot an arrow at " + QTNAME(target) +
            ", but it merely glances off " + HIS(target) + " " + hdesc +
            ", just nicking " + HIS(target) + " skin",

            "You load your " + bow->short() + " and almost without aiming " +
            "shoot at " + QTNAME(target) + ", but the arrow merely glances " +
            "off " + HIS(target) + " " + hdesc + ", just nicking " +
            HIS(target) + " skin"
            });

        target_msg = ({
            QCTNAME(archer) + " shoots an arrow at you, but " +
            "it merely glances off your " + hdesc + ", just nicking " +
            "your skin",
            
            QCTNAME(archer) + " loads " + HIS(archer) + " " +
            bow->short() + " and almost without aiming shoots at you, but " +
            "the arrow merely glances off your " + hdesc + ", just " +
            "nicking your skin"
            });

        others_msg = ({
            QCTNAME(archer) + " shoots an arrow at " +
            QTNAME(target) + ", but it merely glances off " + HIS(target) +
            " " + hdesc + ", just nicking " + HIS(target) + " skin",
            
            QCTNAME(archer) + " loads " + HIS(archer) + " " + bow->short() +
            " and almost without aiming shoots at " + QTNAME(target) +
            ", but the arrow merely glances " + HIS(target) + " " + hdesc +
            ", just nicking " + HIS(target) + " skin"
            });

    break;
    case 3..5:
        
        reduce_stack_and_do_miss(target, bow);
        
        archer_msg = ({
            "You shoot wildly at " + QTNAME(target) +
            ", with the arrow just grazing " + HIS(target) + " " + hdesc +
            " and falling to the ground",

            "You bend your " + bow->short() + " and fit an arrow to the " +
            "string. You shoot wildly at " + QTNAME(target) +
            ", with the arrow just grazing " + HIS(target) + " " +
            hdesc + " and falling to the ground"
            });

        target_msg = ({
            QCTNAME(archer) + " shoots wildly at you, but the " +
            "arrow just grazes your " + hdesc + " and falls to the ground",

            QCTNAME(archer) + " bends " + HIS(archer) + " " +
            bow->short() + " and fits an arrow to the string. " +
            "Then " + HE(archer) + " shoots wildly at you, but the " +
            "arrow just grazes your " + hdesc + " and falls to the " +
            "ground"
            });

        others_msg = ({ 
            QCTNAME(archer) + " shoots wildly at " +
            QTNAME(target) + ", but the arrow just grazes " +
            HIS(target) + " " + hdesc + " and falls to the ground",

            QCTNAME(archer) + " bends " + HIS(archer) + " " +
            bow->short() + " and fits an arrow to the string. " +
            "Then " + HE(archer) + " shoots wildly at " + QTNAME(target) +
            ", but the arrow just grazes " + HIS(target) + " " +
            hdesc + " and falls to the ground"
            });

    break;
    case 6..15:
    
        rnd_desc = ONE_OFX( ({ "opening a nasty wound",
                               "causing significant damage",
                               "leaving a minor wound",
                            }) );
                            
        reduce_stack_and_do_hit(target, bow);
       
        archer_msg = ({
            "You fire accurately at " + QTNAME(target) + ", the arrow " +
            "pierces " + HIS(target) + " " + hdesc + ", " + rnd_desc,
            
            "You quickly set an arrow to the string and fire accurately " +
            "at " + QTNAME(target) + ". The arrow pierces " + HIS(target) +
            " " + hdesc + ", " + rnd_desc
            });
            
        target_msg = ({ 
            QCTNAME(archer) + " fires accurately at you, the arrow " +
            "pierces your " + hdesc + ", " + rnd_desc,
            
            QCTNAME(archer) + " quickly sets an arrow to the string and " +
            "fires accurately at you. The arrow pierces your " + hdesc +
            ", " + rnd_desc
            });
            
        others_msg = ({ 
            QCTNAME(archer) + " fires accurately at " + QTNAME(target) +
            ". The arrow pierces " + HIS(target) + " " + hdesc + ", " +
            rnd_desc,
            
            QCTNAME(archer) + " quickly sets an arrow to the string and " +
            "fires accurately at " + QTNAME(target) + ". The arrow " +
            "pierces " + HIS(target) + " " + hdesc + ", " + rnd_desc
            });

    break;
    case 16..27:

        reduce_stack_and_do_hit(target, bow);

        archer_msg = ({
            "You fall back several steps, trying to gain some distance " +
            "and then shoot at " + QTNAME(target) + ". The arrow stabs " +
            "deeply into " + HIS(target) + " " + hdesc,
            
            "You fall back several steps, load your bow and shoot at " +
            QTNAME(target) + ". The arrow stabs deeply into " + HIS(target) +
            " " + hdesc
            });
            
        target_msg = ({
            QCTNAME(archer) + " falls back several steps, trying to gain " +
            "some distance and then shoots at you. The arrow stabs " +
            "deeply into your " + hdesc,
            
            QCTNAME(archer) + " falls back several steps, loads " +
            HIS(archer) + " " + bow->short() + " and shoots at you. " +
            "The arrows stabs deeply into your " + hdesc
            });
            
        others_msg = ({ 
           QCTNAME(archer) + " falls back several steps, trying to gain " +
           "some distance and then shoots at " + QTNAME(target) +
           ". The arrow stabs deeply into " + HIS(target) + " " + hdesc,
           
            QCTNAME(archer) + " falls back several steps, loads " +
            HIS(archer) + " " + bow->short() + " and shoots at " +
            QTNAME(target) + ". The arrow stabs deeply into " + HIS(target) +
            " " + hdesc
            });
            
    break;
    case 28..43:

        rnd_desc = ONE_OFX( ({ "deeply", 
                               "badly", 
                               "easily",
                               "forcefully",
                               "accurately",
                               "solidly"
                            }) );
                            
        reduce_stack_and_do_hit(target, bow);

        archer_msg = ({
            "You focus intently on " + QTNAME(target) + " and then shoot, " +
            "sending an arrow in " + HIS(target) + " direction. It " +
            rnd_desc + " impales " + HIS(target) + " " + hdesc,
            
            "You load your " + bow->short() + ", focus intently on " +
            QTNAME(target) + " and then shoot, sending an arrow in " +
            HIS(target) + " direction. It " + rnd_desc + " impales " +
            HIS(target) + " " + hdesc 
            });

        target_msg = ({
            QCTNAME(archer) + " shoots, sending an arrow in your " +
            "direction. It " + rnd_desc + " impales your " + hdesc,
            
            QCTNAME(archer) + " loads " + HIS(archer) + " " + bow->short() +
            " and shoots, sending an arrow in your direction. It " +
            rnd_desc + " impales your " + hdesc
            });
         
        others_msg = ({
            QCTNAME(archer) + " shoots at " + QTNAME(target) + ", sending " +
            "an arrow in " + HIS(target) + " direction. It " + rnd_desc +
            " impales " + HIS(target) + " " + hdesc,
            
            QCTNAME(archer) + " loads " + HIS(archer) + " " + bow->short() +
            " and shoots at " + QTNAME(target) + ", sending an arrow in " +
            HIS(target) + " direction. It " + rnd_desc + " impales " + 
            HIS(target) + " " + hdesc 
            });
            
    break;
    case 44..65:

        reduce_stack_and_do_hit(target, bow);
        
        if ( target->query_humanoid() )
        {
            archer_msg = ({
                "You shoot " + QTNAME(target) + " with great precision. " +
                capitalize(HE(target)) + " grasps " + HIS(target) + " " +
                hdesc + ", which is deeply punctured by the arrow",
            
                "You swiftly bend your " + bow->short() + " and shoot at " +
                QTNAME(target) + " with great precision. " +
                capitalize(HE(target)) +
                " grasps " + HIS(target) + " " + hdesc +
                ", which is deeply punctured by the arrow"
                });
            
            target_msg = ({
                QCTNAME(archer) + " shoots at you with great precision. " +
                "You grasp your " + hdesc + ", which is deeply punctured " +
                "by the arrow",
            
                QCTNAME(archer) + " swiftly bends " + HIS(archer) + " " +
                bow->short() + " and shoots at you with great precision. " +
                "You grasp your " + hdesc + ", which is deeply punctured " +
                "by the arrow"
                });
            
            others_msg = ({
                QCTNAME(archer) + " shoots at " + QTNAME(target) +
                " with great precision. " + capitalize(HE(target)) +
                " grasps " + HIS(target) + " " + hdesc + ", which is " +
                "deeply punctured by the arrow",
         
                QCTNAME(archer) + " swiftly bends " + HIS(archer) + " " +
                bow->short() + " and shoots at " + QTNAME(target) +
                " with great precision. " + capitalize(HE(target)) +
                " grasps " + HIS(target) + " " + hdesc + ", which is " +
                "deeply punctured by the arrow"
                });
        }
        else
        {
            archer_msg = ({
                "You shoot at " + QTNAME(target) + " with great precision. " +
                "The arrow deeply punctures " + HIS(target) + " " + hdesc,
                
                "You swiftly bend your " + bow->short() + " and shoot at " +
                QTNAME(target) + " with great precision. The arrow deeply " +
                "punctures " + HIS(target) + " " + hdesc
                });
            
            target_msg = ({
                QCTNAME(archer) + " shoots at you with great precision. " +
                "The arrow deeply punctures your " + hdesc,
                
                QCTNAME(archer) + " swiftly bends " + HIS(archer) + " " +
                bow->short() + " and shoots at you with great precision. " +
                "The arrow deeply punctures your " + hdesc
                });
            
            others_msg = ({
                QCTNAME(archer) + " shoots at " + QTNAME(target) +
                " with great precision. The arrow deeply punctures " +
                HIS(target) + " " + hdesc,
                
                QCTNAME(archer) + " swiftly bends " + HIS(archer) + " " +
                bow->short() + " and shoots at " + QTNAME(target) +
                " with great precision. The arrow deeply punctures " +
                HIS(target) + " " + hdesc
                });
        }
        
    break;
    case 66..99:

        reduce_stack_and_do_hit(target, bow);
        
        archer_msg = ({
            "You shoot accurately at " + QTNAME(target) + ", who staggers " +
            "when the arrow lances through " + HIS(target) +
            " " + hdesc + ", opening a heavily bleeding wound",
            
            "You draw your " + bow->short() + " and shoot accurately at " +
            QTNAME(target) + ", who staggers when the arrow lances " +
            "through " + HIS(target) + " " + hdesc + ", opening a " +
            "heavily bleeding wound"
            });

        target_msg = ({ 
            QCTNAME(archer) + " shoots accurately at you. You stagger " +
            "when the arrow lances through your " + hdesc +
            ", opening a heavily bleeding wound",
            
            QCTNAME(archer) + " draws " + HIS(archer) + " " +
            bow->short() + " and shoots accurately at you. You stagger " +
            "when the arrow lances through your " + hdesc +
            ", opening a heavily bleeding wound"
            });
            
        others_msg = ({
            QCTNAME(archer) + " shoots accurately at " + QTNAME(target) +
            ", who staggers when the arrow lances through " +
            HIS(target) + " " + hdesc + ", opening a heavily " +
            "bleeding wound",
            
            QCTNAME(archer) + " draws " + HIS(archer) + " " +
            bow->short() + " and shoots accurately at " + QTNAME(target) +
            ", who staggers when the arrow lances through " +
            HIS(target) + " " + hdesc + ", opening a heavily " +
            "bleeding wound"
            });
        
    break;
    default:

        reduce_stack_and_do_hit(target, bow);
        
        if ( target->query_humanoid() )
        {
            archer_msg = ({ 
                "You shoot " + QTNAME(target) + " through the neck and " +
                HE(target) + " falls to to the ground, desperately " +
                "clutching " + HIS(target) + " throat",
            
                "You bend your bow and shoot " + QTNAME(target) + " through " +
                "the neck. " + capitalize(HE(target)) + " falls to the " +
                "ground, desperately clutching " + HIS(target) + " throat" 
                });
            
            target_msg = ({
                QCTNAME(archer) + " shoots you through the neck and you " +
                "fall to the ground, desperately clutching your throat",
            
                QCTNAME(archer) + " bends " + HIS(archer) + " " +
                bow->short() + " and shoots you through the neck. You fall " +
                "to the ground, desperately clutching your throat"
                });
            
            others_msg = ({ 
                QCTNAME(archer) + " shoots " + QTNAME(target) + " through " +
                "the neck. " + capitalize(HE(target)) + " falls to the " +
                "ground, desperately clutching " + HIS(target) + " throat",
            
                QCTNAME(archer) + " bends " + HIS(archer) + " " +
                bow->short() + " and shoots " + QTNAME(target) +
                " through the neck. " + capitalize(HE(target)) +
                " falls to the ground, desperately clutching " +
                HIS(target) + " throat"
                });
        }
        else
        {
            archer_msg = ({
                "You shoot at " + QTNAME(target) + " with devastating " +
                "precision. " + capitalize(HE(target)) + " falls to " +
                "the ground, with an arrow sticking from a mortal " +
                "wound in " + HIS(target) + " " + hdesc,
                
                "You bend your bow and shoot at " + QTNAME(target) +
                " with devastating precision. " + capitalize(HE(target)) +
                " falls to the ground, with an arrow sticking from a " +
                "mortal wound in " + HIS(target) + " " + hdesc
                });

            target_msg = ({
                QCTNAME(archer) + " shoots at you with devastating " +
                "precision. You fall to the ground, with an arrow " +
                "sticking from a mortal wound in your " + hdesc,
                
                QCTNAME(archer) + " bends " + HIS(archer) + " " +
                bow->short() + " and shoots at you with devastating " +
                "precision. You fall to the ground, with an arrow " +
                "sticking from a mortal wound in your " + hdesc
                });
                
            others_msg = ({
                QCTNAME(archer) + " shoots at " + QTNAME(target) +
                " with devastating precision. " + capitalize(HE(target)) +
                " falls to the ground, with an arrow sticking from a " +
                "mortal wound in " + HIS(target) + " " + hdesc,
                
                QCTNAME(archer) + " bends " + HIS(archer) + " " +
                bow->short() + " and shoots at " + QTNAME(target) +
                " with devastating precision. " + capitalize(HE(target)) +
                " falls to the ground, with an arrow sticking from a " +
                "mortal wound in " + HIS(target) + " " + hdesc
                });
        
        }
        
    break;    
    }

       /* Additional load messeges,  
        *    ({ msg_for_archer, msg_for_others }).
        */
        
    switch ( random(3) )
    {
    case 0:
        quick_load = ({ "You nock another missile and draw your bow again",
             QCTNAME(archer) + " nocks another missile and draws " +
             HIS(archer) + " bow again" });
    break;
    case 1:
        quick_load = ({ "You load your bow again",
             QCTNAME(archer) + " loads " + HIS(archer) + " bow again" });
    break;
    default:
        quick_load = ({ "You set another arrow to the string",
             QCTNAME(archer) + " sets another arrow to the string" });
    break;
    }
 
         // Add some messages if our bow was loaded before the special and
         // we need to 'load' it. Just so the whole fight looks better.

    if ( bow_loaded )
    {
        archer->catch_msg(archer_msg[0] + ". " + quick_load[0] + ".\n");
        target->catch_msg(target_msg[0] + ". " + quick_load[1] + ".\n");
        archer->tell_watcher(others_msg[0] + ". " + quick_load[1] + ".\n", 
                             target);
    }
    else
    {
        archer->catch_msg(archer_msg[1] + ".\n");
        target->catch_msg(target_msg[1] + ".\n");
        archer->tell_watcher(others_msg[1] + ".\n", target);
    }        
    
    if ( target->query_hp() <= 0 )
    {
        target->do_die(archer);
    }        
 
}

public int
query_archer_attack()
{
    return !!attack_alarm_id;
}

public int
query_aiming()
{
    return !!aiming;
}

