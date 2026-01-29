inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define MIN_STRENGTH 40

void
create_door()
{
    ::create_door();
    set_door_id("Morgul_Cellar_Trapdoor");
    set_pass_command(({"u","up"}));
    set_door_name(({"trap door","hole","ceiling","hatch","board","plank","door","trapdoor"}));
    set_door_desc(VBFC_ME("long_desc"));
    set_str(MIN_STRENGTH);
    set_closed_desc("");
    set_open_desc("There is an open trap door leading up.\n");

    set_other_room(MORGUL_DIR + "city/tunnels/pass02");

    set_open(0);         /* 1 if open, 0 if closed */
}

string
long_desc()
{
    if (query_open())
        return BSN("There is a hole in the ceiling. Using a ladder you "
          + "can climb up to the ground floor of the building.");
    else
        return BSN("Looking at the ceiling, you notice that there is a "
          + "hole covered by a large wooden plank. It looks like a trap "
          + "door leading up.");
}

/*
 * Function name: pass_door
 * Description:   Pass the door.
 * Arguments:	  arg - arguments given
 */
int
pass_door(string arg)
{
    object  tp = TP;

    if (!other_door)
	load_other_door();

    if (open_status)
    {
        if (!present("ladder", ENV(TO)))
        {
            write("You cannot climb up through the door. You will "
              + "need a ladder to do that!\n");
            return 1;
        }
        tp->move_living(query_verb(), other_room);
    }
    else
	write(check_call(fail_pass));

    return 1;
}

