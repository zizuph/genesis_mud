/*
 * eroad5.c
 * Kahlen Road
 * by Alaron August 31, 1996
 * Noiseroom added by Jaypeg - 13Feb97
 * Rock chimney (vamp shortcut) added 18Feb97
 */

#include "defs.h"
#include "/d/Emerald/common/guild/vamp/guild.h"

inherit "/d/Emerald/kroad/vamp/lib/out_vamp_tellroom";

string
entchimney()
{
#ifdef VAMP_SHRINE_ENTRANCE
    if (!IS_MEMBER(TP) && !IS_WIZ(TP))
    {
#endif
	write( "You try to get into the chimney, but only manage to get "+
	  "some of your arm inside. You fall off the formation and land "+
	  "ungracefully.\n" );
	say( QCTNAME(TP)+" jumps onto the rock formation, but only manages "+
	  "to get an arm down into it before falling down and landing very "+
	  "ungracefully.\n" );
	return "";
#ifdef VAMP_SHRINE_ENTRANCE
    }
    else
	write( "You close your eyes and focus your subconscious, leaving "+
	  "your physical form to disperse into a mist, and quickly glide "+
	  "down through the narrow rock chimney below you.\n" );
    say( QCTNAME(TP)+" dissipates into a mist and floats down into "+
      "the rock chimney hidden amongst the weeds.\n" );

    TP->move_living("down the chimney", VAMP_AREA_DIR + "cavend", 1);

    return "";
#endif

}

void
create_ov_road()
{
    set_short("Coastal road");
    set_long("   You stand on a damp, dirt road which runs parallel to "+
      "the coastal edge bordered by enormous white and gray cliffs. "+
      "As the cliffs drop off to the south, they allow view of another "+
      "set of cliffs across the water. From the sounds of the rushing "+
      "water it seems there is a channel into the inlet to the west "+
      "running beneath these cliffs. The north side of the road "+
      "is bordered by low, overgrown greenery and vegetation. Further "+
      "back from the road to the north the greenery seems to rise "+
      "and expand until it becomes the edge of an enormous forest.\n\n");

    OUTSIDE;
    LIGHT(1);

    add_item( ({"cliffs", "south", "white cliffs", "gray cliffs",
	"white and gray cliffs"}),
      "The massive cliffs to the south drop off abruptly and slant "+
      "straight into the ocean channel. Across the narrow channel "+
      "another set of cliffs rises out of ocean, its white and gray "+
      "stone standing in majestic contrast with the deep blue color "+
      "of the ocean far below.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
	"vegetation", "greenery"}),
      "The greenery bordering the road's northern side is overgrown "+
      "and seems to stretch out over the road, reaching for the "+
      "salty moisture collecting on the edges of the cliffs to the "+
      "south. Amongst the various weeds and vines you notice several "+
      "types of plant life which you recognize.\nFurther back from "+
      "the road, the greenery seems to rise up out of the ground and "+
      "melt into the edge of a forest.\n");

    add_item( ({"flowers", "weeds", "vines", "plant life"}),
      "There are hundreds of flowers, weeds and other forms of "+
      "plant life growing among the green mass which you "+
      "recognize. You do notice, however, a dark shape amongst "+
      "the weeds.\n");

    add_item( ({"shape", "dark shape"}),
      "By peering closer, and groping through the weeds with your "+
      "hands, you become to understand the dark shape in the weeds "+
      "a little better. It seems to be the top of a rock formation, "+
      "the only part visible to you that breaks above the surface "+
      "and into the outdoors. This rock formation seems to be of the "+
      "shiny black rock that makes up most of the cliffs around here, "+
      "hard and sharp-edged. The top of the formation is smooth, "+
      "almost flat, and approximately in the middle is a hole big "+
      "enough only for you to put your hand in.\n");

    add_item( ({"hole", "chimney", "rock chimney"}),
      "The hole seems to be some kind of rock chimney, very narrow, "+
      "and you guess also very deep. The edges seem sharp but regular, "+
      "and a faint whisp of stale air is your only clue to where it "+
      "leads.\n");

    add_cmd_item( ({"chimney", "hole", "rock chimney"}),"enter", entchimney);

    add_exit(PATH + "eroad4", "west", 0, 1);
    add_exit(PATH + "eroad6", "east", 0, 1);

}

