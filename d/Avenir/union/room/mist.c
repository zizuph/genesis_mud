#pragma strict_types
/*
 * - /d/Avenir/union/room/mist.c
 *
 * The board room for the mentors of the Shadow Union.
 *
 * Revisions:
 *   Lucius, Oct 2005: Increased tell-time delay, modified clear command
 *           to work on single type restrictions.
 *
 *   Lucius, Apr 2009: Clarified logging on restricions + cleanups.
 *   Lucius, Apr 2009: Corrected mistake in permissions checking.
 *   Lucius, Jul 2011: Modified logging bits.
 *   Lucius, Apr 2016: Modified room_tell bits.
 *                     Changed access to allow all Active Warriors
 *                     read-only access.
 *   Lucius, Jun 2016: Modified to use a new library base.
 *   Lucius, Apr 2018: Gave Voice same access as Mentors.
 */
#include "../defs.h"

inherit BASE;
inherit (LIB + "library");

inherit "/d/Avenir/inherit/tail";
inherit "/d/Avenir/inherit/room_tell";

#include <math.h>

private string *phrases = ({
    "Those who teach, learn much in return.",
    "To indoctrinate without discouraging: that is the challenge "+
	"of mentoring.",
    "You are the future of the Union, for tomorrow's Warriors "+
    "know the touch of your hand more than any other.",
    "If you would harness the spirit of a creature, take care you "+
    "do not turn it into a beast of burden.",
    "With firmness and eloquence shall we train our Novices.",
    "If you would learn what must be taught,\nlisten to those whom "+
	"you would teach.",
    "Foster enthusiasm, joy, and delight! The spirit of a\n"+
	"Warrior should burn bright in its cloak of Shadows.",
    "Amongst the Hopefuls are nascent Warriors to be guided "+
	"through parturition.",
    "Let not your fears prevent you from pursuing Jazur's Will.",
    "If one cannot do great things,\none can do small things in a "+
	"great way.",
    "Of our novices demand excellence, not perfection.\n"+
	"Perfection comes in its own time.",
    "The mantle of Jazur's grace rests upon your shoulders.\nGo "+
	"forth and teach those who would learn Our ways.",
    "Which is the greater loss to Jazur? For a Novice to try to\n"+
	"become a Warrior and fail, or for you to fail to recognize\n"+
	"a Hopeful who would have become great Warrior?",
});

private int words = random(sizeof(phrases));


public void
union_room(void)
{
    set_short("place of parturient mist");
    set_long("Mist curls about the room, and where it touches "+
	"the polished granite walls, becomes glistening vapour "+
	"which soon transmutes again into mist. A narrow set "+
	"of shelves has been cut into one wall, upon which rests "+
	"various slender volumes. Hanging just above the shelves "+
	"is a small sign. Letters have been posted to "+
	"a large book standing on a pedestal nearby.\n");

    add_item(({"word","words","wall","inscription",
	    "inscriptions","phrases"}),
	"One of the phrases reads:\n@@words@@");
    add_item(({"wall","walls","granite"}),
	"The walls are of polished granite, glistening with "+
	"moisture.\nAll along the walls are tiny inscriptions "+
	"engraved in elegant script.\n");

    add_cmd_item(({"wall","walls","granite"}),({"touch","feel"}),
	"The granite is smooth to the touch.\n");
    add_cmd_item(({"board"}),({"touch","feel"}),
	"It is rough and hard, covered with many spidery scrawlings.\n");
    add_cmd_item(({"word","words","wall","inscription",
	    "inscriptions","phrases"}),
	"read","One of the phrases reads:\n@@words@@");

    /* Add a sign that gives instructions on how to use the library */
    add_item("sign", library_help);
    add_cmd_item("sign","read", library_help);
    add_item(({"bookshelves","bookshelf","stone bookshelves", "shelves"}),
	"They are carved into the stone. They contain a collection "+
	"of letters to be used to communicate with Hopefuls, Accepted "+
	"and Trainees. Mysteriously enough, they seem to be impervious "+
	"to the dampness that pervades this room. Above the shelves is "+
	"posted a sign that reads:\nYou do not have to borrow the books "+
	"inorder to read them.\n@@library_help@@\n");
    add_item("letters", "You can learn more about them using <exa book>\n");

    set_tell_time(600 + random(300));
    add_tell("@@words@@");

    add_exit("novlib0", "east");

    add_object(OBJ +"mboard");

    set_library_save_path(LIBSAVE + "mentor/");
    set_library_save_file(LIBSAVE + "mentor/data");
    set_library_log_file(LIBSAVE + "mentor/log");

    set_library_book_object(LIB + "book");

    add_library_access_level( "member", "Amlis'k'mia" );
    add_library_access_level(  "admin", "Mentors"     );

    set_library_librarian_level("admin");
    set_library_new_book_shelf("pending");

    set_library_allow_new_books(1);
    set_library_allow_edit_direct(1);
    set_library_allow_read_direct(1);

    set_library_cmd_prefix("u");

    create_library();
}

