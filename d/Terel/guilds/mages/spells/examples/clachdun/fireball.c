#include "spells.h"
#include <composite.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_INHERIT;
inherit SPELL_BOLT;

void
fireball_damage_msg(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
    case 0..20:
	how = "barely singed";
	break;
    case 21..50:
	how = "slightly burned";
	break;
    case 51..80:
	how = "somewhat burned";
	break;
    case 81..110:
	how = "burned";
	break;
    case 111..140:
	how = "very burned";
	break;
    case 141..170:
	how = "extermely burned";
	break;
    default:
	how = "horribly burned";
	break;
    }
    target->catch_tell("You feel " + how + " from the impact of the "+
      "small fireballs.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
      how + " from the impact of the fireballs.\n");
    if (caster->query_wiz_level())
	caster->catch_tell("DAMAGE:  "+result[3]+"\n");
    caster->tell_watchers(QCTNAME(target) + " appears " + how + 
      " from the impact of the fireballs.\n",target);

}

void
fireball_casting_msg(object caster, object *targets)
{
    caster->catch_tell("You finish you weave and molten balls "+
      "of flame appears hovering above your palm. Directing the balls you take "+
      "aim at "+ FO_COMPOSITE_ALL_LIVE(targets, caster) +" and hurl "+
      "them at your "+ (sizeof(targets) > 1 ? "foes" : "foe") + ".\n");
    targets->catch_msg(QCTNAME(caster)+" finishes constructing "+
      HIS_HER(caster)+" pattern and several molten balls of flame appears above  "+
      HIS_HER(caster)+" hand. Directing the balls "+HE_SHE(caster)+
      " takes aim at you and hurls them in your direction!\n");
    caster->tell_watcher(QCTNAME(caster) +" finishes constructing "+
      HIS_HER(caster)+" pattern and several balls of flame appears floating above "+
      HIS_HER(caster)+" hand.  Directing the orb "+HE_SHE(caster)+
      " takes aim at "+ QCOMPLIVE +" and hurls them in "+
      (sizeof(targets) > 1 ? "thier" : HIS_HER(targets[0])) +
      " direction!\n", targets);
}

int
create_fireball_bolt(object caster, object *targets, string arg)
{
    create_spell_bolt(caster, targets, arg);
    config_default_spell();
    set_spell_time(4);
    set_spell_mana(80);
    set_spell_element(SS_ELEMENT_FIRE, 60);
    set_spell_form(SS_FORM_CONJURATION, 75);

    set_bolt_desc("fireballs");
    set_bolt_pen(650);
    set_spell_resist(spell_resist);
    set_bolt_casting_msg(fireball_casting_msg);
    set_bolt_damage_msg(fireball_damage_msg);
}
