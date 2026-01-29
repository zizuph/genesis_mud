/*
 * /d/Gondor/morgul/tower/tower_0sw.c
 * The southwest room on the ground floor of the Morgul Tower
 *
 * Olorin, 10-jan-1994
 *
 * Modification log:
 * Olorin, 31-Oct-1995: Added thrones for the Lord of the Nazgul,
 *                      the nazgul, and the Lieutenant.
 * Morbeche, 29 Feb 2000:  Added a trapdoor to a random room in cellar.
 *                         added "mconsider" emote
 *                         Added Ugelplect's emote:  drum fingers on throne 
 * Stern, 20 Apr 2001: removed trap door, mescort, and mconsider.
 * Gorboth, 10 Sep 2013: Added the functions:
 *                       =============================================
 *                         public string  exa_shackles();
 *                         public int     check_shackled(object who);
 *                         public int     check_exit();
 *                         public int     safe_msg(object who);
 *                         public int     catch_all(string str);
 *                         public mixed   shackle_attack();
 *                         public int     do_shackle(string arg);
 *                         public int     do_unshackle(string arg);
 *                         public int     throat_slit(string arg);
 *                         public void    corpse_event();
 *                       =============================================
 *                       These improve on descriptions and general
 *                       atmosphere, along with giving a method for
 *                       the Nazgul to have complete control over the
 *                       fates of players who enter these premises (and
 *                       those players have been fully warned of what
 *                       it might mean to tread within!)
 * 
 */
#pragma strict_types

inherit "/d/Gondor/morgul/tower/tower.c";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <time.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

#define MORGUL_S_THRONE		"_morgul_s_throne"
#define LORD_THRONE		"_gLord_throne"
#define NAZGUL_THRONE		"_nazgul_throne"
#define STONE_CHAIR		"_gStone_chair"
#define NO_NAZGUL		8
#define MORGUL_LOWER_THRONEROOM "_morgul_lower_throneroom"
#define MORGUL_I_SHACKLED       "_morgul_i_shackled"
#define SHACKLE_LOG             "/d/Gondor/log/morgul_shackle"

#define HE(xxx)		(xxx)->query_pronoun()
#define HIS(xxx)	(xxx)->query_possessive()
#define HIM(xxx)  (xxx)->query_objective()

#define MY_COMPOSITE_LIVE(xxx, for)	COMPOSITE_WORDS((xxx)->query_art_name(for))

//	Prototypes
public string  exa_shackles();
public int     check_shackled(object who);
public int     check_exit();
public int     safe_msg(object who);
public int     catch_all(string str);
public mixed   shackle_attack();
public int     do_shackle(string arg);
public int     do_unshackle(string arg);
public int     throat_slit(string arg);
public void    corpse_event();
public int     do_name(string str);
public void    query_new_name(string name);
public int     do_drum();
public int     do_grip();
public int     do_appoint(string str);
public int     do_inspect(string str);
public int     do_promote(string str);
public int     do_recline(string str);
public int     do_release(string str);
//	Global variables.
static int     gSummon_alarm_id,
gSummon_step,
gNaming_seq_id,
gNaming_step,
click = 0,
trapdoor_alarm;

//	The thrones:	6 4 2 0 H 1 3 5 7
static object  gLord_throne = 0,
*gNazgul_thrones = ({}),
gStone_chair = 0;
static string  gNew_name,
gNew_name2;

void
create_morgul_tower_room()
{
    set_level(0);
    set_room_type("large hall");

    set_extra_long("You have entered none other than the audience chamber"
      + " of the Lord of the Nazgul, whose power is supreme and cannot"
      + " be fathomed within these halls. Two rows of mighty pillars"
      + " run southwest, ending astride a dais of many"
      + " steps where a canopy of blood-red stone looms above a high"
      + " throne. To each side, and three steps lower, four smaller"
      + " thrones crown the dais. A pile of shackles rests in one corner,"
      + " ominously implicating the potentials here.");

    add_item( ({ "pile", "corner", "pile in the corner",
                 "shackle", "shackles", "pile of shackles" }),
        exa_shackles);

    add_item(({"steps", "step", "dais", }), BSN(
	"The dais at the end of the hall rises high above the floor. A broad "
	+ "set of steps is leading up to the high throne on the dais. The "
	+ "smaller thrones on both sides of the high throne are set three steps "
	+ "lower. At the foot of the dais, upon the lowest step, there is a "
	+ "stone chair."));

    add_item(({"throne", "high throne", }), "@@exa_high_throne@@");
    add_item(({"thrones", "smaller thrones", }), "@@exa_thrones@@");
    add_item(({"chair", "stone chair", }), "@@exa_stone_chair@@");

    add_item( ({ "canopy", "red stone", "red canopy",
                 "blood-red stone", "blood-red canopy",
                 "canopy of blood-red stone" }), BSN(
	"A canopy of red stone rises over the High Throne of the King of "
	+ "Minas Morgul. It is shaped like a devouring flame. Set into the "
	+ "center of the canopy is a threatening Red Eye."));

    add_item( ({ "red eye", "eye", "threatening eye",
                 "threatening red eye" }), BSN(
	"Hewn from stone, the Red Eye set into the canopy over the High "
	+ "Throne seems to be alive and to pierce every soul in this hall "
	+ "with its terrible glance."));

    add_item( ({ "hall", "here", "area", "chamber",
                 "audience chamber", }), BSN(
	"The halls extends to the northeast as far as you can see by " +
	"the shine of your light source. Two rows of mighty pillars " +
	"divide the hall into three parts. Right now you are in the " +
	"central part between the two rows. Walking through the pillars " +
	"to the north, you can reach the northwestern part, walking east " +
	"the southeastern part."));

    add_item(({"columns", "pillar", "pillars", "row", "rows",
	"row of pillars", "rows of pillars"}), BSN(
	"The two rows of pillars run diagonally across the large hall from " +
	"the northeast to the southwest. They divide the hall into three " +
	"parts. Each of the pillars is several yards thick, completely void " +
	"of any decoration, and hewn from black marble."));

    add_item(({"bas-reliefs", "bas-relief", "reliefs", "relief", }),
      "Examine the bas-relief on which of the nine thrones?\n");

    add_no_roof();
    add_floor();
    add_walls();

    add_exit(TOWER_DIR  + "tower_0c",  "northeast", check_exit, 1);
    add_exit(TOWER_DIR  + "tower_0w",  "north",     check_exit, 1);
    add_exit(TOWER_DIR  + "tower_0s",  "east",      check_exit, 1);

    clone_object("/d/Gondor/clubs/anghoth/obj/anghoth_admin")->move(TO, 1);
    add_prop(MORGUL_LOWER_THRONEROOM, 1);
    add_prop(ROOM_M_NO_ATTACK, "@@shackle_attack@@");
}


/*
 * Function name:        exa_shackles
 * Description  :        provide a state-dependent description of the
 *                       shackle pile
 * Returns      :        string - the description
 */
public string
exa_shackles()
{
    if (!IS_MEMBER(this_player()))
    {
        return "A pile of thick iron shackles rests in one corner of"
          + " this chamber. They look cruel and strong, easily capable"
          + " of restraining any who might be unfortunate enough to"
          + " find themselves subject to their use.\n";
    }

    if (!this_player()->query_nazgul())
    {
        return "Ah, the shackles ... such marvelous tools! You gaze at them"
          + " fondly, hoping for an opportunity soon to see them put to"
          + " use against the wretched fools of the West by your dark"
          + " masters.\n";
    }

    return "These shackles are enchanted by the power of the Dark Lord"
      + " to respond to your needs here. As one of the high servants of"
      + " the Tower, you may use the following commands:\n\n\t"
      + "<shackle>    - imprison anyone of your choosing\n\t"
      + "<unshackle>  - release someone from being shackled\n\t"
      + "<throatslit> - slit the throat of someone who is shackled\n";
} /* exa_shackles */


/* 
 * Function name:        check_shackled
 * Description  :        See if the player has been shackled, and thus
 *                       is unable to move/quit/etc.
 * Arguments    :        object who - the player in question
 * Returns      :        int 1/0 - depending on state
 */
public int
check_shackled(object who)
{
    return this_player()->query_prop(MORGUL_I_SHACKLED);
} /* check_shackled */


/*
 * Function name:        check_exit
 * Description  :        See what happens when the player tries to leave.
 * Returns      :        int 1 - cannot leave, 0 - allow it
 */
