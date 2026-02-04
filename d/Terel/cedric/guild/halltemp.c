#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"

#define BBOARD          GUILDOBJ+"board.c"
#define MORE_OBJ 	"/std/board/board_more"

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
    add_action("do_renew", "renew");
}


int
do_renew(string str)
{
    object book, instrument, shadow;
    string ins_type, book_init_str;
    int muse;
    
    /* Parse command line */
    if (str != "oath" && str != "my oath")
    {
	NF("Renew what? your oath, perhaps?\n");
	return 0;
    }
    if (!MEMBER(TP()))
    {
	NF("You are not a member of our guild; you have no oaths to renew "
	   + "here!\n");
	return 0;
    }

    /* Destroy old stuff */
    setuid(); seteuid(getuid());
    muse = 2;
    TP()->remove_guild_lay();
    TP()->remove_cmdsoul("minstrel");
    instrument = present("minstrel_instrument", TP());
    if (!instrument)
    {
	TP()->CM("You realize as you begin your oath that you need an "
		 + "instrument to dedicate to "+TP()->query_muse_name()+". "
		 + "Perhaps you should approach the instrument of your "
		 + "choice, just as you did on that day long ago when you "
		 + "first joined the ranks of the Muses.\n");
	return 1;
    }
    ins_type = instrument->query_name();
    instrument->remove_object();
    book = present("minstrel_song_book", TP());
    if (book)
	book_init_str = book->query_auto_load();
    book->remove_object();
    
    /* Clone new stuff */
    shadow = clone_object(GUILDOBJ+"m_shadow");
    shadow->shadow_me(TP(), "layman", "cleric", GUILD_NAME);
    TP()->set_muse(muse);
    TP()->catch_msg(BS("You take hold of the carved "+ins_type+" and hold it "
	+ "aloft, dedicating it to the service of "+TP()->query_muse_name()
	+ ". Suddenly there is a brilliant flash of light, and the icon "
	+ "in your hand becomes as a living thing, warm and vibrant with "
	+ "power. The figure grows and becomes a true Minstrel's "+ins_type
	+ ", dedicated to "+TP()->query_muse_name()+" and alive with "
	+ "music...\n"));
	say(QCTNAME(TP())+" takes ahold of the carved "+ins_type+" and "
	+ "dedicates it to "+TP()->query_muse_name()+". Suddenly there is "
	+ "a brilliant flash of light and "+QTNAME(TP())+" is left holding "
	+ "a true Minstrel's instrument!\n");
    instrument = clone_object(GUILDOBJ+"instrument");
    instrument->set_name(ins_type);
    instrument->move(TP(),1);
    instrument->do_things();
    book = clone_object(GUILDOBJ+"song_book");
    book->set_owner(TP());
    book->init_args(book_init_str);
    book->move(TP(),1);

    /* assign the minstrel a random voice */
    TP()->set_random_voice(TP()->query_real_name);
    
    /* Committee members get special stuff */
    if (TP()->query_special_title())
    {
	object scroll;

	scroll = clone_object(GUILDOBJ + "scroll");
	scroll->move(TP(),1);
    }
    return 1;
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
    if (!parse_command(str, TP(), "%o", instrument))
	return 0;
    if (!(instrument->id("minstrel_instrument")))
	return 0;
    if (TP()->query_prop("_minstrel_i_wants_to_resign"))
    {
	TP()->CM("You release your "+instrument->query_name()+" back into the "
	+ "care of "+TP()->query_muse_name()+". Suddenly, a wave of regret and "
	+ "sorrow crashes over you and you fall to the floor, overwhelmed. "
	+ "When you look up "+TP()->query_muse_name()+" stands before you with a "
	+ "look of disappoinment painful to bear. Her eyes speak volumes, but "
	+ TP()->query_muse_name()+" only speaks two words: \"Go, then.\" \n"
	+ "You lower your head in shame. The room grows dark and very, "
	+ "very quiet. When you next look up "+TP()->query_muse_name()+" is gone, "
	+ "and you are deaf again, on your knees in a silent world...\n");
	TP()->clear_guild_stat(SS_LAYMAN);
	TP()->remove_guild_lay();
	TP()->remove_cmdsoul("minstrel");
	present("minstrel_instrument", TP())->remove_object();
	present("minstrel_song_book", TP())->remove_object();
	forks = filter(deep_inventory(TP()), is_fork);
	for (i=0;i<sizeof(forks);i++)
	{
	    forks[i]->break_fork();
	}
	TP()->remove_skill(SG_INSTRUMENTAL);
	TP()->remove_skill(SG_VOCAL);
	TP()->remove_skill(SG_READ_MUSIC);
	TP()->remove_skill(SG_TUNE_REPAIR);
	TP()->remove_skill(SG_FAKE_SKILL);
	TP()->remove_skill(SG_VOCAL_DAMAGE);
	TP()->remove_skill(SG_FLAG);
	TP()->remove_skill(SS_LANGUAGE);
	logfile = read_file(LOGFILE);
	loglines = explode(logfile+"\n", "\n");
	for (i=0;i<sizeof(loglines);i++)
	{
	    if (member_array(TP()->query_name(), explode(loglines[i], ":"))!= -1)
		loglines -= ({loglines[i]});
	}
	logfile = implode(loglines, "\n");
	rm(LOGFILE);
	write_file(LOGFILE, logfile);
	return 1;
    }
    else
    {
	TP()->CM("Are you sure you wish to do this? If so, release "
	+ "your "+instrument->query_name()+" again, and pray to "
	+ TP()->query_muse_name()+" for mercy...\n");
	TP()->add_prop("_minstrel_i_wants_to_resign", 1);
	return 1;
    }
}

int
check_enter()
{
    if (1 /* !BLACKLIST(TP()) */)
    {
	TP()->catch_msg("You pass through the great hall and enter the inner "
	+ "sanctum.\n");
	return 0;
    }
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
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
    + "each supporting a musical instrument, line the hall.\n")+"Near the front entrance "
    + "stands a podium, supporting a large book.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_exit(GUILD+"entrance", "north");
    add_exit(GUILD+"nice", "south", "@@check_enter");
    add_item(({"book", "podium"}), BS("Here on an elegant marble podium sits "
    + "a large text, bound in leather and handsomely engraved. Perhaps you "
    + "should <read> it, or even <mread> it.\n"));
    add_cmd_item(({"book", "book"}), ({"read","mread"}), ({read_file(GUILDTEXT+"welcome"),"@@do_mread"})); 
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
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("lute");
	ob->move(TO());
    }    
    if (!present("recorder", TO()))
    {
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("recorder");
	ob->move(TO());
    }
    if (!present("dulcimer", TO()))
    {
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("dulcimer");
	ob->move(TO());
    }
    if (!present("shawm", TO()))
    {
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("shawm");
	ob->move(TO());
    }
    if (!present("viol", TO()))
    {
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("viol");
	ob->move(TO());
    }
    if (!present("trumpet", TO()))
    {
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("trumpet");
	ob->move(TO());
    }
    if (!present("harp", TO()))
    {
	ob=clone_object(GUILDOBJ+"pedestal");
	ob->set_ped("harp");
	ob->move(TO());
    }
    
}
