/*
 * Filename:		road1.c
 * Description: 	Area around Newports, Abanasinia
 *
 * Coded by:		Aridor, 03/95
 *
 * Revision history:
 * Oct 25 1999 by Boron: Added warfare support
 *
 */

#include "local.h"

inherit BASE_FILE;


void
create_newport_room()
{
    set_short("Crossroads");
    set_long("The main road you are standing on runs southwest and northeast. " +
	     "Further southwest it runs along the edge of a large forest and " +
	     "eventually disappears into distant hills. To your west a new " +
             "wooden structure has hastily been constructed, with a firebranded " +
             "sign indicating it is the 'Langtree Mercenaries Recruitment Office'. " +
	     "Looking northeast, you can see a bridge up ahead. A track " +
	     "branches off from the road to the east, leading to several small " +
	     "cottages, the village of Newports. Water can be seen beyond the " +
	     "village. A sign hangs from a pole.\n");

    add_item(({"firebranded sign"}), "Above the new building to your west is " +
        "a sign branded with the words 'Langtree Mercenaries Recruitment " +
        "Office'.\n");
    add_item(({"wooden structure","building","new wooden structure","office"}),
        "To your west is a newly constructed building consisting of a single " +
        "large room. Over the door is a sign branding it as the recruitment " +
        "office of the Langtree Mercenaries. You can enter the building by " +
        "heading west.\n");
    add_item("road","This is a gravel road, leading northeast and southwest.\n");
    add_item("gravel","It looks very ordinary.\n");
    add_item("track","An ordinary track, leading east to a couple of houses.\n");
    add_item(({"houses","cottages","village","newports"}),
	     "The few houses making up the village of Newports can be seen to " +
	     "the east, a track from here leads there.\n");
    add_item("water","This seems to be a quite large body of water, probably " +
	     "an ocean.\n");
    add_item("forest","The forest is quite some distance away, but can be seem " +
	     "very well, even from this distance. It lies far to the southwest.\n");
    add_item("bridge","The bridge to the northeast seems to span across a wide " +
	     "valley. You cannot see much more, unless you go northeast.\n");
    add_item("sign","It's a metal sign hanging from a wooden pole. A drawing " +
	     "and some words are painted on it.\n");
    add_item("pole","A normal wooden pole sticking up from the ground, about " +
	     "five feet high.\n");
    add_search("pole",-1,"You see that someone has carved the letters 'T&A' into " +
	       "the pole, whatever that means.\n");
    add_item("drawing","You see the following:\n" +
	     "        Solace    Que Shu\n" +
	     "              \\  /\n" +
	     "               |/\n" +
	     "               /\n" +
	     "You are here  X--Newports\n" +
	     "             /\n" +
	     "       Pax Tharkas\n");
    add_cmd_item(({"sign","words"}),"read","You see the following:\n" +
		 "        Solace    Que Shu\n" +
		 "              \\  /\n" +
		 "               |/\n" +
		 "               /\n" +
		 "You are here  X--Newports\n" +
		 "             /\n" +
		 "       Pax Tharkas\n");

    add_exit(TDIR + "road2","southwest",0,3);
    add_exit(TDIR + "village","east",0,3);
    add_exit(TDIR + "newport_recruitment","west",0,3);
    add_exit(TDIR + "bridge_end", "northeast",0,3);
}

