/*
 * Spell object for the Oneiro spell of the SCoP guild in Calia.
 *
 * It acts as a paralysis object and only allows the caster a few
 * actions.
 * 
 * Bishop, May 2004.
 * 
 * November 2008 - added check in do_watch for validity of scried object.
 *                 This was causing a runtime when someone quits. (Petros)
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/d/Calia/std/contents_desc";
inherit "/std/object";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <language.h>
#include <composite.h>
#include <cmdparse.h>
#include "defs.h"

#define SLEEP_STAGE_1 1
#define SLEEP_STAGE_2 2
#define FULL_SLEEP_IDLE 3
#define FULL_SLEEP_WATCHING 4
#define FULL_SLEEP_PRESENT 5
#define DREAM_TRAVELLING 6
#define WAKING_UP 7

#define DREAM_ROOM "/d/Calia/guilds/scop/objects/dream_room"
#define SCOP_O_SLEEP_LOCATION "_scop_o_sleep_location_"
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

/* Prototypes */

void enter_dream_state();
void dream_check();
void arrive_at_target(object target);
varargs public int dispel_spell_effect(object dispeller, int mode);
int check_user(object player);
int attempt_action(string str);
int do_dreamhelp(string str);
int do_visit(string str);
int do_sense(string str);
int do_wake(string str);
int do_withdraw(string str);
int do_watch(string str);
int do_enter(string str);

/* Variables */

int state = 0;
object scried_room; // The room we are scrying
object scried;      // The person we're scrying
string* allowed_actions = (({"wake", "visit", "sense", "dreamhelp",
                             "watch", "enter", "withdraw"}));
object scop_clone;
object * enemies;

void
create_object()
{
    set_name("_oneiro_ob_");

    set_no_show();

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_TELEPORT, 1);
    
    add_prop(OBJ_S_WIZINFO, "This is a spell object for a SCoP spell. It" +
                            " paralyzes the player, only allowing him/her " +
                            "a few actions.\n");
}
void
create_clone(object scop, object env)
{
   string* adj;
   int stat0, stat1, stat2, stat3, stat4, stat5;   
 
   string short_descr;

   setuid();
   seteuid(getuid());

   stat0 = scop->query_stat(0);
   stat1 = scop->query_stat(1);
   stat2 = scop->query_stat(2);
   stat3 = scop->query_stat(3);
   stat4 = scop->query_stat(4);
   stat5 = scop->query_stat(5);

   adj = scop->query_adj(1);

   scop_clone = clone_object(SPIRIT_SPELLS + "scop_clone");
   scop_clone->set_adj(adj[0]);
   scop_clone->add_adj(adj[1]);
   short_descr = adj[0]+" "+adj[1]+" "+scop->query_gender_string()+
                 " "+scop->query_race_name();
   scop_clone->set_nshort(short_descr+" sleeping soundly");
   scop_clone->set_race_name(scop->query_race_name());
   scop_clone->set_gender(scop->query_gender());
   scop_clone->add_prop(LIVE_S_SOULEXTRA, "sleeping softly");
   scop_clone->set_stats(({stat0,stat1,stat2,stat3,stat4,stat5}));
   scop_clone->add_prop(LIVE_I_NEVERKNOWN, 1);
   scop_clone->add_name(scop->query_real_name());
   scop_clone->set_long("");
   scop_clone->set_living_name(scop->query_real_name());
   scop_clone->heal_hp(10000);
   scop_clone->set_cleric(scop);
   scop_clone->move(env);
}

