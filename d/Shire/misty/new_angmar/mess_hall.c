/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void
create_room()
{
  set_short("Mess hall");
/*
// original descr

  set_long("Once, many soldiers gather here to eat their communal " +
    "meals before leaving to war. Now, the room is bare except for " +
    "the overturned tables and chairs, which have rotted away.\n");
*/

    set_long("Rotting, overturned tables and benches are scattered " +
        "about and buried under the caved in ceiling. This seems to " +
        "have been a communal mess hall for the Army that dwelt here. " +
        "No doubt, the soldiers would have met and had meals before " +
        "going out and conquering lands. Now, little remains other " +
        "than broken dishes and melted implements.\n");
    
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */


  add_exit(NEW_ANGMAR + "c3", "west");
}
