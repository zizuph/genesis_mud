/* Camp in the plains of Abanasinia
 * Aridor, 08/97
 */

#include "local.h"

inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the western part of an army camp. There are " +
	     "tents scattered about.\n");
    add_item("tents","They look like standard army tents.\n");
        
    add_exit("camp04","west","@@block@@");
    add_exit("camp11","south","@@block@@");
    add_exit("camp05","north","@@block@@");
    add_exit("camp09","east","@@block@@");

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}