public int
check_exit()
{
    if (check_shackled(this_player()))
    {
        write("You strain against your shackles, but are held fast!\n");
        tell_room(this_object(), QCTNAME(this_player())
          + " strains against " + this_player()->query_possessive()
          + " shackles, but is unable to escape.\n", this_player());

        return 1;
    }

    set_alarm(0.5, 0.0, &safe_msg(this_player()));
    return 0;
} /* check_exit */


/*
 * Function name:    safe_msg
 * Description  :    Illustrate to the player and onlookers how relieved
 *                   they must feel having escaped the throne room.
 * Arguments    :    object who - the player
 */
public void
safe_msg(object who)
{
    if (IS_MEMBER(who))
    {
        return;
    }

    if (environment(who)->query_prop(MORGUL_LOWER_THRONEROOM))
    {
        return;
    }

    write(one_of_list( ({
        "Your heartbeat steadies, having removed yourself from the perils"
      + " of that dreadful throneroom.\n",
        "Free of the perils of the throneroom, you feel the blood"
      + " returning to your face.\n",
        "It feels very good to be out of that sinister throneroom.\n",
        "",
        "",
        "" }) ) );

    who->command(one_of_list( ({
        "$sigh nerv",
        "$lick nerv",
        "$peer uncomf",
        "",
        "",
        "" }) ) );
} /* safe_msg */


/*
 * Function name:    catch_all
 * Description  :    if the player is shackled, we make it impossible
 *                   for them to escape
 * Arguments    :    string str - what the player typed
 * Returns      :    int 1 - catch it, 0 - let it through
 */
public int 
catch_all(string str)
{
    string  vb = query_verb();

    if (!this_player()->query_prop(MORGUL_I_SHACKLED))
    { 
        return 0;
    }
    
    switch (vb)
    {
    case "n":
    case "nw":
    case "w":
    case "sw":
    case "s":
    case "se":
    case "e":
    case "ne":
    case "u":
    case "d":
    case "north":
    case "northeast":
    case "northwest":
    case "southwest":
    case "southeast":
    case "west":
    case "up":
    case "down":
    case "south":
    case "east":
    case "say":
    case "shout":
    case "scream":
    case "ask":
    case "whisper":
    case "look":
    case "l":
    case "cry":
    case "wail":
    case "sob":
    case "weep":
    case "sniff":
        return 0;
        break;
    case "commune":
        write("Nope. You are beyond the help of the immortals"
          + " now, subject entirely to the whims of your captor.\n");
        return 1;
        break;
    case "quit":
        write("You cannot escape, even in so cowardly a fashion!\n");
        return 1;
        break;
    default:
        write("Hopeless ... it is all hopeless ... your will to"
          + " even attempt most things now is completely sapped. If"
          + " only the Nazgul would show you mercy ... You do feel"
          + " you still have powers of speech if there is anything"
          + " you wished to <say> to your captors.\n");
        return 1;
        break;
    }
} /* catch_all */


/*
 * Function name:        shackle_attack
 * Desctription :        see if the player can try to perform an
 *                       attack here. If shackled, prevent it.
 * Returns      :        mixed - 0, allow it
 *                       string - the failure message
 */
public mixed
shackle_attack()
{
    if (this_player()->query_prop(MORGUL_I_SHACKLED))
    {
        return "How could you possibly do that while held fast in these"
          + " shackles?\n";
    }

    return 0;
} /* shackle_attack */


/*
 * Function name:        do_shackle
 * Description  :        allow a Nazgul to shackle someone
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_shackle(string arg)
{
    int     actor_level = this_player()->query_nazgul();
    int     victim_level;
    object *ob;
    object *weapons;
    object  tp;
    string  where;

    if (!actor_level)
    {
        return 0;
    }

    if (this_player()->query_prop(MORGUL_I_SHACKLED))
    {
        notify_fail("It is too late for that! You have been placed"
          + " in shackles yourself! Clearly, you have displeased"
          + " the Lord of the Nazgul, perhaps for the last time!\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Whom do you wish to shackle?\n");
        return 0;
    }

    if (!parse_command(arg, environment(this_player()),
        "%i", ob))
    {
        if (arg == "me" || arg == "myself" ||
            arg == this_player()->query_real_name())
        {
            notify_fail("Shackle yourself? Do not jest in the presence of"
              + " the Dark Lord, wraith!\n");
            return 0;
        }

        notify_fail("Whom do you wish to shackle?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);

    if (!sizeof(ob) || arg == "me" || arg == "myself" ||
            arg == this_player()->query_real_name())
    {
        notify_fail("Shackle yourself? Do not jest in the presence of"
          + " the Dark Lord, wraith!\n");
        return 0;
    }

    if (!living(ob[0]))
    {
        notify_fail("Shackle the " + ob[0]->short()
          + "? Do not be absurd!\n");
        return 0;
    }

    if (ob[0]->query_wiz_level())
    {
        notify_fail("To try to shackle a wizard would be folly,"
          + " indeed.\n");
        return 0;
    }

    victim_level = ob[0]->query_nazgul();

    if (victim_level >= actor_level)
    {
        if (victim_level > actor_level)
        {
            notify_fail("You cannot shackle the Lord of the Nazgul! It"
              + " is well that the Dark Lord does not sense your"
              + " miserable thoughts, wretched one!\n");
            return 0;
        }

        notify_fail("You cannot shackle a wraith of value equal to"
          + " your own! Only the Lord Nazgul has such authority here.\n");
        return 0;
    }

    if (ob[0]->query_prop(MORGUL_I_SHACKLED))
    {
        notify_fail("Shackles have already been placed on this"
          + " wretch!\n");
        return 0;
    }

    tp = ob[0];

    if (living(tp) && strlen(where = tp->query_prop(MORGUL_S_THRONE)))
    {
	switch (where)
	{
	case NAZGUL_THRONE:
	    write("You stumble from your throne to the base of the dais!\n");
	    say(QCTNAME(tp)+" stumbles from "+HIS(tp)+" throne"
              + " to the base of the dais!\n",tp);
	    gNazgul_thrones -= ({ tp });
	    break;
	case STONE_CHAIR:
	    write("You topple from the stone chair!\n");
	    say(QCTNAME(tp)+" topples from the stone chair!\n",tp);
	    gStone_chair = 0;
	    break;
	default:
	    break;
	}
	tp->remove_prop(LIVE_S_EXTRA_SHORT);
	tp->remove_prop(MORGUL_S_THRONE);
	tp->remove_subloc(MORGUL_S_THRONE);
	tp->set_no_show_composite(0);
    }

    write("You thrust a your hand toward " 
      + ob[0]->query_the_name(this_player())
      + " with a grisley clutching motion. Instantly, shackles"
      + " rise from the pile in the corner and spring toward "
      + ob[0]->query_objective() + ", catching each wrist and"
      + " anchoring " + ob[0]->query_possessive() + " fast"
      + " to the wall!\n");
    ob[0]->catch_tell(this_player()->query_The_name(ob[0]) + " thrusts"
      + " a hand toward you with a grisley clutching motion. From"
      + " out of nowhere, shackles spring toward you, catching each"
      + " of your wrists and pinning you against the wall, where"
      + " you are anchored in place!\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " thrusts a hand toward " + QCTNAME(ob[0]) + " with a grisley"
      + " clutching motion. Instantly, shackles rise from the pile"
      + " in the corner and spring toward "
      + ob[0]->query_objective() + ", catching each"
      + " of " + ob[0]->query_possessive() + " wrists and pinning "
      + ob[0]->query_objective() + " in place, anchored to the wall!\n",
        ({ this_player(), ob[0] }));

    weapons = ob[0]->query_weapon(-1);

    foreach(object weapon: weapons)
    {
        ob[0]->command("$drop " + OB_NAME(weapon));
    }

    ob[0]->add_prop(MORGUL_I_SHACKLED, 1);
    ob[0]->add_prop(LIVE_S_EXTRA_SHORT, " (shackled to the wall)");

    write_file(SHACKLE_LOG,
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " shackled " + capitalize(ob[0]->query_real_name()) + ".\n");

    return 1;
} /* do_shackle */


