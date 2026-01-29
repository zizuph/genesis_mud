/* rapier  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
  set_name(({"rapier","sword","weapon"}));
  set_pname("rapiers");
  add_pname("swords");
  set_short("long steel rapier");
  set_pshort("rapiers");
  set_long("This is a long, thin blade, known as a rapier. It is quite effective\n"+
    "as an impaling weapon. The quality craftsmanship shows it was\n"+
    "made in Gondor. It is made of alloyed greyish steel.\n");
  set_adj("long");
  set_adj("grey");
  set_adj("steel");
  set_adj("thin");
  set_adj("gondorian");
  set_default_weapon(35, 20, W_SWORD, W_IMPALE, W_ANYH, 0);
  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,1280);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,20)+random(200)-100);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
