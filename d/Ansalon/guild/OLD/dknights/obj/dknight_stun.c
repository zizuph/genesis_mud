/* 
 * ppain object - paralysing pain
 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#define PARALYZE_SUBLOC "dk_PARALYZE_SUBLOC"

int changeAmount, gAlarm, gRemovedAlarm;
int alarm;

void
create_object()
{
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "Dk's magical object that paralyses.\n");
    set_no_show();
}


varargs public int
dispel_spell_effect(object dispeller)
{
    if (dispeller)
    {
    	  spell_target->catch_tell("Blood begins once again to flow to your limbs, and "+
        "you can move again.\n");

	     tell_room(environment(spell_target),
	     QCTNAME(spell_target) + " begins to be able to move and the paralyze disappears " +
	     "from "+HIS(spell_target) + " limbs.\n", spell_target);
    }

    if (spell_target)
    {
	      spell_target->remove_stun();
	      spell_target->remove_subloc(PARALYZE_SUBLOC);
              remove_object();
	      //spell_target->remove_prop(LIVE_S_EXTRA_SHORT);
    }

    return 1;
}

public void
set_ppain_time(int t)
{
    remove_alarm(alarm);
    alarm = set_alarm(itof(45 + t), 0.0, &dispel_spell_effect(this_object()));
}

public int
do_all_commands(string str)
{
    string *allowed;

    if (E(TO) != TP)
	return 0;

    if (TP->query_wiz_level())
	return 0;

    allowed = ({ "help","commune","reply",
	"bug","typo","idea","praise","sysbug",
	"stats", "health", "h", "vitals", "v",
	"look", "l","exa",
	"scream","moan","cry"});

    if (member_array(query_verb(), allowed) >= 0)
        return 0;
    write("You are completely paralyzed and unable to do that.\n");
    return 1;
}

init()
{
    ::init();
    if (!gRemovedAlarm)
        add_action(do_all_commands, "", 1);
}


public int
start()
{
    object horse;
	
    set_spell_effect_desc("paralysis");

    if (!::start() || move(spell_target,1))
    {
        remove_spell_effect_object();
        return 0;
    }

    if(spell_target->query_wiz_level())
    {
        spell_target->catch_tell("As a wizard, you are immune to being " +
        "stunned.\n");
        remove_spell_effect_object();
        return 0;
    }

    if (horse = spell_target->query_prop(LIVE_O_STEED))
    {
        spell_target->catch_tell("You lose your seat on your horse and fall "+
        "to the ground.\n");

        horse->do_dismount(spell_target,1,1);

        tell_room(E(spell_target),QCTNAME(spell_target) + " falls off the " +
        horse->short() + ".\n", spell_target);
        
    }
    else
    {
        spell_target->catch_msg("You try to move, but instead you fall to "+
        "the ground.\n");
    }

    //spell_target->add_prop(LIVE_S_EXTRA_SHORT, " is curled up in pain");
    spell_target->add_stun();
        
    spell_target->add_subloc(PARALYZE_SUBLOC, TO);

    alarm = set_alarm(60.0, 0.0, &dispel_spell_effect(this_object()));

    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are lying on the ground completely motionless.\n";

    return C(HE(me)) + " is lying on the ground completely motionless.\n";
}
