// file name: /d/Terel/common/herbs/argil.c
// creator:  Tomas -- Jan 2000
// Effect: Anti-Fatigue
// Mountain herb
/*
    Modified: 6 May 2003, by Bleys
        - Fixed a typo in the pname
        - Added the herb name to the id_long
*/


inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("root");
  add_name("herb");
  add_pname(({"herbs", "roots", "argils"}));
  set_short("dark spotted root");
  set_adj(({"dark", "spotted"}));
  set_herb_name("argil");
  set_id_long("This small dark spotted root, known as Argil, is " +
     "known to grow at higher elevations and thrives " +
     "under extreme cold conditions. It is known for its " + 
     "fatigue restoration properties.\n");
  set_unid_long("The dark spotted root feels firm yet " +
     "pliable to the touch.\n");
  set_ingest_verb("chew");
  set_id_diff(40);
  set_find_diff(6);
  set_effect(HERB_HEALING,"fatigue", 40);
  set_decay_time(8500);
  set_herb_value(800);
  set_dryable();
}


