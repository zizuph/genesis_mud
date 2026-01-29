
/* 
 * /d/Calia/palace/specials/calian_specials.c 
 * 
 * This contains the Calian guild specials: move behind, swarm 
 * and maul, plus a number of associated commands. Once the 
 * specials were part of the calian cmdsoul, then separated into 
 * included files, which were later included in the shadow, now 
 * after the latest set of additions and updates, this is just 
 * one file inherited in the shadow (as of June 2001, Maniac). 
 * 
 * Coders: Maniac and Glykron 
 * 13/4/2001       Separated from cmdsoul                           Maniac 
 *  5-6/2001       added auto-repeat features, new descriptions, 
 *                 change hands command, adverb options, updated 
 *                 mana/fatigue drawbacks, major code overhaul, 
 *                 tweaking of swarm and maul, documentation added, 
 *                 "set who to move behind" command added           Maniac 
 *  6/7/01         fixed bugs                                       Maniac 
 * 13/7/01         updated skill practice code                      Maniac 
 * 21/7/01         swarm coordination bug fixed                     Maniac 
 * 19/8/01         updated skill practice code                      Maniac 
 * 27/9/01         added checks for abilities of enemy in skill 
 *                 practice code                                    Maniac 
 * 30/9/01         modified skill practice code                     Maniac
 * 6/11/01         fixed ROOM_M_NO_ATTACK bug for move behind       Maniac
 * 22/8/02         fixed move behind bug                            Maniac
 * 7/9/02          fixed swarm reset bug                            Maniac
 * 20/10/02        fixed practice bug                               Maniac 
 * 08/6/05         10% damage bonus added to maul, and reduced 
 *                 dependency on being in a team -                  Bishop
 */ 

#include <macros.h>
#include <options.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include "defs.h"

inherit CALIAN_UTILITY;

#include COUNCIL_HEADER
#include CALIAN_HEADER
#define CALIAN_ATTACK_DESC "/d/Calia/std/attack_desc"


static string *swarm_adverbs = 
        ({ "", " slightly", " stingingly", " adeptly", 
           " precisely", " keenly", " incisively", " deeply", 
           " with deadly accuracy" }); 

static string *maul_adverbs = 
        ({ "", " superficially", " bitingly", " sharply", 
           " damagingly", " viciously", " ruinously", 
           " destructively", " with deadly force" }); 


/* 
 * Prototypes. 
 */ 
void restart_calian_special(object calian); 
private object query_calian_main_weapon(object player); 
varargs int calian_swarm(string str, int auto, int just_moved_behind); 
varargs int calian_maul(string str, int auto); 
private int query_maul_state(); 
private int query_swarm_state(); 
private void change_swarm_state(int new_state); 
private void change_maul_state(int new_state); 
private int special_tell_watcher(object tp, string str, 
                                 object enemy, mixed notell); 
private varargs void calian_swarm_enemy(object tp, object enemy, 
                     object weapon, string current_adverb, int just_mbd); 
private void calian_maul_enemy(object tp, object enemy, 
                               object weapon, string current_adverb, 
                               int time_diff); 
varargs int calian_move_behind(string str, int auto); 
varargs int calian_mbsw(string str, int auto, int just_tried_swarm); 


/* 
 * Global variables. 
 */ 
private int restart_alarm = 0;              // restart special alarm 
private int skill_by_practice = 0;          // practice special skills 
private int auto_rep = 0;                   // whether the specials auto-repeat 
private string hands_str = 0;               // which hand to attack with 
private int swarm_state = PRE_PREPARE;      // cycle state of swarm special 
private int maul_state = PRE_PREPARE;       // cycle state of maul special 
private string swarm_adv = "deftly";        // swarm adverb 
private string maul_adv = "determinedly";   // maul adverb 
private string mb_adv = "quickly";          // mb adverb 
private string mb_command = 0;              // automatic move behind command 
private string mb_player = 0;               // automatic move behind target 
private string last_special = 0;            // last special used 
private int simul_reset = 0;                // whether swarm resets with mb

/* 
 * **************************** 
 * Function code starts here. * 
 * **************************** 
 */ 


/* 
 * Function:     set_skill_by_practice 
 * Description:  Calling this with True (non-zero) value makes 
 *               it possible for the Calian to practice special 
 *               skills e.g. swarming can result in an increase 
 *               in the swarm skill and a loss in the maul skill, 
 *               Calling this with False (i.e. zero) stops this
 *               being possible. 
 * Argument:     int status - practice possible (1) or not (0). 
 */ 
private void 
set_skill_by_practice(int val) 
{ 
    skill_by_practice = val; 
} 


/* 
 * Function:     practice_calian_specials 
 * Description:  Action function called from the Calian command soul. 
 *               This allows the player to state whether to practice 
 *               in order to increase form in a special (thereby 
 *               also decreasing form in the other). 
 * Argument:     string str - the 
 */ 
int 
practice_calian_specials(string str) 
{ 
    if (!stringp(str) || !strlen(str)) 
    { 
        write("Syntax: " + capitalize(query_verb()) + " start / stop.\n" + 
              "Currently you " + (skill_by_practice ? "practice" : 
              "do not practice") + " Calian specials when fighting.\n"); 
        return 1; 
    } 

    if (str == "start") 
    { 
        if ((this_player()->query_skill(SS_MAUL_KNOWLEDGE) == 0) || 
            (this_player()->query_skill(SS_SWARM_KNOWLEDGE) == 0)) 
        { 
            notify_fail("You have to have knowledge of both " + 
                "swarm and maul in order to improve form by " + 
                "practicing.\n"); 
            return 0; 
        } 
        set_skill_by_practice(1); 
        tell_object(this_player(), 
            "As you have knowledge of both swarm and maul, " + 
            "you can now practice to improve form in these " + 
            "specials by swarming or mauling. " + 
            "Practicing a special will improve its form while " + 
            "losing you form in the other.\n"); 
        return 1; 
    } 
    else if (str == "stop") 
    { 
        set_skill_by_practice(0); 
        tell_object(this_player(), "When you swarm or maul, " + 
             "your form in the specials will not change.\n"); 
        return 1; 
    } 

    notify_fail(capitalize(query_verb()) + " start / stop?\n"); 
    return 0; 
} 


/* 
 * Function:     change_calian_special_skill_levels 
 * Description:  Change skill levels in swarm and maul, based on 
 *               the swarm_level_change parameter. 
 * Arguments:    object calian      -  the Calian 
 *               int level_change   -  levels adding to SWARM (+ or -). 
 *               int swarm_val      -  the skill value of swarm. 
 *               int maul_val       -  the skill value of maul. 
 */ 
private void 
change_calian_special_skill_levels(object calian, int level_change, 
                                   int swarm_val, int maul_val) 
{ 
    if (level_change > 0) 
    { 
        /* 
         * Add levels to swarm, remove levels from maul. 
         */ 
        if ((level_change = 
                 min(level_change, 
                     calian->query_skill(SS_SWARM_KNOWLEDGE) - 
                         swarm_val)) 
             > 0) 
        { 
            tell_object(calian, "You gain " + 
                LANG_WNUM(level_change) + 
                (level_change == 1 ? " level " : " levels ") + 
                "of swarm" + 
                (maul_val == 0 ? ".\n" : 
                                 " but become rustier in maul.\n")); 
            calian->set_skill(SS_SWARM, swarm_val + level_change); 
            calian->set_skill(SS_MAUL, max(maul_val - level_change, 
                                           0)); 
        } 
    } 
    else if (level_change < 0) 
    { 
        /* 
         * Add levels to maul, remove levels from swarm. 
         */ 
        level_change = -level_change; 
        if ((level_change = 
                 min(level_change, 
                     calian->query_skill(SS_MAUL_KNOWLEDGE) - 
                         maul_val)) 
             > 0) 
        { 
            tell_object(calian, "You gain " + 
                LANG_WNUM(level_change) + 
                (level_change == 1 ? " level " : " levels ") + 
                "of maul " + 
                (swarm_val == 0 ? ".\n" : 
                                  " but become rustier in swarm.\n")); 
            calian->set_skill(SS_MAUL, maul_val + level_change); 
            calian->set_skill(SS_SWARM, max(swarm_val - level_change, 
                                            0)); 
        } 
    } 
} 


/* 
 * Function:     practice_calian_maul_skill 
 * Description:  Adjusts maul skill after practicing maul. 
 * Arguments:    object calian   -  the Calian 
 *               object opponent -  the opponent 
 */ 
private void 
practice_calian_maul_skill(object calian, object opponent) 
{ 
    int maul_level, swarm_level, avg, part1, part2; 

    if ((maul_level = calian->query_skill(SS_MAUL)) < 100) 
    { 
        swarm_level = calian->query_skill(SS_SWARM); 
        avg = opponent->query_average_stat(); 

        part1 = (min((115 * (avg / 2 + random(avg))) / 100, 115) 
                 - maul_level) / 10; 

        part2 = min((calian->query_stat(SS_OCCUP) * (avg / 2 + random(avg))) 
                / 2500, 5); 

        if ((avg = max(part1 / 2, 0) + max(part2 / 2, 0)) > 0) 
        { 
            change_calian_special_skill_levels(calian, 
                -avg, swarm_level, maul_level); 
        } 
    } 
} 


/* 
 * Function:     practice_calian_swarm_skill 
 * Description:  Adjusts swarm skill after practicing swarm. 
 * Arguments:    object calian   -  the Calian 
 *               object opponent -  the opponent 
 */ 
private void 
practice_calian_swarm_skill(object calian, object opponent) 
{ 
    int swarm_level, maul_level, avg, part1, part2; 

    if ((swarm_level = calian->query_skill(SS_SWARM)) < 100) 
    { 
        maul_level = calian->query_skill(SS_MAUL); 
        avg = opponent->query_average_stat(); 

        part1 = (min((130 * (avg / 2 + random(avg))) / 100, 130) 
                 - swarm_level) / 20; 

        part2 = min((calian->query_stat(SS_OCCUP) * (avg / 2 + random(avg))) 
                / 5000, 3); 

        if ((avg = max(part1 / 2, 0) + max(part2 / 2, 0)) > 0) 
        { 
            change_calian_special_skill_levels(calian, 
                avg, swarm_level, maul_level); 
        } 
    } 
} 


