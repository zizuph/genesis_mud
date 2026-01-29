/* created by Splunge 01/94 */

inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"


create_weapon()
{
    set_name("club");
    set_pname("clubs");
    set_pname("weapons");
    set_short("massive wooden club");
    set_adj(({"massive", "wooden"}));
    set_long("This looks more like the base of a tree! Anything using a club "+
         "this big must have tremendous strength.\n");
    set_default_weapon(23, 40, W_CLUB, W_BLUDGEON, W_BOTH);
    add_prop(OBJ_I_WEIGHT, 120000);
    add_prop(OBJ_I_VOLUME, 42000);
}
