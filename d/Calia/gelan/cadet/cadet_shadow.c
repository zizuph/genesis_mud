
/* 
     ~Calia/gelan/cadet/cadet_shadow.c 

     Cadets of Gelan layman guild shadow 

     Coded by Maniac@Genesis, March 1997 

     Copyright (C) Miguel Leith 1997 

     History: 
     1998/99/2000/2001    blah blah blah updates not documented     Maniac 
     5/7/01               no automatic expulsion for growing
                          above veteran, titles change, also
                          graduates can re-join                     Maniac 
     18/10/02             reminder to read help files               Maniac 
 */ 


#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include "/std/combat/combat.h"

#include "cadet.h"

varargs int gc_prepare_to_donk(string str, int auto); 
int gc_is_dedicated_cadet(); 

/* global variables */ 
int donk_state = GC_DONK_STATE_START; 
int i_attacked_cadets = 0; 
int title_restriction = 0; 
int auto_rep = 0; 
string selected_title, pretitle = ""; 
object *attacked_me = ({ }); 
object *cadet_foes = ({ }); 
object *accidental_victims = ({ }); 
string *donk_verb  = ({ }); 
string donk_str = 0; 

string query_guild_style_lay() { return GC_GUILD_STYLE; }
string query_guild_name_lay() { return GC_GUILD_NAME; }

int 
query_guild_tax_lay() 
{ 
    return GC_GUILD_TAX; 
}


/* 
 * Return 1 if they try to join an occupational guild, since
 * people in the cadets can't have an occupation. Set up a notify 
 * fail to say why in response to the join action. 
 */ 
int
query_guild_not_allow_join_lay(object player, string type, 
                               string style, string name) 
{
    if ((type == "occupational") && !player->query_wiz_level()) 
    { 
         notify_fail("You may not be in the cadets " +
                     "and have an occupation.\n"); 
         return 1;
    } 

    return ::query_guild_not_allow_join_lay(player, type, style, name);
}


void
gc_init_title()
{
   selected_title = 
      GC_SELECTED_TITLE_MAP[shadow_who->query_skill(GC_SKILL_PRIMARY_WEAPON)];  
}


/* 
 * Function:     greet_cadet 
 * Description:  Gives greetings on logging in. 
 */ 
void 
greet_cadet() 
{
    tell_object(shadow_who, 
        "Welcome, " + 
        capitalize(shadow_who->query_real_name()) + ", " + 
        query_guild_title_lay() + 
        (gc_is_dedicated_cadet() ? 
         " and dedicated guild member!\n" : 
         "!\n")); 

    if (!random(4) && 
        shadow_who->query_stat(SS_LAYMAN) < 30) 
    { 
        tell_object(shadow_who, 
            "Remember to read the help files if you " + 
            "haven't already (see \"help cadet\").\n"); 
    } 
} 


/* 
void
kick_out_if_too_big()
{
    seteuid(getuid()); 
    GC_TRAINROOM->kick_out_if_too_big(shadow_who); 
}
*/ 


void 
cadet_arrival_check() 
{
    seteuid(getuid()); 
    // kick_out_if_too_big(); 
    if (!GC_TRAINROOM->is_registered_graduate(shadow_who->query_real_name()) && 
        !IS_GRADUATE(shadow_who)) 
        GC_TRAINROOM->register_cadet(shadow_who); 
    greet_cadet(); 
}


/* 
 *  Function:     gc_set_exemplary
 *  Description:  updates the status of the cadet depending 
 *                on the opinions of dedicated cadets to
 *                exemplary.  
 */
void
gc_set_exemplary()
{
    pretitle = "Esteemed ";
}


/* 
 *  Function:     gc_set_unworthy 
 *  Description:  updates the status of the cadet depending 
 *                on the opinions of dedicated cadets to 
 *                unworthy. 
 */
void
gc_set_unworthy()
{
    title_restriction = 1; 
    i_attacked_cadets = 1; 
    pretitle = "Bothersome "; 
}


void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    gc_init_title(); 
    set_alarm(1.0, 0.0, cadet_arrival_check); 
}


void
kick_out_for_misconduct(string victim_name, string reason)
{
    seteuid(getuid()); 
    GC_TRAINROOM->kick_out_for_misconduct(shadow_who, victim_name, reason); 
}


void
warn_for_misconduct(string victim_name, string reason)
{
    seteuid(getuid()); 
    GC_TRAINROOM->warn_for_misconduct(shadow_who, victim_name, reason); 
}


