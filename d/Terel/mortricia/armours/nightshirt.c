/*
   A nightshirt. Mortricia 920717
 */

inherit "/std/armour";
#include "/sys/wa_types.h"

create_armour()
{
    set_name("nightshirt");
    set_short("old nightshirt");
    set_adj(({"old", "shabby"}));
    set_long("It is a shabby looking nightshirt.\n");

    set_default_armour(3, A_ROBE, 0, 0);
}
