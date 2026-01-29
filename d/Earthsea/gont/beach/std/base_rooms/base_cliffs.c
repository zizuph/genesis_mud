/*
 * Cliff base room
 * This file doesn't contain room descriptions, 
 * just item descriptions.
 * By Finwe, May 1997
 */

inherit "/d/Earthsea/std/room.c";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"

void create_cliffs();

void
create_earthsea_room()
{
    add_item(({"cliff", "cliffs"}),
      "The cliffs are made from hard limestone that has been " +
      "carved over the centuries by the fury of the elements.\n");
    add_item(({"caves", "holes", "niches", "cracks", 
	"crevices", "crevice", "clefts"}),
      "Holes, cracks, and niches have been carved into the " +
      "side of the cliffs by the raging sea wind. The holes " +
      "are generally clean from the constant wind, but some " +
      "of the protected cracks and niches have debris in them. " +
      "At the top of the cliffs, the cracks and niches are " +
      "used by various seabirds.\n");
    add_item("debris",
      "You can see twigs, leaves, grasses and other forest " +
      "debris blown into the cracks and niches by the wind.\n");
    add_item(({"twig", "twigs", "leaves", "leaf", "grass", 
	"grasses"}),
      "These are dried from the sun. They fill the holes and " +
      "cracks in the cliffs.\n");
    add_item(({"up", "sky"}),
      "The sky is gray and cloudy, the kind of sky sailors " +
      "dislike.\n");
    add_item(({"down", "ground", "path"}),
      "The ground is worn smooth by all the traffic that has " +
      "travelled this path.\n");
    add_item(({"sea", "ocean", "water"}),
      "You peer out to sea. It looks restless. Waves crash " +
      "against the base of the cliffs.\n");
    add_item("sand",
      "Sand that has been blown up here is scattered around " +
      "the edges of the cliffs.\n");
    add_item(({"birds", "seabirds"}),
      "Seagulls, puffins, albatrosses, and other seabirds " +
      "fly overhead as they fly to and from their nests in " +
      "the cliffs.\n");
    add_item("nests",
      "They are too high above you to see.\n");


    create_cliffs();
}
create_cliffs(){}

init()    
{
    ::init();
    add_action("air", "smell");
}

air(string s)
{
    NF("Smell what? The air?\n");
    if(!strlen(s) || !parse_command(s,TO,"[the] [sea] 'air'"))
	return 0;
    else
    { 
	TP->catch_msg("You breathe the fresh, salty sea "+
	  "air deep in your lungs, tasting it on your"+
	  " lips.\n");
	set_alarm(1.0, 0.0, &write("Mmmm.....\n"));
	set_alarm(2.0, 0.0, &say(QCTNAME(TP)+ " takes a "+
	    "deep breath, smiling happily.\n"));
	set_alarm(3.0, 0.0, &write("There is no place like"+
	    " the sweet lands of the Archipelago.\n"));
	return 1;
    }
}
