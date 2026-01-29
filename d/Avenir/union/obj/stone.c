/*
 * - /d/Avenir/union/obj/stone.c
 *
 * Guild token for the Shadow Union
 * Cirion 032596
 *
 * Revisions:
 * 	Cirion, Apr 1997: Added some guildmaster commands to the
 * 			  stone as well.
 *	Lucius, Sep 2005: Some cleaning and modifications to ufeel.
 *	Lucius, Aug 2017: Re-Code.
 *  Lilith, Feb 2022: Re-enabled "union" functionality for wizards.
 *  Lilith, May 2022: Updated messages for the flame levels, added
 *                    some capitals, per Elder request.
 */
#pragma strict_types
#pragma no_inherit
#pragma no_shadow

#include <time.h>
#include <files.h>
#include <macros.h>
#include <wa_types.h>
#include <composite.h>

#include "../defs.h"

inherit "/std/key";
inherit "/lib/holdable_item";
inherit "/lib/help";

#define FEEL_OFF	"_union_i_ufeel_off"
#define NHELP_DIR   "/d/Avenir/union/help/novice/"

private static int alarm;
private static mapping m_ufeel;


/* Create our guild token, the Union's tiny black sphere. */
public void 
create_key(void)
{
    if (!IS_CLONE)
	return;

    reset_euid();

    remove_name("key");
    remove_pname("keys");

    set_name("sphere");
    set_pname("spheres");
    add_name(({"_crucible_component"}));
    add_name(TOKEN_ID);
    set_key(TOKEN_ID);
    set_adj(({"small","tiny","black","obsidian"}));
    set_short("tiny black sphere");
    set_pshort("tiny black spheres");

    /* long() masked, see below. */
    set_long("YOU SHOULD NOT SEE THIS!\n");

    set_slots(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 16);
    add_prop(OBJ_I_VALUE, 198);
    add_prop(OBJ_M_NO_SELL, "That would be unwise.\n");

    m_ufeel = LIST->query_ufeel_map();
	
	// Help files directed toward Novices
	set_help_dir(NHELP_DIR);
	set_help_category("novice");
}

/*
 * Update on Sybarun hour changes.
 */
public int
avenir_time(int year, int week, int day, int hour)
{
    tell_object(environment(this_object()),
	"The "+ short() +" subtly pulses "+
	LANG_NUM2WORD(hour) +
	(hour == 1 ? " time" : " times") + ".\n");

    /* Always 1 */
    return 1;
}

/*
 * This gets the time from the avenir_time object and returns the
 * get_time_text string.
 */
private string 
tell_time(void)
{
    return LIST->get_time_text();
}

/*
 * Returns help text based on Union level.
 */
private string
show_help(void)
{
    string str = " To learn more, try 'help sphere'. "+
	"For general Union help, try 'help union'."; 

    if (!IS_MEMBER(TP))
	return "";

    if (MEMBER_SPHERE(TP, SPH_MENTOR))
	str += " As a Mentor of the Union, also try 'help mentor'.";

    if (IS_ELDER(TP))
	str += " As one of the Flari, you may also try 'help elders'.";

    return str;
}

/*
 * Returns text based on the strength of the Flame.
 */
private string 
show_flame(void)
{
    switch(STATE)
    {
    case 6501..MAX_FLAME_STATE:
	return "The stone feels almost on fire with tiny white "+
	    "sparks that dance chaotically around in furious swirls.";
    case 4001..6500:
	return "The stone gleams and shines with hundreds of tiny "+
	    "white points of light that seem to dance and swirl "+
	    "around themselves.";
    case 2001..4000:
	return "The stone glimmers with many tiny points of white "+
	    "light, swirling and dancing.";
    case 1001..2000:
	return "The stone gleams with a number of tiny white points "+
	    "that are moving in slow swirls around the edges.";
    case 501..1000:
	return "In the stone you can see a few small pinpoints "+
	    "of bright white light, moving very slowly around the sphere.";
    case 2..500:
	return "In the stone you can see two tiny points of "+
	    "white light that seem to be moving very slowly.";
    case 1:
	return "One single tiny point of white light rests "+
	    "on the surface of the stone, unmoving.";
    default:
	return "The stone lies cold and dead in your hands, "+
	    "lifeless and heavy.";
    }
}

