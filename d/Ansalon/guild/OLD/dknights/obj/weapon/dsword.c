/*******************************************************
 *  Solamnic greatsword for The Death Knights of Krynn *
 *  By Elmore, April - 2001                            *
 *******************************************************/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("greatsword");
    add_name("sword");
    set_adj("ancient");
    add_adj("solamnic");
    set_short("ancient solamnic greatsword");
    set_long("This is one of the ancient solamnic greatswords "+
             "that dates back before the Cataclysm. The sword blade "+
             "has been decorated with beautiful ornate carvings but "+
             "the once flawless design has been charred black "+
             "by fire.\n");
    set_default_weapon(40, 40, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 5600);
    add_prop(OBJ_I_WEIGHT, 5500);
}
