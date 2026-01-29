/*
 * Angmar Weapon Rack
 */
 
inherit "/d/Genesis/specials/guilds/objs/weapon_rack";

#include <stdproperties.h>

void
create_rack()
{
    set_adj("weapon");
    set_short("weapon rack");
    set_long("Large trees were felled and converted into a rack "
        + "for storing the army's belongings.\n");
    add_prop(OBJ_M_NO_GET, "You are unable to take that.\n");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT,99999999);
    add_prop(CONT_I_MAX_VOLUME,99999999);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);
    add_prop(CONT_I_IN,1);
}
