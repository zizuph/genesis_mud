#include "default.h"
inherit PORT_ROOM;

void reset_room();
void do_search();
int recently_searched;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Warehouse");
    set_long("This large wooden enclosure is the interior of one of the "+
      "port district warehouses. The only light comes from several windows "+
      "high up in the southern wall. All about you are a myriad number of "+
      "large wooden crates, each bearing the same symbol.\n");
    add_item(({"several windows","windows","window"}),"Small, narrow windows that "+
      "let in a minimum of light.\n");
    add_item(({"large wooden crates","large crates","wooden crates","crates","crate"}),
      "From the size of the containers, you estimate their weight to be in the "+
      "hundreds of pounds. Each one bears a mark, indicating which company or group "+
      "it belongs to.\n");
    add_item(({"symbol","mark"}),"An image of a flute "+
      "has been placed on each crate.\n");
    add_item(({"southern wall","wall"}),"It holds up the warehouse.\n");
    add_exit(PORT + "s28", "south");
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
    add_action("search_crates","search");
}

int
search_crates(string s)
{
    if(!s || s != "crates")
	return 0;
    if(recently_searched)
    {
	write("Your search revealed nothing special.\n");
	return 1;
    }

    write("You start to search the crates.\n");
    say(QCTNAME(TP) + " starts to search the crates.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

void
do_search()
{
    recently_searched = 1;
    write("You find a ledger among the crates!\n");
    say(QCTNAME(TP) + " takes something from the crates.\n");
    clone_object(PORT + "obj/ledger")->move(TP);
    return;
}

