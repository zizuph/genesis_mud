inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("axe");
    set_adj("woodman's");
    set_short("woodman's axe");
    set_long("This axe has been designed to be wielded by " +
      "a woodsman. The head of the axe is of strong " +
      "steel and is about the size of a horse's " +
      "head making you think that the sort of trees " +
      "this axe is used to cutting down are rather " +
      "big.\n");
    set_default_weapon(20, 33, W_AXE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 15000);
}
