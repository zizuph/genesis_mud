/*
 * f30
 * Grave of the First
 * Forest of Coramar
 * Alaron March 1998
 */

#include "/d/Emerald/defs.h"
#include "dirheader.h"
#include "coramar.h"

inherit BASEGRAVE;

void
create_graveyard()
{
    set_long("   You are standing in what appears to be a graveyard of some kind. The "+
	"small clearing in the middle of the dense, mist-covered forest seems to be "+
	"unaffected by the mist. The dense, gray cloud hovers and swirls at the edge "+
	"of the iron fence but seems unable to move beyond. The black iron fence is "+
	"short and more decorative than functional. It serves more as a boundary line "+
	"indicating the edge of the graveyard. The clearing is made of perfectly trimmed, "+
	"straight lines and light, neatly trimmed grass. A small break in the fence "+
	"leads to a branch of the forest path leading southeast into the swirling, "+
	"ominous mist. There is a wooden sign here.\n\n");


    add_item( ({"sign", "wooden sign", "wood sign"}),
	"The wooden sign is made of a dark wood. The wood has a glaze-like, hard "+
	"material surrounding it that probably protects it from the surrounding "+
	"moisture. There is a brass plaque hammered into the wooden sign.\n");

    add_item( ({"plaque", "brass plaque"}),
	"The brass plaque is a thin piece of brass that has been carefully hammered "+
	"into the wood with small, brass wide-head pegs. There has been some "+
	"writing etched into the face of the brass plaque.\n");

    add_item( ({"writing", "etched writing", "etching"}),
	"The writing etched into the plaque is beautiful. The craftsmanship involved "+
	"in creating such flowing strokes and perfect lines and lettering is "+
	"amazing. The skill involved in creating these letters makes the writing "+
	"very easy to read.\n");

    add_cmd_item( ({"writing" , "etched writing", "etching", "sign", "wooden sign",
	"plaque", "brass plaque"}),
	"@@read_plaque@@");

    add_fexit(CORAMAR+"f31", "southeast", 0);
    add_fexit(CORAMAR+"f29", "west", 0);
}

string
read_plaque()
{
   string rc;
   string rcn;

   rc = this_player()->query_race();

   if (rc == "elf")
	rcn = "elven";
   else if (rc == "dwarf")
 	rcn = "dwarven";
   else if (rc == "human")
	rcn = "human";
   else if (rc == "goblin")
	rcn = "goblinish";
   else
	rcn = "your native language";

   if (DRUID_MEMBER(this_player()))
	rcn = "tohk'mai'an";

   return "The writing is extremely pretty and the strokes and curves of the lettering "+
	"painstakingly carved into the brass so as not to distort any of the letters "+
	"in the metal. It reads:\n"+
	"         Here Lie\n\n"+
	"         Those Who came before\n"+
        "         Those who are With us now\n"+
	"         Those who will show us the way\n\n"+
	"         Those who are the First.\n\n"+
	"What pleases you most is that the words have been perfectly written and "+
	"composed in "+rcn+".\n";
}