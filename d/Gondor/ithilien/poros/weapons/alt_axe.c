/* 
 * /d/Gondor/ithilien/poros/weapons/alt_axe.c
 *
 * Modification log:
 * Gwyneth - Added more verbose set_pshort 4/1/01
 */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_weapon() {
  set_name(({"battleaxe","axe","weapon"}));
  set_pname("axes");
  add_pname("battleaxes");
  set_short("black carbon steel battleaxe");
    set_long("This heavy battleaxe is made of black carbon steel, and " +
        "inlaid with silver and adamant.\n");
  set_pshort("black carbon steel battleaxes");
  set_adj("black");
  add_adj("steel");
  add_adj("heavy");
  add_adj("dwarven");
    set_default_weapon(30, 35, W_AXE, W_SLASH|W_IMPALE, W_ANYH, 0);
  add_prop(OBJ_I_WEIGHT,5000);
  add_prop(OBJ_I_VOLUME,1000);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(28,35)+random(200)-100);
}
