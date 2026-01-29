/*

  Remove enchantment from target's armour.
  
 */

#include "spells.h"
#include <filter_funs.h>
#include <composite.h>

inherit SPELL_INHERIT;


int
query_enchanted(object o)
{
    if (sizeof(o->query_prop("_magic_am_magic")))
        return 1;
}


void
do_dispell_spell(object caster, object *targets, int *resist, int result)
{
    object *items, target = targets[0], lucky_armour;
    string to_write, *stuff;

    tell_room(environment(caster), QCTNAME(caster) + " looks "+
      "intently at " + CAP(target->query_real_name()) + ".\n", ({caster}));

    to_write = "You observe "+CAP(target->query_real_name())+
    ", searching for auras of enchantment.\n";

    
    if (resist[0] > random(100) )
    {
        caster->catch_tell("Your spell is resisted by "+
        CAP(target->query_real_name()) + "!\n");
        return;
    }

    if (!objectp(environment(target)))
        to_write += "A dark void.\n";
    else if (environment(target)->query_prop(OBJ_I_LIGHT) < 1)
        to_write += "A dark room.\n";
    else
    {
        // to_write += ENV(target)->long();
        items = all_inventory(target);
        if (items)
        {
	    stuff = filter(items, query_enchanted);
            if (sizeof(stuff))
            {
	        lucky_armour = ONE_OF_LIST(stuff);
                to_write += "You dispell the magic on ";
		to_write += HIS_HER(target[0]) + " " + lucky_armour->short()  + ".\n";
            }
            else
                to_write += "You detect no auras of enchantment.\n";
        }
    }
    caster->catch_tell(to_write);

    
}

int
create_dispell_spell(object caster, string args, object *targets)
{
    default_heren_istimor_spell_config();
    set_spell_time(1);
    set_spell_mana(5);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_OCCUP) / 2));
    set_spell_ingredients(0);
    set_spell_peaceful(0);
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_effect(do_dispell_spell);
}
