/* 
 * ppain object - paralysing pain
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";

#define PAIN_SUBLOC "pot_pain_subloc"

int changeAmount, gAlarm, gRemovedAlarm;
int alarm;

void
create_object()
{
    add_name(PAIN_ID);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "PoT magical object inflicting paralysing pain.\n");
    set_no_show();
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (dispeller)
    {
    	spell_target->catch_tell("The pain leaves you as suddenly as it appeared. " +
	"You stand up, feeling a bit unsteady for a short while.\n");

	tell_room(environment(spell_target),
	QCTNAME(spell_target) + " stops screaming in pain and slowly regains " +
	HIS(spell_target) + " feet.\n", spell_target);
    }

    if (spell_target)
    {
	spell_target->remove_stun();
	spell_target->remove_subloc(PAIN_SUBLOC);
	//spell_target->remove_prop(LIVE_S_EXTRA_SHORT);
    }

    gRemovedAlarm = set_alarm(itof((5 -
        query_spell_effect_caster()->query_priest_level()) +
        random(3)) * 60.0, 0.0, &remove_spell_effect_object());
    remove_alarm(gAlarm);
    return 1;
}

public void
set_ppain_time(int t)
{
    if (t > 15) {
        t = 15;
    }
    remove_alarm(alarm);
    alarm = set_alarm(itof(45 + t), 0.0, &dispel_spell_effect(this_object()));
}

#ifdef 0
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
    write("You are in such terrible pain that it is impossible to do that.\n");
    return 1;
}

init()
{
    ::init();
    if (!gRemovedAlarm)
        add_action(do_all_commands, "", 1);
}
#endif

void
pain_message()
{
    string *s;
    int tmp;

    if (spell_target->query_ghost())
    {
    	// Target died, so remove ourselves quietly
    	dispel_spell_effect(0);
    	return;
    }

    switch(random(10))
    {
        case 0..2:
            s = ({ "You scream in pain!",
            QCTNAME(spell_target) + " screams in pain!" });
            break;
        case 3..4:
            s = ({ "You twitch uncontrollably as a new wave of pain " +
            "sears through your body.",
            QCTNAME(spell_target) + " twitches uncontrollably." });
            break;
        case 5..7:
            s = ({ "You moan pitifully.",
            QCTNAME(spell_target) + " moans pitifully." });
            break;
        default:
            s = ({ "The pain sears through your body.",
            "" });
    }

    spell_target->catch_tell(s[0] + "\n");
    if (s[1] != "")
        tell_room(environment(spell_target), s[1] + "\n", spell_target);

#ifdef 0
    tmp = (100 - ftoi(get_alarm(alarm)[2])) / 20;
    if (!tmp)
        tmp = 1;
    spell_target->add_fatigue(-(spell_target->query_max_fatigue() / tmp));
#endif
    spell_target->add_tmp_stat(SS_CON,
        -((query_spell_effect_caster()->query_priest_level() + 1) * 3), random(10));
 
    gAlarm = set_alarm(itof(10+random(10)), 0.0, pain_message);
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
        spell_target->catch_tell("The pain makes your muscles cramp, and you " +
        "lose your seat on your horse, falling to the ground.\n");

        horse->do_dismount(spell_target,1,1);

        tell_room(E(spell_target),QCTNAME(spell_target) + " falls off the " +
        horse->short() + ".\n", spell_target);
        
    }
    else
    {
        spell_target->catch_msg("The pain makes your muscles cramp, and you " +
        "curl up on the ground.\n");
    }

    //spell_target->add_prop(LIVE_S_EXTRA_SHORT, " is curled up in pain");
    spell_target->add_stun();
        
    spell_target->add_subloc(PAIN_SUBLOC, TO);

    gAlarm = set_alarm(itof(10+random(10)), 0.0, pain_message);
    alarm = set_alarm(80.0 + itof(random(30)), 0.0, &dispel_spell_effect(this_object()));
    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "You are curled up on the ground, screaming in terrible pain.\n";

    return C(HE(me)) + " is curled up on the ground, screaming in pain.\n";
}

