#include "../default.h"
inherit CVAN_ROOM;

void reset_room();
void do_search();
int recently_searched;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Slave Overseer's Office");
    set_long("You enter the small building just north of the platform, the "+
      "air smells of sweat mingled with leather. Looking around you see a "+
      "very spartan room, with little in the way of furnishings. A small, "+
      "wooden desk lies on the far side. A window looks out to the south.\n");

    add_item(({ "wooden desk", "desk" }),
      "An ordinary-looking desk, there are a few papers scattered on the top.\n");

    add_item(({ "papers" }),
      "They look like documents on the day to day workings of the slave trade, "+
      "such as how many slaves were bought and sold, and to whom.\n");

    add_item(({ "window" }),
      "A small opening looking out to the south. Through the dirty glass you "+
      "can see the center of the Slave Market, mud-churned surface and all.\n");

    clone_object(CVAN + "door/wdoor1")->move(this_object());
    clone_object(OBJ + "torch")->move(this_object());

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
    write("You find a bag within the desk. The overseer must have left "+
      "it there.\n");
    say(QCTNAME(TP) + " takes something from the desk.\n");
    clone_object(OBJ + "lbag")->move(TP);
    return;
}

int
search_desk(string str)
{
    if(!str || str != "desk")
	return 0;

    if(recently_searched)
    {
	write("You find nothing in the desk except for some dustballs.\n");
	return 1;
    }
    write("You start to search the desk.\n");
    say(QCTNAME(TP) + " searches the desk.\n");
    set_alarm(4.0, 0.0, do_search);
    return 1;
}

void
init()
{
    ::init();
    add_action(search_desk, "search");
}
