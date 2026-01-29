/* Sack for VK, based on Maniac's for Calia */
/* Teth and Morrigan, Jan/Feb 97 */

#pragma save_binary


inherit "/d/Genesis/std/pack";
inherit "/lib/keep"; 
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

void
create_pack()
{
    set_name("sack");
    set_pname("sacks");
    set_short("black leather sack");
    set_pshort("black leather sacks");
    set_adj(({"black", "leather"}));
    add_name("bag");
    add_pname("bags");
    set_long("This is an ordinary sack of fine black leather. Sacks "+
      "of this kind can be purchased in Vingaard Keep, as you see "+
      "from the small inscription on it: Vingaard Keep Equipment "+
      "Store. You may <fill> and <empty> the sack as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 1750); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 75000); /* grams */
    add_prop(CONT_I_VOLUME, 2000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 75000); /* ml */

    add_prop(OBJ_I_VALUE, 225); 		/* Worth 225 cc */
    set_alarm(0.1,0.0, "make_me_sack");
}


string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}


void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg); 
}


void
make_me_sack()
{
    remove_name("pack");
    remove_pname("packs");
}
