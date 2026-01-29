#include "default.h"
inherit PORT_ROOM;

void reset_room();
void do_search();

int recently_searched;
object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Halfling Brewery");
    set_long("This room seems to be the source of the strange whirring "+
        "noise and more importantly, the fragrant aroma of beer. On the "+
        "far east end of the room, past long rows of conveyor belts is a "+
        "gigantic wooden contraption. An archway is to the west.\n");

    add_item(({"long rows","long row","rows","row","conveyor belts",
        "conveyor belt","belts","belt"}),
        "Large pieces of tanned hide that have been stretched over "+
        "wooden wheels. Moving along the belt are many beers, all of "+
        "which seem to be emerging from the machine in the east.\n");
    add_item(({"gigantic wooden contraption","gigantic contraption",
        "wooden contraption","contraption","machine"}),
        "A simply-looking object, roughly fifteen feet high and ten feet "+
        "wide. Alot of strange, unusual noises seems to be coming from "+
        "within. You can't quite tell if the sounds are artificial or "+
        "natural in nature. Two openings, both on opposite sides of the "+
        "object have beer bottles flowing into and out of them. From the "+
        "left opening a continuous flow of bottles full with beer passes "+
        "by, the right opening has a continuous flow of empty beer "+
        "bottles passing into the machine.\n");
    add_item(({"archway"}),"An opening that leads west into another "+
        "room.\n");

    add_exit(PORT + "s40", "west");
    reset_room();
}

void
reset_room()
{
    recently_searched = 0;
    
    if(!ob1)
    {
    ob1 = clone_object(PORT + "npc/hbworker1");
    ob1 -> move_living("xxx", TO);
    }
}

void
init()
{
    ::init();
    add_action("search","search");
}

int
search(string s)
{
    if(!s || s != "contraption")
        return 0;

    if(recently_searched)
    {
        write("You search the strange machine but only succeed in "+
        "finding some old dregs.\n");
        return 1;
    }

    write("You start to search the contraption.\n");
    say(QCTNAME(TP) + " searches the contraption.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

void
do_search()
{
    recently_searched = 1;
    write("You find a large foaming mug of stout beer!\n");
    say(QCTNAME(TP) + " takes something from the contraption.\n");
    clone_object(PORT + "obj/hbmbeer")->move(TP);
    return;
}

