/*
 * Dark, wrinkled herb
 * Enables mortals to see invisible people
 * Palmer - April 1, 2004
 */

#include "defs.h"
#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/herb.c";

#define EFFECT "/d/Shire/common/herbs/glimmeref"

create_herb()
{
    set_name("root");
    add_name(({"small wrinkled root","wrinkled root", "dark root"}));
    set_adj(({"small","wrinkled"}));
    set_short("small wrinkled root");
    set_pshort("small wrinkled roots");
    set_herb_name("glimmer root");
    set_id_long("This is a small, wrinkled root known by most as the " +
        "glimmer root. It looks old, and dried out, after being buried " +
        "for centuries. It is scaly looking and seems to glimmer faintly " +
        "under all the dirt clinging to it.\n");
    set_unid_long("This is a small wrinkled root.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(1);
    set_effect(HERB_SPECIAL);
    set_decay_time(500);
    set_herb_value(2592);
    set_dryable();
}

string
query_recover() { return MASTER+":"+query_herb_recover(); }
 
void
init_recover(string arg) { init_herb_recover(arg); }
 
void
special_effect()
{
    object eff;
    eff = clone_object(EFFECT);
    eff->move(this_player());
}
