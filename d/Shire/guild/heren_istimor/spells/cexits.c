/*
 *  Heren Istimor cexits spell
 *  by Palmer, January 2003
 */

#include "spells.h"

inherit SPELL_INHERIT;

void
do_cexits_spell(object caster, object *targets, int *resist, int result)
{
    string *cmds;
    int *exits, exit_nbr, nbr_exits, i, ttl=0;

    if (resist[0] > random(100))
    {
        caster->catch_tell("Your spell failed.\n");
        return;
    }
    tell_room(ENV(caster),QCTNAME(caster) + " studies "+ HIS_HER(caster)+
      " environment carefully.\n", caster);
    caster->catch_tell("You study your environment carefully, looking for hidden paths.\n");


    // Get array of exit cmds
    cmds = (environment(TP))->query_exit_cmds();

    // Get array of exits
    exits = (environment(TP))->query_non_obvious_exits();

    nbr_exits = sizeof(exits);
    for (i = 0; i < nbr_exits; i++)
    {
        if (exits[i] == 1)  // 0 = obvious, 1 = non-obvious
        {
	    ttl += 1;
            write (cmds[i] + " ");
        }
    }

    if (ttl == 0)
        write("You find no hidden paths.\n");

}

int
create_cexits_spell(object caster, object *targets, string args)
{
    default_heren_istimor_spell_config();
    set_spell_mana(5);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP) / 2));
    set_spell_time(6);
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_ingredients(0);
    set_spell_effect(do_cexits_spell);
    set_spell_resist(spell_resist_beneficial);
    return 0;
}
