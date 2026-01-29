inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("apron");
    add_name("chef_apron");
    set_short("food stained apron");
    set_long("It looks like it has seen its brighter days in " +
        "the past. The myriad of food stains creates an interesting " +
        "mix of colours, however: gravy brown, slop green, dried " +
        "blood red, and burnt grease black.\n");
    set_default_armour(3, A_ROBE);
}
