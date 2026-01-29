/* Generic boss encounter, prototype
 * 
 * Nerull 2018
 */
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */
inherit "/lib/unique.c";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include "boss_encounter.h";


// Integers
int maxhp;
int x = 0;
int engaged = 0;


//-------------Various Boss-like selectable abilities below---------------
static int
break_weapon(object weapon, object att)
{
    if (!objectp(att) || !objectp(weapon))
	return 0;

    tell_object(att, "Your " + weapon->query_name() +
         " breaks in many shards as it hits the menacing shape!\n");

    tell_room(environment(this_object()), QCTNAME(att) + "'s " 
    + check_call(weapon->short()) + " breaks into many shards as it "
    +"hits the "+QTNAME(this_object()) +"!\n", att);
    
    weapon->remove_broken();
    
    return 1;
}


/* Function name: max_health_while_not_in_combat
* Description  : If the monster is not engaged, give it
*                max health and fatigue.
*               
* Arguments    : 
*/
void
max_health_while_not_in_combat()
{
    int healmeamount = 0;
    
    // If the boss is left unattendend, it quickly regenerates to
    // max health. This enforces an enemy encounter/team to keep
    // it engaged at all times in order to defeat it.
    if (this_object()->query_attack() == 0)
    {
        tell_watcher(QCTNAME(this_object())
        + " regenerates to full health.\n");
        
        healmeamount = this_object()->query_max_hp();

        this_object()->heal_hp(healmeamount);
        this_object()->set_fatigue(1000);
        
        engaged = 0;
        
        return;
    }
    
    return;
}


