/* File:          /d/Khalakhor/ship/macdunn/ansalon/apple.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Modifications:
 * Purpose:       This is an apple, of which many are placed in the
 *                crate on the ship between Faerie and Khalakhor.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/ship/macdunn/faerie/crate.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h";

public void
create_food()
{
    set_amount(5);
    set_name("crabapple");
    add_name(({"fruit","food","apple"}));
    set_pname("crabapples");
    add_pname(({"fruits","food","apples"}));
    set_adj("green");
    add_adj("crab");
    set_short("green crabapple");
    set_pshort("green crabapples");
    set_long("This is a green crabapple, a favourite snack of " +
      "sailors due to its compact size and resilience.\n");
}

/*
public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
      ", causing your face to pucker from the tartness!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
      ", causing " + HIS + " face to pucker from the tartness!\n");
}
*/
