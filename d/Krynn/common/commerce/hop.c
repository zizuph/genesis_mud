/* created by Aridor  09/07/93 */

inherit "/std/food";
inherit "/d/Genesis/lib/commodity";

#include "/sys/stdproperties.h"

void
create_food()
{
    set_name("hop");
    add_name("leaves");
    set_pname("leaves");
    add_pname(({"hops","wreaths"}));
    set_adj({("hop", "wreath", "wreath of"}));
    set_short("wreath of hop");
    set_pshort("wreaths of hop");
    set_long("A leather cord have been tied around the leaves of hop, " +
             "forming a wreath of hop.\n");
             
    set_commodity_name ("hops"); // required to link this
                                  // object with the domain server
    set_commodity_value(300);             
    
    add_prop(OBJ_I_WEIGHT, 3);
    add_prop(OBJ_I_VOLUME, 10);
    set_amount(10);
}