/*
 * Function name:        do_unshackle
 * Description  :        allow a Nazgul to unshackle someone
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_unshackle(string arg)
{
    int     actor_level = this_player()->query_nazgul();
    int     victim_level;
    object *ob;

    if (!actor_level)
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Whom do you wish to shackle?\n");
        return 0;
    }

    if (this_player()->query_prop(MORGUL_I_SHACKLED))
    {
        notify_fail("The will of the Lord of the Nazgul is absolute"
          + " here, even for you. You cannot escape!\n");
        return 0;
    }

    if (!parse_command(arg, environment(this_player()),
        "%i", ob))
    {
        if (arg == "me" || arg == "myself" ||
            arg == this_player()->query_real_name())
        {
            notify_fail("Unshackle yourself? Awaken from your sleeping"
              + " state, Nazgul!\n");
            return 0;
        }

        notify_fail("Whom do you wish to unshackle?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);

    if (!sizeof(ob) || arg == "me" || arg == "myself" ||
            arg == this_player()->query_real_name())
    {
        notify_fail("Unshackle yourself? Awaken from your sleeping"
          + " state, Nazgul!\n");
        return 0;
    }

    if (!living(ob[0]))
    {
        notify_fail("Unshackle the " + ob[0]->short()
          + "? Foolishness!\n");
        return 0;
    }

    if (!ob[0]->query_prop(MORGUL_I_SHACKLED))
    {
        notify_fail("This one has not been shackled.\n");
        return 0;
    }

    victim_level = ob[0]->query_nazgul();

    if (victim_level == actor_level)
    {
        notify_fail("To do so would be to violate the authority of"
          + " the Lord Nazgul. You can do no such thing here!\n");
        return 0;
    }

    write("You gesture casually toward " 
      + ob[0]->query_the_name(this_player())
      + " with a brief wave of your hand. Instantly, the shackles"
      + " fall from " + ob[0]->query_possessive() + " wrists and"
      + " soar back to the pile in the corner.\n");
    ob[0]->catch_tell(this_player()->query_The_name(ob[0])
      + " gestures casually"
      + " toward you with a brief wave of "
      + this_player()->query_possessive() + " hand. Instantly, the"
      + " shackles fall from your agonized wrists and soar back"
      + " to a pile in the corner.\n");
    tell_room(this_object(), QCTNAME(this_player())
      + " gestures casually toward " + QCTNAME(ob[0]) + " with a"
      + " brief wave of " + this_player()->query_possessive()
      + " hand. Instantly, the shackles fall from the latter's"
      + " wrists and soar back to a pile in the corner.\n",
        ({ this_player(), ob[0] }));

    ob[0]->remove_prop(MORGUL_I_SHACKLED);
    ob[0]->remove_prop(LIVE_S_EXTRA_SHORT);

    write_file(SHACKLE_LOG,
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " released " + capitalize(ob[0]->query_real_name()) + ".\n");

    return 1;
} /* do_unshackle */


/*
 * Function name:        throat_slit
 * Description  :        Allow the Nazgul to execute their victims
 *                       if they so choose in this room
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
throat_slit(string arg)
{
    int     actor_level = this_player()->query_nazgul();
    int     victim_level;
    object *ob;
    object *weapons;
    mixed   slit_wep = 0;
    object  tp;
    string  where;

    if (!actor_level)
    {
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Whose throat do you wish to slit?\n");
        return 0;
    }

    if (this_player()->query_prop(MORGUL_I_SHACKLED))
    {
        notify_fail("The only throat likely to be slit here is your"
          + " own!\n");
        return 0;
    }

    if (!parse_command(arg, environment(this_player()),
        "%i", ob))
    {
        if (arg == "me" || arg == "myself" ||
            arg == this_player()->query_real_name())
        {
            notify_fail("A Nazgul does not commit suicide. Find"
              + " yourself a proper subject!\n");
            return 0;
        }

        notify_fail("Whose throat do you wish to slit?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);

    if (!sizeof(ob) || arg == "me" || arg == "myself" ||
            arg == this_player()->query_real_name())
    {
        notify_fail("A Nazgul does not commit suicide. Find"
          + " yourself a proper subject!\n");
        return 0;
    }

    if (!living(ob[0]))
    {
        notify_fail("Slit the throat of " + ob[0]->short()
          + "? Your mind is clearly fogged, Nazgul!\n");
        return 0;
    }

    if (!ob[0]->query_prop(MORGUL_I_SHACKLED))
    {
        notify_fail("First, you must <shackle> your victim.\n");
        return 0;
    }

    weapons = this_player()->query_weapon(-1);

    foreach(object weapon: weapons)
    {
        if (weapon->query_wt() == W_KNIFE ||
            weapon->query_wt() == W_SWORD)
        {
            slit_wep = weapon;
        }
    }

    if (!slit_wep)
    {
        notify_fail("You will first need to wield a blade.\n");
        return 0;
    }

    tp = this_player();

    if (living(tp) && strlen(where = tp->query_prop(MORGUL_S_THRONE)))
    {
	switch (where)
	{
	case LORD_THRONE:
	    write("You rise from your High Throne and descend from the dais.\n");
	    say(QCTNAME(tp)+" rises from "+HIS(tp)+" High Throne and descends from the dais.\n",tp);
	    gLord_throne = 0;
	    break;
	case NAZGUL_THRONE:
	    write("You rise from your throne and descend from the dais.\n");
	    say(QCTNAME(tp)+" rises from "+HIS(tp)+" throne and descends from the dais.\n",tp);
	    gNazgul_thrones -= ({ tp });
	    break;
	case STONE_CHAIR:
	    write("You rise from the stone chair.\n");
	    say(QCTNAME(tp)+" rises from the stone chair.\n",tp);
	    gStone_chair = 0;
	    break;
	default:
	    break;
	}
	tp->remove_prop(LIVE_S_EXTRA_SHORT);
	tp->remove_prop(MORGUL_S_THRONE);
	tp->remove_subloc(MORGUL_S_THRONE);
	tp->set_no_show_composite(0);
    }

    write("\nApproaching " + ob[0]->query_the_name(this_player())
      + " with remorseless intent, you force back "
      + ob[0]->query_possessive() + " head and, with one swift motion,"
      + " slit the soft flesh of " + ob[0]->query_possessive()
      + " throat with your " + slit_wep->short() + ".\n\n");
    ob[0]->catch_tell("\n" + this_player()->query_The_name(ob[0])
      + " approaches you with a remorseless stare, forces back your"
      + " head and, with one swift motion slits your throat"
      + " with " + tp->query_possessive() + " "
      + slit_wep->short() + "! Your vision fades to black ...\n\n");
    tell_room(this_object(), "\n" + QCTNAME(this_player())
      + " approaches " + QCTNAME(ob[0]) + " with a"
      + " remorseless stare, forces back " + ob[0]->query_possessive()
      + " head and, with one swift motion, slits "
      + ob[0]->query_possessive() + " throat with "
      + tp->query_possessive() + " " + slit_wep->short() + ".\n\n",
        ({ this_player(), ob[0] }));

    ob[0]->remove_prop(MORGUL_I_SHACKLED);

    ob[0]->heal_hp(-(ob[0]->query_hp()));
    ob[0]->do_die(tp);

    set_alarm(5.0, 0.0, &corpse_event());

    write_file(SHACKLE_LOG,
        TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
      + ctime(time())[11..18] + ") "
      + capitalize(this_player()->query_real_name()) 
      + " killed " + capitalize(ob[0]->query_real_name()) + "!\n");

    return 1;
} /* throat_slit */


/*
 * Function name:        corpse_event
 * Description  :        so someone got their throat slit. Lets make
 *                       a bit of a show following the event.
 */
public void
corpse_event()
{
    tell_room(this_object(),
        "\nAs if sensing that their prey has been dealt with, the shackles"
      + " open, pitching the corpse headlong onto the floor of the"
      + " chamber where blood runs freely toward the dais. The shackles"
      + " soar once again across the chamber and land back in the pile"
      + " from whence they came.\n\n");
} /* corpse_event */


