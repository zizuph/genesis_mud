/*
Pax Tharkas, Wall level, chainchamber, Crack in wall, view of the 
throne room.

chainchamber2.c
---------------

Coded ........: 95/02/15
By ...........: Jeremiah

Latest update : 95/03/08
By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define CRACK \
({   \
      GROUND_LEVEL + "throne_room", \
 })


create_pax_room()
{
   set_short("Chain chamber");
   set_long("@@room_descr");
   
   INSIDE;
   add_prop(ROOM_I_LIGHT, 1);
   
   add_item("chain", "A huge chain made of steel links. Each chain " +
      "link is as high as a grown human, and as thick as a human's leg.\n");
   
   add_item("dust", "A thick layer of greyish dust, covering everything " +
      "in here.\n");
   
   add_item("crack", "@@crack_descr");
   
   add_exit(WALL_LEVEL + "chainchamber1", "east", 0);   
   add_exit(WALL_LEVEL + "chainchamber3", "west", 0);
}      


string
room_descr()
{
   if (light() <= 1)
      return "An almost dark room. A thin trickle of light leaks through " +
   "a crack in the north wall. It is too dark in here too see " +
   "any further features of this room.\n";
   
   
   return "You are standing in a cavernous tunnel stretching to the " +
   "east and to the west from here. A huge chain runs " +
   "though the room. Everything in here is covered in a thick " +
   "layer of dust. There is small crack in the north " +
   "wall.\n";
}


string
crack_peek()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;
   
   roomfiles = CRACK;
   inv = ({});
   
   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }
   
   if (inv && sizeof(inv) > 0)
      {
      live = FILTER_LIVE(inv);
      if (sizeof(live) > 0)
         return (COMPOSITE_LIVE(live) + ".");
   }
   return "";
}


string
crack_descr()
{
   return "Peeking through the crack you look down into a large room, " +
   "furnished with every possible luxury. You are sure that " +
   "all that is beautiful, graceful, delicate and valuable in " +
   "the world, has been brought here to decorate this room. " +
   "A large ornate throne stands, raised above the floor on " +
   "a stone dais, in the south end of the room. Rare and " +
   "priceless silver mirrors hang on the walls. A pair of huge " +
   "open doors lead west.\n" + crack_peek() + "\n";
}


construction()
{
   write("Sorry this are is under construction.. you can't go there.\n");
   return 1;
}

