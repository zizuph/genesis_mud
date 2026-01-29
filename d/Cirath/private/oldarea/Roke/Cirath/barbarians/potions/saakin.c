inherit "/std/potion";
inherit "/lib/herb_support";

#include "/d/Roke/Cirath/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

int invis=30;

void
create_potion()
{
  set_name("potion");
  set_adj("red");
  add_adj("metallic");
  set_short("metallic red potion");
  set_id_long("This red potion is called Saakin. It is made by "+
              "the shamans in the barbarian herd and it turns the quaffer "+
              "invisible.\n");
  set_unid_long("This is a metallic red potion.\n");
  set_unid_smell("The potion doesn't smell anything in particular.\n");
  set_id_smell("The Saakin potion doesn't smell anything in particular.\n");
  set_unid_taste("It tastes sweet.\n");
  set_id_taste("The Saakin potion tastes sweet.\n");
  set_potion_name("saakin");
  set_soft_amount(50);
  set_alco_amount(0);
  set_id_diff(10);
  set_potion_value(0);
  set_quaff_verb("quaff");
  set_effect(HERB_HEALING,"hp",500);
  set_effect(HERB_SPECIAL,"",0);

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

void
special_effect()
{
  object ob;

  write("You become invisible!!.\n");
  say(QCTNAME(this_player())+" suddenly disappears in a puff!!.\n");
  
  ob = clone_object(BARBARIANS+"obj/invis_obj");
  ob->set_invis_time(invis);
  ob->move(this_player());
}

set_invis_time(time)
{
  invis == time;
}
