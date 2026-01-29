inherit "/std/object";
#include "/d/Gondor/defs.h"

#include "/sys/stdproperties.h";

create_object() {
  set_short("set of beaten silverware");
  set_long(BSN("A set of beaten silver forks, spoons, and knives, lost long ago by "+
    "some wealthy family."));
  set_name(({"Xeros_SilverWare"}));
  add_name(({"spoons","silverware","forks","knives"}));
  set_adj("silver");
  add_adj("beaten");
  add_prop(OBJ_I_WEIGHT,143);
  add_prop(OBJ_I_VOLUME,54);
  add_prop(OBJ_I_VALUE,290+random(36));
  add_prop("_gilraen_wolfcave_quest_forks",1);
}

