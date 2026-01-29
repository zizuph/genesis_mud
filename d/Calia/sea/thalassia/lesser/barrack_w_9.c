
/* 	Guard Barracks in the Lesser Zone of Thalassia

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

#define NUM 2

inherit "/d/Calia/std/water_room";
inherit "/lib/pub";

object *guard = allocate(NUM);

void
make_monster(int i)
{
    guard[i] = clone_object(SEA_CREATURES+"ori_triton");
    guard[i]->equip_me();
    guard[i]->move(TO);
    tell_room(TO, QCTNAME(guard[i]) + " arrives.\n");
}

void
reset_room()
{
    int i;

    for (i=0; i < NUM; i++)
        if (!guard[i])
            set_alarm(0.5, 0.0, &make_monster(i));
}

void
create_water_room()
{
    set_short("Guard barracks pub");
    set_long("You are in the pub, where the guards of this "+
        "barracks come to drink and relax. There is a large "+
        "counter, behind which you see a bartender. On the "+
        "counter you see a pricelist.\n");

    add_item("bartender", "The bartender is a fairly tall "+
        "triton. He looks fairly muscular and is looking at "+
        "you with caution. Perhaps you shouldn't start any "+
        "trouble in here.\n");

    add_item("counter","The counter is made from some type of heavy "+
        "wood, weighted down with a stone bottom so it does not "+
        "float away.\n");

    add_item(({"pricelist","menu"}),"It appears to have the prices of "+
        "all of the things you can order here. Perhaps you should "+
        "read it.\n");

    add_cmd_item("pricelist","read","@@read");
    add_cmd_item("menu","read","@@read");

    add_drink(({"beer","beers","dark beer","dark beers"}),
        "beer","dark",100,4,12,0,0,
        "It's a refreshing beer.\n",0);

    add_drink(({"grog","grogs","dark grog","dark grogs"}),
        "grog","dark", 300, 30, 120, 0, 0,
        "Its very dark and almost totally black.\n",0);

    add_drink(({"moonshine","moonshines","pale moonshine","pale moonshines"}),
        "moonshine","pale", 70, 50, 210, 0, 0,
        "This home-brewed alcohol looks very strong.\n",0);

    add_food(({"meat","fish","fish meat"}),
        "meat","fish", 65, 80, "strip of fish meat",
        "strips of fish meat",
        "It's a small strip of fish meat.  It looks edible.\n",0);

    add_food(({"scallop","scallops","small scallop","small scallops"}),
        "scallop","small",  30, 25, "small scallop","small scallops",
        "It is a small scallop.\n",0);

    add_food(({"crab","leg","crab leg","crab legs","legs"}),
        "leg","crab", 100,100,0,0,
        "It is a fairly large pink crab leg.\n",0);

    add_food(({"tail","lobster","tails","lobster tail","lobster tails"}),
        "tail","lobster",150,150,0,0,
        "It is a large cooked lobster tail.  It looks very delicious.\n",0);

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
    add_swim_exit(THALL+"barrack_w_8","west",0,1);
    set_alarm(1.0, 0.0, reset_room);
}

public int
clean_up()
{
    int i;

    for (i=0; i < NUM; i++)
        if (guard[i])
            return 1;

    remove_object();
}

void
init()
{
    ::init();
    init_pub();
}

int
read(string str)
{
    write("\n"+
        "    Dark beer                     12 cc\n"+
        "    Dark Grog                    120 cc\n"+
        "    Pale Moonshine               210 cc\n"+
        "\n"+
        "    Small Scallop                 25 cc\n"+
        "    Fish Meat                     80 cc\n"+
        "    Crab Leg                     100 cc\n"+
        "    Lobster Tail                 150 cc\n"+
        "\n"+
        "Try 'buy beer with gold' if you want to specify what\n"+
        "coin type to pay with, or 'buy 10 beer' would get\n"+
        "you ten beers from the bar.\n\n");
    return 1;
}

