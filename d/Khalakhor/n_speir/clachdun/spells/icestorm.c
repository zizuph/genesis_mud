#include "spells.h"
#include <composite.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;
inherit SPELL_HARM;

public void
desc_casting(object caster, object *targets)
{
    string str;

    caster->catch_tell("You finish weaving your pattern, which summons a "+
      "massive storm of magical ice towards "+
      FO_COMPOSITE_ALL_LIVE(targets,caster) + ".\n");
    targets->catch_msg(QCTNAME(caster) + " finishes his magical pattern in "+
      "the air and a chilling blue flame surrounds "+HIM_HER(caster)+".  "+
      "Then with a swift movement of "+HIS_HER(caster)+" hand "+
      "the flame explodes towards you, spliting up into thousands "+
      "of razor sharp pieces of ice.\n");
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
    case 0..20:
	how = "barely scratched";
	break;
    case 21..50:
	how = "scratched";
	break;
    case 51..80:
	how = "somewhat frostbitten";
	break;
    case 81..110:
	how = "frostbitten";
	break;
    case 111..140:
	how = "badly slashed and frostbitten";
	break;
    case 141..170:
	how = "horrible slashed and frostbitten";
	break;
    default:
	how = "chilled to the bone";
	break;
    }
    target->catch_tell("You feel "+how+" from the shards of ice.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
      how + " from your shards of ice.\n");
    caster->tell_watchers(QCTNAME(target) + " appears " + how +
      " from the shards of ice.\n", target);
}

int
create_icestorm(object caster, object *targets, string argument)
{
    create_spell_harm(caster, targets, argument);
    config_default_spell();
    set_spell_time(5);
    set_spell_mana(120);
    set_spell_element(SS_ELEMENT_WATER, 75);
    set_spell_form(SS_FORM_CONJURATION, 90);

    set_harm_pen(750);
    set_spell_resist(spell_resist_cold);
}