/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
public int
query_not_attack_me(object att, int att_id)
{
   object  weapon = att->query_weapon(att_id);
   
   mixed  *mag_arr;
   int     mid;
   
   if (!objectp(weapon))
       return 1;
   
   Last_Weapon = weapon;
    
   if (NEMEZIS == 1)
   {
       tell_room(environment(this_object()), "The " 
       + weapon->short() + " seems to have no effect on "
       +"the "+QTNAME(this_object()+"!"));
       
       return 1;
   }
  
   if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
   {
       if (BREAK_WEAPON == 0)
       {
           tell_room(environment(this_object()), "The " 
           + weapon->short() + " seems to have no effect on "
           +"the "+QTNAME(this_object()+"!"));
         
           return 1;
       }
       
	   break_weapon(weapon, att);
       
       return 1;
   }
   
   mag_arr = weapon->query_prop(MAGIC_AM_MAGIC);
   

   if (WEAPON_UNDEAD_SLAYER_REQUIRED == 1)
   {
       if ((mid = member_array("undead-slaying", mag_arr)) > -1)
       {
           return 0;
       }
       
       tell_room(environment(this_object()), "The " 
       + weapon->short() + " seems to have no effect on "
       +"the "+QTNAME(this_object()+"!"));
       
       return 1;
   }
 
   return 0;
}
//------------------------------------------------------------------------


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    setuid();
    seteuid(getuid());

    set_race_name("elemental");
    add_name("elemental");
    add_name("_corr_stone_elem");

    add_adj("massive");
    add_adj("corrupted");
    add_adj("stone");

    set_gender(G_NEUTER);

    // Generic properties. General boss properties
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_STUN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_I_RES_MAGIC, 30);
    
    // Thematic properties. Depending on the type of 
    // boss and monster, add properties that fits it here
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_INVIS, 99); 
    add_prop(OBJ_I_RES_POISON, 100);
   
    set_short("massive corrupted stone elemental");
    
    set_long("This creature is a sight to behold. Shaped "
    +"like a giant humanoid from thousands of pebbles, this "
    +"stone elemental measures about thirteen feet in height "
    +"and must weight a ton. Judging by its rough shifting facial "
    +"grimaces, this elemental is in contant state of pain "
    +"and agony. Almost invisible to the naked eye, the pebbles "
    +"are bound together by fine threads of human hair and "
    +"strengtened or enchanted by ancient binding and tormenting "
    +"magic. Stinking swamp water trickles from every crack and "
    +"opening between the pebbles like blood from thousands of "
    +"cuts and wounds. This creature is somewhat sentient judging "
    +"by the wailing, fully knowing it's in some cursed state and "
    +"wants to be freed.\n");

    add_prop(CONT_I_WEIGHT, BOSS_WEIGHT);
    add_prop(CONT_I_HEIGHT, BOSS_HEIGHT);

    set_stats(({ BOSS_STR, BOSS_DEX, BOSS_CON,
                 BOSS_INT, BOSS_WIS, BOSS_DIS }));

    set_hitloc_unarmed(A_HEAD, BOSS_HEAD, 15, "stone head");
    set_hitloc_unarmed(A_R_ARM, BOSS_RARM, 10, "right stone arm");
    set_hitloc_unarmed(A_L_ARM, BOSS_LARM, 10, "left stone arm");
    set_hitloc_unarmed(A_BODY, BOSS_BODY, 45, "stone body");
    set_hitloc_unarmed(A_LEGS, BOSS_LEGS, 20, "stone legs");

    set_attack_unarmed(W_LEFT,  BOSS_HIT_1, BOSS_PEN_1, W_BLUDGEON,
    BOSS_USAGE_1, "left stone fist");

    set_attack_unarmed(W_RIGHT,  BOSS_HIT_1, BOSS_PEN_1, W_BLUDGEON,
    BOSS_USAGE_1, "right stone fist");
    
    set_attack_unarmed(W_FOOTR, BOSS_HIT_1, BOSS_PEN_1, W_BLUDGEON,
    BOSS_USAGE_2, "left stone foot");

    set_attack_unarmed(W_FOOTL, BOSS_HIT_1, BOSS_PEN_1, W_BLUDGEON,
    BOSS_USAGE_2, "right stone foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);

    set_act_time(5);
    add_act("emote wails violently.");
    add_act("leer angri");
    add_act("emote booms: Mortal, end me! Or, I will end you!");
    add_act("get gems");
    add_act("get coins");
    add_act("get corpse");

    add_cact("emote booms: I will pulverize you, mortal!");
    add_cact("emote booms: If you can't free me, I shall "
    +"free you..from your mortal shell!");
    add_cact("emote booms: Eat my fists of stone!");
    add_cact("emote throws a rock at you!");
    add_cact("emote laughs at your feeble attempt at fighting!");

    set_aggressive(BOSS_AGGRESSIVE);

    set_exp_factor(BOSS_EXP_FACTOR);
}


/*
* Function name: query_max_hp()
* Description  : Determines the max hp of Damon Skragg.
*/
int
query_max_hp()
{
    ::query_max_hp();

    return BOSS_HITPOINTS;
}


 /* Function name: boss_combat_routine
 * Description  : This routine is engaged when the boss fights.
 *                Modify this to fit the monster and events.
 * Arguments    : 
 */
void
boss_engaged_routine(object enemy)
{
    // Just to ensure that it stops here if the boss is 
    // not truly engaged.
    if (engaged == 0)
    {
        return;
    }
    
    
    
    //--------------------------------------------------------------------
    // Do something combatrelated special thingy thingy here
    // for the boss, picked from the inherited 
    // file boss_encounter_actions.c
    
    max_health_while_not_in_combat();
    
    //
    //--------------------------------------------------------------------
    
    
    
    
    // If still in combat, this routine is executed anew.
    set_alarm(BOSS_CROUTINE_ALARM, 0.0, &boss_engaged_routine(enemy));
    
    return;
}


/* Function name: attacked_by
* Description  : This routine is called when we are attacked.
* Arguments    : object attacker - the attacker.
*/
public void
attacked_by(object attacker)
{
    // Already in combat, so additional attacks don't "
    // create more alarms.
    if (engaged == 1)
    {
        return;
    }
     
    engaged = 1;
     
    set_alarm(BOSS_CROUTINE_ALARM, 0.0, &boss_engaged_routine());
     
    return;
}