/* 
 * Function:      calian_special_notify_fail 
 * Description:   If the argument "as_tell" is 1, tell the player 
 *                the message directly, otherwise this function 
 *                behaves just like the notify_fail efun. 
 * Arguments:     string msg  - the message 
 *                object tp   - this player 
 *                int as_tell - whether to send as tell or not 
 * Returns:       int - 1 if sent as tell, 0 otherwise. 
 * 
 */ 
private varargs int 
calian_special_notify_fail(string msg, object tp, int as_tell) 
{ 
    if (as_tell) 
    { 
        tell_object(tp, msg); 
        return 1; 
    } 
    notify_fail(msg); 
    return 0; 
} 


/* 
 * Function:     query_calian_ready_auto_repeat 
 * Description:  Should return 1 if the auto-repeat option is on 
 *               and the appropriate special is ready to use, 0 
 *               otherwise. 
 */ 
int 
query_calian_ready_auto_repeat(object calian) 
{ 
    if (auto_rep) 
    { 
        if (stringp(last_special)) 
        { 
            if (last_special == "swarm") 
                return (swarm_state == PRE_PREPARE); 
            if (last_special == "maul") 
                return (maul_state == PRE_PREPARE); 
        } 
        if (calian->query_skill(SS_SWARM) >= 
            calian->query_skill(SS_MAUL)) 
            return (swarm_state == PRE_PREPARE); 
        if (calian->query_skill(SS_MAUL)) 
            return (maul_state == PRE_PREPARE); 
    } 
    return 0; 
} 


/* 
 * Function:     restart_calian_special 
 * Description:  Restart a special attack if the auto repeat 
 *               option is on. 
 * Arguments:    object calian      -  the calian. 
 */ 
void 
restart_calian_special(object calian) 
{ 
    int tm; 

    if (restart_alarm && !get_alarm(restart_alarm)) 
    { 
        restart_alarm = 0; 
    } 

    if (auto_rep) 
    { 
        /* 
         * What was the last special used on this login? 
         */ 
        if (stringp(last_special)) 
        { 
            if (last_special == "swarm") 
            { 
                if (swarm_state != PRE_PREPARE) 
                    return; 
                /* 
                 * Try to swarm. 
                 */ 
                set_this_player(calian); 
                calian_swarm(0, 1); 
            } 
            else if (last_special == "maul") 
            { 
                if (maul_state != PRE_PREPARE) 
                    return; 
                /* 
                 * Try to maul. 
                 */ 
                set_this_player(calian); 
                calian_maul(0, 1); 
            } 
        } 
        /* 
         * No special used on this login! Find preference. 
         */ 
        else if (calian->query_skill(SS_SWARM) >= 
            calian->query_skill(SS_MAUL)) 
        { 
            if (swarm_state != PRE_PREPARE) 
                return; 
            /* 
             * Try to swarm. 
             */ 
            set_this_player(calian); 
            calian_swarm(0, 1); 
        } 
        else if (calian->query_skill(SS_MAUL)) 
        { 
            if (maul_state != PRE_PREPARE) 
                return; 
            /* 
             * Try to maul. 
             */ 
            set_this_player(calian); 
            calian_maul(0, 1); 
        } 
    } 
} 


/* 
 * Function:      calian_auto_repeat 
 * Description:   Action function, to set auto repeat of specials 
 *                to on or off. 
 * Arguments:     string str  - predicate 
 * Returns:       int         - success 
 */ 
int 
calian_auto_repeat(string str) 
{ 
    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    if (!stringp(str) || !strlen(str)) 
    { 
        write("Calian specials are currently " + 
              (auto_rep ? "" : "not ") + 
              "repeated automatically.\n"); 
        return 1; 
    } 
    else if (str == "off") 
    { 
        auto_rep = 0; 
        write("Calian specials are now NOT repeated automatically.\n"); 
        return 1; 
    } 
    else if (str == "on") 
    { 
        auto_rep = 1; 
        write("Calian specials are now repeated automatically.\n"); 
        return 1; 
    } 
    return 0; 
} 


/* 
 * Function:     calian_change_hands 
 * Description:  Action function to change the hand that is used 
 *               for the "swarm" and "maul" specials. 
 * Arguments:    string str - predicate 
 * Returns:      int - success. 
 */ 
int 
calian_change_hands(string str) 
{
    string specials;
    
    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    if (this_object()->is_calian_follower())
    {
        specials = "<swarm> special.";
    }
    else
    {
        specials = "<swarm> and <maul> specials.";
    }
    
    if (str == "right" || str == "rhand") 
    { 
        hands_str = "right"; 
        write("You prefer to attack with the weapon wielded in " + 
              "the RIGHT hand when using the " + specials + "\n"); 
        return 1; 
    } 
    else if (str == "left" || str == "lhand") 
    { 
        hands_str = "left"; 
        write("You prefer to attack with the weapon wielded in the " + 
              "LEFT hand when using the " + specials + "\n"); 
        return 1; 
    } 
    else if (str == "both") 
    { 
        hands_str = "both"; 
        write("You prefer to attack with a weapon wielded in " + 
              "BOTH hands when using the " + specials + "\n"); 
        return 1; 
    } 

    if (!stringp(str) || !strlen(str)) 
    { 
        if (!stringp(hands_str)) 
        { 
            write("You have not specified which hand(s) " + 
                  "you prefer to attack with when using the " + 
                  specials + "\n"); 
            return 1; 
        } 
        write("You prefer to attack with " + 
              (hands_str == "both" ? "a " : "the ") + 
              "weapon wielded in " + 
              (hands_str == "both" ? "BOTH hands" : "the " + 
              (hands_str == "left" ? "LEFT" : "RIGHT") + " hand") + 
              " when using the " + specials + "\n"); 
        return 1; 
    } 
    notify_fail(capitalize(query_verb()) + " [left/right/both]?\n"); 
    return 0; 
} 


/* 
 * Function:     calian_set_adverb 
 * Description:  Set adverb to be used with swarm or maul specials. 
 * Arguments:    string str - predicate 
 * Returns:      int - success 
 */ 
int 
calian_set_adverb(string str) 
{ 
    string *tmp, spec, adv, usage; 
    int ix; 

    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    if (this_object()->is_calian_follower())
    {
        usage = "<calian specials | move behind | swarm> <how>"; 
    }
    else
    {
        usage = "<calian specials | maul | move behind | swarm> <how>"; 
    }
    /*
     * If no argument or syntax was incorrect, give 
     * adverb status for each special and describe 
     * correct syntax. 
     */ 
    if (!stringp(str) || !strlen(str) || 
        (sizeof(tmp = explode(str, " ")) < 2) || 
        (sizeof(tmp) > 3)) 
    {
        spec = "Currently you carry out move behind " + mb_adv;
        if (this_object()->is_calian_follower())
        {
            spec += " and swarm " + swarm_adv;
        }
        else
        {
            spec += ", swarm " + swarm_adv + " and maul " + maul_adv;
        }
        spec += ". To make a change, try:\n" + query_verb() 
              + " " + usage + ".\n";
        write(spec);
        return 1; 
    } 

    /* 
     * Get text for special and adverb. 
     */ 
    if (sizeof(tmp) == 2) 
    { 
        spec = lower_case(tmp[0]); 
        adv = tmp[1]; 
    } 
    else 
    { 
        spec = lower_case(tmp[0]) + " " + tmp[1]; 
        adv = tmp[2]; 
    } 

    /* 
     * Check that full adverb exists. 
     */ 
    if (!strlen(adv = FULL_ADVERB(adv))) 
    { 
        notify_fail("That adverb is unknown.\n"); 
        return 0; 
    } 

    /* 
     * Set adverb for special(s). 
     */ 
    switch (spec) 
    { 
        case "calian specials" : 
            maul_adv = mb_adv = swarm_adv = adv; 
            break; 
        case "maul" : 
            if (this_object()->is_calian_follower())
            {
                notify_fail(capitalize(query_verb()) + " " 
                          + usage + "?\n");
                return 0;
            }
            maul_adv = adv; 
            break; 
        case "move behind" : 
            mb_adv = adv; 
            break; 
        case "swarm" : 
            swarm_adv = adv; 
            break; 
        default : 
            notify_fail(capitalize(query_verb()) + " " 
                      + usage + "?\n");
            return 0; 
    } 

    /* 
     * Give final confirmation message about the adverb to the Calian. 
     */ 
    write(capitalize(spec) + " will be carried out " + adv + "!\n"); 
    return 1; 
} 


/* 
 * Function:      calian_prepare_to_move_behind 
 * Description:   Action function, to set who to move behind 
 *                automatically (if anyone) when attacked. 
 * Arguments:     string str  - predicate 
 * Returns:       int         - success 
 */ 
