/*
  this is a special file of the lost land

  coder(s):   Deinonychus

  history:
  DATE		WHAT DONE					WHO DID
  23.10.93	created						Deinonychus


  purpose:	holding all pathes to all files in Gelan

  to do:	none
  bug:		none known
*/

#include "specials.h"
#include "path.h"

/*
 * Function name:	room_path
 * Description:		returns the filename for a room
 * Arguments:		id of room
 * Returns:		filename of the room
 */
string
room_path(string str)
{
  return rooms_path[str];
}

/*
 * Function name:	object_path
 * Description:		returns the filename for an object
 * Arguments:		id of object
 * Returns:		filename of the object
 */
string
object_path(string str)
{
  return objects_path[str];
}

/*
 * Function name:	weapon_path
 * Description:		returns the filename for a weapon
 * Arguments:		id of weapon
 * Returns:		filename of the weapon
 */
string
weapon_path(string str)
{
  return weapons_path[str];
}

/*
 * Function name:	armour_path
 * Description:		returns the filename for a armour
 * Arguments:		id of armour
 * Returns:		filename of the armour
 */
string
armour_path(string str)
{
  return armours_path[str];
}

/*
 * Function name:	special_path
 * Description:		returns the filename for a special
 * Arguments:		id of special
 * Returns:		filename of the special
 */
string
special_path(string str)
{
  return specials_path[str];
}

/*
 * Function name:	monster_path
 * Description:		returns the filename for a monster
 * Arguments:		id of monster
 * Returns:		filename of the monster
 */
string
monster_path(string str)
{
  return monsters_path[str];
}


