/*
 * A small chest 940618, belongs to Mzzz, Lt of the orc camp
 */

/* Not really. This chest is sold by the cart salesman on the Eastroad */
/* Dunstable */
inherit "/std/receptacle";
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define WEAPON  "/d/Shire/evendim/wep/"
#define ARMOUR  "/d/Shire/evendim/arm/"

void reset_chest();

void
create_receptacle()
{
    set_name("_buried_sack_");
    add_name("sack");
    set_pname("sacks");
    set_adj( ({ "dirty","canvas" }) );
    set_short("dirty canvas sack");
    set_pshort("dirty canvas sacks");
    set_long("This is a large dirty canvas sack. It is " +
        "encrusted with dirt and looks like it has been buried " +
        "for some time. It can probably hold quite a bit of " +
        "stuff still.\n");


    add_prop(CONT_I_WEIGHT, 2500); 	/* It weights 2500 grams */
    add_prop(CONT_I_MAX_WEIGHT, 10000); 	/* It can hold 10000 grams. */
    add_prop(CONT_I_VOLUME, 1000); 	/* 1 l volume (very small) */
    add_prop(CONT_I_MAX_VOLUME, 3000); 	/* 3 litres of volume */
    add_prop(CONT_I_RIGID, 1);            /* It is a rigid object   */
   add_prop(CONT_I_CLOSED, 1);
 //   add_prop(CONT_I_LOCK,   1);
    add_prop(OBJ_M_NO_SELL,"@@no_sell");
    add_prop(OBJ_I_VALUE, 120); 		/* Worth 120 cc */
    reset_chest();

}

query_recover() { return MASTER + ":"; }

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

    setuid(); seteuid(getuid());
    if (!present("dagger"))
        clone_object(WEAPON + "dagger")->move(this_object(), 1);
    if (!present("helmet"))
        clone_object(ARMOUR + "helm")->move(this_object(), 1);
    if (!present("platemail"))
        clone_object(ARMOUR + "pmail")->move(this_object(), 1);

    if (!present("coin"))
	MONEY_MAKE_SC(random(22))->move(this_object(), 1);
  	MONEY_MAKE_CC(random(47))->move(this_object(), 1);
   	MONEY_MAKE_GC(random(6))->move(this_object(), 1);
}


string clean_lock()
{
    return "You attempt to clean the dirt out of the lock. You " +
    "get most of it out, but it still looks jammed and broken.\n";
}

