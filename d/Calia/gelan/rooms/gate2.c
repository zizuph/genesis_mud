/*  
    this is a room of the town Gelan

    coder(s):   Merlin & Maniac

    History:
             15/7/2000  enemy & murder features introduced      Maniac
             14/2/2000  entrance criteria changed to consider
                        cadets, graduates, calians & sneaking   Maniac
             24/8/95    revised                                 Maniac
             18/8/95    Exit northeast added                    Maniac        
             26/7/95    Old file revised                        Maniac

    purpose:    guards the town, only pass when have not caused trouble
                in the town recently

    objects:    notice obout entrance
    npcs:       entrance guard, some 'normal' guards

    quests:     none
    special:    exits not open to all

    to do:      none
    bug:        none known
*/

#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <filter_funs.h> 
#include <cmdparse.h> 
#include <macros.h>
#include GUARD_INCLUDE
#include CADET_INCLUDE
#include GELAN_ENEMY_INCLUDE

#define IS_CALIAN(tp) (tp->query_guild_name_occ() == "Calian warrior's guild")
#define PLAYER_I_GELAN_CHECKED_ENEMY "_player_i_gelan_checked_enemy"

int check_letter = 'a'; 
string *enemies = ({ }); 


static object entrance_guard; 


/* 
 * Function:     query_should_be_enemy
 * Description:  Given a murder count and a last murder time, 
 *               returns 1 if the player with this record should 
 *               now be considered an enemy, 0 otherwise. 
 */ 
int 
query_should_be_enemy(int murder_count, int last_murder_time) 
{ 
    return 
        (murder_count >= MURDER_COUNT_THRESHOLD && 
         (last_murder_time + MURDER_FORGIVE_DURATION * murder_count) 
          > time()); 
} 


/* 
 * Function:     query_enemy 
 * Description:  returns 1 if player with the specified real 
 *               name (pn) is an enemy of Gelan, 0 otherwise. 
 */ 
int
query_enemy(string pn) 
{
    return (member_array(pn, enemies) > -1); 
}


/*
 * Function:    remove_enemy
 * Description: removes the player with the specified real name
 *              from the enemy list. 
 */ 
void
remove_enemy(string pn)
{
    int i; 

    if ((i = member_array(pn, enemies)) > -1) {
        enemies = exclude_array(enemies, i, i); 
        save_object(GELAN_ENEMIES_SAVE); 
    }
}


/* 
 * Function:     record_murder 
 * Description:  records that a certain player just murdered 
 *               an inhabitant of Gelan. 
 */ 
void 
record_murder(object murderer, object victim) 
{ 
    string pn; 
    string tmp; 
    mapping m; 

    if (!objectp(murderer) || murderer->query_wiz_level() ||
        !stringp(pn = murderer->query_real_name()) || 
        !strlen(pn))
        return; 

    if (!mappingp(m = restore_map(tmp = GELAN_ENEMY_SAVE(pn))))
        m = ([ ]);  

    m["murder_count"] = m["murder_count"] + 1; 
    m["last_murder_time"] = time(); 
    save_map(m, tmp); 
    if (query_should_be_enemy(m["murder_count"], m["last_murder_time"]) 
        && member_array(pn, enemies) == -1) {
        enemies += ({ pn }); 
        save_object(GELAN_ENEMIES_SAVE);     
        murderer->add_prop(ATTACKED_GELAN, 1); 
        murderer->add_prop(PLAYER_I_GELAN_CHECKED_ENEMY, 1); 
    }
} 


/* 
 * Function:     query_murder_record 
 * Description:  determines the number of murders carried out by 
 *               the given player, which can be an object or 
 *               the real name of the player, and the time that 
 *               the last murder was carried out. 
 * Returns:      An array of integers, first argument indicating 
 *               the murder count, second argument indicating 
 *               the time the last murder was committed, or 0 if 
 *               the player is not a recorded murderer. 
 */ 
int * 
query_murder_record(mixed player)
{ 
    string pn;
    mapping m;

    if ((objectp(player) &&
         stringp(pn = player->query_real_name()) &&
         strlen(pn)) ||  
        (stringp(player) && strlen(pn = player))) {
        m = restore_map(GELAN_ENEMY_SAVE(pn)); 
        return ((mappingp(m) && m_sizeof(m)) ? 
                ({ m["murder_count"], m["last_murder_time"] }) : 0); 
    } 
} 


