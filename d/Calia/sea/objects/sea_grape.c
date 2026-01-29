
 /* A nice green grape for sale in Thalassia */

#include "defs.h"
inherit FRUIT;

void
create_fruit()
{
    set_name("grape");
    add_name("sea grape");
    set_short("small green sea grape");
    set_adj(({"small","green","sea"}));
    set_long("This looks like a rather small ordinary grape, save "+
        "it is smaller than normal and does not appear to have grown on "+
        "land, rather underwater somehow. It is fully ripe, yet is "+
        "alot smaller, almost pea sized. It is probably "+
        "from the lack of direct sunlight. ");
    set_fruit_amount(1);
    set_mana_add(0);
    set_hp_add(0);
    set_fatigue_add(10);
}
