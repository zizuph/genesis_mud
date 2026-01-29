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
    set_name("prune");
    set_pname("prunes");
    set_adj("dried");
    set_short("dried prune");
    set_pshort("dried prunes");
    set_long("A dried prune. You think you need the extra fiber "+
	"in your diet.\n");
}

public void
consume_text(object *arr, string vb)
{
    string str;

    if(this_player()->query_wiz_level())
    {
	write("You " + vb + " " + (str=COMPOSITE_DEAD(arr)) +
	", suddenly feeling like you should leave and visit "+
	"the bathroom!\n");
	say(QCTNAME(this_player()) + " " + vb + "s " + str +
	", then suddenly leaves ... apparantly to visit the "+
	"bathroom.\n");
	this_player()->remove_object();
    return;
}
    write("You eat gross, yukky putrid prune.\n");
    say(QCTNAME(this_player()) + " eats a yukky prune.\n");
}
