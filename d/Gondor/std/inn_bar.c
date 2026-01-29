/*
 *  /d/Gondor/std/inn_bar.c
 *
 *  Generic bar for use in combination with /d/Gondor/lib/inn.c
 *  Will be used by the inn to put stuff on when a player can't carry
 *  his/her order.
 *
 *  Will only accept food / drinks / coins to be placed on top of it.
 *
 *  Override create_container to alter it's appearance.
 *
 *  Eowul, April 6th, 2015
 */

#pragma strict_types
#pragma save_binary 

#include <stdproperties.h>
#include <files.h>

inherit "/std/container";

/*
 * Function name: create_container
 * Description:   Default bar, reconfigure to define your own
 */
void
create_container()
{
    set_short("wooden bar");
    set_name("bar");
    set_adj("wooden");
    set_long("It's a ordinary wooden bar.\n");

    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 1000000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(OBJ_M_NO_GET, 1);

    set_no_show_composite(1);
}


/*
 * Function name: prevent_enter
 * Description:   Prevent anything other than food/drink/coins from being
 *                placed on top of the bar.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int 
prevent_enter(object ob)
{
    if (IS_DRINK_OBJECT(ob)) return 0;
    if (IS_FOOD_OBJECT(ob)) return 0;
    if (IS_COINS_OBJECT(ob)) return 0;

    write("As you attempt to put " + ob->short() + " on the " + short() 
        + ", a serving maid reminds you that the " + short() + " is only "
        + "for food and drinks.\n");
    return 1;
}