public varargs mixed
long(string str, object obj)
{
    string res;

    if (strlen(str))
	return ::long(str, obj);

    res = "Perfectly round and smooth, this deep black "+
	"sphere seems to be made of a stone similar to obsidian. ";

    if (TP != environment())
	return res + "\n";

    res += show_flame();
    res += " Through it, you can sense that it is currently the ";
    res += tell_time();
    res += ". " + show_help();

    return res + "\n";
}

private int
sphere_hearers(object who, int rubbed)
{
    // Don't hear: Its me.
    if (who == TP)
	return 0;

    // Don't hear: I don't have a sphere.
    if (!present(TOKEN_ID, who)) 
	return 0;

    // If I'm a wiz who doesn't want to hear.
    if (who->query_prop(FEEL_OFF))
	return 0;

    // Don't hear: I'm in Isolation or Training
    if (who->query_union_sphere() == SPH_TRAINING ||
	who->query_union_sphere() == SPH_ISOLATION)
	return 0;

    // Allow people to not be spammed by zealous sphere rubbers.
#ifdef UOPT_STOUCH
    if (rubbed && LIST->query_union_option(who, UOPT_STOUCH))
	return 0;
#endif

    // Ok, I can hear.
    return 1;
}

public nomask int 
is_union_guild_token(object obj)
{
    return obj->id(TOKEN_ID);
}

/*
 * This must be public, called when leaving
 * the guild to remove the sphere.
 */
public void
crumble(void)
{
    object dust = clone_object("/std/object");
    dust->add_prop(OBJ_I_WEIGHT, 5);
    dust->add_prop(OBJ_I_VOLUME, 8);
    dust->add_prop(OBJ_I_VALUE, 1);
    dust->set_name(({"dust", "handful", "_crucible_component"}));
    dust->set_short("handful of black dust");
    dust->set_pshort("handfuls of black dust");
    dust->set_long("It is a small handful of black, "
      +"fine dust, almost like soot.\nIt smells very strange.\n");
    dust->add_cmd_item(({"dust","pile"}),({"touch","rub","feel"}),"It is soft "
      +"and grainular, as smooth as silk.\n");
    dust->add_cmd_item(({"dust","pile"}),({"smell","sniff"}),"It smells of "
      +"purity and shadows, of the sad memories of a lost life.\n");
    dust->move(ENV(TO), 1);

    tell_room(ENV(TO), "The obsidian sphere crumbles to dust.\n");
    set_alarm(0.0, 0.0, remove_object);
}

private void 
check(void)
{
    object *stuff, who = ENV(TO);

    alarm = 0;
    stuff = filter(all_inventory(who), is_union_guild_token);

    if (sizeof(stuff) > 1)
    {
	crumble();
	return;
    }

    if (!IS_MEMBER(who))
    {
	crumble();
	return;
    }

    who->catch_tell("You are at one with the shadows.\n");
}

public int
do_rub(string str)
{
    string heat, *members;

    if (str != "sphere")
	return notify_fail(CAP(query_verb()) + " what?\n");

    write("You run your fingers along the smooth surface of "+
	LANG_THESHORT(TO) + ".\n");

    // Don't do say if player is invis.
    if (!TP->query_invis())
    {
	say(QCTNAME(TP)+" rubs "+ HIS(TP) +" finger along the surface of "+
	    LANG_ASHORT(TO) + ".\n");
    }

    filter(users(), &sphere_hearers(, 1))->catch_tell("You feel "+
	LANG_POSS(CAP(TP->query_real_name())) +
	" touch through your sphere.\n");

    switch(STATE)
    {
        case 9001..MAX_FLAME_STATE: heat = "hot as the Passion of Jazur"; break;
        case 8001..9000:    heat = "impossibly hot";    break;
        case 7001..8000: heat = "blazing hot";       break;
        case 6001..7000: heat = "blissfully hot";    break;
        case 5001..6000: heat = "delightfully hot";  break;
        case 4001..5000: heat = "pleasantly warm";   break;
        case 3001..4000: heat = "declining in warmth";  break;    
        case 2601..3000: heat = "sadly tepid";          break;
        case 2001..2600: heat = "shamefully lukewarm";  break;
        case 1001..2000: heat = "just slightly warm";   break;
        case 601..1000: heat = "like the Flame is dying"; break;
        case 301..600: heat = "alarmingly cool";  break;
        case 101..300: heat = "cold";             break;
        default: heat = "freezing";         break;    
    }

    write("It feels "+ heat +".\n");

    members = filter(users(), &->query_is_union_player())->query_real_name();
    members = sort_array(members);

    if (sizeof(members) <= 1)
    {
	write("Jazur is your only source of Passion and Joy.\n"+
	  "Your Other Selves are resting in shadow.\n"); 
	return 1;
    }

    write("Through your link with the Flame, you feel joyful "+
      "at the presence of:\n");

    foreach(string who: members)
    {
	write(sprintf("    %-11s %s\n", CAP(who),
	    find_player(who)->query_guild_title_occ()));
    }

    return 1;
}

