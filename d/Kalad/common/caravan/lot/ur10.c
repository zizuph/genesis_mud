#include "../default.h"
inherit CVAN_ROOM;

void reset_room();
void do_search();

int recently_searched;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("The quarters of the priest");
    set_long("You are within the priest's private room.\n"+
      "This small room is devoid of any tasteful furnishings. The entire "+
      "room is filled with objects of horror. Covering the walls are aging "+
      "tapestries depicting unholy acts. The most prevalent symbol, however, "+
      "is the symbol of a dark sun. The only furnishings this room has are "+
      "a bookshelf, filled with strange books, a desk and chair, and a "+
      "small bed. The room is lit by a pair of torches mounted on the "+
      "western and eastern walls.\n");

    add_item(({ "objects" }),
      "Decapitated heads, fleshless skulls, and other horrible things can "+
      "be seen.\n");

    add_item(({"tapestries"}),
      "They depict dark warriors overrunning a small village, slaying men, "+
      "women and children indiscriminately.\n");

    add_item(({"bookshelf"}),
      "A large wooden bookshelf, filled to the brim with books of strange "+
      "appearances.\n");

    add_item(({"books"}),
      "The books seem normal at first...then it dawns on you! As you felt "+
      "the covers you realized that they were made not of leather, but of "+
      "hobbit and even gnomish skin!\n");

    add_item(({"desk"}),
      "An ordinary desk, used for paperwork.\n");

    add_item(({"chair"}),
      "A small chair directly behind the wooden desk.\n");

    add_item(({"bed"}),
      "Small and tidy-looking, this is where the priest must sleep.\n");

    add_item(({"torches"}),
      "Standard torches, the kind you find in your general store. They are "+
      "mounted on the side walls to provide light.\n");

    clone_object(CVAN + "door/urdoor3")->move(TO);

    reset_room();
}

void
reset_room()
{
    recently_searched = 0;
}

void
do_search()
{
    recently_searched = 1;
    write("You find a medallion of thanar inside the desk!\n");
    say(QCTNAME(TP) + " takes something from the desk.\n");
    clone_object(CVAN + "arm/ktmed")->move(TP);
}

int
search_desk(string str)
{
    if(!str || str != "desk")
	return 0;

    if(recently_searched)
    {
	write("All you find are a few papers detailing torture techniques, "
    +"you quickly put them back.\n");
	return 1;
    }
    write("You start to search through the desk.\n");
    say(QCTNAME(TP) + " starts searching through the desk.\n");
    set_alarm(4.0, 0.0, do_search);
    return 1;
}

void
init()
{
    ::init();
    add_action(search_desk, "search");
}
