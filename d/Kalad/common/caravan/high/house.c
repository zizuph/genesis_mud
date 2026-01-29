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

    set_short("House");
    set_long("You are within a middle class home in the High Street area. "+
      "Looking about the room you see a large throw rug near the door "+
      "leading outside. A circular table lies near the corner aside a shiny "+
      "iron stove. Several chairs are at differing points around the room, "+
      "while in the east is a short hallway. Two windows are on the western "+
      "side of the room.\n");

    add_item(({ "large throw rug", "large rug", "throw rug", "rug" }), "A "+
      "red circular carpet that has been laid out at the entrance of this "+
      "home.\n");

    add_item(({ "door" }), "It leads outside.\n");

    add_item(({ "circular table", "table" }), "A wooden table used by the "+
      "occupants of this home to eat upon.\n");

    add_item(({ "shiny iron stove", "iron stove", "stove", "shiny stove" }), "A "+
      "brand new stove used for cooking. Above it is a small cabinet.\n");

    add_item(({ "small cabinet", "cabinet" }), "An ordinary wooden cabinet, it "+
      "doesn't seem to be locked.\n");

    add_item(({ "chairs" }), "These are what people sit on.\n");

    add_item(({ "short hallway", "hallway" }), "It leads to the east into "+
      "another room.\n");

    add_item(({ "two windows", "windows", "window" }), "Looking out you can see "+
      "High Street.\n");

    add_exit(CVAN + "high/s3", "out");
    add_exit(CVAN + "high/h1", "east");

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
    write("You find a tasty-looking pie inside the cabinet! What a treat!\n");
    say(QCTNAME(TP) + " takes something from the cabinet.\n");
    clone_object(OBJ + "pie")->move(TP);
}

int
search_cabinet(string str)
{
    if(!str || str != "cabinet")
	return 0;
    if(recently_searched)
    {
	write("You find nothing save for a few spiderwebs.\n");
	return 1;
    }
    write("You start to search the cabinet.\n");
    say(QCTNAME(TP) + " searches the cabinet.\n");
    set_alarm(4.0, 0.0, do_search);
    return 1;
}

void
init()
{
    ::init();
    add_action("search_cabinet", "search");
}