mixed 
query_guild_skill_name(int type)
{
    if ((type == GC_SKILL_PRIMARY_WEAPON) || 
        (type == GC_SKILL_SECONDARY_WEAPON) ||  
        (type == SS_CADET_DROPROOM_POINTS)) 
         return "";
    else 
         return 0;
}


int
query_i_attacked_cadets()
{
    return i_attacked_cadets; 
}


/*
 * Function:    is_accidental_victim
 * Description: returns 1 if the victim was attacked as a result 
 *              of a call from another object ("forced attack" 
 *              e.g. by magic), otherwise returns 0. 
 *  
 */ 
int
is_accidental_victim(object victim) 
{
    int i = 0; 
    object pr1, pr2; 

    while (objectp(pr1 = previous_object(i--))) 
        pr2 = pr1; 

    return (objectp(pr2) && 
            (file_name(pr2) != file_name(shadow_who))); 
}


/*
 *  Suspend donk of a cadet who attacks another cadet unprovoked 
 *  or cadet friend, unless they have both agreed to brawl or duel. 
 */
void
attack_object(object victim)
{
    if (IS_GELAN_CADET(victim) || IS_CADET_FRIEND(victim) ||
        IS_GRADUATE(victim)) 
    { 
        if ((member_array(victim, cadet_foes) == -1) && 
            !(victim->query_i_attacked_cadets()) &&  
            !CADETS_CAN_BRAWL(victim, shadow_who) &&
            !CADETS_CAN_DUEL(victim, shadow_who)) 
        { 
            i_attacked_cadets = 1; 
            if (is_accidental_victim(victim)) 
            { 
                if (member_array(victim, accidental_victims) == -1) 
                    accidental_victims += ({ victim }); 
            } 
            else 
            { 
                accidental_victims -= ({ victim }); 
                cadet_foes += ({ victim }); 
                if (IS_GRADUATE(victim) && !IS_GELAN_CADET(victim)) 
                { 
                    tell_object(shadow_who, "\nYou realise that you " + 
                                "just attacked a graduate, " + 
                                "and that if you kill " + 
                                victim->query_objective() +  
                                " you will be expelled from the cadet " +
                                "guild.\n\n"); 
                } 
                else 
                { 
                    set_alarm(1.0, 0.0, 
                        &warn_for_misconduct(victim->query_real_name(), 
                        "assaulting " + capitalize(victim->query_real_name())));
                } 
            } 
        } 
    } 

    shadow_who->attack_object(victim); 
    victim->attacked_by_gelan_cadet(shadow_who); 
}


void
attacked_by(object attacker)
{
    if (IS_GELAN_CADET(attacker) || IS_CADET_FRIEND(attacker) ||
        IS_GRADUATE(attacker)) 
    { 
        if (!CADETS_CAN_DUEL(shadow_who, attacker) && 
            !CADETS_CAN_BRAWL(shadow_who, attacker)) 
        { 
            attacked_me = filter(attacked_me, objectp); 
            cadet_foes = filter(cadet_foes, objectp); 

            if (member_array(attacker, cadet_foes) == -1) 
                cadet_foes += ({ attacker }); 

            if ((member_array(attacker, attacked_me) == -1) &&  
                !query_i_attacked_cadets()) 
                attacked_me += ({ attacker }); 
        } 
    } 
    shadow_who->attacked_by(attacker); 
}


/*
 *  Kick out a cadet who kills another cadet or cadet friend unless 
 *  they were duelling or attacked by the cadet or an accidental 
 *  victim. 
 */
void
notify_you_killed_me(object victim)
{
    if (IS_GELAN_CADET(victim) || IS_CADET_FRIEND(victim) || 
        IS_GRADUATE(victim)) 
    { 
        if (!CADETS_CAN_DUEL(shadow_who, victim) && 
            !(victim->query_i_attacked_cadets()) && 
            (member_array(victim, attacked_me) == -1) && 
            (member_array(victim, accidental_victims) == -1)) 
            set_alarm(1.0, 0.0, 
                &kick_out_for_misconduct(victim->query_real_name(), 
                "killing " + capitalize(victim->query_real_name()))); 
    } 
    shadow_who->notify_you_killed_me(victim); 
}


int
gc_donk_state_start()
{
    return (donk_state == GC_DONK_STATE_START); 
}


int
gc_donk_state_prepare()
{
    return (donk_state == GC_DONK_STATE_PREPARE); 
}


