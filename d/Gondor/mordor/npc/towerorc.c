/*
 * /d/Gondor/mordor/npc/towerorc.c
 *
 * This is the default orc in the Cirith Ungol. This orc will also patrol in
 * Torech Ungol from time to time. It is a very nice orc, for everything
 * in this orc is adjustable with only one patch. His armour and weapons are
 * dependant on his average stats and his skills will also be dependant on
 * his stats. The orc has several attack cries, which he obviously not waists
 * on wizards. With a slight chance he will get a key to the tower at
 * Cirtih Ungol and you can also give him a whip.
 *
 * I spent some time time coding this sucker and even more on debugging and
 * enhancing it. If you want to copy this orc and adjust it for your own
 * purposes, I do not mind you doing so IF you leave this header in tact.
 * You can add your own header AFTER this one.
 *
 * /Mercade 27 September 1993
 *
 * Revision history:
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

inherit "/std/monster";

#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Gondor/common/lib/logkill.c"
#include "/d/Gondor/defs.h"

#undef ARM_DIR
#undef WEP_DIR
#define ARM_DIR MORDOR_DIR + "obj/arm/"
#define WEP_DIR MORDOR_DIR + "obj/wep/"

#define TOWER_KEY MORDOR_DIR + "obj/towerkey"
#define WHIP      WEP_DIR + "whip"

#define CHANCE_FOR_KEY      20

#define HIGH_ORC_LEVEL      80
#define MEDIUM_ORC_LEVEL    50
#define MIN_ALIGNMENT_LEVEL -50

#define HIGH_ORC_STRING     "_high"
#define MEDIUM_ORC_STRING   "_med"
#define LOW_ORC_STRING      "_low"

#define RANDOM_WEAPONS  ({ "sword", "club", "axe" })
#define RANDOM_ARMOURS  ({ "helm", "shield" })
#define DEFAULT_ARMOURS ({ "mail" , "greaves" })

#define ALIGNLOOKS ({ "cruel", "angry", "mean", "foul", "brutal", "sinister", \
    "evil", "savage", "dangerous", "strong" })

#define ATTACKCRY ({ "DIE! You miserable rat!",                   \
                     "Warn Shagrat, there are intruders.",        \
                     "This will be your death, filthy creature!", \
                     "Da brkoles grmpaz rowpyll!",                \
                     "I'll help you with that wimp.",             \
                     "Can't you even kill him alone, coward!" })

/*
 * Prototypes
 */
void add_triggers();
void add_act_cact();

/*
 * Global variables
 */
int knight_prestige;
string looks = ONE_OF_LIST(ALIGNLOOKS);

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_pname("orcs");
    set_race_name("orc");
    set_adj(looks);
    set_short(looks + " orc");
    set_pshort(looks + " orcs");

    set_long("@@long_description");

    add_prop(CONT_I_HEIGHT, 160 + random(20));
    add_prop(CONT_I_WEIGHT, 75000 + random(15000));
    add_prop(CONT_I_VOLUME, 70000 + random(20000));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 2);

    add_act_cact();
    add_triggers();

    set_aggressive(1);
}

/*
 * Give the long description of the orc
 */
string
long_description()
{
    return BSN("This is " + LANG_ADDART(TO->short()) + " with long arms " +
        "and crooked legs. It looks mean and you do not want to mess with " +
        "it. " +
        (present("armour", TO) ?
            "On its armour you can see a crest painted: A red eye, meaning " +
            "that this " + query_real_name() + " is a member of the armies " +
            "of the dark Lord." :
            "To your astonishment you notice that the " + query_real_name() +
            " doesn't wear any armour at all."));
}

/*
 * The nonmet name will be the same as the short description. This is a hack
 * to make the name-change from orc to uruk work ;-) Note that you cannot use
 * the short() here for short() uses query_nonmet_name().
 */
string
query_nonmet_name()
{
    return (looks + " " + query_real_name());
}

