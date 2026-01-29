/* Slight increase in AC to strengthen the NPCs that use them, Eowul, 2009 */

inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_armour()
{
  set_name(({"chainmail","chain mail","mail"}));
  set_pname("chainmails");
  add_pname("mails");
  set_short("silver chainmail");
  set_pshort("silver chainmails");
  set_adj("silver");
  set_long("The silver chainmail is made of shiny metal rings.\n"+
    "A black tunic covers most of the torso, and a white tree is\n"+
    "embroidered on the front. This is standard Gondorian armour.\n");
  set_default_armour(30,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,9500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(200)-100);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
