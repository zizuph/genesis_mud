/*
 * Post office for the Union
 *  Cirion 032096
 *
 * Revisions:
 *  Lucius, Jul 2011: Many, many cleanups+changes+additions.
 *  Lucius, Apr 2016: More cleanups and changes.
 *  Lucius, May 2016: Added non-members blocking to 'up' exit.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;
inherit "/d/Genesis/lib/post";

#include <files.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#define MAILCHECKER	"/secure/mail_checker"
#define MAILREADER	"/secure/mail_reader"
#define MAILREADER_ID	"_reader_"

private int new_mail;
private string messages;


public int
exit_block(void)
{
    write("You pass through the shadows above.\n");
    return 0;
}

public void
union_room(void)
{
    set_short("oval chamber");
    set_long("This is a large, silent chamber with smooth stone "+
	"walls that reach around to form an oval. In the centre of "+
	"the room rises a rock table with a small chair before it, "+
	"upon which you can read and write letters. "+
	"The only exit is to the south, where a hallway can "+
	"be made out.\n");

    add_item(({"wall","walls","oval","stone"}),
	"The stone wall in this room is one continuous "+
	"slab of very smooth rock that wraps around the "+
	"room. The only break in the wall is to the "+
	"south, where it leads out into a hallway.\n");
    add_item(({"table","rock","tablet"}),
	"The table is smooth and hard, made from the same "+
	"material as the walls. On the table are scattered "+
	"pens, quills, ink wells, parchment, and other writing "+
	"instruments.\n");
    add_item(({"pen","pens","quill","quills","ink","well",
	"wells","ink well","ink wells","parchment","paper",
	"papers","parchments"}),
	"They are writing utensils with which you can send out mail "+
	"all accross the lands.\n");

    set_noshow_obvious(1);

    add_exit("crossing", "south");
//    add_exit("voice", "up", exit_block);
}

private int
silence(string str)
{
    write("The walls of the room seem to swallow up all "+
	"the noise you make.\n");

    return !TP->query_wiz_level();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

private void
mail_message(string new)
{
    write("\n"+
      "                   *               -*-                 *\n"+
      "                "+new+" awaits you in the Hall of Shadow\n"+
      "                   *             *******               *\n");
}

/*
 * Function name: query_mail
 * Description  : This function is called when a player logs on to give him
 *                a message about the (new) mail in his mailbox.
 * Arguments    : silent - Set to 1 to not tell the player about the mail.
 * Returns      : 0 - no mail
 *                1 - mail, all read
 *                2 - new mail
 *                3 - unread mail
 */
public int
query_mail(int silent)
{
    string new;
    int mail = MAILCHECKER->query_mail();

    if (silent || mail < 2)
	return mail;

    switch(mail)
    {
    case 2:
	new = "   New mail";
	break;
    default:
	new = "Unread mail";
	break;
    }

    mail_message(new);
    return mail;
}

/*
 * Verify we have a valid array of names. Capitalize
 * the names, too, to make them look nice. Also allow
 * blocking out of wizard and *jr names.
 */
private varargs string *
valid_array(mixed elem, int block_wiz)
{
    string *newelem = ({ });

    if (stringp(elem))
	return ({ CAP(elem) });

    if (!sizeof(elem))
	return ({ });

    if (block_wiz && TP->query_wiz_level())
	block_wiz = 0;

    // Make sure we are dealing with strings.
    elem = filter(elem, strlen);

    foreach(string who: elem)
    {
	// parse out non-existant players
	if (SECURITY->exist_player(who) == 0)
	    continue;
	// parse out jr's
	if (wildmatch("*jr", who))
	    continue;
	// parse out wizards
	if (block_wiz && (SECURITY->query_wiz_level(who)))
	    continue;

	newelem += ({ CAP(who) });
    }

    return sort_array(newelem);
}

