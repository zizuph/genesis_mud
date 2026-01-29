/*
 * /d/Gondor/ithilien/forest/harad_earring.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

public int	no_wear(string str);

public void
create_object()
{
    set_name("earrings");
    set_adj("golden");
    set_short("pair of golden earrings");
    set_pshort("pairs of golden earrings");
    set_long(BSN("These wide golden earrings are typically worn by the "+
	"Southrons from Harad."));
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,40);
    add_prop(OBJ_I_VALUE,720);
}

public void
init()
{
    ::init();
    add_action(no_wear,"wear");
}

public int
no_wear(string str)
{
    if ( str == "earrings" || str == "golden earrings" ||
    str == "pair of golden earrings" )
    {
	write("You can't seem to fit the earrings into your ears.\n");
	return 1;
    }
    return 0;
}