int
do_sit(string str)
{
    int     level,
    size;
    string  where,
    where_old;
    object  tp = TP;

    if (!strlen(str))
    {
	NFN("Sit where?");
	return 0;
    }

    str = LOW(str);

    if (parse_command(str, ({ }), " [down] [on] [my] [the] 'throne' "))
	where = NAZGUL_THRONE;
    else if (parse_command(str, ({ }), " [down] [on] [my] [the] 'high' 'throne' "))
	where = LORD_THRONE;
    else if (parse_command(str, ({ }), " [down] [on] [my] [the] [stone] 'chair' "))
	where = STONE_CHAIR;
    else
    {
	NFN("Sit down on one of the thrones or on the stone chair?");
	return 0;
    }

    if (stringp(where_old = tp->query_prop(MORGUL_S_THRONE)))
    {
	switch (where_old)
	{
	case LORD_THRONE:
	    NFN("But you are already sitting on the High Throne!");
	    return 0;
	case NAZGUL_THRONE:
	    NFN("But you are already sitting on one of the thrones!");
	    return 0;
	case STONE_CHAIR:
	    NFN("But you are already sitting on the stone chair!");
	    return 0;
	}
    }

    level = tp->query_nazgul();

    if (!level) level = -1;
    
    // stone chair for the Lt
    if (IS_LIEUTENANT(tp)) level = 0;

    switch(level)
    {
    case 2:
	if ((where != NAZGUL_THRONE) && (where != LORD_THRONE))
	{
	    NFN("Why would you wish to sit down anywhere but on your High Throne?");
	    return 0;
	}
	if (objectp(gLord_throne))
	{
	    if (!present(gLord_throne, TO) ||
	      (gLord_throne->query_prop(MORGUL_S_THRONE) != LORD_THRONE))
		gLord_throne = 0;
	    else
	    {
		NFN(gLord_throne->query_The_name(TP)
		  + " is already sitting on your throne!");
		return 0;
	    }
	}
	write("You walk up the steps onto the dais and sit down on your throne.\n");
	say(QCTNAME(tp) + " walks up the steps onto the dais and sits down on "
	  + HIS(tp)+" High Throne.\n", tp);
	gLord_throne = tp;
	tp->add_prop(MORGUL_S_THRONE, LORD_THRONE);
	tp->add_prop(LIVE_S_EXTRA_SHORT,", sitting on "+HIS(tp)+" High Throne upon the dais");
	tp->add_subloc(MORGUL_S_THRONE, TO);
	tp->set_no_show_composite(1);
	break;
    case 1:
	if (where == LORD_THRONE)
	{
	    write("As you lower yourself onto the High Throne of the King, you "
	      + "feel the gaze of the Red Eye falling heavily upon you, and you "
	      + "quickly rise again.\n");
	    say(QCTNAME(tp) + " tries to sit on the High Throne, but " + HE(tp)
	      + " quickly rises again, trembling with fear.\n");
	    return 1;
	}
	else if (where != NAZGUL_THRONE)
	{
	    NFN("Why would you wish to sit down anywhere but on your throne?");
	    return 0;
	}
	gNazgul_thrones &= all_inventory(TO);
	gNazgul_thrones -= ({ 0 });
	if ((size = sizeof(gNazgul_thrones)) >= NO_NAZGUL)
	{
	    NFN(MY_COMPOSITE_LIVE(gNazgul_thrones, tp) + " are sitting on the thrones!");
	    return 0;
	}
	write("You walk up the steps onto the dais and sit down on one "
	  + "of the smaller thrones.\n");
	say(QCTNAME(tp) + " walks up the steps onto the dais and sits "
	  + "down on one of the smaller thrones.\n", tp);
	gNazgul_thrones += ({ tp });
	tp->add_prop(MORGUL_S_THRONE, NAZGUL_THRONE);
	//      tp->add_prop(LIVE_S_EXTRA_SHORT,", sitting on a throne");
	tp->add_subloc(MORGUL_S_THRONE, TO);
	tp->set_no_show_composite(1);
	break;
    case 0:
	if (where != STONE_CHAIR)
	{
	    write("As you start to climb up the steps to sit down on one of "
	      + "the thrones, you feel the gaze of the Red Eye falling heavily "
	      + "upon you, and you quickly descend again.\n");
	    say(QCTNAME(tp) + " starts to climb up the steps leading up to the "
	      + "nine thrones set unto the dais, but trembling with fear, "
	      + HE(tp) + " turns and descends again.\n");
	    return 1;
	}
	if (objectp(gStone_chair))
	{
	    if (!present(gStone_chair, TO) ||
	      (gStone_chair->query_prop(MORGUL_S_THRONE) != STONE_CHAIR))
		gStone_chair = 0;
	    else
	    {
		NFN(QCTNAME(gStone_chair) + " is already sitting on the stone chair!");
		return 0;
	    }
	}
	write("You sit down on the stone chair.\n");
	say(QCTNAME(tp) + " sits down on the stone chair.\n", tp);
	gStone_chair = tp;
	tp->add_prop(MORGUL_S_THRONE, STONE_CHAIR);
	tp->add_prop(LIVE_S_EXTRA_SHORT,", sitting on the stone chair at the foot of the dais");
	tp->add_subloc(MORGUL_S_THRONE, TO);
	tp->set_no_show_composite(1);
	break;
    case -1:
    default:
	write("As you approach the dais to sit down on one of the thrones, "
	  + "you feel the gaze of the Red Eye falling heavily upon you, and "
	  + "you stop in your tracks.\n");
	say(QCTNAME(tp) + " approaches the dais, but suddenly stops, "
	  + "trembling with fear.\n");
	break;
    }
    return 1;
}

int
do_rise(string str)
{
    object  tp = TP;
    string  vb = query_verb(),
    where = tp->query_prop(MORGUL_S_THRONE);

    if (vb == "stand" && str != "up")
    {
	NFN(CAP(vb)+" what? Up?");
	return 0;
    }

    if (!strlen(tp->query_prop(MORGUL_S_THRONE)))
    {
	NFN("But you are not sitting on one of the thrones!");
	return 0;
    }

    switch (where)
    {
    case LORD_THRONE:
	write("You rise from your High Throne and descend from the dais.\n");
	say(QCTNAME(tp)+" rises from "+HIS(tp)
	  + " High Throne and descends from the dais.\n",tp);
	gLord_throne = 0;
	break;
    case NAZGUL_THRONE:
	write("You rise from your throne and descend from the dais.\n");
	say(QCTNAME(tp)+" rises from "+HIS(tp)
	  + " throne and descends from the dais.\n",tp);
	gNazgul_thrones -= ({ tp });
	break;
    case STONE_CHAIR:
	write("You rise from the stone chair.\n");
	say(QCTNAME(tp)+" rises from the stone chair.\n",tp);
	gStone_chair = 0;
	break;
    default:
	break;
    }
    tp->remove_prop(LIVE_S_EXTRA_SHORT);
    tp->remove_prop(MORGUL_S_THRONE);
    tp->remove_subloc(MORGUL_S_THRONE);
    tp->set_no_show_composite(0);
    return 1;
}

void
leave_inv(object ob, object to)
{
    string  where;

    ::leave_inv(ob, to);

    if (!objectp(ob))
	return;

    if (living(ob) && strlen(where = ob->query_prop(MORGUL_S_THRONE)))
    {
	switch (where)
	{
	case LORD_THRONE:
	    write("You rise from your High Throne and descend from the dais.\n");
	    say(QCTNAME(ob)+" rises from "+HIS(ob)+" High Throne and descends from the dais.\n",ob);
	    gLord_throne = 0;
	    break;
	case NAZGUL_THRONE:
	    write("You rise from your throne and descend from the dais.\n");
	    say(QCTNAME(ob)+" rises from "+HIS(ob)+" throne and descends from the dais.\n",ob);
	    gNazgul_thrones -= ({ ob });
	    break;
	case STONE_CHAIR:
	    write("You rise from the stone chair.\n");
	    say(QCTNAME(ob)+" rises from the stone chair.\n",ob);
	    gStone_chair = 0;
	    break;
	default:
	    break;
	}
	ob->remove_prop(LIVE_S_EXTRA_SHORT);
	ob->remove_prop(MORGUL_S_THRONE);
	ob->remove_subloc(MORGUL_S_THRONE);
	ob->set_no_show_composite(0);
    }
}

