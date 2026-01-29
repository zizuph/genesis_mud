/*
 * Ashlar, 09 Jul 98
 *
 * A scroll detailing the ritual to become
 * a priest, and also the spell used to start
 * the ritual
 */
#pragma strict_types

inherit "/std/scroll";
inherit "/d/Genesis/newmagic/spellcasting";

#include <stdproperties.h>
#include "../guild.h"

public void
create_scroll(void)
{
    setuid();
    seteuid(getuid());

    set_short("scroll of dedication");
    set_long("This is a scroll of dedication, giving the requirements " +
    "and equipment needed to perform the Ritual of Dedication, " +
    "to become a Priest of Takhisis.\n");

    set_name(({"scroll","dedication","scroll_of_dedication"}));
    set_adj(({"scroll","of"}));

    set_file(GUILDDIR + "doc/priest_scroll");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

/*
    add_spell("dedication", "The Ritual of Dedication", create_dedication,
        ded_target);
*/
}

public void
list_spells(void)
{
    /*
     * Asked not to display.
     *
    write("\nOn the Scroll of Dedication:\n" +
	"    dedication - The Ritual of Dedication\n\n");
     */
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    remove_spell_object(env);
    remove_spell((GUILDDIROBJ + "priest_spell")->query_spell_name());
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    add_spell_object(env);
    add_spell(GUILDDIROBJ + "priest_spell");
}
