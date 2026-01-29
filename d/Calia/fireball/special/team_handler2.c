
 /* 

     ~Calia/fireball/special/team_handler.c 

     This is the file containing all static info on npc fireball 
     teams. It also contains action functions for outputting npc 
     player and team data and functions for cloning a team of npcs. 

     Coded by Maniac@Genesis, 1997/1998/1999

     Copyright (C) Miguel Leith 1997/1998/1999

     History: 
     1997/1998/1999        Created                                 Maniac 
     2000       blah blah undocumented modifications               Maniac 
     15/12/01   Modified ready for general experience awards       Maniac 
     29/12/01   General experience added.                          Maniac
 */ 

#pragma save_binary
#pragma strict_types
#pragma no_inherit

#include "defs.h"

#include FIREBALL_HEADER

inherit "/std/room"; 
inherit FIREBALL_UTILS; 

#include <macros.h>
#include <stdproperties.h>
#include <const.h> 
#include <ss_types.h>
#include <files.h>
#include <living_desc.h>
#include <composite.h>
#include <language.h>
#include <state_desc.h>
#include "/d/Genesis/login/login.h"

#define GIVE_QUEST_REWARDS
#define GIVE_GENERAL_REWARDS

/* 
 * Player profiles take form shown in the FIREBALL_P_ defs below
 */ 

#define FIREBALL_P_ADJ  0 
#define FIREBALL_P_GENDER 1 
#define FIREBALL_P_RACE 2 
#define FIREBALL_P_HEIGHT 3 
#define FIREBALL_P_WEIGHT 4 
#define FIREBALL_P_STAT 5 
#define FIREBALL_P_ALIGN 6 
#define FIREBALL_P_SKILL 7 
#define FIREBALL_P_POS 8 
#define FIREBALL_P_COMMENT 9
#define FIREBALL_P_WAGES 10

#define FIREBALL_QUEST_GROUP 1 

/* 
 * Team data takes form shown in the FIREBALL_TD_ defs below
 */ 
#define FIREBALL_TD_TEAM 0 
#define FIREBALL_TD_QUEST_XP 1
#define FIREBALL_TD_QUEST_BIT 2
#define FIREBALL_TD_FORMATION 3
#define FIREBALL_TD_FORMATION_FILE 4


mapping gdesc = LD_GENDER_MAP; 

/* Team goes: defender, midfield, attacker */ 
mapping team_data; 

mapping player_data;

