/*
 * Spellbook
 */

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/spellcasting";

#include <macros.h>

create_object()
{
    set_name("book");
    set_long("Test spellbook");
    set_short("book");

    add_spell("blast", "blast", "Blast");
}

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

#include "blast.c"









