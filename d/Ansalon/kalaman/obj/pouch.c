/* Backpack for VK, based on Maniac's Calian Backpack. */
/* Morrigan and Teth, Jan/Feb 97 */
/* Arman, May 97 */

#pragma save_binary

inherit "/d/Genesis/std/pack";
inherit "/lib/keep"; 

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Ansalon/common/defs.h"

object this;

void
create_pack()
{
    set_name("pouch");
    set_pname("pouches");
    set_short("leather pouch");
    set_pshort("leather pouches");
    set_adj("leather");
    set_long("This is an average sized pouch often used by merchants to keep their " +
      "valuables in. You may <fill> and <empty> the pouch as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 800);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_VOLUME, 150000); /* ml */

    add_prop(OBJ_I_VALUE, 100);

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

