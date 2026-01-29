/* ARGOS - Metro - A spool of yarn spun by the seamstress in rooms/woolwrk
**
** Date      Coder     Action
** ________  _________ ____________________________
** 8/15/95   Zima      Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_object() {
   set_name("yarn");
   add_name(({ARGOS_YARN,"spool","spool of yarn"}));
   set_adj(({"large","wool"}));
   set_short("spool of yarn");
   set_pshort("spools of yarn");
   set_long(
      "It is a large spool of yarn recently spun from wool.\n");
   add_prop(OBJ_I_WEIGHT, 700);
   add_prop(OBJ_I_VOLUME, 700);
   add_prop(OBJ_I_VALUE, 10);
}