#ifdef UOPT_RMTXT
public int
skip_room_tells(object who)
{
    return !LIST->query_union_option(who, UOPT_RMTXT);
}
#endif

public string
words(void)
{
    if (++words >= sizeof(phrases))
	words = 0;

    return phrases[words] +"\n";
}

private int
help(string str)
{
    str = "Library: for help with the library functions, try <exa sign>.\n\n"
    + "Ceremony of Naming: requires that the person to be Named must "
    + "be bathed and must be clothed in the garb of the Union (cape, "
    + "boots, veil, and shirt).\n"
    + "To begin the Ceremony, you must be at the Flame and use the "
    + "command:\n  <cname on who>.\n"
    + "Once you have done that, you can use <help ceremony> for more info.\n\n"
    + "Warrior commands available in this room are:\n"
    + " check    <who>        - Check novice restrictions\n"
    + " level    <who>        - Check novice current library level\n\n";

    if (MEMBER_SPHERES(TP, ({ SPH_VOICE, SPH_MENTOR })))
    {
	str += "Mentor commands available in this room are:\n"
	+ " restrict <who> <how>  - Restrict novice access\n"
	+ " clear    <who> <how>  - Clear restrictions\n"
	+ " grant    <who> <#>    - Grant library access by level\n\n"
	+ " logview               - Review the Mentor log\n\n";
    }

    write(str);
    return 1;
}

private void
mistlog(string str)
{
    LOG_MENTOR(str);
}

private int
log_view(string str)
{
    if (file_size(MENTOR_LOG) < 1)
    {
	write("The Mentor log appears to be empty.\n");
	return 1;
    }

    write("//*********[  You begin viewing the Mentor log  ]*********\\\\\n\n");
    tail_file(MENTOR_LOG);
    return 1;
}

static nomask int
query_nov_restrict(string str)
{
    string name, *result;

    if (!strlen(str))
	return notify_fail("Check <who>?\n");

    name = lower_case(str);
    result = LIST->sphere_members()["training"];

    if (member_array(name, result) == -1)
	return notify_fail(capitalize(name) +" is not in training.\n");

    result = LIST->query_union_punished_strings(name);
    if (!sizeof(result))
    {
	write(capitalize(name) +" has no restrictions.\n");
	return 1;
    }

    write(sprintf("%15s: %-#60.1s\n",
	capitalize(name), implode(result, "\n")));

    return 1;
}

