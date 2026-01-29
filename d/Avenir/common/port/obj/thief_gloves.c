/*
 * Created By : Ibun 070524
 *
 * Revisions:
 * 	Lucius, Jun 2017: Cleaned up duplicated code and
 * 	                  extra_skill handling.
 * 	Lucius, Sep 2017: Try to fix skill-wearing bugs.
 */
#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"
#include <stdproperties.h>     /* Where the properties are defined. */
#include <wa_types.h>          /* Where weapon and armour defs are. */
#include <ss_types.h>          /* Where the skill defines are.      */
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>

#define EXTRA_KNIFE	10
#define EXTRA_PPOCKET	10

/* WHO, SKILL, AMOUNT */
#define INC_SK_EXTRA(x, y, z) (x)->set_skill_extra(y, \
    (x)->query_skill_extra(y) + z)
#define DEC_SK_EXTRA(x, y, z) (x)->set_skill_extra(y, \
    (x)->query_skill_extra(y) - z)

#define DBG(msg) if (wearer->query_wiz_level()) \
    wearer->catch_tell("Wizinfo: "+ msg +"\n");

int timer, got_extra_pp, got_extra_knife;

string message();


void
create_armour()
{
    setuid();
    seteuid(getuid());

    set_name("gloves");
    add_name("_ave_thief_gloves");
    add_adj("black");
    set_adj("leather");
    set_short("pair of black leather gloves");
    set_pshort("pairs of black leather gloves");
    set_long("These are a pair of gloves made from "+
      "skin. The leather is shimmering in black, " +
      "almost distracting you, and on the back " +
      "you see a cross branded into the gloves.\n");
    set_at(A_HANDS);
    set_ac(2);
    set_af(TO);
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(MAGIC_AM_MAGIC, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
	    "Theese gloves gives excellent grip. ", 10,
	    "It has the virtues of affecting the wearers "+
	    "stealing and knife skills. ", 70,
	    "The gloves may allow the wearer to distract livings.\n", 90})),
    add_prop(OBJ_S_WIZINFO,
	"Theese gloves increase SS_PICK_POCKET and SS_KNIFE by 5 " +
	"and allows the wearer to distract livings in the room for " +
	"a short while (5-10sec).\n");
}

void
init()
{
    ::init();
    add_action("distract", "distract");

    if (!query_worn())
    {
	got_extra_pp = 0;
	got_extra_knife = 0;
    }
}

mixed
wear(object arm)
{
    int extra;
    object cloak = wearer->query_armour(TS_ROBE);

    DBG("WEARER == " + wearer->query_name());

    if (!got_extra_pp)
    {
	extra = wearer->query_skill_extra(SS_PICK_POCKET);
	INC_SK_EXTRA(wearer, SS_PICK_POCKET, EXTRA_PPOCKET);
        got_extra_pp = wearer->query_skill_extra(SS_PICK_POCKET) - extra;
	DBG("Added extra pick pocket skill: "+  got_extra_pp);
    }

    if (cloak && (cloak->id("_ave_shadow_cloak")) )
    {
        if (!got_extra_knife)
        {
	    DBG("CLOAK FOUND: Adding extra knife skill.");
	    extra = wearer->query_skill_extra(SS_WEP_KNIFE);
	    INC_SK_EXTRA(wearer, SS_WEP_KNIFE, EXTRA_KNIFE);
	    got_extra_knife = wearer->query_skill_extra(SS_WEP_KNIFE) - extra;
	    DBG("Added extra knife skill: "+  got_extra_knife);
        }

       	// Add the cloak skills
        cloak->add_extra_skills();
    }
    return 0;
}

int
remove(object arm)
{
    object cloak = wearer->query_armour(TS_ROBE);

    DBG("WEARER == " + wearer->query_name());
    if (got_extra_pp)
    {
	DBG("Removing extra pick pocket skill: "+ got_extra_pp);
	DEC_SK_EXTRA(wearer, SS_PICK_POCKET, got_extra_pp);
        got_extra_pp = 0;
    }

    if (got_extra_knife)
    {
	DBG("Removing extra knife skill: "+ got_extra_knife);
	DEC_SK_EXTRA(wearer, SS_WEP_KNIFE, got_extra_knife);
        got_extra_knife = 0;
    }

    // Call the function in the cloak
    if (cloak && cloak->id("_ave_shadow_cloak"))
        cloak->remove_extra_skills();

    return 0;
}

int
remove_extra_skills()  // Called if the player remove the cloak
{
    if (!got_extra_knife)
	return 0;

    DBG("WEARER == " + wearer->query_name());
    DBG("CLOAK REMOVED: Removing extra knife skill.");
    DEC_SK_EXTRA(wearer, SS_WEP_KNIFE, EXTRA_KNIFE);
    got_extra_knife = 0;
    return 1;
}

