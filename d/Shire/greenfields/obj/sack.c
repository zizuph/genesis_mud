/*
 * sack.c
 *
 * A simple rugged sack which makes you able to carry more.
 *
 */

inherit "/std/receptacle";

#include "/d/Shire/common/obj/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

/*
 *  Description: Constructor.
 */
public void
create_container()
{
    set_name("sack");
    set_pname("sacks");
    set_adj( ({ "rugged","old" }) );
    set_short("old rugged sack");
    set_pshort("old rugged sacks");
    set_long("This is an old, well-used, rugged sack.\n");
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 60*1000);       /* 60 l          */
    add_prop(CONT_I_MAX_WEIGHT, 300*1000);      /* 300 kg        */
    add_prop(CONT_I_CLOSED,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,	0);
    add_prop(OBJ_M_NO_SELL,	"@@check_sell@@");
    add_prop(OBJ_I_VALUE,	86);
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
	return "There are things in the sack! Empty it first.\n";
    else
	return 0;
}

string
short(object for_obj)
{
    if (query_prop(CONT_I_CLOSED))
	return "closed " + ::real_short(for_obj);
    else
	return "open " + ::real_short(for_obj);
}