void
create_room()
{
    mapping raceattr;

    set_short("Fireball team handler room"); 
    set_long("Fireball team npcs please wait here until " +
             "you are called.\n"); 
 
    team_data = 
    ([ 
       "All Scums" : ({ ({ "xenvyr", "dakjo", "clurata", "gorphu" }), 
                        10000, 17, FIREBALL_FORMATION_SICKLE,
                        FIREBALL_SICKLE_FORMATION_FILE }), 
       "War Eagles" : ({ ({ "regan", "phorias", "gymar", "katren" }), 
                         5600, 16, FIREBALL_FORMATION_ARROW,
                         FIREBALL_ARROW_FORMATION_FILE }), 
       "Tiger Sharks" : ({ ({ "dresha", "zoye", "ordania", "isteron" }), 
                         3200, 15, FIREBALL_FORMATION_SCORPION,
                         FIREBALL_SCORPION_FORMATION_FILE }), 
       "Poison Arrows" : ({ ({ "quarvic", "gindru", "taros", "teryn" }), 
                            1700, 14, FIREBALL_FORMATION_DAGGER,
                            FIREBALL_DAGGER_FORMATION_FILE }), 
       "Hailrocks" : ({ ({ "gundar", "nellie", "apir", "tai" }), 
                        900, 13, FIREBALL_FORMATION_ARROW,
                        FIREBALL_ARROW_FORMATION_FILE }), 
     ]); 

/*
 * RACEATTR
 *
 * This mapping holds the standard attributes for each race. The attributes
 * are: 
 *      standard height         (cm)
 *      standard weight         (kg)
 *      standard opinion        (0-100)
 *      standard appereance     (0-100)
 *      standard volume         (dm^3)
 *      standard fatness        (g/cm)
 */
    raceattr = RACEATTR; 
    raceattr["ogre"] = ({ 290, 200, 90, 90, 200, 500 }); 

    player_data  = 
      ([ 
      /* Hailrocks */  
      "gundar" : ({ ({ "stout", "red-eyed" }), G_MALE, "human",  
                  raceattr["human"][0]+1, raceattr["human"][1]+2, 
                  20, 50, 24, FIREBALL_POS_BACK, "", 25 }), 

      "nellie" : ({ ({ "willowy", "weathered" }), G_FEMALE, "elf", 
                   raceattr["elf"][0]-9, raceattr["elf"][1]+3, 
                  20, 25, 25, FIREBALL_POS_LEFT_MIDFIELD, "", 25 }), 

      "apir" : ({ ({ "green-skinned", "pointy-eared" }), G_MALE, "goblin", 
                   raceattr["goblin"][0]+3, raceattr["goblin"][1]+1, 
                  20, -50, 24, FIREBALL_POS_RIGHT_MIDFIELD, "", 25 }), 

      "tai" : ({ ({ "angry", "blond-bearded" }), G_MALE, "gnome", 
                   raceattr["gnome"][0]+1, raceattr["gnome"][1]-2, 
                  20, -25, 25, FIREBALL_POS_FORWARD, "", 25 }), 

      /* Poison Arrows */  
      "quarvic" : ({ ({ "adolescent", "dimpled" }), G_MALE, "elf",  
                  raceattr["elf"][0]-5, raceattr["elf"][1]-10, 
                  45, 400, 43, FIREBALL_POS_BACK, "", 75 }), 

      "gindru" : ({ ({ "pale", "wide-mouthed" }), G_MALE, "gnome", 
                   raceattr["gnome"][0]+2, raceattr["gnome"][1]+5, 
                  46, 200, 39, FIREBALL_POS_LEFT_MIDFIELD, "", 75 }), 

      "taros" : ({ ({ "charming", "energetic" }), G_MALE, "dwarf", 
                   raceattr["dwarf"][0]+3, raceattr["dwarf"][1]+1, 
                  45, 230, 41, FIREBALL_POS_RIGHT_MIDFIELD, "", 75 }), 

      "teryn" : ({ ({ "friendly", "young" }), G_FEMALE, "human", 
                   raceattr["human"][0]-2, raceattr["human"][1]-4, 
                  47, 230, 41, FIREBALL_POS_FORWARD, "", 75 }), 

      /* TIGER SHARKS */ 
      "dresha" : ({ ({ "tanned", "animated" }), G_FEMALE, "goblin", 
                   raceattr["goblin"][0]-4, raceattr["goblin"][1]-6, 
                  65, 150, 54, FIREBALL_POS_BACK, "", 165 }), 

      "zoye" :  ({ ({ "depressed", "dirty" }), G_MALE, "human", 
                   raceattr["human"][0]+3, raceattr["human"][1]+7, 
                  68, 0, 56, FIREBALL_POS_LEFT_MIDFIELD, "", 165 }), 

      "ordania" : ({ ({ "athletic", "long-legged" }), G_FEMALE, "gnome", 
                   raceattr["gnome"][0]+1, raceattr["gnome"][1]-4, 
                  67, 50, 58, FIREBALL_POS_RIGHT_MIDFIELD, "", 165 }), 

      "isteron" : ({ ({ "calm", "black-haired" }), G_MALE, "hobbit", 
                   raceattr["hobbit"][0]+5, raceattr["hobbit"][1]+5, 
                  65, 100, 56, FIREBALL_POS_FORWARD, "", 165 }), 

      /* WAR EAGLES */ 
      "regan" : ({ ({ "muscular", "black-haired" }), G_MALE, "hobbit", 
                   raceattr["hobbit"][0]+2, raceattr["hobbit"][1]+5, 
                  91, 200, 69, FIREBALL_POS_BACK, 
                  "", 250 }), 

      "phorias" : ({ ({ "tall", "black-eyed" }), G_MALE, "human",  
                  raceattr["human"][0]+4, raceattr["human"][1]+3, 
                  94, 250, 73, FIREBALL_POS_LEFT_MIDFIELD, 
                  "", 250 }), 

      "gymar" : ({ ({ "philosophical", "long-faced" }), G_MALE, "dwarf",  
                  raceattr["dwarf"][0]+2, raceattr["dwarf"][1]-3, 
                  93, 300, 69, FIREBALL_POS_RIGHT_MIDFIELD, 
                  "", 250 }), 

      "katren" : ({ ({ "ivory-skinned", "dark-eyed" }), G_FEMALE, "elf",  
                  raceattr["elf"][0]-12, raceattr["elf"][1]+5, 
                  94, 300, 71, FIREBALL_POS_FORWARD, 
                  "", 250 }), 

      /* ALL SCUMS */ 
      "xenvyr" : ({ ({ "crude", "surly" }), G_MALE, "ogre", 
                   raceattr["ogre"][0], raceattr["ogre"][1]+5,  
                   120, -400, 81, FIREBALL_POS_BACK,  
                   "He's nasty but classy.", 
                   400 }),  

      "dakjo":({ ({ "lumbering", "brutal" }), G_MALE, "ogre", 
                   raceattr["ogre"][0]+15, raceattr["ogre"][1]+20,  
                   125, -350, 79, FIREBALL_POS_LEFT_MIDFIELD,  
                   "He can move mountains (himself).",
                   400 }),  

      "clurata":({ ({ "indignant", "obnoxious" }), G_FEMALE, "ogre", 
                   raceattr["ogre"][0]-5, raceattr["ogre"][1]-5,  
                   120, -450, 81, FIREBALL_POS_RIGHT_MIDFIELD,  
                   "She's one tricky customer.", 
                   400 }),  

      "gorphu": ({ ({ "cruel", "aggressive" }), G_MALE, "ogre", 
                   raceattr["ogre"][0]+5, raceattr["ogre"][1]+10,  
                   130, -500, 85, FIREBALL_POS_FORWARD,
                   "He shoots like a catapult and kicks like a mule.", 
                   400 }),  
     ]); 
}