int 
calian_prepare_to_move_behind(string str) 
{ 
    string *tmp; 

    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    if (str == "clear") 
    { 
        write("OK, you will not move behind anyone automatically.\n"); 
        mb_player = 0; 
        mb_command = 0; 
        return 1; 
    } 

    if (stringp(str) && strlen(str) && 
        sizeof(tmp = explode(str, " ")) > 1) 
    { 
        if (tmp[0] == "to") 
        { 
            tmp = tmp[1 .. sizeof(tmp) - 1]; 
        } 

        /* 
         * If Calian wants to prepare to move behind (as opposed 
         * to move behind and swarm i.e. mbsw).. 
         */ 
        if (tmp[0] == "move") 
        { 
            /* 
             * If the syntax was correct .. 
             */ 
            if (tmp[1] == "behind" && sizeof(tmp) == 3) 
            { 
                /* 
                 * If the Calian has met the person s/he wants to 
                 * move behind and swarm, success.. 
                 */ 
                if (SECURITY->exist_player(tmp[2] = lower_case(tmp[2])) 
                    && TP->query_met(tmp[2])
                    && tmp[2] != TP->query_real_name()) 
                { 
                    mb_player = tmp[2]; 
                    mb_command = "move behind"; 
                    write("If attacked you will attempt to " + 
                          "move behind " + capitalize(mb_player) + 
                          ".\n"); 
                    return 1; 
                } 
                /* 
                 * .. else failure. 
                 */ 
                else 
                { 
                    notify_fail("You don't know another person called " + 
                                capitalize(tmp[2]) + ".\n"); 
                    return 0; 
                } 
            } 
        } 
        /*
         * .. else if Calian wants to prepare to move behind and 
         * swarm i.e. mbsw .. 
         */ 
        else if (tmp[0] == "mbsw") 
        { 
            /* 
             * If the Calian has met the person s/he wants to 
             * move behind and swarm.. 
             */ 
            if (SECURITY->exist_player(tmp[1] = lower_case(tmp[1])) 
                && TP->query_met(tmp[1]) 
                && tmp[1] != TP->query_real_name()) 
            { 
                /* 
                 * If the syntax was correct, success. 
                 */ 
                if (sizeof(tmp) == 2) 
                { 
                    mb_player = tmp[1]; 
                    mb_command = "mbsw"; 
                    write("If attacked you will attempt to mbsw " + 
                          capitalize(mb_player) + ".\n"); 
                    return 1; 
                } 
            } 
            /* 
             * .. else failure. 
             */ 
            else 
            { 
                notify_fail("You don't know another person called " + 
                            capitalize(tmp[1]) + ".\n"); 
                return 0; 
            } 
        } 
    } 

    /* 
     * Getting here means the syntax was incorrect. 
     */ 
    if (stringp(mb_command)) 
    { 
        write("If attacked you will attempt to " + 
              mb_command + " " + capitalize(mb_player) + ".\n"); 
    } 

    write(capitalize(query_verb()) + 
          " to <move behind | mbsw> <person>?\n"); 
    return 1; 
} 


/* 
 * Function:     query_calian_attempt_mb_automatically 
 * Description:  Should return whether the Calian attempts 
 *               to move behind automatically when attacked. 
 * Returns:      int - whether attempt should be made 
 */ 
int
query_calian_attempt_mb_automatically()
{
    return stringp(mb_command); 
}


/* 
 * Function:      calian_attacked_by_mb_hook 
 * Description:   Called when the shadowed Calian is attacked. If 
 *                s/he previously set the name of the player to 
 *                move behind, the attempt will be made automatically. 
 * Arguments:     object attacker   -  living who attacked the Calian 
 */ 
void 
calian_attacked_by_mb_hook(object attacker) 
{ 
    if (mb_command == "move behind") 
    { 
        set_this_player(this_object()->query_shadow_who()); 
        tell_object(this_player(), 
            "You immediately try to move behind.\n"); 
        calian_move_behind("behind " + mb_player, 1); 
    } 
    else if (mb_command == "mbsw") 
    { 
        set_this_player(this_object()->query_shadow_who()); 
        tell_object(this_player(), 
            "You immediately try to move behind and swarm.\n"); 
        calian_mbsw(mb_player, 1, 1); 
    } 
} 


/* 
 * Function:      special_tell_watcher 
 * Description:   Gives a combat message to those who "see blood". 
 *                This is rather like the standard tell_watcher 
 *                function but takes into account the Calian 
 *                "see specials" option. 
 * Arguments:     object tp    - the hitter 
 *                string str   - message 
 *                object enemy - the living getting hit 
 *                mixed notell - those not to tell the message 
 */ 
private void
special_tell_watcher(object tp, string str, object enemy, mixed notell)
{
    object *ob; 
    int i, size; 

    ob = all_inventory(environment(tp)) - ({ tp, enemy }); 

    if (pointerp(notell)) 
        ob -= notell; 

    /* We only display combat messages to interactive players. */ 
    ob = FILTER_PLAYERS(ob); 

    i = -1; 
    size = sizeof(ob); 

    while(++i < size) 
    { 
        if ((!ob[i]->query_option(OPT_BLOOD) || 
             (ob[i]->query_skill(CALIAN_OPTIONS) & CALOPT_SEE_SPECIALS)) 
             && CAN_SEE_IN_ROOM(ob[i])) 
        { 
            if (CAN_SEE(ob[i], tp)) 
                ob[i]->catch_msg(str); 
            else 
                tell_object(ob[i], enemy->query_The_name(ob[i]) + 
                    " is hit by someone.\n"); 
        }
    }
}


/* 
 * Function:     query_main_weapon 
 * Description:  Should return the main weapon wielded by the 
 *               shadowed Calian, or 0 if no weapon is wielded. 
 *               If a preference was stated about which hand to 
 *               use, that is checked first. Otherwise, the 
 *               default order of checks is: right, left, both. 
 * Arguments:    object player - the Calian 
 * Returns:      object - The main weapon 
 */ 
private object 
query_calian_main_weapon(object player) 
{
    object weapon; 

    if (hands_str == "left") 
    { 
        if (objectp(weapon = player->query_weapon(W_LEFT)))
            return weapon; 

        if (objectp(weapon = player->query_weapon(W_RIGHT))) 
            return weapon; 

        return player->query_weapon(W_BOTH); 
    } 
    else if (hands_str == "both") 
    {
        if (objectp(weapon = player->query_weapon(W_BOTH))) 
            return weapon; 

        if (objectp(weapon = player->query_weapon(W_RIGHT)))
            return weapon; 

        return player->query_weapon(W_LEFT); 
    } 

    if (objectp(weapon = player->query_weapon(W_RIGHT))) 
        return weapon; 

    if (objectp(weapon = player->query_weapon(W_LEFT)))
        return weapon; 

    return player->query_weapon(W_BOTH); 
}


/* 
 * Function:     query_special_state 
 * Description:  Returns the state of the special of the given name, 
 *               or -1 if there was no special of that name. 
 * Arguments:    string special_name - the name of the special 
 * Returns:      int - the prep / recovery state of the special, -1 
 *                     if the special name is unknown 
 */ 
private int 
query_special_state(string special_name) 
{ 
    if (special_name == "swarm") 
        return query_swarm_state(); 
    else if (special_name == "maul") 
        return query_maul_state(); 

    return -1; 
} 


/* 
 * Function:     change_special_state 
 * Description:  Changes the state of the special of the given name. 
 * Arguments:    string special_name - the special name 
 *               int new_state       - the new state of prep / recovery 
 */ 
private void 
change_special_state(string special_name, int new_state) 
{ 
    if (special_name == "swarm") 
        return change_swarm_state(new_state); 
    else if (special_name == "maul") 
        return change_maul_state(new_state); 
} 


/* 
 * Function:      check_prepare_special 
 * Description:   Does a number of checks when someone attempts 
 *                to prepare swarm or maul to make sure it can 
 *                go ahead. 
 * Arguments:     object tp           - player using a special 
 *                string special_name - name of the special 
 *                string weapon_hand  - left, right or both 
 *                int auto            - whether special invoked automatically 
 * Returns:       the object for the weapon to be used in the 
 *                attack if all the checks passed, 0 otherwise. 
 * 
 */ 
private varargs object 
check_prepare_special(object tp, string special_name, int auto) 
{ 
    int ss; 
    string nam; 
    object weapon; 

    ss = query_special_state(special_name); 

    /* 
     * If already preparing, just return 0. 
     */ 
    if (ss == PREPARING) 
    { 
        calian_special_notify_fail("You are currently preparing to " + 
            special_name + ".\n", tp, auto); 
        return 0; 
    } 

    /* 
     * JUST_SWARMED def should be the same as JUST_MAULED 
     */ 
    if (ss == JUST_SWARMED) 
    { 
        calian_special_notify_fail("You have only just " + 
            special_name + "ed.\n", tp, auto); 
        return 0; 
    } 

    /* 
     * It may not be possible to attack in the room. 
     */ 
    if (nam = environment(tp)->query_prop(ROOM_M_NO_ATTACK)) 
    { 
        if (stringp(nam)) 
        { 
            calian_special_notify_fail(nam, tp, auto); 
            change_special_state(special_name, PRE_PREPARE); 
            return 0; 
        } 
        else 
        { 
            calian_special_notify_fail("A magical force prevents you " + 
                "from " + special_name + "ing.\n", tp, auto); 
            change_special_state(special_name, PRE_PREPARE); 
            return 0; 
        } 
    } 

    /* 
     * If the player is stunned, it's impossible to use a special. 
     */ 
    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) 
    { 
        calian_special_notify_fail("You are currently stunned so " + 
            "you can't " + special_name + "!\n", tp, auto); 
        change_special_state(special_name, PRE_PREPARE); 
        return 0; 
    } 

    /* 
     * Player may have been banned from swarming / mauling by 
     * the Calian Council. 
     */ 
    seteuid(getuid()); 
    if (COUNCIL_CODE->is_swarm_banned(tp)) 
    { 
        calian_special_notify_fail("The Calian Council has banned you " + 
                    "from " + special_name + "ing.\n", tp, auto); 
        change_special_state(special_name, PRE_PREPARE); 
        return 0; 
    } 

    /* 
     * Check that the player is wielding a weapon. 
     */ 
    if (!objectp(weapon = query_calian_main_weapon(tp))) 
    { 
        calian_special_notify_fail("You cannot " + special_name + 
                    " your enemy without a weapon!\n", tp, auto); 
        change_special_state(special_name, PRE_PREPARE); 
        return 0; 
    } 

    return weapon; 
} 


/* 
 * Function:     try_assist 
 * Description:  If this_player() not in combat, try assisting. 
 * Returns:      object - who is fought, 0 if no-one. 
 */ 
private object 
try_assist(int auto, string special_name)
{
    object enemy; 

    /* 
     * If not in combat yet, assist and check again. 
     */ 
    if (!objectp(enemy = TP->query_attack())) 
    { 
        TP->command("$assist"); /* Will assist a fellow team member */ 
        if (!objectp(enemy = TP->query_attack())) 
        { 
            calian_special_notify_fail("You are not fighting anyone.\n", 
                TP, auto); 
            return 0; 
        } 
    } 
    else 
    { 
        /* 
         * To avoid the swarmer's paradox you need to swarm an enemy who 
         * is not attacking someone who is attacking someone who is 
         * attacking you, which results in a knot. That sentence is not 
         * a typo! 
         */ 
        if (special_name == "swarm" && 
            ((enemy->query_attack())->query_attack())->query_attack() == TP) 
        { 
            TP->command("$assist"); /* Will assist a fellow team member */ 
            if (!objectp(enemy = TP->query_attack())) 
            { 
                calian_special_notify_fail("You are not fighting anyone.\n", 
                     TP, auto); 
                return 0; 
            } 
        } 
    } 
    return enemy; 
}


