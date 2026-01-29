/*
 * - /d/Avenir/union/room/council.c
 *
 * Council chambers for the Union of the Warriors of
 * Shadow. Contains the code for the council log book,
 * banishing players, etc.
 *    Cirion, May Morning, 1996
 *
 * Revisions:
 *    Lilith, Apr 2003: Updated help info
 *    Lilith, Sep 2003: remove-curse ability, ability to send visions
 *            -thanks to Mercade for creating the lfun copy_file() :)
 *    Lilith, Jun 2004: Made it so unifidel lifts more levels of infidel
 *                      Updated help info for clarification
 *    Lucius, Unknown:  Updated reprieve to allow for single-types.
 *    Lucius, Unknown:  Cleanups, removed (illegal) access to logs.
 *    Lucius, Unknown:  Fixed a bug in promtion, query_elders()->elder_list()
 *    Lucius, Jul 2011: Added block/unblock, many cleanups and
 *                      changes to logging bits.
 *    Lucius, Apr 2016: Removed never used Elect code.
 *    Lucius, May 2016: Code cleanups. Added union texts handling.
 *                      Removed 'reassign', this is in the elder soul.
 *                      Removed hopeful/unhopeful, they are in the post.
 *    Lucius, Jun 2016: Added library.
 *    Lucius, Jun 2017: Visions completely re-done.
 *    Lilith, Apr 2022: Added expunge to allow removal of names from 
 *                        the 'Named' list.
 *
 */
#pragma no_shadow
#pragma no_inherit
#pragma strict_types
#include "../defs.h"

inherit BASE;
inherit (LIB + "library");
inherit (LIB + "visions");
inherit "/d/Avenir/inherit/tail";

#include <math.h>
#include <files.h>
#include <macros.h>
#include <language.h>
#include <composite.h>
#include <stdproperties.h>


/* Not a big enough population to require more than 3. */
#define MAX_ELDERS  3

private mapping prop_map = ([
  "restrict"   : ({ "lock_doors", 1,
    "restrict access to the union hall to members and friends only"
  }),
  "unrestrict" : ({ "lock_doors", 0,
    "allow outsiders access to the union guild hall"
  }),
]);

private mapping punished_str  = U_PUNISHED_STR,
	        punished_type = U_PUNISHED_TYPE;


public nomask int
query_prevent_snoop(void)	{ return 1; }

static void
union_room(void)
{
    set_short("shadow-draped chamber");
    set_long("A high-ceilinged chamber draped in shadows "
      +"that seem to draw near you as moths to a flame. "
      +"Here the link with the Union feels very strong, "
      +"you can almost sense the presence of Warriors long "
      +"dead. Your ears strain to hear the nearly soundless "
      +"whispering which seems to ebb and flow, echos "
      +"from the past whose words are unintelligible "
      +"but whose voices seem oddly familiar. Your skin "
      +"prickles constantly with the awareness of the "
      +"supernatural presences surrounding you, observing "
      +"your every move.\nThe room itself is somewhat stark "
      +"but not uncomfortable, furnished as it is with "
      +"stone benches and a small, marble-topped table. "
      +"A sybarun carpet covers the floor, and there is "
      +"an opening in the north wall through which a "
      +"yellow glow can be seen. Above the opening a "
      +"long list has been engraved into the stone, "
      +"and a small painted sign has been hung on the "
      +"western wall. A bronzed plaque has been placed "
      +"on the south wall, near some bookshelves. ");

    add_item(({"shadow","shadows","presence", "presences"}),
      "The shadows press in from everywhere, mingling with the "
      +"light. You sense they are curious and concerned.\n");
    add_item(({"glow", "yellow glow", "opening", "north wall"}),
      "Looking through the opening, a source of light and warmth, "
      +"you can see the molten floor of the chasm far below. "
      +"Just east you can see the overhang which warriors cross "
      +"to reach the stairs down to the sea.\n");
    add_item(({"carpet", "thick carpet", "sybarun carpet"}),
      "This is a thick carpet, woven from the wool of the "
      +"sybarun goat. It has been dyed a dark blue which "
      +"closely resembles the colour of Jazur's Flame. This "
      +"expensive luxury would seem incongruous in the stark "
      +"room, were it not for the fact it is without any "
      +"decoration or adornment, not even fringe.\n");
    add_item(({"peephole", "hole"}),
      "It is a hole in the door that will allow you to look "
      +"into the other room before leaving this one. Try "
      +"<peep through hole>.\n");
    add_item(({"list","members","member list","list of members",
	"wall"}), "@@memberlist@@");

    add_cmd_item(({"members","list","member list","list of members",
	"north wall"}), "read", "@@memberlist@@");
    add_item(({"sign", "west wall", "western wall", "painted sign",
	"small sign", "small painted sign"}), "@@read_help@@");
    add_cmd_item(({"sign", "west wall", "western wall", "painted sign",
	"small sign", "small painted sign"}), "read", "@@read_help@@");

    add_exit("post2", "post");

    add_prop(ROOM_M_NO_SCRY, 1);

    add_object(OBJ + "cboard");
    add_object(OBJ + "c_door_w");

    set_library_save_path(LIBSAVE + "elder/");
    set_library_save_file(LIBSAVE + "elder/data");
    set_library_log_file(LIBSAVE + "elder/log");

    set_library_book_object(LIB + "book");

    add_library_access_level("admin", "Flari");

    set_library_librarian_level("admin");
    set_library_new_book_shelf("pending");

    set_library_allow_new_books(1);
    set_library_allow_edit_direct(1);
    set_library_allow_read_direct(1);

    set_library_cmd_prefix("u");

    create_library();

    /* Add a sign that gives instructions on how to use the library */
    add_item(({"plaque","bronze plaque"}), library_help);
    add_cmd_item(({"plaque","bronze plaque"}), "read", library_help);
    add_item(({"shelves","bookshelves","book shelves","south wall"}), 
      "Against the south wall are bookshelves constructed from "+
      "solid and dark kesoit wood native to Sybarus. You should "+
      "read the nearby plaque for instructions on how to use them.\n");
}

