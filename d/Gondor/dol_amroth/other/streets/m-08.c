/*
 * other/streets/m-08.c
 *
 * By Skippern 20(c)01
 *
 * A pier where some military vessels dock.
 */
#include "../../defs.h"

inherit DOL_STD + "city.c";

/* Prototypes */
int theater();

public void
create_dol_amroth()
{
    set_short("a dirty street");
    set_extralines("The street goes right by the waterfront.");
    set_lastline("A large teather is seen to the southwest.");

    set_no_of_lamps(3);

    bay_tells();
    street_tells();
    add_tell("Waves splashes against the road foundations.\n");

    set_sounds("The waves crushes into the road foundments and makes " +
	"a buzzing sound mixed with the sound of sea gulls screaming in " +
        "the sky.");
    set_sound_detail("You can hear music and song coming from the large " +
	"building to southwest. It sounds like somebody is practicing for " +
	"a play.");
    
    add_exit(DOL_OTHER + "theather/l-09", "southwest", &theater(), 1);
    add_exit(DOL_OTHER + "pier/l-07", "northwest", 0, 1);
    add_exit(DOL_OTHER + "streets/n-08", "east", 0, 1);
    set_grate("down", DOL_SEWER+"m-08");

    reset_room();
}

int
theater()
{
    write("You thread silently as you enter the theater.\n");

    if (this_player()->query_wiz_level()) return 0;

    return 0;
}

void
reset_room()
{
    object o;

    ::reset_room();
    /*
    if (!present("poet"))
    {
	o = clone_object(DOL_NPC + "artist-poet");
	o->move(this_object());
    }
    */
}

void
init()
{
    ::init();
}