/*
 * Function:     query_team_names
 * Description:  returns an array of the fireball npc team names
 *
 */ 
string * 
query_team_names()
{
    return m_indexes(team_data); 
}


int
query_npc_team(string tn)
{
    return (member_array(query_proper_team_name(tn), query_team_names()) > -1); 
}

/* 
 * Function:     query_player_info
 * Description:  Returns a formatted string describing data about 
 *               a particular player. 
 */ 
string
query_player_info(string nm)
{
    int i, j;
    string r;
    mixed info; 

    nm = lower_case(nm);  
    if (!(info = player_data[nm])) 
        return 0;

    r = ("Player Profile: " + capitalize(nm) + "\n"); 
    j = strlen(r) - 1; 
    for (i = 0; i < j; i++)  
       r += "="; 
    r += "\n";

    r += sprintf("%-12s %s. \n", "Description:", 
                   capitalize(implode(info[FIREBALL_P_ADJ], " ") + " " + 
                              gdesc[info[FIREBALL_P_GENDER]] + " " +   
                              info[FIREBALL_P_RACE])); 

    r += sprintf("%-12s %s metres. \n", "Height:", 
                        info[FIREBALL_P_HEIGHT] / 100 + "." + 
                        ((info[FIREBALL_P_HEIGHT] % 100) / 10)  + 
                        ((info[FIREBALL_P_HEIGHT] % 100) % 10)); 

    r += sprintf("%-12s %d kg. \n", "Weight:", 
                        info[FIREBALL_P_WEIGHT]);  

    seteuid(getuid()); 
    r += sprintf("%-12s %s. \n", "Power:", capitalize(
           GET_STAT_LEVEL_DESC(SS_STR, info[FIREBALL_P_STAT])));  
    r += sprintf("%-12s %s. \n", "Skill:", 
          capitalize(SKILL_LIBRARY->sk_rank(info[FIREBALL_P_SKILL])));  
    r += sprintf("%-12s %s. \n", "Position:", capitalize(info[FIREBALL_P_POS])); 
    r += sprintf("%-12s %s. \n", "Wages:", info[FIREBALL_P_WAGES] + " cc"); 
    if (strlen(info[FIREBALL_P_COMMENT])) 
        r += sprintf("%-12s %s\n", "Comment:", info[FIREBALL_P_COMMENT]); 

    return r; 
}