/*
 * Make orc looks. If an orc has average stats >= HIGH_ORC_LEVEL he will be
 * called uruk rather than orc. Note that uruk-hai is plural.
 */
void
make_orc_looks(int base)
{
    if (base >= HIGH_ORC_LEVEL)
    {
        set_name("uruk");
        set_pname("uruk-hai");
        add_adj("uruk");
        add_pname("hai");
        set_short(looks + " uruk");
        set_pshort(looks + " uruk-hai");

        add_prop(CONT_I_WEIGHT, 95000 + random(20000));
        add_prop(CONT_I_VOLUME, 85000 + random(20000));
        add_prop(LIVE_I_SEE_DARK, 2);
    }
}

/*
 * Give the orc armour and a weapon.
 */
void
arm_me(string type, int whip)
{
    int i;

    seteuid(getuid(this_object()));

    /*
     * Give him a key if he is 'strong' or else with a slight chance.
     */
    if ((random(100) < CHANCE_FOR_KEY) || (type == HIGH_ORC_STRING))
    {
        clone_object(TOWER_KEY)->move(TO);
    }

    clone_object(WEP_DIR + ONE_OF_LIST(RANDOM_WEAPONS) + type)->move(TO);
    clone_object(ARM_DIR + ONE_OF_LIST(RANDOM_ARMOURS) + type)->move(TO);

    for (i = 0; i < sizeof(DEFAULT_ARMOURS); i ++)
    {
        clone_object(ARM_DIR + DEFAULT_ARMOURS[i] + type)->move(TO);
    }

    /* Add a whip if he needs one */
    if (whip)
    {
        clone_object(WHIP)->move(TO);
        add_cact("whip enemy");
        add_cact("whip enemy");
    }
    else
    {
        add_cact("@@do_knee");
        add_cact("@@do_kick");
    }

    /*
     * This order is important for we want them to wield their weapon before
     * they wear a possible shield.
     */
    command("wield all");
    command("wear all");
}

/*
 * Of each weapon are three types. A high-level version, a medium-level version
 * and a low-level version.
 */
string
base_to_type(int base)
{
    string type = LOW_ORC_STRING;

    if (base >= HIGH_ORC_LEVEL)
        type = HIGH_ORC_STRING;
    else if (base >= MEDIUM_ORC_LEVEL)
        type = MEDIUM_ORC_STRING;

    return type;
}

/*
 * Configurates the orc with a certain base. This base will be used to set
 * his stats, his skills and his alignment (and knight prestige).
 *
 * Base will be the average of the stats/skills.
 */
varargs void
make_the_orc(int base, int whip)
{
    if (!base)
    {
        base = 40 + random(80);
    }

    make_orc_looks(base);

    /*
     * The Steward of Gondor, Olorin, counciled me to lower the int and wis
     * of the orc. Its str, dex, con and dis are between 75% and 125% of
     * base. Its int and wis will be between 75% and 100%
     */
    set_base_stat(SS_STR, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_DEX, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_CON, (base * 3 / 4) + random(base / 2));
    set_base_stat(SS_WIS, (base * 3 / 4) + random(base / 4));
    set_base_stat(SS_INT, (base * 3 / 4) + random(base / 4));
    set_base_stat(SS_DIS, (base * 3 / 4) + random(base / 2));

    REFRESH; /* set mana, hp, fatigue */

    set_alignment(-(5 * base));
    knight_prestige = (5 * base);

    /*
     * His skills will be between 75% and 125% of base and his blind combat
     * is always 100.
     */
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_WEP_SWORD,    (base * 3 / 4) + random(base / 2));
    set_skill(SS_WEP_CLUB,     (base * 3 / 4) + random(base / 2));
    set_skill(SS_WEP_AXE,      (base * 3 / 4) + random(base / 2));
    set_skill(SS_PARRY,        (base * 3 / 4) + random(base / 2));
    set_skill(SS_DEFENCE,      (base * 3 / 4) + random(base / 2));
    set_skill(SS_AWARENESS,    (base * 3 / 4) + random(base / 2));
    set_skill(SS_UNARM_COMBAT, (base * 3 / 4) + random(base / 2));

    arm_me(base_to_type(base), whip);
}

