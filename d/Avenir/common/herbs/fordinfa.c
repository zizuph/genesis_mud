// file name: fordinfa.c
// creator(s): Ilyian (April, 1995)
// last update:
// purpose: Mana healing mushrooms found in /park/glade.c
// note: 
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("mushrooms");
  add_name("herb");
  add_name("handful");
  set_pname("handfuls");
  add_pname("herbs");
  set_adj("tiny");
  add_adj("grey");
  set_short("handful of tiny grey mushrooms");
  set_herb_name("fordinfa");
  set_id_long("This is a handful of tiny delicate mushrooms known "
      +"as fordinfa mushrooms. They each have long, thin stalks and "
      +"comparatively wide heads. They are said to give mental strength "
      +"to those who eat it.\n");
  set_unid_long("This is a handful of tiny and delicate mushrooms "
      +"with long, thin stalks.\n");
  set_ingest_verb("eat");
  set_id_diff(30);     //not difficult to id
  set_find_diff(3); 
  set_decay_time(200);  //will decay quickly if not preserved.
  set_effect(HERB_HEALING,"mana",35); 
  set_herb_value(400);  
}


