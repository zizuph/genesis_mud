inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
void reset_room();

void
create_room()
{
    set_short("In a lavish spacious bedroom");
    set_long("You have walked into a very spacious bedroom. There is "+
    "a large bed in one corner, alongside a giant tapestry. Paintings "+
    "adorn the black walls. In the center of the room, there is an "+
    "altar. Chests and dressers are lined up against another wall, "+
     "under a small window. A large oak desk is proped up against "+
    "another wall, next to the door. The room smells like pine.\n");
    add_item("walls","They are polished very well.\n");
    add_item("bed","The bed is covered with many plush, down-filled "+
    "blankets. The big, white pillows and covers contrast the general "+
    "blackness of the room.\n");
    add_item("tapestry","It is a large tapestry with a giant, golden "+
    "symbol of a dark sun.\n");
    add_item("paintings","You see many paintings of black-clad warriors "+
    "with platinum necklaces sacrificing demi-humans.\n");
    add_item("altar","A small altar, with little candles on it. It "+
    "looks like it is dedicated to the god Thanar.\n");
    add_item("chests","They are made of hard, black wood, with silver "+
    "bands of steel to renforced them. They are all locked.\n");
    add_item("dressers","Tall, wooden shelves and drawers, wich are "+
    "filled with clothes and other such articles.\n");
    add_item("window","A small window, framed in gold. You can see "+
    "the outside gardens through the clear glass. Sunlight streaks "+
    "through it, giving the room its light.\n");
    add_item("desk","A giant, black oak desk. You see many drawers "+
    "full of papers and pens in it. Books line the top part of it, "+
    "while spilled ink stains some of the parchments laying on it.\n");
    add_item("door","The door you came in through.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m17),"southwest",0,-1,0);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/alexander));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

