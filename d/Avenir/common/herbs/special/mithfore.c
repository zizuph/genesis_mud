// file name: mithfore.c
// creator(s): Ilyian (April, 1995)
// last update:
// purpose: Healing herb guarded by Green Dragon
// note: Is very powerful (will heal fully), but next to impossible
//       to get.
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("vine");
  set_short("tiny silver vine");
  set_herb_name("mithfore");
  set_id_long("This is Mithfore, an ancient herb spoken of in legends but "
     +"until now never seen in the known lands. It is a long "
     +"and very thin vine, which over the years had curled into "
     +"itself. It is said that this herb can cure even the most "
     +"grevious of wounds, bringing life to those near death.\n");
  set_unid_long("This strange herb is a long "
     +"and very thin silvery vine, which over the years had curled into "
     +"itself.\n");
  set_ingest_verb("eat");
  set_id_diff(60);     //quite difficult to id
  set_find_diff(8);   //redundant, since you never need to search for it.
  set_effect(HERB_HEALING,"hp",10000);  //will heal anyone fully.
  set_decay_time(22000); //won't decay for a very long time.
  set_herb_value(8050);  //worth a lot if you ever want to sell it.
}