static nomask int
restrict_nov(string str)
{
    object who;
    int p_type;
    string name, type, *sph, *args, *types;


    if (!strlen(str))
	str = " ";
    else
	str = lower_case(str);

    args = explode(str, " ");

    /* Did we enter the right args? Is           */
    /* the level specified valid?   */
    if (sizeof(args) != 2 || !U_PUNISHED_TYPE[args[1]])
    {
	write("Restrict <who> to from <what>?\n"+
	    "Possible restrictions are:\n");

	types = m_indices(U_PUNISHED_TYPE);

	for(int i = 0; i < sizeof(types); i++)
	{
	    type = types[i];

	    /* U_PUNISHED_TYPE gives the description of the punishment */
	    /* e.g., "may not enter the halls of the Union"            */
	    write(sprintf("%12s : %s", type, "Subject "+
		    U_PUNISHED_STR[U_PUNISHED_TYPE[type]] + "\n"));
	}

	write("\nNote that restrictions are additive, in that a subject "+
	    "can have more than one restriction at any time.\n");

	return 1;
    }

    name = lower_case(args[0]);
    type = args[1];
    p_type = U_PUNISHED_TYPE[type];

    if (name == TP->query_real_name())
	return NF("You may not restrict yourself, silly.\n");

    if (U_IS_PUNISHED(name, p_type))
	return NF("That person is already under that restriction.\n");

    sph = LIST->sphere_members()["training"];
    if (member_array(name, sph) == -1)
	return NF("That person is not in training.\n");

    if (!(LIST->add_union_punishment(name, p_type)))
	return NF("Something goes wrong! Please leave a bug report.\n");

    mistlog(NM(TP) + " restricted " + CAP(name) + ": \"" + type + "\"");
    write(CAP(name) + " restricted: " + U_PUNISHED_STR[p_type] + ".\n");

    return 1;
}

static nomask int
clear_nov(string str)
{
    int type;
    string name, *sph, *args;

    str = lower_case(str);

    if (!strlen(str))
	return NF("Clear what restriction(s) on whom?\n");

    args = explode(str, " ");
    if ((sizeof(args) != 2) || !(U_PUNISHED_TYPE[args[1]] || args[1] == "all"))
    {
	int i, *types;

	write("Clear who <type of restriction | all>?\nPossible forms of "
	  + "restrictions to clear are:\n");

	types = m_indices(U_PUNISHED_TYPE);

	for(i=0;i<sizeof(types);i++)
	{
	    type = types[i];

	    /* U_PUNISHED_TYPE gives the description of the punishment */
	    /* e.g., "may not enter the halls of the Union"            */
	    write(sprintf("%12s : %s", type, "Subject "
		+ U_PUNISHED_STR[U_PUNISHED_TYPE[type]] + "\n"));
	}

	write("\nNote that restrictions are additive, in that a subject "
	  + "can have more than one type of restriction at any time. "
	  + "Consequently, removing only one type of restriction will "
	  + "leave any other restrictions intact.\n");

	return 1;
    }

    name = lower_case(args[0]);
    sph = LIST->sphere_members()["training"];
    type = U_PUNISHED_TYPE[args[1]];

    if (member_array(name, sph) == -1)
	return NF("That person is not in training.\n");

    if (!U_PUNISHED_LEVEL(name))
	return NF("That person is not under restriction.\n");

    if (type && !U_IS_PUNISHED(name, type))
	return NF("That person is not under that restriction.\n");

    if (!(LIST->remove_union_punishment(name, type)))
	return NF("Something goes wrong! Please leave a bug report.\n");

    mistlog(NM(TP) + " removed restriction " +
      CAP(name) + ": \"" + args[1] + "\"");

    write(CAP(name) + " restriction removed: " +
      (type ? U_PUNISHED_STR[type] : "All restrictions") + ".\n");

    return 1;
}

