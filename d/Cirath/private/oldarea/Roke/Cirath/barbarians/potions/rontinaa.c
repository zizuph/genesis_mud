inherit "/std/potion";
inherit "/lib/herb_support";

#include "/d/Roke/Cirath/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

void
create_potion()
{
  set_name("potion");
  set_adj("yellow");
  add_adj("clear");
  set_short("clear yellow potion");
  set_id_long("This yellow potion is called Rontinaa. It is made by "+
              "the shamans in the barbarian herd and is used to heal "+
              "the wounds.\n");
  set_unid_long("This is a clear yellow potion.\n");
  set_unid_smell("The potion smells a little alcohol.\n");
  set_id_smell("The Rontinaa potion smells like some nice whiskey.\n");
  set_unid_taste("The potion tastes bitter with an alcoholic touch to it.\n");
  set_id_taste("The Rontinaa potion has a bitter taste with some alcohol in it.\n");
  set_potion_name("rontinaa");
  set_soft_amount(50);
  set_alco_amount(0);
  set_id_diff(10);
  set_potion_value(0);
  set_quaff_verb("quaff");
  set_effect(HERB_HEALING,"hp",500);

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_NO_GIVE,1);
  add_prop(OBJ_I_NO_DROP,1);

  set_long("@@long_func");
}
void
destruct_object()
{
  object ob;
 
 if (quaffed_it && quaff_verb != "quaff")
  {
    quaffed_non_quaff_potion();
  }
  else
  {
    do_herb_effects();
  }
  seteuid(getuid());

  ob = clone_object(OBJ+"flask");

  if (ob->move(environment(this_object())))
    ob->move(environment(this_object()), 1);

  set_alarm(0.0, 0.0, "remove_object");
}
