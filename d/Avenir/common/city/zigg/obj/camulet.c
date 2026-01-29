 // file name:    ~Avenir/common/city/zigg/obj/camulet.c
 // creator(s):    Zielia & Lucius, 09-2006
 // purpose:       Amulet of Cahor, prize for defeating Rynal.
 // note:          'invoke' - Reveal names of players in a room.
 // 		   'touch'  - Add bonus to see_invis and awareness.
 // 		   'wear'   - Detect illusion magic & invis players.
 //		   Touch and Invoke have mana costs, wearing doesn't.
 // revisions:
 // bugs:
 // to-do:

inherit "/std/armour";
inherit "/lib/keep";

#include "zigg.h"
#include "/d/Avenir/include/deities.h"

#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

// The awareness was removed because of stupid balance rules.
//#define BONUS_AWARE  25
#define BONUS_INVIS  50
#define BONUS_MANA   15
// Half the benefit, half the cost.
//#define BONUS_MANA   30
//  The invoke ability was deemed too much.
//#define INVOKE_MANA 300

#define ALARM 30.0
#define UNAME "zigg:amulet:cahor"
#define VNAME ("detect_invis:" + file_name(this_object()))

private static int alarm, active;


public void 
create_armour(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"amulet", "amulet of cahor", UNAME}));
    set_pname(({"amulet", "amulets of cahor"}));
    set_short("engraved chromatic amulet");
    set_pshort("engraved chromatic amulets");
    set_adj(({"engraved", "inscribed", "chromatic", "cahor"}));
    set_long("shouldn't see this");

    add_item(({"circles","half-circles","merged circles"}),
	"shouldn't see this either.\n");

    add_item(({"engraving", "inscription"}),
	"Engraved into the chromatic amulet is the symbol of "+
	"two circles, half-merged.\n");

    set_ac(1);
    set_af(TO);
    set_am(({ 0, 0, 0}));
    set_at(A_NECK);
    set_likely_break(20);

    add_prop(CAHOR_OFFERING, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "illusion" }));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    /* XXX:  Needs updating. */
    add_prop(MAGIC_AM_ID_INFO ,
           ({ "   Illusion and deception are rife in this world.\n", 11,
              "   And I shall tingle and flash when it lies near.\n", 22,
              "   With but a touch, those secrets may be revealed.\n", 33,
              "   Or you may invoke Cahor to unmake deceptions.\n", 55,
            }));

    add_prop(OBJ_S_WIZINFO, "Adds the ability to detect hidden people "+
	"in the room\n\tas well as revealing names through the 'invoke' "+
	"command.\n\tWhen 'touch'-ed, increases see_invis and awareness.\n");

    add_prop(OBJ_I_VALUE, 2900);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 400);

    set_keep(1);
}

public varargs mixed
long(string str, object for_obj = this_player())
{
    if (strlen(str))
    {
	if (IN_ARRAY(str, ({"circles","half-circles","merged circles"})))
	{
	    str = "The two circles engraved into the chromatic amulet "+
		"are depicted as being half-merged together at a "+
		"diagonal going from northwest to southeast.";

	    if (active)
	    {
		str += " The circles are visibly pulsing to an "+
		    "alternating beat.";
	    }

	    return str + "\n";
	}

	return ::long(str, for_obj);
    }

    str = "This "+ short() +" is crafted from some unknown chromatic "+
	"material. It glistens with rainbowed hues in even the faintest "+
	"light. Inscribed into its surface is the image of half-merged "+
	"circles.";

    if (active)
	str += " They seem to glow on and off to some unknown beat.";

    if (IS_SYBARITE(for_obj) ||
	(for_obj->query_skill(SS_LANGUAGE) > (60 + random(50))))
    {
        str += " You aren't certain, but you think that this amulet "+
               "harnesses the power of Cahor, the Sybarite Goddess "+
               "of the Seventh Hour, who governs all illusory arts.";
    }

    return str + "\n";
}

/*
 * Doesn't actually add resistance, just detects illusion magic.
 */
public mixed 
query_magic_protection(string prop, object what)
{
    if ((what == wearer) && (prop == MAGIC_I_RES_ILLUSION))
    {
	wearer->catch_tell("A rainbow hued light ripples across "+
	    "the surface of the "+ short() +".\n");
        tell_room(ENV(wearer), QCTPNAME(wearer) +" "+
            QSHORT(TO) +" flashes with a rippling, "+
	   "rainbow-hued light.\n", wearer, what);

        return ({ 0, 1 });
    }
 
    return ::query_magic_protection(prop, what);
}
 