static nomask int
grant_nov(string str)
{
    int type;
    object who;
    string name, *sph, *args, *types;


    if (!strlen(str))
	str = " ";
    else
	str = lower_case(str);

    args = explode(str, " ");

    /* Did we enter the right args? Is */
    /* the level specified valid?   */
    if (sizeof(args) != 2)
    {
	write("Grant <who> <level #>? There are 5 levels to the "+
	  "novice library.\n");
	return 1;
    }

    name = lower_case(args[0]);
    sscanf(args[1], "%d", type);;

    if (name == TP->query_real_name())
	return NF("You already have access, silly.\n");

    sph = LIST->sphere_members()["training"];
    if (member_array(name, sph) == -1)
	return NF("That person is not in training.\n");

    if (type < 0 || type > 6)
    {
	write("Specify a value from 0 to 6.\n");
	return 1;
    }

    if (type == 0)
    {
	LIST->remove_nov_lvl(name);
	mistlog(NM(TP) + " cleared library access for " + CAP(name));
	write(CAP(name) + "'s novice library access is cleared.\n");
	return 1;
    }

    if (!(LIST->add_nov_lvl(name, type)))
	return NF("Something goes wrong! Please leave a bug report.\n");

    mistlog(NM(TP) + " granted " + CAP(name) + " library level: " + type);
    write(CAP(name) + " granted access to library level "+ type +".\n");
    LIST->add_union_message(name, "You have been granted access to "+
      "another level of the library.\n");

    return 1;
}

static nomask int
query_nov_level(string str)
{
    string    name, result;
    string   *sph;

    if (!strlen(str))
	return notify_fail("Check <who>?\n");

    name = lower_case(str);

    sph = LIST->sphere_members()["training"];
    notify_fail(capitalize(name) +" is not in training.\n");
    if (member_array(name, sph) == -1)
	return 0;

    result = LIST->query_nov_lvl(name);
    if (!result)
    {
	notify_fail(capitalize(name) +" has no access.\n");
	return 0;
    }

    write(capitalize(name) + " has access to level: " + result + "\n");
    return 1;
}

public void
init(void)
{
    ::init();

    /* Add the library commands */
    init_library();

    add_action(query_nov_restrict, "check");
    add_action(query_nov_restrict, "sucheck");
    add_action(query_nov_level,    "level");
    add_action(query_nov_level,    "sulevel");
    add_action(help,               "help");
    add_action(help,               "suhelp");

    /* Restrict access. */
    if (!MEMBER_SPHERES(TP, ({ SPH_VOICE, SPH_MENTOR })))
	return;

    add_action(restrict_nov, "restrict");
    add_action(restrict_nov, "surestrict");
    add_action(clear_nov,    "clear");
    add_action(clear_nov,    "suclear");
    add_action(grant_nov,    "grant");
    add_action(grant_nov,    "sugrant");
    add_action(log_view,     "logview");
}

public int
query_librarian(object who)
{
    /* Mentors, Elders and GM's. */
    if (MEMBER_SPHERES(who, ({ SPH_VOICE, SPH_MENTOR })))
	return 1;

    return 0;
}

public string *
query_player_access(object who)
{
    /* Mentors, Elders and GM's. */
    if (query_librarian(who))
	return ({ "member", "admin" });

    /* If the player is punished with "noarchives", prevent
     * him from making use of this library.  */
    if (U_IS_PUNISHED(who, U_PUNISHED_LIBRARY))
	return ({ });

    /* Warriors. */
    if (IS_MEMBER(who))
	return ({ "member" });

    return ({ });
}

public void
library_configure_book(object book, string book_id)
{
    ::library_configure_book(book, book_id);

    if (!strlen(book_id))
	return;

    string *adjs = ({ "slender", "fragile", "shadowy"});
    int index, sz = sizeof(adjs);
    string adj, nm = book->query_title();

    // parse out spaces: name_to_random will choke on them
    nm = implode(explode(nm, " "), "");
    index = NAME_TO_RANDOM(nm, 13254, sz);

    // I am not confident that NAME_TO_RANDOM is reliable (I have
    // seen it return random numbers!). So I will do my own sanity
    // checking.
    if ((index >= 0) && (index < sizeof(adjs)))
	adj = adjs[index];
    else
	adj = adjs[random(sz)];

    book->add_adj(adj);
    book->set_short(adj + " book");
    book->set_long("This book is a part of the Mentor's library.\n"+
      "Along the spine is writ the following: "+ book->query_title() +
      ".\n");
}

public void
leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

/* Start the room tells as soon as someone enters the room */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
}