/*
 * Function:     write_player_info
 * Description:  An action function called from the foyer. 
 */ 
int
write_player_info(string nm)
{
    string pi; 

    if (!stringp(nm) || !strlen(nm)) { 
        notify_fail("Which player do you want info about?\n"); 
        return 0; 
    } 

    if (!(pi = query_player_info(nm))) { 
        notify_fail("No information on a player called " + nm + " " + 
                    "is available.\n"); 
        return 0;
    } 

    write(pi); 
    return 1;
}


/* 
 * Function:     query_team_average
 * Description:  return an average value an attribute for a team  
 *               e.g. average skill/stat of All Scums.
 * 
 */ 
int
query_team_average(string team_name, int attr)
{
    mixed t;
    int i, a;

    if (!pointerp(t = team_data[query_proper_team_name(team_name)])) 
        return 0;

    t = t[FIREBALL_TD_TEAM]; 
    a = 0; 
    for (i = 0; i < sizeof(t); i++)    
        a += player_data[t[i]][attr];  

    return (a / sizeof(t));
}


int
query_team_average_stat(string team_name)
{
    return query_team_average(team_name, FIREBALL_P_STAT);
}


string
query_team_average_stat_desc(string team_name)
{
    seteuid(getuid()); 
    return capitalize(GET_STAT_LEVEL_DESC(SS_STR, 
                             query_team_average(team_name, FIREBALL_P_STAT)));  
}


string
query_team_average_skill_desc(string team_name)
{
    seteuid(getuid()); 
    return capitalize(SKILL_LIBRARY->sk_rank(query_team_average(team_name, 
                                                          FIREBALL_P_SKILL)));  
}

string
query_formation(string team_name)
{
    mixed t; 

    if (pointerp(t = team_data[query_proper_team_name(team_name)]))
        return t[FIREBALL_TD_FORMATION]; 

    return 0; 
}


string
query_formation_file(string team_name)
{
    mixed t; 

    if (pointerp(t = team_data[query_proper_team_name(team_name)]))
        return t[FIREBALL_TD_FORMATION_FILE]; 

    return 0; 
}


string
query_team_info(string team_name)
{
    int i, j; 
    mixed t;
    string r;

    team_name = query_proper_team_name(team_name); 
    if (!(t = team_data[team_name])) 
        return 0;

    r = ("Team Profile: " + team_name + "\n"); 
    j = strlen(r) - 1; 
    for (i = 0; i < j; i++)  
       r += "="; 
    r += "\n";

    r += sprintf("%-10s %s. \n", "Players:",
                 COMPOSITE_WORDS(map(t[FIREBALL_TD_TEAM], capitalize))); 
    r += sprintf("%-10s %s. \n", "Power:", 
                      capitalize(query_team_average_stat_desc(team_name))); 
    r += sprintf("%-10s %s. \n", "Skill:", 
                      capitalize(query_team_average_skill_desc(team_name)));
    r += sprintf("%-10s %s. \n", "Formation:", 
                      capitalize(t[FIREBALL_TD_FORMATION]));  
    return r;
}


/*
 * Function:     write_team_info
 * Description:  An action function called from the foyer. 
 */ 
int
write_team_info(string team_name)
{
    string ti; 

    if (!stringp(team_name) || !strlen(team_name)) { 
        notify_fail("Which team do you want info about?\n"); 
        return 0; 
    } 

    if (!(ti = query_team_info(team_name))) { 
        notify_fail("No information on a team called " + team_name + " " + 
                    "is available.\n"); 
        return 0;
    } 

    write(ti); 
    return 1;
}


