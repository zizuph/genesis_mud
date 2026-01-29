/*
 * std_boat_room file.
 *
 * Arman 27 September 2020
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

#pragma save_binary

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_boat_room"
#define RESET "reset_boat_room"

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
   
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
   call_other(TO, RESET);
}

