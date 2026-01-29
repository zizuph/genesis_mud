#pragma save_binary

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

#define ARMOUR_CLASS 30+random(3)

void
create_armour()
{
    set_name(({"cloak", "_filip_armour_"}));

    set_adj(({"elven", "green"}));

    set_short("elven cloak");
    set_pshort("elven cloaks");

    set_long("Nice green elven made cloak and as many elven things "+
             "this one was made to fit exactly its owner. It is made "+
             "to cover the entire body.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_ROBE | A_L_ARM | A_HEAD);
    set_am( ({ random(7)-3, random(7)-3, random(7)-3 }) );

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS) *
                          (90+random(21)) / 100);

  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1); /* it is magic */
  add_prop(MAGIC_AM_MAGIC,({ 25, "enchantment" }));
  add_prop(MAGIC_AM_ID_INFO,({"This cloak seems to be magicaly enchanted.\n",1,
      "Moreover it can cover your entire body.\n",10,
      "But you can wear it only if your stature is similar to the\n"+
      "stature of the owner of this cloak.\n",25 }));
}

wear_me()
{
  if((50 < TP->query_stat(SS_STR)) && (60 > TP->query_stat(SS_STR)))
    return ::wear_me();
  return "Elven cloak doesn't fit you at all.\n";
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