/* 
 *   S W A R M  S T A R T S  H E R E 
 */ 

/* 
 * Function:      change_swarm_state 
 * Description:   Changes the preparation / recovery state of swarm. 
 * Arguments:     int new_state - the new state 
 */ 
private void 
change_swarm_state(int new_state) 
{ 
    swarm_state = new_state; 

    if (swarm_state == PRE_PREPARE) 
        simul_reset = 0; 
} 


/* 
 * Function:      ready_to_swarm_now 
 * Description:   Called by alarm when the player is ready to swarm 
 *                again, to make the appropriate variable / property 
 *                changes and invoke an auto-repeat if appropriate. 
 * Arguments:     object tp        - the player ready to swarm again. 
 */ 
private varargs void 
ready_to_swarm_now(object tp) 
{ 
    change_swarm_state(PRE_PREPARE); 
    tell_object(tp, "You are ready to swarm again.\n"); 
    if (auto_rep) 
    { 
        set_this_player(tp); 
        calian_swarm(0, 1); 
    } 
} 


/* 
 * Function:      do_dismember 
 * Description:   When a Calian has killed an enemy with swarm 
 *                it is usually dismembered as a result, this 
 *                function makes this gruesome end possible by 
 *                cloning and moving in all the body parts. 
 * Arguments:     object tp    - the dismemberer 
 *                object enemy - the living to dismember 
 */ 
private void 
do_dismember(object tp, object enemy) 
{ 
    object piece; 
    string enemy_race, hit_piece, *piece_names; 
    int x, *ids; 
    mixed *loc; 

    /* get hitloc strings ready for pieces */ 
    ids = ({ }); 
    ids += (enemy->query_combat_object())->query_hitloc_id(); 
    piece_names = ({ }); 
    for (x = 0; x < sizeof(ids); x++) 
    { 
        loc = (enemy->query_combat_object())->query_hitloc(ids[x]); 
        if (stringp(loc[2])) 
            piece_names += ({ loc[2] }); 
    } 

    enemy->add_prop(LIVE_I_NO_CORPSE, 1); 
    enemy_race = enemy->query_race_name(); 

    enemy->do_die(tp); 
    setuid(); 
    seteuid(getuid(this_object())); 
    for (x = 0; x < sizeof(piece_names); x++) 
    { 
        piece = clone_object(LEFTOVER_OBJECT); 
        piece->leftover_init(piece_names[x], enemy_race); 
        piece->move(environment(tp), 0); 
    } 
} 


/* 
 * Function:     calian_swarm_enemy 
 * Description:  Carry out swarm special after preparation 
 * Arguments:    object tp               - the swarmer 
 *               object enemy            - the enemy 
 *               object weapon           - the weapon 
 *               string current_adverb   - descriptive adverb 
 *               int just_mbd            - just moved behind 
 */ 
private varargs void 
calian_swarm_enemy(object tp, object enemy, 
                   object weapon, string current_adverb, 
                   int just_mbd) 
{ 
    object *calians, enemy_target, *team, *focused_team; 
    string weapon_desc, *hit_descr; 
    int sk, p, d; 
    mixed hit; 

    /* 
     * If enemy gone, can't swarm it. 
     */ 
    if (!objectp(enemy) || 
        !present(enemy, environment(tp))) 
    { 
        tell_object(tp, 
            "You can no longer see the enemy you were preparing " + 
            "to swarm.\n"); 
        change_swarm_state(PRE_PREPARE); 
        if (auto_rep && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_swarm(current_adverb, 1); 
        } 
        return; 
    } 

    /* 
     * If no longer fighting enemy, can't swarm it. 
     */ 
    if (enemy != tp->query_attack()) 
    { 
        tell_object(tp, 
            "You are no longer attacking your swarm target.\n"); 
        change_swarm_state(PRE_PREPARE); 
        if (auto_rep && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_swarm(current_adverb, 1); 
        } 
        return; 
    } 

    /* 
     * If chosen weapon is no longer wielded, swarm fails. 
     */ 
    if (!objectp(weapon) || weapon->query_wielded() != tp) 
    { 
        tell_object(tp, 
            "You're not wielding the same weapon " + 
            "as when you prepared to swarm.\n"); 
        change_swarm_state(PRE_PREPARE); 
        if (auto_rep && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_swarm(current_adverb, 1); 
        } 
        return; 
    } 

    /* 
     * If no longer in a team, swarm fails. 
     */ 
    if (!sizeof(team = tp->query_team_others())) 
    { 
        tell_object(tp, "You are not in a team!\n"); 
        change_swarm_state(PRE_PREPARE); 
        return; 
    } 

    /* 
     * If enemy now attacks swarmer, swarming is impossible. 
     */ 
    if (enemy->query_attack() == tp) 
    { 
        tell_object(tp, 
            "Your enemy is paying too much attention for you " + 
            "to swarm " + enemy->query_objective() + ".\n"); 
        change_swarm_state(PRE_PREPARE); 
        if (auto_rep && stringp(mb_command) && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_mbsw(mb_player, 1); 
        } 
        return; 
    } 

    /* 
     * If stunned, can't swarm. 
     */ 
    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) 
    { 
        tell_object(tp, 
            "You are currently stunned so you can't swarm!\n"); 
        change_swarm_state(PRE_PREPARE); 
        return; 
    } 

    /* 
     * If no team members are present, can't swarm. 
     */ 
    if (!sizeof(team = FILTER_PRESENT_LIVE(team))) 
    { 
        tell_object(tp, "None of your team is present!\n"); 
        change_swarm_state(PRE_PREPARE); 
        return; 
    } 

    /* 
     * If no team members are fighting, can't swarm. 
     */ 
    if (!sizeof(filter(map(team, &->query_attack()), objectp))) 
    { 
        tell_object(tp, 
            "None of your present team members are fighting!\n"); 
        change_swarm_state(PRE_PREPARE); 
        return; 
    } 

    /*
     * It may not be possible to attack the enemy. 
     */ 
    if (enemy->query_not_attack_me(tp, weapon->query_attack_id())) 
    { 
        change_swarm_state(PRE_PREPARE); 
        return; 
    } 

    weapon_desc = weapon->short(); 

    change_swarm_state(JUST_SWARMED); 
    if (!just_mbd) 
        set_alarm(itof(SWARM_EXEC_TIME), 0.0, &ready_to_swarm_now(tp)); 

    focused_team = filter(team, &operator(==)(, enemy) @ &->query_attack()); 


    /* 
     * If fighting together with a Calian, on average only half the 
     * amount of fatigue and mana are taken. 
     */ 
    if (!sizeof(calians = filter(focused_team, is_calian)) || 
        !random(2)) 
    { 
        if (tp->query_mana() < SWARM_MANA || 
            tp->query_fatigue() < SWARM_FATIGUE) 
        { 
            tell_object(tp, "As you are so weary, using " + 
                "the swarm special is damaging your " + 
                "health.\n"); 
            tp->heal_hp(-10); 
        } 
        tp->add_mana(-SWARM_MANA); 
        tp->add_fatigue(-SWARM_FATIGUE); 
    } 

    /* 
     * The tohit value given to cb_tohit depends on the weapon 
     * hit value and swarm skill or wisdom. For a good weapon 
     * (40 hit value) and maxed maul skill, the tohit value is 
     * 126. 
     */ 
    if (tp->query_combat_object()->cb_tohit(-1, 
                    min(max(((sk = tp->query_skill(SS_SWARM)) / 2), 
                        tp->query_stat(SS_WIS) / 2), 50) + 
                    ((25 * weapon->query_hit()) / 13), 
                     enemy) >= 0) 
    { 
        /* 
         * Basic multiplier for weapon pen (percentage) 
         */ 
        d = 120; 

        /* 
         * Polearm bonus, or similar bonus if size of team is 
         * greater than two 
         */ 
        if (weapon->query_wt() == W_POLEARM || 
            sizeof(team) > 2) 
            d += 20; 

        /* 
         * Calian fighting in team bonus, or similar bonus if 
         * size of team is greater than three. 
         */ 
        if (sizeof(calians) || 
            sizeof(team) > 3) 
            d += 20; 

        /* 
         * Rogue tanker penalty 
         */ 
        if (member_array(enemy_target = enemy->query_attack(), team) == -1) 
        { 
            tell_object(tp, 
                "You find it hard to coordinate your " + 
                "swarm attack with " + 
                enemy_target->query_the_name(tp) + ".\n"); 
            d = d / 3; 
        } 

        /* water penalties 
        if (IN_DEEP_WATER(tp) || UNDER_WATER(tp)) 
            d = (d * tp->query_skill(SS_SWIM) / 100); 
        */ 

        /* 
         * Final pen calculation 
         */ 
        p = ((weapon->query_pen() * d) / 100) + 
            min(max(tp->query_stat(SS_DEX) / 12, 
                    tp->query_stat(SS_OCCUP) / 12), 16); 

        hit = enemy->hit_me(F_PENMOD(p, sk), W_IMPALE, tp, -1); 

        if (!stringp(current_adverb) || !strlen(current_adverb)) 
            current_adverb = swarm_adv; 

        /* 
         * Get the hit descriptions. 
         */ 
        hit_descr = CALIAN_ATTACK_DESC->attack_desc_template_one(tp, 
                        enemy, W_IMPALE, hit[0], hit[1], 
                        weapon_desc, 
                 ({ " pounce " + current_adverb + " and ", 
                    " pounces " + current_adverb + " and ", 
                    " pounces " + current_adverb + " and " }), 
                 swarm_adverbs, 1); 

        if (tp->query_wiz_level()) 
            tell_object(tp, 
                "Pen on this swarm was: " + p + ". " + 
                "Damage was: " + hit[3] + ".\n"); 

        /*
         * If the swarm was a killing blow, give a special message
         * and call the do_die function in the enemy. 
         */ 
        if (enemy->query_hp() < 1) 
        { 
            /* 
             * If the monster should have a corpse and the Calian's 
             * dismember option is set to on, then .. dismember. 
             */ 
            if (!enemy->query_prop(LIVE_I_NO_CORPSE) && 
                (tp->query_skill(CALIAN_OPTIONS) & CALOPT_DISMEMBER)) 
            { 
                tell_object(tp, 
                    "You hit " + enemy->query_the_name(tp) + 
                    " with a thunderous blow of your " + weapon_desc + 
                    ", dismembering " + enemy->query_objective() + "!\n"); 
                if (interactive(enemy)) 
                    tell_object(enemy, tp->query_The_name(enemy) + 
                        " hits you with a thunderous blow of " + 
                        tp->query_possessive() + " " + 
                        weapon_desc + ", dismembering you!\n"); 
                special_tell_watcher(tp, QCTNAME(tp) + " hits " + 
                    QTNAME(enemy) + " with a thunderous blow of " + 
                    tp->query_possessive() + " " + weapon_desc + 
                    ", dismembering " + enemy->query_objective() + "!\n", 
                    enemy, 0); 
                if (skill_by_practice) 
                    practice_calian_swarm_skill(tp, enemy); 
                do_dismember(tp, enemy); 
            } 
            else // otherwise, kill without dismembering. 
            { 
                tell_object(tp, 
                    "You hit " + enemy->query_the_name(tp) + 
                    " with a thunderous blow of your " + 
                    weapon_desc + "!\n"); 
                if (interactive(enemy)) 
                    tell_object(enemy, tp->query_The_name(enemy) + 
                        " hits you with a thunderous blow of " + 
                        tp->query_possessive() + " " + weapon_desc + 
                        "!\n"); 
                special_tell_watcher(tp, QCTNAME(tp) + " hits " + 
                    QTNAME(enemy) + " with a thunderous blow of " + 
                    tp->query_possessive() + " " + weapon_desc + 
                    "!\n", enemy, 0); 
                if (skill_by_practice) 
                    practice_calian_swarm_skill(tp, enemy); 
                enemy->do_die(tp); 
            } 
            return; 
        } 
        tell_object(tp, hit_descr[0]); 

        if (interactive(enemy)) 
            tell_object(enemy, hit_descr[1]); 

        special_tell_watcher(tp, hit_descr[2], enemy, 0); 
        if (skill_by_practice) 
            practice_calian_swarm_skill(tp, enemy); 
    } 
    else 
    { 
        /* 
         * Damn, missed! 
         */ 
        tell_object(tp, "You fail to sneak around " + 
            enemy->query_the_name(tp) + "'s defences.\n"); 
        if (interactive(enemy)) 
            tell_object(enemy, 
                tp->query_The_name(enemy) + " fails to " + 
                "sneak around your defences.\n"); 
        special_tell_watcher(tp, QCTNAME(tp) + " fails to sneak " + 
            "around " + QTNAME(enemy) + "'s defences.\n", 
            enemy, 0); 
        if (skill_by_practice) 
            practice_calian_swarm_skill(tp, enemy); 
    } 
} 