string
query_available_teams() 
{
    return ("Available Teams:\n" +  
            "================\n" + 
            sprintf("%-80#s\n", 
                   implode(query_team_names(), "\n"))); 
}


/*
 * Function:     write_teams_info 
 * Description:  An action function called from the foyer. 
 */ 
int
write_teams_info(string str)
{
    write(query_available_teams()); 
    return 1;
}



/*
 * Function:     query_wages
 * Description:  returns the wages of the named npc in copper coins
 *
 */ 
int
query_wages(string name) 
{
    mixed info; 

    if (!(info = player_data[lower_case(name)])) 
        return 0;

    return info[FIREBALL_P_WAGES]; 
}


/*
 * Function:     query_team
 * Description:  returns the players names of a fireball npc team
 *
 */ 
varargs string *
query_team(string team_name, int lower_case = 0)
{
    mixed t; 

    if (pointerp(t = team_data[query_proper_team_name(team_name)])) {
        if (lower_case) 
            return secure_var(t[FIREBALL_TD_TEAM]); 
        return map(secure_var(t[FIREBALL_TD_TEAM]), capitalize); 
    } 

    return 0; 
}


/*
 * Function:     query_beaten_team
 * Description:  Returns 1 if the given player has beaten the specified
 *               npc team, 0 otherwise. 
 */ 
int
query_beaten_team(object player, string team_name)
{
    mixed t; 
    int qbit; 

    if (!pointerp(t = team_data[query_proper_team_name(team_name)]))
        return 0; 

    qbit = t[FIREBALL_TD_QUEST_BIT]; 
    return player->test_bit("Calia", FIREBALL_QUEST_GROUP, qbit); 
}


/* 
 * Function:     reward_team 
 * Description:  Give quest xp to players who defeated an npc team. 
 */ 
void 
reward_team(object *players, string npc_team_name, string result_desc, 
            int player_score, int npc_score, int training_match)
{
    int i, gxp, qxp, qbit, team_avg; 
    mixed t; 
    string tm; 

    if (!pointerp(t = team_data[npc_team_name = 
                          query_proper_team_name(npc_team_name)]))
        return; 


    tm = ctime(time()); 
    qbit = t[FIREBALL_TD_QUEST_BIT]; 
    qxp = t[FIREBALL_TD_QUEST_XP]; 

    players = secure_var(players); 

    /* Quest rewards only possible if the player team won 
       and it was not a training match. */ 
    if (!training_match && (player_score > npc_score)) 
    { 
        log_file("fireball", result_desc); 

        for (i = 0; i < sizeof(players); i++) 
        { 
            if (interactive(players[i]) && 
                !players[i]->test_bit("Calia", FIREBALL_QUEST_GROUP, 
                                      qbit)) 
            {
#ifdef GIVE_QUEST_REWARDS
                players[i]->add_exp_quest(qxp); 
                players[i]->set_bit(FIREBALL_QUEST_GROUP, qbit); 
                tell_object(players[i], "You feel more experienced.\n"); 
                players[i]->command("$save"); 
                log_file("fireball", tm + ": " + 
                         players[i]->query_real_name() + 
                         " awarded " + qxp + ".\n"); 
                players[i] = 0; 
#else
               tell_object(players[i], "You would have gained quest " + 
                           "experience now but fireball quest rewards " + 
                           "are disabled.\n"); 
#endif
            } 
        } 
    } 

    players = filter(players, objectp); 

    /* Award general experience to anyone who wasn't given 
       quest xp */ 
    if (sizeof(players)) 
    { 
#ifdef GIVE_GENERAL_REWARDS
        if (player_score > npc_score) 
            gxp = qxp * 3; 
        else 
            gxp = (qxp * 5) / 2;
 
        /* e.g. for the all scums who give 10000 quest xp, 
         * start with 30000 for beating them or 25000 for 
         * drawing/losing (continued below..) 
         */ 

        if (player_score != npc_score) 
            gxp = gxp + ((player_score - npc_score) * (qxp / 2)); 

        /* e.g. beating the all scums 3 - 0 gives a bonus of 
         * 15000 xp, with a result of 45000 xp. Losing 2 - 1 
         * removes 5000 xp, with a result of 25000 xp. 
         * (continued below..) 
         */ 

        gxp = max(gxp, qxp / 8); 

        /* 
         * e.g. 1250 basic minimum for playing the all scums, 
         * it takes some effort to assemble a team of similar 
         * statted players, even if it's not a good one. 
         */ 

        team_avg = query_team_average_stat(npc_team_name); 

        for (i = 0; i < sizeof(players); i++) 
        { 
            if (interactive(players[i]))
            {
                gxp = (team_avg * gxp) / players[i]->query_average_stat();
                /* Just took into account relative average stat. */ 
 
                players[i]->add_exp_general(gxp = min(gxp, qxp * 8)); 
                /* cap xp at 8 times the quest xp, e.g. 80000 against
                 * the all scums. 
                 */

                tell_object(players[i], "You gain some general experience.\n"); 
                log_file("fireball_general", tm + ": " + 
                         players[i]->query_real_name() + 
                         " awarded " + gxp + ".\n"); 
            } 
        } 
#else
        for (i = 0; i < sizeof(players); i++) 
        { 
            if (interactive(players[i]))
            {
                tell_object(players[i], "You would have gained general " + 
                           "experience now but fireball general rewards " + 
                           "are disabled.\n"); 
           } 
       } 
#endif
    } 
} 


