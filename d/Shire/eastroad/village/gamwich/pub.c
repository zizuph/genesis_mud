
/* pub.c
 * Town of Gamwich
 * Local Pub
 * Adapated 23 February 1995 by Farlong
 */

/* Copied over from Quetzl's Esgaroth pub */
/* (Originally) */

inherit "/d/Shire/room";
inherit "/lib/pub";

#include "defs.h"

object st,hob1,hob2;

void
reset_room()
{
    if(!st)
    {
        reset_euid();
        st=clone_object(GAMWICH_DIR+"npc/storyteller");
        st->arm_me();
        st->move(TO);
    }

    if(!hob1)
    {
        reset_euid();
        hob1=clone_object(ER_DIR+"npc/femhobbit");
        hob1->arm_me();
        hob1->move(TO);
    }

    if(!hob2)
    {
        reset_euid();
        hob2=clone_object(ER_DIR+"npc/mhobbit");
        hob2->arm_me();
        hob2->move(TO);
    }
}

void
create_room()
{
    set_short("The Golden Wheelbarrow Pub");
    set_long("This is the Golden Wheelbarrow Pub, a local "+
        "bar where the residents of Gamwich come to relax after a hard "+
        "day's work.  The building is wooden, with a thatched roof-- "+
        "one of the only above-ground structures around here, seeing "+
        "as how most folks reside in their coisy hobbit-holes, "+
        "or smials.  "+
        "A large menu occupies one wall, and "+
        "the local storyteller, an old and retired hobbit, "+
        "can generally be found here spinning his tales, unless "+
        "he's fallen down drunk elsewhere.  Two doors exit the Golden "+
        "Wheelbarrow: one to the north, into the town square, "+
        "and a second "+
        "onto a path to the west.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(GAMWICH_DIR+"square_sw","north");
    add_exit(GAMWICH_DIR+"sw_path_1","west");

    add_drink(({"beer","gamwich beer","Gamwich beer"}),"beer",
        "Gamwich",500,15,150,"Gamwich beer","Gamwich beers",
        "This is a beer from the Golden Wheelbarrow Pub in "+
        "the hobbit-village of Gamwich.  It is a "+
        "deep yellow-brown in color, and looks quite "+
        "inviting.\n");

    add_drink(({"special","Wheelbarrow special",
        "wheelbarrow special","Wheelbarrow Special"}),"special",
        "Wheelbarrow",238,102,300,"Wheelbarrow special",
        "Wheelbarrow specials","This is the Wheelbarrow Special, "+
        "from the local tavern in the hobbit-village of "+
        "Gamwich.  It is said to be quite strong!\n");

    add_item("menu", "You could read it.\n");

    add_cmd_item("menu", "read", "You can buy the following things from us" +
        "(all purchases are final):\n\n" +
        "    Gamwich beer for 150 coppers\n" +
        "    Wheelbarrow special for 300 coppers\n");


    reset_room();

}

init()
{
    ::init();
    init_pub();
}
