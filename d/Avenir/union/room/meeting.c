/*
 *  Union meeting room.
 *  Created by Cirion
 *
 *  Revisions:
 *    Lucius, Jun 2004: Added a help func for the treaties
 *    Lucius, Feb 2009: Some cleanup, made more things fails when the
 *                      case glass is darkened.
 *    Lucius, Apr 2016: Removed never used Elect code.
 *    Lucius, May 2016: Darken all cases by default initially
 *                      upon reboot.
 *
 */
#pragma strict_types

#include "../defs.h"
#include "/d/Avenir/include/macros.h"

inherit BASE;

#include <math.h>
#include <files.h>
#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#define FPROP   "_union_i_saw_conference_flame"
#define SPROP   "_union_i_found_conference_star"

#undef LOG_CONFERENCES

#define CONFLOG		(GUILDLOG + "conference")
#define LANTHORN	(GUILDLOG + "lanthorn")

#define VALID_SCROLL(who) \
    MEMBER_SPHERES(who, ({ SPH_DIPLOMACY, SPH_VOICE }))

#define TREATY_TITLE	"_Union_treaty_title"
#define TREATY_BODY	"_Union_treaty_body"

#define NAMES ({ "Quenit", "Farros", "Teliat", "Ekcu", "Marshir",    \
                 "Oman", "Ondel", "Apra", "Esqui", "Orin", "Tente",  \
                 "Calaha", "Eston", "Mirhish", "Tenara", "Orcash",   \
                 "Spila", "Turrin", "Fores", "Amas", "Elequit",      \
                 "Endist" })

/* VARG1 lets you pass an argument to your VBFC_ME call */
#define VARG1(x,y)      VBFC((x) + ":" + file_name(TO) + "|" + (y))

/* treaties of form:
 * "title" : ({ "body", date written, voided, ({ signed }), ({ for_who }), darkened })
 */
public mapping treaties = ([]);

#define DARKENED(title)    treaties[title][5]

public void add_treaties_to_room(void);


public int
query_prevent_snoop(void) { return 1; }

