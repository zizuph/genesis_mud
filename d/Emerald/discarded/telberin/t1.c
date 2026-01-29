/*
 * Precinct with the Temples In It.
 * Re-Described, Updated to point to new Temple of Telan-Ri
 *
 * By Alaron August 14, 1996
 */

inherit "/std/room";

#include "default.h"

void
create_room()
{
   set_short("Temple precinct");
   set_long("   Standing in a cobblestoned square surrounded by a low "+
	    "stone wall, you notice an overwhelming sense of peace "+
	    "and serenity here. All of the noises of the city seem to "+
	    "drift silently past, not disturbing the quiet solitude of "+
	    "this area. At the end of the cobblestoned square lie three "+
	    "large temples. On either side, the small temples are circular "+
	    "stone buildings with gold and silver edge trimming and a "+
	    "plain-looking door. The temple in the center, at the northeast "+
	    "end of the square, towers majestically above the scene, "+
	    "proudly displaying its marble columns and arched entry for "+
	    "all to see. Lavish red rugs drape the steps of each of the "+
	    "temples, coming to a halt in the middle of the square.\n\n");

    add_item( ({"wall", "stone wall", "low stone wall"}),
             "It is a simple, stone wall. The wall encloses the cobblestoned "+
             "square at waist-height.\n");

   add_item( ({"north temple", "north", "east temple", "east"}),
	    "The north and east temples are temples of the lesser, or "+
	    "less-worshipped Gods. They are simple, single-room structures "+
	    "with intricate carvings and ornate gold and silver imbedded "+
	    "exterior trims.\n");

   add_item( ({"northeast temple", "telan-ri temple", "temple of telan-ri",
	       "telan-ri"}),
	    "The temple in the center of the precinct to the northeast "+
	    "is absolutely magnificent. It reaches several stories into "+
	    "the sky, towering over the nearby buildings of Telberin. Its "+
	    "lavish, gold- and silver-trimmed exterior gleams in the "+
	    "sunlight as if it were radiating the light itself. Four "+
	    "large columns support the front overhang of the giant "+
	    "temple of Telan-Ri.\n");

   add_item( ({"column", "columns", "large columns", "overhang", 
	       "front overhang"}),
	    "The front overhang of the temple of Telan-Ri is breathtaking. "+
	    "The whole structure is made out of one single piece of "+
	    "black speckled marble, but carved smoothly and intricately "+
	    "to give it the appearance of a column support structure. The "+
	    "architecture, design and beauty of the temple are staggering.\n");

   add_item( ({"fires", "coal fires", "coal", "warmth"}),
	    "The are four coal fires burning at each corner of the "+
	    "precinct. You suppose that they have some form of "+
	    "ceremonial value, and also enjoy the added warmth as this "+
	    "section of the precinct seems much colder than other places "+
	    "in Telberin.\n");

   add_item("temple",
	    "Which temple do you wish to look at? The north, northeast "+
	    "or east temple?\n");

   add_item( ({"rug", "rugs", "red rugs", "lavish rugs", "lavish red rugs"}),
	    "The lavish red rugs climb the steps toward each of the "+
	    "three temples. None of the people walking in or out of the "+
	    "temples seem to be stepping on the rugs. Perhaps only the "+
	    "clerics and priests are allowed to tread on the carpets?\n");
   
   add_exit(THIS_DIR + "t4","north");
     add_exit(THIS_DIR + "t3", "northeast"); 
   add_exit(THIS_DIR + "t2","east");
   add_exit(AVENUE_DIR + "ave23","southwest");
}

int
temple_block()
{
    write("The temple seems to be undergoing some restoration work "+
          "at the moment. Perhaps it will be open to visitors again "+
          "soon.\n");
    return 1;
}
