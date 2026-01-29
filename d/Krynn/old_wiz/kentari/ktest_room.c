inherit "/d/Krynn/std/room";

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/herbsearch.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
 
void
reset_room()
{
}


void
create_room()
{
    set_short("Kentari's testing lab");
    set_long("This is where Kentari tests code, fiddles with nature, " +
        "conducts experiments, and tries not to blow up the Universe. " +
	"You see beakers, test tubes, and stacks of complex data. " +
	"This room is heavily shielded with thick steel, and you see " +
	"spots of black that can only be from explosions.\n");
    add_item(({"shielding","steel"}),
	"Even with all the walls, floor, and ceiling covered in a thick " +
	"titanium steel alloy, and most likely enhanced by spells of " +
	"protection, you still worry that Kentari's experiments don't " +
	"get out of hand.\n.");
    add_item(({"spots","spot","black"}),
	"Various patches of black cover the metal ceiling and a couple " +
	"walls.  It seems explosions happen all too frequently down " +
	"here.\n");
    add_item(({"beakers","test tubes","tubes","data","stacks"}),
	"This equipment seems quite alien to the world you know, and " +
	"you can only hope that Kentari knows what he's doing.\n");

    set_tell_time(360);
    add_tell("You feel a tremor in the nature of the Universe and " +
    	"more data is added to the stack before you.  Kentari must be " +
	"messing with things again.\n");
    add_tell("A bright explosion lights up the room and the walls " +
	"glow with protective magics.  Must have breathed wrong.\n");

    add_exit("/d/Krynn/kentari/workroom", "up");
    add_prop(ROOM_I_INSIDE, 1);
    NO_TIME;
}

public void
enter_inv (object ob, object from)
{
	::enter_inv(ob,from);
	if (interactive(ob))
	   start_room_tells();
}

static int
query_prevent_snoop()
{
   return 1;   
}
