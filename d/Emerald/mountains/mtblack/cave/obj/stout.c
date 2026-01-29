/* A harsh stout for use in npcs - coded 28/12/95 by Tulix III */

inherit "/std/drink";

/* This line is put in to keep Mercade happy */
#pragma strict_types

#include <stdproperties.h>

public void
create_drink()
{
    set_name("stout");
    set_pname("stouts");
    set_adj("harsh");
    
    set_short("harsh stout");
    set_pshort("harsh stouts");
    set_long("A harsh stout that is probably better sold as shoe-polish.\n");
    
    set_soft_amount(270);
    set_alco_amount(25);
    
    add_prop(OBJ_I_WEIGHT, 270);
    add_prop(OBJ_I_VOLUME, 270);
}
