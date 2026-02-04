/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP  this_player()
#define ETP environment(TP)

public void
create_drink()
{
   set_name("wine");
   set_adj("red");
   add_name(MYSTIC_WINE);
   set_long("Some dark red wine.\n");

   set_soft_amount(100 + random(25));
   set_alco_amount(50);
   add_prop(HEAP_S_UNIQUE_ID, "mystic_grape_wine");
}

public int
drink_access(object ob)
{
   if (function_exists("create_heap", ob) != "/std/drink")
       return 0;
   if (environment(ob) == TP ||
         (environment(ob)->id(MYSTIC_CHALICE) &&
          environment(environment(ob)) == TP))
       if (ob->short())
           return 1;
   return 0;
}

public void
consume_text(object *arr, string vb)
{
   TP->catch_msg("You feel glorious as the holy wine instills " +
                 "you with mystery.\n");
   tell_room(ETP, QCTNAME(TP) + " drinks some red wine.\n", TP);
   TP->add_mana(100);
   if (MEMBER(TP))
       TP->set_piety((TP->query_piety() + 1));
}

