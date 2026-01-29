/*   captains.c
 *
 *  Captain's cabin
 *
 * Baldacin@Genesis, July 2003
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"
inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("Captain's cabin");
    set_long("You have swam into what seems to be the Captain's "+
      "cabin. The room is furnished with an elegant looking table and "+
      "a few chairs, and what used to be a comfortable bed before "+
      "the ship sunk. A small chest has been placed next to the bed.\n");
      
    add_item("table", "An elegant looking table, at least it used to be. "+
      "Now it is decaying.\n");
    add_item(({"chair", "chairs"}), "Wooden chairs, they seem to have been "+
      "made of strong oak.\n");
    add_item("bed","An old rickety bed, It is where the captain used to "+
      "sleep.\n");    
    
    clone_object(OBJ + "chest")->move(TO);
    add_swim_exit(WRECKU + "upper4","out");
}
