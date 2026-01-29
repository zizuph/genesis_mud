// file name: alehina.c
// creator(s): Ilyian (April, 1995)
// last update:
// purpose: Mana healing herb guarded by Green Dragon
// note: Is very powerful (will heal all mana), but next to impossible
//       to get.
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("flower");
  set_short("small blood-red flower");
  set_herb_name("alehina");
  set_id_long("This exquisite flower is Alehina, the Glory "
     +"of Mages. It's virtues are known to restore the mental "
     +"powers to their full potential, when it is rubbed between "
     +"the fingertips. Eating it has no effect.\n");
  set_unid_long("It is a beautiful blood red flower, incrediably "
     +"delicate and fragile, with a long, thin stem that trails "
     +"down from the petals.\n");
  set_ingest_verb("rub");
  set_id_diff(65);     //quite difficult to id
  set_find_diff(8);   //redundant, since you never need to search for it.
  set_decay_time(100); //will decay very quickly if not preserved.
  set_effect(HERB_HEALING,"mana",10000);  //will heal anyone fully.
  set_herb_value(9000);  //worth a lot if you ever want to sell it.
}


