#include "../default.h"
inherit CVAN_ROOM;

#include <ss_types.h>

#define HARD_TO_CLIMB 50
#define DAMAGE 50

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    set_short("Deep tunnel");
    set_long("You can barely see within this dark and "+
      "extremely damp tunnel. The walls are made of what appears to be "+
      "limestone, or some such porous rock. This explains the ceiling, "+
      "which is so moist, water is dripping from it.\n");

    add_item(({ "tunnel" }), "The tunnel seems to grow colder to the west.\n");

    add_item(({ "ceiling" }), "You peer more intently at it and notice one "+
      "section of it is completely dry, not a single trace of moisture is "+
      "visible.\n");

    add_item(({ "walls", "wall" }), "The entire tunnel is made out of the "+
      "limestone rock.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur12b", "west");
    add_exit(CVAN + "lot/ur12d", "up", "@@climb");
}

void
init()
{
    ::init();
    write("Warm air envelopes you.\n");
}

int
climb()
{
    if(TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
    {
	write("You slipped on the moist walls and fell down.\n");
	write("Ouch, that hurt!\n");
	TP->heal_hp(-DAMAGE);
	say(QCTNAME(TP) + " fell down while trying to climb the wall and got hurt.\n");
	if(TP->query_hp() <= 0)
	    TP->do_die(TO);
	return 1;
    }
    write("You manage to climb up the wall.\n");
    return 0;
}
