
/*     
    This is the cmdsoul of the Calian guild

    coder(s):   Glykron & Maniac
    history:
                20. 4.93   created                          Glykron
                16. 8.93   move behind delay added          Glykron
                 1. 2.94   emotes and list warriors added   Maniac
                    3.94   dismemberment added to swarm     Maniac
                    3.94   move behind tempr protection     Maniac
                    5.94   council additions - swarm check  Maniac
                29.11.94   move behind protection as vbfc   Rogon
                 8.12.94   toggle of insignia on/off added  Maniac
                 9. 1.95   query_wiz_dom for query_domain   Maniac
                15. 1.95   better swarm descriptions        Maniac
                 7. 2.95   "interactive" checks in swarm    Maniac
                 15.3.95   emotes split off                 Maniac 
                 28.3.95   included help                    Maniac
                 28.4.95   added ctaunt to command list     Maniac
                 11/5/95   cinfo, center and cremove added  Maniac
                  5/6/95   swarm pen handled differently    Maniac
                  7/7/95   initial prep for swarm added     Maniac
                 14/7/95   swarm changed for lhand/rhand choice   Maniac
                 20/7/95   swarm delay changes              Maniac
                 31/8/95   team emotes added                Maniac
                30/10/95   more team names                  Maniac
                16/11/95   more team emotes added           Maniac
                30/11/95   swarm 9/5, change down           Maniac
                22/12/95   change to list_active_calians    Maniac
                27/12/95   special titles feature added     Maniac
                25/1/96    move behind maintained           Maniac
                5/2/96     notify_fail in swarm             Maniac 
                2/2/96     move behind modified             Maniac
               21/3/96     title handling modified          Maniac
               30/3/96     underwater block and new  
                           emotes                           Maniac
              4/4/96       fine tuning of emotes            Maniac
              2/5/96       call_out -> set_alarm            Maniac
             17/5/96       special title handling altered   Maniac 
              2/6/96       swarm bug corrected              Maniac
              2/9/96      swarm takes a little mana        Maniac
              5/9/96      check for attack delay (stun)    Maniac
             17/9/96      calian options commands added    Maniac
             4/10/96      new team titles, lowered swarm
                          mana and added bit of fatigue,
                          corrected mb bug                 Maniac
             7/10/96      modularised the specials into 
                          .c files                         Maniac
            26/10/96      applicants command added,        Maniac 
                          removed "invulnerability" and
                          spiralling problems from
                          move behind.                     Maniac
            26/2/97       capp made generally available    Maniac
            21/11/98      mbsw updated                     Maniac
             7/5/99       short delay before move behind
                          can be used after an attack      Maniac 
            26/10/00      move behind takes tanker into 
                          account                          Maniac

    purpose:    to load commands into a Calian warrior
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/cmd/std/command_driver";
inherit "/cmd/std/soul_cmd";

int is_calian(object tp);
object query_main_weapon(object o, string s);
int maul_state(object tp); 
int swarm_state(object tp); 
int filter_attack_team(object calian, object enemy); 
int special_tell_watcher(string str, object me, object enemy, mixed notell); 


#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <state_desc.h>
#include <options.h>
#include <std.h>
#include <adverbs.h>
#include <filter_funs.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define MY this_player()->query_possessive()

#define UNDER_WATER_BLOCK  \
   if (UNDER_WATER(this_player())) \
        {  notify_fail("Not under water.\n"); return 0; }

#define IN_WATER_BLOCK  \
   if (IN_WATER(this_player())) \
        {  notify_fail("Not in water.\n"); return 0; }

#include "soulconst.h" 
#include "emotes1.c"
#include "emotes2.c"
#include "emotes3.c"
#include "team_emotes.c"
#include "help.c"
#include "swarm.c"
#include "maul.c" 


/*
 * Function name: get_soul_id
 * Description:   give identification of soul
 * Arguments:     none
 * Returns:       string with id
 */