/* 
 * Function:     is_fireball_npc
 * Description:  Returns 1 if the named npc plays in one of 
 *               the fireball league teams.
 */ 
int
is_fireball_npc(string name) 
{
    return pointerp(player_data[lower_case(name)]); 
}


/* 
 * Function:    make_team_member
 * Description: Make an npc of given name in a given team, 
 *              using the team data stored in this file, and 
 *              return the cloned object. 
 */ 
object
make_team_member(string nm, string team_name)
{
    object o; 
    int v;
    mixed info; 

    if (objectp(o = present(nm = lower_case(nm), this_object()))) {
        o->set_hp(o->query_max_hp()); 
        return o; 
    } 

    if (!(info = player_data[nm])) 
        return 0; 

    seteuid(getuid()); 

    o = clone_object(FIREBALL_MONSTER);  
    o->set_name(nm); 
    o->set_gender(info[FIREBALL_P_GENDER]); 
    o->set_race_name(info[FIREBALL_P_RACE]); 
    o->default_config_npc(info[FIREBALL_P_STAT]); 
    o->add_prop(CONT_I_HEIGHT, info[FIREBALL_P_HEIGHT]); 
    v = info[FIREBALL_P_WEIGHT]; 
    o->add_prop(CONT_I_WEIGHT, v*1000); 
    o->add_prop(CONT_I_MAX_WEIGHT, v*2000); 
    o->add_prop(CONT_I_VOLUME, v*1000); 
    o->add_prop(CONT_I_MAX_VOLUME, v*2000); 
    o->set_adj(info[FIREBALL_P_ADJ]); 
    o->set_long(capitalize(LANG_ADDART(implode(info[FIREBALL_P_ADJ], " "))) + 
        " " + o->query_gender_string() + 
        " " + info[FIREBALL_P_RACE] + ". " + info[FIREBALL_P_COMMENT] + "\n");  
    o->set_fireball_skill(info[FIREBALL_P_SKILL]); 
    o->set_fireball_team(team_name);  
    o->set_alignment(info[FIREBALL_P_ALIGN]); 
    o->add_prop(FIREBALL_LIVE_S_TEAM_POS, info[FIREBALL_P_POS]); 

    return o;
}


/* 
 * Function:    make_team
 * Description: Make a team of npcs given the team name.  
 */ 
object *
make_team(string team_name)
{
    mixed t;

    team_name = query_proper_team_name(team_name); 
    if (!(t = team_data[team_name])) 
        return 0;
    return map(t[FIREBALL_TD_TEAM], &make_team_member(,team_name)); 
}
