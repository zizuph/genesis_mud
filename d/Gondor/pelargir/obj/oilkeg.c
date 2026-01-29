/*
 * /d/Gondor/pelargir/obj/oilkeg.c
 *
 * This is a large keg of oil that Lumendil the lighthouse
 * attendant appears to use when filling the beacon lantern.
 *
 * Original idea and coding by Lord Elessar Telcontar as "oil-flask"
 * Recoded for use with /std/torch.c by Mercade, 30 October 1993
 *
 * Revision history:
 *
 * -  4 Sep 1996, Olorin: Modified to use /lib/keep.
 *                        Modified to use functions for VBFC.
 *    8/13/98 - Modified version of /Gondor/common/obj/oilkeg
 *              to become Lumendil's lantern oil supply by Tyr
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 *
 * limited dispensation re coding standard granted because this is
 * existing code -- gnad
 */

#pragma strict_types

inherit "/std/object.c";
inherit "/lib/keep.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
void   create_object();
string short_description();
string long_description();

void
create_object()
{
    set_name("oil");
    add_adj( ({ "keg", "of" }) );
    add_adj("oil");
    add_name("keg");
    add_name("oil-keg");
    add_name("oilkeg");
    add_name("lamp-oil");
    add_name("_large_keg_of_oil_");
    add_adj("lamp");

    set_short(short_description);
    set_long(long_description);

    set_no_show_composite(1);   /* makes keg "non-obvious" */

    add_prop(OBJ_M_NO_GET, "The keg is far too heavy to lift.\n");
} /* end create_object */

string
short_description()
{
    return "keg of oil";
} /* end short_description */

string
long_description()
{
    string long_desc = "It is an extremely large wooden oil-keg. "+
        "It was designed to contain lamp-oil.";
} /* end long_description */
