/* longsword  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_weapon() {
  set_name(({"rapier","sword","weapon"}));
  set_short("finely sharpened rapier");
  set_pshort("rapiers");
set_long("A finely sharpened rapier, commonly used by sailors.\n");
  set_adj("long");
  set_adj("sharp");
  set_adj("steel");
  set_adj("swashbuckler");
  set_default_weapon(29,26,W_SWORD,W_SLASH | W_IMPALE,W_RIGHT,0);
  add_prop(OBJ_I_WEIGHT,7000);
  add_prop(OBJ_I_VOLUME,1280);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(29,26)+random(200)-100);
}
