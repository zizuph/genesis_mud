
/*
 * claws.c
 * Created by Pasqua with the help of Mercade who made the examlple 
 * /w/mercade/open/dragonscale_greaves.c 21 May 2006 to demonstrate
 * how to create an armour(gauntlets) that will prevent the wearer 
 * from wielding anything.
 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("claws");
    set_short("pair of dragon claws");
    set_pshort("pairs of dragon claws");
    set_long("This is the vicious claws from the black dragon in Terel.\n");

    set_adj( ({ "pair", "pairs", "of", "dragon claws" }) );

    set_ac(40);
    set_at(A_HANDS);
}

/*
 * Function name: query_slots
 * Description  : We mask the query_slots to add the weapon tool slots for
 *                the hands. This way, these slots will also be covered by
 *                this item, and the user cannot wield anything in these
 *                locations.
 * Returns      : int * - the normal (armour) slots plus the two weapon slots
 *                    we want to block.
 */
int *
query_slots()
{
    int *my_slots = ::query_slots();

    if (!pointerp(my_slots))
    {
        return ({ });
    }

    /* Let this weapon also block the two weapon hands. */
    return my_slots + ({ W_LEFT, W_RIGHT });
}

/* Will give this item speed and unarmed boost 
 * It will be a powerful unarmed aid
 */