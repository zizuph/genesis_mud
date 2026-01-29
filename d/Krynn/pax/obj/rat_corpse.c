/*
   rat_corpse.c
   ------------

   Coded ........: 95/05/19
   By ...........: Jeremiah

   Latest update : 95/05/19
   By ...........: Jeremiah

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


void
create_object()
{
   set_name(({"corpse", "rat", "_rat_corpse_"}));
   set_short("corpse of a grey hairy rat");
   set_long("This is the corpse of a grey hairy rat.\n"); 

   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT,1200);
   add_prop(OBJ_I_VOLUME,800);
}
