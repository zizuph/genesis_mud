#include "defs.h"

inherit GROTTOBASE;

public void
create_room()
{
    set_short("a dark grotto");
    set_long("You are in what appears to be a dark cave or " +
        "grotto of some sort. It extends off northwards, where " +
       "the ground seems visibly drier than it is right here. " +
        "Immediately to your south, a wide subterranean " +
        "lake extends off into darkness, and the only visible " +
        "way across it seems to be a narrow bridge that " +
        "ascends upwards into the darkness somewhere above " +
        "the dark waters of the lake.\n\n");

    INSIDE;
    DARK;
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_item(({"walls", "ceiling", "wall", "roof"}),
        "You stare intently towards where it should be, but " +
        "all of the walls, and the ceiling, are beyond the edge " +
        "of light, impossible to see.\n");
    add_item(({"floor", "ground"}),
        "The ground here dips slightly towards the lake, until " +
        "it's grey stone slips beneath the surface of the still, " +
        "cold waters of the underground lake.\n");
    add_item(({"water", "lake"}),
        "The still, black waters of the underwater lake spread " +
        "out southwards, as far as you can see. Which, you must " +
        "admit, isn't very far.\n");
    add_item(({"bridge"}),
        "Apparently the only way across the lake from here, the " +
        "bridge seems to have had better days. It's little more " +
        "that a couple thick ropes (now largely tattered), across " +
        "which have been lashed several short planks. To make " +
        "matters worse, it's not even a level bridge, it climbs " +
        "upwards to the south rather sharply.\n");

    add_exit(GROTTO + "grotto", "north");
    add_exit(GROTTO + "n_bridge", "south");
}
