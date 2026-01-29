
/* 
    This is the cmdsoul of the Calian guild

    coder(s):   Maniac and Glykron 
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
            14/6/01       updates for new commands in 
                          shadow                           Maniac 
            18/4/02       ctitle disabled for trainees     Maniac
            2/5/02        cteam disabled for trainees      Maniac

    purpose:    to load commands into a Calian warrior
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary

#include "defs.h"

inherit "/cmd/std/command_driver"; 
inherit "/cmd/std/soul_cmd"; 
inherit CALIAN_UTILITY;

object query_main_weapon(object living, string p); 

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
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER
#include "/d/Genesis/specials/debugger/debugger_tell.h"

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
 * Function:     query_main_weapon 
 * Description:  returns the main weapon or the weapon
 *               which is specified by the player in the 
 *               string p.
 */
object
query_main_weapon(object living, string p)
{
    object weapon;

    if (p == "lhand" || p == "left") {
        if (objectp(weapon = living->query_weapon(W_LEFT)))
            return weapon;

        if (objectp(weapon = living->query_weapon(W_RIGHT)))
            return weapon;

        return living->query_weapon(W_BOTH);
    }

    if (objectp(weapon = living->query_weapon(W_RIGHT)))
        return weapon;

    if (objectp(weapon = living->query_weapon(W_LEFT)))
        return weapon;

    return living->query_weapon(W_BOTH);
}


/*
 * Function:     swarm 
 * Description:  Wrapper for swarm code in the Calian shadow. 
 */ 
int 
swarm(string str)
{
    return this_player()->calian_swarm(str); 
}


/*
 * Function:     swarm 
 * Description:  Wrapper for maul code in the Calian shadow. 
 */ 
int 
maul(string str)
{
    if (IS_CALIAN_FOLLOWER(this_player()))
    {
        return 0;
    }
    return this_player()->calian_maul(str); 
}


/*
 * Function:     move_behind 
 * Description:  Wrapper for move behind code in the Calian shadow. 
 */ 
int 
move_behind(string str)
{
    return this_player()->calian_move_behind(str); 
}


/* 
 * Function:     mbsw 
 * Description:  Wrapper for mbsw code in the Calian shadow. 
 */ 
int
mbsw(string str)
{
    return this_player()->calian_mbsw(str); 
}


/*
 * Function:     crepeat 
 * Description:  Wrapper for special repeat code in the Calian shadow. 
 */ 
int
crepeat(string str)
{
    return this_player()->calian_auto_repeat(str); 
}


/* 
 * Function:     cprepare 
 * Description:  Wrapper for "prepare to move behind" code in 
 *               the Calian shadow. 
 */ 
int
cprepare(string str)
{
    return this_player()->calian_prepare_to_move_behind(str); 
}


/* 
 * Function:     cadverb 
 * Description:  Wrapper for special adverb code in the Calian shadow. 
 */ 
int
cadverb(string str)
{
    return this_player()->calian_set_adverb(str); 
}


/* 
 * Function:     cchange 
 * Description:  Wrapper for change weapon hand code in the Calian shadow. 
 */ 