public int
do_examine(string str)
{
    int     n_throne,	// nazguls: 0-7, high: 8
    occ_thrones;
    string  vb = query_verb(),
    dummy,
    number,
    who,
    desc;

    if (!strlen(str))
	return 0;

    str = LOW(str);

    if (vb == "l" || vb == "look")
    {
	if (sscanf(str, "at %s", dummy) != 1)
	    return 0;
	str = dummy;
	vb = "look at";
    }

    if (vb == "exa")
	vb = "examine";

    if (parse_command(str, ({}),
	" [the] 'bas-relief' / 'relief' 'on' [the] [back] [of] [the] 'throne' "))
    {
	number = "high";
	n_throne = NO_NAZGUL + 1;
    }
    else if (!parse_command(str, ({}),
	" [the] 'bas-relief' / 'relief' 'on' [the] [back] [of] [the] %s 'throne' ",
	number))
    {
	if (!parse_command(str, ({ }),
	    " [the] %s 'bas-relief' / 'relief' ", number))
	    return 0;
    }

    if (!n_throne)
    {
	n_throne = LANG_ORDW(number);
	if (n_throne > NO_NAZGUL)
	{
	    write("There are only eight thrones for the nazgul and the High Throne "
	      + "of the King of Minas Morgul here.\n");
	    return 1;
	}
	if (!n_throne)
	{
	    if (number == "high")
		n_throne = NO_NAZGUL + 1;
	    else
	    {
		write(CAP(vb) + " the bas-relief on which of the nine thrones?\n");
		return 1;
	    }
	}
    }

    //  write("DEBUG: "+number+" = "+n_throne+"!\n");

    if (n_throne <= NO_NAZGUL)
	occ_thrones = sizeof(((gNazgul_thrones & all_inventory(TO)) - ({ 0 })));

    if (n_throne <= occ_thrones)
    {
	if (TP == gNazgul_thrones[n_throne-1])
	    who = "you are";
	else
	    who = gNazgul_thrones[n_throne-1]->query_the_name(TP) + " is";
	write("You cannot "+vb+" the bas-relief on the "+number+" throne, "
	  + "as "+who+" sitting on that throne!\n");
	return 1;
    }

    if ((n_throne == (NO_NAZGUL + 1)) && objectp(gLord_throne))
    {
	if (TP == gLord_throne)
	    who = "you are";
	else
	    who = gLord_throne->query_the_name(TP) + " is";
	write("You cannot "+vb+" the bas-relief on the High Throne, as "
	  + who + " sitting on that throne!\n");
	return 1;
    }

    switch (n_throne)
    {
    case 9:	// High Throne!
	desc = "The bas-relief on the back of the High Throne shows this "
	+ "very hall with the Nine presiding on their thrones over "
	+ "the assembly of a victorious army, laden with the spoils "
	+ "of war. Directly in front of the dais is depicted a group "
	+ "of creatures clothed in black robes who are torturing a "
	+ "captive according to the commands of the ringwraiths. A "
	+ "fake crown reveals the captive as Earnur, last King of Gondor.";
	break;
    case 8:
	desc = "The bas-relief on the throne that is farthest from the High Throne "
	+ "on the right side of the dais shows some strange and mysterious "
	+ "ornaments.";
	break;
    case 7:
	desc = "The bas-relief on the throne that is farthest from the High Throne "
	+ "on the left side of the dais shows some strange and mysterious "
	+ "ornaments.";
	break;
    case 6:
	desc = "The bas-relief on the throne that is the third from the High Throne "
	+ "on the right side of the dais shows some strange and mysterious "
	+ "ornaments.";
	break;
    case 5:
	desc = "The bas-relief on the throne that is the third from the High Throne "
	+ "on the left side of the dais shows some strange and mysterious "
	+ "ornaments.";
	break;
    case 4:
	desc = "The bas-relief on the throne that is the second from the High Throne "
	+ "on the right side of the dais shows some strange and mysterious "
	+ "ornaments.";
	break;
    case 3:
	desc = "The bas-relief on the throne that is the second from the High Throne "
	+ "on the left side of the dais shows some strange and mysterious "
	+ "ornaments.";
	break;
    case 2:
	desc = "The bas-relief on the throne that is closest to the High Throne "
	+ "on the right side of the dais shows the ruins of Eregion where "
	+ "Celebrimbor first rebelled against the Dark Lord and later was "
	+ "slain in punishment, together with all of his people.";
	break;
    case 1:
	desc = "The bas-relief on the throne that is closest to the High Throne "
	+ "on the left side of the dais shows Glaurung, Father of Dragons, "
	+ "in the Nirnaeth Arnoediad. Numerous scorched bodies "
	+ "of Noldor and men are lying on the ground before him, and "
	+ "even more of his enemies are fleeing in terror.";
	break;
    case 0:
    default:
	write("There are only eight thrones for the nazgul and the High Throne "
	  + "of the King of Minas Morgul here.\n");
	break;
    }
    write(BSN(desc));
    return 1;
}


public void
init()
{
    ::init();


    add_action(do_examine, "exa", 1);
    add_action(do_examine, "l");
    add_action(do_examine, "look");

    /* Commands */
    add_action(do_appoint,   "appoint");
    add_action(do_name,      "name");
    add_action(do_name,      "rakasul");
    add_action(do_release,   "release");
    add_action(do_shackle,   "shackle");
    add_action(do_unshackle, "unshackle");
    add_action(throat_slit,  "throatslit");
    add_action(do_promote,   "promote");
    add_action(catch_all, "", 1);

    /* Emotions */
    add_action(do_sit,     "sit");
    add_action(do_rise,    "stand");
    add_action(do_rise,    "rise");
    add_action(do_inspect, "inspect");
    add_action(do_drum,    "mdrum");
    add_action(do_grip,    "mgrip");
    add_action(do_recline, "recline");
}

public string
exa_high_throne()
{
    string  desc = 
    "Under a canopy of stone red as blood stands the High Throne of the "
    + "King of Minas Morgul. To both sides of the High Throne are four "
    + "smaller thrones for the other ringwraiths. All thrones are hewn "
    + "from black marble which seems to swallow all light.",
    name;

    if (objectp(gLord_throne) && present(gLord_throne, TO))
    {
	if (TP == gLord_throne)
	    name = "You are";
	else if (TP->query_met(gLord_throne))
	    name = gLord_throne->query_name() + ", "
	    + gLord_throne->query_morgul_title() + ", is";
	else
	    name = CAP(LANG_ADDART(gLord_throne->query_nonmet_name())) + " is";
	desc += " " + name + " sitting on the High Throne.";
    }
    else
	desc += " On the back of the High Throne is a bas-relief.";

    return BSN(desc);
}

public string
exa_thrones()
{
    int     size,
    size_t;
    object *thrones;
    string  desc =
    "Set to both sides of the High Throne of the King of Minas Morgul, "
    + "but three steps lower are the thrones of the other eight "
    + "ringwraiths.",
    vb;

    gNazgul_thrones &= all_inventory(TO);
    gNazgul_thrones -= ({ 0 });

    if (!(size = sizeof(gNazgul_thrones)))
	desc += " Set into the back of each of the smaller thrones "
	+ "are bas-reliefs.";
    else
    {
	if (member_array(TP, gNazgul_thrones) >= 0)
	{
	    thrones = gNazgul_thrones - ({ TP });
	    desc += " You";
	    if (size == 1)
		;
	    else if (size == 2)
		desc += " and";
	    else
		desc += ",";
	    vb = " are";
	}
	else
	{
	    thrones = gNazgul_thrones;
	    if (size > 1)
		vb = " are";
	    else
		vb = " is";
	}
	if ((size_t = sizeof(thrones)) == size)
	    //          desc += " " + CAP(COMPOSITE_LIVE(thrones));
	    desc += " " + CAP(MY_COMPOSITE_LIVE(thrones, TP));
	else if (size_t)
	    //          desc += " " + COMPOSITE_LIVE(thrones);
	    desc += " " + MY_COMPOSITE_LIVE(thrones, TP);
	desc += vb + " sitting in " + LANG_WNUM(size) + " of the thrones. "
	+ "The other " + LANG_WNUM(NO_NAZGUL - size) + " smaller "
	+ "thrones are empty and one can see that there are "
	+ "bas-reliefs set into the back of the thrones.";
    }

    return BSN(desc);
}