/*
 * Add the speech and actions.
 */
void
add_act_cact()
{
    set_chat_time(10 + random(10));
    add_chat("Let's hurry!");
    add_chat("When are we gonna eat?");
    add_chat("Let's find some humans to molest!");
    add_chat("I don't like running in the sunlight!");
    add_chat("Attack on sight. You can ask questions later.");
    add_chat("Why are we always sent out on Patrol?");
    add_chat("News from high up: prisoners must be taken to Lugburz.");
    add_chat("Be wary! There is a large elf warrior on the run.");
    add_chat("Uruk drepa tuluk! Egur lug en vesall hai krimpatul!");
    add_chat("Onreinn hundur drepa!");

    set_cchat_time(5 + random(5));
    add_cchat("Finish it!");
    add_cchat("No prisoners, no witnesses!");
    add_cchat("Ash nazg gimba, burz goth thraka!");
    add_cchat("Rum marzgitul! Auga bukratul!");
    add_cchat("Kill this bastard!");
    add_cchat("Attack this intruder!");
    add_cchat("Die! You miserable rat!");
    add_cchat("Lets feed him to Shelob.");
    add_cchat("It this that elf warrior we were warned for?");

    set_act_time(10 + random(10));
    add_act("burp");
    add_act("hiss");
    add_act("grin");
    add_act("spit");

    set_cact_time(5 + random(5));
    add_cact("scream");
    add_cact("grin");
    add_cact("@@do_tackle");
}

/*
 * This will make the orc react to several triggers. Er... quite a lot of
 * triggers to be honest.
 */
void
add_triggers()
{
    trig_new("%w 'caresses' 'you.\n'", "react_trigger");
    trig_new("%w 'caresses' 'you' %s", "react_trigger");
    trig_new("%w 'congratulates' 'you.\n'", "react_trigger");
    trig_new("%w 'cuddles' 'you.\n'", "react_trigger");
    trig_new("%w 'cuddles' 'you' %s", "react_trigger");
    trig_new("%w 'sweeps' 'you' 'across' 'the' 'dance' 'floor.\n'",
        "react_trigger");
    trig_new("%w 'fondles' 'you.\n'", "react_trigger");
    trig_new("%w 'fondles' 'you' %s", "react_trigger");
    trig_new("%w 'gives' 'you' 'a' 'deep' 'and' 'passionate' %s",
        "react_trigger");
    trig_new("%w 'holds' 'you' 'close.\n'", "react_trigger");
    trig_new("%w 'hugs' 'you.\n'", "react_trigger");
    trig_new("%w 'hugs' 'you' %s", "react_trigger");
    trig_new("%w 'jumps' 'all' 'over' 'you.\n'", "react_trigger");
    trig_new("%w 'jumps' %w 'all' 'over' 'you.\n'", "react_trigger");
    trig_new("%w 'kicks' 'you.' %s", "react_trigger");
    trig_new("%w 'kicks' 'you' %s", "react_trigger");
    trig_new("%w 'kisses' 'you.\n'", "react_trigger");
    trig_new("%w 'kisses' 'you' %s", "react_trigger");
    trig_new("%w 'tries' 'to' 'knee' 'you,' 'without' 'much' 'effect.\n'",
        "react_trigger");
    trig_new("%w 'hits' 'you' 'with' %w 'knee' 'below' 'your' 'belt!\n'",
        "react_trigger"); 
    trig_new("%w 'licks' 'you.\n'", "react_trigger");
    trig_new("%w 'nibbles' 'on' 'your' %s", "react_trigger");
    trig_new("%w 'nudges' 'you.\n'", "react_trigger");
    trig_new("%w 'pats' 'you' %s", "react_trigger");
    trig_new("%w 'pokes' 'you' 'in' 'the' %s", "react_trigger");
    trig_new("%w 'pukes' 'all' 'over' 'you!\n'", "react_trigger");
    trig_new("%w 'ruffles' 'your' %s", "react_trigger");
    trig_new("%w 'scratches' 'you' 'at' 'your' %s", "react_trigger");
    trig_new("%w 'shakes' 'your' 'hand.\n'", "react_trigger");
    trig_new("%w 'slaps' 'you!\n'", "react_trigger");
    trig_new("%w 'snuggles' 'up' 'to' 'you.\n'", "react_trigger");
    trig_new("%w 'spanks' 'you.\n'", "react_trigger");
    trig_new("%w 'spanks' 'you' %s", "react_trigger");
    trig_new("%w 'spits' 'on' 'you!\n'", "react_trigger");
    trig_new("%w 'squeezes' 'you.\n'", "react_trigger");
    trig_new("%w 'squeezes' 'you' %s", "react_trigger");
    trig_new("%w 'tickles' 'you.\n'", "react_trigger");
    trig_new("%w 'tickles' 'you' %s", "react_trigger");
}

