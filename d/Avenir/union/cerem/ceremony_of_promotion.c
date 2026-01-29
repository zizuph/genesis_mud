/*
 * Revisions:
 *   Lucius, May 2016: Fix OCC_LEVEL setting
 *   Lucius, Jul 2017: Re-code.
 *
 */
#include "../defs.h"
inherit CEREMONY + "ceremony";

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

public string sph, *flame_msgs = ({
	"The flame flickers darkly.\n",
	"The flame writhes and twists, as if it were alive, emitting "+
		"red-glowing sparks throughout the area.\n",
	"Wavering sinuousley, the flame casts long shadows " +
		"into the mist.\nThe shadows seem to move of their " +
		"own accord, as if alive.\n",
	"The mist gathers about the flame in a soft halo.\n"
});

/* Bathed within the last 1/2 hour? */
#define RECENTLY_BATHED(who) \
    ((time() - who->query_prop(CLEANSED)) < (60 * 30))


public void
ceremony_tell(void)
{
    if (valid_ceremony())
    {
	tell_room(ENV(TO), one_of_list(flame_msgs));
	set_alarm(5.0 + itof(random(20)), 0.0, ceremony_tell);
    }
}

public void
create_ceremony()
{
    set_ceremony_sequence(({
	1, "kneel/bow 'before' [the] 'flame' / 'fire'", "kneel_flame",
	1, "pledge [my] 'soul' 'to' [the] 'flame' / 'fire' / 'jazur' "+
	   "[of] [flame] / [fire] / [jazur]", "pledge_soul",
	1, "pledge [my] 'body' 'to' [the] 'flame' / 'fire' / 'jazur' "+
	   "[of] [flame] / [fire] / [jazur]", "pledge_body",
	1, "feel/touch/pass/reach [my] [hand] / [hands] [within] / [in] / "+
	   "[into] / [through] [the] 'flame' / 'fire'", "reach_hand",
	0, "invoke %s", "invoke_sphere",
	0, "name %s", "name_trainee",
    }));

    set_alarm(10.0, 0.0, ceremony_tell);
}

public int
valid_ceremony()
{
    if (!STATE)
    {
	NF("The flame has gone out - no ceremony may be performed.\n");
	return 0;
    }

    if (ENV(TO) && (file_name(ENV(TO)) != HOME))
    {
	NF("This ceremony may only be performed at the Fire of Jazur.\n");
	return 0;
    }

    return 1;
}

public varargs int
valid_master(object who = this_player(), object for_obj = who)
{

    if (!IS_MEMBER(who))
	return NF("You are not a member of the Union.\n");

    return MEMBER_SPHERE(who, SPH_MENTOR);
}

public int
query_worn_garb(object who)
{
    string *files = ({});

    foreach(object ob: who->query_clothing(-1))
	files += ({ MASTER_OB(ob) });

    return (member_array(OBJ + "boots", files) != -1) &&
	   (member_array(OBJ + "cape",  files) != -1);
}

public varargs int
valid_target(object who = this_player(), object for_obj = who)
{
    string *fail = ({ });

    if (!IS_MEMBER(who))
    {
	fail = ({ "You are not a member of the Union.\n",
	    	  " must be a member of the Union.\n" });
    }
    else if (who->query_union_sphere() != SPH_TRAINING)
    {
	fail = ({ "You must be of the Sphere of Training.\n",
	    	  " must be of the Sphere of Training.\n" });
    }
    else if (!RECENTLY_BATHED(who))
    {
	fail = ({ "You have not been cleansed recently.\n",
	    	  " has not been cleansed recently.\n" });
    }
    else if (!query_worn_garb(who))
    {
	fail = ({ "You must be dressed in the full garb of the Union.\n",
	    	  " must be dressed in the full garb of the Union.\n" });
    }
    else if (sizeof(who->query_weapon(-1)))
    {
	fail = ({ "Your hands must be free of weapons.\n",
		  " hands must be free of weapons.\n" });
    }

    if (sizeof(fail))
    {
	if (who == for_obj)
	    notify_fail(fail[0]);
	else
	    notify_fail(who->query_The_name(for_obj) + fail[1]);

	return 0;
    }

    return 1;
}

public int
kneel_flame(string str)
{
    write("You kneel before the flame, your head bowed nearly "+
	"to the ground.\n");
    say(QCTNAME(TP) + " kneels before the flame, " + HIS(TP) +
	" head bowed nearly to the ground.\n");
    return 1;
}

public int
pledge_soul(string str)
{
    TP->command("shout I offer my soul to the fires of the Jazur Flame,");
    TP->command("shout that it may burn in the purifying fires!");
    return 1;
}

public int
pledge_body(string str)
{
    TP->command("shout I offer my body to Jazur's Fires,");
    TP->command("shout that within her dark beauty");
    TP->command("shout I may become graceful and dignified!");
    return 1;
}

