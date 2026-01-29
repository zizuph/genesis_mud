/*
   Pax Tharkas, Valley.....

   main_gate.c
   -----------

   Coded ........: 95/04/05
   By ...........: Jeremiah

   Latest update : 95/07/27
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;

int    gate_is_open = 0;     /* 0 : gate is closed. */

void
create_pax_room()
{
   set_short("Outside gate of Pax Tharkas");
   set_long("@@room_descr");
	
   OUTSIDE;

   add_item(({"gate", "gates", "double gate"}), "These are huge iron " +
        "reinforced gates. They stand 6 times as tall as a grown man, "+
            "and 8 horses could easily ride next to each other through " +
            "them. The gates look extremely sturdy, and could probably " +
            "withstand serious and persistent ramming attempts. There are " +
            "no hinges or anything visible, indicating that the gates " +
            "open inwards.\n");

   add_item(({"tower", "towers"}), "At each side of the gate, a huge " +
            "tower rises high into the air. The stones these towers " +
            "are built of has been fitted very tightly together, making " +
            "the towers look like they were made of solid stone.\n");

   add_item("wall", "This wall connects the two tall towers of Pax " +
            "Tharkas. The stones this wall is built of are fitted " +
            "very tightly together, giving the wall an appearance " +
            "as if it was of solid stone. A large gate is set in " +
            "the middle of this wall.\n");

   add_item("road", "The road leads downwards, north, through the " +
            "curtain walls on the slopes in front of the fortress " +
            "and out into the valley. There are lots of tracks on " +
            "the road.\n");

   add_item("tracks", "Tracks from wheeled carts, horses and feet in " +
            "different sizes. They all lead to, or from, the fortress.\n");

   add_exit(VALLEY + "curtain_wall1", "north", 0);
}


void
init()
{
   ::init();
   add_action("do_knock", "knock");
   add_action("do_open", "open");
}


int
do_knock(string what)
{
   if((what == "gate") || (what == "on gate") ||
      (what == "gates") || (what == "on gates"))
   {
      write("You knock on the huge gates. Your knocking can barely " +
            "be heard. Nothing happens.\n");

      tell_room(TO, QCTNAME(TP) + " knocks on the huge gates. The " +
            "knocking can barely be heard. Nothing happens.\n", TP);

      return 1;
   }

    NF("Knock on what ?\n");
   return 0;
}


int
do_open(string what)
{
   if((what == "gate") || (what == "gates"))
   {
      write("The gates are impossible to open from this side.\n");
      return 1;
   }
   
   return 0;
}


string
room_descr()
{
   string ret_str;

   ret_str = "You are standing on a road in front of the mighty gates " +
             "of Pax Tharkas. To each side of you a huge tower rises " + 
             "high into the sky. The gates are solidly set in the center " +
             "of the wall connecting the two towers.";

   if(!gate_is_open)
      ret_str += " The gates are closed, and apparently they can only " +
             "be operated from the inside. There is nothing on this " +
             "side except their iron reinforced surface.";

   ret_str += " The road leads north, downwards, towards some curtain " +
             "walls on the slopes in front of the fortress.";
             

   if(gate_is_open)
      ret_str += " South, the road disappears through the open gates " +
             "into the fortress.";      

   ret_str += "\n";

   return ret_str;
}


void
gate_opens()
{
   tell_room(TO, "Suddenly, with a rumbling sound, the mighty gates " +
             "of Pax Tharkas swings open, revealing a large entrance " +
             "into the heart of the fortress.\n");

   add_exit(GROUND_LEVEL + "hollow_wall2", "south", 0);
   gate_is_open = 1;
}


void
gate_closes()
{
   tell_room(TO, "Suddenly, with a rumbling sound, the mighty gates of " +
             "Pax Tharkas close, effectively sealing off the entrance " +
             "to the fortress.\n");

   remove_exit("south");
   gate_is_open = 0;
}