void
enter_dream_state()
{
    object env;
    if (!state)
    {
        state = SLEEP_STAGE_1;
        spell_caster->catch_tell("Your limbs grow leaden as " +
                                 "you move further and " +
                                 "further away from the " +
                                 "waking world.\n");
        set_alarm(itof(5 + random(10)), 0.0, enter_dream_state);            
    }
    else
    if (state == SLEEP_STAGE_1)
    {
        state = SLEEP_STAGE_2;
        spell_caster->catch_tell("Your physical body begins to " +
                                 "feel like a distant memory " +
                                 "as you venture further and " +
                                 "further into the dream " +
                                 "world.\n");
        set_alarm(itof(5 + random(10)), 0.0, enter_dream_state);  
    }
    else
    if (state == SLEEP_STAGE_2)
    {
        state = FULL_SLEEP_IDLE;
        spell_caster->catch_tell("Softly, as if breaking " +
                                 "through a thin membrane, " +
                                 "you fully enter a dreaming " +
                                 "state. With the aid of " +
                                 "Psuchae, you might be able " +
                                 "to travel in the shadowlands " +
                                 "between reality and the dream " +
                                 "world. <dreamhelp> gives you" +
                                 " information on what actions " +
                                 "are possible here.\n");
        tell_room(environment(spell_caster), QCTNAME(spell_caster) +
                  " seems to have entered a deep state of sleep.\n",
                  (spell_caster));
        spell_caster->add_prop(SCOP_O_SLEEP_LOCATION, environment(spell_caster));
        
        spell_caster->add_prop(LIVE_I_SEE_DARK, 
                               spell_caster->query_prop(LIVE_I_SEE_DARK) + 20);
        spell_caster->add_prop(LIVE_M_NO_SCRY, 1);
        env = environment(spell_caster);   
        spell_caster->move_living("M", DREAM_ROOM, 1, 1);
        spell_caster->set_no_show();

        create_clone(spell_caster, env);
        
        // In order to prevent auto attacking of enemies, we
        // store the current set of enemies
        enemies = spell_caster->query_enemy(-1);
        spell_caster->stop_fight(enemies);
        
        set_alarm(itof(30 + random(30)), 0.0, dream_check);
    }
}

void
wake_me_up(object spell_caster)
{
    spell_caster->catch_tell("You can no longer maintain the link to your" +
                             " presence in the dream world, and slowly" +
                             " begin your ascent to consciousness.\n");
       
    if (environment(spell_caster) != find_object(DREAM_ROOM))
    {
        tell_room(environment(spell_caster), "You feel the intruding " +
                  "presence fade and disappear.\n", spell_caster);
        spell_caster->move_living("M", DREAM_ROOM, 1, 1);
    }
        
    state = WAKING_UP;
    set_alarm(itof(10 + random(20)), 0.0, dispel_spell_effect);
}


int
start()
{
    int gstat, wis;

    set_spell_effect_desc("dreamwalk");
    spell_caster->add_prop(LIVE_I_SEE_DARK, 
                           spell_caster->query_prop(LIVE_I_SEE_DARK) - 20);
    spell_caster->add_stun();
    
    spell_caster->add_prop(LIVE_S_SOULEXTRA, "sleeping softly");
    
    set_alarm(itof(10 + random(10)), 0.0, enter_dream_state);

    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    set_alarm(itof(MIN(1200, 600+2*gstat+wis+random(gstat))),
              0.0, &wake_me_up(spell_caster));
    return 1;
}


void
dream_check()
{
    
    if (!(environment(spell_caster) == find_object(DREAM_ROOM) ||
          environment(spell_caster) == scried_room))
    {
        //Caster has linkdied while present at a location:
        if (spell_caster->query_prop(PLAYER_S_LD_IN_ROOM))
        {
            spell_caster->add_prop(PLAYER_S_LD_IN_ROOM, 
                          file_name(spell_caster->query_prop(SCOP_O_SLEEP_LOCATION)));
        }
        dispel_spell_effect(spell_caster, 1);
        return;
    }
        tell_room(environment(spell_caster), "You still feel the " +
                  "intruding presence in here.\n", spell_caster);
        set_alarm(itof(30 + random(30)), 0.0, dream_check);        
}

/*
 *   This function takes a pointer to a player as argument, and determines
 *   if we are allowed to scry that person, returning 1 if we can and 0 if
 *   not. 
 */
int
check_user(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_wiz_level()) 
    {
        return 0;
    }
    
    if (environment(player)->query_prevent_snoop())
    {
        return 0;
    }
    
    if (environment(player) == find_object("/d/Genesis/obj/statue"))
    {
        return 0;
    }

    if (player == spell_caster)
    {
        return 0;
    }
 
    if (player->query_prop(SCOP_O_SLEEP_LOCATION))
    {
        return 0;
    }

    if(player->query_prop(LIVE_M_NO_SCRY))
    {
      return 0;
    }

    if (player->is_spirit_member())
    {
        return 1;
    }
    
    if (spell_caster->query_met(player))
    {
        return 1;
    }
    
    return 0;
}

/*
 *  This function intercepts all commands.
 */
