/*
 * Updated entrance to Tricksters guild
 * Finwe, June 2002
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit "/d/Shire/room";

create_room()
{
   set_short("A secret room.");
   set_long("This is a secret room behind the bookcase of the house. " +
        "The room is bare except for a large table sitting in the " +
        "middle of the room surrounded by several chairs. A frayed " +
        "carpet covers the floor and a door is set in the east wall.\n");
   
   
   add_item(({"walls"}), 
        "The walls are unpainted and bare. Narrow lines of light " +
        "stream through the cracks in the walls.\n");
    add_item("ceiling", 
        "The ceiling is flat, bare, and unpainted.\n");
    add_item(({"carpet", "frayed carpet", "large frayed carpet", 
            "rug", "large frayed rug", "frayed rug"}),
        "The carpet is large, covering most of the floor. It is " +
        "frayed around the edges and thread-bare in spots.\n");
    add_item(({"floor", "ground"}),
        "The floor is covered by a large frayed carpet.\n");
   
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,1);
   
   add_exit(TOWN_DIR + "hhouse1","east");
//   add_exit("/d/Shire/trickster/join.c","down");
}

init()
{
    ::init();
    add_action("do_push","move");
    add_action("do_push","lift");
}


int
do_push(string str)
{
  if (!str)
  {
     notify_fail("Move what?\n");
     return 0;
  }
   if (str != "carpet")
      {
      NF("You move the "+str+", but nothing happens.\n");
      return 0;
   }
   say(QCTNAME(TP) + " moves the carpet and opens a trapdoor. " +
        CAP(HE_SHE(TP))+" climbs down the trapdoor and disappears.\n");
   write("You move the carpet and discover a trapdoor.\n");
   write("You climb down through the trapdoor and disappear.\n");
//   TP->move_living("M","/d/Shire/trickster/join",1);
   TP->move_living("M","/d/Shire/trickster/join.novouching",1);
   
   return 1;
   
}