public void
add_aliases(object reader)
{
    object for_who = TP;
    string str = "", *recip = ({});

    reader->set_short("long feathered pen");
    reader->add_name(({"pen","quill"}));
    reader->add_adj(({"long","feather","feathered","quill"}));

    str = "You may use the following Union aliases here:\n\n";

#define HIC(x, y)  sprintf("%' '"+x+"s: %-=*s\n", y, 80 - (x + 3), \
       	(sizeof(recip) ? COMPOSITE_WORDS(recip) : "(none)"))

    /*  
     *  So Outlanders know who to contact for 
     *  Union-related inquiries.
     */
    if (!IS_MEMBER(for_who) && !IS_GMASTER(for_who))
    {
	recip = valid_array(LIST->sphere_members()["voice"], 1);
	reader->set_long("@@long_description@@\n" +
	    str + HIC(13, "Voice")); 
	reader->set_alias("voice", recip);  
	return;
    }

    recip = valid_array(LIST->gm_list());
    str += HIC(13, "Guildmaster");
    reader->set_alias("guildmaster", recip);

    recip = valid_array(LIST->hopeful_list(), 1);
    str += HIC(13, "Hopefuls");
    reader->set_alias("hopefuls", recip);

    str += "\n";

    recip = valid_array(LIST->friend_list(), 1);
    str += HIC(13, "Friends");
    reader->set_alias("friends", recip);

    recip = sort_array(LIST->friend_guild_list());
    str += HIC(13, "Friend Guilds");

    recip = valid_array(LIST->blocked_list(), 1);
    str += HIC(13, "Blocked");
    reader->set_alias("blocked", recip);

    recip = sort_array(LIST->blocked_guild_list());
    str += HIC(13, "Blocked Guilds");

    recip = valid_array(LIST->enemy_list(), 1);
    str += HIC(13, "Enemies");
    reader->set_alias("enemies", recip);

    recip = sort_array(LIST->enemy_guild_list());
    str += HIC(13, "Enemy Guilds");

    if (MEMBER_SPHERE(TP, SPH_VOICE))
    {
	str += "\n";

	recip = valid_array(LIST->elder_list(), 1);
	str += HIC(13, "Elders");
	reader->set_alias("elders", recip);

	// Display only!
	recip = valid_array(LIST->expel_list(), 1);
	str += HIC(13, "Expelled");
    }

    str += "\n";

    /* obtain the mapping from the list of:
     *    sphere name : ({ member1, member2, ... })
     */
    foreach(string sph, string *whom: LIST->sphere_members())
    {
	if (SECURITY->exist_player(sph))
	    sph = "Union_" + CAP(sph);
	else
	    sph = CAP(sph);

	if (!sizeof(recip = valid_array(whom, 1)))
	    continue;

	str += HIC(13, sph);
	reader->set_alias(sph, recip);
    }

    if (MEMBER_SPHERE(TP, SPH_VOICE))
    {
	str += "\n *** You can adjust the list of Hopefuls with "+
	    "'hopeful / unhopeful <who>' *** \n";
    }

    reader->set_long("@@long_description@@\n" + str);
}

/* 
 * As the Voice is responsible for maintaining the list of Hopefuls
 * in his/her function as Interviewer/Recruiter for the Council,
 * but is not (usually) on the Council itself, the ability to  
 * manipulate the list of Hopefuls has been moved to here.
 */
private nomask int
hopeful(string str)
{
    if (!str || !strlen(str))
	return NF("Recognize <who> as a Union Hopeful?\n");

    str = lower_case(str);

    if (LIST->idle_time(str) == -1)
	return NF("No such player.\n");

    if (LIST->query_is_member(str))
	return NF(CAP(str) + " is already a member.\n");

    if (LIST->query_hopeful(str))
	return NF(CAP(str) + " is already listed as a Hopeful.\n");

    if (LIST->query_accepted(str))
	return NF(CAP(str) + " is currently Accepted.\n");

    if (LIST->query_blocked(str))
	return NF(CAP(str) + " is currently Persona Non Grata!\n");

    if (LIST->query_enemy(str))
	return NF(CAP(str) + " is an enemy of the Union!\n");

    if (!LIST->add_hopeful(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    write(CAP(str) + " is now recognized as a Union Hopeful.\n");
    return 1;
}

private nomask int
unhopeful(string str)
{
    if (!strlen(str))
	return NF("Take <who> off the Hopeful list?\n");

    str = lower_case(str);

    if (!LIST->query_hopeful(str))
	return NF(CAP(str) + " has not been listed as a Hopeful.\n");

    if (!LIST->remove_hopeful(str))
	return NF("Something goes wrong. You cannot do that right now.\n");

    write(CAP(str) +" is no longer listed as a Hopeful.\n");
    return 1;
}

/*
 * Wizards don't need to watch people read and
 * write mail here.
 */
public nomask int
query_prevent_snoop(void)
{
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(silence, "say");
    add_action(silence, "'", 2);
    add_action(silence, "shout");
    add_action(silence, "ask");
    add_action(silence, "ponder");
    add_action(silence, "think");
    add_action(silence, "sing");
    add_action(silence, "laugh");
    add_action(silence, "us");
    add_action(silence, "usay");

    if (MEMBER_SPHERE(TP, SPH_VOICE))
    {
	add_action(hopeful,   "hopeful");
	add_action(hopeful,   "suhopeful");
	add_action(unhopeful, "unhopeful");
	add_action(unhopeful, "suunhopeful");
    }

    post_init();
}
