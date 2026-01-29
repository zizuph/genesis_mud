// file name: /d/Avenir/common/herbs/narcissus.c
// creator(s): Ilyian
// last update: 29 April, 1995
// purpose: May be later used in a quest
// note: 
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("flower");
  add_name("herb");
  add_pname("herbs");
  add_name("_this_is_narcissus_herb_");
  set_adj("ghostly");
  add_adj("black");
  set_short("ghostly black flower");
  set_herb_name("narcissus");
  set_id_long("This dark and beautiful flower is known as Narcissus. It is "
     +"common in damp and dark places, usually growing near a pool "
     +"or stream.\n");
  set_unid_long("This is a beautiful and pale flower, with a long "
     +"red stem and velvety black petals that curl inwards.\n");
  set_ingest_verb("eat");
  set_id_diff(35);
  set_find_diff(3);
  set_decay_time(220);
  set_herb_value(49);
}
