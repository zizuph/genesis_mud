inherit "/d/Faerun/std/obj/wand";

#include "/d/Faerun/std/obj/wand.h"
#include <ss_types.h>

create_wand()
{
  set_name("wand");
  set_adj("confusion");
  
  add_name("wand");
  add_adj(({"ivory", "carved"}));

  set_short("carved ivory wand");
  set_long("Blah, blah, blah....\n");

  set_id_short("wand of confusion");
  set_id_long("Identified blah, blah, blah.\n");

  set_wand_type(WAND_SPECIAL);
  set_wand_effect("confusion");

  set_charges(6);
  set_charge_value(100);

  set_ident_limit(100);
}

void special_effect(object obj) {
  object sh;

  seteuid(getuid());
  sh = clone_object("/d/Faerun/std/obj/WoC_sh.c");
  sh -> shadow_me(obj);
 
}



