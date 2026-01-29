#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("berry");
    set_short("little black berry");
    set_pshort("little black berries");
    set_adj(({"little", "black", }));
    set_herb_name("black raspberry");
    set_id_long(BSN("This black raspberry is a member of the genus Rubus. "+
	"The berry is small and tart, with red-purple tinge and tangy "+
	"flavour. "+
	"The black raspberry has a mild healing and restorative effect."));
    set_unid_long("This black berry looks like an ordinary berry.  "+
	"You do not know what it is for.\n");
    set_ingest_verb("eat");
    set_id_diff(15);
    set_find_diff(5);
    set_effect(HERB_HEALING, "hp", 2);
    set_decay_time(3600);
    set_herb_value(144);
}