string
get_soul_id()
{
    return "Calian";
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this one as cmd soul
 * Arguments:     none
 * Returns:       always 1
 */
int
query_cmd_soul()
{
    return 1;
}

int
is_calian(object living)
{
    return living->query_guild_name_occ() == GUILD_NAME;
}

int
is_attacking_this_living(object enemy, object tp)
{
    return enemy->query_attack() == tp;
}


void
reattack_object(object enemy, object friend)
{
    enemy->stop_fight(friend);
    enemy->attack_object(friend);
}

void
ready_to_move_behind_now(object tp)
{
    tp->remove_prop(CALIAN_I_JUST_MOVED_BEHIND);
    tp->catch_msg("You are ready to try to move behind again.\n");
}



void
cleanup_mb_info(object player)
{
    if (!objectp(player)) 
        return;

    player->remove_prop(OBJ_M_NO_ATTACK); 
}


/*
 * Function name:   behind_time_left
 * Description:     This is a support function which determines
 *                  how much time a Calian is "behind" another
 *                  friend.
 * Arguments:       object tp         - Person behind.
 *                  object friend     - Who tp is behind.
 *                  int start_time    - When tp moved behind friend.
 *                  int behind_time   - Default duration in seconds behind.
 * Returns:         ret > 0  : Is behind for ret seconds more.
 *                  ret <= 0 : Is *not* behind the friend no more.
 * 
 * Author:          Sir Rogon.
 */
private int 
behind_time_left(object tp, object friend, int start_time, int behind_time)
{
    if (living(tp) && living(friend) &&
        CAN_SEE_IN_ROOM(tp) && CAN_SEE(tp, friend))
        return start_time + behind_time - time(); 
    else
        return -1;
}


/* 
 * Function:     write_attack_mb_message 
 * Description:  Writes messages when someone who has moved behind 
 *               is attacked, telling those who do not have the 
 *               option set for "see fights" or "gagmisses" of 
 *               the attempted attack and its failure. 
 */ 
void 
write_attack_mb_message(object targ, object friend, object attacker) 
{
    object *liv = 
        FILTER_PLAYERS(all_inventory(environment(targ))) - 
        ({ targ, friend, attacker }); 
    int i; 

    for (i = 0; i < sizeof(liv); i++) { 
        if (!liv[i]->query_option(OPT_BLOOD) && 
            !liv[i]->query_option(OPT_GAG_MISSES)) { 
            tell_object(liv[i], attacker->query_The_name(liv[i]) + 
                " attempts to attack " + targ->query_the_name(liv[i]) + 
                " but " + targ->query_pronoun() + 
                " evades the onslaught with the help of " + 
                friend->query_the_name(liv[i]) + ".\n"); 
        } 
    } 

    if (!targ->query_option(OPT_BLOOD) && 
        !targ->query_option(OPT_GAG_MISSES)) { 
        tell_object(targ, attacker->query_The_name(targ) + 
            " attempts to attack you but you evade " + 
            "the onslaught with the help of " + 
            friend->query_the_name(targ) + ".\n"); 
    } 

    if (!friend->query_option(OPT_BLOOD) && 
        !friend->query_option(OPT_GAG_MISSES)) { 
        tell_object(friend, attacker->query_The_name(friend) + 
            " attempts to attack " + targ->query_the_name(attacker) + 
            " but " + targ->query_pronoun() + 
            " evades the onslaught with your help.\n"); 
    } 
}


/* 
 * Function name:   calian_is_behind 
 * Description:     This function is normally called as a value by function 
 *                  call. It should return a string if text == 1, the time 
 *                  left if text == 0. It used both for the properties 
 *                  OBJ_M_NO_ATTACK and "calian_is_attacked". 
 * Arguments:       tp - this player. 
 *                  friend - Who tp is behind. 
 *                  start_time - When tp moved behind friend. 
 *                  behind_time - For how long is he/she behind? 
 *                  text - Produce text (1) or time (0). 
 * Returns:         A text or the time left. 
 * 
 * Author:          Sir Rogon. 
 */
mixed
calian_is_behind(mixed tp, mixed friend, mixed start_time, mixed behind_time, 
                 mixed text)
{
    int time; 
    object attacker = this_player(); 

    /* Resolve string parameters with find_object() and atoi(). */
    if (stringp(tp)) 
	  tp = find_object(tp); 
    if (stringp(friend)) 
	  friend = find_object(friend); 
    start_time = atoi(start_time); 
    behind_time = atoi(behind_time); 
    text = atoi(text); 

    time = behind_time_left(tp, friend, start_time, behind_time); 
    if (time > 0) { 
	if (text) { 
          if (objectp(attacker) && 
              attacker != tp && 
              attacker != friend && 
              present(attacker, environment(tp))) { 
              write_attack_mb_message(tp, friend, attacker); 
          } 
	    return "That opponent has temporarily maneuvered out " + 
		     "of harm's way by moving behind.\n"; 
      } 
	else
	    return time;
    } 
    else 
	return 0;
}



/*
 * Function name: move_behind
 * Description:   executes the move behind command
 * Arguments:     str - predicate
 * Returns:       success
 */
int
move_behind(string str)
{
    string prep, friend_name, swarm_hand, vb, *tmp;
    object tp, this, friend, attacker, *team, *enemies;
    int number_enemies, tm;
    int mb, i, d, top_dex, total_for, total_against;

    if (!str)
        return 0;

    vb = query_verb(); 

    if (vb == "mbsw") {
        if (sizeof(tmp = explode(str, " "))) { 
            swarm_hand = tmp[sizeof(tmp)-1]; 
            switch (swarm_hand) {
                case "lhand" : 
                case "rhand" : 
                     if (sizeof(tmp) > 1) 
                         friend_name = implode(tmp[0..sizeof(tmp)-2], " ");
                     else
                         friend_name = "";  
                     break; 
                default : 
                     swarm_hand = 0; 
                     friend_name = str;
                     break; 
            }
        }
        else
            friend_name = str; 
    }
    else { 
        if (sscanf(str, "%s %s", prep, friend_name) != 2 || prep != "behind")
        {
            if (explode(str, " ")[0] == "behind")
                 NF("Move behind whom ?\n");
            else
                NF("Move what ?\n");
            return 0;
        }
    } 

    tp = TP;
    friend_name = lower_case(friend_name);
    friend = present(friend_name, environment(tp));
    if (!friend)
    {
        NF("Move behind whom ?\n");
        return 0;
    }

    if (!living(friend))
    {
        NF("You can only move behind living beings if you actually expect " +
            "to get away.\n");
        return 0;
    }

    tm = time();

    if (tm - tp->query_prop(CALIAN_I_LAST_ATTACK_TIME) < 3) {
        notify_fail("Having recently launched an attack " +
                    "you are not yet ready to move behind.\n"); 
        return 0; 
    }

    /* This code prevents the tactic known as `spiralling' which 
       can unbalance the attack/ */ 
    if ((tm - tp->query_prop(CALIAN_I_LAST_MBD_BY_AT_TIME)) <  
        (3 * (SWARM_PREP_TIME + SWARM_EXEC_TIME) / 2)) {  
        notify_fail("Someone moved behind you very recently, you " +
                    "may not use move behind just yet.\n"); 
        return 0;
    } 
    tp->remove_prop(CALIAN_I_LAST_MBD_BY_AT_TIME); 

    this = THIS;
    enemies = filter(all_inventory(environment(tp)), 
                     &is_attacking_this_living(,tp));
    number_enemies = sizeof(enemies);
    team = tp->query_team_others();

    attacker = tp->query_attack();

    /* Check for pigeons and such :) */ 
    if (objectp(present(attacker, tp))) { 
        notify_fail("You can't get away from something you are carrying!\n"); 
        return 0;
    } 

    if (!(mb = tp->query_skill(SS_MOVE_BEHIND))) {
        notify_fail("You have no skill in moving behind team members during " +
                    "battle!\n");
        return 0;
    }
    else if (!number_enemies) {
        notify_fail("No-one is attacking you!\n");
        return 0;
    }
    else if (!sizeof(team)) {
        notify_fail("You are not a member of a team.\n");
        return 0;
    }
    else if (member_array(friend, team) == -1) {
        tp->catch_msg(QCTNAME(friend) + " is not a member of your team.\n");
        return 1;
    }
    else if (tp->query_prop(CALIAN_I_JUST_MOVED_BEHIND)) {
        notify_fail("You are not ready to try to move behind anyone again " +
                    "yet.\n");
        return 0;
    }
    else 
    { 
        tp->add_prop(CALIAN_I_JUST_MOVED_BEHIND, 1); 

        /* Estimate most powerful enemy */ 
        top_dex = 0; 
        for (i = 0; i < sizeof(enemies); i++) 
            if ((d = enemies[i]->query_stat(SS_DEX)) > top_dex)  { 
                 attacker = enemies[i]; 
                 top_dex = d; 
             } 

        total_for = 
          ((mb * (tp->query_stat(SS_DEX) + 
                  tp->query_stat(SS_WIS) + 
                  tp->query_stat(SS_INT) + 
                  friend->query_stat(SS_STR) + 
                  friend->query_stat(SS_DIS))) / 100); 

        total_against = (top_dex + attacker->query_stat(SS_WIS) + 
                        (number_enemies * 16)); 

        if ((random(total_for) + mb)  > random(total_against)) 
        {
            map(enemies, &reattack_object(,friend));
            tp->catch_msg("You move behind " + QTNAME(friend) +
                " and your enemies move to attack " +
                friend->query_objective() + ".\n");
            friend->catch_msg(QCNAME(tp) + " moves behind you, and " +
                tp->query_possessive() + " enemies move to attack you!\n");
            tell_room(environment(tp), QCTNAME(tp) + " moves behind " +
                QTNAME(friend) + ", who is attacked by " +
                tp->query_possessive() +
                " enemies!\n", ({ tp, friend }) );

	    /* Setting up the OBJ_M_NO_ATTACK prop as VBFC. */
            tp->add_prop(OBJ_M_NO_ATTACK,
			 "@@calian_is_behind:" +    // Function name
			 file_name(this) + "|" +    // Object/file name
			 file_name(tp) + "|" +      // tp
			 file_name(friend) + "|" +  // friend
			 tm + "|" +             // start time
			 MB_NO_ATTACKED_TIME + "|" +     // behind time
			 1 + "@@");                 // Produce text.

            /* After a successful move behind, one may not 
               move behind again for twice the period for which
               one may not be attacked.. this ensures against 
               "invulnerability" */ 
            set_alarm(itof(MB_NO_ATTACKED_TIME * 2), 0.0, 
                             &ready_to_move_behind_now(tp));

            set_alarm(itof(MB_NO_ATTACKED_TIME), 0.0, 
                      &cleanup_mb_info(tp));  

            if (is_calian(friend)) 
                friend->add_prop(CALIAN_I_LAST_MBD_BY_AT_TIME, tm); 

            if (vb == "mbsw")  { 
                set_this_player(tp); 
                return swarm(swarm_hand);  
            } 
	}
        else { 
            write("The enemy onslaught is too overwhelming for you " +
                  "to manuever.\n");
            set_alarm(itof(MOVE_BEHIND_DELAY), 0.0, 
                             &ready_to_move_behind_now(tp));
        } 
    }

    return 1;
}



/* The function team_title(str) is intended to be used to set
     a special team title for the Calian should s/he desire, by 
     selection (using a number) from the preset titles in *team_title_list.
     Typing simply "cteam" results in the player being told what
     team title, if any, has previously been set.
*/
int
cteam(string str)
{
    object tp;
    string team_title;
    int i, selection;

    tp = TP;
    if (!is_calian(tp))
        return 1;

    if (!strlen(str))
    {
        team_title = tp->query_prop(CALIAN_S_TEAM_TITLE);
        if (stringp(team_title))
            tp->catch_msg("Your team title is: " + team_title + ".\n");
        else
            tp->catch_msg("You've set no team title.\n");
        tp->catch_msg("\nThe possible team titles are:\n"); 
        for (i = 0; i < sizeof(team_title_list); i++)  
            tp->catch_msg((i+1) + ": " + team_title_list[i] + ".\n"); 
        return 1;
    }
    else
    {
        selection = atoi(str);
        if (selection < 0 || selection > sizeof(team_title_list))
        {
            NF("The number chosen is not in the range 0 - " +
               sizeof(team_title_list) + ".\n");
            return 0;
        }

        if (selection == 0) {
            tp->remove_prop(CALIAN_S_TEAM_TITLE);
            tp->catch_msg("Calian team title turned off.\n");
            return 1;
        }
        team_title = tp->query_name() + "'s" + team_title_list[selection-1];
        tp->add_prop(CALIAN_S_TEAM_TITLE, team_title);
        tp->catch_msg("Your team title is now set to: " + team_title + ".\n");
            return 1;
    }
}


int 
calian_insig()
{
    object tp = TP;
    if (!tp->query_prop(CALIAN_I_WEARING_INSIGNIA)) {
        tp->catch_msg("You wear your Calian insignia.\n");
        tp->add_prop(CALIAN_I_WEARING_INSIGNIA, 1);
    }
    else {
        tp->catch_msg("You remove your Calian insignia.\n");
        tp->remove_prop(CALIAN_I_WEARING_INSIGNIA);
    }
    return 1;
}

/* list_active_calians()
 *
 * This function will list all active Calians/Calian Warriors.
 * It is copied and changed from the Rangers command to list all
 * active Rangers.
 *
 * Originally Coded by Lord Elessar Telcontar of Gondor
 *
 * Revision history:
 * /Mercade, altered for the Calians on 6 Janury 1994
 * Revised by Maniac 2/10/98
 */
int
list_active_calians()
{
    string g_name, g_short;
    int i;
    int cnt = 0;
    object ring;
    object *list;
    int warriors;
    string *name_list, s_desc, p_desc;

    setuid(); 
    seteuid(getuid()); 

    warriors = query_verb() == "warriors";
    if (warriors) { 
        s_desc = "Calian Warriors"; 
        p_desc = "Calian Warriors"; 
    } 
    else {
        s_desc = "Calian"; 
        p_desc = "Calians"; 
    } 

    write("These " + p_desc + " are currently playing:\n");
    name_list = ({ }); 
    list = users();
    for (i = 0; i < sizeof(list); i++)
    {
        if (!is_calian(list[i]))
            continue;

        g_name = capitalize(list[i]->query_real_name());

        /* Don't want a jr's name on the guildlist */
        if (extract(g_name, -2) == "jr" && !TP->query_wiz_level())
            continue;

        if (!list[i]->query_wiz_level() || 
            (!warriors && !list[i]->query_invis() && 
             (COUNCIL_CODE->is_calian_wiz(list[i]) ||
              list[i]->query_prop(LIVE_I_ALWAYSKNOWN))))
        {
            if (query_verb() == "clevwho") 
                g_short = ("the " + list[i]->query_calian_normal_title());
            else
                g_short = list[i]->query_title();
           
            name_list += ({ g_name + " " + g_short }); 
            cnt++;
        }
    }

    name_list = sort_array(name_list); 
    for (i = 0; i < sizeof(name_list); i++) 
        write("- " + name_list[i] + "\n");

    write("There " + (cnt == 1 ? "is " : "are ") + 
          "now " + cnt + " " + (cnt == 1 ? s_desc : p_desc) + 
          " playing.\n");
    return 1;
}



void
reset_calian_title(object tp, int v)
{
    if (!objectp(tp)) 
        return;

     if (v & CALOPT_TITLE_NORMAL) 
         v -= CALOPT_TITLE_NORMAL; 

     if (v & CALOPT_TITLE_SPECIAL)
         v -= CALOPT_TITLE_SPECIAL;

     if (v & CALOPT_TITLE_MIXED)
         v -= CALOPT_TITLE_MIXED; 

     tp->set_skill(CALIAN_OPTIONS, v); 
}


/* Allows one to see / set a special Calian title. */
int
calian_title(string str)
{
    object tp;
    mixed t;
    int i;
    string m, n, *els;

    tp = this_player();

    t = tp->query_calian_special_title();
    n = capitalize(tp->query_real_name());
    if (!stringp(str) || !strlen(str)) {
        m = "Your Calian special title ";
        if (!t)
            m += "has not yet been set up.\n";
        else 
            m += ("is currently: " + t + ".\n"); 

        tell_object(tp, m); 
        return 1;
    }

    els = explode(str, " "); 
    if (sizeof(els) != 2) {
        notify_fail("You attempted to set your special title, but gave the " +
                    "wrong number of title elements. There must be two.\n");
        return 0;
    }

    if (CALIAN_TITLE_HANDLER->query_valid_title(els[0], els[1]) == 0) { 
        notify_fail("You attempted to set your special title, but " +
                    "entered a selection that was not valid.\n");
        return 0;
    }

    if (CALIAN_TITLE_HANDLER->query_title_taken(els[0], els[1])) { 
        notify_fail("You attempted to set your special title, but " +
                    "alas that selection had already been taken by " +
                    "someone else.\n");
        return 0;
    }

    if (!tp->query_wiz_level() &&
        !CALIAN_TITLE_HANDLER->query_time_to_set_title(n)) {
        notify_fail("You attempted to set your special title, but " +
                    "not enough time has passed yet since when you " +
                    "last set it.\n");
        return 0;
    }

    CALIAN_TITLE_HANDLER->set_calian_special_title(n, els[0], els[1]);
    tp->catch_msg("Ok.\n");
    return 1;
}



string
copt_title_status(object tp, int v)
{
     string r;

     r = "Title status: ";

     if (v & CALOPT_TITLE_SPECIAL)
           r += "special.\n";
     else if (v & CALOPT_TITLE_MIXED) 
           r += "mixed.\n"; 
     else if (v & CALOPT_TITLE_NORMAL) 
           r += "normal.\n"; 
     else { 
          tp->set_skill(v | CALOPT_TITLE_NORMAL); 
          r += "normal.\n";
     }

     return r;
}


int
copt_title_set(object tp, int v, string str)
{
    if ((str == "mixed") || (str == "special") || (str == "normal")) {
        reset_calian_title(tp, v); 
        v = tp->query_skill(CALIAN_OPTIONS); 
        if (str == "mixed") { 
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_TITLE_MIXED);
             tp->catch_msg("Your Calian title status is now: mixed.\n"); 
             return 1;
        }
        else if (str == "special") {
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_TITLE_SPECIAL);
             tp->catch_msg("Your Calian title status is now: special.\n"); 
             return 1;
        }
        else if (str == "normal") { 
            tp->set_skill(CALIAN_OPTIONS, v | CALOPT_TITLE_NORMAL);
            tp->catch_msg("Your Calian title status is now: normal.\n");
            return 1;
        }
    } 
    notify_fail("No such value is possible for the title option. " +
                "The possible values are: mixed, special, normal.\n"); 
    return 0;

}


