/* /d/Sparkle/area/jade/obj/wep/billhook.c
*  Created 2017-05-29 by Martin Berka on Genesis MUD
*/

inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <wa_types.h>

int do_peer(string str);

void
create_weapon()
{
    int rand;

    set_name( ({"billhook"}) );
    set_pname( ({"billhooks"}) );
    set_short("wide billhook");
    set_adj( ({"wide"}) );
    set_long("The billhook has a wide blade which curves almost 90 degrees "
        + "at the end. It is meant for trimming tree branches, and is stained "
        + "with plenty of sap.\n");

    set_hit(28);
    set_pen(25);
    set_wt(W_KNIFE);
    set_dt(W_SLASH); //Hard to stab with this blade shape
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

}

init()
{
    ::init();
    add_action("do_peer", "test");
}

/*
 * Function name: do_peer
 * Description	: Emote: peer at the knife.
 * Arguments	: (string) str - adverb to emote
 * Returns		: (int) 1 - command recognized
 */
int
do_peer(string str)
{
    //FIND HOW TO CALL THIS - REFER HERB JAM
    str = find_object("/lib/commands.c")->check_adverb(str);
    if (strlen(str) < 4)
    {
        str = "";
    }
    else
    {
        str = str + " ";
    }

    write("You " + str + "test the billhook blade while "
        + "peering around for something to prune.\n");
    SAYBB(str + "tests the curved blade of a wide billhook while "
        + "peering around for something to prune.");
    return 1;
}
