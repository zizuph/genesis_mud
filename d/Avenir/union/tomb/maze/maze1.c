#include "../defs.h"
inherit (MAZE + "maze");
#include <macros.h>

public void
create_maze(void)
{
    set_short("beneath the pool");
    set_long("Overhead is a flat, shimmering surface of water, "+
	"gleaming a dazzling blue, hanging impossibly over your "+
	"head without a drop falling. The water is framed by a "+
	"circular border, past which the ceiling is made from "+
	"grey sandstone. "+ ::query_long());

    add_item("border",
	"It is made from a strange, luminous azure stone.\n");

    add_item(({"ceiling","water","pool"}),
	"The water hangs impossibly overhead, calm except for an "+
	"occassional ripple that passes along the surface. Looking "+
	"up through the pool gives you a sense of vertigo, but high "+
	"overhead you think you can make out a large chamber.\n");

    add_cmd_item(({"pool","water","into the pool","into pool","in pool",
	    "in the pool","into the water","in water","into water"}),
	({ "enter", "swim", "climb" }),
	"You can reach the pool above you, but you cannot "+
	"find any means of entering it.\n");

    add_cmd_item(({"pool","water","into the pool","into pool","in pool",
	    "in the pool","into the water","in water","into water"}),
	"jump", "@@go_up@@");
}

public string
go_up(void)
{
    say(QCTNAME(TP) +" jumps up and is drawn into the pool.\n");
    write("You jump up and are drawn quickly into the pool. "+
	"You float to the surface, and climb out onto the ledge.\n");

    TP->move_living("M", PUZZLE + "pool_room", 1, 1);
    return "";
}

/* reset the words */
public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (to->query_prop(WORD_PROP))
    {
        to->remove_prop(WORD_PROP);
        set_alarm(0.5, 0.0, &tell_object(to,
		"You feel you are at the beginning again.\n"));
    }
}
