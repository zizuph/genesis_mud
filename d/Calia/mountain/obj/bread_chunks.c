// OBJECT:  bread_chunks

    /* Calia Domain

    HISTORY

    [96-02-21] Created by Uhclem from [C:\CALIA\MOUNTAIN\OBJ\BREAD_CH.DOC].

    PURPOSE

    This pile of bread chunks is a quest item.  It is obtained by going to
    /d/Calia/mountain/croad/garden7 and "break"ing a loaf of bread.  Any bread
    will do.  The loaf of bread is then deducted from the player's inventory
    and replaced with the pile of bread chunks. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include "obj.h"

// OBJECT DEFINITION

void
create_food()

    {

    /*  DESCRIPTION  */

    set_name("chunks");
    add_name("pile");
    set_adj("bread");
    set_short("pile of bread chunks");
    set_pshort("piles of bread chunks");

    set_long("This bread has been broken into bite-size chunks " +
        "just the right size for feeding to friendly fish.\n");

    /*  PROPERTIES  */

    set_amount(50);

    }
