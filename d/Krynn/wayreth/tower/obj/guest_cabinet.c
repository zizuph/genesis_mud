/* 
 * General Miscellaneous Rack for the Guilds of Genesis
 *  
 * This misc rack is based on the describable rack system. It holds
 * items that are neither weapons nor armours.
 *
 * Created by Petros, July 2009
 */

inherit "/d/Genesis/specials/guilds/objs/describable_rack";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>

void
create_rack()
{
    remove_name("rack");
    set_name("cabinet");
    set_adj("elegant");
    set_short("@@short_fun");
    set_long("This is an elegant cabinet made from polished oak, for use " +
       "by visitors to store their equipment.\n");
}

public string
short_fun()
{
    if (sizeof(all_inventory(this_object())) >= 1)
	return "elegant cabinet";
    return "empty elegant cabinet";
}

