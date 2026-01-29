inherit "/std/object";
#include "/d/Gondor/defs.h"

#include "/sys/stdproperties.h";

create_object() {
  set_short("set of beaten silver plates");
  set_long(BSN("A set of beaten silver dishes, lost long ago by "+
    "some wealthy family."));
  set_name(({"Xeros_Plates"}));
  add_name(({"plates","dishes"}));
  set_adj("silver");
  add_adj("beaten");
  add_prop(OBJ_I_WEIGHT,87);
  add_prop(OBJ_I_VOLUME,25);
  add_prop(OBJ_I_VALUE,280+random(36));
  add_prop("_gilraen_wolfcave_quest_plates",1);
}