int
attempt_action(string str)
{
    /* Only paralyze our environment */
    if (environment() != spell_caster)
    {
        return 0;
    }

    if (query_verb() == "look")
    {
        spell_caster->catch_tell("You cannot look at things while" +
                                 " dreaming.\n");
    }
    else
    /* Some commands may always be issued, except look - eliminated above. */
    if (CMDPARSE_PARALYZE_CMD_IS_ALLOWED(query_verb()))
    {
        return 0;
    }
    else
    if (!state || state == SLEEP_STAGE_1 || state == SLEEP_STAGE_2)
    {
        spell_caster->catch_tell("You are attempting to descend into the" +
                                 " dream world, and are unable to do that.\n");
    }
    else 
    if (state == DREAM_TRAVELLING)
    {
        spell_caster->catch_tell("You are travelling in the dream world," +
                                 " and are unable to do that.\n");
    }
    else    
    if (state == WAKING_UP)
    {
        spell_caster->catch_tell("You are on your way back to the waking" +
                                 " world, and are unable to do that.\n");
    }
    else
    if (member_array(query_verb(), allowed_actions) != -1)
    {
        return 0;
    }
    else
    {
        spell_caster->catch_tell("You are unable to do that in the dream" +
                                 " world.\n");
    }
    return 1;    
}


void
arrive_at_target(object target)
{
    int diff = TASK_ROUTINE;

    if (spell_caster->query_wiz_level())
    {
        diff = 100;
    }

    if (!check_user(target) ||
        spell_caster->resolve_task(diff, (({TS_WIS, TS_OCC})), target,
                                  (({SKILL_WEIGHT, 200,  
                                     SS_FORM_DIVINATION, SKILL_END, 
                                     TS_INT}))) <= 0 ||
        target->query_magic_res(MAGIC_I_RES_MAGIC) > 25 ||
        sizeof(filter(all_inventory(environment(target)), 
               &->query_wiz_level())))
    {
        state = FULL_SLEEP_IDLE;
        spell_caster->catch_tell("Your search is in vain, you find nothing" +
                                 " but shadows.\n");
    }
    else
    {
        spell_caster->catch_tell("After journeying for a time through the" +
                                 " dream world, and witnessing many " +
                                 "strange and outlandish sights, you " +
                                 "begin to draw closer to your target. " +
                                 "You arrive at a place where the border " +
                                 "between the dream world and the real " +
                                 "world is particularly thin. Here you " +
                                 "can <watch> or attempt to <enter> the " +
                                 "waking world.\n");
        state = FULL_SLEEP_WATCHING;
        scried = target;
    }
}

int
do_wake(string str)
{
    spell_caster->catch_tell("You begin your ascent to consciousness.\n");
        
    if (environment(spell_caster) != find_object(DREAM_ROOM))
    {
	tell_room(environment(spell_caster), "You feel the intruding " +
                  "presence fade and disappear.\n", spell_caster);
        spell_caster->move_living("M", DREAM_ROOM, 1, 1);
    }
        
    state = WAKING_UP;
    set_alarm(itof(10 + random(20)), 0.0, &dispel_spell_effect(spell_caster));
    
    return 1;
}


int
do_sense(string str)
{
    string desc, *list;
    
    list = filter(users(), check_user)->query_name();
    list = sort_array(list);
    
    if (!sizeof(list))
    {
        spell_caster->catch_tell("You cannot sense anyone.\n");
    }
    else
    {
        desc = "Reaching out with your mind, you sense the following" +
        " presences that you may be able to visit: " + COMPOSITE_WORDS(list)
        + ".\n";
        spell_caster->catch_tell(desc);
    }
    
    return 1;
}
                

int
do_dreamhelp(string str)
{
    string desc;
    
    desc = "You can perform the following actions in the dream world:\n" +
        "<dreamhelp>      - Display this message.\n" +
        "<sense>          - Sense what presences you might reach from the" +
        " dream world.\n" +
        "<wake>           - Return to the waking world.\n" +
        "<visit [target]> - Attempt to visit someone.\n" +
        "<watch>          - Watch someone you are currently visiting.\n" +
        "<enter>          - Attempt to project your presence into the waking\n" +
        "                   world at the person you are currently visiting\n" +
        "                   and observe the happenings there. While " +
                            "projected,\n" +
        "                   you will be invisible, but may still be " +
                            "vulnerable\n" +
        "                   to the dangers of the waking world.\n" +
        "                   It is fully possible to die in the dream. "+
                            " Bewarned!\n" +
        "<withdraw>       - Withdraw your projection from the waking world.\n";
    
    spell_caster->catch_tell(desc);
    
    return 1;
}

