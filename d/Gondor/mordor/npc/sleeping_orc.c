/*
 * /d/Gondor/mordor/npc/sleeping_orc.c
 *
 * This orc sleeps on the bunks in the tower at Cirith Ungol. He is slightly
 * modified from the standard or for he is asleep by default. Unlike other
 * orcs, this orc will be awake when you attack it.
 *
 * /Mercade, 4 October 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/npc/towerorc";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"

#define SLEEPING_ORC_NAME "_sleeping_towerorc_"
#define SLEEPING_ORC_ADJ  "sleeping"

/*
 * Global variables
 */
int orc_is_asleep;

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_pname("orcs");
    set_race_name("orc");
    set_adj(looks);

    add_name(SLEEPING_ORC_NAME);
    set_adj(SLEEPING_ORC_ADJ);

    set_long("@@long_description");
    set_short("@@short_description");
    set_pshort("@@pshort_description");

    add_prop(CONT_I_HEIGHT, 170 + random(20));
    add_prop(CONT_I_WEIGHT, 75000 + random(10000));
    add_prop(CONT_I_VOLUME, 70000 + random(20000));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 2);

    orc_is_asleep = 1;

    set_act_time(random(5));
    add_act("fart");
    add_act("groan dangerously");
    add_act("moan sleepily");
    add_act("shiver");
    add_act("snore");
    add_act("snore heavily");
    add_act("snore heavily");

    add_triggers();
}

/*
 * Some code to make the orc act like on.
 */
void
finish_the_orc()
{
    /* This should remove all previous (sleepy) add_acts of the orc */
    monster_act      = ({ });
    monster_act_left = ({ });

    add_act_cact();    

    set_aggressive(1);
}

/*
 * Get the long description of the orc.
 */
string
long_description()
{
    if (orc_is_asleep)
    {
        if (ENV(TO)->query_bunk())
        {
            return BSN("It is " + LANG_ADDART(query_race_name()) + " with " +
                "long arms and crooked legs. It is asleep on one of the " +
                "bunks on the ground. You think that the saying about " +
                "letting sleeping dogs lie is also valid for orcs and that " +
                "you should let it sleep.");
        }
        else
        {
            return BSN("This is " + LANG_ADDART(query_race_name()) + " with " +
                "long arms and crooked legs. It is asleep on the gound. You " +
                "think that the saying about letting sleeping dogs lie is " +
                "also valid for orcs and that you should let it sleep.");
        }
    }

    return BSN("This is " + LANG_ADDART(TO->short()) + " with long arms " +
        "and crooked legs. It looks mean and you do not want to mess with " +
        "it. " +
        (present("armour", TO) ?
            "On its armour you can see a crest painted: A red eye, meaning " +
            "that this " + query_race_name() + " is a member of the armies " +
            "of the dark Lord." :
            "To your astonishment you notice that the " + query_race_name() +
            " doesn't wear any armour at all."));
}

/*
 * Get the plural short description of the orcs
 */
string
pshort_description()
{
    if (orc_is_asleep)
    {
        if (ENV(TO)->query_bunk())
        {
            return "orcs sleeping on bunks";
        }
        else
        {
            return "orcs sleeping on the ground";
        }
    }

    return looks + " orcs";
}

/*
 * Get the short description of the orc
 */
string
short_description()
{
    if (orc_is_asleep)
    {
        if (ENV(TO)->query_bunk())
        {
            return "orc sleeping on a bunk";
        }
        else
        {
            return "orc sleeping on the ground";
        }
    }

    return looks + " orc";
}

/*
 * To add the adjective 'sleeping' if the orc is sleeping ;-)
 * Note that I redefined query_nonmet_name() in towerorc.c
 */
string
query_nonmet_name()
{
    if (orc_is_asleep)
    {
        return (SLEEPING_ORC_ADJ + " " + query_race_name());
    }

    return ::query_nonmet_name();
}

void
init_living()
{
    add_action("do_wake", "wake");
}

/*
 * Wake the orc up.
 */
void
wake_orc_up()
{
    orc_is_asleep = 0;

    remove_name(SLEEPING_ORC_NAME);
    remove_adj(SLEEPING_ORC_ADJ);

    command("wield all");
    command("wear all");

    finish_the_orc();
}

/*
 * Uruks don't sleep. In fact, I am too lazy to code sleeping stuff for both
 * orcs and uruks. *grin*
 */
void
make_orc_looks(int base)
{
    return;
}

/*
 * Make the orc unwield his stuff for he is asleep
 */
void
make_the_orc(int base, int whip)
{
    ::make_the_orc(base, whip);

    command("unwield all");
    command("remove all");
}

void
init_attack()
{
    if (orc_is_asleep)
    {
        return;
    }

    set_alarm(1.0, 0.0, &slow_init_attack(TP));
}

/*
 * Delay this fun if the orc sleeps.
 */
void
delayed_attacked_by(object ob)
{
    object *arr;
    int i;
    int found;

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
        command("emote growls: Are you going to do something or what?");
    }
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    if (!orc_is_asleep)
    {
        delayed_attacked_by(ob);
    }

    command("emote wakes up with a shock as it is attacked.");
    wake_orc_up();
    set_alarm(2.0, 0.0, "delayed_attacked_by", ob);
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

    if (orc_is_asleep)
    {
        command("emote wakes up from the noises of fighting.");
        wake_orc_up();
    }

    set_alarm(5.0, 0.0, "help_friend", attacker);
}

/*
 * Query whether the orc is sleeping or not.
 */
int
query_asleep()
{
    return orc_is_asleep;
}

/*
 * Wake up and attack.
 */
void
return_trigger(object obj)
{
    if (orc_is_asleep)
    {
        if (ENV(TO) == ENV(obj))
        {
            obj->catch_msg("The orc wakes up as you approach it.\n");
        }
        LTELL_ROOM(ENV(TO), obj, "The orc wakes up as ", " approaches it.",
            obj);

        wake_orc_up();
    }

    command("kill " + obj->query_real_name());
    delayed_attacked_by(obj);
}

/*
 * This is the code if you try to wake the orc. This is a very short and
 * rather ugly implementation that allows you to wake only one orc at a time.
 * Let a mortal complain about it before I make a change *grin*
 */
int
do_wake(string str)
{
    if (!orc_is_asleep)
    {
        NFN("The orc is not sleeping.");
        return 0;
    }

    return_trigger(TP);
    return 1;
}
