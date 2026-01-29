   /*
    *    A fox skin
    */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("fox skin");
  add_name("skin");
  add_name("foxskin");
  add_name("fur");
  add_name("fox fur");
  set_short("red fox skin");
  set_pshort("fox skins");
  set_long("The skin of a red fox out of Gondor.\n");
  set_adj(({"red","fox's","fox"}));
  set_ac(9);
  set_at(A_BODY);
  set_am(({-2,2,1}));
  add_prop(OBJ_I_WEIGHT,(800+(random(200))));
  add_prop(OBJ_I_VOLUME,(200+(random(400))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(40)-50);
  add_prop("_skin_by_gresolle",10);
}

