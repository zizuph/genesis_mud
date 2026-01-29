#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_moor_room"
#define RESET  "reset_moor_room"

#define HAS_SEARCHED_GRUBS   "_has_searched_ground"
#define HOW_MANY_GRUBS       2
#define GRUB_OBJECT          "/d/Krynn/common/fishing/earthworm"

int times_searched = 0;

public int
query_grub_time_searched()
{
    return times_searched;
}

mixed
search_for_worms(object searcher, string what)
{
  int find_grub = this_player()->query_skill(SS_HUNTING);

  if (CAN_SEE_IN_ROOM(this_player()))
    {
        times_searched += 1;
        // 20% chance with superior layman hunting skill
        if(random(150) > find_grub)
	    return ("Your search of the ground here but find nothing.\n");

	if (times_searched >= HOW_MANY_GRUBS)
	  {
	      return ("Your search of the ground reveals nothing special. " +
                  "You don't think you'll find any worms in this location.\n");

	  }
	else
	  {
              say(QCTNAME(this_player())+ " pulls an earthworm from " +
                  "the ground!\n");
              setuid();
              seteuid(getuid());
              object grub = clone_object(GRUB_OBJECT);
              grub->move(this_player(), 1);
	      return "You find an earthworm in the damp ground!\n";
	  }
    }
  return 0;
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);

    add_search(({"ground", "moor", "moors" }), 
       10, "search_for_worms", 1);

    add_item(({"ground", "grass", "tufts"}),
        "The ground of the moor is very muddy, dotted with tufts " +
        "of grass.\n");
    add_item(({"moor","moors"}),
        "You find yourself standing on the moors west of Palanthas.\n");
    
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    times_searched = 0;
    call_other(TO, RESET);
}






