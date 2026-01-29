
/*  
   The Cadets of Gelan training room 

   Coded by Maniac@Genesis, March 1997

   Copyright (c) Miguel Leith 1997, 1998, 1999

   Last revised 12/2/2000, Maniac
*/

#include <state_desc.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <composite.h>
#include <std.h>
#include <files.h>
#include <time.h>
#include "/d/Genesis/login/login.h"

#include "/d/Calia/gelan/gelan.h"
#include "cadet.h"

#undef DEBUG_TRAINROOM

#pragma save_binary
#define CADET_I_FORGIVEN "_cadet_i_forgiven" 
#define GC_KEEP_FILE_TIME 2160000 /* 25 days, temporary measure, norm 40 */ 

inherit "/std/room"; 
inherit "/lib/skill_raise";

void unregister_graduate(mixed graduate);
void unregister_cadet(mixed cadet); 
varargs private void update_exemplary_and_unworthy(string name); 
int is_qualified_opiner(object player); 
int is_unworthy(string name); 
int is_exemplary(string name); 

mapping worth = ([ ]); 
string *opiners = ({ }); 
string *allowed_back = ({ });
string *graduate_restore = ({ });  
mapping assaulted = ([ ]);
int check_letter = 'a'; 

static int exemplary_vote_target, unworthy_vote_target; 
static string *unworthy; 
static string *exemplary; 

static mapping sk = ([ SS_WEP_SWORD : "sword", 
                       SS_WEP_AXE : "axe", 
                       SS_WEP_KNIFE : "knife", 
                       SS_UNARM_COMBAT : "unarmed", 
                       SS_WEP_POLEARM : "polearm", 
                       SS_WEP_CLUB : "club" ]); 

static mapping player_info = ([ ]); 

static mapping attribute_map = 
    ([ 
        "gamelevel" : SD_AV_TITLES, 
        "race" : ({ }), 
        "guildlevel" : map(GC_LEVEL_TITLE_ARR, lower_case), 
        "weapon" : ({ }), 
        "gender" : ({ }), 
        "adj1" : ({ }), 
        "adj2" : ({ })
    ]); 


static object guildmaster;

static mapping gc_name_selected_map = GC_NAME_SELECTED_MAP; 

#define WORTH_ARR ({ "neutral", "negative", "positive" })
#define MAX_WORTH_NAMES 15
#define MIN_OPINIONS 15

void
set_up_skills()
{
    string me, ot;

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }), 0, 0, 50 );

    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }), 0, 0, 50 );

    me = "use a polearm"; ot = me;
    sk_add_train(SS_WEP_POLEARM,({ me, ot }), 0, 0, 50 );

    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,({ me, ot }), 0, 0, 50 );

    me = "use an axe"; ot = me;
    sk_add_train(SS_WEP_AXE,({ me, ot }), 0, 0, 50 );

    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,({ me, ot }), 0, 0, 50 );

    me = "fight with both hands"; ot = me; 
    sk_add_train(SS_2H_COMBAT,  ({ me, ot }), 0, 0, 37 );

    me = "fight in the dark"; ot = me;
    sk_add_train(SS_BLIND_COMBAT,  ({ me, ot }), 0, 0, 50 );

    me = "parry"; ot = me;
    sk_add_train(SS_PARRY,      ({ me, ot }), 0, 0, 37 );

    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,    ({ me, ot }), 0, 0, 50 );

    me = "remember what continent it is"; ot = me;
    sk_add_train(SS_LOC_SENSE,    ({ me, ot }), 0, 0, 30 );

    me = "sneak"; ot = me;
    sk_add_train(SS_SNEAK,    ({ me, ot }), 0, 0, 20 );

    me = "hide"; ot = me;
    sk_add_train(SS_HIDE,    ({ me, ot }), 0, 0, 20 );
}


/* 
 * Bring guildmaster back in if he's missing, remove the records 
 * of cadets or graduates who no longer exist. 
 */
void
reset_room()
{
     int i, c, t; 
     string dir, *g, *file_list, l; 

     if (!objectp(guildmaster)) { 
         guildmaster = clone_object(GC_GUILDMASTER); 
         guildmaster->arm_me(); 
         guildmaster->move_living("into the training room", this_object()); 
     } 

     restore_object(GC_SAVE); 

     l = strchar(check_letter); 
     t = time(); 

     dir = (GC_GRADUATE_PICTURE_DIR + l + "/"); 
     file_list = get_dir(dir);

     for (i = 0; i < sizeof(file_list); i++) {
         if (((t - file_time(dir + file_list[i])) > GC_KEEP_FILE_TIME) ||
             !SECURITY->exist_player(file_list[i]))
             unregister_graduate(file_list[i]); 
     }

     dir = (GC_CADET_PICTURE_DIR + l + "/"); 
     file_list = get_dir(dir);

     for (i = 0; i < sizeof(file_list); i++) {
         if (((t - file_time(dir + file_list[i])) > GC_KEEP_FILE_TIME) ||
             !SECURITY->exist_player(file_list[i])) {
             unregister_cadet(file_list[i]); 
             assaulted = m_delete(assaulted, file_list[i]); 
         } 
     }

     if (check_letter == 'z')
         check_letter = 'a'; 
     else
         check_letter++; 

     update_exemplary_and_unworthy();
     save_object(GC_SAVE); 
}


/* 
 *  Function:    recalculate_worth
 *  Description: Recalculate the worth mapping for guild members using the
 *               opinions expressed in dedicated cadets' files. 
 */ 
void
recalculate_worth() {
    int i, j; 
    mapping worthiness; 
    string *ix; 

    worth = ([ ]); 

    for (i = 0; i < sizeof(opiners); i++) {
        if (mappingp(player_info = restore_map(GC_CADET_INFO_SAVE(opiners[i]))) 
            && mappingp(worthiness = player_info["worthiness"])) { 
            ix = m_indexes(worthiness); 
            for (j = 0; j < sizeof(ix); j++) { 
                if (WORTH_ARR[worthiness[ix[j]]] == "positive")
                    worth[ix[j]]++; 
                else 
                    worth[ix[j]]--;
                if (worth[ix[j]] == 0) 
                    worth = m_delete(worth, ix[j]); 
            } 
        }
    } 
    save_object(GC_SAVE); 
}


void
restore_ring(object ob) {
    clone_object(GC_DIR + "graduation_ring")->move(ob);  
}


void
enter_inv(object ob, object from)
{
    int i;

    ::enter_inv(ob, from); 

    if (interactive(ob)) { 
        if ((i = member_array(ob->query_real_name(), allowed_back)) > -1) {
            ob->clear_bit(GC_GROUP, GC_BIT);   
            allowed_back = exclude_array(allowed_back, i, i);  
            save_object(GC_SAVE); 
        } 
        if ((i = member_array(ob->query_real_name(), graduate_restore)) > -1) { 
            set_alarm(0.0, 0.0, &restore_ring(ob));  
            tell_object(ob, "Your graduation ring is restored (an " + 
                        "automatic suspension system now replaces " +  
                        "instant loss). See \"help cadet graduate\" and " +
                        "\"help cadet reputation\".\n"); 
            graduate_restore = exclude_array(graduate_restore, i, i); 
            save_object(GC_SAVE); 
        } 
    } 
}


/*
 * Function:    cadet_check
 * Description: Returns 1 if this_player() is a cadet or graduate.
 *              That means the player will be allowed into private
 *              cadet rooms. 
 */
int
cadet_check()
{
    object tp = this_player(); 

    if (IS_GELAN_CADET(tp) || tp->query_wiz_level()) 
        return 0;

    if (IS_GRADUATE(tp)) {
         if (is_unworthy(tp->query_real_name())) { 
             tell_object(tp, "Your reputation is not so good, " +
                         "so you are barred from entering.\n"); 
             return 1; 
         } 
         return 0; 
    } 

    tell_object(tp, "Only cadets and graduates may go in there.\n");  
    return 1;
}


/*
 * Function:    is_registered_graduate
 * Arguments:   n
 * Description: Tests whether the player n is registered 
 *              as a graduate, return 1 if s/he is, 0 otherwise.  
 */
int
is_registered_graduate(string n)
{ 
    return (file_size(GC_GRADUATE_PICTURE(n)) != -1); 
}


