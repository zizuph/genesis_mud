/* By McCram march/97 */

#pragma save_binary

inherit "/std/herb";
#include "/d/Roke/common/defs.h"

#include <herb.h>

create_herb()
{
   set_name("leaf");
   set_adj("blue");
   set_short("blue leaf");
   set_id_long("This leaf has a strange blue colour. It is a humbleleaf, which when eaten\n"+
      "makes you invisible for a short while. It is also poisonus.\n");
   set_unid_long("This leaf has a strange blue colour.\n");
   set_herb_name("humbleleaf");
   set_find_diff(7);
   set_id_diff(35);
   set_dryable();
   set_ingest_verb("eat");
   set_herb_value(600);
   set_decay_time(300);
   set_amount(5);
   set_poison_file("/d/Roke/mccram/herbs/obj/humble_poison");
   /*HERBS + "obj/invispois"*/
   set_effect(HERB_POISONING);
   seteuid(getuid());
}
