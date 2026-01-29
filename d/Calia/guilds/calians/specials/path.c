/*      this is a special file of the crystalline palace
 
    coder(s):   Merlin, Glykron
    history:
                20.10.93    created                         Glykron
                27. 9.94    log_path added                  Glykron
 
    purpose:    holding all pathes to all files in the palace
 
    to do:      none 
    bug:        none known 
*/ 
 
#pragma save_binary

#include "defs.h" 
#include "paths.h" 
 
/* 
 * Function name: room 
 * Description:   returns the filename for a room 
 * Arguments:     id of room 
 * Returns:       filename of the room 
 */ 
string 
room_path(string str) 
{ 
    return rooms_path[str]; 
} 

/* 
 * Function name: object 
 * Description:   returns the filename for an object 
 * Arguments:     id of object 
 * Returns:       filename of the object 
 */ 
string 
object_path(string str) 
{ 
    return objects_path[str]; 
} 
 
/* 
 * Function name: weapon 
 * Description:   returns the filename for a weapon 
 * Arguments:     id of weapon 
 * Returns:       filename of the weapon 
 */ 
string 
weapon_path(string str) 
{ 
    return weapons_path[str]; 
} 
 
/* 
 * Function name: armour 
 * Description:   returns the filename for a armour 
 * Arguments:     id of armour 
 * Returns:       filename of the armour 
 */ 
string 
armour_path(string str) 
{ 
    return armours_path[str]; 
} 
 
/* 
 * Function name: door 
 * Description:   returns the filename for a door 
 * Arguments:     id of door 
 * Returns:       filename of the door 
 */ 
string 
door_path(string str) 
{ 
    return doors_path[str]; 
} 
 
/* 
 * Function name: special 
 * Description:   returns the filename for a special 
 * Arguments:     id of special 
 * Returns:       filename of the special 
 */ 
string 
special_path(string str) 
{ 
    return specials_path[str]; 
} 
 
/* 
 * Function name: monster_path 
 * Description:   returns the filename for a monster 
 * Arguments:     id of monster 
 * Returns:       filename of the monster 
 */ 
string 
monster_path(string str) 
{ 
    return monsters_path[str]; 
} 
 
/* 
 * Function name: text_path 
 * Description:   returns the filename for a text 
 * Arguments:     id of text 
 * Returns:       filename of the text 
 */ 
string 
text_path(string str) 
{ 
    return texts_path[str]; 
} 
 
/* 
 * Function name: log_path 
 * Description:   returns the filename for a log 
 * Arguments:     id of log 
 * Returns:       filename of the log 
 */ 
string 
log_path(string str) 
{ 
    return logs_path[str]; 
} 