public void
union_room(void)
{
    set_short("conference chamber");
    set_long("A massive oval table of burnished dark steel dominates "+
	"the center of this large room. Noises seem to reverberate "+
	"along the walls, making anything spoken seem to echo with "+
	"great significance. The walls are also made from black steel, "+
	"and are covered with tiny etched patterns, thin and obscure "+
	"in meaning. Around the table are @@num_chairs@@ carved ebony "+
	"chairs, with the one at the eastern most end of the table "+
	"being the most ornate. Against the south wall, away from the "+
	"table, @@num_wiz_chairs@@. Behind the ornate ebony chair on "+
	"the east wall rises a huge and dazzling mural of a great, "+
	"deep blue flame, rising up in graceful power and spreading "+
	"along the border between the ceiling and the wall.\n"+
	"@@cases_desc@@");

    // ceiling, star, compass
    add_item(({"ceiling","roof"}), "The ceiling is high and is made "+
	"from light grey stone. Painted on the ceiling and spanning "+
	"its entire area is a large, eight pointed star with a black "+
	"sphere in its center.\n");
    add_item(({"star","compass"}), "The star has eight points, and the "+
	"points that aim in the cardinal directions are longer than "+
	"those in between, making it look like a map compass.\nIn the "+
	"center of the star is a bas relief black sphere.\n");
    add_item(({"sphere","bas relief","black sphere","center of star"}),
	"The sphere in the center of the painted star is in bas " +
	"relief, protruding slightly from the ceiling.\n");
    // flame, mural, east wall
    add_item(({"flame","fire","mural","east wall","painting", "image"}),
	"A beautiful piece of artwork, the mural seems to move as you "+
	"look at it, twisting and wavering about the edge of your "+
	"perception, threatening to envelope you in its strength and "+
	"passion.\n@@flame_effect@@");
    add_item(({"wall","walls"}), "The walls are made from black "+
	"steel, glimmering with tiny pieces of some luminous mineral. "+
	"In the west wall is the outline of a doorway.\n"+
	"Etched in the walls, leading curving paths between the "+
	"mineral shards, are strange and obscure etchings in the "+
	"steel.\n");
    add_item(({"west wall","door","doorway","west", "outline",
	    "the west wall","the door","the doorway","the west"}),
	"The doorway on the west wall is almost perfectly flush with "+
	"the rest of the wall, and you would not be able to "+
	"distinguish its existence if you had not entered by it "+
	"yourself.\n");
    add_item(({"etchings","lines","etching","line","pattern","patterns"}),
	"The etched patterns on the wall trace paths between the "+
	"shards of mineral that provide light for the room. They are "+
	"etched so lightly into the walls that it is difficult to "+
	"follow their trail.\n");
    add_item(({"mineral","shard","shards","piece","pieces"}),
	"The tiny shards of mineral are made from a shiny rock, "+
	"perhaps feldspar, and they each shine with an internal "+
	"flickering light that casts a low, even glow about "+
	"the chamber.\n");
    add_item(({"floor","ground"}),
	"It is made from blocks of dark slate, worn and smooth.\n");
    add_item(({"slate","blocks"}), "They are smooth.\n");
    add_item(({"table","desk"}), "The table is massive, and must "+
	"weigh tons. It is made completely from black melted steel, the "+
	"surface of which is smooth and unbroken. The table stretches "+
	"out in an oval, and around the table are @@num_chairs@@ "+
	"carved chairs.\n@@see_scrolls@@");
    add_item(({"chairs","chair"}),
	"There are simple chairs along the south wall and ornate "+
	"chairs around the table.\n");
    add_item(({"ornate chair", "ornate chairs"}),
	"There are @@num_chairs@@ around the table, with the seat "+
	"at the eastern end of the table being the most ornate.\n"+
	"Inscribed on the backs of each of the chairs are the names: "+
	"@@player_names@@.\n");
    add_item(({"simple chair","simpler chair","simple chairs",
	    "simpler chairs", "south chair","south chairs"}),
	"The chairs against the south wall are simple, as if "+
	"reserved for impartial observers. Inscribed on the backs "+
	"of the chairs are the names: @@wiz_names@@.\n");

    add_cmd_item(({"sphere","bas relief","black sphere","center of star",
	    "the sphere","the bas relief","the black sphere",
	    "the center of star", "star", "compass"}),
	({"push","move","press"}),"You reach up and press the sphere "+
	"in the middle of the star.\nIt moves slightly, and you feel "+
	"vaguely dizzy.\n@@star_effect@@");
    add_cmd_item(({"flame","fire","mural","east wall","painting","image"}),
	({ "feel","touch","push","press","rub" }),
	"The mural feels warm to the touch, and the wall itself feels "+
	"like it is vibrating gently.\n");
    add_cmd_item(({"wall","walls"}),"tap",
	"You tap the wall.\nThe echo reverberates softly, and "+
	"quickly dies down.\n");
    add_cmd_item(({"west wall","door","doorway","west", "outline",
	    "the west wall","the door","the doorway","the west"}),
	({"push","enter"}), "@@west@@");

    add_exit("blue", "west", "@@west_move@@", 1, 1);
    add_exit("lanthorn_room", "east", "@@east_move@@", 1, 1);

    restore_object(SAVINGS + "treaties");
    add_treaties_to_room();
}

public void
add_treaties_to_room(void)
{
    int i = m_sizeof(treaties);

    if (i < 1)
	return;

    /* Here we add all the treaties as items of the room */

    add_item(({ "case","cases" }), "The "
      + (i>1 ? "cases are" : "case is") + " made from "
      + "finished rosewood, smelling of age and darkness, and "
      + "topped with a thin, crystaline pane of glass. The case"
      + (i>1 ? "s are " : " is ")
      + "tilted back at an angle, allowing for the easy reading of "
      + "its contents.\n"
      + (i>1 ? "There are " + LANG_WNUM(i) + " cases arranged against "
	+ "the wall.\n" : ""));

    while(i--)
    {
	string title = m_indexes(treaties)[i];

	/* Make all cases opaque by default.  */
	DARKENED(title) = 1;

	add_item(({LANG_WORD(i+1) +" case", "case "+ ( i+1) }),
	    "The "+ LANG_WORD(i+1) +" case is made from finished "+
	    "rosewood, smelling of age and darkness.\n" +
	    VARG1("darkened_case", title));

	add_cmd_item(({LANG_WORD(i+1) +" case", "case "+ ( i+1) }),
	    "open", "The case is sealed shut.\nYou can copy down the "+
	    "treaty within, however.\n");

	add_cmd_item(({LANG_WORD(i+1) +" case", "case "+ (i+1) }),
	    ({ "break","smash","destroy","wreck" }),
	    "It is impervious to your attempts to destroy it.\n");

	add_item(({LANG_WORD(i+1) +" treaty", "treaty "+ (i+1),
		title }), VARG1("treaty_desc", title));

	add_cmd_item(({LANG_WORD(i+1) + " treaty", "treaty " + (i+1),
		title }), ({ "get", "take" }),
	    "You cannot take it out of the case.\nYou can, however, "+
	    "copy down the parchment onto another scroll.\n");
    }
}

