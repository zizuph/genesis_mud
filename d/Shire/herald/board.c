#pragma save_binary

inherit "/d/Shire/room";

#include "/d/Shire/herald/herald.h"

#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include <std.h>


void reset_room();
static void create_board();
#define ACCEPT_LOG  "/d/Shire/herald/accept"
#define FAIL_LOG "/d/Shire/herald/failedaccept"
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define LOG_SIZE 4000
#define MORE_OBJ "/std/board/board_more"

nomask private void
log_fail(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(FAIL_LOG) > LOG_SIZE)
    {
	rename(FAIL_LOG, (FAIL_LOG + ".old"));
    }

    write_file(FAIL_LOG, text);
}

nomask private void
log_accept(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(ACCEPT_LOG) > LOG_SIZE)
    {
	rename(ACCEPT_LOG, (ACCEPT_LOG + ".old"));
    }

    write_file(ACCEPT_LOG, text);
}


int
study(string str)
{


    if(!str)
    {
	TP->catch_msg("Study what?\n");
	return 1;
    }

    if((str != "large scroll") && (str != "scroll"))
    {
	TP->catch_msg("Study what? Scroll?\n");
	return 1;
    }

    if(!(IS_MEMBER(TP)))
    {
	TP->catch_msg("You're not a Herald! How'd you get in here anyway?\n");
	return 1;
    }

    clone_object(MORE_OBJ)->more(ACCEPT_LOG, 2);

    return 1;

}


int
accept(string str)
{
    int guildstat;
    object member;

    guildstat = TP->query_stat(SS_LAYMAN);


    if(!str)
    {
	TP->catch_msg("Accept whom as member of the Heralds of the Valar?\n");
	return 1;
    }


    if(!(TP->query_guild_name_lay() == HERALD_GUILD_NAME))
    {
	TP->catch_msg("You aren't a Herald! How did you get in here?\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "they were not a member!\n");
	TP->move("/d/Shire/herald/path3");
	return 1;
    }

    if(TP->query_wiz_level())
    {
	TP->catch_msg("Wizards may not do this.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "wizards cannot accept new members!\n");
	return 1;
    }

    if(guildstat < 40)
    {
	TP->catch_msg("You are not experienced enough as a Herald to do this.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "failed, heraldstat <"+guildstat+">\n");
	return 1;
    }

    member = find_player(str);
    if(!member)
    {
	TP->catch_msg("Can't find that person.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "failed, couldn't find them.\n");
	return 1;
    }

    if(member->query_guild_name_lay() == HERALD_GUILD_NAME)
    {
	TP->catch_msg("That person is already a Herald!\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "failed, they were already a Herald of the Valar.\n");
	return 1;
    }


    if(member->query_guild_name_lay())
    {
	TP->catch_msg("That person cannot be accepted because of other allegiances.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "failed, they were already in a lay guild.\n");
	return 1;
    }

    if(member->query_prop("_i_can_join_the_heralds_of_the_valar"))
    {
	TP->catch_msg("That person has already been given permission to join.\n");
	log_fail(WRITE_NAME(TP)+ " tried to accept "+str+", but "+
	  "failed, they were already cleared to join.\n");
	return 1;
    }

    write("Very well, "+capitalize((member->query_real_name()))+" may now join the "+
      "Heralds of the Valar.\n");
    log_accept(WRITE_NAME(TP)+ " accepted "+ capitalize( (member->query_real_name()) )+".\n");
    say(QCTNAME(TP)+ " writes a name in the large scroll.\n");
    member->add_prop("_i_can_join_the_heralds_of_the_valar",1);
    member->catch_msg(QCTNAME(TP)+" has vouched for you so that you may "+
      "join the Heralds of the Valar.\n");
    return 1;

}



void
create_room()
{
    object board;

    set_short("Between large branches in a giant maple tree");
    set_long("A meeting of branches at the main trunk causes "+
      "this place to be a natural center of conversation.  "+
      "To that end, the Heralds of the Valar have put a "+
      "bulletin board here so that all may join in the discussion. "+
      "Branches lead northeast and southwest, while the main "+
      "trunk leads up and down leads a rope ladder.  A large scroll "+
      "has been affixed to the trunk here.  Just "+
      "below the scroll you notice a piece of aged parchment.\n");

    add_item(({"meeting","branches"}),
      "The largest of the branches attach here at the main trunk and lead "+
      "northeast and southwest, as if on an axis.  They are strong enough that "+
      "even the plumpest hobbit may walk on them.\n");

    add_item(({"trunk","main trunk"}),
      "The pillar of the tree, the trunk is approximately twenty feet around at "+
      "this point and hardly even sways in the most powerful of gusts.\n");

    add_item(({"scroll","large scroll"}),"The large scroll is a list of some sort.  "+
      "Perhaps you could study it?\n");

    add_item(({"parchment","aged parchment"}),
      "@@book_desc@@");
    add_exit(HERALD_DIR + "herb","down",0,1);
    add_exit("/d/Shire/guild/heralds/room/train","southwest",0,1);
    add_exit("/d/Shire/guild/heralds/room/library","northeast",0,1);
    add_exit(HERALD_DIR + "post","up",0,1);

    add_prop(ROOM_I_ALLOW_STEED, 0);  // no horses here.

    reset_room();
}


string
book_desc()
{
    TP->more(MEMBER_TRACKER->query_members(TP->query_wiz_level()));

    return "";
}
void
init()
{
    ::init();
    add_action("accept","accept");
    add_action("study","study");
}

void
reset_room()
{
    if (!present("board", TO))
	create_board();
}

static void
create_board()
{
    object board;

    if ((board = clone_object("/d/Shire/std/board")))
    {
	board->set_board_name("/d/Shire/herald/board");
	board->set_num_notes(30);
	board->set_silent(1);
	board->set_show_lvl(0);
	board->set_remove_rank(WIZ_NORMAL);
	board->set_remove_str("Sorry, mortals are not allowed to remove notes.\n");
	board->move(TO);
    }
    return 0;
}
