#pragma  strict_types

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "../sys/defs.h"

inherit  ("/std/armour");
inherit  ("/lib/keep");

public nomask string
wiz_info() {
  return ("A platemail forged in Sauron's stronghold.\n" +
          "Magically strengthened against death spells.\n" +
          "MAGIC_AM_MAGIC    : " +
          query_prop(MAGIC_AM_MAGIC)[0] + "%, " +
          query_prop(MAGIC_AM_MAGIC)[1] + "\n" +
          "MAGIC_I_RES_DEATH : 33%, additive.\n");
}

public nomask void
create_armour() {
  set_name("platemail");
  add_name("mail");
  set_adj("black");
  add_adj("steel");
  add_adj("high");
  set_short("black platemail");
  set_pshort("black platemails");
  set_long("A black platemail forged from high steel in the pits " +
           "below Barad-Dur for the officers of the Dark Lord's " +
           "armies.  You can see a strange magical glimmer " +
           "radiating from the armour.  The breastplate shows a " +
           "picture of the Red Eye with rays of red light " +
           "extending from behind its lower hemisphere.\n");
  set_at(A_BODY);
  set_ac(50);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50) + random(1000) + 500);
  add_prop(OBJ_M_NO_BUY, 1);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(50, A_BODY) +
                         random(2000) - 1000);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
  add_prop(MORDOR_M_NO_SELL, 1);
  add_prop(OBJ_S_WIZINFO, wiz_info);
  add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
  add_prop(MAGIC_AM_ID_INFO,
           ({ "The black platemail seems to be magically " +
              "strengthened.", 1,
              "The black platemail seems to be magically " +
              "enhanced to protect against magic spells.", 25,
              "The black platemail protects against " +
              "death spells.", 50 }));
  add_prop(MAGIC_I_RES_DEATH, 100);
  add_prop(MAGIC_I_RES_DEATH, ({ 33, 0 }));
}

public mixed
wear(object obj) {
  object tp = ENV(TO);
  if ((tp != TP) || (obj != TO))
    return (-1);
  if (living(tp))
    tp->add_magic_effect(TO);
}

public mixed
remove(object obj) {
  object tp = TO->query_worn();
  if ((tp != TP) || (obj != TO))
    return (-1);
  if (living(tp))
    tp->remove_magic_effect(TO);
}

public mixed
query_magic_protection(string prop,
                       object for_what = previous_object()) {
  object tp = TO->query_worn();
  if (for_what == tp) {
    switch (prop) {
      case MAGIC_I_RES_DEATH :
        return ({ 33, 1 });
    }
  }
  return (::query_magic_protection(prop, for_what));
}
