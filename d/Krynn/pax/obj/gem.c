/*
   gem.c
   -----

   Coded ........: 95/05/09
   By ...........: Jeremiah

   Latest update : 95/05/09
   By ...........: Jeremiah

   Gem to open the entrance to Sla mori

*/

inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


void
create_object()
{
   set_name(({"gem", "sla_mori_gem"}));
   add_adj(({"green", "shiny", "small", "beautiful"}));
   set_short("green gem");
   set_long("This is a small shiny green gem. It is a very beautiful " +
            "stone. The light of the sun sparkles through the green " +
            "glasslike material.\n");
   set_keep(1);
   
   add_prop(OBJ_I_VALUE, 30);
   add_prop(OBJ_I_WEIGHT,20);
   add_prop(OBJ_I_VOLUME,20);
}
