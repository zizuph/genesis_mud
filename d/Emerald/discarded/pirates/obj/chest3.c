
inherit "/std/receptacle";
#include <stdproperties.h>
#include <money.h>
#include "defs.h"

void
create_container()
{
   set_name("chest");
   set_adj("treasure");
   set_short("treasure chest");
   set_long("This chest is ancient.\n");
   
   add_prop(CONT_I_WEIGHT, 5000);
   add_prop(CONT_I_MAX_WEIGHT, 100000);
   add_prop(CONT_I_MAX_VOLUME, 5000000);
   add_prop(CONT_I_VOLUME, 10000);
   add_prop(OBJ_I_VALUE, 1000 + random(250));
   
   {
      object pegleg, eyepatch, chains, bag_of_diamonds, bag_of_rubies, chalice, dagger;
      MONEY_MAKE_CC(100)->move(this_object());
      MONEY_MAKE_SC(100)->move(TO);
      MONEY_MAKE_GC(100)->move(TO);
      seteuid(getuid());
      pegleg = clone_object(PIRATES_DIR+"obj/peg_leg");
      pegleg ->move(TO);
      seteuid(getuid());
      eyepatch = clone_object(PIRATES_DIR+"obj/eyepatch");
      eyepatch ->move(TO);
      seteuid(getuid());
      chains = clone_object(PIRATES_DIR+"obj/chains");
      chains ->move(TO);
      seteuid(getuid());
      bag_of_rubies = clone_object(PIRATES_DIR+"obj/bag_of_rubies");
      bag_of_rubies ->move(TO);
      seteuid(getuid());
      bag_of_diamonds = clone_object(PIRATES_DIR+"obj/bag_of_diamonds");
      bag_of_diamonds ->move(TO);
      seteuid(getuid());
      dagger = clone_object(PIRATES_DIR+"obj/pir_dagger");
      dagger ->move(TO);
   }
   
   add_prop(CONT_I_CLOSED, 1);
   
   /* things to add:  rubies, diamonds, gold crown, silver chalice, */
}
