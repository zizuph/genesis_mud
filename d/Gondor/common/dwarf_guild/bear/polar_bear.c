/*
 * /d/Gondor/common/dwarf_guild/bear/polar_bear.c
 *
 * A friend from Bearlin, this is a polar bear.
 *
 * Created by Mercade, 24 October 2007.
 */

#pragma strict_types

inherit "/d/Gondor/common/dwarf_guild/bear/bear";

#include <language.h>
#include <stdproperties.h>

/*
 * Function name: create_container
 * Description  : Creator.
 */
void
create_container()
{
    ::create_container();

    remove_adj("rather");
    remove_adj("large");
    add_adj("jr");
    add_adj("polar");

    set_short("cute furry jr polar bear");
    set_pshort("cute furry jr polar bears");
}


/*
 * Function name: bear_long
 */
string
bear_long()
{
    string sDesc = "It is a very cute and growing teddybear. It is fluffy " +
                   "and furry and totally white. It has everything you ever " +
                   "looked for in a teddy and looks very huggable.";
    if (oDress)
    {
         sDesc += " It is dressed in " + LANG_ASHORT(oDress) + ".";
    }
    
    sDesc += "\n";
    
    return sDesc;
}
