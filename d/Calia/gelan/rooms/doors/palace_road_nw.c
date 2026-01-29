/* 	this is a door of the town Gelan

    coder(s):   Merlin

    history:    21. 2.93    path system                     Merlin
                14. 1.93    towndoors.h -> door.h           Merlin
                21.12.92    created                         Merlin

    purpose:	door to close the stable
    exits:      door between palace road east and stable west

    quests:     none
    special:    none

    to do:      install same door in the stable
    bug:        none known
*/


inherit "/std/door";
#include "door.h"
#include <stdproperties.h>

create_door() {

  ::create_door();                              /* get defaults */

  set_door_id("stable_door");                   /* id, must be unique in room */
  set_door_name(({"wooden door","door"}));      /* name(s) for the door, first
                                                   string is std desc */
  set_door_desc(BS("It is a simple wooden door with the golden sign of Gelan on it.\n"));

  /* commands */

  set_other_room(GELAN_ROOMS + "stables_w");            /* room on the other side */
  set_pass_command(({"west","in","enter"}));    /* command(s) to pass the door */

  /* lock */

  /* state */

  set_open(0);                                  /* 1 for open, 0 for closed, std 1 */
  set_locked(0);                                /* 1 for unlocked, 0 for locked, std 1 */

  /* descs */

  set_open_desc("There is a open door leading west.\n"); /* desc for the open door */
  set_closed_desc("There is a closed door leading west.\n"); /* desc for the closed door */

  /* properties */

  add_prop(DOOR_I_HEIGHT, 300);                    /* height of the door, std 2 m */
  add_prop(OBJ_I_WEIGHT, 100000);                  /* weight of the door, std 60 kg */
  add_prop(OBJ_I_VOLUME, 10000);                   /* volume of the door, std 80 l */
}


/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
