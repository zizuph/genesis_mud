/*
 * Chainmail for elf guards
 * - Finwe, August 2004
 *
 * Fixed and re-balanced non-working resistances.
 * - Arman, January 2021
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

mapping resistances = ([ MAGIC_I_RES_FIRE: 30 ]); 

void
create_armour()
{

    set_name("armour");
    add_name("chainmail");
    set_short("light elven chainmail");
    set_adj("light");
    set_adj("elven");
    set_long("This is a " + short() + ". It is a flexible piece of armour " +
        "made of metal rings, linked together to form a flexible metal " +
        "shirt. The rings are woven together tightly, and designed to " +
        "protect the wearer.\n");
    set_ac( 33 );
    set_at( A_TORSO );
    set_am( ({ -4, -3, 7}) );   
    set_af( this_object() );   
    
    add_prop(OBJ_I_VALUE, 800);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 2700);

    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
	({  "This " + short() + " is designed to protect the body.\n", 1,
	    "It protects you against fire magic.\n",20 }) );

}

mixed
query_magic_protection(string prop, object who)
{
    if (who != query_worn() || !resistances[prop])
        return 0;

    return ({ resistances[prop], 1 });
}

mixed
wear(object ob)
{
    this_player()->add_magic_effect(this_object());
}

mixed
remove(object to)
{ 
    this_player()->remove_magic_effect(this_object());
}