string
copt_dismember_status(object tp, int v)
{
     string r;

     r = "Dismember status: ";

     if (v & CALOPT_DISMEMBER)
           r += "on.\n";
     else 
           r += "off.\n"; 
    return r;
}


int
copt_dismember_set(object tp, int v, string str)
{
    if ((str == "on") || (str == "off")) {
        if (str == "on") { 
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_DISMEMBER);
             tp->catch_msg("Your dismember status is now: on.\n"); 
             return 1;
        }
        else if (str == "off") {
             if (v & CALOPT_DISMEMBER) 
                 tp->set_skill(CALIAN_OPTIONS, v - CALOPT_DISMEMBER);
             tp->catch_msg("Your dismember status is now: off.\n"); 
             return 1;
        } 
    } 
    notify_fail("No such value is possible for the dismember option. " +
                "The possible values are: on, off.\n"); 
    return 0;
}


string
copt_specials_status(object tp, int v)
{
     string r;

     r = "See specials status: ";

     if (v & CALOPT_SEE_SPECIALS)
           r += "on.\n";
     else 
           r += "off.\n"; 

    return r;
}


int
copt_specials_set(object tp, int v, string str)
{
    if ((str == "on") || (str == "off")) {
        if (str == "on") { 
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_SEE_SPECIALS);
             tp->catch_msg("Your see specials status is now: on.\n"); 
             return 1;
        }
        else if (str == "off") {
             if (v & CALOPT_SEE_SPECIALS) 
                 tp->set_skill(CALIAN_OPTIONS, v - CALOPT_SEE_SPECIALS);
             tp->catch_msg("Your see specials status is now: off.\n"); 
             return 1;
         } 
    } 
    notify_fail("No such value is possible for the see specials option. " +
                "The possible values are: on, off.\n"); 
    return 0;
}


