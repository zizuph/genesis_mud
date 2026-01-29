inherit "/std/herb.c";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <herb.h>
#include "defs.h"

string flavour = "bland";

void
create_herb()
{
    set_adj(({"green","leafy"}));
    set_name("weed");
    add_prop(OBJ_I_WEIGHT, 8);
    add_prop(OBJ_I_VOLUME, 5);

    set_ingest_verb("chew");
    set_short("leafy green weed");
    set_herb_name("tobacco");
    set_unid_long("This is a leafy green weed.\n");
    set_id_long("This leafy green weed is tobacco, a plant with wide " +
        "green leaves. The leaves are often dried and either chewed " +
        "or smoked and are often relaxing.\n");
    set_herb_value(175);
    set_find_diff(1);
    set_id_diff(1);
    set_effect(HERB_HEALING,"fatigue",3);
    add_effect(HERB_SPECIAL,"",0);
    set_dryable();
    set_decay_time(2000);
}

void
special_effect()
{
    object eff;

    setuid(); seteuid(getuid());
    if (query_dried())
	return;

    eff = clone_object("/d/Shire/common/herbs/obj/tobacco_spit");
    eff->move(this_player());
}

int
query_is_tobacco()
{
    return 1;
}

void
set_flavour(string flav)
{
    flavour = flav;
}

string
query_flavour()
{
    return flavour;
}