public string
treaty_read(string title)
{
    string str;

    /* Sanity check */
    if (!sizeof(treaties[title]))
	return "";

    if (DARKENED(title))
	return "The glass is opaque; you can see nothing within.\n";

    str = treaties[title][0] + "\n";

    if (!sizeof(treaties[title][3]))
    {
	str += "The treaty is unsigned.\n";
    }
    else
    {
	str += "The treaty has been signed by:\n";
	for(int j = 0; j < sizeof(treaties[title][3]); j++)
	{
	    str += "\t" + treaties[title][3][j] + ", for the " +
		treaties[title][4][j] + "\n";
	}
    }

    return "The parchment reads:\n" + str ;
}

public int
read(string str)
{
    int num;
    string *titles = m_indices(treaties), which = "first";

    if (!strlen(str))
	return NF("Read what?\n");

    if (parse_command(str, ({}), "[the] 'paper' / 'parchment' / 'treaty'"))
	which = "first";
    else if (!parse_command(str, ({}),
	    "[the] %s 'paper' / 'parchment' / 'treaty'", which))
    {
	return NF("Read which treaty?\n");
    }

    num = LANG_NUMW(which);
    if (!num) num = LANG_ORDW(which);
    if (!num) num = member_array(which, titles) + 1;
    if (!num || num > sizeof(titles))
	return 0;

    if (!strlen(which))
	num = 1;

    num--;

    if (query_verb() == "mread")
	TP->more(treaty_read(titles[num]));
    else
	write(treaty_read(titles[num]));

    return 1;
}

public string
darkened_case(string title)
{
    if (!DARKENED(title))
	return "The case contains a piece of parchment.\n";
    else
	return "The glass of the case is darkened and opaque, as "+
	    "if shadows had gathered there and remained.\n";
}

public string
treaty_desc(string title)
{
    if (!DARKENED(title))
    {
	return "The parchment in the case is made from a soft, "+
	    "ivory-shaded paper, upon which words are written in a dark "+
	    "red script.\nThe title at the top of the paper reads: \""+
	    title + "\"\n";
    }
    else
    {
	return "The glass of the case is darkened and opaque, as "+
	    "if shadows had gathered there and remained.\n";
    }
}

public string
cases_desc(void)
{
    int i = sizeof(m_indices(treaties));

    if (i == 0)
    {
	return "";
    }
    else if (i == 1)
    {
	return "Against the east wall is a single case made from "+
	    "rosewood, within which is a parchment.\n";
    }
    else
    {
	return "Against the east wall are " + LANG_WNUM(i) +
	    " rosewood cases, each containing a piece of paper.\n";
    }
}

public void
close_doorway(void)
{
    tell_room(BLUE, "The doorway closes silently and becomes "+
	"flush with the wall.\n");
}

public int
west_move(void)
{
    if (!BLUE->open_exit())
	write("You pass through the open doorway.\n");

    return 0;
}

public int
east_move(void)
{
    /* See if player is anything other than the desired people */
    if (!IS_MEMBER(TP) || !IS_TORNU(TP) || !TP->query_prop(SPROP))
    {
	write("There is no obvious exit east.\n");
	return 1;
    }

    /* Return 0 to allow the player to exit */
    write("You step into the mural of the flame on the east wall.\n");
    SCROLLING_LOG(LANTHORN, CAP(TP->query_real_name()) +
	" accessed the lanthorn room.");

    return 0;
}

