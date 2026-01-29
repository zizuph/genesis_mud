/*
 * Spellbook
 */

inherit "/std/object";
inherit "/d/Calia/worshippers/spells/spellcasting";

#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include SPELLS_HEADER

public int
query_spell_mess(string verb, string arg)
{
    switch (verb)
    {
        case "chage":
            write("You begin to murmur the Chage incantation.\n");
            say(QCTNAME(this_player())+" begins to murmur a strange "+
                "incantation.\n");
            return 1;
            break;
        case "chkiller":
            write("You begin to murmur the Chkiller incantation.\n");
            say(QCTNAME(this_player())+" begins to murmur a strange "+
                "incantation.\n");
            return 1;
            break;
    }
    return 0;
}

#include STOUS

create_object()
{
    set_name("tbook");
    set_long("Test spellbook");
    set_short("book");

    add_spell("stous",stous,"Stous Spell - Summon Spirit");
}
