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
scroll_consume(void)
{
    object bearer = environment(this_object());

    if (bearer)
    {
        if (living(bearer))
        {
            bearer->catch_tell("The " + short() +
                " bursts into flame as the spell is cast!\n");
        }
        else
        {
            tell_room(bearer,
                "The " + short() + " bursts into flame!\n");
        }
    }

    remove_object();
}

public void
create_scroll(void)
{
    setuid();
    seteuid(getuid());

    set_short("scroll of high dedication");
    set_long("This is a scroll of dedication, giving the requirements " +
    "and equipment needed to perform the Ritual of Dedication, " +
    "to become a High Priest of Takhisis.\n");

    set_name(({"scroll","dedication","scroll_of_high_dedication"}));
    set_adj(({"scroll","of","high"}));

    set_file(GUILDDIR + "doc/high_priest_scroll");

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
    write("\nOn the Scroll of High Dedication:\n" +
	"    dedication - The Ritual of Dedication\n\n");
 */
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    remove_spell_object(env);
    remove_spell((GUILDDIROBJ + "high_priest_spell")->query_spell_name());
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    add_spell_object(env);
    add_spell(GUILDDIROBJ + "high_priest_spell");
}