void
init_attack()
{
    set_alarm(1.0, 0.0, "slow_init_attack", TP);
}

void
slow_init_attack(object tp)
{
    /* wizards aren't attacked... */
    if (tp->query_wiz_level())
    {
        return;
    }

    /* NPC's neither */
    if ((tp->query_npc()) || (query_attack()))
    {
        return;
    }

    /* Goblins and generally bad people aren't attacked either */
    if ((tp->query_race() == "goblin") ||
        (tp->query_alignment() < MIN_ALIGNMENT_LEVEL))
    {
        return;
    }

    set_alarm(1.0, 0.0, "command", "shout Die, scum!");
    set_alarm(3.0, 0.0, "aggressive_attack", tp);
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;
    int found = 0;

    ::attacked_by(ob);

    arr = FILTER_LIVE(all_inventory(ENV(TO)));
    for (i = 0; i < sizeof(arr); i++)
    {
        if ((arr[i]->id("orc")) && (arr[i] != TO))
        {
            arr[i]->notify_ob_attacked_me(TO, ob);
            found = 1;
        }
    }

    if (found)
    {
        command("emote growls: Are you going to help me or what?");
    }
}

/*
 * Return to a trigger and attack.
 */
void
return_trigger(object obj)
{
    if (ENV(TO) != ENV(obj))
    {
        return;
    }

    FIX_EUID;

    command("kill " + obj->query_real_name());
    attacked_by(obj);
}

/*
 * React on some triggers, if you try to do something to a sleeping orc.
 * I haven't the faintest why this function should be declared int, but
 * Tricky did so in his alchemist, so there is probably a good reason to
 * do so.
 */
varargs int
react_trigger(string who, string foobar)
{
    object obj;

    if (stringp(who))
    {
        who = lower_case(who);

        obj = present(who, ENV(TO));
        set_alarm(1.0, 0.0, "return_trigger", obj);

        return 1;
    }

    return 0;
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
    {
        return;
    }

    set_alarm(5.0, 0.0, "help_friend", attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if ((!query_attack()) && (present(ob, environment())))
    {
        command("shout " + ONE_OF_LIST(ATTACKCRY));
        command("kill " + ob->query_real_name());
    }
}

void
do_knee()
{
    command("knee " + query_attack()->query_real_name());
}

void
do_kick()
{
    command("kick " + query_attack()->query_real_name());
}

void
do_tackle()
{
    command("tackle " + query_attack()->query_real_name());
}

/*
 * Solamnian knight prestige
 */
int
query_knight_prestige()
{
    return knight_prestige;
}
