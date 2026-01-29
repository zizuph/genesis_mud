#include "../spells.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Khalakhor/sys/defs.h"

inherit SPELL_OBJECT;
inherit "/std/object";

#define BARRIER_PROP  "_live_i_kahalkhor_failed_water_barrier"


//  Prototypes
varargs void dispell_spell_effect(object dispeller);

// Global vars
static string blocked;

void
create_object()
{
    set_name("barrier");
    add_name("_magic_water_barrier_");
    set_short("massive barrier of water");
    set_long("This thing has not been configured correctly.\n");

    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
}

void
set_blocked_dir(string where)
{
    blocked = where;
}

public int
start()
{
    set_spell_effect_desc("water barrier");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }
    set_blocked_dir(ONE_OF(spell_target->query_exit_cmds()));
    set_long("This "+short()+" has been magically summoned and "+
      "is currently blocking the "+blocked+" exit from this room.\n");
    move(spell_target, 1);
    spell_caster->catch_tell("You finish you weave and a massive column "+
      "of water springs forth from the ground and rises to block "+
      "the exit which leads "+blocked+" from this room.\n");
    tell_room(spell_target, QCTNAME(spell_caster) + " finishes "+
      HIS_HER(spell_caster)+" pattern and a massive column of water "+
      "springs forth from the ground and rises to block the exit "+
      "which leads "+blocked+" from this room.\n", spell_caster);
    set_alarm(180.0, 0.0, dispell_spell_effect);
    return 1;
}

varargs int
dispell_spell_effect(object dispeller)
{
    tell_room(spell_target, "The "+short()+" collaspses in upon "+
      "itself and evaporates, leaving no trace of itself behind.\n");
    remove_spell_effect_object();
    return 1;

}

int
block(string str)
{
    int task;

    if (stringp(str) && str == blocked)
    {
	write("You are unable to "+query_verb()+" in that direction.\n");
	return 1;
    }
    else if (query_verb() == "sneak")
    {
	return 0;
    }
    if (!present(spell_caster, environment()))
    {
	dispell_spell_effect();
	return 0;
    }
    if (TP->query_prop(BARRIER_PROP) + 10 >= time())
    {
	write("You are unable to make another attempt until "+
	  "you can recover from your last failed attempt.\n");
	return 1;
    }
    task = TASK_DIFFICULT + spell_power;
    task -= TP->query_prop(MAGIC_I_BREATH_WATER);
    task -= TP->query_prop(MAGIC_I_RES_WATER) * 5;
    if (TP->query_wiz_level())
    {
	TP->catch_tell("BARRIER TASK IS: "+ task + "\n");
    }
    if (TP->resolve_task(task, ({SKILL_AVG, TS_DIS, TS_STR, SKILL_END,
	  SKILL_AVG, SS_ELEMENT_WATER, SS_FORM_ABJURATION, SKILL_END})) >= 0)
    {
	write("Taking a deep breath you manage to force you way "+
	  "through the "+short()+".\n");
	say(QCTNAME(TP) + " manages to force "+HIS_HER(TP)+" way "+
	  "through the "+short()+".\n");
	TP->remove_prop(BARRIER_PROP);
	return 0;
    }
    TP->add_prop(BARRIER_PROP, time());
    write("Taking a deep beath and with all your might you are unable "+
      "to force your way through the massive barrier of water.\n");
    say(QCTNAME(TP)+" struggles to pass through the "+short()+
      " but fails.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(block, blocked);
    add_action(block, "sneak");
}
