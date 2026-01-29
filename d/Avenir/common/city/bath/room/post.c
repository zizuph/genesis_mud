#pragma strict_types
/*
 * ~/post.c
 *
 * Post office in Melchior's Bath.
 *
 * Revisions:
 *   Lilith, Jun 2004: Created.
 *   Lucius, Oct 2008: Cleanup.
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#include "../bath.h" 
inherit BATH_ROOM;
inherit "/d/Genesis/lib/post";

static void
create_bath_room(void)
{
    set_short("decadent writing room");
    set_long("This is a writing room with postal service.\n"+
	"The walls of this small, domed room are dove gray. "+
	"Pink carnelian forms the floor, columns, and moldings, "+
	"while the inside of the dome is painted a rich teal "+
	"colour. Large overstuffed chairs covered in burgundy "+
	"leather are arranged next to small writing stands. "+
	"Words have been carved along the curving wall in large, "+
	"handsbreadth letters: "+ get_std_use());

    add_item(({"stand", "stands" }),
	"The stands are of a pale, grayish wood that contrasts "+
	"nicely with the burgundy leather chairs.\n");
    add_item(({"wall","walls"}),
	"The walls are cut from a smooth greyish stone the colour "+
	"of doves.\n");
    add_item(({"chair","chairs"}),
	"The chairs are quite large and plumply stuffed. They are "+
	"covered in red leather.\n");
    add_item(({"leather"}), "It is over good quality.\n");
    add_item(({"floor", "columns", "moldings", "carnelian", "pink carnelian"}),
	"Pink carnelian is a noble stone, favoured by the office "+
	"of the Hegemon itself, particularly in its darker, purplish "+
	"colour.\n"); 
    add_item(({"dome","ceiling", "teal"}),
	"The ceiling is domed, as are the ceilings of most rooms in "+
	"the Bath. This one is painted a vivid shade of teal.\n");

    add_exit(BATHRM + "desk", "east");
}

public void
init(void)
{
    ::init();
    post_init();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
}
