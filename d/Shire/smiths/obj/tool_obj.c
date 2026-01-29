/*
 *   Fake invisible toolobject to be autoloaded
 *   to the smith
 */

#pragma save_binary;

inherit "/std/object";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "smiths.h"

void
create_object() {
   set_name("_forge_tool_object_");

   add_prop(OBJ_I_VALUE,0);
   add_prop(OBJ_I_WEIGHT,0);
   add_prop(OBJ_I_VOLUME,0);

   add_prop(OBJ_M_NO_DROP, "");
   add_prop(OBJ_M_NO_GIVE, "");
   add_prop(OBJ_M_NO_SELL, "");
   add_prop(OBJ_M_NO_STEAL,"");

   set_no_show();
}

init() {
   ::init();

   set_alarm(1.0, 0.0, "verify_me", TP);
}

int
verify_me(object ob) {
   // Temp fix while fixing personal tools.
   TO->remove_object();
   return 1;
   if (!IS_MEMBER(ob)) {
      TO->remove_object();
   }
   return 0;
}

string
query_auto_load() { return MASTER + ":"; }

public string
query_recover() { return 0; }
