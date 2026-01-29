#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    add_name("myrtle");
    set_adj(({"translucent","red"}));
    set_short("translucent red berry");
    set_pshort("translucent red berries");
    set_herb_name("myrtleberry");
    set_id_long(BSN("This myrtleberry is a member of the Communis species "
      + "of the laurel family, genus Myrtus. Although the myrtle is said "
      + "to have power in matters of love, without refinement the berry "
      + "is mildly toxic."));
    set_unid_long("This red berry looks like an ordinary berry.\n");
    set_ingest_verb("eat");

    set_effect(HERB_POISONING, "fatigue", 75);
    set_poison_damage( ({ POISON_FATIGUE, 100, POISON_STAT, SS_STR, }) );

    set_id_diff(5);
    set_find_diff(2);

    set_decay_time(1800);
    set_herb_value(36);
}
