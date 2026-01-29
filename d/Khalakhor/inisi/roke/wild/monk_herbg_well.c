/*
 * monk_herbg_well.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  updated by Amelia 6/21/97:
*   to fix well, so it soaks when you drink from it
*  changing strategy a bit on holy water, adding a
*  pseudo-poison, if drunk by an undead
*  also updating herb search to standard herbsearch
*  and planting a wider variety of herbs each time
*  room is loaded (random set from roke_herbs.h)
*  reset_room fixed also, so herbs reset
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "wild/monk_herbg_base";

#include <stdproperties.h>
#include <macros.h>

#define HOLY_POISON (ROKEDIR + "obj/holy_poison.c")

int drink_msg();

void
create_herbg_room()
{
    set_short("At the well");
    set_long("You are at the center of the garden. " +
             "There is a well here and the plants around it appear " +
             "greener and more richly coloured than in the rest of " +
             "the garden. You notice that even the air, though it " +
             "is filled with life, is somehow more peaceful here.\n");

    add_exit("monk_herbg_ne", "northeast");
    add_exit("monk_herbg_nw", "northwest");
    add_exit("monk_herbg_se", "southeast");
    add_exit("monk_herbg_sw", "southwest");

    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(ROOM_M_NO_ATTACK, "This is a holy place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK, "This is a holy place!\n");

    add_item("well", "This is a holy well, with holy water.\n");
    add_item((({"ground", "bushes"})),
             "The ground is covered with grass and fragrant " +
             "herbs.\n");
}

int
drink_it(string s)
{
    object poison;
    NF("Drink what?\n");
    if (s != "water" && s != "holy water" &&
        s != "from well" && s != "water from well" &&
        s != "holy water from well")
        return 0;

    if (TP->query_prop_setting(LIVE_I_UNDEAD))
    {
        if (!present("_holy_poison_", TP))
        {
            write("You try to drink the holy water ... " +
                  "It burns you! Something is happening...\n");
            setuid();
            seteuid(getuid(TO));
            poison = clone_object(HOLY_POISON);
            poison->move(TP);
            return 1;
        }
        /* else if already has been poisoned
         */
        write("You choke as you try to drink more " +
              "of the holy water.\n");
        TP->command("choke");
        return 1;
    }

    if (TP->drink_soft(3000, 1))
    {
        TP->drink_soft(2000);
        drink_msg();
        return 1;
    }
    if (TP->drink_soft(1500, 1))
    {
        TP->drink_soft(1300);
        drink_msg();
        return 1;
    }
    if (TP->drink_soft(1000, 1))
    {
        TP->drink_soft(800);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(800, 1))
    {
        TP->drink_soft(600);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(600, 1))
    {
        TP->drink_soft(500);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(400, 1))
    {
        TP->drink_soft(300);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(300, 1))
    {
        TP->drink_soft(200);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(200, 1))
    {
        TP->drink_soft(150);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(100, 1))
    {
        TP->drink_soft(50);
        drink_msg();
        return 1;
    }

    if (TP->drink_soft(50, 1))
    {
        TP->drink_soft(25);
        drink_msg();
        return 1;
    }

    write("You can't drink any more holy water.\n");
    return 1;
}

int
drink_msg()
{
    write("As you take a long drink from the " +
          "holy well, you feel refreshed and at peace.\n");
    say(QCTNAME(TP) + " drinks some holy water.\n");

    return 1;
}

void
init()
{
    ::init();

    add_action(&drink_it(), "drink");
}
