inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("A small study");
    INSIDE;
    set_long("You find yourself in a small study room. There is a "+
    "window on the north wall, which light streams through. Under "+
    "the window, a large desk sits. In the center of the room, "+
    "a large table is placed, with many chairs around it. On another "+
    "wall, a bookcase is placed. The floor is made of black and "+
    "white tiles, which go nicely with the black walls of this room. "+
    "There are a few paintings on the walls.\n");
    add_item("desk","The desk is fairly large, and is made out of "+
    "red oak wood. It is polished to a shine. A few drawers, which are "+
    "locked, are under it. There are a few scattered books lying on "+
    "the desk, as well as a few pens and papers.\n");
    add_item("window","A nice-sized window, in which you can see "+
    "the garden of this estate. Fresh summer breezes waft through.\n");
    add_item("books","A few books, not very intresting.\n");
    add_item(({"pens","papers"}),"The pens and papers are what you "+
    "expect them to be, not very intresting.\n");
    add_item("table","The table is made of black oak wood, and is bare "+
    "save for a small picture on it.\n");
    add_item("chairs","The chairs are made of black oak wood, and have "+
    "soft white cusions on them.\n");
    add_item("bookcase","A large bookcase made of white oak wood, and "+
    "with many volumes of books placed in it.\n");
    add_item("floor","The floor is made of smooth tile.\n");
    add_item("walls","The walls are constructed of sturdy, smooth black "+
    "oak.\n");
    add_item("picture","It is a picture of a giant forest, in which "+
    "a lone dark sun rises over it.\n");
    add_item("paintings","There are few paintings, many of which "+
    "depict violent battle scenes.\n");

    add_exit(NOBLE(alexander/m1),"south",0,-1,-1);
}
