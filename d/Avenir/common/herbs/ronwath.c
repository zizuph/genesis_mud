// file name: /d/Avenir/common/herbs/ronwath.c
// creator(s): Ilyian
// last update: 29 April, 1995
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("vine");
  add_name("herb");
  add_pname("herbs");
  set_short("long tangled vine");
  set_adj("long");
  add_adj("tangled");
  set_herb_name("ronwath");
  set_id_long("This thin and long vine is known as a Ronwath vine. "
    +"They tend to grow along stone walls or other structures, obscuring "
    +"them completely if they are allowed to grow for long enough.\n");
  set_unid_long("This is a long and thin vine that is hopelessly "
    +"tangled up within itself.\n");
  set_ingest_verb("eat");
  set_id_diff(35);
  set_find_diff(3);
  set_decay_time(800);
  set_herb_value(56);
  set_dryable();
}