/*
 * Function name:  do_ufeel
 * Description:    Provide help for the ufeel emote
 * Argument:       sphere and other strings
 * Returns:        0/1
 */  
public int
do_ufeel(string str)
{
    mixed tmp;

    if (TP->query_union_sphere() == SPH_TRAINING)
    {
	write("You feel your sphere, but nothing happens. Your "+
	    "link to the Flame has not yet been forged.\n");
	return 1;       
    }
    else if (TP->query_union_sphere() == SPH_ISOLATION)
    {
	write("You clench your fist around your sphere, but nothing "+
	    "happens. You are in isolation.\n");
	return 1;       
    }

    str = lower_case(str);

    if (!strlen(str) || (str == "sphere"))
    {
	write("Only those who are One have the ability to "+
	    "communicate the way they are feeling to their other "+
	    "selves through the sphere. Those who are in Training "+
	    "and Isolation are not able to link their spheres "+
	    "through the Flame.\n   You can express the following "+
	    "using <ufeel [feeling]>:\n");

	write(sprintf("\n%-#76s\n\n", implode(sort_array(
			m_indices(m_ufeel) + ({"<name>"})), "\n")));

	write("You may also test how a feeling might work via "+
	    "<ufeel test [feeling]>.\n");

	return 1;
    }

    if (TP->query_wiz_level())
    {
	if (str == "on")
	{
	    TP->remove_prop(FEEL_OFF);
	    write("Ufeel is on. You can feel mortal use of "+
		"the sphere, and they can feel yours.\n");
	    return 1;
	}
	else if (str == "off")
	{
	    TP->add_prop(FEEL_OFF, 1);
	    write("Ufeel is off. You have blocked messages "+
		"from the sphere.\n");
	    return 1;
	}
	else if (str == "testall")
	{
	    int size, ix = -1;
	    string *ufeels = sort_array(m_indices(m_ufeel));

	    size = sizeof(ufeels);
	    while(++ix < size)
		do_ufeel(ufeels[ix]);

	    write("Tested "+ size +" sphere feelings.\n");
	    return 1;
	}
	else if (TP->query_prop(FEEL_OFF))
	{
	    write("Ufeel is currently 'off'. If you want to be able "+
	      "to sense mortal use of the sphere, you will need to "+
	      "do <ufeel on>.\n");
	    return 1;       
	}
    }

    int testing = 0;
    tmp = explode(str, " ");

    if (tmp[0] == "test")
    {
	if (sizeof(tmp) < 2)
	{
	    write("Which feeling are you seeking to test?\n");
	    return 1;
	}

	testing = 1;
	str = implode(tmp[1..], " ");
    }

    if (stringp(tmp = m_ufeel[str]))
	tmp = m_ufeel[tmp];

    if (!pointerp(tmp))
    {
	if (IN_ARRAY(str, LIST->member_list()) &&
	    (str != TP->query_real_name()))
	{
	    tmp = CAP(str);
	    tmp = ({ "thoughts of "+ tmp, "thinking of "+ tmp });
	}
	else
	{
	    write("That feeling isn't possible to communicate "+
	      "at this time. Please do an idea report if you want "+
	      "it added.\n");
	    return 1;
	}
    }

    write("You clench your fist around your sphere, causing it to "+
      "pulse with your "+ tmp[0] +".\n");

    object *listeners;

    if (testing)
    {
	listeners = ({ TP });
	write("Since you are testing, this is what others "+
	  "would see:\n");
    }
    else
    {
	listeners = filter(users(), sphere_hearers);
    }

    listeners->catch_tell("There is a pulse from your sphere and you "+
	"have a sudden understanding that\n"+
	CAP(TP->query_real_name()) +" is "+ tmp[1] +".\n");

    return 1;        
}

