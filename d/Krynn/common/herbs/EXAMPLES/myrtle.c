#pragma save_binary

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    set_adj(({"translucent","red"}));
    set_short("translucent red berry");
    set_pshort("translucent red berries");
    set_pname(({"berries", "herbs", }));
    set_herb_name("myrtleberry");
    set_id_long(BSN("This myrtleberry is a member of the Communis species "
      + "of the laurel family, genus Myrtus. Although the myrtle is said "
      + "to have power in matters of love, without refinement the berry "
      + "is mildly toxic."));
    set_unid_long("This red berry looks like an ordinary berry.\n");
    set_ingest_verb("eat");
    set_id_diff(5);
    set_find_diff(2);
    set_effect(HERB_POISONING,"fatigue",25);
    set_decay_time(2000);
    set_herb_value(36);
}

string  query_recover() { return MASTER+":"+query_herb_recover(); }
void    init_recover(string arg) { init_herb_recover(arg); }
