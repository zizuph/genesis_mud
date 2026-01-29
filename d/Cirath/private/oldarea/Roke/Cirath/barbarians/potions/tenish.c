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
  set_adj("green");
  add_adj("misty");
  set_short("misty green potion");
  set_id_long("This green potion is called Tenish. It is made by "+
              "the shamans in the barbarian herd and is used to calm "+
              "down the on who quaffs it.\n");
  set_unid_long("This is a misty green potion.\n");
  set_unid_smell("The potion smells like...you don't have the word for it.\n");
  set_id_smell("The Tenish potion smells like something the dog has made on "+
               "floor.\n");
  set_unid_taste("Aarghh...It tastes like....\n");
  set_id_taste("Urrrk...the Tenish potion tastes like...\n");
  set_potion_name("tenish");
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
  this_player()->add_panic(-100);
  write("You feel calmer.\n");
}