string
copt_rack_club_status(object tp, int v)
{
     string r;

     r = "Rack club status: ";

     if (v & CALOPT_RACK_CLUB)
           r += "on.\n";
     else 
           r += "off.\n"; 

    return r;
}

int
copt_rack_club_set(object tp, int v, string str)
{
    if ((str == "on") || (str == "off")) {
        if (str == "on") { 
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_RACK_CLUB);
             tp->catch_msg("Your rack club status is now: on.\n"); 
             present(MEDALLION_ID, tp)->setup_rack_desc(tp); 
             return 1;
        }
        else if (str == "off") {
             if (v & CALOPT_RACK_CLUB) 
                 tp->set_skill(CALIAN_OPTIONS, v - CALOPT_RACK_CLUB);
             tp->catch_msg("Your rack club status is now: off.\n"); 
             present(MEDALLION_ID, tp)->setup_plain_desc(tp); 
             return 1;
         } 
    } 
    notify_fail("No such value is possible for the rack club option. " +
                "The possible values are: on, off.\n"); 
    return 0;
}

int
calian_options(string str)
{
     int v, i;
     object tp;
     string r, *cm;

     tp = this_player(); 
     v = tp->query_skill(CALIAN_OPTIONS); 

     if (!stringp(str) || !strlen(str)) 
          str = "all"; 

     cm = explode(str, " ");  

     if (sizeof(cm) == 1) { 
         r = "";
         if (cm[0] == "all") 
             r = (copt_title_status(tp, v) +  
                  copt_dismember_status(tp, v) +  
                  copt_specials_status(tp, v) +
                  copt_rack_club_status(tp, v));  
         else if (cm[0] == "title") 
             r = copt_title_status(tp, v);  
         else if (cm[0] == "dismember")
             r = copt_dismember_status(tp, v); 
         else if (cm[0] == "specials") 
             r = copt_specials_status(tp, v); 
         else if (cm[0] == "rack")
             r = copt_rack_club_status(tp, v); 

         if (strlen(r))  { 
             tp->more(r); 
             return 1;
         }
         else  { 
            notify_fail("Didn't recognise that option.\n"); 
            return 0;
         } 
     }


    if (sizeof(cm) == 2)  { 
         if (cm[0] == "title") 
             return copt_title_set(tp, v, cm[1]); 
         else if (cm[0] == "dismember")
             return copt_dismember_set(tp, v, cm[1]); 
         else if (cm[0] == "specials") 
             return copt_specials_set(tp, v, cm[1]); 
         else if (cm[0] == "rack") 
             return copt_rack_club_set(tp, v, cm[1]); 
         else { 
             notify_fail("Didn't recognise that option.\n"); 
             return 0;
         }
    }

    notify_fail("Please check your syntax.\n"); 
    return 0;
}


