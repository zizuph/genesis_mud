inherit "/std/potion";
inherit "/lib/herb_support";

#include "/d/Roke/Cirath/defs.h"
#include "/d/Roke/common/defs.h"
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
  set_adj("golden");
  add_adj("shiny");
  set_short("shiny golden potion");
  set_id_long("This golden potion is called Jiiru. It is made by "+
              "the shamans in the barbarian herd and it makes the quaffer "+
              "move faster.\n");
  set_unid_long("This is a shiny golden potion.\n");
  set_unid_smell("The potion smells lovely.\n");
  set_id_smell("The Jiiru potion smells lovely.\n");
  set_unid_taste("Its tast has a real sting in it.\n");
  set_id_taste("The Jiiru potion has a real sting in its taste.\n");
  set_potion_name("jiiru");
  set_soft_amount(50);
  set_alco_amount(0);
  set_id_diff(10);
  set_potion_value(0);
  set_quaff_verb("quaff");
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

  write("You start to move faster.\n");
  say(QCTNAME(TP)+" seems to move faster!\n");
  
  ob = clone_object(BARBARIANS+"obj/speed_obj");
  ob->set_duration_time(duration);
  ob->move(this_player());
}

set_duration_time(time)
{
  duration == time;
}
