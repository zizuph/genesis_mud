/*
 * /d/Gondor/clubs/storytellers/obj/club_key.c
 */
inherit "/std/key";
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

void
create_key()
{
    add_name(KEY_ID);
    set_adj("steel");
    set_adj("old");
    set_pshort("steel keys");
    set_long("This steel key looks to be quite old.\n");
    set_key("_StoRyTelLer_kEy_");
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_DROP, "You hang on to the "+short()+" for safe keeping.\n");

    setuid();
    seteuid(getuid());
}

nomask public string
query_auto_load()
{
    return MASTER + ":";
}

void
init()
{
    ::init();

    if (!IS_STORYTELLER(environment(this_object())))
	remove_object();
}
