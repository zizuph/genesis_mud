#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name(({"moss", "blunfing"}));
    set_adj(({"pile", "of", "shaggy","blung","purple","green","purple-green"}));
    set_herb_name("blung");
    set_short("purple-green shaggy moss");
    set_pshort("piles of purple-green shaggy moss");
    set_ingest_verb("eat");
    set_unid_long(BSN("This is a shaggy matted purple-green moss lying "
    + "primarily in isolated clumps on the north side of the trees."));
    set_id_long(BSN("This is blung moss, known as blunfing to the learned. "
    + "This bitter, astringent moss is often eaten by the lowland "
    + "Dunlendings when they must travel swiftly over long distances. "
    + "Use of blung is said by some to be habit-forming."));
    set_herb_value(84);
    set_id_diff(15);
    set_find_diff(3);
    set_effect(HERB_HEALING, "fatigue", 10);
    set_decay_time(7200);
    set_dryable();
}