/*
 * Function name:  do_help
 * Description:    Provide help for the functions in this obj
 * Argument:       sphere
 * Returns:        0/1
 */  
public int 
do_help(string str)
{
    if (str != "sphere" && str != "stone")
	return 0;

    write("The sphere you hold in your hand is your link to the "+
      "Flame of Jazur, and to your other selves.\n"+
      " Using <rub sphere> will reveal unto you the presence of "+
      "your other selves, and reveal your presence unto them. "+
      "By its temperature you can also gauge the strength of "+
      "the Flame.\n"+
      " Using <exa sphere> will provide you with another measure "+
      "of the the Flame's strength, as well as the time in Sybarus.\n"+
      " Using <ufeel sphere> will reveal unto you the ways "+
      "you can communicate the state of your Passion to your "+
      "other selves through your link with the Flame.\n");

    if (TP->query_wiz_level())
    {
	write(" Wizards default to <ufeel off>. Toggling to "+
	  "<ufeel on> will allow you to use and to feel "+
	  "mortal use of the sphere.\n"+
      "Typing <union> will give a list of Union members with "+
	  "their spheres, stat av, and location.\n"+
	  "<uupdate soul/shadow> allows safe updates.\n");
    }
    return 1;
}


private int
has_arg(string *list, string arg)
{
    int i;

    if (!(i = sizeof(list)))
	return 0;

    while(--i)
    {
	if (wildmatch(arg + "*", list[i]))
	    return 1;
    }

    return 0;
}

public int
union(string str)
{
    string *members, *arg, dist = "", when;
    object who, player;
    int idle = 0,
    last = 1,
    virtues = 0,
    loc = 1,
    team = 0,
    spheres = 1,
    stat = 1,
    titles = 1,
    i;

    if (!(TP->query_wiz_level()))
	return 0;

    if (strlen(str))
    {
	str = " " + str;
	arg = explode(str, " -");

	if (has_arg(arg, "h"))
	{
	    write("Possible flags: idle, virtues, loc, team, spheres, "+
	      "averagestat, guildtitle.\n");
	}
	if (has_arg(arg, "i"))
	    idle = !idle;
	if (has_arg(arg, "v"))
	    virtues = !virtues;
	if (has_arg(arg, "l"))
	    loc = !loc;
	if (has_arg(arg, "t"))
	    team = !team;
	if (has_arg(arg, "s"))
	    spheres = !spheres;
	if (has_arg(arg, "a"))
	    stat = !stat;
	if (has_arg(arg, "g"))
	    titles = !titles;
    }

    if (idle)
	members = LIST->member_list();
    else
	members = filter(users(), &->query_is_union_member())->query_real_name();

    if (!sizeof(members))
    {
	write("No members of the Union found.\n");
	return 1;
    }

    for (i = 0; i < sizeof(members); i++)
    {
	who = find_player(members[i]);
	dist += sprintf("%-10s", CAP(members[i]));

	if (idle)
	{
	    if(!who)
	    {
		player = SECURITY->finger_player(members[i]); 
		when = TIME2STR(time() - player->query_login_time(), 2); 
		player->remove_object();
	    }
	    else if(interactive(who))
	    {
		when = TIME2STR(query_idle(who), 2);
	    }

	    dist += " [" + when + "] ";
	}

	if (stat && who)
	    dist += sprintf("%-6s", " (" + who->query_average_stat() + ") ");
	if (loc && who)
	    dist += file_name(ENV(who));
	if (spheres && who)
	{
	    dist += "\n\t" + who->query_union_sphere_title() + " {"+
	    who->query_union_sphere() + "}";
	}
	if (titles && who)
	    dist += "\n\t" + who->query_guild_title_occ();
	if (virtues && who)
	{
	    dist += "\n\tDignity: " + who->query_union_virtue(US_DIGNITY) + "  "
	    + "Purity: " + who->query_union_virtue(US_PURITY) + "  "
	    + "Grace: " + who->query_union_virtue(US_GRACE) + "  "
	    + "Pride: " + who->query_union_virtue(US_PRIDE);
	}
	if (who && team && sizeof(who->query_team_others()))
	    dist += "\n\tTeamed: " + COMPOSITE_LIVE(who->query_team_others());

	dist += "\n";
    }