int
add_extra_skills()   // Called if the player wear the cloak
{
    int extra;

    if (got_extra_knife)
	return 0;

    DBG("WEARER == " + wearer->query_name());
    DBG("CLOAK WORN: Adding extra knife skill.");
    extra = wearer->query_skill_extra(SS_WEP_KNIFE);
    INC_SK_EXTRA(wearer, SS_WEP_KNIFE, EXTRA_KNIFE);
    got_extra_knife = wearer->query_skill_extra(SS_WEP_KNIFE) - extra;
    DBG("Added extra knife skill: "+  got_extra_knife);
    return 1;
}

int
do_distract(object who, int amount)
{
    float time = 5.0 + ((rnd() * 10.0) / 2.0);
    object distract = clone_object(PORT + "obj/distract");

    int awareness = min(amount, who->query_skill(SS_AWARENESS));
    DEC_SK_EXTRA(who, SS_AWARENESS, awareness);

    distract->time_left(time, awareness, who);
    distract->move(who, 1);

    string text = message();
    who->catch_msg(QCTNAME(TP) + text + "\n");
}

int
distractall(string str)
{
    int i, failed;
    object *victims;

    victims = FILTER_OTHER_LIVE(all_inventory(ENV(TP)));

    if (sizeof(victims) < 1)
    {
        write("Distract who?");
        return 1;
    }

    for (i = 0; i < sizeof(victims); i++)
    {
        timer = time();

        if (!(random(5))) // 20% fail
            failed++;
        else if (!(CAN_SEE(TP, victims[i]))) // Can not distract unseen opps
            failed++;
        else if (!(CAN_SEE(victims[i], TP))) // Can not distract opps that do not see you
            failed++;
        else
	    do_distract(victims[i], 20);
    }

    if (!failed)
        write("You managed to distract your victims.\n");
    else if (failed == sizeof(victims))
        write("You failed to distract anyone.\n");
    else
	write("You managed to distract some of your victims.\n");

    return 1;
}

int
distract(string str)
{
    object victim;

    if (!query_worn())
        return 0;

    if (!strlen(str))
    {
        notify_fail("Possible ways are: 'distract <target>' "+
	    "and 'distract all'.\n");
        return 0;
    }

    if (time() - timer <= 20)
    {
        if (TP->query_wiz_level())
	{
            write("Wizinfo: Your wizard status allows you to distract " +
                "sooner than normal.\n");
	}
        else
        {
            write("Not so soon after last attempt.\n");
            timer = time(); // Resetting timer to prevent spam
            return 1;
        }
    }

    if (TP->query_attack())
    {
        write("You can not distract someone while fighting.\n");
        return 1;
    }

    if (str == "all")
        return distractall(str);

    /* Find the target of the of the action. */
    object *targetlist = PARSE_THIS(str, "[the] %l");

    switch(sizeof(targetlist))
    {
    case 0:
        notify_fail("Who do you want to distract?\n");
        return 0;

    case 1:
        victim = targetlist[0];
        /* Must aim at something in your environment. */
        if (environment(victim) != environment(this_player()))
        {
            notify_fail("You cannot distract something you carry.\n");
            return 0;
        }
        break;

    default:
        /* Sure, two birds with the same stone ?!? */
        notify_fail("Aiming for two birds with the same stone? Please " +
            "select only a single target.\n");
        return 0;
    }

    if (!victim)
    {
        write("There is no such target here.\n");
        return 1;
    }

    if (!(CAN_SEE(TP, victim)))
    {
        write("Distract who?\n");
        return 1;
    }

    if (!(CAN_SEE(victim, TP)))
    {
        write("The victim looks undistracted.\n");
        return 1;
    }

    if (!(random(10)))  // 10% chance of fail
    {
        write("Your victim does not look distracted.\n");
        timer = time();
        return 1;
    }

    timer = time();
    do_distract(victim, 40);

    TP->catch_msg("You manage to distract " + QTNAME(victim) +
	" for a short while.\n");

    string text = message();
    victim->catch_msg(QCTNAME(TP) + text + "\n");
    return 1;
}

string
message()
{
    return one_of_list(({
      " flashes a smile in your direction.",
      " grins at you.",
      " giggles to " + TP->query_objective() + "self.",
      " waves " + TP->query_possessive() + " hands.",
      " inspects " + TP->query_possessive() + " finger nails.",
      " looks behind your back.",
      " whistles a strange tune.",
      " throws a small stone in the air.",
      " draws a figure in the air.",
      " rolls " + TP->query_possessive() + " eyes.",
      " snickers softly at something behind " +
          " your back.",
      " throws a small rock in the air.",
      " moves " + TP->query_possessive() +
          " hand to " + TP->query_possessive() +
          " arm pit and makes a farting sound.",
      " hickups loudly.",
      " jumps high in the air.",
      " dances a piruett.",
      " flexes " + TP->query_possessive() + " muscles.",
      " dusts some dust from your shoulder."
    }));
}
