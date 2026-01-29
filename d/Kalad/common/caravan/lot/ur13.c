#include "../default.h"
inherit CVAN_ROOM;

object ob1;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A guardpost in the underground lair");
    set_long("You are within a large, dimly-lit room.\n"+
      "A few torches are mounted upon the bare stone walls. Other than "+
      "that, there is little of interest in this room, for the rest of it "+
      "is just plain stone. A dimly-lit passage leads south.\n");

    add_item(({ "walls" }), "It seems to have been carved from the natural "+
      "rock of this area. The stonework looks to be quite old.\n");

    add_item(({ "torches" }), "Standard torches, the kind you find in your "+
      "general store. They are mounted upon the walls.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur14", "south");

    clone_object(CVAN + "door/urdoor9")->move(TO);

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
	tell_room(TO, "A lone knight arrives to secure his post.\n");
	ob1->command("chuckle evil");
	ob1->command("think torturing some slave to pass the time");
	ob1->command("grin mer");
    }
}