public mixed 
wear(object ob)
{
    int damage;

    if ((ob != TO) || (TP != ENV(TO)))
        return -1;

    if ((damage = TP->query_magic_res(MAGIC_I_RES_ILLUSION)) > 0)
    {
        write("As you try to wear the amulet around your neck, "
             +"the chromatic metal heats up and turns a solid "+
	     "orange, searing you as you touch it.\n");
        say(QCTNAME(TP)+" tries to wear the "+ short() +" but quickly "+
	    "stops as it turns a searing orange colour.\n");

        TP->heal_hp(-(damage * 5));
        return "";
    }

    TP->add_magic_effect(TO);
    TP->add_notify_meet_interactive(VNAME);
    return 0;
}
 
public mixed
remove(object ob)
{
    if (!objectp(wearer) || (TP != ENV(TO)))
	return 1;

    if (alarm)
    {
	say(QCTNAME(wearer) +" struggles to remove the "+ short() +
	    ", but fails.\n");
	return "You struggle to remove the "+ short() +", but fail.\n";
    }

    wearer->remove_notify_meet_interactive(VNAME);
    wearer->remove_magic_effect(TO);

    /* Disable active effect. */
    if (active)
	TO->emote_hook("touch", wearer, "", ({}), 0, 1);

    return 0;
}

public nomask void
detect_invis(void)
{
    if (active)
	return;

    /* not worn? */
    if (!objectp(wearer))
	return;

    /* Only one message per room. */
    if (time() == wearer->query_last_met_interactive())
	return;

    /* skip non-invis */
    if (!TP->query_invis())
	return;

    /* skip wizards */
    if (TP->query_wiz_level())
	return;

    set_alarm(0.0, 0.0, &wearer->catch_tell(
	    "You sense a tingling vibration from your "+ short() +
	    ", as though it's warning you of unseen others.\n"));
}

#ifdef INVOKE_MANA

/* Invoke, phase 2 */
private void
invoke_two(void)
{
    object *obs;
    string *arr = ({});

    alarm = 0;

    /* Just in case. */
    if (!objectp(wearer))
	return;

    obs = all_inventory(ENV(wearer));
    obs -= ({ wearer });

    foreach(object ob : filter(obs, query_interactive))
    {
	string name = ob->query_met_name();

	/* Common case first. */
	if (ob->query_prop(OBJ_I_HIDE))
	    name = "[" + name +"]";
	else if (ob->query_invis())
	    name = "("+ name +")";

	arr += ({ name });
    }

    wearer->add_mana(-(INVOKE_MANA));

    if (!sizeof(arr))
    {
	wearer->catch_tell("\nThough your vision is keen, you find "+
	    "no souls with which to reveal.\n");
    }
    else
    {
	wearer->catch_tell("\nThrough your keen vision and the gift "+
	    "of alien insight, you detect these presences amongst you:\n");
	wearer->catch_tell(sprintf("%|=13.75@s\n", arr));
    }

    wearer->catch_tell("\nYour vision returns to normal and the alien "+
	"presence has left you.\n");
    tell_room(ENV(wearer), QCTPNAME(wearer) +" eyes return to normal "+
	"along with "+ HIS(wearer) +" posture.\n", wearer, wearer);
}

/* Invoke, phase 1 */
private void
invoke_one(void)
{
    alarm = 0;

    /* Just in case. */
    if (!objectp(wearer))
	return;

    wearer->catch_tell("\nYou feel an otherwordly presence invade your "+
	"being and your vision turns a bluish hue.\n\nYou find "+
	"yourself scanning the surroundings not of your own volition...\n");
    tell_room(ENV(wearer), QCTNAME(wearer) +" goes still, "+ HIS(wearer) +
	" eyes taking on an alien, cobalt-blue hue, as though overlain "+
	"with anothers as "+ HE(wearer) +" scans the surroundings with "+
	"mechanical precision.\n", wearer, wearer);

    wearer->add_mana(-(INVOKE_MANA / 2));
    alarm = set_alarm(2.0, 0.0, invoke_two);
}