/*
 * Function:    is_registered_cadet
 * Arguments:   n
 * Description: Tests whether the player n is registered 
 *              as a cadet, return 1 if s/he is, 0 otherwise.  
 */
int
is_registered_cadet(string n)
{ 
    return (file_size(GC_CADET_PICTURE(n)) != -1); 
}


/* Returns a portrait of a player as a string */ 
string
portrait(object p)
{
    string s, r;  

    r = capitalize(p->query_pronoun()) + " is " + 
        LANG_ADDART(p->query_nonmet_name()) + ", " +
        p->query_exp_title() + ".\n"; 

    if (objectp(guildmaster)) { 
        r += p->show_sublocs(guildmaster, ({"hairstyle", "eyes"}));  
        if ((member_array(p->query_race_name(), RACES) > -1) ||  
            !stringp(s = p->show_subloc_size(p, guildmaster))) 
            s = CMD_LIVE_STATE->show_subloc_size(p, guildmaster); 
        r += capitalize(p->query_pronoun()) + " is" + s;  
    } 

    return r; 
}


/* Returns the category of main weapon favoured by a player */ 
string
main_weapon(object p)
{
    int tmp, i, *s, best_sk, l;

    s = m_indexes(sk); 
    
    best_sk = s[0];
    l = p->query_skill(s[0]);  
    for (i = 1; i < sizeof(s); i++) {
        if ((tmp = p->query_base_skill(s[i])) > l) {
            best_sk = s[i]; 
            l = tmp; 
        } 
    } 

    return sk[best_sk]; 
}



/* 
 * Function:      get_attribute_dir
 * Description:   Returns the directory for an attribute
 *                for either graduates or cadets
 */ 
string
get_attribute_dir(int graduate, string attribute)
{
    switch (attribute) {
        case "gamelevel" :
             if (graduate) 
                 return GC_GRADUATE_GAMELEV_DIR;
             else
                 return GC_CADET_GAMELEV_DIR;  
        case "guildlevel" :
             if (graduate) 
                 return 0;
             else
                 return GC_CADET_GUILDLEV_DIR;  
             break;
        case "race" :
             if (graduate) 
                 return GC_GRADUATE_RACE_DIR;  
             else 
                 return GC_CADET_RACE_DIR; 
        case "gender": 
             if (graduate)
                 return GC_GRADUATE_GENDER_DIR; 
             else
                 return GC_CADET_GENDER_DIR; 
        case "adj1" : 
             if (graduate) 
                 return GC_GRADUATE_ADJ1_DIR; 
             else
                 return GC_CADET_ADJ1_DIR; 
        case "adj2" : 
             if (graduate) 
                 return GC_GRADUATE_ADJ2_DIR; 
             else
                 return GC_CADET_ADJ2_DIR; 
        case "weapon" :
             if (graduate) 
                 return GC_GRADUATE_WEAPON_DIR; 
             else
                 return GC_CADET_WEAPON_DIR; 
    } 
    return 0;
}


/* 
 * Determines the path of a file for an attribute of the 
 * specified player and does an operation on it. 
 * A op_type of 1 creates an attribute file, 2 deletes 
 * the file. 
 */ 
private string
attribute_file_op(mixed player, string attr, int graduate, int op_type)
{
    string tmp, alt, dir, rn; 

    if (stringp(player)) { 
        rn = capitalize(lower_case(player)); 
    } 
    else if (objectp(player)) { 
        rn = capitalize(player->query_real_name()); 
    } 
    else
        return 0;

    alt = 0; 
    switch (attr) {
        case "gamelevel" : 
             if (objectp(player))  {
                 alt = implode(explode(tmp = 
                                   player->query_exp_title(), " "), "_");
                 player_info["gamelevel"] = tmp;  
             } 
             else if (stringp(tmp = player_info["gamelevel"])) 
                 alt = implode(explode(tmp, " "), "_"); 
             if (!alt)
                 return 0;  
             if (graduate) 
                 dir = GC_GRADUATE_GAMELEV_DIR;
             else
                 dir = GC_CADET_GAMELEV_DIR;  
             break;
        case "race" : 
             if (objectp(player)) {  
                 alt = player->query_race();
                 player_info["race"] = alt;  
             } 
             else
                 alt = player_info["race"]; 
             if (!alt)
                 return 0; 
             if (graduate) 
                 dir = GC_GRADUATE_RACE_DIR;  
             else 
                 dir = GC_CADET_RACE_DIR; 
             break;
        case "gender" : 
             if (objectp(player)) {
                 alt = player->query_gender_string();
                 player_info["gender"] = alt;
             }
             else
                 alt = player_info["gender"];
             if (!alt)
                 return 0;
             if (graduate)
                 dir = GC_GRADUATE_GENDER_DIR;
             else
                 dir = GC_CADET_GENDER_DIR;
             break;
        case "adj1" : 
             if (objectp(player)) {
                 if (sizeof(player->query_adj(1)) > 0) { 
                     alt = player->query_adj(1)[0];
                     player_info["adj1"] = alt;
                 } 
             }
             else
                 alt = player_info["adj1"];
             if (!alt)
                 return 0;
             if (graduate)
                 dir = GC_GRADUATE_ADJ1_DIR;
             else
                 dir = GC_CADET_ADJ1_DIR;
             break;
        case "adj2" : 
             if (objectp(player)) {
                 if (sizeof(player->query_adj(1)) > 1) { 
                     alt = player->query_adj(1)[1];
                     player_info["adj2"] = alt;
                 } 
             }
             else
                 alt = player_info["adj2"];
             if (!alt)
                 return 0;
             if (graduate)
                 dir = GC_GRADUATE_ADJ2_DIR;
             else
                 dir = GC_CADET_ADJ2_DIR;
             break;
        case "weapon" :
             if (objectp(player)) { 
                 alt = main_weapon(player); 
                 player_info["weapon"] = alt;  
             } 
             else
                 alt = player_info["weapon"]; 
             if (!alt)
                 return 0;
             if (graduate) 
                 dir = GC_GRADUATE_WEAPON_DIR; 
             else
                 dir = GC_CADET_WEAPON_DIR; 
             break; 
        case "guildlevel" :
             if (objectp(player)) { 
                 alt = lower_case(player->gc_level_title());
                 player_info["guildlevel"] = alt; 
             } 
             else if (stringp(tmp = player_info["guildlevel"])) 
                 alt = lower_case(tmp);
             if (!alt)
                 return 0;   
             if (graduate) 
                 return 0;
             else
                 dir = GC_CADET_GUILDLEV_DIR;  
             break;
    }

    dir = dir + alt; 
    if ((file_size(dir) != -2) && ((op_type == 2) ||  
        (op_type == 1 && !mkdir(dir))))  
        return 0;

    tmp = dir + "/" + rn;  
    if (op_type == 1 && file_size(tmp) == -1) {  
        write_file(tmp, "1");  
    } 
    else if (op_type == 2) {
        rm(tmp);  
        rmdir(dir);   // will fail if the directory contains files 
    } 

    return tmp; 
}


/*
 * Function:    register_graduate
 * Description: Register a graduate in the records.
 */
void
register_graduate(object graduate)
{
    string n, f2; 

    if (!objectp(graduate))
        return; 

    n = graduate->query_real_name(); 
#ifndef DEBUG_TRAINROOM
    if (wildmatch("*jr", n) || graduate->query_wiz_level())
        return; 
#endif

    if (this_interactive()->query_wiz_level()) 
        log_file("cadet", n + " registered by " + 
                          this_interactive()->query_real_name() + 
                          ".\n");  

    /* Delete old attributes */  
    player_info = restore_map(GC_GRADUATE_INFO_SAVE(n));  
    if (mappingp(player_info) && m_sizeof(player_info)) {
        attribute_file_op(n, "gamelevel", 1, 2);  
        attribute_file_op(n, "race", 1, 2); 
        attribute_file_op(n, "gender", 1, 2); 
        attribute_file_op(n, "adj1", 1, 2); 
        attribute_file_op(n, "adj2", 1, 2); 
        attribute_file_op(n, "weapon", 1, 2);  
    } 

    /* Register new attributes */ 
    attribute_file_op(graduate, "gamelevel", 1, 1); 
    attribute_file_op(graduate, "race", 1, 1); 
    attribute_file_op(graduate, "gender", 1, 1); 
    attribute_file_op(graduate, "adj1", 1, 1); 
    attribute_file_op(graduate, "adj2", 1, 1); 
    attribute_file_op(graduate, "weapon", 1, 1); 

    save_map(player_info, GC_GRADUATE_INFO_SAVE(n)); 

    f2 = GC_GRADUATE_PICTURE(n); 
    if (file_size(f2) != -1) 
        rm(f2); 
    write_file(f2, portrait(graduate)); 

    if (is_exemplary(n)) 
        graduate->gc_set_exemplary(); 
    else if (is_unworthy(n)) 
        graduate->gc_set_unworthy(); 
} 


