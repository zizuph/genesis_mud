/* Mute Feb. 2, 1995 */
inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   set_short("tunnel");
   set_long("Your footsteps echo off the walls and play on your ears...    ...strange noises seem to echo occasionally throughout this long, uniform passageway.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost black color that is very dull in luster and reflects little light.\n");
   add_item("block", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_item("blocks", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/tun1","south");
   add_exit("/d/Rhovanion/mute/dungeon1/int1","north");
}
