/*
 * Chest that is on the mumak.c when it's killed in the haradrim camp
 * The chest is locked, and the key is cloned into a haradrim when the 
 * mumak dies.
 * -- Finwe, August 2005

 Palmer April 19, 2006:
 Lowered number of coins until exploit is fixed and this is reviewed.

 */

inherit "/std/receptacle";

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <ss_types.h>

void reset_chest();

void
create_receptacle()
{
    set_name("_mumak_chest_");
    add_name("chest");
    set_pname("chest");
    set_adj( ({ "strong","iron-bound" }) );
    set_short("strong iron-bound chest");
    set_long("This is a " + short() + ". It is made of wood and wrapped " +
        "with iron bands. The chest appears to be used to hold valuables.\n");


    add_prop(CONT_I_WEIGHT, 2500); 	/* It weights 2500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 10000); 	/* It can hold 10000 grams. */
    add_prop(CONT_I_VOLUME, 1000); 	/* 1 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 3000); 	/* 3 litres of volume */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK,   1);
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 120); 		/* Worth 120 cc */
    reset_chest();

}

// query_recover() { return MASTER + ":"; }

mixed
no_sell()
{
  if(sizeof(all_inventory(this_object())))
    return "The "+short()+" seems to still contain items in it.\n";
  return 0;
}

void
reset_chest()
{
    object weapon;


    if (!present("coin"))
	MONEY_MAKE_SC(500 + random(1000))->move(this_object(), 1); 
    MONEY_MAKE_GC(2 + random(10))->move(this_object(), 1);
  	/*MONEY_MAKE_GC(75 + random(50))->move(this_object(), 1);
   	 MONEY_MAKE_PC(25 + random(25))->move(this_object(), 1); */
}