public string
see_scrolls()
{
    if (!VALID_SCROLL(TP))
	return "";

    return "Beneath your section of the table is a small shelf, "+
	"on which lies a number of blank scrolls for the purpose of "+
	"making documents.\n";
}

public void
flame_effect2(object who)
{
    who->catch_tell("The image of the flame has left an afterimage "+
	"against your eyes. \nYou seem to see the world differently, "+
	"with a gentle haze that clings over everything.\n");
}

public string
flame_effect(void)
{
    if (!TP->query_prop(FPROP))
    {
	TP->add_prop(FPROP, 1);
	set_alarm(3.0, 0.0, &flame_effect2(TP));
    }

    return "";
}

public void
star_effect2(object who)
{
    who->catch_tell("Through the gentle haze before your eyes "+
	"you notice the mural of the flame swirling open to "+
	"reveal a passage beyond the once-solid east wall.\n");

    if (!TP->query_prop(SPROP))
	TP->add_prop(SPROP, 1);
}

public string
star_effect(void)
{
    if (IS_TORNU(TP) && TP->query_prop(FPROP))
    {
	set_alarm(3.0, 0.0, &star_effect2(TP));
	return "You sense a faint change in air pressure.\n";
    }
    return "";
}

public int
player_members(string str)
{
    if ((SECURITY->query_wiz_level(lower_case(str)))
	|| wildmatch("*jr", str))
	return 0;

    return 1;
}

public string
num_chairs(void)
{
    string *people = LIST->member_list();
    people = filter(people, player_members);
    return LANG_WNUM(sizeof(people));
}

public int
union_wiz(string str)
{
    if (strlen(SECURITY->query_wiz_dom(lower_case(str))))
	return 1;

    return 0;
}

public string
num_wiz_chairs(void)
{
    string *people = LIST->member_list();
    int size = sizeof(people = filter(people, union_wiz));

    if (size < 2)
	return "is one simple wooden chair";

    return "are "+ LANG_WNUM(size) +" simpler wooden chairs";
}

public string
wiz_names(void)
{
    string *people = LIST->member_list();
    return COMPOSITE_WORDS(map(filter(people, union_wiz), capitalize));
}

public string *
translate_names(string *names)
{
    int i, ntor;
    string *nms = NAMES, *new = ({});

    for(i=0;i<sizeof(names);i++)
    {
	if (!sizeof(nms))
	{
	    new += ({ one_of_list(NAMES) });
	    continue;
	}

	ntor = NAME_TO_RANDOM(names[i], 10544, sizeof(nms));
	new += ({ nms[ntor] });
	nms -= ({ nms[ntor] });
    }

    return new;
}

public string
player_names(void)
{
    string *people = LIST->member_list();
    if (IS_MEMBER(TP))
    {
	return COMPOSITE_WORDS(
	    map(filter(people, player_members), capitalize));
    }
    else
    {
	return COMPOSITE_WORDS(translate_names(
		map(filter(people, player_members), capitalize)));
    }
}

public void
sitdown(object who)
{
    set_this_player(who);

    if (who->query_wiz_level())
    {
	write("You take your seat against the south wall.\n");
	say(({ who->query_met_name() + " takes " + HIS(who) +
		" seat against the south wall.\n",
		who->query_nonmet_name() + " takes " + HIS(who) +
	       	" seat against the south wall.\n", ""}));
	return;
    }

#if 0
Elders do not want to be known
	if (IS_ELDER(who))
	{
	    write("You take your seat at the head of the table.\n");
	    say(({ who->query_met_name() + " takes " + HIS(who)
		+ " seat at the head of the table.\n",
		who->query_nonmet_name() + " takes " + HIS(who)
		+ " seat at the head of the table.\n",
		""}));
	    return;
	}
#endif

    if (SPHERE(who) == SPH_VOICE)
    {
	write("You take your seat along the side of the table.\n");
	say(({ who->query_met_name() + " takes " + HIS(who) +
		" seat along the side of the table.\n",
		who->query_nonmet_name() + " takes " + HIS(who) +
		" seat along the side of the table.\n", ""}));
	return;
    }

    write("You sit down on one of the seats around the table.\n");
    say(({ who->query_met_name() + " sits down on one of the "+
	    "seats around the table.\n",
	    who->query_nonmet_name() + " sits down on one of the "+
	    "seats around the table.\n", ""}));
}

