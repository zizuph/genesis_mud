#pragma save_binary

inherit "/std/object";

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>

query_recover()
{
  string name;
  int i;
  sscanf(file_name(this_object()),"%s#%d", name, i);
  return name;
}

string mylong()
{
  if(TP->query_skill(SS_APPR_OBJ)>40)
    return "At the first look this appears to be a gold bar, but when you\n"+
      "examine it closer you realize that it is nothing but painted lead.\n";
  
  return "This is a small bar of what appears to be perfectly good gold.\n";
}

create_object()
{
  set_short("gold bar");
  set_long("@@mylong");

  set_name("bar");
  set_adj("gold");

  add_prop(OBJ_I_VALUE,300);
  add_prop(OBJ_I_WEIGHT,1930);
  add_prop(OBJ_I_VOLUME,100);
}