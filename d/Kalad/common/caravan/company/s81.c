#include "../default.h"
inherit CVAN_ROOM;

#define EGUARD	(NPC + "tceguard")

object ob1;
object ob2;
object ob3;
object ob4;

void reset_room();

void
create_cvan_room()
{
    set_hear_bell(0);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Inner Sanctum");
    set_long("You are within a magnificently decorated hall.\n"+
      "This massive place is built entirely out of solid marble. Grand pillars "+
      "lie directly to the north and south. Towards the west a series of "+
      "steps slowly rises up to its pinnacle, a large dais in the shape of "+
      "a half-circle. An exquisite red carpet blankets the steps that lead "+
      "up to the dais. Up above, on the ceiling are large crystalline "+
      "chandeliers, providing a brilliant illumination for the entire hall. "+
      "Behind the pillars to the north and south are immense alcoves, so "+
      "large that they are more like rooms, than mere recesses aside this "+
      "grand hall.\n");

    add_item(({ "pillars" }), "Huge pillars built out of solid marble, they "+
      "must be as large as the great redwoods of the Hespyre mountains.\n");

    add_item(({ "steps" }), "Marble steps, about six inches high. They lead "+
      "slowly upwards to the west.\n");

    add_item(({ "dais" }), "A large platform at the end of the series of "+
      "steps which lead west from here. You can see a gigantic throne at the "+
      "far end of it, but can't quite tell if anyone is there, due to the "+
      "distance.\n");

    add_item(({ "throne" }), "You are too far away to pick out any details.\n");

    add_item(({ "carpet" }), "A magnificent carpet woven from some wonderfully "+
      "soft substance. The carpet leads west upon the steps.\n");

    add_item(({ "chandeliers" }), "Great crystalline chandeliers that tinkle "+
      "ever so slightly, creating a soothing melody that flows throughout "+
      "the room.\n");

    add_item(({ "alcoves" }), "All you can see are flickering shadows "+
      "whenever you gaze in their direction. It must be some trick of the "+
      "light, and the fact that most of your view is obscured by the "+
      "gigantic pillars aside the grand carpet.\n");

    add_exit(CVAN + "company/s80", "west", "@@block");
    add_exit(CVAN + "company/s72", "north");
    add_exit(CVAN + "company/s82", "east");
    add_exit(CVAN + "company/s71", "south");

    add_cmd_item(({ "west", "wall" }), "enter", "@@enter");
    add_cmd_item("wall", "enter", "@@enter");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(EGUARD);
	ob1->move_living("M", TO);
    }

    if (!ob2)
    {
	ob2 = clone_object(EGUARD);
	ob2->move_living("M", TO);
    }

    if (!ob3)
    {
	ob3 = clone_object(EGUARD);
	ob3->move_living("M", TO);
	ob1->team_join(ob2);
	ob1->team_join(ob3);
    }

    if (!ob4)
    {
	ob4 = clone_object(NPC + "tcserv1");
	ob4->move_living("M", TO);
    }
}

int
block()
{
    write("As you take a step towards the dais, you slam into an invisible wall "+
      "and are forced back down.\n");
    say(QCTNAME(TP) + " takes a step towards the dais and then slams "+
      "into something and is forced back down.\n");
    return 1;
}

string
enter()
{
    write("You feel slight resistance as you pass through the invisible barrier.\n");
    set_dircmd("wall");
    TP->move_living("into nothingness", CVAN + "company/s80");
    return "You feel the resistance fade away.\n";
}