private void
clog(string str)
{
    LOG_COUNC(str);
}

private int
gmaster(mixed who)
{
    return LIST->gmaster(who);
}

private int
guild_prop(string str)
{
    string verb = query_verb();
    mixed *attrs = prop_map[verb];

    if (!sizeof(attrs))
    {
	notify_fail(capitalize(verb) + " what?\n");
	return 0;
    }

    LIST->guild_add_prop(attrs[0], attrs[1]);
    write("You " + attrs[2] + ".\n");
    return 1;
}

private int
help(string str)
{
    write("The following council commands are available here.\nIn the event "
      + "of conficting commands, try using 'su' before the word:\n"
      + "  list       <what>      - Lists members, accepted people, etc.\n"
      + "  accept     <who>       - Accept someone as worthy of the Union\n"
      + "   unaccept  <who>       - Take someone off the accepted list\n"
      + "  promote    <who>       - Promote someone to Elder rank\n"
      + "   demote    <who>       - Demote someone from the Elder council\n"
      + "  expel      <who>       - Expel someone from the Union\n"
      + "   unexpel   <who>       - Take someone off the pending Expel list\n"
	  + "  expunge    <who>       - Forever purge someone's essence from the Flame\n"
      + "  block      <who>       - Declare someone Persona Non Grata\n"
      + "   unblock   <who/guild> - Forgive someone from being Persona Non Grata\n"
      + "  enemy      <who>       - Declare someone as an enemy of the Union\n"
      + "   unenemy   <who/guild> - Take someone off Union enemy list and lift curse\n"
      + "   uninfidel <who>       - Remove Sybarus infidel status and lift curse\n"
      + "  ally       <guild>     - Declare a certain guild to be allies of the Union\n"
      + "  condemn    <guild>     - Declare a certain guild as enemies of the Union\n"
      + "  unwelcome  <guild>     - Declare a certain guild as Personae Non Gratae\n"
      + "  friend     <who>       - Declare someone as a friend of the Union\n"
      + "   unfriend  <who/guild> - Take someone off the ally list\n"
      + "  punish     <who> <how> - Punish a member of the Union\n"
      + "   reprieve  <who> <how> - Lift someone's punishment\n"
      + "  restrict               - Disallow access to the guild hall by Outsiders\n"
      + "   unrestrict            - Allow outsiders access to the guild hall\n"
      + "  vision    <who> <what> - Send visions in the Sway to one, a sphere or all\n"
      + "  msg       <who> <what> - Send a short login message to one or all\n"
      + "  logview   <log>        - Review the logfile <log>\n"
      + "  sutext    <cmd> [arg]  - View or Modify Union text blocks\n"
      + "\n   Former members who have left the guild voluntarily can enter the\n"
      + "   Halls if made a <friend>; they can also join again if <accepted>.\n");
    return 1;
}

/*
 * For VBFC
 */
public string
read_help(void)
{
    help("");
    return "";
}

private int
valid_list(string str)
{
    /* Wizards will see everyone listed */
    if (TP->query_wiz_level())
	return 1;

    str = lower_case(str);

    /* Else filter out Jrs and wizards */
    if (extract(str, -2) == "jr")
	return 0; // Don't list wizard's juniors

    if (SECURITY->query_wiz_level(str))
	return 0; // Or wizards

    return 1;
}

private int
list(string str)
{
    int flag = 0;
    string head = "", *names = ({});

    switch(str)
    {
    case "members":
	head = "The following are members of the Union";
	names = filter(LIST->member_list(), valid_list);
	break;
    case "elders":
	head = "The Elders of the Union are";
	names = filter(LIST->elder_list(), valid_list);
	break;
    case "accepted":
	head = "The following are worthy of acceptance into the Union";
	names = filter(LIST->accepted_list(), valid_list);
	break;
    case "hopeful":
	head = "The following are recognized as Union Hopefuls";
	names = filter(LIST->hopeful_list(), valid_list);
	break;
    case "friends":
	head = "The following are declared Allies of the Union";
	names = filter(LIST->friend_list(), valid_list);
	break;
    case "blocked":
	head = "The following are declared Persona Non Grata";
	names = filter(LIST->blocked_list(), valid_list);
	break;
    case "enemies":
	head = "The following are Enemies of the Union";
	names = filter(LIST->enemy_list(), valid_list);
	break;
    case "expelled":
	head = "The following shall be expelled from the Union";
	names = filter(LIST->expel_list(), valid_list);
	break;
    case "punished":
	flag |= 1;
	head = "The following are currently being punished";
	names = filter(LIST->punish_list(), valid_list);
	break;
    case "guilds":
	flag |= 2;
	head = "The following guilds are recognized";
	names = LIST->query_all_major_guilds_sorted();
	break;
    case "enemy guilds":
	flag |= 2;
	head = "The following guilds are Enemies of the Union";
	names = LIST->enemy_guild_list();
	break;
    case "blocked guilds":
	flag |= 2;
	head = "The following guilds are Persona Non Grata";
	names = LIST->blocked_guild_list();
	break;
    case "allied guilds":
	flag |= 2;
	head = "The following guilds Allies of the Union";
	names = LIST->friend_guild_list();
	break;
    default:
	notify_fail("List what? Possible options are: members, elders, "+
	  "accepted, hopeful, friends, blocked, enemies, punished, "+
	  "expelled, guilds, blocked guilds, enemy guilds, "+
      "allied guilds\n");
	return 0;
    }

    if (!sizeof(names))
    {
	write("There is no one of that type declared.\n");
	return 1;
    }

    names = sort_array(names);

    /* Treat "list punished" specially: print out the type(s)  */
    /* of punishment the players are under.                    */
    if (flag & 1)
    {
	foreach(string who: names)
	{
	    string *tmp = LIST->query_union_punished_strings(who);
	    if (!sizeof(tmp))
		continue;

	    write(sprintf("%15s: %-#60.1s\n",
		capitalize(who), implode(tmp, "\n")));
	}
	return 1;
    }

    if (!(flag & 2)) foreach(string who: names)
    {
	if (LIST->query_is_member(who))
	{
	    string sphere = SPHERES[LIST->query_union_sphere(who)];
	    sphere = implode(explode(sphere, " ") - ({ "the" }), " ");

	    names -= ({ who });
	    names += ({ who + " (" + sphere + ")" });
	}
    }

    write(head + ":\n" + sprintf("  %-#76s\n",
	implode(map(names, capitalize), "\n")));

    return 1;
}

