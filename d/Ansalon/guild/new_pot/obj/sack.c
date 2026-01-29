/* Shamelessly stolen from the backpack in PoT */

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

public varargs string
short(object for_obj)
{
    return ((query_prop(CONT_I_CLOSED)) ? "" : "open ") +
        real_short(for_obj);
}

public varargs string
plural_short(object for_obj)
{
    string plshort = ::plural_short(for_obj);
    
    return ((strlen(plshort)) ? (
        ((query_prop(CONT_I_CLOSED)) ? "" : "open ") + plshort) : 0);
}

void
create_wearable_pack()
{
    set_name("sack");
    set_pname("sacks");
    set_short("kender-hide sack");
    set_pshort("kender-hide sacks");
    set_adj(({"kender-hide"}));
    set_long("This is a sack made out of the hide of a kender. " +
    "You may <fill> and <empty> the " +
    "sack as you wish.\n");

    set_mass_storage(1); 

    set_keep(1); 

    add_prop(CONT_I_WEIGHT, 2000);      /* grams */
    add_prop(CONT_I_MAX_WEIGHT, 17000); /* grams */
    add_prop(CONT_I_VOLUME, 5000);      /* ml */
    add_prop(CONT_I_MAX_VOLUME, 20000); /* ml */

    add_prop(OBJ_I_VALUE, 300);                 /* Worth 450 cc */

    set_slots(A_WAIST);
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
