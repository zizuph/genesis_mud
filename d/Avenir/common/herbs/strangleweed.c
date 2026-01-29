// file name: /d/Avenir/common/herbs/strangleweed.c
// creator(s): Ilyian
// last update: 29 April, 1995
// purpose: Just a herb for effect..
// note:
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("weed");
  set_pname("weeds");
  add_name(({"herb", "_crucible_component"}));
  add_pname("herbs");
  set_short("handful of thin grey weeds");
  set_pshort("handfuls of thin grey weeds");
  add_name("handful");
  add_pname("handfuls");
  set_adj("thin");
  add_adj("grey");
  set_herb_name("strangleweed");
  set_id_long("These grey leaves are known as Strangleweed, common "
     +"in places that have become overgrown or abandoned.\n");
  set_unid_long("This is a handful of long weeds.\n");
  set_ingest_verb("eat");
  set_id_diff(19);
  set_find_diff(3);
  set_decay_time(80);
  set_herb_value(20);
  set_dryable();
}
