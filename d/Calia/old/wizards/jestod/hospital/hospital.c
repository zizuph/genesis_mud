/*
 *  hospital.c --- Jestod Gelan Hospital
 *
 *  History :
 *    5/12/92 - Scar removal (Jestod)
 *
 *  Exits :
 *
 *
 */

inherit "/std/room";
inherit "/lib/trade";
#include "/d/Dville/gelan/gelan.h"
#include <stdproperties.h>
#define have_scar(x) (this_player()->query_scar() & x)

void
create_room()
{
    ::create_room();
    set_short("Gelan General Hospital");
    set_long(break_string("Just your basic non-descript hospital right now " +
        "with no real description --- don't worry --- I'll put one in " +
        "as soon as I come up with one that I'm happy with.  Oh, and by the " +
	"way, there's a sign on the wall.\n", 75));
    config_default_trade();
    set_money_give_reduce(({0,0,0,0}));
    add_item("sign", "" +
        " Gelan General Hospital\n" +
        "+======================+\n" +
        "          RATES\n" +
        "  Scar removal: 10gc\n" +
        "+======================+\n" +
        "       INSTRUCTIONS\n" +
        "  Scar removal:\n" +
        "   Type \"remove <scar>\"\n" +
        "   where <scar> is the\n" +
        "   location of the scar\n");
    add_exit(TOWN_ROOMS + "road_w", "east", 0);

    add_prop(ROOM_I_INSIDE, 1);
}

void
init()
{
    ::init();
    add_action("do_remove", "remove", 0);
}

int
do_remove(string arg)
{
    int scarnum, *payarr;


    if (arg == "left leg") scarnum = 1;
    else if (arg == "right leg") scarnum =2;
    else if (arg == "nose") scarnum = 4;
    else if (arg == "left arm") scarnum = 8;
    else if (arg == "right arm") scarnum = 16;
    else if (arg == "left hand") scarnum = 32;
    else if (arg == "right hand") scarnum = 64;
    else if ((arg == "forhead") || (arg == "forehead")) scarnum = 128;
    else if (arg == "left cheek") scarnum = 256;
    else if (arg == "right cheek") scarnum = 512;
    notify_fail("I'm sorry, but you don't have a scar there.\n");
    if (!have_scar(scarnum)) return 0;
    notify_fail("You can't afford our services.\n");
    if (can_pay(1440, this_player()))
    {
        payarr = pay(1440, this_player());
        write(break_string("You hand over you " + text(payarr) +
	    " and the scar on your " + arg +
	    " is removed by the expert team of surgeons here.  You receive " +
	    text(split_values(money_merge(payarr) - 1440)) +
	    " in change.\n", 70));
        this_player()->set_scar(this_player()->query_scar() - scarnum);
        return 1;
    }
    else return 0;
}