public string
exa_stone_chair()
{
    string  desc =
    "At the foot of the dais, there is a stone chair, black and "
    + "unadorned.",
    name;

    if (objectp(gStone_chair) && present(gStone_chair, TO))
    {
	if (TP == gStone_chair)
	    name = "You are";
	else if (TP->query_met(gStone_chair))
	    name = gStone_chair->query_name() + ", "
	    + gStone_chair->query_morgul_title() + ", is";
	else
	    name = CAP(LANG_ADDART(gStone_chair->query_nonmet_name())) + " is";
	desc += " " + name + " sitting on the stone chair.";
    }
    else
	desc += " On this chair sits the Lieutenant of Morgul when "
	+ "holding an audience in this hall.";

    return BSN(desc);
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string  str;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc != MORGUL_S_THRONE)
	return me->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
	str = "You are ";
    else
	str = CAP(HE(me)) + " is ";

    str += "sitting on ";

    switch(me->query_prop(MORGUL_S_THRONE))
    {
    case LORD_THRONE:
	str += "the High Throne on the dais.\n";
	break;
    case NAZGUL_THRONE:
	str += "one of the smaller thrones on the dais.\n";
	break;
    case STONE_CHAIR:
	str += "the stone chair at the foot of the dais.\n";
	break;
    }
    return str;
}

/*
 *	For msummon in the throne room:
 */
public int
query_red_eye()
{
    return 1;
}

string *
query_guilds(object x)
{
    return ( ({ x->query_guild_name_race(),
	x->query_guild_name_occ(),
	x->query_guild_name_lay(), }) - ({ 0 }) );
}

string
query_info(object *targets)
{
    int     i,
    s;
    string  desc = "";

    for (i = 0, s = sizeof(targets); i < s; i++)
	desc += "The name of the "+targets[i]->query_nonmet_name()
	+ " is "+targets[i]->query_name()+".\n"
	+ CAP(HE(targets[i]))+" is "+LANG_ADDART(targets[i]->query_exp_title())+".\n"
	+ CAP(HE(targets[i]))+" is "+targets[i]->query_align_text()+".\n"
	+ CAP(HE(targets[i]))+" is a member of the "
	+ COMPOSITE_WORDS(query_guilds(targets[i]))+".\n";
    return desc;
}

public void
do_summon_red_eye(object mage, object *targets)
{
    if (!gSummon_alarm_id || !sizeof(get_alarm(gSummon_alarm_id)))
    {
	gSummon_step = 0;
	gSummon_alarm_id = set_alarm(5.0, 5.0, &do_summon_red_eye(mage, targets));
	return;
    }

    targets -= ({ 0 });
    targets &= all_inventory(TO);
    if (!sizeof(targets))
	gSummon_step = 999;

    switch(gSummon_step++)
    {
    case 0:
	tell_room(TO, "The Red Eye set into the canopy of the High Throne "
	  + "suddenly starts to glow fiercely and seems to come to life!\n");
	break;
    case 1:
	tell_room(TO, "The Red Eye scans the room, looking for a victim.\n");
	break;
    case 2:
	targets->catch_msg("As much as you try to evade the Red Eye, you fail "
	  + "and the Red Eye seems to look deep into your own eyes!\n");
	tell_room(TO, "Finally, it comes to rest heavily on "
	  + COMPOSITE_LIVE(targets) + ".\n", targets);
	targets->command("tremble");
	break;
    case 3:
	targets->catch_msg("The Red Eye seems to read your mind like an "
	  + "open book. You try to resist, but in vain.\n");
	if (!objectp(mage) || !present(mage))
	    break;
	mage->catch_msg("The Red Eye reveals the following information to you:\n"
	  + query_info(targets));
	break;
    case 4:
	break;
    default:
	tell_room(TO, "The fierce glow of the Red Eye subsides again. The "
	  + "Eye that just seemed to be alive turns into stone again.\n");
	remove_alarm(gSummon_alarm_id);
	gSummon_alarm_id = 0;
	break;
    }
}

public void
stop_paralyze(object paralyzed)
{
    paralyzed->catch_msg("You can move again.\n");
    tell_room(TO, QCTNAME(paralyzed) + " seems to be able to move again.\n",
      paralyzed);
}

public void
query_new_name(string name)
{
    string *old_names = m_values(MORGUL_MASTER->query_mage_names());

    if (!strlen(name))
	input_to(query_new_name);

    if (member_array(name, old_names) >= 0)
    {
	write("The terrifying voice rasps: "
	  + "That name is already used by another of my servants!\n"
	  + "The terrifying voice rasps threateningly: "
	  + "Do not try my patience!\n");
	input_to(query_new_name);
    }
    gNew_name = name; 
    gNew_name2 = 0;
}

public void
query_new_name2(string name)
{
    if (!strlen(name))
	input_to(query_new_name2);

    if (gNew_name == name)
    {
	gNew_name2 = name;
	return;
    }
    write("The terrifying voice rasps: Make up your mind!\n"
      + "The terrifying voice rasps threateningly: "
      + "Do not try my patience!\n"
      + "The terrifying voice rasps: "
      + "If your name shall be "+name+", then repeat it!\n");
    tell_room(TO, "The terrifying voice rasps: So thou wouldst want to be "
      +  "known as "+name+"?\n"
      +  "The terrifying voice rasps: If this is so, then repeat "
      +  "your chosen name now!\n", TP);
    gNew_name = name;
    input_to(query_new_name2);
}

public void
naming_seq(object master, object target)
{
    object  paralyze;
    string  mage_name,
    name;

    if (!objectp(target) || !present(target) ||
      !objectp(master) || !present(master))
	gNaming_step = 999;

    switch(gNaming_step++)
    {
    case 0:
	tell_room(TO, "The Red Eye set into the canopy of the High "
	  + "Throne suddenly starts to glow fiercely and seems to "
	  + "come to life!\n");
	break;
    case 1: break;
    case 2:
	tell_room(TO, "The Red Eye scans the room, looking for a victim.\n");
	break;
    case 3: break;
    case 4:
	target->catch_msg("As much as you try to evade the Red Eye, you fail.\n"
	  + "The Red Eye stares at you, tearing through your mind and soul.\n"
	  + "You are unable to move.\n");
	tell_room(TO, "Finally, the Red Eye comes to rest heavily on "
	  + QTNAME(target) + ".\n"
	  + QCTNAME(target) + " seems to be paralyzed by the stare of the "
	  + "Red Eye.\n", target);
	//	Paralyze target
	paralyze = clone_object(MORGUL_OBJ_DIR + "naming_paralyze");
	paralyze->set_stop_object(this_object());
	paralyze->set_stop_fun("stop_paralyze");
	if (paralyze->move(target))
	    paralyze->move(target, 1);
	break;
    case 5: break;
    case 6:
	tell_room(TO, "A terrible wail suddenly fills the hall.\n"
	  + "The Red Eye set into the canopy of the High Throne "
	  + "begins to glow in a brighter red.\n"
	  + "You notice the presence of a powerful spirit.\n");
	break;
    case 7: break;
    case 8:
	mage_name = MORGUL_MASTER->query_mage_name(
	  name = master->query_real_name());
	if (!stringp(mage_name))
	    mage_name = CAP(name);
	tell_room(TO, "A terrifying voice rasps: You have called me, "
	  + mage_name + "?\n");
	break;
    case 9: break;
    case 10:
	tell_room(TO, "The terrifying voice rasps: You find this wretch worthy "
	  + "of my attention?\n");
	target->catch_msg("An iron fist seems to grasp your chest, taking "
	  + "away your breath.\n");
	target->command("$choke");
	tell_room(TO, "Terrible laughter echoes from the walls of the hall.\n");
	break;
    case 11: break;
    case 12:
	tell_room(TO, "The terrifying voice rasps: Well, then commence.\n"
	  +  "The terrifying voice rasps: Cut "+HIS(target)+" eyes out!\n"
	  +  "The terrifying voice screams: Now!\n");
	target->add_prop("_Morgul_remove_eyes", 1);
	break;
    case 13:
	if (target->query_prop(LIVE_I_SEE_DARK) >= 0)
	{
	    gNaming_step--;
	    break;
	}
	tell_room(TO, "The infernal laughing fills the hall once more!\n"
	  +  "The terrifying voice rasps: Good!\n"
	  +  "The terrifying voice rasps: My servants will not see but "
	  +  "through my eyes!\n");
	break;
    case 14: break;
    case 15:
	tell_room(TO, "The terrifying voice rasps: "+target->query_name()
	  +  ", what shall be thy name in the future?\n"
	  +  "The terrifying voice rasps: Tell me now!\n");
	set_this_player(target);
	input_to(query_new_name);
	break;
    case 16:
	if (!strlen(gNew_name))
	{
	    gNaming_step--;
	    break;
	}
	tell_room(TO, "The terrifying voice rasps: So thou wouldst want to be "
	  +  "known as "+gNew_name+"?\n"
	  +  "The terrifying voice rasps: If this is so, then repeat "
	  +  "your chosen name now!\n");
	set_this_player(target);
	input_to(query_new_name2);
	break;
    case 17:
	if (!strlen(gNew_name2))
	{
	    gNaming_step--;
	    break;
	}
	name = target->query_real_name();
	MORGUL_MASTER->add_mage_name(name, gNew_name);
	target->set_morgul_penalty(
	  APPRENTICE_LEVEL + 1 - target->query_morgul_level(1) / 2);
	write_file(MORGUL_REGULAR_RECORDS, "RAKASUL: " + CAP(name) + " received the "
	  + "mage name "+gNew_name+" from "+master->query_name()
	  + " at "+ctime(time())+". New rank is "
	  + target->query_morgul_level() + ".\n");
	write_file(MORGUL_NAZGUL_RECORDS, CAP(name) + " received the mage name "
	  + gNew_name + " at the hands of " + master->query_name()
	  + " ("+ctime(time())+").\n");
	tell_room(TO, "The terrifying voice rasps: So be it!\n"
	  +  "The terrifying voice rasps: "+target->query_name()
	  +  " thou were! "+gNew_name+" thou shall be!\n");
	target->catch_msg("You feel the Power of the Dark Lord enter "
	  + "the sad remains of your body.\n"
	  + "Suddenly, you can see again.\n");
	target->remove_prop(LIVE_I_SEE_DARK);
	paralyze = present("_Stare_of_the_Red_Eye", target);
	if (objectp(paralyze))
	    paralyze->stop_paralyze();
	break;
    case 18: break;
    case 19:
	tell_room(TO, "The Red Eye set into the canopy of the High Throne "
	  + "explodes into a intense blast of fiery red light.\n"
	  + "You are blinded!\n");
	add_prop("_save" + ROOM_I_LIGHT, query_prop(ROOM_I_LIGHT));
	add_prop(ROOM_I_LIGHT, -999);
	add_prop(ROOM_S_DARK_LONG, "Your eyes are still blinded from the glare.\n");
	add_prop(ROOM_S_DARK_MSG, "Your eyes are still blinded from the "
	  + "glare so you are unable to");
	break;
    case 20: break;
    case 21:
	tell_room(TO, "You feel the presence of the powerful spirit fading.\n");
	break;
    case 22: break;
    case 23:
	add_prop(ROOM_I_LIGHT, query_prop("_save" + ROOM_I_LIGHT));
	remove_prop("_save" + ROOM_I_LIGHT);
	remove_prop(ROOM_S_DARK_LONG);
	remove_prop(ROOM_S_DARK_MSG);
	tell_room(TO, "When you are able to see again, the Red Eye set "
	  + "into the canopy of the High Throne has turned back into stone.\n");
	break;
    case 999:
	if (objectp(target) && present(target))
	{
	    paralyze = present("_Stare_of_the_Red_Eye", target);
	    if (objectp(paralyze))
		paralyze->stop_paralyze();
	}
	tell_room(TO, "The fierce glow of the Red Eye subsides again. The "
	  + "Eye that just seemed to be alive turns into stone again.\n");
	// fall thru
    default:
	remove_alarm(gNaming_seq_id);
	gNew_name = 0;
	gNaming_seq_id = 0;
	break;
    }
}

