/* File:          /d/Khalakhor/ship/macdunn/ansalon/pickle.c
 * Creator:       Teth
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This is a pickle, of which many are placed in the
 *                barrel on the way to Khalakhor or Kalaman.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/ship/macdunn/ansalon/barrel.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>

public void
create_food()
{
    set_amount(10);
    set_name("pickle");
    add_name(({"gherkin","food"}));
    set_pname("pickles");
    add_pname(({"gherkins","food"}));
    set_adj("green");
    set_short("green pickle");
    set_pshort("green pickles");
    set_long("A pale green cucumber soaked in a salty brine, and " +
      "flavoured with herbs.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
      ", revelling in the crunchy texture and salty taste!\n");
    say(QCTNAME(this_player()) + " " + vb + "s " + str +
      ", revelling in the crunchy texture and salty taste!\n");
}
