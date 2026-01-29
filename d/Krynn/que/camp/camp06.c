/* Camp in the plains of Abanasinia
 * Aridor, 08/97
 */

#include "local.h"

inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the northern part of an army camp. There are " +
	     "tents scattered about.\n");
    add_item("tents","They look like standard army tents.\n");
        
    add_exit("camp05","west","@@block@@");
    add_exit("camp09","south","@@block@@");
    add_exit("camp01","north","@@block@@");
    add_exit("camp07","east","@@block@@");

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}

