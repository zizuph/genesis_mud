// File name:    /d/Avenir/common/dark/l5/s20.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
// note:         
// bug(s):       
// to-do:        
// revision:     
inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

void reset_room()
{
    cleanup_loot();
}

void
create_room()
{
    set_short("small chamber");
    set_long("This is a very old, worn down room made from the rough-hewn "
      + "stone of the tunnels. Leading upwards into the north wall is "
      + "a wide stone staircase, from where a cool breeze is blowing. To the "
      + "southwest, a terrible smell emanates.\n");

    AI(({"stair", "stairs"}), "They lead up into fresh air.\n");
    add_exit(L5 + "s9", "southwest", 0);
    add_exit(L4 + "e1", "up", 0);
    add_prop(ROOM_I_LIGHT, 0);
    IN
}
