#include "spells.h"
#include <composite.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;
inherit SPELL_BOLT;

void
lightning_damage_msg(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
    case 0..20:
	how = "barely shocked";
	break;
    case 21..50:
	how = "slightly shocked";
	break;
    case 51..80:
	how = "somewhat shocked";
	break;
    case 81..110:
	how = "shocked";
	break;
    case 111..140:
	how = "very shocked";
	break;
    case 141..170:
	how = "extermely shocked";
	break;
    default:
	how = "horribly shocked";
	break;
    }
    target->catch_tell("You feel " + how + " from the impact of the "+
      "lightning bolt.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
      how + " from the impact of the lightning bolt.\n");
    if (caster->query_wiz_level())
	caster->catch_tell("DAMAGE:  "+result[3]+"\n");
    caster->tell_watchers(QCTNAME(target) + " appears " + how + 
      " from the impact of the lightning bolt.\n",target);

}

void
lightning_casting_msg(object caster, object *targets)
{
    caster->catch_tell("You finish you weave and a crackling orb "+
      "of light appears in your palm.   Grasping the orb you take "+
      "aim at "+ FO_COMPOSITE_ALL_LIVE(targets, caster) +" and hurl "+
      "it at your "+ (sizeof(targets) > 1 ? "foes" : "foe") + ".\n");
    targets->catch_msg(QCTNAME(caster)+" finishes constructing "+
      HIS_HER(caster)+" pattern and a cracking orb appears in within "+
      HIS_HER(caster)+" hand.  Grasping the orb "+HE_SHE(caster)+
      " takes aim at you and hurls it in your direction!\n");
    caster->tell_watcher(QCTNAME(caster) +" finishes constructing "+
      HIS_HER(caster)+" pattern and a cracking orb appears in within "+
      HIS_HER(caster)+" hand.  Grasping the orb "+HE_SHE(caster)+
      " takes aim at "+ QCOMPLIVE +" and hurls it in "+
      (sizeof(targets) > 1 ? "thier" : HIS_HER(targets[0])) +
      " direction!\n", targets);
}

int
create_lightning_bolt(object caster, object *targets, string arg)
{
    create_spell_bolt(caster, targets, arg);
    config_default_spell();
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_element(SS_ELEMENT_AIR, 60);
    set_spell_form(SS_FORM_CONJURATION, 75);

    set_bolt_desc("lightning");
    set_bolt_pen(650);
    set_spell_resist(spell_resist_electricity);
    set_bolt_casting_msg(lightning_casting_msg);
    set_bolt_damage_msg(lightning_damage_msg);
}