/*
 * Function:    unregister_graduate
 * Description: Unregister a graduate from the records.
 */
void
unregister_graduate(mixed graduate)
{
    string n, f; 

    if (objectp(graduate))
        n = graduate->query_real_name(); 
    else if (stringp(graduate)) 
        n = graduate; 
    else
        return;

    if (!is_registered_graduate(n)) 
        return;

    if (this_interactive()->query_wiz_level()) 
        log_file("cadet", n + " unregistered by " + 
                          this_interactive()->query_real_name() + 
                          ".\n"); 

    player_info = restore_map(GC_GRADUATE_INFO_SAVE(n));

    attribute_file_op(n, "race", 1, 2); 
    attribute_file_op(n, "gender", 1, 2); 
    attribute_file_op(n, "adj1", 1, 2); 
    attribute_file_op(n, "adj2", 1, 2); 
    attribute_file_op(n, "gamelevel", 1, 2); 
    attribute_file_op(n, "weapon", 1, 2); 
    rm(GC_GRADUATE_INFO_SAVE(n) + ".o"); 
    rm(GC_GRADUATE_PICTURE(n)); 

    player_info = ([ ]); 
}


/*
 * Function:    remove_opiner
 * Description: removes all opinion-related information of a
 *              cadet. If the value of "save" is 1, the state
 *              of the trainroom is saved afterwards. 
 */ 
void
remove_opiner(mapping pinfo, string player_name, int save) 
{
    int i; 
    mapping worthiness; 
    string *ix; 

    if ((i = member_array(player_name, opiners)) == -1) 
        return; 

    opiners = exclude_array(opiners, i, i); 

    /* Remove former dedicated cadet's opinions. */ 
    if (mappingp(pinfo) &&  
        mappingp(worthiness = pinfo["worthiness"])) {
        ix = m_indexes(worthiness); 
        for (i = 0; i < sizeof(ix); i++) {
            if (WORTH_ARR[worthiness[ix[i]]] == "positive")
                worth[ix[i]] = worth[ix[i]] - 1; 
            else 
                worth[ix[i]] = worth[ix[i]] + 1;

            if (worth[ix[i]] == 0) 
                worth = m_delete(worth, ix[i]); 
        }
    }

    if (save) 
        save_object(GC_SAVE); 
}


/*
 * Function:    add_opiner
 * Description: Adds a cadet to the list of opiners. If the value of 
 *              "save" is 1, the state of the trainroom is saved 
 *              afterwards. 
 */ 
void
add_opiner(mapping pinfo, string player_name, int save) 
{
    int i; 
    mapping worthiness; 
    string *ix; 

    if (member_array(player_name, opiners) > -1)
        return; 

    opiners = opiners + ({ player_name }); 

    /* Add former dedicated cadet's opinions. */ 
    if (mappingp(pinfo) &&  
        mappingp(worthiness = pinfo["worthiness"])) {
        ix = m_indexes(worthiness); 
        for (i = 0; i < sizeof(ix); i++) {
            if (WORTH_ARR[worthiness[ix[i]]] == "positive")
                worth[ix[i]] = worth[ix[i]] + 1; 
            else 
                worth[ix[i]] = worth[ix[i]] - 1;

            if (worth[ix[i]] == 0) 
                worth = m_delete(worth, ix[i]); 
        }
    }

    if (save) 
        save_object(GC_SAVE); 
}


/*
 * Function:    register_cadet
 * Description: Register a cadet in the records.
 */
void
register_cadet(object cadet)
{
    string n, f2; 

    if (!objectp(cadet))
        return; 

    n = cadet->query_real_name(); 

#ifndef DEBUG_TRAINROOM
    if (wildmatch("*jr", n) || cadet->query_wiz_level())
        return; 
#endif

    if (this_interactive()->query_wiz_level()) 
        log_file("cadet", n + " registered by " + 
                          this_interactive()->query_real_name() + ".\n"); 

    /* Delete old attributes */  
    player_info = restore_map(GC_CADET_INFO_SAVE(n));  
    if (mappingp(player_info) && m_sizeof(player_info)) {
        attribute_file_op(n, "gamelevel", 0, 2);  
        attribute_file_op(n, "race", 0, 2); 
        attribute_file_op(n, "gender", 0, 2); 
        attribute_file_op(n, "adj1", 0, 2); 
        attribute_file_op(n, "adj2", 0, 2); 
        attribute_file_op(n, "weapon", 0, 2);  
        attribute_file_op(n, "guildlevel", 0, 2); 
    } 

    /* Register new attributes */ 
    attribute_file_op(cadet, "gamelevel", 0, 1);  
    attribute_file_op(cadet, "race", 0, 1);  
    attribute_file_op(cadet, "gender", 0, 1); 
    attribute_file_op(cadet, "adj1", 0, 1); 
    attribute_file_op(cadet, "adj2", 0, 1); 
    attribute_file_op(cadet, "weapon", 0, 1);  
    attribute_file_op(cadet, "guildlevel", 0, 1); 

    save_map(player_info, GC_CADET_INFO_SAVE(n)); 

    f2 = GC_CADET_PICTURE(n); 
    if (file_size(f2) != -1)
        rm(f2); 
    write_file(f2, portrait(cadet)); 

    if (is_qualified_opiner(cadet)) 
        add_opiner(player_info, n, 1); 
    else 
        remove_opiner(player_info, n, 1); 

    if (is_exemplary(n) &&
        cadet->query_skill(SS_CADET_DONK_BAN) < time())
        cadet->gc_set_exemplary(); 
    else if (is_unworthy(n)) 
        cadet->gc_set_unworthy(); 
}


/*
 * Function:    unregister_cadet
 * Description: Unregister a cadet from the records.
 */
void
unregister_cadet(mixed cadet)
{
    string n, f; 

    if (objectp(cadet))
        n = cadet->query_real_name(); 
    else if (stringp(cadet))
        n = cadet; 
    else
        return;

    if (!is_registered_cadet(n)) 
        return;

    if (this_interactive()->query_wiz_level()) 
        log_file("cadet", n + " unregistered by " + 
                          this_interactive()->query_real_name() + 
                          ".\n"); 

    player_info = restore_map(GC_CADET_INFO_SAVE(n));

    attribute_file_op(n, "race", 0, 2); 
    attribute_file_op(n, "gender", 0, 2); 
    attribute_file_op(n, "adj1", 0, 2); 
    attribute_file_op(n, "adj2", 0, 2); 
    attribute_file_op(n, "gamelevel", 0, 2); 
    attribute_file_op(n, "weapon", 0, 2); 
    attribute_file_op(n, "guildlevel", 0, 2); 

    remove_opiner(player_info, n, 1); 

    rm(GC_CADET_INFO_SAVE(n) + ".o"); 
    rm(GC_CADET_PICTURE(n)); 

    player_info = ([ ]); 
}


int
first_non_space_point(string str)
{
    int i; 

    i = 0; 
    while (i < strlen(str) && str[i] == ' ')  
        i++; 

    return i; 
}


string
single_underlined(string str, string ul)
{
    int i, k, s; 
  
    s = strlen(str)-1; 
    k = first_non_space_point(str); 
    for (i = 0; i < s; i++)
        if (i < k) 
            str += " "; 
        else 
            str += ul; 
    return (str + "\n"); 
}