/*
 * Introduce the mode int here to handle different ways this spell is dispelled
 * If mode is set, that means just dispel the spell without any teleporting or 
 * messages,
 * as the caster has been teleported away either by going linkdead or wizard
 * action.
 */
varargs public int
dispel_spell_effect(object dispeller, int mode)
{

    if (!objectp(spell_caster->query_prop(SCOP_O_SLEEP_LOCATION)))
    { 
        spell_caster->catch_tell("Your attempt to enter the dream world has" +
                                 " been disrupted and you awake groggily.\n");
        tell_room(environment(spell_caster), QCTNAME(spell_caster) + 
                  " awakens groggily.\n", (({spell_caster})));
        spell_caster->add_prop(LIVE_I_SEE_DARK, 
                               spell_caster->query_prop(LIVE_I_SEE_DARK) + 20);            
    }
    else 
    if (!mode)
    {    
        spell_caster->catch_tell("You return to the waking world.\n");
        tell_room(environment(spell_caster), "You feel the intruding " +
                  "presence disappear.\n", spell_caster);
        spell_caster->move_living("M", DREAM_ROOM, 1, 1);
        spell_caster->unset_no_show();
        spell_caster->unset_no_show_composite();
        scop_clone->remove_object();
        spell_caster->move_living("M", 
            spell_caster->query_prop(SCOP_O_SLEEP_LOCATION), 1, 1);            
        tell_room(environment(spell_caster), QCTNAME(spell_caster) + 
                  " opens "+spell_caster->query_possessive()+ " eyes and" +
                  " rises smoothly to " + spell_caster->query_possessive() + 
                  " feet.\n", spell_caster);
    }
    else
    {
        spell_caster->unset_no_show();
        spell_caster->unset_no_show_composite();
        spell_caster->catch_tell("Your dream travels have been disrupted," +
                                 " and you return to wakefulness.\n");    
    }
    
    
    spell_caster->remove_prop(SCOP_O_SLEEP_LOCATION);
    
    if (spell_caster->query_prop(LIVE_S_SOULEXTRA) == "sleeping softly");
    {
        spell_caster->remove_prop(LIVE_S_SOULEXTRA);
    }
    
    spell_caster->remove_stun();
    spell_caster->remove_prop(LIVE_M_NO_SCRY);
    // Re-add the old enemies.
    object cobj = spell_caster->query_combat_object();
    foreach (object enemy : enemies)
    {
        if (!objectp(enemy))
        {
            continue;
        }
        cobj->cb_add_enemy(enemy, 0);
    }
    
    remove_spell_effect_object();
    return 1;
}


int
do_enter(string str)
{   

    if (state == FULL_SLEEP_PRESENT)
    {
        notify_fail("You have already entered the waking world!\n");
        return 0;
    }   
    else
    if (state != FULL_SLEEP_WATCHING)
    {
        notify_fail("You are not visiting anyone at the moment," +
                    "so you can not enter the waking world.\n");
        return 0;
    }
    if (spell_caster->query_mana() < 40)
    {
        notify_fail("You do not have the mental strength to" +
                    " enter the waking world.\n");
        return 0;
    }    
    else
    if (!check_user(scried) ||
        scried->query_magic_res(MAGIC_I_RES_MAGIC) > 25 ||
        environment(scried)->query_prop(ROOM_M_NO_TELEPORT) ||
        sizeof(filter(all_inventory(environment(scried)), 
            &->query_wiz_level())))
    {
        notify_fail("You find yourself unable to enter the" +
            " waking world at this location.\n");
        return 0;
    }
    else
    {
        spell_caster->catch_tell("Straining with the effort of " +
                                 "projecting your presence into " +
                                 "the waking world, you arrive, " +
                                 "somewhat disoriented.\n");
        
        scried_room = environment(scried); 
        state = FULL_SLEEP_PRESENT;
        spell_caster->add_mana(-40);
        spell_caster->move_living("M", scried_room, 1, 0);
        tell_room(environment(spell_caster), "You feel an " +
                  "intruding presence observing you.\n",
                  spell_caster);
        update_actions();
    }
    
    return 1;
}

