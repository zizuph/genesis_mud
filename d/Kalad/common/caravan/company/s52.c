#include "../default.h"
inherit CVAN_ROOM;

#define AXEMAN	(NPC + "tcguard1")

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Corner");
    set_long("You've reached a corner.\n"+
      "From here two empty hallways lead away. One passage heads to the "+
      "west while another one goes northwards. Both hallways are devoid of "+
      "any furnishings, the only thing of note in either one is the marble "+
      "floor.\n");

    add_item(({ "marble floor", "floor" }), "The ground is covered in marble "+
      "tiles so brilliantly white that you are nearly blinded when you look "+
      "at them.\n");

    add_exit(CVAN + "company/s53", "west");
    add_exit(CVAN + "company/s65", "north");

    clone_object(CVAN + "door/tcdoor4")->move(TO);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(AXEMAN);
	ob1->move_living("M",TO);
    }

    if(!ob2)
    {
	ob2 = clone_object(AXEMAN);
	ob2->move_living("M",TO);
	ob1->team_join(ob2);
    }
}
