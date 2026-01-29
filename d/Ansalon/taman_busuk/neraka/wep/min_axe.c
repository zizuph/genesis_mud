inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define HIT 29
#define PEN 39

create_weapon()
{
   set_name("poleaxe");
   add_name("axe");
   add_adj("two-handed");
   add_adj("huge");
   set_short("huge two-handed poleaxe");
   set_long("A large axehead is mounted on a thick wooden pole. This axe " +
   "is heavy and can probably do a lot of damage.\n");
   set_default_weapon(HIT,PEN,W_AXE,W_SLASH,W_BOTH);
   add_prop(OBJ_I_VOLUME, 5500);
   add_prop(OBJ_I_WEIGHT, 12000);
}
