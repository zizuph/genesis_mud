/* 	this is a special file of the town Gelan 

coder(s):   Merlin 

history:    
	    14.09.94	function text_path added	Deinonychus
	    14. 1.93    created                         Merlin 

purpose:	holding all pathes to all files in Gelan 

to do:      none 
bug:        none known 
*/ 

#include "specials.h" 
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
 * Description:   returns the filename for a textfile
 * Arguments:     id of textfile
 * Returns:       filename of the textfile
 */ 
 
string 
text_path(string str) 
{ 
    return texts_path[str]; 
} 
 
 