int
cchange(string str)
{
    return this_player()->calian_change_hands(str); 
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


/* 
 * The function team_title(str) is intended to be used to set 
 * a special team title for the Calian should s/he desire, by 
 * selection (using a number) from the preset titles in *team_title_list. 
 * Typing simply "cteam" results in the player being told what 
 * team title, if any, has previously been set. 
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

    if (!IS_CALIAN_WARRIOR(tp)) 
    { 
        notify_fail("Only full Calian Warriors can do that.\n"); 
        return 0; 
    } 

    if (!strlen(str))
    {
        team_title = tp->query_prop(CALIAN_S_TEAM_TITLE);
        if (stringp(team_title))
            tp->catch_tell("Your team title is: " + team_title + ".\n");
        else
            tp->catch_tell("You've set no team title.\n");
        tp->catch_tell("\nThe possible team titles are:\n"); 
        for (i = 0; i < sizeof(team_title_list); i++)  
            tp->catch_tell((i+1) + ": " + team_title_list[i] + ".\n"); 
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
            tp->catch_tell("Calian team title turned off.\n");
            return 1;
        }
        team_title = tp->query_name() + "'s" + team_title_list[selection-1];
        tp->add_prop(CALIAN_S_TEAM_TITLE, team_title);
        tp->catch_tell("Your team title is now set to: " + team_title + ".\n");
            return 1;
    }
}


int 
calian_insig()
{
    object tp = TP;
    if (!tp->query_prop(CALIAN_I_WEARING_INSIGNIA)) {
        tp->catch_tell("You wear your Calian insignia.\n");
        tp->add_prop(CALIAN_I_WEARING_INSIGNIA, 1);
    }
    else {
        tp->catch_tell("You remove your Calian insignia.\n");
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
    string g_name, g_short, title;
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
            title = list[i]->query_title();
            if (query_verb() == "clevwho") 
            {
                if (!list[i]->query_calian_normal_title())
                {
                    // If the title doesn't exist, we just use the
                    // regular title.
                    g_short = title;
                }
                else
                {
                    g_short = "the " + list[i]->query_calian_normal_title();
                }
            }
            else
            {
                g_short = title;
            }
            
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

    if (!IS_CALIAN_WARRIOR(tp)) 
    { 
        notify_fail("That feature is only available to full Calian Warriors.\n"); 
        return 0; 
    } 

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
                    "entered a combination that was not allowed or " +
                    "not applicable to your gender.\n");
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
    tp->catch_tell("Ok.\n");
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
     else 
     { 
          tp->set_skill(v | CALOPT_TITLE_NORMAL); 
          r += "normal.\n";
     }

     return r;
}


int
copt_title_set(object tp, int v, string str)
{
    if (!IS_CALIAN_WARRIOR(tp)) 
    { 
        notify_fail("That feature is only available to full Calian Warriors.\n"); 
        return 0; 
    } 

    if ((str == "mixed") || (str == "special") || (str == "normal")) {
        reset_calian_title(tp, v); 
        v = tp->query_skill(CALIAN_OPTIONS); 
        if (str == "mixed") { 
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_TITLE_MIXED);
             tp->catch_tell("Your Calian title status is now: mixed.\n"); 
             return 1;
        }
        else if (str == "special") {
             tp->set_skill(CALIAN_OPTIONS, v | CALOPT_TITLE_SPECIAL);
             tp->catch_tell("Your Calian title status is now: special.\n"); 
             return 1;
        }
        else if (str == "normal") { 
            tp->set_skill(CALIAN_OPTIONS, v | CALOPT_TITLE_NORMAL);
            tp->catch_tell("Your Calian title status is now: normal.\n");
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
             tp->catch_tell("Your dismember status is now: on.\n"); 
             return 1;
        }
        else if (str == "off") {
             if (v & CALOPT_DISMEMBER) 
                 tp->set_skill(CALIAN_OPTIONS, v - CALOPT_DISMEMBER);
             tp->catch_tell("Your dismember status is now: off.\n"); 
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
             tp->catch_tell("Your see specials status is now: on.\n"); 
             return 1;
        }
        else if (str == "off") {
             if (v & CALOPT_SEE_SPECIALS) 
                 tp->set_skill(CALIAN_OPTIONS, v - CALOPT_SEE_SPECIALS);
             tp->catch_tell("Your see specials status is now: off.\n"); 
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
             tp->catch_tell("Your rack club status is now: on.\n"); 
             present(MEDALLION_ID, tp)->setup_rack_desc(tp); 
             return 1;
        }
        else if (str == "off") {
             if (v & CALOPT_RACK_CLUB) 
                 tp->set_skill(CALIAN_OPTIONS, v - CALOPT_RACK_CLUB);
             tp->catch_tell("Your rack club status is now: off.\n"); 
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

int 
cpractice(string str) 
{
    if (IS_CALIAN_FOLLOWER(this_player()))
    {
        return 0;
    }    
    return this_player()->practice_calian_specials(str); 
} 


mapping
query_cmdlist()
{
    return 
    ([ 
        "move" : "move_behind", 
        "mbsw" : "mbsw", 
        "swarm" : "swarm", 
        "maul" : "maul", 
        "cpractice" : "cpractice", 
        "crepeat" : "crepeat", 
        "cprepare" : "cprepare", 
        "cadverb" : "cadverb", 
        "cchange" : "cchange", 
        "help" : "help",
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

