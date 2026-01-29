/*
 * Overlook in the Union guildhall
 *  Cirion 060597
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>


public int
down_steps(void)
{
    write("You descend the narrow slate steps onto "+
	"a small landing.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("narrow ledge");
    set_long("Far below the molten floor of the chasm looms with "+
	"a menacing yellow glow, from which dark tendrils of black "+
	"smoke curl up and dissipate in the hot air. Far to the north, "+
	"the opposite wall of the chasm rises to unknown heights, "+
	"shrouded in darkness. The ledge continues to the southeast, "+
	"and descends a narrow set of slate steps to the west.\n");

    add_item(({"lake","molten rock","lava","chasm","chasm wall"}),
	"@@exa_chasm@@");
    add_item("bridge","The bridge is about a hundred feet "+
	"up, spanning the entire chasm.\n");
    add_item(({"wall","walls","rock"}),
	"The walls from the corridor to the south widen here, "+
	"making the ledge quite wide.\n");
    add_item(({"stair","stairs","step","steps"}),
	"The steps are quite narrow and are made from dark, smooth "+
	"plates of slate. They descend down onto a landing made "+
	"from slate.\n");

    add_exit("overhang_steps", "west", down_steps);
    add_exit("overhang", "southeast");
}

public void
init(void)
{
    ::init();
    add_action(jump_ledge, "jump");
    add_action(jump_ledge, "leap");
}

public void
leave_inv(object ob, object where)
{
    ::leave_inv(ob, where);
    remove_warned(ob);
}
