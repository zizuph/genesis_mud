/*
 * /d/Gondor/tolfalas/room/cove02.c
 *
 *  Toby - 28 Aug 2006
 *
 *  Northern outcropping in the secret cove on Tolfalas
 *  'home' for the rowboat of the Black Numenorean
 *
 *  Modification log:
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/tolfalas/lib/room_funcs.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public string long_desc();

public void
create_gondor()
{
   set_short("in a cove on the island Tolfalas, in the Bay of Belfalas");
   set_long(&long_desc());

   add_exit(TOLFALAS_DIR + "room/cove03", "west", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove01", "southeast", 0, 2);
   add_exit(TOLFALAS_DIR + "room/cove_above", "up", "@@add_fat");

   sky_add_items();
   beach_add_items();
   cove_add_items();

   add_beach_tells();
   add_cove_tells();
   set_tell_time(300);

   reset_room();
}

string
long_desc()
{
   return "Before you just to the north is a steep rocky hillside " +
          "and to the west it slopes up even more turning into a sheer " +
          "cliff almost as if cut with a knife from above. Further southwest of " +
          "here another hillside subdue into jutting pieces of rock, as " +
          "studs, sticking up through the water surface. There is another " +
          "of these outcroppings a little way further south. Following " +
          "that outcropping to the west it rise quite abruptly into " +
          "the sheer cliff. It looks as if something have been carved " +
          "of the cliff over there." + sky_desc() + "\n"; 
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if(interactive(ob))
      start_room_tells();
      sky_add_items();
}

int add_fat()
{
   TP->add_fatigue(-TP->query_max_fatigue() / 15);

   return 0;
}