public int
do_name(string str)
{
 int i, j;
 object *livings, target;

    if (!this_player()->query_nazgul())
	return 0;

    if (gNaming_seq_id && sizeof(get_alarm(gNaming_seq_id)))
    {
	notify_fail("The Red Eye is busy!");
	return 0;
    }

    notify_fail("Promote whom to magedom?");
    if (!strlen(str))
	return 0;

    str = LOW(str);
    target = find_player(str);
    if (!objectp(target) || !present(target))
	return 0;

    if (target->query_morgul_level() < APPRENTICE_LEVEL)
    {
	write(capitalize(str)+" is not yet worthy to receive the powers of "
	  + "full magedom!\n");
	return 1;
    }

    if (target->query_guild_member_lay())
    {
	write(capitalize(str)+" is still a member of " +
            target->query_guild_name_lay() + ", and must leave them " +
            "before committing fully to being a full mage!\n");
	return 1;
    }

    write("You offer a silent prayer unto the Red Eye to offer the spirit of "
      + capitalize(str) + " to feed its hunger.\n");
    say( QCTNAME(this_player()) + " moves " + HIS(this_player()) +
	    " lips without making a sound.\n");

    gNew_name = 0;
    gNaming_step = 0;
    gNaming_seq_id = set_alarm(4.0, 5.0, &naming_seq(this_player(), target));

    livings = FILTER_LIVE( all_inventory( this_object() ) );
    j = sizeof( livings );
    for (i=0;i<j;i++)
    {
        MORGUL_MASTER->increase_activity( livings[i], ACTIVITY_RAKASUL);
    }

    return 1;
}

public int do_promote(string str)
{
    object  tp = TP, oMage, *livings;
    string  where, which, sMage;
    int i, j;

    if (!this_player()->query_nazgul())
        return 0;

    if (!stringp(where = tp->query_prop(MORGUL_S_THRONE))) {
        notify_fail("You need to be sitting on your throne to do that!\n", 2);
        return 0;
    }

    if (!strlen(str)) {
        notify_fail("Promote whom to servant?\n", 2);
        return 0;
    }

    str = lower_case( str );
    if ((sscanf( str, "%s to servant", sMage) != 1)) {
        notify_fail("Promote whom to servant?\n", 2);
        return 0;
    }

    if(!sMage)
    {
        notify_fail("Which of the members of the Society do you want to promote?\n", 2);
        return 0;
    }

    oMage = find_player(sMage);
    if (!objectp(oMage) || !present(oMage))
    {
        notify_fail(capitalize(sMage)+ " is not present in the Throne Room!\n", 2);
        return 0;
    }

    if(!IS_MEMBER(oMage))
    {
        notify_fail("The wretch " +oMage->query_name()+ " is not a member of the Society!\n", 2);
        return 0;
    }

    if (!MORGUL_MASTER->query_is_tuvale(oMage)) 
    {
        notify_fail(oMage->query_name() + " is not a tuvale!\n", 2);
        return 0;
    }

    write("You remove the Tuvale status of " +oMage->query_name()+ "!\n");

    MORGUL_MASTER->set_tuvale(oMage, 0);
    oMage->catch_msg("You are now a " + oMage->query_morgul_title() + "!\n");

    livings = FILTER_LIVE( all_inventory( this_object() ) );
    j = sizeof( livings );
    for (i = 0; i < j; i++)
    {
        MORGUL_MASTER->increase_activity( livings[i], ACTIVITY_RAKASUL );
    }

    write_file(MORGUL_NAZGUL_RECORDS, 
          capitalize(this_player()->query_real_name()) + " removed the "
        + "Tuvale status of " + capitalize(oMage->query_real_name()) 
        + " (" + ctime(time()) + ").\n");

    return 1;
}

