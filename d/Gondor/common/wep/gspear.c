/* Increased hit/pen, Eowul, 2009 */
/* Ranger spear  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Gondor/defs.h"

create_weapon()
{
  set_name(({"spear","polearm","weapon"}));
  set_pname("spears");
  add_pname("polearms");
  set_short("broad-bladed oak spear");
  set_pshort("broad-bladed spears");
  set_long("A broad-bladed spear made of oak wood, its broad head made of steel.\n"+
    "It is short and light enough to be wielded in one hand, as a stabbing\n"+
    "weapon. The spear was made in Gondor.\n");
  set_adj("gondorian");
  set_adj("bright");
  set_adj("steel");
  set_adj("broad-bladed");
  set_adj("oak");
  set_default_weapon(20,30,W_POLEARM,W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,3500);
  add_prop(OBJ_I_VOLUME,1500);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(20,30)+random(200)-100);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
