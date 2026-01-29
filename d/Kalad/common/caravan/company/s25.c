#include "../default.h"
inherit CVAN_ROOM;

object ob1;
object ob2;
object ob3;
object ob4;

#define SERV	(NPC + "tcserv")

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Servants' Quarters");
    set_long("You enter a crowded room.\n"+
      "This room looks to be quite large, the only thing about it are the "+
      "many crowded beds that nearly fill the entire room. With all the "+
      "bed and tables that crowd this place, it gives you the illusion that "+
      "you're in a smaller space.\n");

    add_item(({ "beds" }),
      "Fairly good-sized beds made of pine wood. A few are covered by some "+
      "thin sheets, the majority however are sheetless.\n");

    add_item(({ "tables" }),
      "There are only a few scattered around the room. On top of some you "+
      "can see empty plates and glasses.\n");

    add_item(({ "plates" }),
      "Cheap tin plates used by the servants to eat off of.\n");

    add_item(({ "glasses" }),
      "Cheap tin cups used by the slaves to drink out of.\n");
    clone_object(CVAN + "door/sdoor1")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1 || !ob2 || !ob3 || !ob4)
    {
	ob1 = clone_object(SERV);
	ob1->move_living("M", TO);
	ob2 = clone_object(SERV);
	ob2->move_living("M", TO);
	ob3 = clone_object(SERV);
	ob3->move_living("M", TO);
	ob4 = clone_object(SERV);
	ob4->move_living("M", TO);
	ob1->team_join(ob2);
	ob3->team_join(ob4);
    }
}