public void
fire_recede(object who)
{
    who->catch_tell("The fire receeds.\nYou have been purified.\n");
    tell_room(ENV(who), "The Fires recede from " +
	QTNAME(who) + ".\n", who, who);
}

public void
fire_hurt(object who)
{
    who->catch_tell("The Fire enters your soul, burning you!\n");
    tell_room(ENV(who), "The fires completely enshroud " +
	QTNAME(who) + ".\n", who, who);

    who->heal_hp(-(who->query_max_hp() / 2));
    who->command("$pain");

    set_alarm(5.0, 0.0, &fire_recede(who));
}

public int
reach_hand(string str)
{
    write("You reach your hand within the Fire.\n"+
	"The flame wraps around your arm, tendrils reaching up to your "+
	"body, engulfing you.\n");
    say(QCTNAME(TP) + " reaches " + HIS(TP) + " hand into the flame.\n"+
	"Dark tendrils of fire wrap around " + HIS(TP) + " arm and "+
	"reach up into " + HIS(TP) + " body.\n");

    set_alarm(4.0, 0.0, &fire_hurt(TP));
    return 1;
}

public int
invoke_sphere(string str)
{
    if (!strlen(str))
	return NF("Invoke what sphere?\n");

    str = lower_case(str);

    if (!SPHERES[str])
    {
	NF("Invoke what sphere? Possible options are:\n\t"+
	    COMPOSITE_WORDS(map(m_indexes(SPHERES), capitalize)) + ".\n");
	return 0;
    }

    sph = str;

    write("You chant out: Jazur, bring upon us the glory of the "+
	"Sphere of " + sph + "!\n");
    say(QCTNAME(TP) + " chants out: Jazur, bring upon us the "+
	"glory of the Sphere of " + sph + "!\n");

    return 1;
}

public void
all_respect(object who)
{
    object *npcs = LIST->query_present_members();
    npcs = filter(npcs, &->query_npc());
    npcs->command("bow resp " + OB_NAME(who));
}

public int
name_trainee(string str)
{
    object scarf, who = get_present(str);

    if (!objectp(who))
	return NF("Name who as a Warrior of the Union?\n");

    if (!IS_MEMBER(who))
       return NF("They are not a member of the Union.\n");

    if (!strlen(sph))
       return NF("You have not invoked a Sphere.\n");

    if (who != query_ceremony_target())
       return NF("They are not the subject of the ceremony.\n");

    if (who->query_skill(OCC_LEVEL) <= NOVICE)
	who->set_skill(OCC_LEVEL, NORMAL);

    who->set_union_sphere(sph);
    who->save_me();

    TP->catch_msg("You pronounce: " + who->query_name() + ", you are "
        + "now a true member of the Union. Yours is now the "
        + "Sphere of " + CAP(sph) + ".\n"
        + "You bestow upon "+ QCTNAME(who) +" a black webcloth scarf.\n"
        + QCTNAME(who) + "'s eyes fade from grey to black.\n");
    who->catch_msg(QCTNAME(TP) + " pronounces: " + who->query_name() + ", you are "
        + "now a true member of the Union. Yours is now the "
        + "Sphere of " + CAP(sph) + ".\nYour eyes suddenly snap "
        + "into greater focus, everything seems to be wreathed "
        + "in sharp and dark outlines.\n"
        + QCTNAME(TP) +" bestows upon you a black webcloth scarf.\n");
    say(QCTNAME(TP) + " pronounces: " + who->query_name() + ", you are "
        + "now a true member of the Union. Yours is now the "
        + "Sphere of " + CAP(sph) + ".\n" + QCTNAME(who) + " shudders "
        + "slightly.\n", ({ who, TP }));
 
    scarf = clone_object(OBJ +"combat_veil");
    scarf->move(who, 1);
   
    LIST->add_named(who->query_name());
    LIST->remove_nov_lvl(who->query_name());    

    set_alarm(3.0, 0.0, &all_respect(who));
    set_alarm(3.1, 0.0, remove_object);

    LOG_COUNC(NM(TP)+" Named "+ NM(who) +" with all due ceremony");
    return 1;
}

public string
ceremony_help()
{
    return "The Ceremony of Promotion requires the following:\n "
      + "The subject of the ceremony must have recently bathed within the "
      + "waters of the astuary, and must be clothed in the garb of the Union "
      + "(cape, boots, veil, and shirt). The ceremony begins by "
      + "the subject kneeling before the flame. The subject must then "
      + "pledge his soul to the Jazur flame, and then pledge his body to "
      + "the flame. The subject must then show his trust in the flame by "
      + "reaching within the fire. The ceremony master must then "
      + "invoke the sphere which will be added to the subject. The ceremony "
      + "then ends with the master naming the subject, at which point "
      + "the subject is a full and true member of the Union of the "
      + "Warriors of Shadow.\n";
}
