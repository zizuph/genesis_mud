#include "spells.h"
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;

void
freeze(object caster, object *targets, int *resist, int result)
{
    if (random(100) < resist[0])
    {
	caster->catch_tell(targets[0]->query_The_name(caster) +" resists your "+
	  "attempt to freeze "+HIM_HER(targets[0])+".\n");
	return;
    }
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
    caster->catch_tell("You finish your web of ice and send it towards "+
      targets[0]->query_the_name(caster) +" entangling "+HIM_HER(targets[0])+
      " within it, freezing him into a solid block of ice.\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) +" finishes "+
      HIS_HER(caster) +" intricate pattern then in one smooth motion points "+
      "at you!  You suddenly feel unbearably cold as the very air "+
      "around you freezes entrapping you within.\n");
    caster->tell_watcher(QCTNAME(caster)+" finishes "+
      HIS_HER(caster) +" intricate pattern then in one smooth motion "+
      "points at "+QTNAME(targets[0])+"!  In blink of an eye "+
      "hundreds of ice crystals form and encase "+LANG_POSS(QTNAME(targets[0]))+
      " body in frosty block of ice.", targets[0]);
}

void
create_freeze(object caster, object *targets, string args)
{
    config_default_spell();
    set_spell_mana(50);
    set_spell_time(5);
    set_spell_form(SS_FORM_TRANSMUTATION, 50);
    set_spell_element(SS_ELEMENT_AIR, 70);
    set_spell_effect(freeze);
    set_spell_object(SPELL_OBJ_DIR + "freeze");
}
