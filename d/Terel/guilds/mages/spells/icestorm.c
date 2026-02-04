inherit "/d/Genesis/newmagic/spell";

#include "spells.h"

#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include "/std/combat/combat.h"


inherit SPELL_BOLT;
inherit SPELL_INHERIT;


static int bolt_pen;
static string bolt_desc;


public void
desc_bolt_cast(object caster, object *targets)
{
    caster->catch_tell("As you finish your gestures "+
      "a violent icestorm forms around "+
      FO_COMPOSITE_ALL_LIVE(targets, caster)+
      ". Engulfing them within its torrent of sharp stinging shards of ice.\n");
    targets->catch_msg(QCTNAME(caster) + " finishes "+
      HIS_HER(caster) + " gestures a violent icestorm suddenly engulfs you "+
      "within its swirling torrent.\n");
    caster->tell_watcher(QCTNAME(caster) + " finishes "+
      HIS_HER(caster) + " gestures a violent icestorm suddenly engulfs "+
      QCOMPLIVE+" within its swirling torrent.\n", targets);
}


public void
desc_bolt_damage(object caster, object target, mixed *result)
{
    string how;

    switch (result[3])
    {
    case 0..60:
	how = "barely touched";
	break;
    case 61..125:
	how = "shaken";
	break;
    case 126..200:
	how = "somewhat cut";
	break;
    case 201..300:
	how = "sliced";
	break;
    case 301..425:
	how = "badly wounded";
	break;
    case 426..600:
	how = "horribly scarred";
	break;
    default:
	how = "nearly cut to ribbons";
	break;
    }
    target->catch_tell("You feel "+how+" from the violent torrent of the sharp stinging shards of ice.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
      how + " from your icestorm.\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how +
      " from the violent torrent of the icestorm.\n", target);
    if (caster->query_wiz_level())
	caster->catch_tell("DAMAGE:  " + result[3] + "\n");
}


int
config_spell(object caster, object *targets, string argument)
{
    set_bolt_desc("ice");
    set_spell_name("icestorm");
    set_spell_desc("Summon an icestorm to harry your enemies");
    set_spell_target(spell_target_present_enemies);
    set_spell_time(5);
    set_spell_mana(150);
    set_spell_element(SS_ELEMENT_WATER, 60);
    set_spell_form(SS_FORM_CONJURATION, 40);
    set_bolt_pen(834);
    set_spell_resist(spell_resist);
    set_spell_offensive(1);


}

public int
try_to_hit(object caster, object target)
{
    // No chance to dodge this spell
    return 1;
}