/* Player can get info that another Calian entered about him/herself */
int 
calian_info(string str)
{
    setuid();
    seteuid(getuid());
    if (!str) 
        CALIAN_INFO_HANDLER->list_calians_with_info(this_player());
    else
        CALIAN_INFO_HANDLER->see_info(this_player(), str); 
    return 1;
}


/* Player can get info that the Council entered about an enemy. */
int 
enemy_info(string str)
{
    setuid();
    seteuid(getuid());
    return COUNCIL_CODE->see_enemy_info(str);
}


/* Calian can enter some info about him/herself that other Calians
   can look up.
*/
int
calian_enter()
{
    setuid();
    seteuid(getuid());
    CALIAN_INFO_HANDLER->add_info(this_player());
    return 1;
}


/* 
 * Calian can remove some info about him/herself that s/he previously
 * entered. 
 */
int
calian_remove()
{
    setuid();
    seteuid(getuid());
    CALIAN_INFO_HANDLER->remove_info(this_player());
    return 1;
}


/* 
 *  Recruitment Officers, Council members and wizards may check 
 *  on which applicants are logged in at the moment. 
 */ 
int
calian_applicants(string str) 
{
     int i;
     object tp, p;
     string *c, *r, *a, *l, nm;

     tp = this_player(); 

/* 
   I commented out the checks for having to be a recruiter of council
   member to see what applicants are on. It's harmless enough,  
   if someone wants to re-install this at some point just remove the
   comments. 
               - Maniac Feb 1997


     r = ({ }); c = ({ });

     nm = capitalize(tp->query_real_name());
     r = RECRUITER_CODE->query_recruiters();
     c = COUNCIL_CODE->query_council_members();
     if ((member_array(nm, r) == -1) &&
         (member_array(nm, c) == -1) &&
         (!this_player()->query_wiz_level())) { 
         notify_fail("You do not have rights to that information!\n"); 
         return 0;
     } 

*/ 

     setuid(); 
     seteuid(getuid(this_object()));

     l = ({ }); 
     a = RECRUITER_CODE->query_applicants();

     if (!sizeof(a)) { 
         notify_fail("There are currently no applicants " +
                     "to the Calian guild!\n");
         return 0;
     } 

     for (i = 0; i < sizeof(a); i++) 
         if (p = find_player(lower_case(a[i])))  { 
             if (p->query_linkdead()) 
                 l += ({a[i]+"*"});
             else 
                 l += ({a[i]});  
        } 

     if (!sizeof(l)) { 
         tell_object(tp, "There are currently no applicants logged in.\n");
         return 1;
     } 

     tell_object(tp, "The following applicants are logged in: " + 
                     COMPOSITE_WORDS(l) + ".\n");
     return 1;
}



