#include "defs.h"

inherit "/std/room";

public void
create_room()
{
    set_short("a darkened spiral stairway");
    set_long("You are on a darkened spiral stairway " +
        "that winds upwards through a narrow shaft " +
        "that appears to have been cut through solid " +
        "stone. Even the landings of the stairs " +
        "themselves look to be of one piece of stone, " +
        "there's not a seam to be found anywhere. " +
        "The stone itself, however, has spent many " +
        "years in this damp atmosphere, and it looks " +
        "like they have taken their toll, as the " +
        "stone is crumbling in a number of places. " +
        "The stairs are quite unremarkable, and " +
        "the only thing of any real note is the faint "+
        "sound of running water coming from down " +
        "the stairs.\n\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "catacomb_8", "up");
    add_exit(GROTTO + "tunnel_6", "down");
}
