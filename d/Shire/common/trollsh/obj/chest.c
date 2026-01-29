/*
 * A small chest 940618, belongs to Hzzz, leader of the orc camp
* Not really. Try the ruling troll in the Trollshaws.
 */

inherit "/std/receptacle";
#include <macros.h>
#include "/sys/stdproperties.h";

void
create_receptacle()
{
    set_name("chest");
    set_adj("bronze");
    add_adj("treasure");
    set_pshort("bronze treasure chests");
   set_long("This well-crafted bronze treasure chest seems to "+
   "have been made long ago, but it looks as new and shiny "+
   "as if it were made yesterday. It has probably had a lot of attention. "+
   "Probably it contains lots and lots of treasure.\n");
    set_key("BIG_Chest_Key");
    set_pick(49);

    add_prop(CONT_I_WEIGHT, 50900); 	/* It weights 4500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 200000); 	/* It can hold 14500 grams. */
    add_prop(CONT_I_VOLUME, 190000); 	/* 1.9 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 600000); 	/* 6 litres of volume */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
//   add_prop(CONT_I_CLOSED, 1);
//   add_prop(CONT_I_LOCK,   1);
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