public int do_appoint(string str)
{
    object  tp = TP, oMage, *livings;
    string  where, which, sMage;
    int i, j;

    if (!this_player()->query_nazgul())
        return 0;

    if (!stringp(where = tp->query_prop(MORGUL_S_THRONE))) {
        notify_fail("You need to be sitting on your throne to do that!\n");
        return 0;
    }

    if (!strlen(str)) {
        notify_fail("Appoint whom to what position?\n");
        return 0;
    }

    str = lower_case( str );
    if ((sscanf( str, "%s to %s", sMage, which ) != 2)) {
        notify_fail("Appoint whom to what position?\n");
        return 0;
    }

    if(!sMage)
    {
        notify_fail( "Which of the members of the Society do you want to appoint?\n");
        return 0;
    }

    if(!which) {
        notify_fail( "Appoint " +capitalize(sMage)+ " to what?\n");
        return 0;
    }

    if(member_array(which, m_indices(ASSIGNABLE_POSITIONS)) == -1) {
        notify_fail("You can appoint someone to the position of "
            + COMPOSITE_WORDS_WITH(m_indices(ASSIGNABLE_POSITIONS), "or")
            + ".\n");
        return 0;
    }
    
    oMage = find_player(sMage);
    if (!objectp(oMage) || !present(oMage))
    {
        notify_fail(capitalize(sMage)+ " is not present in the Throne Room!\n");
        return 0;
    }

    if(!oMage->query_morgul_level())
    {
        notify_fail("The wretch " +oMage->query_name()+ " is not a member of the Society!\n");
        return 0;
    }
        
    string current_holder = MORGUL_MASTER->query_position(which);
    if (stringp(current_holder) && (current_holder != "None")) {
        notify_fail(capitalize(current_holder) + " is already appointed as "
            + "the " + ASSIGNABLE_POSITIONS[which] + "!\nFirst make the "
            + "position available again!\n");
        return 0;
    }

    write("You appoint " +oMage->query_name()+ " as the "
        + ASSIGNABLE_POSITIONS[which] + "!\n");
        
    say(QCTNAME(this_player())+ " appoints " +QTNAME(oMage)+ " as the "
        + ASSIGNABLE_POSITIONS[which] + "!\n", ({oMage, this_player()}) );
    oMage->catch_msg("You have been appointed " + ASSIGNABLE_POSITIONS[which] 
        + " by " + QTNAME(this_player()) + "!\n");

    MORGUL_MASTER->assign_position(which, oMage);

    livings = FILTER_LIVE( all_inventory( this_object() ) );
    j = sizeof( livings );
    for (i = 0; i < j; i++)
    {
        MORGUL_MASTER->increase_activity( livings[i], ACTIVITY_RAKASUL );
    }

    write_file(MORGUL_NAZGUL_RECORDS, 
          capitalize(this_player()->query_real_name()) + " appointed "
        + capitalize(oMage->query_real_name()) + " as the "
        + ASSIGNABLE_POSITIONS[which] + " (" + ctime(time()) + ").\n");

    return 1;
}

public int do_release(string str)
{
    object  tp = TP, oMage, *livings;
    string  where, which, sMage;
    int i, j;

    if (!this_player()->query_nazgul())
        return 0;

    if (!stringp(where = tp->query_prop(MORGUL_S_THRONE))) {
        notify_fail("You need to be sitting on your throne to do that!\n");
        return 0;
    }

    if (!strlen(str)) {
        notify_fail("Release whom from what position?\n");
        return 0;
    }

    str = lower_case( str );
    if ((sscanf( str, "%s from %s", sMage, which ) != 2)) {
        notify_fail("Release whom from what position?\n");
        return 0;
    }

    if(!sMage)
    {
        notify_fail( "Which of the members of the Society do you want to release?\n");
        return 0;
    }

    if(!which) {
        notify_fail( "Release " +capitalize(sMage)+ " from what?\n");
        return 0;
    }

    if(member_array(which, m_indices(ASSIGNABLE_POSITIONS)) == -1) {
        notify_fail("You can release someone from the position of "
            + COMPOSITE_WORDS_WITH(m_indices(ASSIGNABLE_POSITIONS), "or")
            + ".\n");
        return 0;
    }
    
    if(lower_case(MORGUL_MASTER->query_position(which)) != lower_case(sMage)) {
        notify_fail(capitalize(sMage) + " is not the " 
            + ASSIGNABLE_POSITIONS[which] + ".\n");
        return 0;
    }
    
    write("You release " + capitalize(sMage) + " as the " 
        + ASSIGNABLE_POSITIONS[which] + "!\n");

    oMage = find_player(sMage);
    
    if (objectp(oMage)) {
        say(QCTNAME(this_player())+ " releases " +QTNAME(oMage)+ " as the "
            + ASSIGNABLE_POSITIONS[which] + "!\n", ({oMage, this_player()}) );
        oMage->catch_msg("You have been released from being the "
            + ASSIGNABLE_POSITIONS[which] + " by " + QTNAME(this_player()) + "!\n");
    } else { 
        say(QCTNAME(this_player()) + " releases " + capitalize(sMage) + " as the "
            + ASSIGNABLE_POSITIONS[which] + "!\n", ({ this_player()}) );
    }

    MORGUL_MASTER->remove_from_position(which, sMage);
    
    livings = FILTER_LIVE( all_inventory( this_object() ) );
    j = sizeof( livings );
    for (i = 0; i < j; i++)
    {
        MORGUL_MASTER->increase_activity( livings[i], ACTIVITY_RAKASUL );
    }

    write_file(MORGUL_NAZGUL_RECORDS, 
          capitalize(this_player()->query_real_name()) + " released "
        + capitalize(oMage->query_real_name()) + " as the "
        + ASSIGNABLE_POSITIONS[which] + " (" + ctime(time()) + ").\n");

    return 1;
}

/***********************************************
 *      The 'pure emotions' below.             *
 ***********************************************/

int
do_recline(string str)
{
    object  tp = TP;
    string  where;

    if (!stringp(where = tp->query_prop(MORGUL_S_THRONE)))
	return 0;

    if (where == STONE_CHAIR)
    {
	write("You recline thoughtfully upon your chair.\n");
	say(QCTNAME(tp)+" reclines thoughtfully upon "+HIS(tp)+" chair.\n");
	return 1;
    }

    write("You recline thoughtfully upon your throne.\n");
    say(QCTNAME(tp)+" reclines thoughtfully upon "+HIS(tp)+" throne.\n");
    return 1;
}

int
do_inspect(string str)
{
    object  tp = TP,
    *objs,
    *live,
    *dead;
    string  where,
    what;


    if (!stringp(where = tp->query_prop(MORGUL_S_THRONE)))
	return 0;

    if (!str)
    {
	NFN("Inspect what?");
	return 0;
    }

    if (!parse_command(str, TO, "%l", objs))
    {
	NF("You cannot find any "+str+" here.\n");
	return 0;
    }

    objs = NORMAL_ACCESS(objs, 0, 0);
    objs -= ({ tp });
    if (!sizeof(objs))
    {
	NF("You cannot find any "+str+" here.\n");
	return 0;
    }

    if (where == STONE_CHAIR)
	what = "chair";
    else
	what = "throne";

    write("You sit forward on your "+what+", inspecting "
      + COMPOSITE_LIVE(objs) + " carefully.\n");
    objs->catch_msg(QCTNAME(tp) + " sits forward on "
      + HIS(tp) + " "+what+", scrutinizing you carefully.\n");
    say(QCTNAME(tp)+" sits forward on "+HIS(tp)+" "+what+", inspecting "
      + COMPOSITE_LIVE(objs) + " carefully.\n", ({ tp }) + objs);
    return 1;
}

/* Drumming the fingers suggested by Ugelplect - Morbeche */
/* Commented out until I get around to adding in adverbs */
/*
int
do_drum(string str)
{
  string *how;

  how = parse_adverb_with_space(str, "steadily", 0);

  write("You " + how[1] + " drum your fingers on " +
	"the arm of your throne.\n");
  all(" "+ how[1] + " drums "+ HIS(TP) +" haggard " +
      "fingers on the arm of "+HIS(TP)+" throne.");
  return 1;

}

int
do_grip(string str)
{
  string *how;

  how = parse_adverb_with_space(str, "furiously", 0);

  write("You " + how[1] + " grip the arms of your throne " +
	"in both of your powerful hands, barely " +
	"able to control yourself.\n");
  all(" "+ how[1] + " grips the arms of "+ HIS(TP) +
     " throne in both of "+HIS(TP)+" powerful hands, " +
      "barely able to control "+HIM(TP)+"self.");
  return 1;

}
*/

int
do_drum()
{
    string where;

    if (!stringp(where = TP->query_prop(MORGUL_S_THRONE)))
	return 0;

    if (!TP->query_nazgul())
	return 0;


    write("You steadily drum your haggard fingers on " +
      "the arm of your throne.\n");
    tell_room(TO,QCTNAME(TP)+" steadily drums "+ HIS(TP) +
      " haggard fingers on the arm of "+HIS(TP)+" throne.\n",TP);
    return 1;

}

int
do_grip()
{

    string where;

    if (!stringp(where = TP->query_prop(MORGUL_S_THRONE)))
	return 0;

    if (!TP->query_nazgul())
	return 0;


    write("You furiously grip the arms of your throne " +
      "in both of your powerful hands, barely " +
      "able to control your anger.\n");
    tell_room(TO,QCTNAME(TP)+" furiously grips the "+
      "arms of "+ HIS(TP) +
      " throne in both of "+HIS(TP)+" powerful hands, " +
      "barely able to control "+HIS(TP)+" anger.\n",TP);
    return 1;

}

