/*
 * Development Spell Object
 */
inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

#include "../guild.h";

void
create_object()
{
    string *files;

    set_name("crystal");
    set_adj(({ "small", "delicate" }));

    set_long("It's a WoHS test crystal.\n");


    setuid();
    seteuid(getuid());

    files = get_dir(SPELLS) - ({ "", ".", "..", "obj", "spell_std.c" });
    files = map(files, &operator(+)(SPELLS, ));
    map(files, add_spell);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    add_spell_object(to);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    remove_spell_object(from);
}
