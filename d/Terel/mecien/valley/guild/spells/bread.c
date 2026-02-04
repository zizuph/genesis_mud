/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/food";
#include <stdproperties.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()

public void
create_food()
{
   set_name("bread");
   set_adj("mystic");
   set_long("A small mystical loaf of luminous bread.\n");
   set_amount(50); /* 50 grams of food. */
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 100);
}

public void
special_effect(int nums)
{
   object full;
   int n;

   if (present(MYSTIC_FULL, TP)) {
       TP->catch_msg("The Ancient Ones frown upon gluttony.\n");
       n = TP->query_skill(PIETY) - 10;
       if (n < 0) n = 0;
       TP->set_skill(PIETY, n);
       return;
   }

   TP->catch_msg("You feel a mystic power as the bread nourishes you.\n");
   TP->add_mana(15);
   TP->heal_hp(5);
   if (random(2)) {
      TP->set_skill(PIETY, TP->query_skill(PIETY) + 1);
   }
   seteuid(getuid());
   full = clone_object(SPELL_DIR + "full");
   full->move(TP);
   full->set_duration(280+random(40));
}