public int
do_invoke(string str)
{
    if (!strlen(str))
	return notify_fail("Invoke what?\n");

    if (lower_case(str) != "cahor")
	return notify_fail("Invoke what?\n");

    if (wearer != this_player())
    {
        notify_fail("Invoke what? Perhaps you should be "+
	    "wearing the "+ short() +".\n");
	return 0;
    }

    if (TP->query_mana() < (INVOKE_MANA * 2))
    {
	write("You lack the mental fortitude to draw upon "+
	    "the "+ short() +"'s mysteries.\n");

	return 1;
    }

    /* Can't invoke while active. */
    if (active)
    {
	write("You invoke the "+ short() +" but all it does is "+
	    "throw off rainbow coloured flashes.\n");
	say(QCTNAME(TP) +" grasps "+ HIS(TP) +" "+ short() +
	    " and it throws off rainbow coloured flashes.\n");

	return 1;
    }

    write("You invoke the "+ short() +" and it sparkles prettily "+
	"in return.\n");
    say(QCTNAME(TP) +" invokes "+ HIS(TP) +" "+ short() +" and it "+
	"sparkles prettily for "+ HIM(TP) +" in response.\n");

    alarm = set_alarm(3.0, 0.0, invoke_one);
    return 1;
}

/*
 * Add the 'invoke' command.
 */
public void
init(void)
{
    ::init();
    add_action(do_invoke, "invoke");
}

#endif  INVOKE_MANA

/* Handle mana drain. */
private void
heart_beat(void)
{
    /* Just in case. */
    if (!objectp(wearer))
    {
	remove_alarm(active);
	active = 0;
	return;
    }

    /* Not enough mana. */
    if (wearer->query_mana() < BONUS_MANA)
    {
	/* Start draining health. */
	wearer->heal_hp(-(BONUS_MANA * 2));

	/* Not enough health to go on. */
	if (wearer->query_hp() < BONUS_MANA)
	{
	    TO->emote_hook("touch", wearer, "", ({}), 0, 1);
	    return;
	}
    }

    /* Suck mana. */
    wearer->add_mana(-BONUS_MANA);

    /* Add random messages here? */
    switch(random(10))
    {
    case 1:
	wearer->catch_tell("The "+ short() +" flashes brightly "+
	    "from around your neck.\n");
	break;
    case 3:
	wearer->catch_tell("You feel a faint tingling emanating from "+
	    "the "+ short() +".\n");
	break;
    case 5:
	wearer->catch_tell("A blue haze obscures your vision for a "+
	    "brief moment.\n");
	break;
    case 7:
	if (CAN_SEE_IN_ROOM(wearer))
	{
	    wearer->catch_tell("Everything seems to move into "+
		"sharper focus.\n");
	}
	break;
    default:
	/* No message. */
	break;
    }
}

/*
 * Capture the 'touch' emote.
 */
public void
emote_hook(string emote, object actor, string adverb, object *oblist,
	   int cmd_attr, int target)
{
    /* Wearer isn't the emoter. */
    if (!target || !objectp(wearer) || (actor != wearer))
	return;

    /* Not our emote. */
    if (emote != "touch")
	return;

    /* Being invoked. */
    if (alarm)
	return;

    /* Turn on / Turn off */
    if (active)
    {
	remove_alarm(active);
	active = 0;

//	ALTER_SKILL(wearer, SS_AWARENESS, -BONUS_AWARE);
	ALTER_PROP(wearer, LIVE_I_SEE_INVIS, -BONUS_INVIS);

	tell_room(ENV(wearer),
	    "The "+ short() +" ceases its pulsing glow.\n", 0, TO);
    }
    else
    {
	/* Not enough mana. */
	if (wearer->query_mana() < (BONUS_MANA * 10))
	    return;

	wearer->add_mana(-BONUS_MANA);
	active = set_alarm(ALARM, ALARM, heart_beat);

//	ALTER_SKILL(wearer, SS_AWARENESS, BONUS_AWARE);
	ALTER_PROP(wearer, LIVE_I_SEE_INVIS, BONUS_INVIS);

	tell_room(ENV(wearer), "The merged circles of the "+ short() +
	    " begin to glow with an alternating beat.\n", 0, TO);
    }
}

/*
 * There can be only one.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    foreach(object ob : all_inventory(dest))
    {
	if (ob == TO)
	    continue;

	if (ob->id(UNAME))
	{
	    dest->catch_tell("The "+ ob->short() +" shimmers "+
		"then disappears in a flash of rainbow-hued light.\n");
	    ob->remove_object();
	}
    }
}

/*
 * Handle destruction.
 */
public void
remove_object(void)
{
    /* Remove invoke effect. */
    if (alarm)
	remove_alarm(alarm);

    /* Disable active effect. */
    if (active)
	TO->emote_hook("touch", wearer, "", ({}), 0, 1);

    ::remove_object();
}