int
do_visit(string str)
{
    object target;

    if (spell_caster->query_mana() < 30)
    {
        notify_fail("You don't have the mental strength to " +
                    "visit anyone.\n");
        return 0;
    }
    
    if (stringp(str))
    {
        target = find_living((lower_case(str)));
        
        if (!objectp(target))
        {
            notify_fail("You are unable to find anyone with " +
                        "that name.\n");
            return 0;
        }
    }
    else
    {
        notify_fail("Visit whom?\n");
        return 0;
    }
    
    if (!check_user(target))
    {
        notify_fail("You are unable to find anyone with " +
                    "that name.\n");
        return 0;
    }
    
    if (state == FULL_SLEEP_PRESENT)
    {
        notify_fail("You are projected into the waking world!" +
                    "You need to withdraw before you can " +
                    "visit anyone.\n");
        return 0;
    }
    
    
    if (state == FULL_SLEEP_WATCHING)
    {
        // Already watching correct location?
        
        if (objectp(scried) && target == scried)
        {
            notify_fail("You are already visiting that person!\n");
            return 0;
        }
        
    }
    
    spell_caster->catch_msg("Holding " + LANG_POSS(target->query_name()) + 
                            " image in your mind, you begin searching the " +
                            "dream world for a place where you can watch " +
                            target->query_objective() + ".\n"); 

    state = DREAM_TRAVELLING;
    
    if (environment(spell_caster) != find_object(DREAM_ROOM))
    {
        spell_caster->move_living("M", DREAM_ROOM, 1, 1);
    }
    
    set_alarm(itof(20 + random(20)), 0.0, &arrive_at_target(target));
    
    return 1;
}


int
do_withdraw(string str)
{
    if (state != FULL_SLEEP_PRESENT)
    {
        notify_fail("You are not currently projected into the waking" +
                    " world!\n");
        return 0;
    }
    
    spell_caster->catch_tell("You withdraw from the waking world.\n");
    state = FULL_SLEEP_WATCHING;
    tell_room(environment(spell_caster), "You feel the intruding "+
              "presence fade and disappear.\n", spell_caster);
    spell_caster->move_living("M", DREAM_ROOM, 1, 1);
    return 1;
}


int
do_watch(string str)
{
    string desc;
    object env;

    if (state == FULL_SLEEP_PRESENT)
    {
        notify_fail("You are projected into the waking world, " +
                    "and have to withdraw before you can <watch>.\n");
        return 0;
    }
    
    if (state != FULL_SLEEP_WATCHING)
    {
        notify_fail("You are not visiting anyone at the moment, so" +
                    " you have noone to watch.\n");
        return 0;
    }    

    if (spell_caster->query_mana() < 15)
    {
        notify_fail("You do not have the mental strength to watch the" +
                    " waking world.\n");
        return 0;
    }

    if (!objectp(scried))
    {
        notify_fail("You no longer sense the person you are watching in "
            + "the waking world.\n");
        return 0;
    }
    
    env = environment(scried);   
    
    if (!check_user(scried) || sizeof(filter(all_inventory(env), 
                                      &->query_wiz_level())))
    {
        notify_fail("Something obstructs your view of the waking world." +
                    " You cannot see anything.\n");
        return 0;
    }
 
    tell_room(env, "You suddenly feel an intruding presence in " +
                   "here.\n", spell_caster);

    set_this_player(spell_caster);

    desc = ("\n" + env->long(0, TP) + contents_desc(env));


    if (desc[strlen(desc)-1] == '\n')
        desc = desc[0..(strlen(desc)-2)];
    
    spell_caster->add_mana(-15);
    tell_object(spell_caster,"Surrounded by the haze of the dream " + 
                             "world, through your window into the " +
                             "waking world, you see:\n " +
                             desc + "\n");
            
    set_this_player(TP);        

    return 1;    
}

/*
 * Function name: init
 * Description:   Called when meeting an object
 */
void
init()
{
    ::init();

    add_action(do_visit, "visit");
    add_action(do_enter, "enter");
    add_action(do_withdraw, "withdraw");
    add_action(do_watch, "watch");
    add_action(do_wake, "wake");
    add_action(do_sense, "sense");
    add_action(do_dreamhelp, "dreamhelp");
    add_action(attempt_action, "", 1);    
}