string
double_underlined(string str, string ul)
{
    int s, k, i; 
 
    s = strlen(str)-1; 
    k = first_non_space_point(str); 

    for (i = 0; i < s; i++)
        if (i < k) 
            str += " "; 
        else 
            str += ul; 

    str += "\n"; 

    for (i = 0; i < s; i++)
        if (i < k) 
            str += " "; 
        else 
            str += ul; 

    return (str + "\n"); 
}


string 
spaced_form(string str)
{
    return implode(explode(str, "_"), " ");  
}


/*  
 *  Function:      list_membership
 *  Description:   An action function allowing a player to see the 
 *                 membership of the guild or graduates sorted by a 
 *                 particular attribute, where the membership can be 
 *                 further restricted to cadets or graduates who have
 *                 a particular value of a different attribute. 
 */ 
int
list_membership(string str)
{
    int i, j, k, graduate; 
    string sort_attr, sort_dir, *file_list, *sort_value_list, 
           spec_attr, spec_value, spec_dir, *spec_file_list,
           *spec_value_list, expr, mem, msg, *tmp_list; 

    notify_fail("List what?\n"); 
    if (!stringp(str) || !strlen(str))
        return 0;

    if (str == "attributes") {
        write("Possible attributes: " + 
              COMPOSITE_WORDS(m_indexes(attribute_map)) + ".\n"); 
        return 1;
    }

    if (sscanf(str, "values of %s", expr) == 1) {
        expr = lower_case(expr); 

        if (!pointerp(attribute_map[expr])) {
            notify_fail("No such attribute.\n"); 
            return 0;
        } 

        msg = ("Currently the possible values for the attribute " + 
               expr + " are as follows.\n"); 

        if (stringp(spec_dir = get_attribute_dir(0, expr)))  
            tmp_list = get_dir(spec_dir); 
        else 
            tmp_list = ({ "No values" }); 

        msg += ("For cadets: " +
               COMPOSITE_WORDS(map(tmp_list, spaced_form)) + ".\n");  

        if (stringp(spec_dir = get_attribute_dir(1, expr)))  
            tmp_list = get_dir(spec_dir); 
        else 
            tmp_list = ({ "No values" }); 

        msg += ("For graduates: " +
               COMPOSITE_WORDS(map(tmp_list, spaced_form)) + ".\n");  

        this_player()->more(msg); 
        return 1; 
    }

    if (sscanf(str, "%s sorted by %s", expr, sort_attr) != 2) 
        return 0;

    if (!(graduate = (expr == "graduates")) && !(expr == "cadets")) { 
        if (sscanf(expr, "%s of %s", mem, expr) != 2) 
            return 0;

        if (!(graduate = (mem == "graduates")) && !(mem == "cadets"))  
            return 0;

        tmp_list = explode(expr, " ");  
        if (sizeof(tmp_list) < 2)
            return 0;

        spec_attr = lower_case(tmp_list[0]);  

        if (!stringp(spec_dir = get_attribute_dir(graduate, spec_attr))) {
            notify_fail("Unknown attribute: " + spec_attr + ".\n"); 
            return 0;
        } 

        if ((sort_attr == "adj1" && spec_attr != "adj2") ||
            (sort_attr == "adj2" && spec_attr != "adj1")) {
            notify_fail("The attributes adj1 and adj2 can only " +
                        "be used together, for searching non-mets " +
                        "(e.g. 'list cadets of adj1 philosophical " +
                        "sorted by adj2').\n"); 
            return 0; 
        } 

        if (!sizeof(spec_value_list = attribute_map[spec_attr]) &&
            !sizeof(spec_value_list = map(get_dir(spec_dir), 
                                                spaced_form))) {
                notify_fail("There are no values of that attribute " +
                            "for " + mem + ".\n"); 
                return 0;
        }     

        tmp_list = exclude_array(tmp_list, 0, 0); 
        spec_value = lower_case(implode(tmp_list,  " ")); 
        if (member_array(spec_value, spec_value_list) == -1) {
            notify_fail("Unknown attribute value: " + spec_value + ".\n"); 
            return 0;
        } 
        spec_file_list = get_dir(spec_dir + implode(tmp_list, "_") + "/");  
    } 
    else {
        if (sort_attr == "adj1" || sort_attr == "adj2") {
            notify_fail("The attributes adj1 and adj2 can only " +
                        "be used together, for searching non-mets (e.g. " +
                        "'list cadets of adj1 philosophical sorted by " +
                        "adj2').\n"); 
            return 0; 
        }
        mem = expr; 
    }

    if (!stringp(sort_dir = get_attribute_dir(graduate, sort_attr))) { 
        notify_fail("Unknown attribute: " + sort_attr + ".\n");  
        return 0;
    } 

    if (!sizeof(sort_value_list = attribute_map[sort_attr]) && 
        !sizeof(sort_value_list = map(get_dir(sort_dir), spaced_form))) {
        notify_fail("There are no values of that attribute " +
                    "for " + mem + ".\n"); 
        return 0; 
    }     

    msg = single_underlined(capitalize(mem) + 
             (stringp(spec_attr) ? " of " + capitalize(spec_attr) + " " + 
             capitalize(spec_value) : "") + " Sorted by " + 
             capitalize(sort_attr) + "\n", "="); 

    for (i = 0; i < sizeof(sort_value_list); i++) {
        if (stringp(spec_value) && !sizeof(spec_file_list))   
            break;
        file_list = get_dir(sort_dir + 
                            implode(explode(sort_value_list[i], " "), 
                                    "_") + "/"); 
        if (sizeof(file_list)) {
            if (sizeof(spec_file_list)) { 
                tmp_list = ({ }); 
                for (j = 0; j < sizeof(file_list); j++)  
                    if (member_array(file_list[j], spec_file_list) > -1) 
                        tmp_list += ({ file_list[j] }); 

                spec_file_list = spec_file_list - (file_list = tmp_list); 
            } 

            if (sizeof(file_list)) { 
                msg += single_underlined(capitalize(sort_value_list[i])+"\n", 
                                                                         "-");
                msg += (sprintf("%-#80s\n", implode(file_list, "\n")) + "\n"); 
            } 
        } 
    } 

    this_player()->more(msg); 
    return 1;
}


void
create_room()
{ 
    set_short(GC_GUILD_NAME);
    set_long("This is the training room of the " + GC_GUILD_NAME + ". " +
      "Youngsters who want to prepare for life as a warrior " +
      "often spend time as a cadet here under the watchful eye " +
      "of " + GC_GM_NAME + ", the guild's founder. In return for " +
      "the benefits granted, you will only have to invest a fairly " +
      "low amount of the experience that you obtain while you are " +
      "guild member. To find out more about the guild, read the " +
      "topics in <help cadet>. To join, just <csign on>. Cadets " +
      "can <learn> and <improve> various skills here, and can also " +
      "<choose> a primary and secondary offensive skill. Cadet titles " +
      "may be listed here using the <ctitles> command.\n");  

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_WIZINFO, "Wizards with write access in Calia " +  
                            "may use the <cpermit> command here " +
                            "to allow a cadet who left the guild " + 
                            "back in if they lost guild membership " +
                            "due to a bug.\n"); 

    create_skill_raise();
    set_up_skills();

    add_exit(GC_STARTROOM, "south", "@@cadet_check");  
    add_exit(GELAN_SCHOOL_CONNECT, "north"); 

    reset_room();
}




/* 
 * Kick out a cadet from the guild. 
 * The messages should be written elsewhere. 
 */ 
