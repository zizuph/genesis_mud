inherit "/std/container";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"

create_container()
{
  object ob;

  set_name("box");
  set_short("onyx charity box");
  set_adj(({"onyx","charity"}));
  
  add_prop(CONT_I_MAX_WEIGHT,200000); /* lots of stuff */
  add_prop(CONT_I_MAX_VOLUME,200000);
  add_prop(CONT_I_TRANSP,1);
  add_prop(OBJ_I_NO_GET,1);
  
  set_long("This box looks very valuable and is placed here to make "+
           "wealthy people sponsor the poor. There is a sign on it.\n");

  add_cmd_item("sign","exa","It looks readable.\n");
  add_cmd_item("sign","read","Feel free to take anything placed in this box.\n"+
              "You may donate anything you like in it, to help your fellow\n"+
              "adventurers.\n");
  seteuid(getuid(TO));

  clone_object(OBJ+"t_boots")->move(TO);
  clone_object(OBJ+"t_cloak")->move(TO);
}
