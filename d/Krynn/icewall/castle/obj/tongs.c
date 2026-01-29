#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit "/std/object";

init() {
   ADA("get");
   ADD("get","take");
   ::init();
}

create_object() {
   set_short("pair of tongs");
   set_name("tongs");
   set_long("These are standard tongs used for getting things from "
      + "a fire without burning your hand.\n");
   
   add_prop(OBJ_M_NO_GET,"You can use them but you can't take them.\n");
}

int get(string arg) {
   object box;
   NF("Get what?\n");
   if (arg != "ember with tongs" && arg != "ember from fireplace"
         && arg != "ember from fireplace with tongues") return 0;
   if (!(box=P("kender_box",TP))) write("Where would you put it?\n");
   else {
      write("Using the tongs you get a hot ember from the fire "
         + "and place it into the box.\n");
      say(QCTNAME(TP)+" pokes around in the fire with the tongs.\n");
      seteuid(getuid());
      (clone_object(ICE_CAST_O+"ember"))->move(box);
      find_living("stevenson")->catch_msg(TP->query_name()
         + " has begun the Kender Quest!\n");
   }
   return 1;
}
