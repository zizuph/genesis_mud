/* The Adventurers' Guild Hall of Undraeth */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The adventurers' guild hall of Undraeth");
   set_long("Night-black stone walls, fashioned from the very rock of "+
      "the Dark Dominion surrounds you. The walls themselves, however, "+
      "are not bare and undecorated. Upon them have been carved many "+
      "intricate portraits, detailing battles and events that have occured "+
      "throughout the history of the drow. Many stone benches line the "+
      "sides of this large, circular room. At the room's far end lies a "+
      "spiraling stone staircase that leads upwards, while occupying the "+
      "center of the room is an obsidian board.\n");
   add_item(({"night-black stone walls","night-black walls","stone walls","walls","wall"}),
      "They are constructed from a stone that seems to absorb all the light "+
      "in the room, leaving it dim and hazy in appearance.\n");
   add_item(({"floor","ground","ceiling"}),
      "It is constructed just as the walls, from the rock of the Dark "+
      "Dominion itself.\n");
   add_item(({"intricate portraits","portraits","portrait"}),
      "Depicted are various battle scenes, some show drow battling surface elves, "+
      "while others portray drow fighting dwarves and gnomes.\n");
   add_item(({"stone benches","benches","bench"}),
      "Resting places for weary adventurers.\n");
   add_item(({"large room","circular room","room"}),
      "It is where you are, have a look around.\n");
   add_item(({"spiraling stone staircase","spiraling staircase","stone staircase","staircase"}),
      "A twisting set of stairs that leads up into the second floor of this structure.\n");
   add_exit(CPASS(drow/shop/a_g_train),"up",0,-1,-1);
   add_exit(CPASS(drow/d27),"north","@@msg",-1,-1);
   clone_object(CPASS(drow/shop/undraeth_board))->move(TO);
}
msg()
{
   write("You leave the building and venture forth into the street.\n");
   say(QCTNAME(TP) + " heads out the doorway and into the street.\n");
   return 0;
}
