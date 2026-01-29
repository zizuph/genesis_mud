#include "../default.h"
inherit CVAN_ROOM;

#include <ss_types.h>

object ob1;
object ob2;
object ob3;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("The War Room");
    set_long("You are standing in the war room.\n"+
      "This room is filled with all manner of maps. In the center of the room "+
      "is a huge table, upon which several maps have been placed out. "+
      "Hanging on the wall is a huge map of Kabal, and surrounding areas. "+
      "Torches, mounted on stands at the corners of the room, provide a dim "+
      "light.\n");

    add_item(({"huge table", "table"}),
      "A massive stone table, covering its top almost entirely are dozens of "+
      "maps, most of them of this city Kabal. The floor beneath the table "+
      "catches your eye.\n");

    add_item(({"maps", "map"}), "Various maps are strewn about the room, "+
      "one huge map of Kabal instantly attracts your attention.\n");

    add_item(({"huge map of kabal", "huge map"}),
      "A map that nearly covers all of the western wall. It shows the city "+
      "of Kabal and the areas surrounding it, such as the farmlands to the "+
      "west, the great chasm to the north, and the Hespyre mountains to the "+
      "east.\n");

    add_item(({"torches"}),
      "Standard torches, the kind you find in your general store. They are "+
      "dimly illuminating this room.\n");

    add_item(({"stands"}),
      "Thin metal stands upon which the torches are mounted, so they can "+
      "provide light enough to see the maps strewn all over this room.\n");

    add_item(({"floor", "ground"}), "Looking beneath the table you see a "+
      "partially hidden exit. It looks like you could go down here.\n");

    set_noshow_obvious(1);

    clone_object(CVAN + "door/urdoor5")->move(TO);
    clone_object(CVAN + "door/urdoor8")->move(TO);
    add_exit(CVAN + "lot/ur12a", "down", 0, 1, 1);

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
        ob1 = clone_object(NPC + "mknight");
        ob1->arm_me();
        ob1->move_living("M",TO);
        tell_room(TO, "A dark figure enters the room.\n");
    }

    if(!ob2)
    {
        ob2 = clone_object(NPC + "lknight");
        ob2->arm_me();
        ob2->move_living("M",TO);
    }

    if(!ob3)
    {
        ob3 = clone_object(NPC + "lknight");
        ob3->arm_me();
        ob3->move_living("M",TO);
        ob1->team_join(ob2);
        ob1->team_join(ob3);
	    tell_room(TO, "Two figures arrive in the room.\n");
    }
}
