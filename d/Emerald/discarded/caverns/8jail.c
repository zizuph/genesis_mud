/*
 * 8jail.c
 * Jail Cell in the Caverns
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   object door;

   set_short("Prison Cell");
   set_long("   This foul-smelling, damp room is riddled with blood "+
	    "stains on the floor and walls. It looks like a holding "+
	    "cell of some kind. There are several sets of shackles hanging "+
	    "from pitons hammered into the hard stone walls. You try "+
	    "and avoid thinking about what might have been the cause "+
	    "of the blood stains. It appears odd that despite the constant "+
	    "trickling of water down channels in the cave walls, the "+
	    "blood stains have not washed away.\n\n");

   add_item(({"stain","stains","blood stain","blood stains"}),
	    "The stains are thick and dark. They are not much more than "+
	    "dark impressions on the stone now, but you have no doubt "+
	    "that they were blood stains. It strikes you as odd that "+
	    "the constant running water hasn't eroded the blood stains.\n");

   add_item( ({"shackles", "pitons", "sets of shackles", "sets"}),
	     "The shackles are old and rusted. They probably haven't "+
	     "been used in quite some time, but they look quite "+
	     "effective at keeping prisoners chained to the walls.\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(THIS_DIR + "7jail","west");

   seteuid(geteuid());
   door = clone_object(THIS_DIR+"obj/pdoor3b");
   door ->move(TO);
}
