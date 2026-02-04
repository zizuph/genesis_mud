#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#define BBOARD          GUILDOBJ + "board.c"
#define MORE_OBJ 	"/std/board/board_more"
#define START           "/d/Terel/cedric/guild/dorm"

void reset_room();

/*
 * The Minstrel Guild Headquarters: Great Hall
 * Here players join the guild by selecting an instrument,
 * or resign the guild by releasing that instrument.
 * Cedric 1/93
 */

void
init()
{
    ::init();
    add_action("do_release", "release");        /* quit the guild */
}

int
is_fork(mixed ob)
{
    if (function_exists("break_fork",ob))
	return 1;
    else
	return 0;
}

int
do_release(string str)
{
    object  	instrument;
    mixed 	*forks;
    string  	logfile, *loglines;
    int	    	i;

    NF("Release what? Your instrument?\n");    
    setuid();
    seteuid(getuid());

    if (!str) return 0;

    if (!parse_command(str, this_player(), "%o", instrument))
	return 0;

    if (!(instrument->id("minstrel_instrument")))
	return 0;

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
	write("But you aren't a member of the minstrels? If you want " +
            "to leave the performers club simply 'rip up songbook'.\n");
	return 1;
    }

    if (this_player()->query_prop("_minstrel_i_wants_to_resign"))
    {
        setuid();
        seteuid(getuid());

	write("You release your "+instrument->query_name()+" back into the "
	+ "care of "+this_player()->query_muse_name()+". Suddenly, a wave of regret and "
	+ "sorrow crashes over you and you fall to the floor, overwhelmed. "
	+ "When you look up "+this_player()->query_muse_name()+" stands before you with a "
	+ "look of disappoinment painful to bear. Her eyes speak volumes, but "
	+ this_player()->query_muse_name()+" only speaks two words: \"Go, then.\" \n"
	+ "You lower your head in shame. The room grows dark and very, "
	+ "very quiet. When you next look up "+this_player()->query_muse_name()+" is gone, "
	+ "and you are deaf again, on your knees in a silent world...\n");

	this_player()->clear_guild_stat(SS_LAYMAN);
	this_player()->remove_guild_lay();
	this_player()->remove_cmdsoul(GUILDSOUL);
        this_player()->update_hooks();

	present("minstrel_instrument", this_player())->remove_object();
	present("minstrel_song_book", this_player())->remove_object();
	filter(deep_inventory(this_player()), is_fork)->break_fork();

	this_player()->remove_skill(SG_INSTRUMENTAL);
	this_player()->remove_skill(SG_VOCAL);
	this_player()->remove_skill(SG_READ_MUSIC);
	this_player()->remove_skill(SG_TUNE_REPAIR);
	this_player()->remove_skill(SG_FAKE_SKILL);
	this_player()->remove_skill(SG_VOCAL_DAMAGE);
	this_player()->remove_skill(SG_FLAG);

	SONGBOOK_MANAGER->remove_songbook(this_player());
        MEMBER_MANAGER->remove_member(this_player());
        PERFORM_MANAGER->remove_member(this_player());

        if (this_player()->query_default_start_location() == START)
        {
            this_player()->set_default_start_location(this_player()->query_def_start());
        }

        write_file(LEAVE_LOG, capitalize(this_player()->query_real_name()) +
            " " + ctime(time()) + "\n");
	return 1;
    }
    else
    {
	write("Are you sure you wish to do this? If so, release "
	+ "your "+instrument->query_name()+" again, and pray to "
	+ this_player()->query_muse_name()+" for mercy...\n");
	this_player()->add_prop("_minstrel_i_wants_to_resign", 1);
	return 1;
    }
}

int
check_enter()
{
    if (1 /* !BLACKLIST(this_player()) */)
    {
	write("You pass through the great hall and enter the inner "
	+ "sanctum.\n");
	return 0;
    }
    else
	write("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n");
    return 1;
}

string
do_mread()
{
    seteuid(getuid(TO()));
    clone_object(MORE_OBJ)->more(read_file(GUILDTEXT+"welcome"));
    return "";
}

void
create_room()
{
    set_short("The Great Hall of the Minstrels");
    set_long(BS("You stand in a great hall, with stone pillars and stained glass "
    + "windows that rise to dizzying heights far above your head. The architecture "
    + "here emphasizes vertical lines and light; the sunlight pouring through the "
    + "countless colored bits of glass plays along the walls and floor in a "
    + "brilliant show of ever-changing irridescence. Several pedestals, "
    + "each supporting a musical instrument, line the hall.\n")+
      "Near the front entrance stands a podium, supporting a large book.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(GUILD+"entrance", "north");
    add_exit(GUILD+"nice", "south", "@@check_enter");
    add_item(({"book", "podium"}), BS("Here on an elegant marble podium sits "
    + "a large text, bound in leather and handsomely engraved. Perhaps you "
    + "should <read> it, or even <mread> it.\n"));
    add_cmd_item(({"book", "book"}), ({"read","mread"}), 
        ({read_file(GUILDTEXT+"welcome"),"@@do_mread"})); 
    add_item(({"pedestals", "instruments", "marble pedestals"}), "Glancing "
    + "over the pedestals, you see a lute, a viol, a trumpet, a harp, a "
    + "dulcimer, a shawm, and a recorder. Perhaps you should examine each more "
    + "closely?\n");
    reset_room();
}

void
reset_room()
{
    object ob;
    
    seteuid(getuid());
    if (!present("lute", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("lute");
	ob->move(TO());
    }    
    if (!present("recorder", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("recorder");
	ob->move(TO());
    }
    if (!present("dulcimer", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("dulcimer");
	ob->move(TO());
    }
    if (!present("shawm", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("shawm");
	ob->move(TO());
    }
    if (!present("viol", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("viol");
	ob->move(TO());
    }
    if (!present("trumpet", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("trumpet");
	ob->move(TO());
    }
    if (!present("harp", TO()))
    {
	ob=clone_object(NEW_GUILDOBJ+"pedestal");
	ob->set_ped("harp");
	ob->move(TO());
    }
    
}
