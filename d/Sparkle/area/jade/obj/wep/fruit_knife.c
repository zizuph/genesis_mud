/* /d/Sparkle/area/jade/fruit_knife.c
*  Created 2017-05-09 by Martin Berka on Genesis MUD
*  Based on bansword.c by Varian
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
    
    set_name( ({"knife"}) );
    set_pname( ({"knives"}) );
    set_short("paring knife");
    set_pshort("paring knives");
    set_adj( ({"paring"}) );
    set_long("This knife is has a short, straight blade with a sharp tip, "
        + "perfect for peeling and slicing fruits, or anything else of "
        + "limited thickness. Its green, wooden handle is a mottled "
        + "rainbow of juice stains, green, blue, red. Probably juice stains.\n");

    set_hit(28);
    set_pen(25);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 70);
    add_prop(OBJ_I_VOLUME, 70);

}

init()
{
    ::init();
    add_action("do_peer", "knife");
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
    if (!str)
    {
        str = "with interest";
    }

    write("You peer " + str +
        " at the sharp tip of a stained paring knife.\n");
    SAYBB(" peers " + str + " at the sharp tip of a stained paring knife.");
    return 1;
}
