#pragma save_binary

inherit "/std/container";

#include "/d/Roke/common/defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>



mylong()
{
  string s;

  s="This is a metal-reinforced wooden chest used to keep valuables.\n";

  if(query_prop(CONT_I_CLOSED))
    return s+"The chest is closed.\n";

  return s+"The chest is open.\n";
}
create_container()
{
  seteuid(getuid());

  set_short("treasure chest");
  set_long("@@mylong");
  set_name("chest");
  set_adj("treasure");

  add_prop(OBJ_I_VALUE,2000);

  add_prop(CONT_I_VOLUME,10000);
  add_prop(CONT_I_WEIGHT,10000);
  add_prop(CONT_I_REDUCE_WEIGHT,3);
  add_prop(CONT_I_REDUCE_VOLUME,3);

  add_prop(CONT_I_MAX_WEIGHT,40000);
  add_prop(CONT_I_MAX_VOLUME,40000);

  clone_object(CARISCA+"obj/goldbar")->move(TO);
  clone_object(CARISCA+"obj/goldbar")->move(TO);
  clone_object(CARISCA+"obj/goldbar")->move(TO);
  clone_object(CARISCA+"obj/goldbar")->move(TO);
  clone_object(CARISCA+"obj/goldbar")->move(TO);

  MONEY_MAKE_CC(1000)->move(TO);

  add_prop(CONT_I_CLOSED,1);
}
init()
{
  add_action("open","open");
  add_action("close","close");
}
open(string s)
{
  NF("Open what?\n");
  if(s!="chest" && s!="the chest" && s!="treasure chest")
    return 0;

  NF("The chest is already open.\n");
  if(!query_prop(CONT_I_CLOSED))
    return 0;

  write("You open the chest.\n");
  say(QCTNAME(TP)+" opens a chest.\n");

  remove_prop(CONT_I_CLOSED);
  return 1;
}
close(string s)
{
  NF("Close what?\n");
  if(s!="chest" && s!="the chest" && s!="treasure chest")
    return 0;

  NF("The chest is already closed.\n");

  if(query_prop(CONT_I_CLOSED))
    return 0;
  
  write("You close the chest.\n");
  say(QCTNAME(TP)+" closes a chest.\n");

  add_prop(CONT_I_CLOSED,1);
  return 1;
}