int
gc_donk_state_recover()
{
    return (donk_state == GC_DONK_STATE_RECOVER); 
}


void 
gc_recover_donk() 
{ 
    donk_state = GC_DONK_STATE_START; 
    tell_object(shadow_who, "You are ready to donk again!\n"); 
    set_this_player(shadow_who); 
    if (auto_rep) 
        gc_prepare_to_donk(donk_str, 1); 
} 


void 
gc_do_donk(object pl, int aid) 
{ 
     mixed att, hit; 
     object cob; 
     string wep_desc, *hit_desc; 
     int wep_hit, wep_pen, wep_dt, wep_skill, *poss_hit_types; 

     if (!objectp(pl) || 
         !living(pl) || 
         !present(pl, environment(shadow_who))) 
     { 
         tell_object(shadow_who, "You lost your donk target!\n"); 
         donk_state = GC_DONK_STATE_START; 
         return; 
     } 

     if (shadow_who->query_prop(LIVE_I_STUNNED) || 
         shadow_who->query_prop(LIVE_I_ATTACK_DELAY)) 
     { 
         tell_object(shadow_who, "You are too stunned to donk!\n"); 
         donk_state = GC_DONK_STATE_START; 
         return; 
     } 

     cob = shadow_who->query_combat_object(); 

     att = cob->query_attack(aid); 
     wep_desc = cob->cb_attack_desc(aid); 
     wep_hit = max((att[ATT_WCHIT] * 5) / 4, (att[ATT_SKILL] * 13) / 20); 
     wep_pen = (att[ATT_WCPEN][0] * 29) / 20; 
     wep_dt = att[ATT_DAMT]; 
     wep_skill = (att[ATT_SKILL] * 9) / 5; 

     if (cob->cb_tohit(aid, wep_hit, pl) >= 0) 
     { 
         hit = pl->hit_me(F_PENMOD(wep_pen, wep_skill), 
                          wep_dt, shadow_who, -1); 

         if (shadow_who->query_wiz_level()) 
             tell_object(shadow_who, "Wiz info:\n" + 
                         "Hit:" + wep_hit + " Pen:" + wep_pen + 
                         " Dt:" + wep_dt + " Proc hurt:" + hit[0] + 
                         " Sk:" + wep_skill + ".\n"); 

         if (pl->query_hp() <= 0) 
         { 
             switch (random(3)) 
             { 
                 case 0 : 
                          shadow_who->catch_msg("You send " + 
                              pl->query_the_name(shadow_who) + " to meet " + 
                              pl->query_possessive() + " maker with a " + 
                              "deadly donk of your " + wep_desc + ".\n"); 

                          if (interactive(pl)) 
                          { 
                              pl->catch_msg(shadow_who->query_The_name(pl) + 
                                            " sends you to meet your maker " +
                                            "with a deadly donk of " + 
                                            shadow_who->query_possessive() + 
                                            " " + wep_desc + ".\n"); 
                          }

                          pl->tell_watcher(QCTNAME(shadow_who) + " sends " + 
                                           QTNAME(pl) + " to meet " + 
                                           pl->query_possessive() + " maker " + 
                                           "with a deadly donk of " + 
                                           shadow_who->query_possessive() + 
                                           " " + wep_desc + ".\n", shadow_who, 
                                           ({ }));
                          break;  

                 case 1 :
                         shadow_who->catch_msg("As you donk " + 
                             pl->query_the_name(shadow_who) + "'s " + 
                             hit[1] + " you feel Death's cold grasp reach " + 
                             "out from your " + wep_desc + ".\n"); 

                         if (interactive(pl)) 
                         { 
                              pl->catch_msg("As " + 
                                 shadow_who->query_the_name(pl) + " donks " + 
                                 "your " + hit[1] + 
                                 " you feel Death's cold grasp reach " +
                                 "out from " + shadow_who->query_possessive() + 
                                 " " + wep_desc + ".\n"); 
                         }

                         pl->tell_watcher("As " + QTNAME(shadow_who) + 
                               " donks " + QTNAME(pl) + "'s " + hit[1] + 
                               " you sense Death's cold grasp reach " +
                               "out from " + shadow_who->query_possessive() + 
                               " " + wep_desc + ".\n", shadow_who, ({ })); 
                         break; 

                 default : 
                         shadow_who->catch_msg("With a savage donk " + 
                             "of your " + wep_desc + " you send " + 
                             pl->query_the_name(shadow_who) + " to " + 
                             pl->query_possessive() + " grave.\n"); 

                         if (interactive(pl)) 
                         { 
                             pl->catch_msg("With a savage donk " + 
                                 "of " + shadow_who->query_possessive() + 
                                 "'s " + wep_desc + " " + 
                                 shadow_who->query_the_name(pl) + 
                                 " sends you to your grave.\n"); 
                         } 

                         pl->tell_watcher("With a savage donk of " + 
                                shadow_who->query_possessive() + "'s " + 
                                wep_desc + " " + QTNAME(shadow_who) + 
                                " sends " + 
                                QTNAME(pl) + " to " + pl->query_possessive() + 
                                " grave.\n", shadow_who, ({ })); 
                         break; 
             } 
             pl->do_die(shadow_who); 
             donk_state = GC_DONK_STATE_RECOVER; 
             set_alarm(itof(GC_DONK_RECOVER_TIME), 0.0, gc_recover_donk); 
             return; 
         } 
     } 
     else 
     { 
         hit = pl->hit_me(0, wep_dt, shadow_who, -1); 
         hit[0] = -1; 
     } 

     poss_hit_types = ({ }); 
     if (wep_dt & W_SLASH) 
         poss_hit_types += ({ W_SLASH }); 
     if (wep_dt & W_IMPALE) 
         poss_hit_types += ({ W_IMPALE }); 
     if (wep_dt & W_BLUDGEON) 
         poss_hit_types += ({ W_BLUDGEON }); 

     if (!sizeof(poss_hit_types)) 
         wep_dt = W_BLUDGEON; 
     else 
         wep_dt = poss_hit_types[random(sizeof(poss_hit_types))]; 

     seteuid(getuid()); 
     hit_desc = GC_ATTACK_DESC->attack_desc_template_one(shadow_who, pl, 
                                wep_dt, hit[0], hit[1], wep_desc, donk_verb); 

     shadow_who->catch_msg(hit_desc[0]); 

     if (interactive(pl)) 
         pl->catch_msg(hit_desc[1]); 

     pl->tell_watcher(hit_desc[2], shadow_who, ({ })); 

     donk_state = GC_DONK_STATE_RECOVER; 
     set_alarm(itof(GC_DONK_RECOVER_TIME), 0.0, gc_recover_donk); 
     return; 
}


