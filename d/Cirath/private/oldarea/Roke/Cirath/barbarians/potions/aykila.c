inherit "/std/potion";
inherit "/lib/herb_support";

#include "/d/Roke/Cirath/defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <herb.h>

int duration=30;

void
create_potion()
{
  set_name("potion");
  set_adj("milky");
  add_adj("white");
  set_short("white milky potion");
  set_id_long("This white potion is called Aykila. It is made by "+
              "the shamans in the barbarian herd and it makes the quaffer "+
              "able to see in darkness.\n");
  set_unid_long("This is a white milky potion.\n");
  set_unid_smell("The potion has a strange smell.\n");
  set_id_smell("The Aykila potion has a strange smell.\n");
  set_unid_taste("It tastes sour.\n");
  set_id_taste("The Aykila potion tastes sour.\n");
  set_potion_name("aykila");
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

  write("You become able to see in darkness.\n");
  
  ob = clone_object(BARBARIANS+"obj/dark_obj");
  ob->set_duration_time(duration);
  ob->move(this_player());
}

set_duration_time(time)
{
  duration == time;
}