public void
enter_inv(object to, object from)
{
    ::enter_inv(to, from);

    if (query_interactive(to))
	set_alarm(1.0, 0.0, &sitdown(to));
}

public void
leave_inv(object to, object dest)
{
    ::leave_inv(to, dest);

    to->remove_prop(FPROP);
    to->remove_prop(SPROP);
    to->remove_prop(TREATY_BODY);
    to->remove_prop(TREATY_TITLE);

    if (query_interactive(to))
	to->catch_tell("You rise from your chair as you leave the room.\n");
}

public int
tablesay(string str)
{
    mixed prop;

    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (prop = TP->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	NF(stringp(prop) ? prop : "You cannot seem to talk.\n");
	return 0;
    }

#ifdef LOG_CONFERENCES
    write_file(CONFLOG, TP->query_name() + ": " + str + "\n");
#endif

    switch(str[-1])
    {
    case '!':
	switch(random(4))
	{
	case 0:
	    write("You "+ one_of_list(({"pound","slam","smash"})) +
		" your fist against the table as you "+
		one_of_list(({"shout","scream","bellow","yell"})) +
		": "+ str +"\n");
	    say(QCTNAME(TP) + " " +
		one_of_list(({"pounds","slams","smashes"})) +" "+
		HIS(TP) +" fist against the table as "+ HE(TP) + " " +
		one_of_list(({"shouts","screams","bellows","yells"})) +
		": "+ str +"\n");
	    break;

	case 1:
	    write("You jump up from your chair and "+
		one_of_list(({"shout","scream","bellow","yell"})) +
		": " + str + "\n");
	    say(QCTNAME(TP) + " jumps up from " + HIS(TP) +" chair and "+
		one_of_list(({"shouts","screams","bellows","yells"})) +
		": "+ str +"\n");
	    break;

	default:
	    write("You "+
		one_of_list(({"shout","scream","bellow","yell"})) +
		": "+ str +"\n");
	    say(QCTNAME(TP) +" "+
		one_of_list(({"shouts","screams","bellows","yells"})) +
		": "+ str +"\n");
	    break;
	}
	break;

    case '?':
	write("You "+
	    one_of_list(({"query","wonder","ponder","question"})) +
	    ": "+ str +"\n");
	say(QCTNAME(TP) +" "+
	    one_of_list(({"queries","wonders","ponders","questions"})) +
	    ": "+ str +"\n");
	break;

    default:
	return 0;
    }

    return 1;
}

public int
compose(string str)
{
    if (str != "treaty")
	return NF("You may only compose treaties.\n");

    write("You take out a piece of paper and begin to compose.\n");
    say(QCTNAME(TP) +" takes out a piece of paper and begins writing.\n");

    write("What is the title of this treaty: ");
    input_to("treaty_title");
    return 1;
}

public int
register_treaty(string title, string body)
{
    if (sizeof(treaties[title]))
	return 0;

    treaties += ([ title : ({ body, time(), 0, ({ }), ({ }), 0 }) ]);
    save_object(SAVINGS + "treaties");

    /* update the objects in the room */
    add_treaties_to_room();
}

public object
copy_treaty(string str)
{
    object scroll = clone_object(OBJ + "treaty");
    scroll->set_treaty_title(str);
    return scroll;
}

public int
copy(string str)
{
    if (!strlen(str))
	return NF("Copy down which treaty?\n");

    if (!sizeof(treaties[str]))
	return NF("There is no treaty by that name.\n");

    if (DARKENED(str))
    {
	write("The glass is too occluded to allow for that.\n");
	return 1;
    }

    if (copy_treaty(str)->move(TP, 1))
    {
	write("You failed for some reason.\n");
	return 1;
    }

    write("You copy down the treaty titled \"" + str + "\"\n");
    say(QCTNAME(TP) + " copies down a treaty.\n");
    return 1;
}

