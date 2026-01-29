/*
 * GRAVEYARD7.c
 * A grave site in the Emerald Graveyard
 * 
 * by Alaron July 29, 1996
 */

#include "default.h"
#include <macros.h>

inherit "/std/room";

void
create_room()
{
    set_short("Graveyard");
    set_long("   The chill wind whistles quietly as it brushes against "+
	     "the stone side of a large stone tomb. The tomb rests "+
	     "mostly in the side of a knoll. Its enormous, stone "+
	     "door stands slightly ajar as it has long since come off "+
	     "of its rusted iron hinges. A thick, dark fog surrounds "+
	     "the tomb in a shroud of dread and despair, instilling you "+
	     "with such forboding that you feel as though you should "+
	     "turn and run in the other direction. A few small gravestones "+
	     "lie cracked and battered near the side of the tomb, marking "+
	     "where the tomb is separated from the rest of the hundreds "+
	     "of grave markings in the sprawling, dark green field of "+
	     "death.\n\n");

    add_item( ({"tomb", "stone tomb", "large tomb", "large stone tomb"}),
	     "It is a huge tomb resting almost completely in the side "+
	     "of a small hill. It has obviously been around for quite "+
	     "some time, the original death date above the stone "+
	     "door has eroded away with the dampness and the rain, leaving "+
	     "only a faint hint of the age of this tomb. The massive "+
	     "stone door leans slightly to the side, having fallen off "+
	     "of its long-ago rusted iron hinges.\n");

    add_item( ({"door", "stone door", "large stone door", 
		"massive stone door", "large door", "hinges", "iron hinges"}),
	     "The massive stone door has long ago fallen off of its "+
	     "rusted iron hinges and now leans lopsided against the "+
	     "front of the tomb. The leaning door creates a small "+
	     "opening in the tomb revealing the darkness within.\n");

    add_item("opening",
	     "It is a small opening in the tomb formed by the leaning "+
	     "stone door having fallen off of its hinges. It looks "+
	     "almost large enough to crawl through.\n");

    add_item( ({"fog", "mist", "thick fog", "dark fog", "thick dark fog"}),
	     "A thick, dark fog hangs ominously over the entire "+
	     "area, blanketing the tomb in an overcast of sadness "+
	     "and despair.\n");

    add_item( ({"stones", "gravestones", "grave stones"}),
	     "The small gravestones are broken, cracked and neglected. "+
	     "Most of them don't even have enough of their original "+
	     "stone remaining to accurately display the names of "+
	     "the people buried beneath.\n");

    add_item( ({"field", "graveyard", "yard", "sprawling field"}),
	     "The dark green, damp graveyard expands in hills and "+
	     "dips in all directions, revealing before you a seemingly "+
	     "endless sea of gravestones and death.\n");

    add_exit(GRAVEYARD_DIR + "graveyard8", "south");
    add_exit(GRAVEYARD_DIR + "graveyard5", "north");
    add_exit(GRAVEYARD_DIR + "graveyard6", "west");
}

init()
{
    ::init();
    add_action("crawl", "crawl");
}

int
crawl(string str)
{
    if (!str) return 0;

    if ((str!="through opening") && (str!="in opening") &&
	(str!="opening") && (str!="through door") &&
	(str!="into tomb"))
    {
	notify_fail("Crawl where?\n");
	return 0;
    }

    write("You get down on your belly and squirm into the tomb "+
	  "underneath the leaning stone door ...\n\n");
    say(QCTNAME(this_player())+ " gets down on "+HIS_HER(this_player())+
        " belly and squirms into the tomb underneath the leaning stone "+
	"door.\n");
    this_player()->move_living("M",GRAVEYARD_DIR+"atomb1",1,0);
    return 1;
}

    


