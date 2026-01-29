/* 
 * Herald guild list, borrowed from the Rangers
 *
 * Redone and revised for the new spell system by
 * Igneous Feb 1998
 */

#include "spells.h"
#include <filter_funs.h>

inherit SPELL_INHERIT;

void
list_active_heralds(object caster, object *targets, int *resist, int result)
{
    string to_write;
    int i;
    object *list;

    to_write = "You sense the following Heralds occupy the realms:\n";
    to_write += sprintf("%'*'75s", "\n");
    list = filter(users(), &operator(==)(HERALD_GUILD_NAME) @
      &->query_guild_name_lay());
    i = -1;
    while (++i < sizeof(list))
    {
	/* Don't want a jr's name on the guildlist */
	if (extract(list[i]->query_real_name(), -2) == "jr" &&
	  (!TP->query_wiz_level()))
	    continue;
	if (list[i]->query_invis() && !TP->query_wiz_level())
	    continue;

	to_write += (list[i]->query_wiz_level() ? "O" : "o") +
	" "+list[i]->query_cap_name() +" "+ list[i]->query_title();

	if (!present("_herald_robe_", list[i])) 
	{
	    to_write += "  <no robe>";
	}
	if (list[i]->query_ghost()) 
	{
	    to_write += " <deceased>";
	}
	to_write += "\n";
    }
    to_write += sprintf("%'*'75s", "\n");
    caster->catch_tell(to_write);
}

void
palandir_conc_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You concentrate on the palantir in the Elven "+
      "Tower Elostirion.\n");
    FILTER_IS_SEEN(caster, FILTER_PLAYERS(all_inventory(environment(caster)))
      - ({ caster }))->catch_msg(QCTNAME(caster) + " turns to face "+
      "the West for a moment, then turns back.\n", ({caster}));
}

int
create_palandir_spell(object caster, object *targets, string args)
{
    default_herald_spell_config();
    set_spell_mana(3);
    set_spell_time(6);
    set_spell_task(TASK_SIMPLE - (caster->query_stat(SS_LAYMAN) / 4));
    set_spell_ingredients(0);
    set_spell_element(SS_ELEMENT_LIFE, 10);
    set_spell_form(SS_FORM_DIVINATION, 5);
    set_spell_effect(list_active_heralds);
    set_spell_conc_message(palandir_conc_msg);
    return 0;
}