/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public void
attack_object(object ob)
{
    // Already in combat, so additional attacks don't "
    // create more alarms.
    if (engaged == 1)
    {
        return;
    }
    
    engaged = 1;
     
    this_object()->attack_object(ob); 
    
    set_alarm(BOSS_CROUTINE_ALARM, 0.0, &boss_engaged_routine());  
}


/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks
 *                  we died.
 * Arguments:       object killer: The enemy that caused our death.
 *
 * This handles the various random drops aswell when the monster
 * is killed.
 */
void
do_die(object killer)
{
    object random_drop = 0;
    
    tell_room(environment(this_object()), short() + " suddenly "
    +"breaks apart and collapses into a pile "
    +"of fine rubble!\nYou notice something is left "
    +"behind though.\n");
    
    // We use clone unique for rewards.
    random_drop = clone_unique(one_of_list(({
                    B_DROPDIR +  "l_3_axe",
                    B_DROPDIR +  "l_3_mace",
                    B_DROPDIR +  "l_3_spear",
                    B_DROPDIR +  "l_3_sword",
                   })),
                     1, ({ B_DROPDIR + "e_3_2haxe", 
                           B_DROPDIR + "e_3_2hmace",
                           B_DROPDIR + "e_3_2hspear",
                           B_DROPDIR + "e_3_2hsword"}));
                           
    random_drop->move(this_object(), 1);
    
    DROP_LOG("drop_log",
    "A " + random_drop->query_short() 
    + " dropped from the slain "+query_race_name()+".\n");
    
    ::do_die(killer);
}


/*
* Function name: special_attack()
* Description  : The special attack vs player teams.
*/
int
special_attack(object enemy)
{
    mixed *hitresult;
    string how;
    string ohow;
    string tar;
    
    enemy = this_object()->query_attack();
    
    if (random(BOSS_SPECIAL_SPEED))
    {
        return 0;  /* Continue with the normal attacks */
    }

    // The special.
    hitresult = enemy->hit_me(BOSS_SPECIAL_HITME_DEFAULT_VALUE
    + random(BOSS_SPECIAL_HITME_RANDOM_ADD_VALUE), W_SLASH, 
    this_object(), -1);

    how = " but miss";
    ohow = " but misses";

    if (hitresult[0] >= 0)

    {
        how = " and pound into ";
        ohow = " and pound into ";
        tar = " chest";
    }

    if (hitresult[0] > 10)
    {
        how = " and slam into ";
        ohow = " and slam into ";
        tar = " chest";
    }

    if (hitresult[0] > 20)
    {
        how = " and brutaly hammer into ";
        ohow = " and brutaly hammer into ";
        tar = " body, scattering ribs and bones";
    }

    if (hitresult[0] == -1)
    {
        this_object()->catch_msg("You strike out at " + QCTNAME(enemy)
        + " with your massive stone fists," + how + ".\n");

        enemy->catch_msg(QCTNAME(this_object())
        + " strikes out at you with massive stone fists," 
        +ohow + ".\n");

        tell_watcher(QCTNAME(this_object()) + " strikes out at " 
        + QCTNAME(enemy) 
        +" with massive stone fists," + ohow + ".\n", enemy);

        return 1;
    }

    if (hitresult[0] >= 0)
    {
        this_object()->catch_msg("You strike out at " + QCTNAME(enemy)
        + " with your massive stone fists," +
        how + enemy->query_possessive() + tar + ".\n");

        enemy->catch_msg(QCTNAME(this_object())
        + " strikes out at you with massive stone fists," +
        ohow + "your" + tar + ".\n");

        tell_watcher(QCTNAME(this_object()) + " strikes out at "
        + QCTNAME(enemy) + " with " +
        "massive stone fists," +
        ohow + enemy->query_possessive() + tar + ".\n", enemy);

        if (enemy->query_hp() <= 0);
        enemy->do_die(this_object());

        return 1;
    }

    return 1; /*  Important! Should not have two attacks in a round. */
}
