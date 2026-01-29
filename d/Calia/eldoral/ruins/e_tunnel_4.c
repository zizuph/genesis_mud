#include "defs.h"

inherit STDROOM;

public void
create_room()
{
    set_short("inside a darkened tunnel");
    set_long("You are in a darkened tunnel beneath the " +
        "ruins of " + CASTLE_NAME + ". The tunnel is fairly " +
        "wide, with a low ceiling and walls cut from " +
        "solid stone. " +
        "The tunnel here is a three-way " +
        "intersection, of sorts. The main tunnel runs " +
        "east and west, opening into a large room " +
        "to the south.\n\n");

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
        "trickled down through cracks too fine to see.\n");
    add_item(({"stains", "mineral deposits", "deposits"}),
        "The stains bring a touch of colour to the drabness " +
        "of the walls, mottling them in shades of purple, red " +
        "and yellow.\n");
    add_item(({"floor", "ground"}),
        "The floor, like the wall and ceiling, is cut from " +
        "the surrounding stone, and smoothed expertly to " +
        "provide a good walking surface.\n");
    INSIDE;
    DARK;

    add_exit(RUIN + "e_tunnel_1", "east");
    add_exit(RUIN + "e_tunnel_5", "south");
    add_exit(RUIN + "e_tunnel_6", "west");
}