/* 
 * Function:     query_swarm_state 
 * Description:  Should return the state of preparation/recovery of 
 *               the swarm special.  
 * Returns:      int - the swarm state. 
 */ 
int 
query_swarm_state() 
{ 
    return swarm_state; 
} 


/* 
 * Function name: calian_swarm 
 * Description:   executes the swarm command 
 * Arguments:     string str      - predicate 
 *                int auto        - whether invoked automatically by repeat 
 *                int just_mbd    - whether just moved behind 
 * Returns:       int - success 
 */ 
varargs int 
calian_swarm(string str, int auto, int just_mbd) 
{ 
    object enemy, weapon, *team; 
    int dt; 
    string nam, current_adverb; 

    /* 
     * Security check. 
     */ 
    if (TP != this_object()->query_shadow_who()) 
        return 0; 

    /* 
     * Cannot swarm while mauling. 
     */ 
    if (query_maul_state() != PRE_PREPARE) 
    { 
        calian_special_notify_fail("You may not swarm while you " + 
            "are involved in any stage of a maul.\n"); 
        return 0; 
    } 

    last_special = "swarm"; 

    /* 
     * Standard checks for preparing swarm and maul. 
     */ 
    if (!objectp(weapon = check_prepare_special(TP, "swarm", auto))) 
        return 0; 

    /* 
     * If not wielding an impaling weapon, can't swarm. 
     */ 
    if (!(weapon->query_dt() & W_IMPALE)) 
    { 
        calian_special_notify_fail("You can't swarm with a weapon " + 
            "that can't impale.\n", TP, auto); 
        return 0; 
    } 

    /* 
     * If not teamed, can't swarm. 
     */ 
    if (!sizeof(team = TP->query_team_others())) 
    { 
        calian_special_notify_fail("You are not in a team!\n", 
            TP, auto); 
        return 0; 
    } 

    /* 
     * If no team members present, can't swarm. 
     */ 
    if (!sizeof(team = FILTER_PRESENT_LIVE(team))) 
    { 
        calian_special_notify_fail("None of your fellow team " + 
            "members are present!\n", TP, auto); 
        return 0; 
    } 

    /* 
     * If no team members are fighting, can't swarm. 
     */ 
    if (!sizeof(filter(map(team, &->query_attack()), objectp))) 
    { 
        calian_special_notify_fail("None of your present team " + 
            "members are fighting!\n", TP, auto); 
        return 0; 
    } 


    /* 
     * If the player has no skill in swarming and is not practicing, 
     * s/he can't swarm. 
     */ 
    if (!TP->query_skill(SS_SWARM)) 
    { 
        if (!skill_by_practice) 
        { 
            calian_special_notify_fail("You are not skilled in swarming!\n", 
                TP, auto); 
            return 0; 
        } 

        if (!objectp(enemy = try_assist(auto, "swarm"))) 
            return 0; 

        tell_object(TP, "As you begin applying yourself to practicing " + 
            "swarm, you gain one level in swarm form.\n"); 
        TP->set_skill(SS_SWARM, 1); 
        TP->set_skill(SS_MAUL, TP->query_skill(SS_MAUL) - 1); 
    } 
    else 
    { 
        if (!objectp(enemy = try_assist(auto, "swarm"))) 
            return 0; 
    } 


    /* 
     * If the swarm target is the attacking enemy, can't swarm. 
     */ 
    if (enemy->query_attack() == TP) 
    { 
        if (!just_mbd && 
            mb_command == "mbsw" && 
            stringp(mb_player)) 
        { 
            return calian_mbsw(mb_player, auto, 1); 
        } 
        calian_special_notify_fail("Your enemy is paying too " + 
            "much attention for you to swarm " + 
            enemy->query_objective() + ".\n", TP, auto); 
        return 0; 
    } 


    /* 
     * Find full descriptive adverb. 
     */ 
    if (stringp(str)) 
        current_adverb = FULL_ADVERB(lower_case(str)); 

    /* 
     * Prepare to swarm. 
     */ 
    set_alarm(itof(SWARM_PREP_TIME), 0.0, 
              &calian_swarm_enemy(TP, enemy, weapon, current_adverb, 
                                  just_mbd)); 
    change_swarm_state(PREPARING); 
    tell_object(TP, 
        "You prepare to swarm " + enemy->query_the_name(TP) + 
        " with your " + weapon->short() + ".\n"); 
    return 1; 
} 


/* 
 * S W A R M  E N D S  H E R E 
 */ 



/* 
 * M A U L  S T A R T S  H E R E 
 */ 
/* 
 * Function:     change_maul_state 
 * Description:  Changes the preparation / recovery state of maul. 
 * Arguments:    int new_state - the maul state 
 */ 
private void 
change_maul_state(int new_state) 
{ 
    maul_state = new_state; 
} 


/* 
 * Function:      ready_to_maul_now 
 * Description:   Called by alarm when the player is ready to maul 
 *                again, to make the appropriate variable / property 
 *                changes and invoke an auto-repeat if appropriate. 
 * Arguments:     object tp - the mauling Calian  
 */ 
private void 
ready_to_maul_now(object tp) 
{ 
    change_maul_state(PRE_PREPARE); 
    tell_object(tp, "You are ready to maul again.\n"); 
    set_this_player(tp); 
    if (auto_rep) 
        calian_maul(0, 1); 
} 


/* 
 * Function:     query_maul_state 
 * Description:  Should return the state of preparation/recovery 
 *               of maul special. 
 * Returns:      int - the maul state. 
 */ 
private int 
query_maul_state() 
{ 
    return maul_state; 
} 


/* 
 * Function:     is_attacking 
 * Description:  Should return whether the player is attacking  
 *               the enemy (1 for yes, 0 for no). 
 * Arguments:    object player - who is attacking 
 *               object enemy  - who is attacked 
 * Returns:      int - success 
 */ 
int 
is_attacking(object player, object enemy) 
{
    return (player->query_attack() == enemy); 
}


/* 
 * Function:     remove_stun_from_enemy 
 * Description:  Removes a maul-induced stun from an enemy. 
 * Arguments:    object enemy - the enemy. 
 */ 
void 
remove_stun_from_enemy(object enemy) 
{ 
    if (objectp(enemy)) 
        enemy->remove_stun(); 
} 



/* 
 * Function:      deal_stun 
 * Description:   Deals a stun to an enemy as a result of mauling 
 * Arguments:     object enemy - the enemy to stun 
 */ 
void 
deal_stun(object enemy) 
{ 
    if (objectp(enemy)) 
    { 
        enemy->add_stun(); 
        set_alarm(MAUL_ATTACK_DELAY, 0.0, &remove_stun_from_enemy(enemy)); 
    } 
} 


/* 
 * Function:     calian_maul_enemy 
 * Description:  Carry out maul special after preparation 
 * Arguments:    object tp               - the swarmer 
 *               object enemy            - the enemy 
 *               object weapon           - the weapon 
 *               string current_adverb   - descriptive adverb 
 *               int time_diff           - difference in recovery time 
 */ 
