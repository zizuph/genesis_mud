
 /* Worshippers training room/private board room */
 /* by Jaacar 1996                               */
 /* 
  * Change log: 
  *             Baldacin, May 2004.
  *                Added a trash bin where people
  *                can throw useless items in.
  */ 

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "defs.h"

void
create_room()
{
    set_short("Old training chamber");
    set_long("This chamber of the natural temple was a training "+
        "facility for the members of this circle. To the northwest "+
        "you see a large chamber with an altar in it, and to the "+
        "west a cosy chamber with beds.\n");

    add_item(({"walls","wall"}),"The walls here are made of a "+
        "granite-like stone, much like the other walls in this "+
        "temple.\n");

    add_item(({"floor","ground"}),"The floor is a "+
        "nicely trimmed layer of green grass which feels good on your "+
        "feet as you walk around.\n");

    add_item(({"roof","ceiling"}),"The ceiling consists of grass, straw "+
        "and mud packed together in a tight weave to make a warm, sturdy "+
        "roof.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(ELEMENTALIST_TEMPLE+"olds_chamber","northwest",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldstartroom","west",0,1);

}
