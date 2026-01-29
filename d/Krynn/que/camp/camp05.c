/* Camp in the plains of Abanasinia
 * Aridor, 08/97
 */

#include "local.h"

inherit CAMP_BASE

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the northwestern corner of an army camp. There are " +
	     "tents scattered about.\n");
    add_item("tents","They look like standard army tents.\n");
        
    add_exit("camp06","east","@@block@@");
    add_exit("camp08","south","@@block@@");

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}
