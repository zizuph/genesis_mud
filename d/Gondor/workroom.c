/*
 *	/d/Gondor/workroom.c
 *
 *      Modification log:
 *      26-aug-1997, Olorin: query_domain_aliases
 *
 *	12-June-1998, Gnadnar:	added npcsize, general cleanup
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <std.h>
#include <composite.h>
#include <login.h>

#include "/d/Gondor/defs.h"

/* prototypes */
public void		create_gondor();
public string		long_func() ;
public int		block_mortals();
public string		get_mailreader();
public string		exa_clock();
public varargs string	*query_domain_aliases(string guild);
public int		npcsize(object npc, string hdesc, string wdesc);


/*
 * Function name:	create_gondor
 * Description	:	set up the workroom
 */
public void
create_gondor()
{
    object  board;
    string  name;

    set_short("This is the workroom of the domain Gondor");
    set_long(long_func);
    add_prop(ROOM_I_INSIDE,1);

    /* room should not be unloaded */
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit("/d/Gondor/ME_ideas", "north",        block_mortals, 0);
    add_exit("/d/Gondor/idearoom", "east",         block_mortals, 0);
    add_exit("/d/Gondor/domain_office", "office",  block_mortals, 0);
    /*add_exit("/d/Mordor/workroom", "mordor", 
	     &RING_QUEST_MASTER->domain_closed());
     rhovanion is closed -- gnadnar
     * add_exit("/d/Rhovanion/workroom","rho",        block_mortals, 0);
     */
    add_exit("/d/Gondor/lorien/flet", "lorien", block_mortals, 0);
    add_exit(RINGQ_DIR + "rq_master",      "up",   block_mortals, 0);
    add_exit(EDORAS_DIR + "rooms/guild",   "west", block_mortals, 0);
    add_exit(MINAS_DIR + "rooms/mtoffice", "down", block_mortals, 0);
    add_exit(MORGUL_DIR + "city/rooms/boardroom","south", block_mortals, 0);
    add_exit(MAGES_DIR + "boardroom",      "morgul",      block_mortals, 0);
    add_exit(PELAR_DIR + "misc/pel_office","pelargir",    block_mortals, 0);
    add_exit(ITH_DIR + "emyn-arnen/obj/scabbard_master",
	"scabbard", block_mortals, 0);
    add_exit("/d/Gondor/private/boards/announceroom", "announce", block_mortals, 0);

    if (!present("board",this_object()))
    {
	board = clone_object("/std/board");
	name = "/d/Gondor/common/guild/boards";
	if (file_size(name) != -2)
	    mkdir(name);
	board->set_board_name(name + "/wizboard");
	board->set_num_notes(30);
	board->set_silent(0);
	board->set_show_lvl(1);
	board->set_remove_rank(WIZ_NORMAL);
	board->set_remove_str("Nope, you cannot remove that note.");
	board->move(this_object());
    }
   // clone_object("/d/Gondor/private/boards/gondorprivate")->move(TO, 1);

    add_item(({"clock", "time", }), VBFC_ME("exa_clock"));
    add_cmd_item( ({ "reader", "mail", "mailreader", }),
	"get", get_mailreader);

} /* create_gondor */


/*
 * Function name:	long_func
 * Description	:	VFBC for room long (including time of day effects)
 * Returns	:	string -- the long desc
 */
public string
long_func() 
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            longtxt =
	"In this room the wizards of Gondor meet to discuss the future "+
	"of the domain Gondor, to get help with their coding, or to "+
	"make announcements of different kinds. The bulletin board may "+
	"also be used by other wizards of the other Middle Earth "+
	"domains, to encourage better cooperation. A clock on the wall "+
	"shows the time in Middle Earth and the status of the Ring "+
	"Quest. An exit north leads to the Middle Earth bulletin board, "+
	"and another east to the idearoom of Gondor. Other exits are "+
	"leading to various parts of the domain and to the workrooms "+
	"of other Middle Earth domains. Through the window in the "+
	"north wall, you can see ";

    switch (time)
    {
    case "night":
	longtxt += "nothing but darkness outside, as it is night "+
		   "in Middle Earth.";
        break;
    case "early morning":
	longtxt += "the sun rising in the east, casting long shadows "+
		   "over Gondor.";
        break;
    case "morning":
    case "afternoon":
	longtxt += "the green fields of Gondor outside the Walls of "+
		   "Minas Tirith.";
        break;
    case "noon":
	longtxt += "that the sun is almost at its peak on its way "+
		   "across the sky. It is noon in Middle Earth.";
        break;
    case "evening":
	longtxt += "the sun is setting, colouring the western sky "+
		   "golden red.";
        break;
    }
    if (clock->query_war() >= 1) 
    {
	longtxt += " Massive grey clouds cover the east. War is on.";
    }

    return "The Gondor Meetingroom.\n" + BSN(longtxt);
} /* long_func */


/*
 * Function name:	block_mortals
 * Description	:	prevent mortals from taking restricted exits
 * Returns	:	0 if exit is allowed, 1 if not
 */
