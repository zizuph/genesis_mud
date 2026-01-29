/*
 * Spellbook
 */

inherit "/std/object";
inherit "/d/Calia/walkers/specials/spellcasting";

#include <macros.h>
#include <tasks.h>
#include "defs.h"

public int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == query_caster())
        return 0;
    return 1;
}

public int
query_spell_mess(string verb, string arg)
{
    switch (verb)
    {
        case "cure":
	    write("You start to mumble arcane words.\n");
	    say(QCTNAME(this_player()) + " starts to mumble arcane words.\n");
	    return 1;
	    break;
    }
    return 0;
}

#include KAUSAE

create_object()
{
    set_name("fbook");
    set_long("Test spellbook");
    set_short("book");

    add_spell("kausae",kausae,"Kausae Spell");
}
