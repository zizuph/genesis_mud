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
    set_adj("small");
    add_adj("platinum");
    set_pshort("tiny platinum chest");
    set_long("This small platinum chest is still larger than most commonly "+
    "found.  In the front, etched carefully in the precious platinum are three signs: "+
    "A tree, seven stars around it and a crown above them.\n");
    set_key("Ann_Plat_Chest_Key");
    set_pick(49);

    add_prop(CONT_I_WEIGHT, 10500); 	/* It weights 10500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 14500); 	/* It can hold 14500 grams. */
    add_prop(CONT_I_VOLUME, 1900); 	/* 1.9 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 6000); 	/* 6 litres of volume */
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