private void 
calian_maul_enemy(object tp, object enemy, 
                  object weapon, string current_adverb, 
                  int time_diff) 
{ 
    object *team, *calians; 
    string weapon_desc, *hit_descr; 
    int sk, p, d; 
    mixed hit; 

    /* 
     * If enemy gone, can't maul it. 
     */ 
    if (!objectp(enemy) || !present(enemy, environment(tp))) 
    { 
        tell_object(tp, "You can no longer see the enemy you " + 
            "were preparing to maul.\n"); 
        change_maul_state(PRE_PREPARE); 
        if (auto_rep && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_maul(current_adverb, 1); 
        } 
        return; 
    } 

    /* 
     * If no longer fighting enemy, can't maul it. 
     */ 
    if (enemy != tp->query_attack()) 
    { 
        tell_object(tp, "You are no longer fighting your " + 
            "maul target.\n"); 
        change_maul_state(PRE_PREPARE); 
        if (auto_rep && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_maul(current_adverb, 1); 
        } 
        return; 
    } 

    /*
     * If chosen weapon is not wielded now, can't maul. 
     */ 
    if (!objectp(weapon) || weapon->query_wielded() != tp) 
    { 
        tell_object(tp, "You're not wielding the same weapon " + 
           "as when you prepared to maul.\n"); 
        change_maul_state(PRE_PREPARE); 
        if (auto_rep && objectp(tp->query_attack())) 
        { 
            set_this_player(tp); 
            calian_maul(current_adverb, 1); 
        } 
        return; 
    } 

    /*
     * If Calian is stunned, can't maul. 
     */ 
    if (tp->query_prop(LIVE_I_ATTACK_DELAY) || 
        tp->query_prop(LIVE_I_STUNNED)) 
    { 
        tell_object(tp, "You are currently stunned so you can't maul!\n"); 
        change_maul_state(PRE_PREPARE); 
        return; 
    } 

    /*
     * It may not be possible to attack the enemy. 
     */ 
    if (enemy->query_not_attack_me(tp, weapon->query_attack_id())) 
    { 
        change_maul_state(PRE_PREPARE); 
        return; 
    } 

    weapon_desc = weapon->short(); 
    team = FILTER_PRESENT_LIVE(tp->query_team_others()); 
    team = filter(team, &operator(==)(, enemy) @ &->query_attack()); 
    set_alarm(itof(MAUL_EXEC_TIME + time_diff), 0.0, &ready_to_maul_now(tp)); 
    change_maul_state(JUST_MAULED); 

    /* 
     * If fighting together with a Calian, on average only half the 
     * amount of fatigue and mana are taken. 
     */ 
    if (!sizeof(calians = filter(team, is_calian)) || 
        !random(2)) 
    { 
        if (tp->query_mana() < MAUL_MANA || 
            tp->query_fatigue() < MAUL_FATIGUE) 
        { 
            tell_object(tp, "As you are so weary, using " + 
                "the maul special is damaging your " + 
                "health.\n"); 
            tp->heal_hp(-20); 
        } 
        tp->add_mana(-MAUL_MANA); 
        tp->add_fatigue(-MAUL_FATIGUE); 
    } 

    /* 
     * Formula for the basic (unmodified) penetration of the attack. 
     * For a good weapon (pen 40) and stats of 100, 
     * p = (40 + ((100 / 4) + (100 / 4))) / 2 = 45. 
     */ 
    p = (weapon->query_pen() + ((tp->query_stat(SS_STR) / 4) + 
                                (tp->query_stat(SS_OCCUP) / 4))) / 2; 

    /* 
     * Make sure the basic penetration is between 24 and 65. 
     */ 
    if (p > 65) 
        p = 65; 
    else if (p < 24) 
        p = 24; 

    /* 
     * Basic multiplier for penetration (percentage) 
     */ 
    d = 80; 

    /* 
     * Closeness at start of move bonus, this applies 
     * if solo or in front line of team. Similar bonus 
     * for being in a team of more than two people. 
     */ 
    if (enemy->query_attack() == tp || 
        sizeof(team) > 2) 
        d += 10; 

    /* 
     * Sword bonus, or large team bonus.  
     */ 
    if (weapon->query_wt() == W_SWORD || 
        sizeof(team) > 3) 
        d += 10; 

    /* 
     * Team bonuses. 
     */ 
    if (sizeof(team)) 
    { 
        d += 15; 
        /* 
         * Bonus if a fellow Calian is in the team and fighting the enemy. 
         */ 
        if (sizeof(calians)) 
            d += 10; 
    } 

    /* water penalties 
    if (IN_DEEP_WATER(tp) || UNDER_WATER(tp)) 
        d = (d * tp->query_skill(SS_SWIM) / 100); 
    */ 


    /* 
     * Final pen calculation. For a good weapon (40 pen), 
     * stats of 100 and a percentage multiplier of 85 (average)
     * p will be 40. 
     */ 
    p = 2 + ((p * d) / 100); 


    /* 
     * The tohit value given to cb_tohit depends on the weapon 
     * hit value and maul skill or wisdom. For a good weapon 
     * (40 hit value) and maxed maul skill, the tohit value is 
     * 126. 
     */ 
    if (tp->query_combat_object()->cb_tohit(-1, 
                    min(max(((sk = tp->query_skill(SS_MAUL)) / 2), 
                        tp->query_stat(SS_WIS) / 2), 50) + 
                    ((25 * weapon->query_hit()) / 13), 
                     enemy) >= 0) 
    { 
        hit = enemy->hit_me(F_PENMOD(p, sk), W_SLASH, tp, -1); 

        /* 
         * If the enemy should die from this blow, give a 
         * special message, and call the do_die function in 
         * the enemy. 
         */ 
        if (enemy->query_hp() < 1) 
        { 
            tell_object(tp, "You maul " + 
                enemy->query_the_name(tp) + 
                " to death with your " + weapon_desc + "!\n"); 
            if (interactive(enemy)) 
                tell_object(enemy, tp->query_The_name(enemy) + 
                    " mauls you to death with " + tp->query_possessive() + 
                    " " + weapon_desc + "!\n"); 
            special_tell_watcher(tp, QCTNAME(tp) + " mauls " + 
                QTNAME(enemy) + " to death with " + 
                tp->query_possessive() + " " + weapon_desc + 
                "!\n", enemy, 0); 
            if (skill_by_practice) 
                practice_calian_maul_skill(tp, enemy); 
            enemy->do_die(tp); 
            return; 
        } 

        /* 
         * Check for descriptive adverb, otherwise use default. 
         */ 
        if (!stringp(current_adverb) || !strlen(current_adverb)) 
            current_adverb = maul_adv; 

        hit_descr = CALIAN_ATTACK_DESC->attack_desc_template_one(tp, 
            enemy, W_SLASH, hit[0], hit[1], weapon_desc, 
                 ({ " advance " + current_adverb + " and ", 
                    " advances " + current_adverb + " and ", 
                    " advances " + current_adverb + " and " }), 
                 maul_adverbs, 1); 

        tell_object(tp, hit_descr[0]); 

        if (interactive(enemy)) 
        { 
            tell_object(enemy, hit_descr[1]); 
        } 

        special_tell_watcher(tp, hit_descr[2], enemy, 0); 

        if (hit[0] >= 10) 
        { 
            deal_stun(enemy); 
            tell_object(tp, 
                 enemy->query_The_name(tp) + " looks stunned!\n"); 
            tell_object(enemy, "You feel stunned!\n"); 
        } 

        if (skill_by_practice) 
            practice_calian_maul_skill(tp, enemy); 

        if (tp->query_wiz_level()) 
            tell_object(tp, 
                "Pen on this maul was: " + p + ". " + 
                "Damage % was: " + hit[0] + ".\n" + 
                "Hit point damage was: " + hit[3] + ".\n" + 
                "Stun: " + (hit[0] >= 10 ? "yes" : "no") + ".\n"); 
    } 
    else 
    { 
        /* 
         * Damn, missed! 
         */ 
        tell_object(tp, 
            "You try to rip into " + enemy->query_the_name(tp) + 
            " with your " + weapon_desc + " but miss.\n"); 
        if (interactive(enemy)) 
        { 
            tell_object(enemy, tp->query_The_name(enemy) + 
                " tries to rip into you with " + tp->query_possessive() + 
                " " + weapon_desc + " but misses.\n"); 
        } 
        special_tell_watcher(tp, QCTNAME(tp) + " tries to rip into " + 
            QTNAME(enemy) + " with " + tp->query_possessive() + 
            " " + weapon_desc + " but misses.\n", enemy, 0); 

        if (skill_by_practice) 
            practice_calian_maul_skill(tp, enemy); 
    } 
} 


/* 
 * Function name: calian_maul 
 * Description:   executes the maul command 
 * Arguments:     string str - predicate 
 *                int auto - whether invoked by automatic repeat 
 * Returns:       string - success 
 */ 
varargs int 
calian_maul(string str, int auto)
{
    object enemy, weapon; 
    string current_adverb; 
    int time_diff; 

    /* 
     * Security check. 
     */ 
    if (this_object()->query_shadow_who() != TP) 
        return 0; 

    // Followers aren't allowed to maul
    if (IS_CALIAN_FOLLOWER(TP))
    {
        return 0;
    }
    
    /* 
     * If currently swarming, can't maul. 
     */ 
    if (query_swarm_state() != PRE_PREPARE) 
    { 
        calian_special_notify_fail("You may not maul while you are " + 
            "involved in any stage of a swarm.\n", TP, auto); 
        return 0; 
    } 

    last_special = "maul"; 

    /* 
     * Standard checks for preparing swarm and maul. 
     */ 
    if (!objectp(weapon = check_prepare_special(TP, "maul", auto))) 
        return 0; 

    /* 
     * If not wielding a slashing weapon, can't maul. 
     */ 
    if (!(weapon->query_dt() & W_SLASH)) 
    { 
        calian_special_notify_fail("You can't maul with a weapon " + 
            "that can't slash.\n", TP, auto); 
        return 0; 
    } 

    /* 
     * If not skilled in mauling, can't maul. 
     */ 
    if (!TP->query_skill(SS_MAUL)) 
    { 
        if (!skill_by_practice) 
        { 
            calian_special_notify_fail("You are not skilled in mauling!\n", 
                TP, auto); 
            return 0; 
        } 

        if (!objectp(enemy = try_assist(auto, "maul")))
            return 0; 

        tell_object(TP, "As you begin applying yourself to practicing " + 
            "maul, you gain one level in maul form.\n"); 
        TP->set_skill(SS_MAUL, 1); 
        TP->set_skill(SS_SWARM, TP->query_skill(SS_SWARM) - 1); 
    } 
    else 
    { 
        if (!objectp(enemy = try_assist(auto, "maul"))) 
            return 0; 
    } 

    /* 
     * Find full descriptive adverb. 
     */ 
    if (stringp(str)) 
        current_adverb = FULL_ADVERB(lower_case(str)); 

    time_diff = random(3) - 1; 

    /* 
     * Prepare to maul. 
     */ 
    set_alarm(itof(MAUL_PREP_TIME + time_diff), 0.0, 
        &calian_maul_enemy(TP, enemy, weapon, current_adverb, time_diff)); 
    tell_object(TP, "You prepare to maul " + 
        enemy->query_the_name(TP) + " with " + 
        "your " + weapon->short() + ".\n"); 
    change_maul_state(PREPARING); 
    return 1; 
} 

