/*  
 *  vision spell
 *
 */

inherit "/d/Genesis/newmagic/spell";

#include "spells.h"
#include <filter_funs.h>
#include <composite.h>

inherit SPELL_INHERIT;



void
resolve_spell(object caster, object *targets, int *resist, int success)
{
    object *items, target = targets[0];
    string to_write;

    if (resist[0] > random(100) || target->query_wiz_level() ||
      ENV(target)->query_prop(ROOM_M_NO_MAGIC))
    {
	caster->catch_tell("Your vision is resisted by "+
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
    tell_room(environment(caster), QCTNAME(caster) + " stares off "+
      "into the distance.\n", ({caster}));
// add here a check of int and wis versus the scrier to determine the following msg or not.
    if ( (target->query_stat(3) ) <= ( caster->query_stat(3) ) || 
         (target->query_stat(4) ) <= ( caster->query_stat(4) ) )
    {
       return;
    }
    else
    {
    target->catch_tell("You shiver slightly as a sudden gust of " +
      "wind blows past.\n");
    } 
}



int
config_spell(object caster, object *targets, string argument)
{
    set_spell_name("vision");
    set_spell_desc("Find people over great distances");
    set_spell_target(spell_target_one_distant_known_living);
    set_spell_time(5);
    set_spell_mana(150);
    set_spell_element(SS_ELEMENT_AIR, 35);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_resist(spell_resist);

}