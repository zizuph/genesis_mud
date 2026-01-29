//   Replaced the IM_TELL_FILE functions  -Igneous- Dec 5th 96
#include "defs.h"
#include <stdproperties.h>

inherit "/std/object";

create_object()
{
   set_name("cylinder");
   set_short("cylinder");
   set_long(
      "A long cylinder with a string attached to it.\n");
   add_item("string",
      "A string which is attached to the cylinder.\n");
   add_prop(OBJ_I_WEIGHT, 460);
   add_prop(OBJ_I_VOLUME, 349);
   add_prop(OBJ_I_VALUE, 100);
}

init()
{
   ::init();
   add_action("do_pull", "pull");
}

do_pull(string what)
{
   if(what!="string")
      return notify_fail("Pull what?\n");
   
   write("You pull the string attached to the cylinder.\n"
      + "Suddenly, the cylinder puffs into smoke!\n"
      + "Instead, a heavy boat of wood appears right in front of you!\n"
      + "The boat seems far to heavy to carry.\n");
   say(QCTNAME(TP)+" pulls the string attaches to the cylinder.\n"
      + "Suddenly, the cylinder puffs into smoke!\n"
      + "Instead, a heavy boat of wood appears right in front of "
      +QTNAME(TP)+"!\nThe boat seems far to heavy to carry.\n");
   FIXEUID;
   clone_object(MORIA_OBJ+"raft")->move(ETP);
   TO->remove_object();
   return 1;
}