/* 
 * Function:      prepare_donk_fail_message 
 * Description:   provides a donk fail message via either notify_fail 
 *                or tell_object. 
 * Arguments:     as_tell     -  1 to get message via tell, 0 for nf. 
 * Returns:       1 if message sent as tell, 0 otherwise. 
 */ 
int 
prepare_donk_fail_message(string str, int as_tell)
{
    if (as_tell)
    { 
        tell_object(shadow_who, str); 
        return 1; 
    } 
    notify_fail(str); 
    return 0; 
}



/* 
 *   Function:      gc_prepare_to_donk 
 *   Description:   Action function to prepare to use the "donk" 
 *                  special attack. Called from the cadet soul 
 *                  or automatically from the shadow when donk 
 *                  cycles. 
 *   Arguments:     string str -  the argument of the command. 
 *                  int auto   -  if this is invoked automatically. 
 */ 
varargs int 
gc_prepare_to_donk(string str, int auto) 
{
     object pl; 
     int aid, donk_ban; 

     if (!auto) 
     { 
         if (auto_rep) 
         { 
             if (query_verb() == "donk") 
                 auto_rep = 0; 
         } 
         else 
         { 
             if (query_verb() == "cdonk") 
                 auto_rep = 1; 
         } 
     } 

     if (stringp(str)) 
         donk_str = str; 
     else if (stringp(donk_str)) 
         str = donk_str; 
     donk_ban = shadow_who->query_skill(SS_CADET_DONK_BAN); 
     if (donk_ban) 
     { 
         if (donk_ban > time()) 
         { 
             return prepare_donk_fail_message(
                         "You have been banned from donking " + 
                         "until " + ctime(donk_ban) + ".\n", auto); 
         } 
         else 
         { 
             shadow_who->remove_skill(SS_CADET_DONK_BAN); 
         } 
     } 

     if (str == "left") 
         aid = W_LEFT; 
     else if (str == "right") 
         aid = W_RIGHT; 
     else if (str == "both") 
     { 
         if (!shadow_who->query_weapon(W_BOTH)) 
         { 
             return prepare_donk_fail_message(
                         "You are not wielding a two-handed weapon, " + 
                         "and a two-handed unarmed attack will not " + 
                         "have any effect.\n", auto); 
         } 
         aid = W_BOTH; 
     } 
     else if (!stringp(str) || !strlen(str)) 
     { 
         if (objectp(shadow_who->query_weapon(W_BOTH))) 
             aid = W_BOTH; 
         else if (objectp(shadow_who->query_weapon(W_LEFT))) 
             aid = W_LEFT; 
         else 
             aid = W_RIGHT; 
     } 
     else 
     { 
         return prepare_donk_fail_message(
                    "Donk with what hand?\n", auto); 
     } 

     if (gc_donk_state_prepare())  
     { 
         return prepare_donk_fail_message(
                "You are currently preparing to donk.\n", auto); 
     } 

     if (gc_donk_state_recover())  
     { 
         return prepare_donk_fail_message(
                "You are currently recovering from a donk.\n", auto); 
     } 

     if (shadow_who->query_prop(LIVE_I_STUNNED) || 
         shadow_who->query_prop(LIVE_I_ATTACK_DELAY)) 
     { 
         return prepare_donk_fail_message(
                 "You are too stunned to donk!\n", auto); 
     } 

     if (!objectp(pl = shadow_who->query_attack())) 
     { 
         return prepare_donk_fail_message(
                "You are not fighting anyone!\n", auto); 
     } 

     donk_state = GC_DONK_STATE_PREPARE; 
     tell_object(shadow_who, "You prepare to donk " + 
                  pl->query_the_name(shadow_who) + ".\n"); 
     set_alarm(itof(GC_DONK_PREP_TIME), 0.0, &gc_do_donk(pl, aid)); 
     return 1; 
}


