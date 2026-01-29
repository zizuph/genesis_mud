/*
 * Sandals for Faerie Leather Shop
 * Finwe, April 2005
 */

#include "defs.h"
#include <stdproperties.h>
#include <wa_types.h>

inherit FOOTWEAR_BASE;

void
create_shoes()
{
    setuid(); seteuid(getuid());

    set_name("sandals");
    set_short("pair of leather sandals");
    set_pshort("pairs of leather sandals");
    add_adj(({"leather"}));
    set_long("It is a piece of stiff, brown leather that is strapped " +
        "to the foot. Wide, supple, brown, leather straps are used " +
        "to secure the sandals to the feet.\n");
}

void
leave_env(object from, object to)
{
    ::leave_env();
}

