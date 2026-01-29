#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include "herald.h"
#include "/d/Shire/common/defs.h"


void
create_object()
{
   set_name("acorn");
   add_name(({"holy acorn","herald acorn"}));
   add_adj(({"shining","yellow"}));
   set_short("shining yellow acorn");
   set_long("This shining yellow acorn glows with a light of "+
   "its own.  It looks very unusual indeed.\n");

   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_NO_GET, 1);

}