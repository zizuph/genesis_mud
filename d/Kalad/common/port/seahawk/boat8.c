#include "../default.h"
inherit PORT_ROOM;

void reset_room();
void do_search();
int recently_searched;

void
create_port_room()
{
    set_short("Far corner of the Seahawk");
    set_long("This is the far corner of the ship's stern. This is the "+
      "side of the ship closest to the mainland Port District. Above you, "+
      "the sky is a brilliant navy blue in color, a perfect day for "+
      "sailing. In the corner a few feathers have been piled.\n");
    add_item(({"mainland","port district","district"}),"Peering over the ship's "+
      "side you can see the many wooden buildings of the port area of Kabal.\n");
    add_item(({"wooden buildings","buildings","building"}),"Little can "+
      "be made out from this distance.\n");
    add_item(({"sky"}),"The sky is crystal clear in all its beautiful "+
      "splendor.\n");
    add_item(({"feathers","feather"}),"They appear to be the plucked and "+
      "possibly dropped feathers of a seagull. Someone seems to have "+
      "arranged them into this pile.\n");
    add_item(({"pile"}),"A large number of feathers that have been "+
      "heaped together.\n");
    add_item(({"corner"}),"A pile of feathers lies there.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat1", "east");
    add_exit(PORT + "seahawk/boat9", "south");
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
    add_action("search_feathers","search");
}

int
search_feathers(string s)
{
    if(!s || s != "feathers")
	return 0;
    if(recently_searched)
    {
	write("Your search reveals nothing special.\n");
	return 1;
    }

    write("You start to search the feathers.\n");
    say(QCTNAME(TP) + " starts to search the feathers.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

void
do_search()
{
    recently_searched = 1;
    write("You find a shiny piece of gold foil!\n");
    say(QCTNAME(TP) + " takes something from the feathers.\n");
    clone_object(PORT + "obj/gfoil")->move(TP);
    return;
}