/* 
 * Function:     update_enemy_status 
 * Description:  updates whether the specified player is an enemy, 
 *               (the player may be specified as an object or a 
 *                string indicating his/her real name). 
 * Returns:      1 if the player is now an enemy, 0 otherwise. 
 */ 
int
update_enemy_status(mixed player) 
{ 
    string pn; 
    mapping m; 

    if (((objectp(player) &&
          stringp(pn = player->query_real_name()) &&
          strlen(pn)) ||  
         (stringp(player) && strlen(pn = player))) && 
        mappingp(m = restore_map(GELAN_ENEMY_SAVE(pn))) && 
        m_sizeof(m)) { 
        if (member_array(pn, enemies) > -1) { 
            if (!query_should_be_enemy(m["murder_count"], 
                                       m["last_murder_time"])) {
                enemies -= ({ pn }); 
                save_object(GELAN_ENEMIES_SAVE); 
                return 0; 
            }
            return 1; 
        } 
        else { 
            if (query_should_be_enemy(m["murder_count"], 
                                      m["last_murder_time"])) {
                enemies += ({ pn }); 
                save_object(GELAN_ENEMIES_SAVE);
                return 1;  
            }
            return 0; 
        } 
    } 
    return 0; 
} 


/*
 * Function:     enter_inv 
 * Description:  Called when an object enters this room. This 
 *               instance of the function updates an interactive's
 *               enemy status when they enter the gate for the
 *               first time in a login. 
 */ 
void 
enter_inv(object ob, object from) 
{ 
    ::enter_inv(ob, from); 
    if (interactive(ob) && 
        !ob->query_prop(PLAYER_I_GELAN_CHECKED_ENEMY)) { 
        if (update_enemy_status(ob)) 
            ob->add_prop(ATTACKED_GELAN, 1); 
        ob->add_prop(PLAYER_I_GELAN_CHECKED_ENEMY, 1); 
    } 
}


/* 
 * Function name: exa_drawbridge
 * Description:   gives description of bridge, depending on daytime
 * Arguments:     none
 * Returns:       string with description
 */
string
exa_drawbridge()
{
    return "The drawbridge looks solid. Because it is down now, you "
         + "can easily leave Gelan.\n";

} /* exa_drawbridge */



/*
 * Function name: pass_drawbridge
 * Description:   checks if drawbridge is down (to cross it)
 * Arguments:     none 
 * Returns:       0 if down, 1 if up and not passable 
 */
int
pass_drawbridge()
{
        return 0;
} /* pass_drawbridge */


/*
 * Function name: pass_guards
 * Description:   checks if a player can enter Gelan
 * Arguments:     none
 * Returns:       0 if the player can pass, 1 if not
 */
int
pass_guards()
{
    int alignment, safe;
    object tp = this_player();

    /* test if entrance_guard is present and
       can see entrant. */
    if(!objectp(entrance_guard) || 
       !objectp(present(entrance_guard, this_object())) ||
       !CAN_SEE(entrance_guard, tp) ||
       !CAN_SEE_IN_ROOM(entrance_guard) ||
       tp->query_wiz_level()) 
        return 0;

    alignment = tp->query_alignment();
    safe = (IS_GELAN_CADET(tp) ||
            IS_GRADUATE(tp) ||
            IS_CALIAN(tp)); 

    if (!safe &&
        (tp->query_prop(OBJ_I_INVIS) ||
         tp->query_prop(OBJ_I_HIDE))) { 
        tell_room(this_object(), QCTNAME(entrance_guard) + 
            " blocks " + QTNAME(tp) + " from entering Gelan.\n", 
            ({ entrance_guard, tp })); 
        tell_object(tp, entrance_guard->query_The_name(tp) + 
            " blocks you from entering Gelan.\n"); 
        entrance_guard->command("say " +  
            tp->query_The_name(entrance_guard) +  
            ", if you stop trying to enter town by stealth, " +  
            "I may let you by."); 
        return 1; 
    } 

    if (tp->query_prop(ATTACKED_GELAN)) {
        say(QCTNAME(entrance_guard) + " will not let " + QTNAME(tp) +
             " by, as he believes " + tp->query_objective() +
             " to be a menace!\n");
        tp->catch_msg(QCTNAME(entrance_guard) + " will not let you by, " +
                    "as he believes you to be a menace!\n");
        return 1;
    }
    else if ((alignment < 0) && !safe) 
  	{
        say(QCTNAME(entrance_guard) + " only reluctantly lets " + QTNAME(tp)  
          + " through, and with a warning, because in the eyes of the " 
          + "representatives of Gelan " + tp->query_pronoun() 
          + " is evil and therefore a potential menace.\n");
        tp->catch_msg(QCTNAME(entrance_guard) + " is reluctant to let " 
          + "you pass because he detects the evil that rules your soul, " 
          + "but he lets you through with a warning.\n");
        return 0;
    }
    else
        if (interactive(tp) && !safe) {
            say(QCTNAME(entrance_guard) + " lets " + QTNAME(tp) 
              + " pass into the town of Gelan.\n");
            tp->catch_msg("As you pass the gate, " + QTNAME(entrance_guard)  
              + " tells you:\nThe guards welcome you, traveller, into "
              + "the town of Gelan. May your stay be pleasant.\n");
            return 0;
        }
} /* pass_guards */


