#include "../default.h"
inherit PORT_ROOM;

void reset_room();
void do_search();
int recently_searched;

void
create_port_room()
{
    set_short("Weapon storage room");
    set_long("This is a small storage room for the weapons that the "+
      "guards don't presently require. The room itself is entirely bare of "+
      "furnishings. The only noteworthy thing here are the scratch marks "+
      "covering the walls.\n");
    add_item(({"walls","wall"}),"The plain wooden walls of the room are "+
      "covered with numerous scratch marks.\n");
    add_item(({"scratch marks","marks","mark"}),"The markings look to "+
      "be a tally of fight results between the guards and prisoners. You "+
      "note the apparent lopsidedness in the tally that favors the guards.\n");
    add_item(({"floor"}),"The bare wooden floor is made out of several "+
      "planks.\n");
    add_item(({"planks","plank"}),"Ordinary wooden planks that are found "+
      "all over the ship.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/ba2", "north");
    reset_room();
}

void
reset_room()
{
    recently_searched = 0;
}

void
init()
{
    ::init();
    add_action("search_floor","search");
}

int
search_floor(string s)
{
    if(!s || s !="floor")
	return 0;
    if(recently_searched)
    {
	write("You find nothing at all.\n");
	return 1;
    }

    write("You start to search the floor.\n");
    say(QCTNAME(TP) + " starts to search the floor.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

void
do_search()
{
    recently_searched = 1;
    write("You find a small key hidden in between the planks of the floor!\n");
    say(QCTNAME(TP) + " takes something from the floor.\n");
    clone_object(PORT + "obj/bronze_key")->move(TP);
    return;
}

