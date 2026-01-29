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
    add_adj("silver");
    set_pshort("large silver chests");
    set_long("A large silver chest made of a solid piece of "+
      "cast silver with an tough lock to keep the lid in "+
      "place.  It sports the design of a five-sided star.\n");

    set_key("Ann_Silver_Chest_Key");
    set_pick(49);

    add_prop(CONT_I_WEIGHT, 40500); 	/* It weighs 40500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 140500); 	/* It can hold 140500 grams. */
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

