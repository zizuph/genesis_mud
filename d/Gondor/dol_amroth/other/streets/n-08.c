/*
 * other/streets/n-08.c
 *
 * By Skippern 20(c)01
 *
 * A pier where some military vessels dock.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("The street goes right by the waterfront.");
    set_lastline("A large teather is seen to the southwest.");

    set_no_of_lamps(2);
    reset_room();

    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    set_sounds("The waves crushes into the road foundments and makes " +
        "a buzzing sound mixed with the sound of sea gulls screaming in " +
	"the sky.");

    add_exit(DOL_OTHER + "streets/m-08", "west", 0, 1);
    add_exit(DOL_TRADE + "streets/o-09", "southeast", 0, 1);
}

void
reset_room()
{
    object o;

    ::reset_room();
    /*
    if (!present("singer"))
    {
	o = clone_object(DOL_NPC + "artist-singer");
	o->move(this_object());
    }
    */
}
