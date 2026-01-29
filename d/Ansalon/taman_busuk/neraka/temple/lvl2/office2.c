/* This is a room which can be used as an office. It has a lockable door
 * for privacy.
 */

/* Navarre august 6th 2006, fixed typo, changed lie to lies. */

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
    set_long("This is a large semi-circular room. It is dimly lit and there " +
        "is a large wooden desk just beside the door. Behind the desk is a " +
        "large high-backed chair and several piles of papers lie neatly " +
        "stacked upon it. In front of the desk stand two smaller armchairs " +
        "and the floor is covered with a dark carpet.\n");

    add_item("desk", "The desk is large and made of dark stained oak. " +
        "A pile of scrolls lies stacked on it and beside the piles is an " +
        "inkpot and quill.\n");
    add_item("wood", "It is oak which has been stained dark by time and use.\n");
    add_item(({"pile", "scrolls", "pile of scrolls"}), "Severeal sealed " +
        "scrolls lie stacked in a neat pile on the desk.\n");
    add_item(({"seal", "seals"}), "The seals are dark red and unbroken.\n");
    add_item(({"pot", "inkpot"}), "The inkpot is black and otherwise " +
        "non-descript.\n");
    add_item(({"chair", "high-backed chair", "large chair"}), "The chair " +
        "is made of dark oak and has a high back with carvings. The seat is " +
        "covered with leather and it stands behind the desk facing out " +
        "towards the room.\n");
    add_item(({"back", "carvings"}), "The back of the chair is decorated " +
        "with carvings of dead roses with sharp thorns.\n");
    add_item(({"roses", "dead roses", "thorns"}), "They look very life like.\n");
    add_item("seat", "The seat of the chair is made of burgundy coloured " +
        "leather. It has become a little worn from use.\n");
    add_item("armchairs", "There are two armchairs placed infront of the " +
        "desk. They are made of black leather with high backs and comfortable " +
        "looking armrests.\n");
    add_item(({"carpet", "dark carpet"}), "A large black carpet lies on the " +
        "floor. It is made of wool.\n");
        

    set_chairs(({"large high-backed chair", "small armchair",
        "small armchair"}));

    door = clone_object( DOOR + "office2b.c" );
    door->move(this_object());
    desk = clone_object(TEMPLE + "lvl2/desk_office");
    desk->move(this_object());
    clone_object("/d/Ansalon/guild/pot/obj/diary")->move(desk);
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
