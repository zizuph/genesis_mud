inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_name("warhammer");
    add_name("hammer");
    add_name("club");
    set_adj("dwarven");
    add_adj("metal");
    set_short("dwarven warhammer");
    set_long("This is a warhammer developed by dwarven smiths of the " +
           "Theiwar Clan. While not as renowned weaponsmiths as some " +
           "of their other mountain dwarf cousins, this weapon is " +
           "exquisite in make and would be the envy of smiths of other " +
           "races.\n");

    set_likely_dull(1);
    set_likely_corr(1);
    set_likely_break(1);
    set_default_weapon(35, 35, W_CLUB, W_BLUDGEON, W_ANYH);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