/* 
 * M A U L  E N D S  H E R E 
 */ 


/* 
 * M O V E  B E H I N D  S T A R T S  H E R E 
 */ 

/* 
 * Function:     it_attacking_this_living 
 * Description:  Should return whether enemy attacks player. 
 * Arguments:    object enemy    -  the enemy 
 *               object player   -  the possible victim 
 * Returns:      1 if enemy is attacking player, 0 otherwise. 
 */ 
int 
is_attacking_this_living(object enemy, object player) 
{ 
    return enemy->query_attack() == player; 
} 


/* 
 * Function:      reattack_object 
 * Description:   Called to make an enemy re-attack someone whom 
 *                a Calian moved behind. 
 * Arguments:     object enemy   - the person attacking 
 *                object friend  - the person attacked 
 */ 
void 
reattack_object(object enemy, object friend) 
{ 
    enemy->stop_fight(friend); 
    enemy->attack_object(friend); 
} 


/* 
 * Function:      stopattack_object 
 * Description:   Called to make an enemy stop fighting a Calian who 
 *                moves behind in a ROOM_M_NO_ATTACK room. 
 * Arguments:     object enemy   - the person attacking 
 *                object calian  - the person who moved behind 
 *                object friend  - person who is now in front 
 */ 
void 
stopattack_object(object enemy, object calian, object friend) 
{ 
    enemy->stop_fight(calian); 
    calian->stop_fight(enemy); 
    if (friend->query_attack() == enemy) 
    { 
        enemy->stop_fight(friend); 
        enemy->attack_object(friend); 
    } 
} 


/* 
 * Function:     ready_to_move_behind_now 
 * Description:  Called by alarm when a Calian is ready to 
 *               move behind again. By specifying the friend 
 *               they last tried to move behind, another 
 *               attempt can be made automatically. 
 * Arguments:    object tp              -  the person ready to move behind 
 *               string friend_name     -  the person who was moved behind last 
 *               string current_adverb  -  adverb to use in description 
 *               int failed             -  whether last mb failed 
 *               int mbsw               -  whether mbsw used last 
 */ 
varargs private void 
ready_to_move_behind_now(object tp, string friend_name, 
                         string current_adverb, int failed, 
                         int mbsw) 
{ 
    tp->remove_prop(CALIAN_I_JUST_MOVED_BEHIND); 
    tell_object(tp, "You are ready to move behind again.\n"); 

    /* 
     * If Calian moved behind and swarmed last time, s/he should 
     * be ready to swarm at the same time as ready to mb again. 
     */ 
    if (!failed && mbsw && simul_reset && swarm_state == JUST_SWARMED) 
    { 
        ready_to_swarm_now(tp); 
        return; 
    } 

    if (!stringp(current_adverb) || !strlen(current_adverb)) 
        current_adverb = ""; 
    else 
        current_adverb = " " + current_adverb; 

    /* 
     * If friend is specified, automatically invoke another 
     * attempt of "mbsw" or "move behind". 
     */ 
    if (stringp(friend_name)) 
    { 
        set_this_player(tp); 
        if (mbsw) 
        { 
            if (failed) 
                calian_mbsw(friend_name + current_adverb, 1); 
        } 
        else 
        { 
            if (failed) 
                calian_move_behind("behind " + 
                    friend_name + current_adverb, 1); 
        } 
    } 
} 


private void 
attack_if_not_fighting(object attacker, object victim) 
{ 
    if (objectp(attacker)) 
    { 
        if (objectp(present(attacker, environment(victim))) &&
            !objectp(attacker->query_attack()))
        { 
            attacker->stop_fight(victim); 
            attacker->attack_object(victim); 
        } 
        else 
        { 
            (attacker->query_combat_object())->cb_add_enemy(victim); 
            (victim->query_combat_object())->cb_add_enemy(attacker); 
        } 
    } 
} 


/* 
 * Function:       cleanup_mb_info 
 * Description:    allow a player who moved behind to be attacked again 
 * Arguments:      object player - the player who moved behind 
 *                 object *enemies - the livings who were avoided 
 */ 
private varargs void 
cleanup_mb_info(object player, object *enemies) 
{ 
    player->remove_prop(OBJ_M_NO_ATTACK); 
    if (pointerp(enemies) && sizeof(enemies)) 
        map(enemies, &attack_if_not_fighting(, player)); 
} 


/* 
 * Function:     write_attack_mb_message 
 * Description:  Writes messages when someone who has moved behind 
 *               is attacked, telling those who do not have the 
 *               option set for "see fights" or "gagmisses" of 
 *               the attempted attack and its failure. 
 * Arguments:    object targ     - the target of the attack 
 *               object friend   - the person protecting the target 
 *               object attacker - the person attacking 
 */ 
