// path:         /d/Avenir/common/outpost/obj/food/steak.c
// creator(s):   Lilith May 2022
// desc:         Steak for the Fort dining hall.
// note:         

inherit "/std/food";
inherit "/lib/commands";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <adverbs.h>
#include "/d/Avenir/common/outpost/outpost.h"

void
create_food()
{
    set_amount(250);
    set_name(({"steak", "meat"}));
    set_long("This is a thick and juicy steak cut from the loin of "+
        "a phrynos. It has been seared to perfection, sprinkled with "+
        "sybarun sea salt, and topped with a pat of butter. "+
        "The aroma is mouth-watering and it looks like it would be "+
        "quite filling.\n");
    set_short("perfectly-seared phrynos steak");
    add_name(({"thick steak", "tender steak", "phrynos steak", 
        "food", "phrynos" }));
	add_pname(({"steaks"}));
    add_adj(({"seared", "thick", "tender", "juicy", "phrynos", 
        "perfectly-seared"}));
	
} 

/*
 * int amnt = # of portions to try to eat.
 *            0 == try to eat all remaining.
 */
private int
try_to_eat(int amnt)
{

    if (!this_player()->eat_food())
    {
	write("The " + singular_short() + " is too much for you.\n");
	return 0;
    }

	special_effect(1);
    return 1;
}

public void
hook_smelled(string str)
{
    write("The scent of the seared meat is making your mouth water.\n");
}

public void
special_effect(int amnt)
{
    write("The "+ singular_short() +" is tender enough to melt "+
        "in your mouth.\n");
}


