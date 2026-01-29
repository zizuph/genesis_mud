#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Office");
    set_long("This small back room is where the shipping clerk keeps "+
      "all his records of the daily shipping activities in the Port District. "+
      "The walls are covered with shelves filled with many rolled "+
      "parchments and the several desks scattered around the room are "+
      "similarly covered. A small chair sits amongst the rampant chaos "+
      "of parchment.\n");
    add_item(({"walls","wall"}),"The walls are so crammed with shelves "+
      "that you can't really see them, you just assume they're there.\n");
    add_item(({"shelves","shelf"}),"The sides of the room appear to be "+
      "made out of wooden bookshelves, however, its most likely that there "+
      "are walls behind them, its just that they are hidden from view by the "+
      "inordinately large number of shelves.\n");
    add_item(({"rolled parchments","parchments","rolled parchment","parchment"}),
      "Sealed in wax, the papers must be scribed accounts of the daily "+
      "transactions in the port.\n");
    add_item(({"small chair","chair"}),"A small and rickety wooden chair "+
      "that sits in the very center of the room, surrounded by the confusing "+
      "number of desks and parchment that fills the room.\n");
    add_item(({"desks","desk"}),"Small wooden desks whose tops are "+
      "covered with parchment.\n");
    add_exit(PORT + "s57", "west");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/shipclerk");
	ob1 -> move_living("xxx",TO);
    }

}

