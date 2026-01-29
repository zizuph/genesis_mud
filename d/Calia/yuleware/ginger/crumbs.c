// OBJECT:  gingerbread crumbs

    /* Calia Domain

    HISTORY

    [2001-12-15] Created by Uhclem from
        [C:\CALIA\YULEWARE\GINGER\CRUMB.DOC].

    PURPOSE

    An edible trash object invented to satisfy players' curiosity about the
    conservation of gingerbread when a 1Kg gingerbread house is broken to
    reveal a single 1g gingerbread man.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include "defs.h"

// FUNCTIONS

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    write("The " + short() + " smells of many spices, but" +
        " the strongest scent is of ginger.\n");

}

// OBJECT DEFINITION

void
create_food()

{

    /*
     *  DESCRIPTION    
     */

    set_name("gingerbread");  /*  first word of description  */
    add_name("piece");
    set_adj("gingerbread");  /*  so player can take 'gingerbread piece'  */
    set_short("piece of gingerbread");
    set_pshort("pieces of gingerbread");

    set_long("It's a piece of gingerbread with ragged edges in a roughly" +
        " rectangular shape; a little icing is spread on it.\n");

    /*
     *  PROPERTIES    
     */

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_VALUE, 1);

    add_prop(OBJ_M_NO_SELL, "Demand for secondhand gingerbread is," +
        " alas, at an all-time low; you would do better to trade" +
        " in a commodity that people actually wanted.\n");

    /*
     *  ITEMS    
     */

    add_item(({"icing", "multicolored icing"}),
        "There is a little icing smeared on the gingerbread," +
        " a few streaky colors that probably rubbed" +
        " off something else.\n");

    add_item(({"shape", "rectangular shape", "edges", "edge",
        "ragged edge", "ragged edges"}),
        "The edges seem to be broken rather than cut, and" +
        " the rectangular shape suggests that this was a flat" +
        " section of some larger piece of gingerbread.\n");

}