public int
touch(string str)
{
    int dark, num;
    string *titles = m_indices(treaties), which;

    if (!strlen(str) || !present(TOKEN_ID, TP))
	return NF("Touch what?\n");

    if (!parse_command(str, ({}),
	"[my] / [the] 'sphere' 'to' [the] [glass] [of] [the] %s 'case'",
	which))
	return NF("Touch what?\n");

    if (!strlen(which))
	which = "first";

    num = LANG_NUMW(which);
    if (!num) num = LANG_ORDW(which);
    if (!num) num = member_array(which, titles) + 1;

    if (!num || num > sizeof(titles))
    {
	write("Touch your sphere against which case?\n");
	return 1;
    }

    num--;
    dark = DARKENED(titles[num]);

    if (!dark)
    {
	write("You touch your sphere against the glass and it "+
	    "goes opaque.\n");
	say(QCTNAME(TP) + " touches " + HIM(TP) + " sphere against the "+
	    "glass of one of the cases, and the glass suddenly fades to "+
	    "midnight black.\n");
    }
    else
    {
	write("You touch your sphere against the glass and it suddenly "+
	    "becomes clear.\n");
	say(QCTNAME(TP) +" touches "+ HIS(TP) +" sphere against "+
	    "the glass of one of the cases, and the glass suddenly turns "+
	    "crystal clear.\n");
    }

    DARKENED(titles[num]) = !dark;
    return 1;
}

public mixed
query_treaty(string str)
{
    return treaties[str];
}

public void
treaty_title(string str)
{
    if (!strlen(str) || str == "~q")
    {
	TP->remove_prop(TREATY_BODY);
	TP->remove_prop(TREATY_TITLE);
	write("You stop writing the treaty.\n");
	say(QCTNAME(TP) + " stops writing.\n");
	return;
    }

    if (query_treaty(str))
    {
	write("There is already a treaty titled \"" + str + "\"\n"+
	    "You must either choose a different name, or destroy the "+
	    "current treaty first.\n");
	return;
    }

    TP->add_prop(TREATY_TITLE, str);

    write("Enter the body of the treaty (** to finish, ~q to abort):\n");
    write("] ");
    input_to("write_treaty");
}

public void
write_treaty(string str)
{
    object scroll;

    if (!str)
	str = "";

    if (str == "~q")
    {
	TP->remove_prop(TREATY_BODY);
	TP->remove_prop(TREATY_TITLE);
	write("You stop writing the treaty.\n");
	say(QCTNAME(TP) + " stops writing.\n");
	return;
    }

    if (str != "**")
    {
	if (TP->query_prop(TREATY_BODY))
	    TP->add_prop(TREATY_BODY, TP->query_prop(TREATY_BODY) + str + "\n");
	else
	    TP->add_prop(TREATY_BODY, str + "\n");

	add_prop(ROOM_I_HIDE, -1);

	write("] ");
	input_to("write_treaty");
	return;
    }

    register_treaty(TP->query_prop(TREATY_TITLE),
	TP->query_prop(TREATY_BODY));

    write("You complete the treaty titled \"" +
	TP->query_prop(TREATY_TITLE) + "\"\n");
    say(QCTNAME(TP) + " finishes writing.\n");

    scroll = copy_treaty(TP->query_prop(TREATY_TITLE));

    if (!scroll->move(TP))
	write("You take up the treaty.\n");
    else
	scroll->remove_object();
}

public string *
all_guilds(object who)
{
    return filter(({
	    who->query_guild_name_occ(),
	    who->query_guild_name_lay(),
	    who->query_guild_name_race(),
	    who->query_guild_name_craft()
	    }), strlen);
}

