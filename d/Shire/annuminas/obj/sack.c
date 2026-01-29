/*
 * sack.c
 *
 * A simple rugged sack which makes you able to carry more.
 *
 */

inherit "/std/receptacle";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>

/*
 *  Description: Constructor.
 */
public void
create_container()
{
    set_name("_annuminas_sack_");
    add_name("bag");
    set_pname("bags");
    set_adj( ({ "fine","linen" }) );
    set_short("fine linen sack");
    set_pshort("fine linen sacks");
    set_long("This is a large canvas sack, smelling of blood.\n");
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_WEIGHT,     1200);          /* 1.2 kg        */
    add_prop(CONT_I_VOLUME,     500);           /* Empty volume. */
    add_prop(CONT_I_MAX_VOLUME, 3*1000);       /* 3.0 l          */
    add_prop(CONT_I_MAX_WEIGHT, 5*1000);      /* 5.0 kg        */
    add_prop(CONT_I_CLOSED,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(CONT_I_TRANSP,	0);
    add_prop(OBJ_M_NO_SELL,	"@@check_sell@@");
    add_prop(OBJ_I_VALUE,	50+random(11));
}

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
	return "There are things in the "+short()+"! Empty it first.\n";
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