varargs int
kick_out_cadet(object player, int misconduct = 0)
{
    string n = player->query_real_name(), graduate, msg, *ix; 
    object shoes, board;
    int i; 

    if ((player->gc_level_title() == GC_LEVEL_GRADUATE) && !misconduct) 
        graduate = " (graduated)"; 
    else 
        graduate = ""; 

    if (!player->remove_guild_lay()) {  
        tell_object(player, 
                 "Ack, could not remove you from the guild.\n");
        log_file("cadet", "Could not kick out " + 
                          n + " from the guild.\n"); 
        return 0;
    } 

    player->clear_guild_stat(SS_LAYMAN); 
    player->remove_prop(CADET_I_CONFIRM_LEAVE); 
    player->remove_skill(SS_CADET_DONK_BAN); 
    player->remove_skill(SS_CADET_DROPROOM_POINTS); 
    player->remove_skill(GC_SKILL_PRIMARY_WEAPON); 
    player->remove_skill(GC_SKILL_SECONDARY_WEAPON); 
    player->setup_skill_decay(); 
    if (objectp(shoes = present(GC_SHOES_ID, player))) 
        shoes->remove_object(); 
    unregister_cadet(player); 

    if (strlen(graduate))  { 
        seteuid(getuid()); 
        clone_object(GC_DIR + "graduation_ring")->move(player); 
        board = present("board", GC_BOARDROOM->get_this_object());
        register_graduate(player); 
        if (objectp(board)) 
            board->create_note("Graduation News", 
                   "Xorfin", capitalize(n) + 
                   " graduated today!\n\nXorfin\n"); 
    } 
    else {
        if (environment(player)->gc_query_private_room())  
            player->move_living("to the cadet training room", this_object());  

        if (player->query_default_start_location() == GC_STARTROOM) 
            player->set_default_start_location(player->query_def_start()); 
    } 

    log_file("cadet", ctime(time()) + " " + 
             n + " left" + graduate + ".\n"); 
    return 1;
}


/*
 * Kick a cadet out if he's too big, otherwise register the
 * cadet and check if s/he is a qualified opiner. 
 */ 
void
too_big_check(object player)
{
     if (!objectp(player) || 
         !IS_GELAN_CADET(player) ||
         player->query_wiz_level()) 
         return;

     if (GC_AVG_STAT_EXPEL(player)) {  
         if (!kick_out_cadet(player)) 
             return;

         tell_object(player, 
             "You have now outgrown the cadets. " +
             "The guild thanks you for your efforts and wishes you " +
             "every success in your future occupation.\n"); 

         log_file("cadet", player->query_real_name() + 
             " discharged for outgrowing the cadets.\n"); 
         return;
    } 

    register_cadet(player); 
}


/* 
   This is called from the shadow on initialisation, we break it up 
   with an alarm to ensure everything works ok when it removes the 
   guild member. 
 */ 
void
kick_out_if_too_big(object player)
{
     set_alarm(1.0, 0.0, &too_big_check(player)); 
}


void
warn_for_misconduct(object player, string victim_name, string reason)
{
    int t = time(); 
    int current_ban = player->query_skill(SS_CADET_DONK_BAN);
    int new_ban; 
    string n = player->query_real_name(); 

    if (current_ban < t)
        current_ban = t; 

    new_ban = current_ban + GC_DONK_BAN_DURATION; 

    player->set_skill(SS_CADET_DONK_BAN, new_ban); 

    if (!mappingp(player_info = restore_map(GC_CADET_INFO_SAVE(n)))) 
        player_info = ([ ]); 
 
    player_info["warn_start_" + victim_name] = current_ban; 
    player_info["warn_end_" + victim_name] = new_ban; 
    save_map(player_info, GC_CADET_INFO_SAVE(n)); 

    tell_object(player, 
                  "\nFor misconduct you have been banned from " +
                  "donking until " + ctime(new_ban) + ".\n\n"); 

    log_file("cadet", ctime(t) + ": " + player->query_real_name() + 
                      " gets donk banned until " + ctime(new_ban) + 
                      " for " + reason + ".\n"); 
}


/* 
 * Kick a player out for misconduct, this may be called 
 * from the cadet shadow or from a Gelan npc if the
 * cadet killed a fellow cadet or citizen/guard of Gelan.  
 */
void
kick_out_for_misconduct(object player, string victim_name, string reason)
{
    object board; 

    if (!objectp(player) || !IS_GELAN_CADET(player)) 
        return;

    if (!kick_out_cadet(player, 1)) 
        return;

    tell_object(player, 
         "You are guilty of misconduct in the cadets and have " +
         "therefore been expelled.\n"); 

    if (stringp(victim_name) && objectp(find_player(victim_name))) { 
        assaulted[player->query_real_name()] = lower_case(victim_name);  
        save_object(GC_SAVE); 
    }

    log_file("cadet", player->query_real_name() + 
             " kicked out for " + reason + ".\n"); 

    seteuid(getuid()); 
    if (objectp(board = present("board", GC_BOARDROOM->get_this_object()))) 
        board->create_note("Expulsion News", 
               "Xorfin", capitalize(player->query_real_name()) + 
               " has been expelled for " + reason + ".\n\nXorfin\n"); 
}


/* See is_exemplary, below */ 
private int
is_exemplary_p(string cadet_name)
{
    return (worth[cadet_name] >= exemplary_vote_target); 
}


/* See is_unworthy, below */ 
private int
is_unworthy_p(string cadet_name)
{
    return (-worth[cadet_name] >= unworthy_vote_target); 
}


/*
 * Function:     update_exemplary_and_unworthy
 * Description:  updates the lists of those who are considered unworthy
 *               and exemplary by the cadet community
 */
private varargs void
update_exemplary_and_unworthy(string name = 0)
{
    string *ix = m_indexes(worth); 
    int i; 

    exemplary_vote_target = unworthy_vote_target = (2 * sizeof(opiners)) / 7; 

    if (stringp(name)) {
        if (is_exemplary_p(name)) {
            if ((i = member_array(name, unworthy)) > -1) {
                unworthy = exclude_array(unworthy, i, i); 
                exemplary = exemplary + ({ name }); 
                find_player(name)->gc_set_exemplary(); 
            } 
            else if (member_array(name, exemplary) == -1) {
                exemplary = exemplary + ({ name }); 
                find_player(name)->gc_set_exemplary(); 
            }
         }
        else if (is_unworthy_p(name)) {
            if ((i = member_array(name, exemplary)) > -1) {
                exemplary = exclude_array(exemplary, i, i);
                unworthy = unworthy + ({ name }); 
                find_player(name)->gc_set_unworthy(); 
            }  
            else if (member_array(name, unworthy) == -1) {
                unworthy = unworthy + ({ name });
                find_player(name)->gc_set_unworthy(); 
            }
        } 
    } 
    else {
        exemplary = ({ }); 
        unworthy = ({ }); 
        for (i = 0; i < sizeof(ix); i++) {
            if (is_exemplary_p(ix[i]))
                exemplary = exemplary + ({ ix[i] }); 
            else if (is_unworthy_p(ix[i]))
                unworthy = unworthy + ({ ix[i] });
        }  
    }
}


/*
 * Function:      is_exemplary
 * Description:   Returns 1 if the cadet of the given name
 *                is considered exemplary according to opinions
 *                expressed by other cadets. 
 */ 
int
is_exemplary(string cadet_name)
{
    return (sizeof(opiners) >= MIN_OPINIONS) && 
           (member_array(cadet_name, exemplary) + 1); 
}


/* 
 * Function:      is_unworthy
 * Description:   Returns 1 if the cadet of the given name
 *                is considered unworthy according to opinions
 *                expressed by other cadets. 
 */ 
int
is_unworthy(string cadet_name)
{
    return (sizeof(opiners) >= MIN_OPINIONS) && 
           (member_array(cadet_name, unworthy) + 1); 
}


/* 
 * Function:      is_qualified_opiner
 * Description:   Returns 1 if the specified cadet is qualified 
 *                to register opinions about other guild members. 
 */ 
int
is_qualified_opiner(object player)
{
    return player->gc_is_dedicated_cadet(); 
}


/*
 * Function:     register_opinion
 * Description:  A cadet with a reasonable degree of experience in 
 *               the guild may use this action to register his/her 
 *               opinions of how worthy to be associated with the 
 *               cadet guild various people are. If someone is 
 *               considered overall unworthy or exemplary by the
 *               cadet community, his/her reputation will be publicly 
 *               proclaimed. In the former case, this means that 
 *               they will be freely huntable and killable by all 
 *               guild members. 
 */ 