public int
sign(string str)
{
    string *sigs, treaty, for_who;

    if (!strlen(str))
	return NF("Sign what?\n");

    if (str == "treaty")
    {
	write("You will need to specify which treaty you will sign.\n");
	return 1;
    }

    treaty = str;
    parse_command(str, ({}), "%s 'for' %s", treaty, for_who);

    if (!strlen(treaty) || !sizeof(treaties[treaty]))
    {
	write("There is no treaty by that name.\n");
	return 1;
    }

    if (DARKENED(treaty))
    {
	write("The glass is too occluded to allow for that.\n");
	return 1;
    }

    if (member_array(TP->query_name(), treaties[treaty][3]) != -1)
    {
	write("You have already signed that treaty.\n"+
	    "You cannot do so twice.\n");
	return 1;
    }

    if (!strlen(for_who))
    {
	write("You will need to sign the treaty as a representative "+
	    "of a certain group. Possible groups for you are: " +
	    COMPOSITE_WORDS(all_guilds(TP)) + ".\n");
	return 1;
    }

    if (member_array(for_who, all_guilds(TP)) == -1)
    {
	write("You are not a member of the " + for_who + ".\n");
	write("Possible groups for you are: " +
	    COMPOSITE_WORDS(all_guilds(TP)) + ".\n");
	return 1;
    }

    treaties[treaty][3] += ({ TP->query_name() });
    treaties[treaty][4] += ({ for_who });
    save_object(SAVINGS + "treaties");

    write("You sign the treaty titled \"" + treaty + "\"\n");
    say(QCTNAME(TP) + " signs the treaty titled \"" + treaty + "\"\n");
    return 1;
}

public int
destroy(string str)
{
    if (!strlen(str))
	return NF(CAP(query_verb()) + " which treaty?\n");

    if (!sizeof(treaties[str]))
    {
	write("There is no treaty by that title you may remove.\n");
	return 1;
    }

    if (DARKENED(str))
    {
	write("The glass is too occluded to allow for that.\n");
	return 1;
    }

    m_delkey(treaties, str);
    save_object(SAVINGS + "treaties");
    add_treaties_to_room();

    write("You remove the treaty \"" + str + "\" forever.\n");
    return 1;
}

public int
list(string str)
{
    if (str != "treaties")
	return notify_fail("List what?\n");

    if (!m_sizeof(treaties))
    {
	write("No treaties have been written.\n");
	return 1;
    }

    write("The following treaties have been written here:\n");
    foreach(string name : m_indexes(treaties))
	write("\t" + name + "\n");

    return 1;
}

/*
 * Function name:  help_here
 * Description:    Provide help for the functions in this room
 */
public int
help_here(string str)
{
    if (!strlen(str))
	return notify_fail("Help what? Help treaty?\n");

    if (!IN_ARRAY(str, ({ "treaty", "treaties", "case", "here" })))
	return notify_fail("Help what? Help treaty?\n");

    write("The following commands relate to any treaties and their "+
      "cases:\n\n"+
      "    list   List the treaties in currently in force.\n"+
      "    read   You can read treaty, first treaty, second treaty\n"+
      "             etc. If the glass is opaque, you should try using\n"+
      "             touch, below.\n"+
      "    mread  Same as 'read', except using more.\n"+
      "    sign   You can <sign 'treaty name' for 'guild name'>.\n"+
      "    copy   You can make a copy of a specific treaty using its\n"+
      "             name, ie <copy Pax Verax>.\n"+
      "    touch  You can clear the opaque glass using <touch sphere\n"+
      "             to 'first' case> where 'first' is the number of the\n"+
      "             case you want to be able to see into.\n");

    if (VALID_SCROLL(TP))
    {
	write("\nIn addition, due to your Sphere,"+
	  " may access the following commands:\n\n"+
	  "     compose  You can use <compose treaty> to write a new treaty.\n"+
	  "     destroy  Remove a treaty using <remove 'treaty name'>\n"+
	  "                where 'treaty name' is the name of the treaty\n"+
	  "                as printed using <list treaties>.\n");
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(tablesay, "say");
    add_action(tablesay, "us");
    add_action(tablesay, "usay");

    add_action(read, "read");
    add_action(read, "mread");
    add_action(sign, "sign");

    if (IS_MEMBER(TP) || IS_GMASTER(TP))
    {
	add_action(copy, "copy");
	add_action(list, "list");
	add_action(touch, "touch");
	add_action(help_here, "help");
    }

    if (VALID_SCROLL(TP))
    {
	add_action(compose, "compose");
	add_action(destroy, "destroy");
    }
}
