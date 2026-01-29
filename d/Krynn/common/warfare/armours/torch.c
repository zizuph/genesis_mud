/*
 * A torch.
 */
 
inherit "/std/torch";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

create_torch()
{
    set_name("torch");
    set_short("wooden torch");
    set_long("A standard torch of some wood that you don't recognise. "+
         "it creates an impressive amount of light.\n");       
    set_strength(5);

}

