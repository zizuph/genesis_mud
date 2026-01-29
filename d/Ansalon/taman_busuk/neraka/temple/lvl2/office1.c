/* This is a room which can be used as an office. It has a lockable door
 * for privacy.
 */

/* Navarre August 06 2006, fixed typo, leater changed to leather */

#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";
inherit TEMPLE + "lib/seats.c";

void
create_temple_room()
{
    object door, desk;
    

    ::create_temple_room();

    set_short("A small office");
    set_long("This is a small square room. It is dimly lit and there " +
        "is a large wooden desk opposite the door. Behind the desk is a " +
        "large high-backed chair and several piles of papers lie neatly " +
        "stacked upon it. A rug woven in heavy dark wool lies on the " +
        "floor and a black iron candleholder stands in a corner shedding " +
        "some faint light.\n");

    add_item("desk", "The desk is large and made of dark stained oak. " +
        "A pile of scrolls lie stacked on it and beside the piles is an " +
        "inkpot and quill.\n");
    add_item("wood", "It is oak which has been stained dark by time and " +
        "use.\n");
    add_item(({"pile", "scrolls", "pile of scrolls"}), "Several sealed " +
        "scrolls lie stacked in a neat pile on the desk.\n");
    add_item(({"seal", "seals"}), "The seals are dark red and unbroken.\n");
    add_item(({"pot", "inkpot"}), "The inkpot is black and otherwise " +
        "non-descript.\n");
    add_item(({"quill", "black quill", "goose quill"}), "Beside the inkpot " +
        "lies a black goos quill for writing.\n");
    add_item(({"chair", "high-backed chair", "large chair"}), "The chair " +
        "is made of dark oak and has a high back with carvings. The seat " +
        "is covered with leather and it stands behind the desk facing out " +
        "towards room and door.\n");
    add_item(({"back", "carvings"}), "The back of the chair is decorated " +
        "with carvings of dead roses with sharp thorns.\n");
    add_item(({"roses", "dead roses", "thorns"}), "They look very life-like.\n");
    add_item("rug", "This rug is made of dark red wool and it is thick. " +
        "It gives the room the feeling of comfort.\n");
    add_item(({"candleholder", "black candleholder", "iron candleholder",
        "holders"}), "The candleholder is three foot high. It has six holders " +
        "for candles with one larger in the centre and five smaller ones evenly " +
        "spaced in a circle around it.\n");
    add_item("candles", "The six candles are burning, giving off a faint " +
        "light to the room.\n");
    add_item("corner", "A black candleholder stands in the corner.\n");

    set_chairs("large high-backed chair");

    door = clone_object( DOOR + "office1b.c" );
    door->move(this_object());
    desk = clone_object(TEMPLE + "lvl2/desk_office");
    desk->move(this_object());
    clone_object("/d/Ansalon/guild/pot/obj/priest_board")->move(desk);
}

void
leave_inv(object ob, object to)
{
    seats_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

void
init()
{
    ::init();
    seats_init();
}