public string
memberlist(void)
{
    int size;
    string *members, *elders;

    members = sort_array(LIST->gm_list());
    if (size = sizeof(members))
    {
	if (size == 1)
	{
	    write("The Guild Master of the Union is:  "+
	      capitalize(members[0]) +"\n");
	}
	else
	{
	    write("The Guild Masters of the Union are:  "+
	      COMPOSITE_WORDS(map(members, capitalize)) +"\n");
	}
    }

    elders = sort_array(filter(LIST->elder_list(), valid_list));

    if (size = sizeof(elders))
    {
	if (size == 1)
	{
	    write("The Elder of the Union is:  "+
	      capitalize(elders[0]) + "\n");
	}
	else
	{
	    write("The Elders of the Union are:  "+
	      COMPOSITE_WORDS(map(elders, capitalize)) + "\n");
	}
    }
    else write("There are no Elders of the Union.\n");

    members = sort_array(filter(LIST->member_list(), valid_list) - elders);

    if (size = sizeof(members))
    {
	if (size == 1)
	{
	    write("The sole Member of the Union is:  "+
	      capitalize(members[0]) +"\n");
	}
	else
	{
	    write("The Members of the Union are:  "+
	      COMPOSITE_WORDS(map(members, capitalize)) +"\n");
	}
    }
    else write("There are no Members of the Union of the Warriors of Shadow.\n");

    say(QCTNAME(TP)+" reads over the member list.\n");
    return "";
}

private int
rank(mixed who)
{
    if (gmaster(who))
	return 10;

    if (LIST->query_is_elder(who))
	return 8;

    if (LIST->query_is_member(who))
	return 1;

    return 0;
}

private int
expel(string str)
{
    object who;

    if (!strlen(str))
	return NF("Expel who from the Union?\n");

    str = lower_case(str);

    if (str == TP->query_real_name())
	return NF("You may not expel yourself.\n");

    if (!LIST->query_is_member(str))
	return NF("That person is not a Member of the Union.\n");

    if (rank(TP) < rank(str))
	return NF("You may not expel anyone of greater rank than yourself.\n");

    if (rank(TP) == rank(str))
	return NF("You may not expel anyone of equal rank to yourself.\n");

    if (!LIST->add_expelled(str, TP))
	return NF("Something goes wrong! Leave a bug report please.\n");

    if (!(who = find_living(str)))
    {
	clog(NM(TP) +" marked "+ CAP(str) +" for expulsion");
	write(CAP(str)+" will be expelled upon their next login.\n");
	return 1;
    }

    write("Trying to expel "+ CAP(str) +" immediately.\n");
    if (who->query_guild_keep_player(who))
    {
	write("Something goes wrong, "+ CAP(str) +" has not been "+
	  "expelled. Leave a bug report.\n");
	return 1;
    }

    clog(NM(TP) + " has expelled " + CAP(str));
    write("You have expelled "+CAP(str)+".\n");
    return 1;
}

private int
unexpel(string str)
{
    if (!strlen(str))
	return NF("Unexpel who from the Union?\n");

    str = lower_case(str);

    if (str == TP->query_real_name())
    {
	NF("You may not unexpel yourself. See the person that expelled you.\n");
	return 0;
    }

    if (!sizeof(LIST->query_expelled(str)))
	return NF("That person is not a member of the Union.\n");

    if (rank(TP) < rank(str))
	return NF("You may not unexpel anyone of greater rank than yourself.\n");

    if (rank(TP) == rank(str))
	return NF("You may not unexpel anyone of equal rank to yourself.\n");

    if (!LIST->remove_expelled(str, TP))
	return NF("Something goes wrong! Leave a bug report.\n");

    clog(NM(TP) + " cancelled expulsion of " + CAP(str));
    write(CAP(str)+" is no longer marked for expulsion.\n");
    return 1;
}

private int
promote(string str)
{
    object who;

    if (!strlen(str))
	return NF("Promote who to Elder status?\n");

    str = lower_case(str);

    if (!LIST->query_is_member(str))
	return NF("That person is not a member of the Union.\n");

    if (LIST->query_is_elder(str))
    {
	NF(CAP(str) + " is already an Elder!\n");
	return 0;
    }

    if (sizeof(LIST->elder_list()) >= MAX_ELDERS)
    {
	write("There may only exist "+ LANG_WNUM(MAX_ELDERS) +
	  " Elders at any one time.\n");
	return 1;
    }

    if (!LIST->add_elder(str))
    {
	write("Something went wrong! Leave a bug report.\n");
	return 1;
    }

    if (!objectp(who = find_living(str)))
    {
	clog(NM(TP) +" promoted " + CAP(str) +" to Elder");
	write(CAP(str)+ " will become an Elder upon their next login.\n");
	return 1;
    }

    who->check_union_occ_status(who);
    clog(NM(TP) + " promoted " + CAP(str) +" to Elder");
    write(CAP(str)+" is now an Elder.\n");
    return 1;
}

