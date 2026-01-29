/* ARGOS - Metro - A quill
**
** This quill is part of the Registry Tour quest
** The quill is gotten in rooms/bank with 'ask bursar for quill'
** The quill is then taken to rooms/visitctr, dipped in ink and
**    used to sign the registry.
**
*/
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "../tours.h"
 
void create_object() {
   set_name("quill");
   add_name(REG_TOUR_QUILL);
   set_adj(({"fluffy","blue"}));
   set_short("fluffy blue quill");
   set_long("@@exa_long");
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_VALUE, 1);
}
 
string exa_long() {
   string desc="It is a quill used for writing, made of a large fluffy "+
               "blue feather. ";
   if (this_object()->query_prop(REG_TOUR_DIPPED))
      return (desc+"It has ink on its tip.\n");
   else
      return (desc+"\n");
}