void 
write_attack_mb_message(object targ, object friend, object attacker) 
{
    object *liv; 
    int i; 

    liv = FILTER_PLAYERS(all_inventory(environment(targ))) - 
         ({ targ, friend, attacker }); 

    /* 
     * Show attempted attack to each onlooker who 
     * sees blood and doesn't gag misses. 
     */ 
    for (i = 0; i < sizeof(liv); i++) 
    { 
        if (!liv[i]->query_option(OPT_BLOOD) || 
            liv[i]->query_option(OPT_GAG_MISSES)) 
        { 
            tell_object(liv[i], attacker->query_The_name(liv[i]) + 
                " attempts to attack " + targ->query_the_name(liv[i]) + 
                " but " + targ->query_pronoun() + 
                " evades the onslaught with the help of " + 
                friend->query_the_name(liv[i]) + ".\n"); 
        } 
    } 

    /* 
     * If Calian sees blood and doesn't gag misses, 
     * show the attempt. 
     */ 
    if (!targ->query_option(OPT_BLOOD) || 
        targ->query_option(OPT_GAG_MISSES)) 
    { 
        tell_object(targ, attacker->query_The_name(targ) + 
            " attempts to attack you but you evade " + 
            "the onslaught with the help of " + 
            friend->query_the_name(targ) + ".\n"); 
    } 

    /* 
     * If friend sees blood and doesn't gag misses, 
     * show the attempt. 
     */ 
    if (!friend->query_option(OPT_BLOOD) || 
        friend->query_option(OPT_GAG_MISSES)) 
    { 
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
 * Returns:         A text. 
 * 
 * Authors:         Sir Rogon 
 *                  Revised and simplified by Maniac, 6/2001 
 */ 
string 
calian_is_behind(object calian, object friend) 
{
    object attacker = TP; 

    if (objectp(attacker) && 
        attacker != calian && 
        attacker != friend && 
        present(attacker, environment(calian)) && 
        CAN_SEE_IN_ROOM(calian) && 
        CAN_SEE(calian, friend)) 
    { 
        write_attack_mb_message(calian, friend, attacker); 
        return ("That opponent has temporarily maneuvered out " + 
                "of harm's way by moving behind.\n"); 
    } 
    return 0; 
} 


/* 
 * Function:     calian_do_move_behind 
 * Description:  Tries to move a Calian behind a teammate. This is 
 *               invoked from the functions "mbsw" and "move behind". 
 * Arguments:    object calian     -  person who is moving behind 
 *               object friend     -  person to move behind 
 *               string current_adverb  -  descriptive adverb (optional) 
 *               int auto          -  whether invoked automatically 
 *                                    (optional) 
 * Returns:      int - 0 for failure, 1 for successfully moving behind, 
 *               2 for the enemy onslought being too overwhelming. 
 */ 
varargs int 
calian_do_move_behind(object calian, object friend, 
                      string current_adverb, int auto, 
                      int mbsw) 
{ 
    object attacker, *team, *enemies; 
    int number_enemies, tm, mb, i, d, top_dex, total_for, 
        total_against; 

    /* 
     * Can't move behind a non-living. 
     */ 
    if (!living(friend)) 
    { 
        calian_special_notify_fail("You can only move behind " + 
           "living beings if you actually expect to get away.\n", 
           calian, auto); 
        return 0; 
    } 


    /* 
     * Check that the friend isn't attacking the Calian. 
     * This has happened in accidents! 
     */ 
    if (friend->query_attack() == calian) 
    { 
        calian_special_notify_fail("You can't move behind " + 
            "someone who is attacking you!\n", calian, auto); 
        return 0; 
    } 


    /* 
     * Check that player hasn't attacked someone within last 3 secs. 
     */ 
    if ((d = (tm = time()) - calian->query_prop(CALIAN_I_LAST_ATTACK_TIME)) 
        < 3) 
    { 
        calian_special_notify_fail("Having recently launched an " + 
            "attack you are not yet ready to move behind.\n", calian, 
            auto); 
        if (mbsw && (!restart_alarm || !get_alarm(restart_alarm))) 
        { 
            restart_alarm = 
                set_alarm(itof(3 - d), 0.0, &restart_calian_special(calian)); 
        } 
        return 0; 
    } 


    /* 
     * Next few lines prevent the tactic known as `spiralling' which 
     * can unbalance the swarm. 
     */ 
    if ((tm - calian->query_prop(CALIAN_I_LAST_MBD_BY_AT_TIME)) < 
        (3 * (SWARM_PREP_TIME + SWARM_EXEC_TIME) / 2)) 
    { 
        calian_special_notify_fail("Someone moved behind you very " + 
            "recently, you may not use move behind just yet.\n", 
            calian, auto); 
        return 0; 
    } 
    calian->remove_prop(CALIAN_I_LAST_MBD_BY_AT_TIME); 

    /* 
     * Find out the present enemies of the Calian. 
     */ 
    enemies = filter(all_inventory(environment(calian)), 
                     &is_attacking_this_living(,calian)); 
    number_enemies = sizeof(enemies); 

    /* 
     * Get team and attacked objects. 
     */ 
    team = calian->query_team_others(); 
    attacker = calian->query_attack(); 


    /* 
     * Check for carried livings like pigeons and such :) 
     */ 
    if (objectp(present(attacker, calian))) 
    { 
        calian_special_notify_fail("You can't get away from " + 
            "something you are carrying!\n", calian, auto); 
        return 0; 
    } 


    /* 
     * Check whether attempt is possible. Criteria are: skill level, 
     * number of enemies, being in a team, presence of friend on team, 
     * whether ready to moved behind again. 
     */ 
    if (!(mb = calian->query_skill(SS_MOVE_BEHIND))) 
    { 
        calian_special_notify_fail("You have no skill in moving " + 
            "behind team members during battle!\n", calian, auto); 
        return 0; 
    } 
    else if (!number_enemies) 
    { 
        calian_special_notify_fail("No-one is attacking you!\n", 
            calian, auto); 
        return 0; 
    } 
    else if (!sizeof(team)) 
    { 
        calian_special_notify_fail("You are not a member of a team.\n", 
            calian, auto); 
        return 0; 
    } 
    else if (member_array(friend, team) == -1) 
    { 
        calian_special_notify_fail(friend->query_The_name(calian) + 
            " is not a member of your team.\n", calian, auto); 
        return 0; 
    } 
    else if (calian->query_prop(CALIAN_I_JUST_MOVED_BEHIND)) 
    { 
        calian_special_notify_fail("You are not ready to try to " + 
            "move behind anyone again yet.\n", calian, auto); 
        return 0; 
    } 
    else 
    { 
        /* 
         * So an attempt can be made. 
         * Now calculate values used in determining success. 
         */ 
        calian->add_prop(CALIAN_I_JUST_MOVED_BEHIND, 1); 

        /* 
         * Estimate most powerful enemy. 
         */ 
        top_dex = 0; 
        attacker = enemies[random(sizeof(enemies))]; 
        for (i = 0; i < sizeof(enemies); i++) 
        { 
            if ((d = enemies[i]->query_stat(SS_DEX)) > top_dex) 
            { 
                 top_dex = d; 
            } 
        } 

        /* 
         * Factors in Calian's favour. 
         */ 
        total_for = 
          ((mb * (calian->query_stat(SS_DEX) + 
                  calian->query_stat(SS_WIS) + 
                  calian->query_stat(SS_INT) + 
                  friend->query_stat(SS_STR) + 
                  friend->query_stat(SS_DIS))) / 100); 

        /* 
         * Factors in enemies favour. 
         */ 
        total_against = (top_dex + attacker->query_stat(SS_WIS) + 
                        (number_enemies * 20)); 

        /* 
         * If move behind roll successful, carry out maneuver. 
         */ 
        if ((random(total_for) + mb)  > random(total_against)) 
        { 
            if (!stringp(current_adverb) || !strlen(current_adverb)) 
                current_adverb = mb_adv; 

            if (environment(calian)->query_prop(ROOM_M_NO_ATTACK)) 
            { 
                map(enemies, &stopattack_object(,calian, friend)); 
                tell_object(calian, "You " + current_adverb + 
                    " move behind " + 
                    friend->query_the_name(calian) + ".\n"); 
                tell_object(friend, calian->query_The_name(friend) + 
                    " " + current_adverb + 
                    " moves behind you.\n"); 
                tell_room(environment(calian), QCTNAME(calian) + 
                    " " + current_adverb + " moves behind " + 
                    QTNAME(friend) + ".\n", ({ calian, friend }) ); 
                set_alarm(itof(MB_NO_ATTACKED_TIME), 0.0, 
                    &cleanup_mb_info(calian, enemies)); 
            } 
            else 
            { 
                map(enemies, &reattack_object(,friend)); 
                tell_object(calian, "You " + current_adverb + 
                    " move behind " + friend->query_the_name(calian) + 
                    " and your enemies move to attack " + 
                    friend->query_objective() + ".\n"); 
                tell_object(friend, calian->query_The_name(friend) + 
                    " " + current_adverb + 
                    " moves behind you, and " + calian->query_possessive() + 
                    " enemies move to attack you!\n"); 
                tell_room(environment(calian), QCTNAME(calian) + 
                    " " + current_adverb + " moves behind " + 
                    QTNAME(friend) + ", who is attacked by " + 
                    calian->query_possessive() + 
                    " enemies!\n", ({ calian, friend }) ); 
                set_alarm(itof(MB_NO_ATTACKED_TIME), 0.0, 
                    &cleanup_mb_info(calian)); 
            } 

            /* 
             * Setting up the OBJ_M_NO_ATTACK prop as VBFC. 
             */ 
            calian->add_prop(OBJ_M_NO_ATTACK, 
                &calian_is_behind(calian, friend)); 

            /* 
             * After a successful move behind, the person may not 
             * move behind again for the time of a complete swarm 
             * cycle. This ensures against "invulnerability" 
             */ 
            set_alarm(itof(SWARM_PREP_TIME + SWARM_EXEC_TIME), 0.0, 
                &ready_to_move_behind_now(calian, 
                     friend->query_real_name(), current_adverb, 0, mbsw)); 

            /* 
             * Could swarm be reset simultaneously with mb?
             */ 
            simul_reset = (swarm_state == PRE_PREPARE); 

            if (is_calian(friend)) 
                friend->add_prop(CALIAN_I_LAST_MBD_BY_AT_TIME, tm); 
	 } 
       else 
       { 
          /* 
           * Failed to move behind. Write fail message and 
           * set recovery alarm. 
           */ 
           write("The enemy onslaught is too overwhelming for you " + 
                 "to manuever.\n"); 

           set_alarm(itof(MOVE_BEHIND_DELAY), 0.0, 
               &ready_to_move_behind_now(calian, 
                    friend->query_real_name(), 
                    current_adverb, 1, mbsw)); 
           return 2; 
       } 
    } 
    return 1; 
} 


/* 
 * Function name: move_behind 
 * Description:   executes the move behind command 
 * Arguments:     string str - predicate 
 *                int auto   - whether invoked automatically 
 * Returns:       int - success 
 */ 
varargs int 
calian_move_behind(string str, int auto) 
{ 
    string current_adverb; 
    object friend; 
    string *tmp; 

    /* 
     * Security check. 
     */ 
    if (TP != this_object()->query_shadow_who()) 
        return 0; 

    /* 
     * Parse preposition ("behind") and friend name (tmp[1]). 
     */ 
    if (!stringp(str) || (sizeof(tmp = explode(str, " ")) < 2) || 
        tmp[0] != "behind") 
    { 
        calian_special_notify_fail("Move what ?\n", TP, auto); 
        return 0; 
    } 

    /* 
     * Check that the number of elements in the syntax is correct. 
     */ 
    if (sizeof(tmp) > 3) 
    { 
        calian_special_notify_fail("Move behind whom [how]?\n", TP, auto); 
        return 0; 
    } 

    /* 
     * Check that target friend is around. 
     */ 
    if (!objectp(friend = present(lower_case(tmp[1]), environment(TP)))) 
    { 
        calian_special_notify_fail("Move behind whom [how]?\n", TP, auto); 
        return 0; 
    } 

    /* 
     * Check for descriptive adverb. 
     */ 
    if (sizeof(tmp) == 3) 
    { 
        /* 
         * Find full descriptive adverb. 
         */ 
        current_adverb = FULL_ADVERB(lower_case(tmp[2])); 
    } 

    /* 
     * Carry out move behind. 
     */ 
    if (calian_do_move_behind(TP, friend, current_adverb, auto, 0)) 
        return 1; 

    // Fail message has already been set up, so just return 0 
    return 0; 
} 


/* 
 * Function:      mbsw 
 * Description:   Action function to move behind then swarm. 
 * Arguments:     string str   - predicate 
 *                int auto     - whether invoked automatically 
 *                int just_tried_swarm  - whether just tried to swarm. 
 * Returns:       int - success 
 */ 
varargs int 
calian_mbsw(string str, int auto, int just_tried_swarm) 
{ 
    string friend_name, current_adverb, *tmp; 
    object friend; 
    int res; 

    /* 
     * Security check. 
     */ 
    if (TP != this_object()->query_shadow_who()) 
        return 0; 

    if (!stringp(str) || !strlen(str)) 
    { 
        calian_special_notify_fail("Move behind whom and swarm [how]?\n", 
            TP, auto); 
        return 0; 
    } 

    /* 
     * Check predicate for current adverb and target friend. 
     */ 
    if (sizeof(tmp = explode(str, " ")) > 1) 
    { 
        current_adverb = FULL_ADVERB(lower_case(tmp[sizeof(tmp) - 1])); 
        friend_name = lower_case(implode(tmp[0 .. sizeof(tmp) - 2], " ")); 
    } 
    else 
        friend_name = lower_case(str); 


    /* 
     * Check that target friend is around. 
     */ 
    if (!objectp(friend = present(friend_name, environment(TP)))) 
    { 
        calian_special_notify_fail("Move behind whom and swarm [how]?\n", 
            TP, auto); 
        return 0; 
    } 


    /* 
     * If already move behind someone, just try to swarm. 
     */ 
    if (TP->query_prop(OBJ_M_NO_ATTACK) && 
        calian_is_behind(TP, friend)) 
    { 
        return calian_swarm(0, auto); 
    } 

    /* 
     * Carry out move behind. If successful, swarm. 
     */ 
    if (res = calian_do_move_behind(TP, friend, current_adverb, auto, 1)) 
    { 
        if (res == 1) 
            calian_swarm(0, auto, 1); 
        return 1; 
    } 

    /* 
     * Move behind failed, just try to swarm. 
     */ 
    if (just_tried_swarm) 
        return 0; 

    return calian_swarm(0, auto); 
} 


/* 
 * MOVE BEHIND ENDS HERE 
 */ 
