/* 
 * Armour Rack for Elementalist Guilds of Calia
 *  
 * Created by Petros, April 2010
 */

#include <stdproperties.h>

inherit "/d/Genesis/specials/guilds/objs/armour_rack";
#include "defs.h"

public void
create_rack()
{
    add_name("_temple_armour_rack");
    set_adj("armour");
    add_adj("stone");
    set_short("stone armour rack");
    set_long("Curiously, the rack here is made of porous stone that "
        + "is very dark. It's shaped in such a way that various types "
        + "of armour can hang off of it and provides for easy "
        + "retrieval as well. Rock this dark could only have come from "
        + "areas with volcanoes.\n\n");

    add_prop(CONT_I_ATTACH, 1); // allows things to be put "on" the rack instead
        
    set_no_show_composite(1);
    set_enable_logging(1);
    set_rack_log_file(ELEMENTALIST_LOGS + "ec_beta_armour_rack_log");
}
