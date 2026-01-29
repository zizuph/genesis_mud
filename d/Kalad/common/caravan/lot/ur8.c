#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A guardroom within the underground lair");
    set_long("A guardroom.\n"+
      "This room is where the guards that follow Thanar reside. The room "+
      "is furnished only with the bare essentials. You can see a few cots "+
      "where the guards sleep and a table with some chairs. Upon the "+
      "wall a huge symbol of a dark sun has been placed.\n");

    add_item(({ "cots" }),
      "Tidy-looking places where the guards sleep.\n");

    add_item(({ "table" }),
      "A large wooden table, on the top lies a deck of playing cards.\n");

    add_item(({ "chairs" }),
      "These are what the guards sit on.\n");

    add_item(({ "cards" }),
      "A typical set of playing cards. This particular set looks rather "+
      "worn and well-used.\n");

    add_item(({ "huge symbol", "symbol" }),
      "                             *****\n"+
      "                           *********\n"+
      "                         *************\n"+
      "                       *****************\n"+
      "                      *******************\n"+
      "                       *****************\n"+
      "                         *************\n"+
      "                           *********\n"+
      "                             *****\n"+
      "                           +-------+\n"+
      "                           | Glory |\n"+
      "                           |Is Ours|\n"+
      "                           +-------+\n");
    "                            ~~~~~~~\n"+

    clone_object(CVAN + "door/urdoor1")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "lknight");
	ob1->arm_me();
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "lknight");
	ob2->arm_me();
	ob2->move_living("M",TO);
	ob1->team_join(ob2);
	tell_room(TO, "Two warrior knights of Thanar enter the room.\n");
    }
}
