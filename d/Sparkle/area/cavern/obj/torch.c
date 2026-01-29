#include "/sys/stdproperties.h"

#pragma save_binary

inherit "/std/object";

create_object()
{
  set_name("torch");
  set_pname("torches");
  set_short("torch");
  set_long("A short piece of wood, soaked with pitch.\n");
  add_prop(OBJ_I_LIGHT,0);

}

init()
{
  add_action("light","light");
  add_action("extinguish","extinguish");
}


light(string str)
{
  if(str!="torch") {
    notify_fail("Light what?\n");
    return 0;
  }
  if(query_prop(OBJ_I_LIGHT)!=0) {
    notify_fail("It is already lit!\n");
    return 0;
  }
  change_prop(OBJ_I_LIGHT,1);
  return 1;
}

extinguish(string str)
{
  if(str!="torch") {
    notify_fail("Extinguish what?\n");
    return 0;
  }
  if(query_prop(OBJ_I_LIGHT)==0) {
    notify_fail("It is not lit!\n");
    return 0;
  }

  change_prop(OBJ_I_LIGHT,0);
  return 1;
}