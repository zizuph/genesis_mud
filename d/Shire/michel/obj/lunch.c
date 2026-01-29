inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/defs.h"

/* Lunch object for the Dondel lunch quest - Dunstable July 1994 */

void
create_object()
{
   set_name("lunch");
   add_name(({"_lunch_","bag","sack"}));
   add_adj(({"brown","wrapped"}));
   set_long("This is the lunch you are supposed to take to Dondel.\n");
   set_short("brown wrapped lunch");
   set_pshort("brown wrapped lunches"); /* This should never happen */
   set_pname("lunches"); /* Nor this */

   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_VALUE, 0); /* Don't want people cheating the quest  */

}
