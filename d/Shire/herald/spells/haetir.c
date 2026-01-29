/*  
 *  Herald Haetir Spell
 *
 *  Updated and revised for the new Spellcasting system
 *  by Igneous Feb 98
 */

#include "spells.h"
#include <filter_funs.h>
#include <composite.h>

inherit SPELL_INHERIT;

void
do_haetir_spell(object caster, object *targets, int *resist, int success)
{
    object *items, target = targets[0];
    string to_write;

    if (resist[0] > random(100) || target->query_wiz_level() ||
      ENV(target)->query_prop(ROOM_M_NO_MAGIC)|| 
      ENV(target)->query_prop(ROOM_M_NO_SCRY))
    {
	caster->catch_tell("Your prayer is resisted by "+
	  CAP(target->query_real_name()) + "!\n");
	return;     
    }
    to_write = "You shift your mind into "+CAP(target->query_real_name())+
    " and look through "+HIS_HER(target)+" eyes.\nYou open your "+
    "new eyes and see:\n";

    if (!objectp(environment(target)))
	to_write += "A dark void.\n";
    else if (environment(target)->query_prop(OBJ_I_LIGHT) < 1)
	to_write += "A dark room.\n";
    else 
    {
	to_write += ENV(target)->long();
	items = FILTER_CAN_SEE(all_inventory(environment(target)), caster);
	if (items) 
	{
	    if (sizeof(FILTER_DEAD(items)))
		to_write += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
	    if (sizeof(FILTER_LIVE(items)))
		to_write += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
	}
    }
    caster->catch_tell(to_write);
    tell_room(environment(caster), QCTNAME(caster) + " seems to look "+
      "intently at something far away.\n", ({caster}));
    target->catch_tell("You feel a weird magical presence inside...\n"+
      "You sense the aura of "+ caster->query_the_name(target)+".\n"+
      "Then the sensation goes away.\n");

    setuid();
    seteuid(getuid());
    write_file("/d/Shire/herald/log/haetir",
        sprintf("%s %-11s on %-11s\n", ctime(time()),
        capitalize(caster->query_real_name()),
        capitalize(target->query_real_name())));
}

int
create_haetir_spell(object caster, object *targets, string args)
{
    default_herald_spell_config();
    set_spell_mana(40);
    set_spell_time(10);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_element(SS_ELEMENT_LIFE, 35);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_ingredients(({"parsley"}));
    set_spell_effect(do_haetir_spell);
}