/* 
 * Function:     gc_change_hands 
 * Description:  Change the hand that is used for the "donk" special. 
 * 
 */ 
int 
gc_change_hands(string str) 
{
    if (str == "right") 
    { 
        donk_str = "right"; 
        write("You will attack with the right fist or the weapon " + 
              "wielded in the right hand when using the " + 
              "<donk> special.\n"); 
        return 1; 
    } 
    else if (str == "left") 
    { 
        donk_str = "left"; 
        write("You will attack with the left fist or the weapon " + 
              "wielded in the left hand when using the " + 
              "<donk> special.\n"); 
        return 1; 
    } 
    else if (str == "both") 
    { 
        donk_str = "both"; 
        write("You will attack with the weapon wielded " + 
              "in both hands when using the <donk> special.\n"); 
        return 1; 
    } 

    if (!stringp(str) || !strlen(str)) 
    { 
        if (!stringp(donk_str)) 
        { 
            write("You have not specified which hand(s) to " + 
                  "attack with when using the <donk> special.\n"); 
            return 1; 
        } 
        write("You will attack with " + (donk_str == "both" ? 
              "the weapon wielded in both hands" : 
              "the " + donk_str + " fist or the weapon wielded in " + 
              "the " + donk_str + " hand") + 
              " when using the <donk> special.\n"); 
        return 1; 
    } 
    notify_fail("Syntax: <cchange> [left/right/both].\n"); 
    return 0; 
}


int
gc_query_skill_num(int sk)
{
    switch (shadow_who->query_skill(sk)) 
    { 
        case GC_SELECTED_NOTHING : 
                return -1; 
                break;
        case GC_SELECTED_SWORD : 
                return SS_WEP_SWORD; 
                break;
        case GC_SELECTED_POLEARM : 
                return SS_WEP_POLEARM; 
                break;
        case GC_SELECTED_AXE : 
                return SS_WEP_AXE; 
                break;
        case GC_SELECTED_KNIFE : 
                return SS_WEP_KNIFE; 
                break;
        case GC_SELECTED_CLUB : 
                return SS_WEP_CLUB; 
                break;
        case GC_SELECTED_UNARMED : 
                return SS_UNARM_COMBAT; 
                break;
    } 
}


int
gc_query_primary_skill_num()
{
    return gc_query_skill_num(GC_SKILL_PRIMARY_WEAPON); 
}


int 
gc_query_secondary_skill_num()
{
    return gc_query_skill_num(GC_SKILL_SECONDARY_WEAPON); 
}


