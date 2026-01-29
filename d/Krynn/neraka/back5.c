#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit TANTALLON_INSIDE;

int beer;

create_tantallon_room()
{
    set_short("Back room");
    set_long(BS(
    	"You are in the back room of the Giants Inn. North you can see a lot " +
           "of giants and that bar, but no one is looking this way. All around you " +
    	"there are a lot of kegs of beer." +
    	"", SL));

    add_item("window", BS(
        "The window is an open hole. Through it you can see a big open " +
        "square.", SL));
    add_item(({"kegs", "kegs of beer"}), BS(
        "The kegs are massive in size, made of a stout dark wood, " +
        "and seem to be freshly imported.", SL));

    add_exit(TDIR + "tent5", "north", 0);

    reset_room();
}

reset_tantallon_room()
{
    beer = 3;
    if (!present("beer", TO))
    	clone_object(OBJ + "giant_beer")->move(TO);
}

init()
{
    ::init();
    if (!present("beer", TO) && (random(10) > 6) && (beer > 0))
    {
    	clone_object(OBJ + "giant_beer")->move(TO);
    	beer--;
    }

    ADA("enter");
    ADD("enter", "go");
    ADD("enter", "climb");
}

enter(str)
{
    NF(C(query_verb()) + " what?\n");
    if (str != "window")
        return 0;

    TP->move_living("through the window", TDIR + "city12");
    return 1;
}