/*
 * Function name: reset_room
 * Description:   resets the room, installs the guards
 * Arguments:     none
 * Returns:       none
 */
void
reset_room()
/* resets the room */
{
    object *gamali;   
    seteuid(getuid());

    (GELAN_SPECIALS + "head_guard")->reset_guards();

    if (!sizeof(gamali = FIND_STR_IN_ARR("gamalus", 
                                 FILTER_LIVE(all_inventory(this_object()))))) 
        return; 

    entrance_guard = gamali[0]; 

} /* reset_room */


/* reading/examining a note */
string
note()
{
     return 
            "The town of Gelan welcomes "
          + "you, traveller. \n\nThe town of Gelan still lives in some "
          + "fear of \nthe dark and evil wizard Kroug. We know that "
          + "\nthere are still some members of his army \naround so " 
          + "people will be closely inspected\nbefore being allowed " 
          + "entry. We "
          + "will not allow\nthose who have recently caused trouble " 
          + "here to\npass this gate, but generally we try to give\n" 
          + "the benefit of the doubt to most folk, even\nthose who " 
          + "are evil.\n"
          + "Please do not abuse our hospitality!\n\n" 
          + "      Gamalus, head of the Gelan Guards\n\n";
}



/*
 * Function name: create_room
 * Description:   creates the room
 * Arguments:     none
 * Returns:       none
 */
void
create_room()
{
    /* descriptions */

    set_short("Gate of Gelan");
    set_long("You are inside the southernmost part of the giant gate "
          + "of Gelan. To the north you see the gate continue, flanking "
          + "the palace road as it runs towards the town square. "
          + "To the south is the drawbridge of the town, which is " 
          + "down now, and further to the south you see a large roundabout. "
          + "To your west is a room for important announcements and " 
          + "discussions. "
          + "You notice an official looking note on the wall here.\n");

    /* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "boardroom", "west");
    add_exit(GELAN_ROOMS + "palace_road_sw","north","@@pass_guards"); 
    add_exit(GELAN_ROOMS + "drawbridge","south","@@pass_drawbridge");
    add_exit(GELAN_ROOMS + "standby_guards","east","@@pass_guards");
    add_exit(GELAN_ROOMS + "palace_road_se", "northeast", "@@pass_guards");
    add_exit(GELAN_ROOMS + "guards_armoury_sw","northwest", "@@gsw_block");

    /* items in the room */

    add_item(({"note", "notice"}), "@@note");
    add_cmd_item(({"note", "notice"}), "read", "@@note");
    add_item(({"bridge", "drawbridge"}), "@@exa_drawbridge");

    add_item(({"road","floor","ground"}), DESC("floor"));
    add_item(({"town","gelan","Gelan"}), DESC("gelan"));
    add_item(({"armoury", "armouries","house","building"}),
      DESC("armoury_house"));
    add_item("entrance", DESC("armoury_entrance"));
    add_item("sign", DESC("armoury_sign"));
    add_item(({"column","columns"}), DESC("gate_columns"));
    add_item("gate", DESC("gate"));
    add_item("square", DESC("square_far"));
    add_item("statue", DESC("fountain_statue_far"));
    add_item("marble", DESC("marble"));

    reset_room();
    restore_object(GELAN_ENEMIES_SAVE); 
} /* create_room */


int
gsw_block()
{
  write("The southwest guards armoury is currently off limits.\n");
  return 1;
}
