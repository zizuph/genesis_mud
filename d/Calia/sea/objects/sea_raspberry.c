
 /* A nice light red raspberry for sale in Thalassia */

#include "defs.h"
inherit FRUIT;

void
create_fruit()
{
    set_name("raspberry");
    add_name("sea raspberry");
    set_short("small red sea raspberry");
    set_adj(({"small","red","sea"}));
    set_long("This looks like a rather small ordinary raspberry, save "+
        "it is light red in colour and does not appear to have grown on "+
        "land, rather underwater somehow. It is fully ripe, yet is "+
        "light red in colour instead of dark red. It is probably "+
        "from the lack of direct sunlight. ");
    set_fruit_amount(1);
    set_mana_add(0);
    set_hp_add(20);
    set_fatigue_add(0);
}