string
gc_query_skill_name(int sk)
{
    switch (shadow_who->query_skill(sk)) 
    { 
        case GC_SELECTED_NOTHING : 
                return "unselected"; 
                break;
        case GC_SELECTED_SWORD : 
                return "sword"; 
                break;
        case GC_SELECTED_POLEARM : 
                return "polearm"; 
                break;
        case GC_SELECTED_AXE : 
                return "axe"; 
                break;
        case GC_SELECTED_KNIFE : 
                return "knife"; 
                break;
        case GC_SELECTED_CLUB : 
                return "club"; 
                break;
        case GC_SELECTED_UNARMED : 
                return "unarmed combat"; 
                break;
        default: return "none"; 
                 break;
    } 
}


string
gc_query_primary_skill_name()
{
    return gc_query_skill_name(GC_SKILL_PRIMARY_WEAPON); 
}


string
gc_query_secondary_skill_name()
{
    return gc_query_skill_name(GC_SKILL_SECONDARY_WEAPON); 
}


string 
gc_selected_title()
{
    return selected_title; 
}


/* 
 * Function:    gc_query_skill_level
 * Description: Query the percentage of skill the cadet has reached 
 *              out of the maximum possible of all the guild's skills.
 */ 
int
gc_query_skill_level()
{
    int l; 

    l = (shadow_who->query_skill(gc_query_primary_skill_num()) + 
         shadow_who->query_skill(gc_query_secondary_skill_num()) + 
         shadow_who->query_skill(SS_DEFENCE) + 
         shadow_who->query_skill(SS_PARRY) + 
         shadow_who->query_skill(SS_2H_COMBAT) + 
         shadow_who->query_skill(SS_BLIND_COMBAT)); 

    /* 269 = 50 + 45 + 50 + 37 + 37 + 50 */ 
    return (l * 100) / 269; 
}


/* 
 * Function:    gc_query_rack_level 
 * Description: returns a rating of the player's rack contribution, 
 *              a value of 100 or more indicates it is excellent. 
 */ 
int 
gc_query_rack_level() 
{ 
    return 
        ((shadow_who->query_skill(SS_CADET_DROPROOM_POINTS) * 100) / 
          max(60000, shadow_who->query_average_stat() * 1000)); 
} 


/* 
 * Function:     gc_is_dedicated_cadet 
 * Description:  returns 1 if the cadet is considered dedicated to 
 *               the guild, 0 otherwise. 
 * 
 */ 
int
gc_is_dedicated_cadet()
{
    return (shadow_who->query_stat(SS_LAYMAN) >= 50 && 
            gc_query_rack_level() >= 100 && 
            gc_query_skill_level() >= 80); 
}


string
gc_level_title()
{
    int l; 

    l = (shadow_who->query_skill(gc_query_primary_skill_num()) + 
         shadow_who->query_skill(gc_query_secondary_skill_num()) + 
         shadow_who->query_skill(SS_DEFENCE) + 
         shadow_who->query_skill(SS_PARRY) + 
         shadow_who->query_skill(SS_2H_COMBAT) + 
         shadow_who->query_skill(SS_BLIND_COMBAT) + 
         (shadow_who->query_stat(SS_LAYMAN) * 2) + 
         (shadow_who->query_skill(SS_CADET_DROPROOM_POINTS) / 500)); 

    /* 404 = 50 + 45 + 50 + 37 + 37 + 50 + 100 + 35 */ 
    l = (l * (GC_NUM_LEVEL_TITLES - 1)) / 404; 

    if (l >= GC_NUM_LEVEL_TITLES) 
        l = (GC_NUM_LEVEL_TITLES - 1); 

    if (l && title_restriction)
        return GC_LEVEL_TITLE_ARR[l - 1]; 

    return GC_LEVEL_TITLE_ARR[l]; 
}


string 
query_guild_title_lay() 
{ 
    if (IS_GRADUATE(shadow_who)) 
    { 
        return (pretitle + 
            (strlen(selected_title) ? (selected_title + " ") : "") + 
            "Postgraduate of Gelan"); 
    } 

    if (shadow_who->query_average_stat() <= GC_MAX_AVG_STAT) 
    { 
        return (pretitle + gc_level_title() + " " + 
                (strlen(selected_title) ? (selected_title + " ") : "") + 
                GC_BASE_TITLE); 
    } 

    return (pretitle + gc_level_title() + " " + 
            (strlen(selected_title) ? (selected_title + " ") : "") + 
             "Warrior of Gelan"); 
} 


string
query_guild_trainer_lay()
{
    return GC_TRAINROOM;
}
