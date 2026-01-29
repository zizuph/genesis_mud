/*
 * A large treasure chest
 */

inherit "/std/receptacle";
#include <macros.h>
#include "/sys/stdproperties.h";

void
create_receptacle()
{
    set_name("chest");
    set_adj("large");
    add_adj("golden");
    set_pshort("large golden chests");
    set_long("This large golden chest reflects all the light around it and "+
    "seems to glow as a light of its own.  Etched into the golden sides are "+
    "many geometric patterns which flow and circle the chest.\n");
    set_key("Ann_Gold_Chest_Key");
    set_pick(49);

    add_prop(CONT_I_WEIGHT, 40500); 	/* It weights 40500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 140500); 	/* It can hold 140500 grams. */
    add_prop(CONT_I_VOLUME, 19000); 	/* 1.9 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 60000); 	/* 6 litres of volume */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
   add_prop(CONT_I_CLOSED, 1);
   add_prop(CONT_I_LOCK,   1);
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 220); 		/* Worth 220 cc */
}

query_recover() { return MASTER + ":"; }

mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "Good thing you happened to check, the "+short()+" "+
      "isn't empty, and you don't want to sell it quite yet!\n";
  return 0;
}