private int
demote(string str)
{
    object who;

    if (!strlen(str))
	return NF("Demote who?\n");

    str = lower_case(str);

    if (!LIST->query_is_member(str))
	return NF("That person is not a member of the Union.\n");

    if (!LIST->query_is_elder(str))
	return NF(CAP(str) + " is not an Elder.\n");

    if (!LIST->remove_elder(str))
	return NF("Something goes wrong!\n");

    if (!objectp(who = find_living(str)))
    {
	write(CAP(str)+" will no longer be an Elder.\n");
	clog(NM(TP) + " demoted " + CAP(str) +" from Elder");
	return 1;
    }

    who->check_union_occ_status(who);
    clog(NM(TP) + " demoted " + CAP(str) +" from Elder");
    write(CAP(str)+" has fallen from the status of Elder.\n");
    return 1;
}

private int
punish(string str)
{
    int p_type;
    object who;
    string *args;

    if (!strlen(str))
	str = " ";

    str = lower_case(str);
    args = explode(str, " ");

    /* Did we enter the right args? Is           */
    /* the type of punishment specified valid?   */
    if (sizeof(args) != 2 || !punished_type[args[1]])
    {
	write("Punish who <how>?\nPossible forms of punishment to add are:\n");

	foreach(string str, int val: punished_type)
	{
	    /* U_PUNISHED_TYPE gives the description of the punishment
	     * e.g., "may not enter the halls of the Union"
	     */
	    write(sprintf("%11s - %s\n", str,
		"Subject "+ punished_str[val]));
	}

	write("\nNote that punishments are additive, in that a subject "+
	  "can have more than one type of punishment at any time.\n");

	return 1;
    }

    str = lower_case(args[0]);
    p_type = punished_type[args[1]];

    if (str == TP->query_real_name())
	return NF("You may not punish yourself.\n");

    if (U_IS_PUNISHED(str, p_type))
	return NF("That person is already under that punishment.\n");

    if (!(LIST->add_union_punishment(str, p_type)))
	return NF("Something goes wrong! Leave a bug report.\n");

    clog(NM(TP) + " added a punishment to " + CAP(str) +
	" ["+ args[1]  +"]");

    write(CAP(str) + " " + punished_str[p_type] + ".\n");
    return 1;
}

private int
reprieve(string str)
{
    int p_type;
    object who;
    string *args;

    if (!strlen(str))
	return NF("Reprieve the punishment of whom?\n");

    str = lower_case(str);
    args = explode(str, " ");

    /* Did we enter the right args? Is           */
    /* the type of punishment specified valid?   */
    if ((sizeof(args) != 2) || !(U_PUNISHED_TYPE[args[1]] || args[1] == "all"))
    {
	write("Reprieve who <type of punishment / all>?\n"+
	  "Possible forms of punishment to reprieve are:\n");

	foreach(string str, int val: punished_type)
	{
	    /* U_PUNISHED_TYPE gives the description of the punishment
	     * e.g., "may not enter the halls of the Union"
	     */
	    write(sprintf("%11s - %s\n", str,
		"Subject "+ punished_str[val]));
	}

	write("\nNote that punishments are additive, in that a subject "
	  + "can have more than one type of punishment at any time. "+
	  "Consequently, removing only one type of punishment will "+
	  "leave any other punishments intact.\n");

	return 1;
    }

    str = lower_case(args[0]);
    p_type = U_PUNISHED_TYPE[args[1]];

    if (str == TP->query_real_name())
	return notify_fail("You may not reprieve your own punishment.\n");

    if (!U_PUNISHED_LEVEL(str))
	return notify_fail("That person is not under punishment.\n");
    else if (p_type && !U_IS_PUNISHED(str, p_type))
	return notify_fail("That person is not under that punishment.\n");

    if (!(LIST->remove_union_punishment(str, p_type)))
	return notify_fail("Something goes wrong! Leave a bug report.\n");

    clog(NM(TP) + " reprieved a punishment from " +
      CAP(str) + " ["+ args[1] +"]");

    write(LANG_POSS(CAP(str)) + " punishment has been reprieved. ("+ args[1] +")\n");
    return 1;
}