    write(dist);
    return 1;
}

/* Commands and function */
/*
 * Function name: copy
 * Description  : Copy a (text) file. Limited to about 50kB files by the GD.
 *                It could be circumvented but very few files are larger
 *                than that. Maybe I should make this into an simul-efun?
 * Arguments    : string path1 - source path.
 *                string path2 - destination path (including filename).
 * Returns      : int 1/0 - success/failure.
 * Note         : Ripped off by Cirion from /cmd/wiz/normal/files.c
 */
private nomask int
copy(string path1, string path2)
{
    string buf;

    /* Read the source file and test for success. */
    buf = read_file(path1);
    if (!strlen(buf))
    {
	return 0;
    }

    switch(file_size(path2))
    {
	/* Target is a directory. Impossible. */
    case -2:
	return 0;

	/* Target file does not exist or is empty. Proceed. */
    case -1:
    case  0:
	break;

	/* Existing target file. Try to remove it first. */
    default:
	if (!rm(path2))
	{
	    return 0;
	}
    }

    /* Write the buffer and return the return value of the efun. */
    return write_file(path2, buf);
}

/*
 * Uupdate [soul/shadow]:
 *
 * Allows a Union wizard to update the soul or shadow nicely.
 * Bugs in the soul/shadow will be checked for by first
 * copying the file to a test file and seeing if it loads.
 * It also checks for alarms running in the object (so
 * updating it does not screw up any special attacks
 * that may be running at the time.)
 */
public int
uupdate(string str)
{
    string   update_from,
    test_file = UNION + "ts";

    /* this is only a wiz command! */
    if (!(TP->query_wiz_level()))
	return 0;

    if (str == "soul" || !str)
	update_from = OCC_SOUL;
    else if (str == "shadow")
	update_from = OCC_SHADOW;
    else
    {
	write("Usage: uupdate [soul/shadow]\n");
	return 1;
    }

    NF("Failed: Could not copy file: " + update_from + ".c to: "
      + test_file + ".c\n");
    if(!copy(update_from + ".c", test_file + ".c"))
	return 0;

    /* remove the old object */
    SECURITY->do_debug("destroy", find_object(test_file));

    if(catch(test_file->teleldensanka()))
    {
	write("Failed: " + test_file + " did not load!\n");
	write("Excerpt from /lplog:\n");
	write("-------------------------------------\n");
	tail("/lplog");
	write("-------------------------------------\n");
	return 1;
    }

    write("Successfully loaded " + test_file + "\n");

    if(sizeof(update_from->query_alarms()))
    {
	write("Cannot update " + update_from + " now: alarms are running.\n");
	write("Try to update it later.\n");
	return 1;
    }

    /* remove the old object */
    SECURITY->do_debug("destroy", find_object(update_from));

    if(catch(update_from->teleldensanka()))
    {
	write("Failed: Woah! " + update_from + " did not load!\n");
	write("Excerpt from /lplog:\n");
	write("-------------------------------------\n");
	tail("/lplog");
	write("-------------------------------------\n");
	return 1;
    }
    write(update_from + " is now updated.\n");
    return 1;
}


public void 
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!alarm)
	alarm = set_alarm(2.0, 0.0, check);

    if (query_interactive(to))
	LIST->notify_time(TO);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

private void
rem_drop_prop(void)
{ 
    remove_prop(OBJ_I_NO_DROP); 
}

public string
query_auto_load(void)
{
    set_alarm(1.0, 0.0, rem_drop_prop);
    add_prop(OBJ_I_NO_DROP, 1);
    return MASTER+":";
}

public void
init(void)
{
    ::init();

    add_action(do_rub,  "rub");
    add_action(do_rub,  "urub");
    add_action(do_rub,  "feel");
    add_action(do_rub,  "touch");
    add_action(do_ufeel, "ufeel");
    add_action(do_help, "help");

    if (TP->query_wiz_level())
    {
		add_action(union, "union");
		add_action(uupdate, "uupdate");
	    TP->add_prop(FEEL_OFF, 1);
    }
}