mapping
query_cmdlist()
{
    return
    ([
        "move" : "move_behind",
        "mbsw" : "move_behind", 
        "swarm" : "swarm",
        "maul" : "maul", 
        "help" : "help",
        "capp" : "calian_applicants", 
        "cteam" : "cteam",
        "cshake" : "calian_shake",
        "clook" : "calian_look",
        "cwarn" : "calian_warn",
        "cwar" : "calian_warcry",
        "cwarcry" : "calian_warcry",
        "cinsig": "calian_insig",
        "cpraise" : "calian_praise",
        "ccurse" : "calian_curse",
        "cwho" : "list_active_calians",
        "clevwho" : "list_active_calians", 
        "warriors" : "list_active_calians",
        "csong" : "calian_song",
        "celeb" : "calian_celeb",
        "celebrate" : "calian_celeb",
        "ctaunt" : "calian_taunt",
        "cinfo"  : "calian_info",
        "ceinfo" : "enemy_info", 
        "ctitle" : "calian_title", 
        "center" : "calian_enter",
        "cremove" : "calian_remove",
        "cni" : "calian_ni",
        "chonk" : "calian_honk", 
        "cl" : "calian_gaze", 
        "cpace" : "calian_pace", 
        "caggr" : "calian_aggression", 
        "coptions" : "calian_options", 
        "cknock" : "calian_knock",
        "cnod" : "calian_nod", 
        "cintro" : "calian_intro", 
        /*  Amelia's additions->emotes2.c */
        "crel" : "calian_relieved",
        "chappy" : "calian_happy",
        "cmisery" : "calian_misery",
        "claugh" : "calian_laugh",
        "cmutter" : "calian_mutter",
        "cfond"	: "calian_fond",
        "cprot" : "calian_protect",
        "cslap" : "calian_slap",
        /*  Digit's additions->emotes3.c */
        "csuspect" : "calian_suspect",
        "camused" : "calian_amused",
        "cconcern" : "calian_concern",
        "cfriend" : "calian_friend",
        "chug" : "calian_hug",
        "cfear" : "calian_fear",
        "cint" : "calian_intim",
        "cdrunk" : "calian_drunk",
        /* Team emotes */
        "ctpost" : "calian_team_posture",     
        "ctprep" : "calian_team_prepare",
        "cthuddle" : "calian_team_huddle",
        "ctcrowd" : "calian_team_crowd",
        "ctleap" : "calian_team_leap", 
        "ctapp" : "calian_team_appraise",
        "ctlaugh" : "calian_team_laugh",
        "ctwar" : "calian_team_warcry", 
        "ctpledge" : "calian_pledge",
    ]);
}

