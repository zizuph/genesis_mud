// file name: /d/Avenir/common/herbs/carlith.c
// creator(s): Ilyian
// last update: 7 April, 1995
// purpose: origional herb, meant to be found on park island.
// note: my first herb - identical to attanar in effect.
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("vine");
  add_name("herb");
  add_pname(({"herbs", "vines", "carliths"}));
  set_short("thin trailing vine");
  set_adj(({"thin", "trailing"}));
  set_herb_name("carlith");
  set_id_long("This longish vine is named Carlith, and it is "
     +"rumoured that ingesting it causes small wounds to close "
     +"rapidly.\n");
  set_unid_long("This is the thin ending of a vine trail. It is "
     +"green and rubbery, with tiny bumps along the sides.\n");
  set_ingest_verb("eat");
  set_id_diff(25);
  set_find_diff(3);
  set_effect(HERB_HEALING,"hp",60);
  set_decay_time(2200);
  set_herb_value(1050);
  set_dryable();
}