public int
block_mortals()
{
    if (TP->query_wiz_level())
    {
        return 0;
    }

    write("That exit is only for wizards.\n");
    return 1;
}


/*
 * Function name:	get_mailreader
 * Description	:	let wizards get a mailreader
 * Returns	:	string -- the results of the "get"
 */
public string
get_mailreader()
{
    object	tp = TP;

    if (!tp->query_wiz_level())
    {
	return "Get what?\n";
    }
    if (objectp(present("mailreader", TP)))
    {
        return "You are already carrying a mail reader.\n";
    }
    clone_object("/secure/mail_reader")->move(TP);
    return "You get a new mailreader.\n";
} /* get_mailreader */


/*
 * Function name: exa_clock
 * Description:   VBFC for the description of the clock in this room.
 * Returns:       string -- the description
 */
public string
exa_clock()
{
    return RING_QUEST_MASTER->exa_clock();
} /* exa_clock */


/*
 * Function name: query_domain_aliases
 * Description:   the names of the Lord and the Steward plus the
 *                guildmasters for different guilds of the domain 
 * Argument:      string guild - guild name
 * Returns:       string * -- guildmaster alias if strlen(guild),
 *                otherwise the names of Lord and Steward
 */
public varargs string *
query_domain_aliases(string guild)
{
    string *aliases = ({ }),
	    name;

    name = SECURITY->query_domain_lord(getuid());
    if (stringp(name) &&
	strlen(name))
    {
	aliases  = ({ name });
    }

    name = SECURITY->query_domain_steward(getuid());
    if (stringp(name) &&
	strlen(name))
    {
	aliases += ({ name });
    }

    // We really want to make sure that the return values are ok:
    // "Just because you're paranoid doesn't mean ..."
    if (!strlen(guild))
    {
	return aliases - ({ 0 }) - ({ "" });
    }

    switch (guild)
    {
    case RANGER_S_GUILD_NAME:
        aliases -= SECURITY->query_guild_masters("ranger");
        aliases += SECURITY->query_guild_masters("ranger");
	break;
    case MORGUL_S_GUILD_NAME:
        aliases -= SECURITY->query_guild_masters("mage");
        aliases += SECURITY->query_guild_masters("mage");
	break;
    case DUNEDAIN_S_GUILD_NAME:
        aliases -= SECURITY->query_guild_masters("dunedain");
        aliases += SECURITY->query_guild_masters("dunedain");
	break;
    case ROCKFRIEND_S_GUILD_NAME:
        aliases -= SECURITY->query_guild_masters("rockfriend");
        aliases += SECURITY->query_guild_masters("rockfriend");
	break;
    case MILITIA_S_GUILD_NAME:
        aliases -= SECURITY->query_guild_masters("militia");
        aliases += SECURITY->query_guild_masters("militia");
    }

    // We really want to make sure that the return values are ok:
    // "Just because you're paranoid doesn't mean ..."
    return aliases - ({ 0 }) - ({ "" });
} /* query_domain_aliases */


/*
 * Function name:	npcsize
 * Description	:	set CONT_I_HEIGHT, CONT_I_WEIGHT and
 *			CONT_I_VOLUME of an npc to give the 
 *			desired appearance
 * Arguments	:	object npc -- the npc
 *		:	string hdesc -- the desired height desc
 *				         (e.g., "tall")
 *		:	string wdesc -- the desired width desc
 *					(e.g., "plump")
 * Returns	:	1 on success, 0 on failure
 */
public int
npcsize(object npc, string hdesc, string wdesc)
{
    int		hindex,
		windex,
		*spread,
		spreadsize,
		height,
		*raceattr;

    if (!objectp(npc) ||
	!npc->query_npc() ||
	!strlen(hdesc) ||
	!strlen(wdesc))
    {
	return 0;
    }
    raceattr = RACEATTR[npc->query_race()];
    if (sizeof(raceattr) < 6 ||
        raceattr[0] <= 0 ||
	raceattr[4] <= 0 ||
	raceattr[5] <= 0)
    {
	return 0;
    }
    if (hdesc == "normal")
    {
	hdesc = "of normal length";
    }
    if ((hindex = member_array(hdesc, HEIGHTDESC)) < 0)
    {
	return 0;
    }
    if (wdesc == "normal")
    {
	wdesc = "of normal width";
    }
    if ((windex = member_array(wdesc, WIDTHDESC)) < 0)
    {
	return 0;
    }
    spread = SPREAD_PROC;
    spreadsize = sizeof(spread);
    if (hindex >= spreadsize ||
        windex >= spreadsize)
    {
	return 0;
    }

    height = ((raceattr[0] * spread[hindex]) / 100);
    npc->add_prop(CONT_I_HEIGHT, height);
    npc->add_prop(CONT_I_WEIGHT,
	(((raceattr[5] * spread[windex]) / 100) * height));
    npc->add_prop(CONT_I_VOLUME,
	(raceattr[4] * 1000));
    return 1;
} /* npcsize */
