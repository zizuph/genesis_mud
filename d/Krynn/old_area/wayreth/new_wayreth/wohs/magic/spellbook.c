/*
 * /d/Krynn/new_wayreth/wohs/magic/spellbook.c
 *
 *
 */
#include "../guild.h"

inherit "/std/book";
inherit "/d/Genesis/magic/spells/identify";
inherit SPELLCASTING spellcasting;

#include <cmdparse.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>

public void
create_book()
{
    set_name("book");
    add_name("spellbook");
    set_long("This is a spellbook.\n");
    set_short("spellbook");

    add_spell_identify();
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}


