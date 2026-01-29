#include "../default.h"
inherit CVAN_ROOM;

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

object ob1;
object ob2;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Entrance Hall");
    set_long("You are at the intersection of two grand hallways.\n"+
      "The main entrance hall stretches out of sight far to the north. "+
      "Lining the entrance hallway are many marble busts. In the south "+
      "lies the two double doors that lead out of the Company Building. "+
      "Running west-east from here is another smaller hallway, though no "+
      "less grand.\n");

    add_item(({ "marble busts", "busts" }),
      "There are dozens of them lining the hallway leading north. You "+
      "read a few of the inscriptions at the base of some busts and realize "+
      "that each of these busts depicts one of the leaders of the Trading "+
      "Company.\n");

    add_item(({ "doors" }),
      "A pair of massive redwood doors that are at the entrance point into "+
      "this building, which is just to the south. The doors rise to a height "+
      "of at least twelve feet and look to be very solid.\n");

    add_item(({ "hallway", "hallways" }), "Contrary to the appearance of the "+
      "building from the outside, the inside is bright. The walls and floor "+
      "are a brilliant white in color.\n");

    add_exit(CVAN + "company/s3", "west");
    add_exit(CVAN + "company/s37", "north");
    add_exit(CVAN + "company/s23", "east");
    add_exit(CVAN + "company/s1", "south");

    reset_room();
}

void
reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(NPC + "tcguard_hall");
	ob1->move_living("M", this_object());
    }

    if(!ob2)
    {
	ob2 = clone_object(NPC + "tcguard_hall");
	ob2->move_living("M", this_object());
	ob1->team_join(ob2);
    }
}


void
init()
{
    ::init();
    write("You almost slip on the marble floor!\n");
}
