/*
 * A small chest 940618, belongs to Mzzz, Lt of the orc camp
 */

inherit "/std/receptacle";
#include <macros.h>
#include "/sys/stdproperties.h";

void
create_receptacle()
{
    set_name("chest");
    set_adj("small");
    add_adj("wooden");
    set_pshort("small wooden chests");
    set_long("A small wooden chest made of battered planks nailed "+
      "together and then bound by rusty iron bands for added "+
      "strength.  A small brass lock keeps unwanted hands out.\n");

    set_key("Mzzz_Chest_Brass_Key");
    set_pick(24);

    add_prop(CONT_I_WEIGHT, 2500); 	/* It weights 2500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 10000); 	/* It can hold 10000 grams. */
    add_prop(CONT_I_VOLUME, 1000); 	/* 1 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 3000); 	/* 3 litres of volume */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 120); 		/* Worth 120 cc */
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

