#include "../default.h"
inherit CVAN_ROOM;

#include <filter_funs.h>

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    add_prop(ROOM_NO_TIME_DESC, 1);

    set_short("Entrance to Company Building");
    set_long("You've reached the entrance to the Trading Company's "+
      "headquarters. From here, the small cobblestoned street heads south "+
      "through the entrance gates and connects with Wayfarer Boulevard. To "+
      "the north the small road ends at two large double doors, the entrance "+
      "into the massive edifice that is the Company building. There "+
      "is a guard post here.\n");

    add_item(({ "gates" }),
      "The gates are the only break in the fifteen foot high stone walls "+
      "that completely encircle the Company building. Made of steel, the "+
      "gates are nearly as tall as the walls, standing about twelve feet in "+
      "height.\n");

    add_item(({ "high stone walls", "stone walls", "walls" }),
      "Impeccably clean walls, free of any filth or refuse. They stand at "+
      "least fifteen feet tall and serve to keep out the ordinary rabble "+
      "that walk the streets, such as yourself.\n");

    add_item(({ "doors" }),
      "Made of solid redwood, cut from the hespyre mountains, they are as "+
      "tall as the entrance gates, approximately twelve feet. They bar the way "+
      "into the Company building.\n");

    add_item(({ "edifice", "building" }),
      "The structure is positively huge. From your close vantage point you "+
      "get an excellent view of its height, which stretches dozens of feet "+
      "into the air. The building itself is made of a dark grey, almost black "+
      "stone.\n");

    add_item(({ "guard post", "post" }),
      "A small structure just a few feet from the gates. This is where the "+
      "Company guardsman make sure no unwanted intruders enter the building.\n");

    add_exit(CVAN + "company/s2", "north");
    add_exit(CVAN + "wayfar/s1", "south");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcguard_ent");
	ob1->move_living("M", this_object());
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "tcguard_ent");
	ob2->move_living("M", this_object());
	ob1->team_join(ob2);
    }
}
