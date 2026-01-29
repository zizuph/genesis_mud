#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("leaf");
    add_name("_herb_for_Black_Breath_cleanse");
    add_name("_cleanse_spell_herb_");
    add_name("_herb_athelas_");
    add_name(({"kingsfoil", "asea aranion"}));
    set_short("green leaf");
    set_pshort("green leaves");
// Do not use add_pname() as this will disable the automatically
// generated plural forms, and specifically "athelases" which 
// should only be active if the herb has been identified.
// Olorin, March 1997
//  add_pname(({"kingfoils", "leaves", "herbs",}));
    set_adj(({"green", "long"}));
    set_herb_name("athelas");
    set_unid_long("This is a long green leaf of an unknown plant.\n");
    set_id_long(BSN("This is a leaf of the well-known herb athelas, or "
		    + "kingsfoil. Its virtue is still unknown though, as nobody has "
		    + "found a use for it yet."));
    set_find_diff(5);
    set_id_diff(35);
    set_herb_value(576);
    set_effect(HERB_CURING, "all", 0);
    set_ingest_verb("eat");
    set_decay_time(7200);
    set_dryable();
}

