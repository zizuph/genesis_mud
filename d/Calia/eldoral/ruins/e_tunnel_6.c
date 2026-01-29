#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("inside a darkened tunnel");
    set_long("You are in a darkened tunnel beneath the " +
        "ruins of Castle Chimera. The tunnel is fairly " +
        "wide, with a low ceiling. The walls and ceiling " +
        "are smoothly cut, apparently through solid " +
        "stone. This appears to be a dead end room, " +
        "absolutely featureless except for some marks " +
        "on the west wall that could have once been " +
        "where something was mounted on it.\n\n");

    add_item(({"walls"}),
        "The walls " +
        "are smoothly cut, apparently through solid " +
        "stone, and the only evidence of the age of " +
        "the structure are the networks of cracks that " +
        "span their surfaces, and stains of mineral " +
        "deposits where water has trickled in through " +
        "the cracks over the years. Mounted on the " +
        "walls at regular intervals, heavy iron sconces, " +
        "now coated with rust, hang in somber silence.\n");
    add_item(({"sconces"}),
        "The torches they once held now long gone, the " +
        "only evidence of their purpose lie in long " +
        "black scorch marks on the walls to which the " +
        "are bolted.\n"); 
    add_item(({"ceiling", "roof"}),
        "The low ceiling has been cut from solid stone, and " +
        "like the walls bears no features except some " +
        "stains produced by mineral deposits as water " +
        "trickled down through cracks to fine to see.\n");
    add_item(({"stains", "mineral deposits", "deposits"}),
        "The stains bring a touch of colour to the drabness " +
        "of the walls, mottling them in shades of purple, red " +
        "and yellow.\n");
    add_item(({"floor", "ground"}),
        "The floor, like the wall and ceiling, is cut from " +
        "the surrounding stone, and smoothed expertly to " +
        "provide a good walking surface.\n");
    add_item(({"marks", "sockets"}),
        "The marks on the wall outline the shape of a " +
        "large rack or shelf of some sort, empty sockets " +
        "which may have once contained mounting pegs.\n");

    INSIDE;
    DARK;

    add_exit(RUIN + "e_tunnel_4", "east");
}