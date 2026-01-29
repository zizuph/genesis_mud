/* 
 * created by Igneous
 */
#pragma save_binary

/*
**This room is used for the vouching of new members in the Tricksters.
**The vouching system was taken from the Heralds
**of the Valar found in /d/Shire/heralds/board.c
*/


inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "trickster.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <std.h>

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define LOG_SIZE       4000
#define MORE(x) this_player()->more(read_file(x,2)) 

nomask private void
log_fail(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(TRICKSTER_GUILD_FAIL_LOG) > LOG_SIZE)
    {
	rename(TRICKSTER_GUILD_FAIL_LOG, (TRICKSTER_GUILD_FAIL_LOG + ".old"));
    }

    write_file(TRICKSTER_GUILD_FAIL_LOG, text);
}

nomask private void
log_accept(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(TRICKSTER_GUILD_ACCEPT_LOG) > LOG_SIZE)
    {
	rename(TRICKSTER_GUILD_ACCEPT_LOG, (TRICKSTER_GUILD_ACCEPT_LOG + ".old"));
    }

    write_file(TRICKSTER_GUILD_ACCEPT_LOG, text);
}

int
glance(string str)
{
    if ((!str) && (str != "big book") && (str != "book"))
    {
	TP->catch_msg("Glance at what?\n");
	return 1;
    }

    if (!(IS_MEMBER(TP)))
    {
	TP->catch_msg("Hey!!!  Your not a Trickster!!  How'd you get in " +
	  "here anways?\n");
	return 1;
    }

    seteuid(getuid());
    if (TP->query_wiz_level())
	TP->more(MEMBER_TRACKER->query_members(1));
    else
	TP->more(MEMBER_TRACKER->query_members(0));
    return 1;
}

int
scribble(string str)
{
    int      guildstat;
    object   member;

    str = lower_case(str);
    guildstat = TP->query_stat(SS_LAYMAN);

    if (!str)
    {
	TP->catch_msg("Accept whom into the ranks of the Tricksters?\n");
	return 1;
    }

    if (!(IS_MEMBER(TP)))
    {
	TP->catch_msg("How can you accept someone if you don't belong here! " +
	  "Now get out!\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "they were not a member!\n");
	return 1;
    }

    if (TP->query_wiz_level())
    {
	TP->catch_msg("Wizards can not accept members.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "wizards can not accept new members!\n");
	return 1;
    }

    if (TP->query_alignment() > TRICKSTER_GUILD_ALIGN_MAX ||
      TP->query_alignment() < TRICKSTER_GUILD_ALIGN_MIN)
    {
	write("Hmm you've ventured too far from the Trickster ideals "+
	  "to invite anyone else to join the guild.\n");
	return 1;
    }

    if (guildstat < 35)
    {
	TP->catch_msg("You aren't tricky enough yet to accept someone new.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "failed, tricksterstat <"+guildstat+">\n");
	return 1;
    }

    member = find_player(str);

    if (!member)
    {
	TP->catch_msg("Can't seem to find that person.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "failed, couldn't find them.\n");
	return 1;
    }

    if (IS_MEMBER(member))
    {
	TP->catch_msg("You fool!!  That person is already a member!\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "failed, they were already a Trickster.\n");
	return 1;
    }

    if (member->query_guild_name_lay())
    {
	TP->catch_msg("That person cannot be accepted beacuse of other " +
	  "allegiances.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "failed, they were already in a layman guild.\n");
	return 1;
    }

    if (member->query_prop("_i_can_join_the_tricksters"))
    {
	TP->catch_msg("That person has already been vouched for!\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but " +
	  "failed, they were already vouched for by someone else.\n");
	return 1;
    }

    write("Ok, you've accepted "+capitalize((member->query_real_name()))+" "+
      "as tricky enough to join the Tricksters.\n");
    log_accept(WRITE_NAME(TP)+ " accepted " +
      capitalize((member->query_real_name()))+".\n");
    say(QCTNAME(TP)+ " adds a name to the big book.\n");
    member->add_prop("_i_can_join_the_tricksters", 1);
    member->catch_msg(QCTNAME(TP)+ " has vouched for you so may join " +
      "the Tricksters.\n");
    return 1;

}
void
create_room()
{
    set_short("A crude hallway");
    set_long("A crude hallway has been dug here.  It's much drier and " +
      "more livable than some of the other rooms around here.  You notice " +
      "a sign pointing east in the middle of the room as well there are " +
      "rows of torches which line this hallway providing some warmth. " +
      "In the corner of the room there is a small wooden desk and " +
      "a big book which lies upon it. " +
      "This hallway breaks off to the east and continues to the south.\n");

    add_cmd_item("sign", "read", "Alchemist shop:  Enter at your own risk!\n");

    add_item(({"book","big book"}),
      "This book is bound in faded leather, within it are numerous " +
      "scribbles made by Tricksters to show that someone is worthy " +
      "to join the ranks of the Tricksters. You may wish to take a " +
      "glance at the book to see who all has been accepted into this guild " +
      "and who accepted them. You may also try to scribble down the name " +
      "of someone who you believe tricky enough to join us.\n");
    add_item(({"desk","wooden desk", "small desk", "small wooden desk"}),
      "The desk is made of some rotting wood, obivously someone scavanged " +
      "this from a junk pile somewhere.  You wonder how much longer " +
      "the desk will hold up, under the weight of the big book, which " +
      "sits upon it.\n");
    add_item("sign", "Ummm maybe you should try reading it?\n");
    add_item(({"torches","torch","light","lights"}),
      "These torches burn brightly in the room providing light.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TRICK_DIR + "alchemy_shop","east","@@shop_open@@",1);
    add_exit(TRICK_DIR + "back_way","south",0,1);
    add_exit(TRICK_DIR + "train","northwest",0,1);

}

void
init()
{
    ::init();
    add_action("glance","glance");
    add_action("scribble","scribble");
}

int
shop_open()
{
    int   closed;

    closed = 0;  /* Set to 1 if you wish to close the alchemy_shop */
    if(closed)
    {
	write("I'm sorry but the Alchemist Shop is currently closed. "+
	  "Perhaps try here later?\n");
	return 1;
    }
    return 0;
}
