#include "spells.h"
#include <macros.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;

void
curse(object caster, object *targets, int *resist, int result)
{
    int i = -1;
    object *resisted = ({});

    while (++i < sizeof(targets))
    {
	if (targets[i]->query_clachdun_cursed() || random(100) < resist[i])
	{
	    resisted += ({targets[i]});
	}
	else
	{
	    targets[i]->catch_tell(caster->query_The_name(targets[i])+
	      " finishes "+HIS_HER(caster)+" pattern in the air and "+
	      "suddenly you feel a wave of despair course through your "+
	      "heart, making you feel less confident in your abilities.\n");
	}
    }
    targets -= resisted;

    if (sizeof(targets))
	caster->catch_tell("You finish your weave of death and cover "+
	  FO_COMPOSITE_ALL_LIVE(targets, caster)+" with a blanket "+
	  "of despair and enfeeblement.\n");
    if (sizeof(resisted))
	caster->catch_tell(capitalize(FO_COMPOSITE_ALL_LIVE(resisted, caster))+
	  " manage to resist your spell.\n");
    else if (!sizeof(targets))
	return;
    caster->tell_watchers(QCTNAME(caster)+" finishes "+
      HIS_HER(caster)+" pattern in the air and then suddenly "+
      COMPOSITE_ALL_LIVE(targets)+" slump "+(sizeof(targets) == 1 ?
	HIS_HER(targets[0]) : "their")+ " shoulders and seem "+
      " less confident with "+(sizeof(targets) == 1 ?
	HIS_HER(targets[0]) + "self" : "themselves")+ " .\n", targets);
    setuid(); seteuid(getuid());
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}

int
create_curse(object caster, object *targets, string args)
{
    config_default_spell();
    set_spell_offensive(1);
    set_spell_mana(90);
    set_spell_time(3);
    set_spell_form(SS_FORM_ENCHANTMENT, 60);
    set_spell_element(SS_ELEMENT_DEATH, 70);
    set_spell_effect(curse);
    set_spell_object(SPELL_OBJ_DIR + "curse");
}
