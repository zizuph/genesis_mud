// file name:    /d/Avenir/common/herbs/blood_creep.c
// creator(s):   Casca 12/13/99
// last update:  Lilith 2/19/04 updated value and desc
// 	Lucius, Jun 2017: "Blood creep" -> "Bloodcreep" in long
// 	                  to reduce confusion.
// purpose:      origional herb, meant to be found in the Dark.
// note:         my first herb
// bug(s):
// to-do:

inherit "/std/herb";
#include "/sys/herb.h"

create_herb()
{
  set_name("lichen");
  add_name("herb");
  add_pname(({"herbs","bloodcreeps", "patches"}));
  set_short("patch of crimson lichen");
  set_pshort("patches of crimson lichen");
  set_adj(({"crimson", "round"}));
  set_herb_name("bloodcreep");
  set_id_long("This is a roundish patch of the lichen "+
        "known as Bloodcreep. Its name comes from its deep "+
        "crimson color which is reminiscent of fresh blood. "+
        "Its name, while accurate to its description, is also "+
        "indicative of its effect, which is to slow the flow "+
        "of blood when applied to wounds.\n");
  set_unid_long("This patch of crimson coloured lichen looks rather "+
        "a lot like blood.\n");
  set_ingest_verb("apply");
  set_id_diff(25);
  set_find_diff(3);

  set_effect(HERB_HEALING,"hp",59);
  set_decay_time(3500);
  set_herb_value(1500);
  set_dryable();
}
