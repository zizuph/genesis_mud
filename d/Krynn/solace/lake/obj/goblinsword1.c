/* created by Aridor 07/13/93 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("sword");
    set_pname("swords");
    set_pname("weapons");
    set_adj("well used");
    add_adj("dirty");
    set_short("well used dirty sword");
    set_long("Don't be deceived by appearances. This sword can do some " +
      "pretty serious damage in the right hands. It hasn't been " +
      "kept too well, though, so it is not very sharp.\n");
    set_default_weapon(16, 21, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 2600);
    add_prop(OBJ_I_WEIGHT, 2500);
}
