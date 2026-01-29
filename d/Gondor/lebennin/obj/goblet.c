inherit "/std/object";
#include "/d/Gondor/defs.h"

#include "/sys/stdproperties.h";

create_object() {
  set_short("beaten silver goblet");
  set_long(BSN("A gem encrusted, beaten silver goblet, lost long ago by "+
    "some wealthy family."));
  set_name(({"Xeros_Goblet"}));
  add_name(({"goblet"}));
  set_adj("silver");
  add_adj("beaten");
  add_prop(OBJ_I_WEIGHT,95);
  add_prop(OBJ_I_VOLUME,45);
  add_prop(OBJ_I_VALUE,300+random(26));
  add_prop("_gilraen_wolfcave_quest_goblet",1);
}

