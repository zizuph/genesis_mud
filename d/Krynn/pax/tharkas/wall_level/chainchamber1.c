/*
   Pax Tharkas, Wall level, chainchamber, entrance to the chainshaft,
   leading down to the chainroom, in Sla Mori. 

   chainchamber1.c
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

inherit PAXINROOM;

int    hidden_door_found = 0;  /* 0 = hidden door NOT found */
object other_room = WALL_LEVEL + "gallery5";
object down_room = WALL_LEVEL + "chainshaft4";


create_pax_room()
{
   set_short("Chain chamber at shaft");
   set_long("You are standing in a cavernous tunnel stretching to the " +
            "west from here. A dark shaft, leads down into darkness. " +
            "A huge chain runs from the shaft and, up, over a huge " +
            "wooden cogwheel mounted on an iron axle, anchored in " +
            "solid stone. The links of the chain fit over teeth big " +
            "as tree trunks, then the chain stretches out, dissapearing " +
            "into the tunnel west from here. The walls in here look " +
            "very smooth.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT, 0);

   add_item("shaft", "The shaft leads down into darkness. It doesn't " +
            "lead vertically down, but slants to the east. Maybe it's " +
            "possible to climb down the chain.\n");

   add_item("chain", "A huge chain made of steel links. each chain " +
            "link as high as a grown human, and thicker than a leg.\n");

   add_item("cogwheel", "A large wooden cogwheel with teeth as big as " +
            "tree trunks. mounted on a iron axle.\n");
 
   add_item("axle", "The axle around which the cogwheel can turn. It " +
            "keeps the cogwheel in place, solidly anchored into the " +
            "stone walls of the tunnel.\n");

   add_item(({"wall", "walls", "north wall"}), "@@wall_descr");
 
   add_search("north wall", 3, "find_door", 1);

   add_exit(WALL_LEVEL + "chainchamber2", "west", 0);
}      


void
init()
{
   ::init();
   add_action("climb_chain", "climb");
}


int
climb_chain(string dir)
{
   if (dir == "down" || dir == "down chain" || dir == "down the chain")
   {
      write("You climb carefully down the chain.\n");
      say(QCTNAME(TP) + " climbs down the chain.\n");
      down_room->someone_arrives(TP);
      TP->move_living("M", WALL_LEVEL + "chainshaft4", 0, 0);
      return 1;
   }
    NF("Climb where?\n");
   return 0;
}


string
wall_descr()
{
   string ret_str;

   ret_str = "The walls are made of almost equal sized blocks of " +
             "stones. They have been fitted very close together " +
             "giving the walls an appearance as if they are solid.";

   if (TP->query_skill(110) > 40)
   {
      ret_str += " The north wall seems to be somehow smoother " +
                 "than the south wall.";
   }
   ret_str += "\n";
   return ret_str;
}


mixed
find_door(object searcher, string what)
{
   if (hidden_door_found)
      return 0;

   if (searcher->query_skill(110) > 45)
   {
      add_exit(WALL_LEVEL + "gallery5", "north", 0);
      say(QCTNAME(searcher) + " discovers a hidden door in the " +
          "north wall.\n");
      hidden_door_found = 1;
      other_room->door_found();
      return "You discover a secret door in the north wall.\n";
   }

   return 0;
}


void
door_found()
{
   tell_room(TO, "Suddenly, with a scraping sound, " +
             "a hidden door in the north wall opens.\n");
   hidden_door_found = 1;
   add_exit(WALL_LEVEL + "gallery5", "north", 0);
}


int
query_hidden_door()
{
   return hidden_door_found;
}


void
someone_arrives(object who, int from)
{
   tell_room(TO, QCTNAME(who) + " arrives from the shaft.\n"); 
}