private int
accept(string str)
{
    if (!strlen(str))
	return NF("Accept who as permitted to join the Union?\n");

    str = lower_case(str);

    if (LIST->idle_time(str) == -1)
	return NF("No such player.\n");

    if (LIST->query_is_member(str))
	return NF(CAP(str) + " is already a member.\n");

    if (LIST->query_accepted(str))
	return NF(CAP(str) + " has already been accepted.\n");

    if (LIST->query_blocked(str))
	return NF(CAP(str) + " is currently Persona Non Grata!\n");

    if (LIST->query_enemy(str))
	return NF(CAP(str) + " is an Enemy of the Union!\n");

    if (!LIST->add_accepted(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" accepted " + CAP(str) +" into the Union");
    write(CAP(str) + " may now join the Union.\n");
    return 1;
}

private int
unaccept(string str)
{
    if (!strlen(str))
	return NF("Take who off the accepted list?\n");

    str = lower_case(str);

    if (!LIST->query_accepted(str))
	return NF(CAP(str) + " has not been accepted.\n");

    if (!LIST->remove_accepted(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" cancelled Union acceptance for " + CAP(str));
    write(CAP(str) + " may no longer join the Union.\n");
    return 1;
}

private int
friend(string str)
{
    if (!strlen(str))
    {
	NF("Declare who as a Friend of the Union?\n"+
	  "Note: Friends of the Union will be greeted as such by all "+
	  "members of the Union. They will have access to the shelf "+
	  "and to those things sold by everyone except Hyacinth.\n");
	return 0;
    }

    str = lower_case(str);

    if (LIST->idle_time(str) == -1)
	return NF("No such player.\n");

    if (LIST->query_is_member(str))
	return NF("Members of the Union may not also be Friends.\n");

    if (LIST->query_friend(str))
	return NF(CAP(str) + " has already been declared a Friend.\n");

    if (LIST->query_blocked(str))
	return NF(CAP(str) + " is currently Persona Non Grata!\n");

    if (LIST->query_enemy(str))
	return NF(CAP(str) + " is an Enemy of the Union!\n");

    if (!LIST->add_friend(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" declared " + CAP(str) +" a Friend of the Union");
    write(CAP(str) + " shall be known as a Friend of the Union.\n");
    return 1;
}

private int
unfriend(string str)
{
    if (!strlen(str))
	return NF("Who shall no longer be an ally of the Union?\n");

    if (LIST->remove_friend_guild(str))
    {
	write(CAP(str) + " is no longer a guild allied to the Union.\n");
	return 1;
    }

    str = lower_case(str);

    if (!LIST->query_friend(str))
	return NF(CAP(str) + " has not been declared a Friend.\n");

    if (!LIST->remove_friend(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" delisted "+ CAP(str) +" as a Friend of the Union");
    write(CAP(str) + " is no longer a friend of the Union.\n");
    return 1;
}

private int
friend_guild(string str)
{
    if (!strlen(str))
	return NF("Declare what guild as Allies of the Union?\n");

    if (member_array(str, LIST->query_all_major_guilds()) == -1)
    {
	NF("There is no such guild '"+ str +"'.\n"+
	  "Try <list guilds> to see which may be specified.\n");
	return 0;
    }

    if (member_array(str, LIST->friend_guilds()) != -1)
    {
	NF("That guild has already been declared as Allies.\n");
	return 0;
    }

    if (member_array(str, LIST->blocked_guilds()) != -1)
    {
	NF("That guild is Persona Non Grata, they cannot also be Allies!\n");
	return 0;
    }

    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
	NF("That guild is a declared Enemy, they cannot also be Allies!\n");
	return 0;
    }

    if (!(LIST->add_friend_guild(str)))
    {
	NF("Something goes wrong, you cannot do that right now.\n");
	return 0;
    }

    clog(NM(TP) +" declared " + CAP(str) +" an Allied Guild");
    write("You declare " + str + " to be an Allied Guild.\n");
    return 1;
}

private int
enemy(string str)
{
    if (!strlen(str))
    {
	NF("Declare who as an enemy of the Union?\n"+
	  "Note: Enemies of the Union will be smote by Plalgus "+
	  "and marked with the blue aura. This will not make them "+
	  "Infidels, but it will make them identifiable as enemies, "+
	  "and they will carry the Curse until such time "+
	  "as the Elders lift their Enemy status.\n");
	return 0;
    }

    str = lower_case(str);

    if (LIST->idle_time(str) == -1)
	return NF("No such player.\n");

    if (LIST->query_is_member(str))
	return NF("Members of the Union may not be Enemies as well.\n");

    if (LIST->query_friend(str))
	return NF("But " + CAP(str) + " is a Friend of the Union!\n");

    if (LIST->query_enemy(str))
	return NF(CAP(str) + " has already been declared an Enemy.\n");

    if (!LIST->add_enemy(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" declared " + CAP(str) +" an Enemy of the Union");
    write(CAP(str) + " shall be known as an Enemy of the Union.\n");

    if (LIST->query_blocked(str) && LIST->remove_blocked(str))
    {
	clog(NM(TP) +" auto-delists " + CAP(str) +" as a Persona non Grata");
	write("Removing Persona Non Grata status from "+ CAP(str) +".\n");
    }

    return 1;
}

private int
enemy_guild(string str)
{
    if (!strlen(str))
	return NF("Declare what guild as enemies of the Union?\n");

    if (member_array(str, LIST->query_all_major_guilds()) == -1)
    {
	NF("There is no such guild '"+ str +"'.\n"+
	  "Try <list guilds> to see which may be specified.\n");
	return 0;
    }

    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
	NF("That guild has already been declared a Enemy!\n");
	return 0;
    }

    if (member_array(str, LIST->blocked_guilds()) != -1)
    {
	NF("That guild has already been declared Persona Non Grata!\n");
	return 0;
    }

    if (member_array(str, LIST->friend_guilds()) != -1)
    {
	NF("That guild is a declared Ally, they cannot also be Enemies!\n");
	return 0;
    }

    if (!LIST->add_enemy_guild(str))
    {
	NF("Something goes wrong, you cannot do that right now.\n");
	return 0;
    }

    clog(NM(TP) +" declared " + CAP(str) +" an Enemy Guild");
    write("You declare " + str + " to be a guild of Enemies.\n");
    return 1;
}

private int
forgive(string str)
{
    if (!str || !strlen(str))
    {
	NF("NOTE: This takes a person off the Union enemy list so the "+
	  "curse of Plalgus will be lifted. If they have not committed "+
	  "murder then the curse and aura will be lifted permanently.\n\n"+
	  "Removing Enemy status does NOT remove Infidel status for "+
	  "those who have committed crimes against Sybarus, such as "+
	  "mass murder. If someone is an Infidel, he will find him"+
	  "self cursed again upon entering Sybarus, and added back onto the "+
	  "Union enemy list.\n\nIf you want to remove ALL of the blood-"+
	  "debt and thus the persons Infidel status, "+
	  "you MUST use <uninfidel> as well as <unenemy>.\n\n"+
	  "SO: Who shall no longer be an enemy of the Union, and thus no "+
	  "longer cursed with the flaming blue aura, so long as they "+
	  "are not also infidel?\n");
	return 0;
    }

    if (LIST->remove_enemy_guild(str))
    {
	write(CAP(str) + " is no longer a hated guild.\n");
	return 1;
    }

    str = lower_case(str);

    if (!LIST->query_enemy(str))
	return NF(CAP(str) + " has not been declared an Enemy.\n");

    if (!LIST->remove_enemy(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" delisted " + CAP(str) +" as an Enemy of the Union");
    write(CAP(str) + " is no longer an Enemy of the Union.\n"+
	"If "+ CAP(str) +" is an Infidel as well, and you "+
	"want to lift the Curse, use <uncurse [who]>.\n");

    return 1;
}

private int
uncurse(string str)
{
    object whom, curse;

    if (!str || !strlen(str))
    {
	NF("NOTE: Infidels are shunned by sybarites, attacked by guards, "+
	  "and cannot use the Gods' gifts. They carry the curse "+
	  "and the aura to make it easier for you to identify them. "+
	  "<Uninfidel> removes the curse and aura as well as the infidel "+
	  "status. The infidel MUST be awake in the world, however.\n\n"+
	  "If you use <uninfidel> only, then this person will "+
	  "remain on the Union Enemy list and will probably be cursed "+
	  "with the aura next time they come to Sybarus. If you want "+
	  "to clear them of everything, use <unenemy> as well.\n\n"+
	  "SO: Who shall no longer be cursed by Plalgus as an infidel "+
	  "and an enemy of Sybarus?\n");
	return 0;
    }

    str = lower_case(str);
    whom = find_player(str);

    if (!whom)
    {
	NF("The curse cannot be lifted while "+ CAP(str) +" is sleeping!\n");
	return 0;
    }

    if (IS_INFIDEL(whom))
    {
	whom->remove_skill(SS_INFIDEL);
	write("Infidel status is removed, however, if this person "+
	  "is still listed as an Enemy of the Union, they will be "+
	  "cursed again until such time as you choose to "+
	  "<unenemy> them.\n");
    }

    if (objectp(curse = present(WRATHNAME, whom)))
    {
	curse->lift_judgement(1);
	clog(NM(TP) +" removed Curse of Plalgus from " + CAP(str));
	write(CAP(str) + " is no longer Cursed by Plalgus.\n");
	return 1;
    }
    else
    {
	write(CAP(str) + " doesn't appear to be an Infidel, afterall.\n"+
	  "Perhaps you meant to use <unenemy> instead?\n");
	return 1;
    }

    return 1;
}

private int
block_guild(string str)
{
    if (!strlen(str))
	return NF("Declare what guild as Personae Non Gratae?\n");

    if (member_array(str, LIST->query_all_major_guilds()) == -1)
    {
	NF("There is no such guild '"+ str +"'.\n"+
	  "Try <list guilds> to see which may be specified.\n");
	return 0;
    }

    if (member_array(str, LIST->friend_guilds()) != -1)
    {
	NF("That guild has already been declared as Allies.\n");
	return 0;
    }

    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
	NF("That guild is a declared Enemy, they cannot also be " +
        "Personae Non Gratae!\n");
	return 0;
    }

    if (member_array(str, LIST->blocked_guilds()) != -1)
    {
	NF("That guild is already Personae Non Gratae!\n");
	return 0;
    }

    if (!(LIST->add_blocked_guild(str)))
    {
	NF("Something goes wrong, you cannot do that right now.\n");
	return 0;
    }

    clog(NM(TP) +" declared " + CAP(str) +" as Personae Non Gratae");
    write("You declare " + str + " to be Personae Non Gratae.\n");
    return 1;
}


/* Addition for Persona Non Grata's */
private int
block(string str)
{
    if (!str || !strlen(str))
	return NF("Declare <who> as Persona Non Grata?\n");

    str = lower_case(str);

    if (LIST->idle_time(str) == -1)
	return NF("No such player.\n");

    if (LIST->query_blocked(str))
	return NF(CAP(str) + " is already Persona Non Grata!\n");

    if (LIST->query_is_member(str))
	return NF(CAP(str) + " is a member, punish them instead.\n");

    if (LIST->query_hopeful(str))
	return NF(CAP(str) + " is currently a Hopeful.\n");

    if (LIST->query_accepted(str))
	return NF(CAP(str) + " is currently Accepted.\n");

    if (LIST->query_enemy(str))
	return NF(CAP(str) + " is already an Enemy of the Union!\n");

    if (LIST->query_friend(str))
	return NF(CAP(str) + " is a Friend of the Union.\n");

    if (!LIST->add_blocked(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" declares " + CAP(str) +" to be Persona Non Grata");
    write(CAP(str) + " is declared Persona Non Grata!\n");
    return 1;
}

private int
unblock(string str)
{
    if (!strlen(str))
	return NF("Forgive <who> as being Persona Non Grata?\n");

    if (LIST->remove_blocked_guild(str))
    {
	    write(CAP(str) + " is no longer a Personae Non Gratae guild.\n");
	    return 1;
    }

    str = lower_case(str);

    if (!LIST->query_blocked(str))
	return NF(CAP(str) + " is not yet declared Persona Non Grata.\n");

    if (!LIST->remove_blocked(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" delisted " + CAP(str) +" as a Persona Non Grata");
    write(CAP(str) + " is no longer Persona Non Grata.\n");
    return 1;
}


private int
expunge(string str)
{
    if (!strlen(str))
    {
	NF("Expunge whose essence from the Flame?\n"+
	  "Note: Using <expunge name> will purge their essence from "+
	  "the Flame and the Well of Souls, such that it is as if they "+
	  "Were never One. This is irrevocable and cannot be undone.\n"+ 
	  "<Expunge name> can only be done with former Warriors and "+
	  "not current ones.\n"+
	  "Be aware that their statue will remain at the Well of Souls "+
      "until you use <destroy name> at the Well itself.\n");
	return 0;
    }

    str = lower_case(str);

    if (LIST->query_is_member(str))
	return NF("You cannot expunge a current member of the Union.\n");

    if (!LIST->query_named(str))
	return NF("The essence of "+ capitalize(str) +" is not part of "+
       "the Flame.\n");
	   
    if (!LIST->remove_named(str))
	return NF("Something went wrong. You could not expunge them. "+
    "Contact the Guildmaster if you think this is a bug.\n");

    clog(NM(TP) +" expunged " + CAP(str) +"'s essence "+
    "from the Flame forever.\n");
    write(CAP(str) + "'s essence has been forever expunged from the "+
    "Flame and the Well of Souls.\n");
    return 1;
}

private int
do_view(string str)
{
    if (str != "hole" && str != "through hole")
	return 0;

    object ob = find_object(ROOM + "hall_nw");

    if (!objectp(ob))
    {
	write("There is nothing to be seen.\n");
	return 1;
    }

    object *live, *dead;

    write("Putting your eye to the hole in the door, you see:\n\n");
    write(ob->long(0));

    dead = all_inventory(ob);
    live = filter(dead, living);
    dead = filter(dead - live, not @ &->query_no_show());

    if (sizeof(dead) && strlen(str = SILENT_COMPOSITE_DEAD(dead)))
	write(break_string((capitalize(str) + "."), 76) + "\n");

    if (sizeof(live) && strlen(str = SILENT_COMPOSITE_LIVE(live)))
	write(break_string((capitalize(str) + "."), 76) + "\n");

    write("\n");
    return 1;
}

/*
 * Subroutines are in ~union/lib/visions.c
 */
private int
do_vision(string str)
{
    string cmd, name, vis;

    notify_fail("To list a vision: vision <list> <who/all>\n"+
	"To send a vision: vision <send> <who/sphere/all> <vision>\n"+
	"To clear visions: vision <clear> <who/all>\n"+
	"To remove one vision: vision <rem> <who> <vision>\n");

    if (!strlen(str))
	return 0;

    str = lower_case(str);
    if (sscanf(str, "%s %s %s", cmd, name, vis) != 3 &&
	sscanf(str, "%s %s", cmd, name) != 2) cmd = str;

    switch(cmd)
    {
    case "list":
	return list_vision(name);
    case "send":
	return assign_vision(name, vis);
    case "rem":
	return remove_vision(name, vis);
    case "clear":
	return clear_vision(name);
    }
    return 0;
}

private int
do_login_msg(string str)
{
    string name, msg;

    if (!strlen(str))
	return NF("Msg <whom/all> <what>?\n");

    if (!parse_command(str, ({}), "%w %s", name, msg))
	return NF("Msg <whom/all> <what>?\n");

    name = lower_case(name);

    if (!LIST->query_is_member(name))
	return NF("That person is not a member of the Union.\n");

    clog(NM(TP) + " msg " + CAP(name) + ": " +  msg);
    LIST->add_union_message(name, msg +"\n");

    write(capitalize(name) +" will get the message: "+
      msg +", upon awakening.\n");

    return 1;
}



/* easy access to the named function in List */
private int
add_named(string str)
{
    if (!str || !strlen(str))
	return NF("Declare who as a Named Warrior of Shadow?\n");

    str = lower_case(str);

    if (LIST->query_named(str))
	return NF(CAP(str) + " has already been Named.\n");

    if (!LIST->add_named(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    clog(NM(TP) +" Named " + CAP(str) +" without ceremony");
    write(CAP(str) + " is Named.\n");
    return 1;
}

private static mapping logs = ([
  "council" : COUNC_LOG,
  "mentor"  : MENTOR_LOG,
  //	  "guild" : GUILD_LOG,
  //       "case_get" : GUILDLOG + "case_get",
  //       "case_put" : GUILDLOG + "case_put",
  //      "shelf_get" : GUILDLOG + "shelf_get",
  //      "shelf_put" : GUILDLOG + "shelf_put",
]);

private int
log_view(string str)
{
    string valid = COMPOSITE_WORDS_WITH(sort_array(m_indexes(logs)), "or");

    if (!strlen(str))
    {
	return NF("Syntax: logview <log>\n"+
	  "Where <log> is one of: "+ valid +"\n");
    }

    string file = logs[str = lower_case(str)];
    if (!strlen(file))
    {
	write("That log is not available, try one of these instead\n"+
	  "    "+ valid +"\n");
	return 1;
    }

    if (file_size(file) < 1)
    {
	write("That log file appears to be empty.\n");
	return 1;
    }

    write("//*********[  You begin viewing the log: "+ str +
      "  ]*********\\\\\n\n");

    tail_file(file);
    return 1;
}

public void
add_union_text(string str, string what, string desc)
{
    // No input, abort.
    if (!strlen(str) || str == "~q")
    {
	write("Aborted.\n");
	return;
    }

    // Set the description
    if (!strlen(desc))
    {
	write("Description has been set.\nNow enter the formatted "+
	  "text which should be displayed:\n");

	clone_object(EDITOR_OBJECT)->edit(&add_union_text(, what, str));
	return;
    }

    // Configure the text
    if (LIST->add_union_text(what, desc, str))
	write("There was an error saving the Union text block.\n");
    else
	write("The Union text block '"+ what +"' has been added.\n");
}

public void
mod_union_text(string what, string text)
{
    // No input, abort.
    if (!strlen(text) || text == "~q")
    {
	write("Aborted.\n");
	return;
    }

    // Modify the text
    if (LIST->change_union_text(what, text))
	write("There was an error modifying the Union text block.\n");
    else
	write("The Union text block '"+ what +"' has been modified.\n");
}

private int
union_text(string str)
{
    string cmd, arg;
    int GM = gmaster(TP);
    mapping texts = LIST->get_union_texts();

    cmd = "Syntax: sutext <cmd> [arg]\n"+
	" - <cmd> can be 'list' or the name of a text to view or modify.\n";
    if (GM) cmd += " - <cmd> can also be 'add' or 'del' for Guildmasters.\n";

    notify_fail(cmd);

    if (!strlen(str))
	return 0;

    if (!parse_command(lower_case(str), ({ }), "%w %s", cmd, arg))
	return 0;

    // GM's can add new text blocks.
    if (GM && cmd == "add")
    {
	if (!strlen(arg))
	{
	    write("You must provide the name of a text block to add.\n");
	    return 1;
	}

	if (texts[arg])
	{
	    write("There is already a Union text named '"+ arg +"'.\n");
	    return 1;
	}

	write("Enter a brief description to be used for: "+ arg +"\n# ");
	input_to(&add_union_text(, arg, ""));
	return 1;
    }

    // Shouldn't happen, but...
    if (!m_sizeof(texts))
    {
	write("There are no Union texts defined!\n");
	return 1;
    }

    // GM's can wipe out text blocks.
    if (GM && cmd == "del")
    {
	if (!strlen(arg))
	{
	    write("You must provide the name of a text block to delete.\n");
	    return 1;
	}

	if (texts[arg])
	    if (LIST->rem_union_text(arg))
		write("There is no Union text named '"+ arg +"'.\n");
	    else
		write("The Union text block named '"+ arg +"' has been removed.\n");

	return 1;
    }

    // Anyone may list.
    if (cmd == "list")
    {
	write("The following Union texts are available:\n");
	foreach(string txt, string *arr: texts)
	{
	    // Skip over bad entries
	    if (sizeof(arr) != 2)
		continue;

	    write(sprintf("%15s: %-=60s\n", txt, arr[0]));
	}
	return 1;
    }

    if (!texts[cmd])
    {
	write("There is no Union text block named '"+ cmd +"'.\n");
	return 1;
    }

    // View a specific text block.
    if (!strlen(arg) || arg == "list" || arg == "view")
    {
	write("Union text '"+ cmd +"': "+ texts[cmd][0] +"\n\n"+
	  texts[cmd][1]);
	return 1;
    }

    if (arg == "mod" || arg == "modify")
    {
	if (!strlen(str = LIST->query_union_text(cmd)))
	{
	    write("Could not retrieve the text for '"+ cmd +"'!\n");
	    return 1;
	}

	write("Modifying the formatted text to be displayed:\n");
	clone_object(EDITOR_OBJECT)->edit(&mod_union_text(cmd, ), str);
	return 1;
    }

    write("The sub-command '"+ arg +"' is not available.\n"+
      "You may use the following: list, view, mod, modify\n");
    return 1;
}

public void
enter_inv(object who, object from)
{
    ::enter_inv(who, from);

    if (!living(who))
	return;

    if (!query_interactive(who))
    {
	who->remove_object();
	return;
    }

    if (!find_object(LIST) && catch(LIST->teledensanka()))
    {
	who->catch_msg("We are experiencing a few problems, so the "+
	  "council chambers are off limits right now.\n");
	who->move(from, 1);
    }
}

public void
init(void)
{
    ::init();

    if (!IS_ELDER(TP) && !gmaster(TP) &&
	!(SECURITY->query_wiz_dom(TP->query_name()) == "Avenir"))
    {
	return;
    }
    /*
     * Try to keep in most-likely-used order.
     */
    add_action(help,         "suhelp");
    add_action(help,         "help");
    add_action(list,         "list");
    add_action(list,         "sulist");
    add_action(log_view,     "logview");
    add_action(accept,       "accept");
    add_action(accept,       "suaccept");
    add_action(unaccept,     "unaccept");
    add_action(unaccept,     "suunaccept");
    add_action(punish,       "punish");
    add_action(punish,       "supunish");
    add_action(do_vision,    "vision");
    add_action(do_login_msg, "msg");
    add_action(expel,        "expel");
    add_action(expel,        "suexpel");
    add_action(unexpel,      "unexpel");
    add_action(expunge,      "expunge");
    add_action(friend,       "friend");
    add_action(friend,       "sufriend");
    add_action(unfriend,     "unfriend");
    add_action(block,        "block");
    add_action(block,        "sublock");
    add_action(unblock,      "unblock");
    add_action(unblock,      "suunblock");
    add_action(enemy,        "enemy");
    add_action(enemy,        "suenemy");
    add_action(forgive,      "unenemy");
    add_action(forgive,      "suunenemy");
    add_action(uncurse,      "uninfidel");
    add_action(uncurse,      "uncurse");
    add_action(reprieve,     "reprieve");
    add_action(friend_guild, "ally");
    add_action(enemy_guild,  "condemn");
    add_action(block_guild,  "unwelcome");
    add_action(promote,      "promote");
    add_action(promote,      "supromote");
    add_action(demote,       "demote");
    add_action(demote,       "sudemote");
    add_action(guild_prop,   "restrict");
    add_action(guild_prop,   "unrestrict");
    add_action(add_named,    "named");
    add_action(do_view,      "peep");
    add_action(union_text,   "sutext");

    /* Add the library commands */
    init_library();
}

public int
query_librarian(object who)
{
    /* Elders and GM's. */
    if (IS_ELDER(who) || IS_GMASTER(who))
	return 1;

    return 0;
}

public string *
query_player_access(object who)
{
    /* Mentors, Elders and GM's. */
    if (query_librarian(who))
	return ({ "admin" });

    return ({ });
}

public void
library_configure_book(object book, string book_id)
{
    ::library_configure_book(book, book_id);

    if (!strlen(book_id))
	return;

    string *adjs = ({ "gilded", "embossed", "illuminated" });
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
    book->set_long("This book is a part of the Elders's library.\n"+
      "Along the spine is writ the following: "+ book->query_title() +
      ".\n");
}

public void
leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}