int
register_opinion(string str)
{
    object player = this_player(); 
    string n = player->query_real_name(), *ix, name, val, oldval;
    mapping worthiness;  
    int i; 

    if (!is_qualified_opiner(player)) {
        notify_fail("You are not a dedicated enough cadet to " +
                    "register opinions about reputation here.\n"); 
        return 0; 
    } 

    if (!mappingp(player_info = restore_map(GC_CADET_INFO_SAVE(n)))) {
        player_info = ([ ]);
        worthiness = ([ ]); 
    }
    else if (!mappingp(worthiness = player_info["worthiness"])) 
        worthiness = ([ ]); 

    add_opiner(player_info, n, 1); 

    if (!stringp(str) || !strlen(str)) {
         write("Your opinions about reputation with respect to the Cadets " +
               "of Gelan are as follows:\n"); 
         if (!sizeof(ix = m_indexes(worthiness))) {
             write("No comment whatsoever!\n"); 
             return 1; 
         } 
         str = ""; 
         for (i = 0; i < sizeof(ix); i++) 
             str += (capitalize(ix[i]) + ": " + 
                     WORTH_ARR[worthiness[ix[i]]] + ".\n");
         write(str); 
         return 1; 
    } 

    if (sscanf(str, "%s is %s", name, val) != 2 ||
        (i = member_array(val, WORTH_ARR)) == -1) {
        notify_fail("Syntax: copinion <name> is " +
                    "<negative|neutral|positive>.\n"); 
        return 0; 
    } 

    if ((name = lower_case(name)) == n) {
        switch (val) {
            case "neutral" : 
                notify_fail("That's a superlative example of indecision!\n"); 
                return 0; 
                break; 
            case "negative" : 
                notify_fail("*Comfort*, don't be so hard on yourself.\n"); 
                return 0; 
                break; 
            default : 
                notify_fail("Not entirely unexpected that one!\n");  
                return 0; 
                break; 
        } 
    } 

    if (m_sizeof(worthiness)) 
        oldval = WORTH_ARR[worthiness[name]];
    else 
        oldval = "neutral"; 

    if (oldval == val) {
        notify_fail("That was the same opinion as before!\n"); 
        return 0; 
    } 

    if (!SECURITY->exist_player(name) ||
        SECURITY->query_wiz_rank(name)) {
        notify_fail("No such player!\n"); 
        return 0; 
    } 

    if (!worth[name] && !worthiness[name] && !is_registered_cadet(name)) {
        notify_fail("There is no cadet of that name in the " +
                    "records at the moment.\n"); 
        return 0; 
    } 

    if (val == "neutral") {
        worthiness = m_delete(worthiness, name); 
        write("Ok, you no longer express an opinion about the " +
              "reputation of " + capitalize(name) + ".\n"); 

        if (oldval == "positive") 
            worth[name] = worth[name] - 1; 
        else
            worth[name] = worth[name] + 1; 

        if (worth[name] == 0) 
            worth = m_delete(worth, name); 
        player_info["worthiness"] = worthiness; 
        save_map(player_info, GC_CADET_INFO_SAVE(n));
        save_object(GC_SAVE); 
        update_exemplary_and_unworthy(name); 
        return 1; 
    } 

    if (oldval == "neutral" && 
        m_sizeof(worthiness) >= MAX_WORTH_NAMES) {
        notify_fail("You may not exceed the maximum number " +
                    "of opinions about reputation, which is " +
                    MAX_WORTH_NAMES + ". You " +
                    "have to make one of your other " +
                    "opinions neutral before you may " +
                    "register a new one.\n"); 
        return 0; 
    } 
 
    worthiness[name] = i; 

    player_info["worthiness"] = worthiness; 
    save_map(player_info, GC_CADET_INFO_SAVE(n));

    if (val == "positive") {
        if (oldval == "negative") 
            worth[name] = worth[name] + 2;
        else
            worth[name] = worth[name] + 1;  
    } 
    else {
        if (oldval == "positive") 
            worth[name] = worth[name] - 2; 
        else 
            worth[name] = worth[name] - 1; 
    } 

    if (worth[name] == 0) 
        worth = m_delete(worth, name); 

    save_object(GC_SAVE); 
    update_exemplary_and_unworthy(name); 
    write("Ok, your opinion has been noted. Currently there are " +
          LANG_WNUM(sizeof(opiners)) + " dedicated cadets. There " +
          "have to be at least " + LANG_WNUM(MIN_OPINIONS) + " for " +
          "their opinions to have a chance of affecting reputations.\n"); 
    return 1;  
}


/*
 * Function:     list_unworthy
 * Description:  action function to list people considered by 
 *               many dedicated cadets to be unworthy to be 
 *               associated with the cadet guild.
 */ 
int
list_unworthy(string str)
{
    write("The following players are considered unworthy to " +
          "be associated with the Cadets of Gelan by " +
          "many dedicated cadets: " + 
          COMPOSITE_WORDS(map(unworthy, capitalize)) + ".\n"); 
    return 1; 
}


/*
 * Function:     list_exemplary
 * Description:  action function to list people whose conduct is
 *               considered by many dedicated cadets to be exemplary 
 *               with respect to the cadet guild.
 */ 
int
list_exemplary(string str)
{
    write("The following players are considered exemplary in their " +
          "conduct with respect to the Cadets of Gelan by " +
          "many dedicated cadets: " + 
          COMPOSITE_WORDS(map(exemplary, capitalize)) + ".\n"); 
    return 1; 
}


/*
 * Function:     list_reputations
 * Description:  action function to list reputations in the cadet
 *               guild (exemplary and unworthy). 
 */ 
int
list_reputations(string str) {
    write("The following players are on balance considered " +
       "exemplary in their conduct with respect to the Cadets " +
       "of Gelan: " + 
       (sizeof(exemplary) ? COMPOSITE_WORDS(map(exemplary, capitalize)) : 
       "none") + ".\nThe following players are on balance considered " +
       "unworthy to be associated with the Cadets of Gelan: " +
       (sizeof(unworthy) ? COMPOSITE_WORDS(map(unworthy, capitalize)) : "none")
       + ".\n"); 
    return 1; 
}


int
offensive_skill(int snum)
{
     if ((snum == SS_WEP_SWORD) ||   
         (snum == SS_WEP_AXE) || 
         (snum == SS_WEP_POLEARM) || 
         (snum == SS_WEP_KNIFE) || 
         (snum == SS_WEP_CLUB) || 
         (snum == SS_UNARM_COMBAT)) 
         return 1;

    return 0;
}


