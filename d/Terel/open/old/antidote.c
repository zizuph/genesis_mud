/*
 * /doc/examples/poison/antidote_potion.c
 * Written by Quis, 920605
 */

inherit "/std/drink.c";
#include <stdproperties.h>
/*
 * We just make a generic drink, with no healing powers.
 * (We'll use the same description as the poison_potion, to be evil 8)
 */



create_drink()
{
    set_soft_amount(0); 
    set_alco_amount(0); 
    set_name("potion"); 
    set_short("potion"); 
    set_long("This potion bubbles and fumes.\n"); 
    add_prop(OBJ_I_VALUE, 144);
}

/*
 * We need to intercept the activating command for the drink.
 * so, we redefine drink_one_thing() from /std/drink.c
 */

int
drink_one_thing(object ob)
{
    int check;
    object *inv;
    int i;
    int strength;
    string *types;

/*
 * We will set up a 1-100 bell curve for the strength of the potion.
 * Since it is a magical potion, it will cure all poisons.  (This
 * should not be the norm!)
 */

/*
    strength = (random(10) + 1)*(random(10) + 1);

    Testing...
*/
    strength = 100;
    types = ({"all"});

/*
 * First, we call the original function.  Only if non-zero is returned do
 * we start the poison.  We will eventually return the original
 * drink_one_thing value.
 */
    check = ::drink_one_thing(ob);
    if(check) {
/*
 * Note that we shouldn't do a "deep_inventory".  All poison must be on
 * the top level.  This will allow a gettable living to be poisoned, 
 * where the living does not get cured when the carrier does.
 */
        inv = all_inventory(this_player());

/* Cycle through each element of the inventory.  If "cure_poison"
 *exists, we must have a poison object, so we call it with the right
 *arguments.
 */
        for (i = 0; i < sizeof(all_inventory(this_player())); i++ ) {
            if(function_exists("cure_poison",inv[i]) == "/std/poison_effect") 
	    {
                inv[i]->cure_poison(types, strength);
		strength = strength / 2;
	    }
        }
    }

    return check;
}
