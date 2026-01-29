#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Street of chains");
    set_long("This darkened street you are walking along is the Street of "+
      "Chains, so named because individuals headed for the slave market are "+
      "held prisoner in the buildings aside this road. A large intersection "+
      "can be seen just to the north, while the Street of Chains continues "+
      "southward, deeper into the city. Refuse litters the ground here.\n");
    set_time_desc("The vicinity is devoid of activity.\n", "There seems to be a "+
      "lot of activity near the building in the east, despite the late hour.\n");

    add_item(({ "street" }),
      "The surface of the street appears to have been paved with cobbles at "+
      "one point, but all that is visible now are a few crumbling "+
      "cobblestones, and most of these are covered by mud and other "+
      "filth.\n");

    add_item(({ "buildings" }),
      "The buildings are all small wooden structures, with few being two "+
      "stories or higher. All of the buildings are in desperate need of "+
      "repair. One building in particular, to the east, catches your attention.\n");

    add_item(({ "east building", "east", "eastern building" }), "A small "+
      "wooden building that looks in slightly better condition than the "+
      "other ones along this street. A small sign is posted at the "+
      "entrance.\n");

    add_item(({ "sign", "@@sign" }), "There are lots of readable words on it.\n");

    add_item(({ "refuse" }),
      "It reeks soooo horribly that you cannot get close enough to get a "+
      "good look at it!\n");
    add_cmd_item(({ "east", "building" }), "enter", "@@enter");
    add_cmd_item("building", "enter", "@@enter");

    add_exit(CVAN + "chains_wayfar", "north");
    add_exit(CVAN + "chains/s2", "south");
    set_alarm(10.0, 120.0, "events");
}

string
sign()
{
    return "\n" +
    "                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"+
    "                    !!!   Madame Salvira's   !!!\n"+
    "                    !!!        House         !!!\n"+
    "                    !!!          of          !!!\n"+
    "                    !!!       Pleasure       !!!\n"+
    "                    !!!   open at all hours  !!!\n"+
    "                    !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
}

string
enter()
{
    write("You pass through the unlocked door of the building.\n");
    set_dircmd("building");
    TP->move_living("into a shady-looking building", CVAN + "chains/wh");
    return "The smell of heavy perfume greets you.\n";
}

void
events()
{
    tell_room(TO, "Faint giggling sounds from the building in the east.\n");
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
