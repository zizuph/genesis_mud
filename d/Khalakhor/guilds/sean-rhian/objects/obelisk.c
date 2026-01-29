/* Obelisk in the garden of MacDunn kirk; marker for a mass grave
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/19/98     Zima        Created
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include "/sys/ss_types.h"
#include "defs.h"
 
void create_object() {
    set_name("obelisk");
    add_name(({"monument","gravestone"}));
    set_adj(({"tall","granite"}));
    set_short("tall granite obelisk");
    set_long(
       "It is a tall granite obelisk, a stone shaft with four tapering "+
       "sides, its top angled to a point. There is writing on its face.\n");
 
   add_item("writing",
      "It is written in strange lettering, but perhaps you can read it.\n");
   add_cmd_item(({"lettering","obelisk","writing"}),"read","@@read");
 
    add_prop(OBJ_I_NO_GET, 1);
}
 
string read() {
   if ((TP->query_skill(SS_LANGUAGE))>40)
      return ("It reads: Here lie the Martyrs of the Rebuilding. May "+
              "their sacrifice ever consecrate this ground, and may "+
              "they rest in the peace and harmony of Ardaugh forever.\n");
   return "You can not make out the strange lettering.\n";
}