int
sk_improve(string str)
{
    object tp;
    int ofsk, max, steps, *guild_sk, *known_sk, snum, level, cost, sub, sw, pa;
    string skill, verb, *tmp;

    if (!str || sscanf(str, "%d", steps))
        return sk_list(steps);

    tp = this_player();
    if (!IS_GELAN_CADET(tp))
    {
        write("You are not a member of this guild.\n");
        return 1;
    }

    if (!objectp(guildmaster) || !present(guildmaster, this_object()))
    {
        write("You cannot improve skills while " + GC_GM_NAME + 
              " is not here.\n");
        return 1;
    }

    tmp = explode(str, " ");
    if (sscanf(tmp[sizeof(tmp) - 1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = str;
        steps = 1;
    }

    guild_sk = sk_query_train();
    known_sk = this_player()->query_all_skill_types();
    if (!known_sk)
        known_sk = ({});

    verb = query_verb();
    if ((snum = sk_find_skill(skill)) < 0)
        return sk_hook_unknown_skill(skill, verb);

    level = this_player()->query_base_skill(snum);

    max = sk_query_max(snum); 

    ofsk = 0;
    if (offensive_skill(snum)) { 
        if (tp->gc_query_primary_skill_num() == snum) 
            max = GC_MAX_LEVEL_PRIMARY_WEAPON; 
        else if (tp->gc_query_secondary_skill_num() == snum) { 
            ofsk = GC_MAX_LEVEL_SECONDARY_WEAPON;
            max = GC_MAX_LEVEL_SECONDARY_WEAPON; 
        } 
        else {  
            ofsk = 30; 
            max = 30; 
        } 
    } 

    if (!level && verb == "improve")
        return sk_hook_improve_unknown(skill);
    if (level && verb == "learn")
        return sk_hook_learn_known(skill);
    if (level + steps > max) { 
        if (ofsk == GC_MAX_LEVEL_SECONDARY_WEAPON) { 
            notify_fail("You cannot train your secondary offensive skill " +
                        "any higher.\n"); 
            return 0;
        } 
        else if (ofsk == 30) {  
            notify_fail("That would have to be your primary or secondary " +
                        "offensive skill for you to train it any higher.\n"); 
            return 0;
        } 
        else
            return sk_hook_improved_max(skill);
    } 
    if (!sk_do_train(snum, this_player(), level + steps))
        return sk_hook_cant_train(skill, level + steps);

    cost = sk_cost(snum, level, level + steps);

    if (!MONEY_ADD(this_player(), -cost))
    {
        this_player()->set_skill(snum, level);
        return sk_hook_cant_pay(skill, level + steps, cost);
    }

    sk_hook_raise_rank(snum, level + steps, cost);

    return 1;
}


/* 
 * Function:     sk_query_max
 * Description:  give the max we can teach of a skill
 * Arguments:    int snum   - the skill number to check
 *               int silent - don't tell anything to the player if true
 * Returns:      int - the maximum you can train the skill to 
 */ 
public varargs int
sk_query_max(int snum, int silent)
{
    object tp = this_player(); 
 
    if (objectp(tp) && offensive_skill(snum)) { 
        if (tp->gc_query_primary_skill_num() == snum) 
            return GC_MAX_LEVEL_PRIMARY_WEAPON; 
        else if (tp->gc_query_secondary_skill_num() == snum)
            return GC_MAX_LEVEL_SECONDARY_WEAPON; 
        else 
            return 30;
    } 

    return ::sk_query_max(snum, silent); 
}


int 
setsk(int skill, object tp, mapping sk)
{
    tp->set_skill(skill, sk[skill]); 
    return 0; 
}


/* 
 * Function:      csign()
 * Description:   Action function for joining the guild.
 */
int
csign(string str)
{
    object tp, shadow;
    mapping sk, tmp; 
    int i, m;
    string et, num; 

    tp = this_player(); 

    if (!objectp(tp))  
         return 0;

    if (!objectp(guildmaster) || !present(guildmaster, this_object()))
    {
        notify_fail(GC_GM_NAME + " is not here.\n");
        return 0;
    }

    if ((str != "on") && (str != "again")) { 
        notify_fail("Did you want to <csign on>?\n"); 
        return 0;
    } 

    if (!GC_AVG_STAT_CAN_JOIN(tp)) { 
        notify_fail("You're a bit too big to be joining the cadets!\n"); 
        return 0;
    } 

    if (IS_GELAN_CADET(tp))
    {
        notify_fail("You are already a member of this guild!\n");
        return 0;
    }

    if (tp->query_guild_member(GC_GUILD_TYPE)) {  
        notify_fail("You are already a member of another " + 
                    GC_GUILD_TYPE + " guild.\n"); 
        return 0;
    } 

    if (tp->query_guild_member_occ()) {  
        if (!tp->query_wiz_level()) { 
            notify_fail("You cannot join if you have an occupation!\n");  
            return 0;
        } 
        write("Since you are a wizard, the fact you have an occupation " +
              "will not stop you joining.\n"); 
    } 

    if (present(GC_RING_ID, tp)) { 
        notify_fail("You graduated from here already!\n"); 
        return 0;
    } 

    if (tp->test_bit(GC_DOM, GC_GROUP, GC_BIT)) { 
        if (tp->test_bit(GC_DOM, GC_GROUP, GC_BIT2)) { 
            notify_fail("You may not re-join more than once.\n"); 
            return 0;
        } 
        else if (str != "again") { 
            notify_fail("You will have to <csign again>, but remember " +
                       "to check <help cadet joining> first.\n");  
            return 0;
        } 
        else { 
            sk = 
                ([ 
                    SS_UNARM_COMBAT : tp->query_skill(SS_UNARM_COMBAT),  
                    SS_WEP_SWORD : tp->query_skill(SS_WEP_SWORD), 
                    SS_WEP_POLEARM : tp->query_skill(SS_WEP_POLEARM), 
                    SS_WEP_AXE : tp->query_skill(SS_WEP_AXE), 
                    SS_WEP_KNIFE : tp->query_skill(SS_WEP_KNIFE), 
                    SS_WEP_CLUB : tp->query_skill(SS_WEP_CLUB), 
                    SS_PARRY : tp->query_skill(SS_PARRY), 
                    SS_DEFENCE : tp->query_skill(SS_DEFENCE),  
                    SS_2H_COMBAT : tp->query_skill(SS_2H_COMBAT) 
                 ]); 
            if (tp->query_prop(CADET_I_FORGIVEN)) {  
                i = 15; 
                num = "fifteen"; 
                tp->remove_prop(CADET_I_FORGIVEN); 
            } 
            else  { 
                i = 30; 
                num = "thirty"; 
            } 
            while (i > 0) { 
                m = applyv(max, m_values(sk));  
                if (m == 0) { 
                    notify_fail("You didn't have " + num + " levels of " +
                                "combat skills to lose!\n"); 
                    return 0;
                } 
                tmp = filter(sk, &operator(==)(,m)); 
                sk[m_indexes(tmp)[0]]--; 
                i--;
            } 
            map(m_indexes(sk), &setsk(, tp, sk));  
            write("Ok, you lost " + num + " levels of combat skills.\n"); 
        } 
    } 

    notify_fail("For some unknown reason you cannot join the cadets.\n"); 
    shadow = clone_object(GC_SHADOW);
    if (shadow->shadow_me(tp, GC_GUILD_TYPE, 
                              GC_GUILD_STYLE, 
                              GC_GUILD_NAME) != 1)
    {
        shadow->remove_shadow();
        return 0;
    }

    tp->setup_skill_decay(); 
    tp->clear_guild_stat(SS_LAYMAN);
    tp->set_guild_pref(SS_LAYMAN, GC_GUILD_TAX);

    if (str == "on") 
        tp->set_bit(GC_GROUP, GC_BIT); 
    else 
        tp->set_bit(GC_GROUP, GC_BIT2); 

    register_cadet(tp); 
    write("You sign on.\n"); 
    write("You are now a Cadet of Gelan!\n"); 
    say(QCTNAME(tp) + " signs on.\n"); 
    log_file("cadet", ctime(time()) + " " + tp->query_real_name() + " " + 
         (str == "again" ? "re-" : "") + "joined.\n"); 
    guildmaster->give_shoes(tp); 
    guildmaster->add_greeted(tp->query_real_name());  
    guildmaster->command("Welcome!"); 

    if ((et = tp->query_exp_title()) == "greenhorne" ||  
        et == "novice" || et == "beginner") {
        write("As you are a youngster you are awarded some free " +
              "droproom points to help you start.\n"); 
        tp->set_skill(SS_CADET_DROPROOM_POINTS, 1000); 
    }  

    return 1;
}


/* 
 * Function:     choose
 * Description:  Action function to choose player's primary and secondary
 *               weapon skills
 */ 
int
choose(string str)
{
     string *sel, pri, sec;
     mixed trainer; 
     int prisel, secsel, old_prisel, 
         old_secsel, old_prinum, old_secnum, 
         pri_reset, sec_reset;
     object tp = this_player(); 

     if (!IS_GELAN_CADET(tp)) { 
         notify_fail("You are not a member of this guild.\n"); 
         return 0;
     } 

     notify_fail("Syntax: choose <primary> <secondary>\n" +
                 "Choose from: " +  
                 COMPOSITE_WORDS(m_indexes(gc_name_selected_map)) + ".\n"); 

     if (!stringp(str) || !strlen(str))  
         return 0;

     sel = explode(str, " "); 
     if (sizeof(sel) != 2) 
         return 0;

     pri = sel[0]; 
     sec = sel[1];

     if (pri == sec) { 
         notify_fail("You may not have the same primary and secondary " + 
                     "offensive skill.\n"); 
         return 0;
     } 

     prisel = gc_name_selected_map[pri];
     if (!prisel) {
          notify_fail("The offensive skill: " + pri + " is unrecognised.\n"); 
          return 0;
     } 

     secsel = gc_name_selected_map[sec];
     if (!secsel) { 
          notify_fail("The offensive skill: " + sec + " is unrecognised.\n"); 
          return 0;
     } 

     old_prisel = tp->query_skill(GC_SKILL_PRIMARY_WEAPON); 
     old_secsel = tp->query_skill(GC_SKILL_SECONDARY_WEAPON); 

     old_prinum = tp->gc_query_primary_skill_num();  
     old_secnum = tp->gc_query_secondary_skill_num(); 

     if (old_prisel) { 
         /* If the old primary selection is now the secondary 
            selection, it may be up to 45, otherwise 30. */ 
         trainer = tp->query_guild_trainer_race(); 
         if (pointerp(trainer) && sizeof(trainer))
             trainer = trainer[0]; 
         seteuid(getuid()); 
         trainer = trainer->sk_query_max(old_prinum); 
         if (trainer > 45) 
             pri_reset = trainer; 
         else if (old_prisel == secsel) 
             pri_reset = min(tp->query_skill(old_prinum), 45);  
         else if (trainer > 30)
             pri_reset = trainer; 
         else
             pri_reset = 30;  
         /* If the player gets a new primary selection, 
            reset the old one if necesssary */ 
         if ((old_prisel != prisel) && 
             (tp->query_skill(old_prinum) > pri_reset)) {  
             tell_object(tp, "Your " + tp->gc_query_primary_skill_name() + 
                             " skill is reset.\n"); 
             tp->set_skill(old_prinum, pri_reset); 
         } 
      } 

      if (old_secsel) { 
         /* If the old secondary selection is now the primary 
            selection, it may be up to 50, otherwise 30 */ 
         trainer = tp->query_guild_trainer_race(); 
         if (pointerp(trainer) && sizeof(trainer))
             trainer = trainer[0]; 
         seteuid(getuid()); 
         trainer = trainer->sk_query_max(old_secnum); 
         if (trainer > 50)
             sec_reset = 50; 
         else if (old_secsel == prisel) 
             sec_reset = 50; 
         else if (trainer > 30)
             sec_reset = trainer; 
         else
             sec_reset = 30;  

         /* If the player gets a new secondary selection, 
            reset the old one if necesssary */ 
         if ((old_secsel != secsel) && 
              (tp->query_skill(old_secnum) > sec_reset)) {   
              tell_object(tp, "Your " + tp->gc_query_secondary_skill_name() + 
                              " skill is reset.\n"); 
              tp->set_skill(old_secnum, sec_reset); 
         } 
     } 

     tp->set_skill(GC_SKILL_PRIMARY_WEAPON, prisel);  
     tp->set_skill(GC_SKILL_SECONDARY_WEAPON, secsel);  
     write("Your primary offensive skill is now: " + pri + ".\n" + 
           "Your secondary offensive skill is now: " + sec + ".\n");  
     tp->gc_init_title(); 
     return 1;
}


int
help(string str)
{
    string content, *files;

    if (!stringp(str) || !strlen(str)) 
        return 0; 

    if (str == "cadet") {
        if (!pointerp(files = get_dir(GC_HELP_DIR)) || !sizeof(files))
            return 0;
        this_player()->more("Cadet help is available on the following " +
                            "topics e.g. \"help cadet " + files[0] + "\":\n"+
                            sprintf("%#-70s", implode(files, "\n")));
        return 1;
    }

    if (sscanf(str, "cadet %s", str) != 1)
        return 0;

    if (stringp(content = read_file(GC_HELP_DIR + str))) {
        this_player()->more(content);
        return 1;
    }

    notify_fail("There is no cadet help available on that topic.\n");
    return 0;
}


int
ctitles(string str)
{
     string r;

     if (stringp(str)) { 
         notify_fail("Ctitles requires no argument.\n"); 
         return 0;
     } 

     write("Cadet titles are made of two parts: cadet type " +
          "and cadet level. Possible cadet types, depending on one's "+
          "primary offensive weapon are: " + 
          COMPOSITE_WORDS(m_values(GC_SELECTED_TITLE_MAP) - ({ "" })) + 
          ". Possible level titles, depending on a number of factors, " +
          "are, in ascending order: " + 
          COMPOSITE_WORDS(GC_LEVEL_TITLE_ARR) + ". " + 
          "Resulting full titles take forms such as `Senior Fistfighter " +
          "Cadet of Gelan.'\n"); 

    return 1;
}


int
cpermit(string str)
{
    if (!this_player()->query_wiz_level())  
        return 0;

    if (!stringp(str)) { 
        notify_fail("Syntax: cpermit <player>\n");  
        return 0;
    } 

    str = lower_case(str); 
    if (member_array(str, allowed_back) > -1) { 
        notify_fail("That player is already allowed back.\n"); 
        return 0;
    } 

    if (!SECURITY->exist_player(str)) { 
        notify_fail("No such player!\n"); 
        return 0;
    } 

    if (!SECURITY->valid_write(MASTER, this_player(), write_file)) { 
        notify_fail("You are not allowed to do that!\n"); 
        return 0;
    } 

    allowed_back += ({ str }); 
    log_file("cadet", capitalize(this_player()->query_real_name()) + 
                      " allowed " + str + " back.\n"); 
    save_object(GC_SAVE); 
    write("Ok.\n"); 
    return 1;
}


private void
write_forgiveness(object victim, object criminal)
{
    tell_object(victim, "You forgive " + 
         criminal->query_the_name(victim) + ".\n"); 
    tell_room(this_object(), 
         QCTNAME(victim) + " forgives " + QTNAME(criminal) + ".\n", 
         ({ criminal, victim })); 
    tell_object(criminal, victim->query_The_name(criminal) + 
         " forgives you.\n"); 
}


/* 
 * Allows someone who was thrown out of the guild for killing 
 * a fellow cadet to be forgiven by their victim, which means they 
 * can be let back in with less of a skills penalty. Also allows
 * one to forgive an aggressing cadet who attacked but didn't kill, 
 * which reduces their donk ban. 
 */ 
int
cforgive(string str)
{
    string rn; 
    object criminal; 
    object tp = this_player(); 
    int start_ban, end_ban, diff, lift_time, tm; 

    if (!stringp(str)) { 
        notify_fail("Syntax: cforgive <player>\n"); 
        return 0; 
    } 

    rn = tp->query_real_name(); 

    if (!objectp(criminal = find_player(str = lower_case(str))) ||
        environment(criminal) != this_object()) { 
        notify_fail("That player has to be present in this room to be " +
                    "forgiven.\n"); 
        return 0;
    } 

    if (criminal == tp) { 
        notify_fail("Har har!\n"); 
        return 0; 
    } 

    if (!(rn == assaulted[str])) { 
        if (!IS_GELAN_CADET(criminal) || 
            !mappingp(player_info = restore_map(GC_CADET_INFO_SAVE(str))) || 
            !m_sizeof(player_info) || 
            !(start_ban = player_info["warn_start_" + rn]) || 
            !(end_ban = player_info["warn_end_" + rn]) || 
            (end_ban < (tm = time())) ||
            ((lift_time = criminal->query_skill(SS_CADET_DONK_BAN)) < tm)) { 
             notify_fail("Seems that there is nothing to forgive!\n"); 
             return 0; 
        } 
        lift_time -= (diff = ((end_ban - tm) * 2) / 3);
        write_forgiveness(tp, criminal); 
        player_info = m_delete(player_info, "warn_start_" + rn); 
        player_info = m_delete(player_info, "warn_end_" + rn); 
        save_map(player_info, GC_CADET_INFO_SAVE(str)); 
        criminal->set_skill(SS_CADET_DONK_BAN, lift_time); 
        tell_object(criminal, "Your donk ban is reduced by " + 
            CONVTIME(diff) + ".\n"); 
        player_info = ([ ]); 
        return 1; 
    } 

    criminal->add_prop(CADET_I_FORGIVEN, 1); 
    assaulted = m_delete(assaulted, str); 
    save_object(GC_SAVE); 

    write_forgiveness(tp, criminal); 
    log_file("cadet", capitalize(rn) + " forgave " + capitalize(str) + ".\n"); 

    return 1;
}


void
init()
{
    ::init();
    init_skill_raise();
    add_action(choose, "choose");
    add_action(csign, "csign");
    add_action(ctitles, "ctitles"); 
    add_action(help, "help"); 
    add_action(cpermit, "cpermit"); 
    add_action(cforgive, "cforgive"); 
    add_action(register_opinion, "copinion"); 
}
