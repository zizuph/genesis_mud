inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* Mana restoring herb */


void
create_herb()
{
    set_name("root");
    add_name("_drakeroot_");
    add_adj("tiny");
    add_adj("black");
    set_short("tiny black root");

    set_id_long("This is a very rare and valuable herb found only in "+
    "the dark and deserted areas of mortal worlds. It is said to contain "+
    "great magical powers, and when eaten, it restores mental energy "+
    "that are used up by wizards. It is known as drakeroot.\n");

    set_unid_long("This is a tiny black gnarled root. You have never "+
    "seen such a thing, and you wonder what it does.\n");

    set_herb_name("drakeroot");
    set_amount(2);
    set_decay_time(4000);
    set_id_diff(45);
    set_find_diff(5);
    set_herb_value(750);
    set_ingest_verb("eat");
    set_effect(HERB_HEALING,"mana",30);
}
