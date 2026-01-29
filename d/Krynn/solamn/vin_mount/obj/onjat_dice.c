inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"


void
create_object()
{
   set_name("dice");
   add_name("_dougan_onjat_dice");
   set_adj("onjat");
   set_short("a pair of onjat dice");
   set_pshort("pairs of onjat dice");
   set_long("A pair of dice used for Onjat, a popular game in the " +
     "gambling dens of the major cities of Krynn. This pair of dice " +
     "looks suspiciously like it has had a few edges shaved back. " +
     "On both die you notice the initials 'D.R' carved on the sole " +
     "blank face of both.\n");
   
   add_prop(OBJ_I_VALUE, 30);
   add_prop(OBJ_I_WEIGHT,20);
   add_prop(OBJ_I_VOLUME,20);
   add_prop(OBJ_I_VALUE, 1200);
}
