/*********************************************************

  This is a feather that is used by the Elemental
  Worshippers of Calia for their air spells Anemos
  and Stous.

  Originally coded by Jaacar  Date Unknown.
  Modified by Quintas  June 2003
  Modifications : Added name FEATHER to give it a unique
                  name so that only this feather 
                  is consumed when the Worshippers
                  cast their spells.

                  FEATHER is also defined in :

                  ~Calia/worshippers/spells/anemos.h
                  ~Calia/worshippers/spells/stous.h

***********************************************************/


inherit "/std/heap";

#include <stdproperties.h>
#include "defs.h"

#define FEATHER "_worshipper_feather_id_"

create_heap()
{
    set_name("feather");
    add_name("white feather");
    add_name(FEATHER);
    add_pname("feathers");
    add_pname("white feathers");
    set_short("white feather");
    set_pshort("white feathers");
    set_long("It's a small white feather.  It looks like it "+
        "might have come from a pigeon.\n");
    set_heap_size(1);
    add_prop(OBJ_M_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,0);
    add_prop(HEAP_I_UNIT_WEIGHT,0);
    add_prop(HEAP_I_UNIT_VALUE,0);
    add_prop(HEAP_S_UNIQUE_ID, "white feather");
}
