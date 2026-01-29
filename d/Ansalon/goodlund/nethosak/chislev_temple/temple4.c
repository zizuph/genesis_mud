/*
 *  temple4.c
 *
 *  This is a room for the druid temple in Mithas.
 *
 *  Created by Carnak, January 2016
 */
#pragma save_binary

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"

inherit MITHAS_IN;

#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Krynn/guilds/sohm/defs.h"

#include "./local.h"

#define SOHM_I_SEARCH_BOOKSHELF   "_sohm_i_search_chislev_bookshelf"

public int     pass_tapestry(string str);
object scroll;

create_mithas_room()
{
    set_short("Temple study");
    set_long("@@long_desc");
	
    add_exit(TDIR +"temple1", "south", &pass_tapestry("south"));
    add_exit(TDIR +"temple7", "north", &pass_tapestry("north"));

    add_item(({"floor","ground","weeds","grass","rocks","dirt",
	"granite rocks"}),
    "The floor is tiled with smooth rocks and covered in dirt, some "+
    "grass and weeds have emerged from beneath the granite rocks.\n");
	 
    add_item(({"ruin","temple","building"}),
    "This must be the temple of an ancient druid order that once "+
    "populated Mithas.\n");

    add_item(({"stones","blocks","granite blocks","granite stones"}),
    "The stones are square gray granite blocks which have "+
    "been worn down by time and harsh weather.\n");

    add_item(({"walls","roots","eastern wall","wall","cracks"}),
    "The roots have found their way into the cracks between the "+
    "stones that make up the walls, seemingly reinforcing the "+
    "structural stability.\n");
	
	add_item(({"wooden roof","roof","ceiling"}),
    "The wooden roof appears to be in good condition, someone "+
    "must have maintained it well.\n");

    add_item(({"hallway"}),
    "You are in the midst of the hallway, it stretches northwards. "+
    "The southern parts of the hallway is cut off by a pale green "+
    "tapestry. There are few decorations, however a few bookcases "+
    "and tables are located in the vicinity.\n");

    add_item(({"decorations","decor","furniture"}),
    "There are few decorations, however a few bookcases and tables "+
    "are located in the vicinity. A pale green tapestry cuts off "+
    "hallway to the south.\n");
	 
    add_item(({"pale green tapestry","green tapestry","tapestry",
    "pale tapestry"}),"The thick tapestry cuts off the hallway to "+
    "the south, preserving the heat during cold winter nights. "+
    "The faded green color is an indication that the cloth has "+
    "hung there for a long time, however the quality of the "+
    "cloth is apparent, as there are few rips or tears.\n");
	 	
	add_item("cloth","The faded green color is an indication that "+
	"the cloth has hung here for a long time, however the quality "+
	"of it is apparent, as there are few rips or tears.\n");

    add_item(({"bookcases","bookcase","western wall","bookshelf",
    "bookshelves"}),
    "The western wall is adorned by bookcases, containing a "+
    "large variety of scrolls and leather-bound books.\n");

    add_item(({"leather-bound books","books","leather-bound book",
    "book","scrolls"}),
    "The books and scrolls all appear to be written in a "+
    "completely illegible writing or code, which makes you "+
    "wonder what secrets they may hold.\n");
	 
    add_item(({"plain table","plain tables","wooden table",
	"wooden tables","table","tables","plain wooden table",
	"plain wooden tables"}),
    "These are plain wooden tables, upon which bookstands and "+
    "candles have been placed.\n");
	 
    add_item(({"wooden benches","wooden bench","bench","benches",
	"plain wooden benches","plain wooden table","plain table",
	"plain tables"}),
    "The plain wooden benches are positioned on each side of "+
    "the tables.\n");
	 
    add_item(({"candle","candles","tallow candle","tallow candles",
	"bit tallow candle","big tallow candles"}),
    "These are big tallow candles, fused to the wooden table "+
    "due to their molten excess.\n");
	 
    add_item(({"bookstand","bookstands","wooden bookstands",
	"wooden bookstand","plain bookstand","plain bookstands",
	"plain wooden bookstand","plain wooden bookstands"}),
    "These are plain wooden bookstands, there is nothing "+
    "interesting about them.\n");

    add_item(({"doorway","arched doorway","arch","stone doorway"}),
    "This is a stone doorway in the form of an arch, it leads "+
    "north.\n");
	
	add_item(({"inner section","section","quarter","sleeping quarter"}),
    "The hallway extends northwards into the temples most inner "+
	"section, where the sleeping quarter is located..\n");

    add_search(({"bookshelves","bookcases","bookshelf","bookcase","books",
        "leather-bound books","books","leather-bound book","book","scrolls"}),
        10,"search_bookshelves",1);
	
}

string
long_desc()
{ 
    return ""+ 
    "You are standing inside a cramped hallway, a set of bookcases "+
    "adorn the western wall, and along the eastern wall two "+
    "wooden tables have been positioned with benches on each side. "+
    "The hallway extends northwards into the temples most inner "+
    "section, where the sleeping quarter is located. A pale green "+
    "tapestry cuts off the hallway to the south which secludes this "+
    "area from the rest of the temple, keeping the warmth in on "+
    "cold winter nights. " + sleep_desc();
}

int
pass_tapestry(string str)
{
    switch (str)
    {
        case "south":
        write("You pass through the pale green tapestry.\n");
        say(QCTNAME(TP) + " steps through the pale green tapestry.\n");
            break;
            
        case "north":
        write("You step through the arched doorway, entering the "+
        "sleeping quarters.\n");
        say(QCTNAME(TP) + " steps through the arched doorway, entering "+
        "the sleeping quarters.\n");
            break;
    }
    return 0;
}

string
search_bookshelves(object searcher, string what)
{
    if((this_player()->query_guild_name_occ() == "School of High Magic") ||
       (this_player()->query_guild_name_occ() == "Wizards of High Sorcery"))
    {
            if(SOHM_MANAGER->query_scribed_spell(this_player(),"vistoma"))
             {
		tell_room(environment(this_player()), QCTNAME(this_player()) + 
                " searches through the bookcase, looking for " +
                "something of interest.\n", ({ this_player() }));

		return ("You don't find anything in the bookcase of " +
                "interest.\n");
              }

             if(!this_player()->query_prop(SOHM_I_SEARCH_BOOKSHELF))
             {
                 tell_room(environment(this_player()), QCTNAME(this_player()) + 
                 " searches through the bookcase, and finds " +
                 "something of interest!\n", ({ this_player() }));

                 scroll = clone_object("/d/Krynn/common/scrolls/truesight_scroll");
                 scroll->move(this_player());

	         this_player()->add_prop(SOHM_I_SEARCH_BOOKSHELF, 1);

	          return ("You search through the bookcase for anything " +
                  "of interest. What is this? You come across an ancient scroll!\n");
             }

    }

    tell_room(environment(this_player()), QCTNAME(this_player()) + 
        " searches through the bookcase, looking for " +
        "something of interest.\n", ({ this_player() }));

    return ("You search through the bookcase for anything of interest. " +
            "You don't uncover anything.\n");
 
}