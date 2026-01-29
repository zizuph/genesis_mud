#pragma save_binary

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_object()
{
  set_name("mark");
  add_name("sticks");
  set_short("@@short_func");
  set_long("@@long_func");
  add_prop(OBJ_I_HIDE,10);
}

long_func()
{
  if (TP->query_guild_name_occ()=="Gondorian Rangers Guild")
    return "A Ranger has left a secret mark here, well camouflaged.\n"+
      "It points to the north.\n";
  else return "They are only some uninteresting sticks and leaves.\n";
}

short_func()
{
  if (TP->query_guild_name_occ() == "Gondorian Rangers Guild")
    return "secret mark from a Ranger";
  else return "few uninteresting sticks";
}
