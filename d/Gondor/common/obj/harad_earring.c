/*  
 *  /d/Gondor/ithilien/forest/harad_earring.c
 *  Golden earrings worn by the haradrim.
 *  Updated August 25, 2001, Serif: made into armour, fixed wear cmd.
 *
 */

inherit "/std/armour";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>  
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

public int      do_wear(string str);

void
create_armour()
{
    set_name("earrings");
    set_adj("golden");
    set_short("pair of engraved golden earrings");
    set_pshort("pairs of engraved golden earrings");
    set_long("These earrings are wide and engraved. They are typically " +
        "worn by the high commanders of Southrons from Harad.\n");

    set_default_armour(12, A_EARS, ({ 0, 0, 0 }), 0);

    add_item(({"engravings"}),
        "They are ornate etchings and cover the surface of the earrings.\n");

    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,40);
    add_prop(OBJ_I_VALUE,800);
}

public void
init()
{
    ::init();
    add_action(do_wear,"wear");
}

public int
do_wear(string str)
{
    if ( str == "earrings" || str == "golden earrings" ||
    str == "pair of golden earrings" )
    {
    if (TP->query_name() != "Haradrim")
        {
        write("You do not have large enough piercings to wear the "
            + "golden earrings.\n");
        return 1;
        }
    }
    return 0;
}


