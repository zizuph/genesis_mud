
 /* A juicy green coloured apple for sale in Thalassia */

#include "defs.h"
inherit FRUIT;

void
create_fruit()
{
    set_name("apple");
    add_name("sea apple");
    set_short("small green sea apple");
    set_adj(({"small","green","sea"}));
    set_long("This looks like a rather small ordinary apple, save "+
        "it is green in colour and does not appear to have grown on "+
        "land, rather underwater somehow. It is fully ripe, yet is "+
        "still green in colour instead of the normal red. It is "+
        "probably from the lack of direct sunlight. ");
    set_fruit_amount(1);
    set_mana_add(10);
    set_hp_add(0);
    set_fatigue_add(0);
}
