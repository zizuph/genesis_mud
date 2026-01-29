/* Created by Dajala
 * Members recieve promotions in this room and may put their 
 * suggestions for new modules up on the board.
 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>

#include "guild.h"

inherit "/d/Krynn/std/room";

object board;
string head_tinker_name;
int stored_max_level, gender, create_again = 0;

/* prototype */
void reset_room();

void
create_room()
{
    set_short("Planning chamber");

    set_long("This room is a mess! Piles of papers are stacked "
      + "on desks all around the cave. Papers cover the floor. "
      + "You see gnomes working at blackboards inventing and "
      + "drawing new fantastic machines. You feel obliged to "
      + "become busy and contribute to the technological advance "
      + "of gnomekind.\nThere is a door with a small plaque "
      + "nailed to it, leading west. A bulletin board "
      + "is placed in the middle of the room and a red poster "
      + "on the south wall.\n");

    add_exit(GGUILD + "joinroom", "north", 0);
    add_exit(GGUILD + "gmaster", "west", "@@wizcheck");
    add_exit(GGUILD + "folderro", "south", 0);
    add_exit(GGUILD + "conference", "east", 0);

    INSIDE;
    LIGHT;

    add_item(({"paper", "papers"}), "You cannot find any order, but "
      + "what you find are bins hidden underneath.\n");
    add_item(({"bin", "bins"}), "They are filled with papers.\n");
    add_item("door", "There is a golden plaque on the wooden door.\n");
    add_item(({"blackboard", "blackboards"}), "You watch amazed and "
      + "feel proud to be a part of it all.\n");
    add_item(({"plaque", "poster", "red poster", "small plaque"}),
      "You can read it.\n");
    add_item(({"box", "black box"}), "It is rather featureless, black "
      + "and has a little hole in the front staring at you.\n");
    add_cmd_item("door", "approach", "You hear a faint CLICK from a "
      + "black box fixed over door.\n");
    add_cmd_item("door", "open", "The door is locked.\n");
    add_cmd_item(({"plaque", "small plaque"}), "read", "The plaque "
      + "reads: Guildmasters office.\nKnock to receive your "
      + "promotion.\n");
    reset_room();
}

int
wizcheck()
{
    if(!TP->query_wiz_level())
    {        
	write("Amazing! You cannot find a handle on this door. "
	  + "But when you approached the door you heard a faint "
	  + "CLICK from a tiny black box over the door. In the "
	  + "front of the box there is a little hole which you "
	  + "feel looking at you.\n");
	return 1;
    }
    if(TP->query_name() == C(WIZARD_IN_CHARGE))
	write("Welcome Guildmaster! Work awaits you...\n");
    else
	write("The door slides open.\nSince you are a wizard you "
	  + "are allowed to have a look into this room. Please do "
	  + "not touch any of the levers or gears. It is dangerous "
	  + "to finger with a Gnomes' dearest toys.\n");
    return 0;
}

string
name()
{
    if(head_tinker_name == "0" || !head_tinker_name)
	return "vacant";
    return "held by " + head_tinker_name;
}

void
reset_room()
{
    string title;
    
    seteuid(getuid(TO));
    if (!board)
    {
	board = clone_object(GOBJ + "noteboard");
	board->set_board_name("/d/Krynn/gnome/guild/log/board_data");
	board->set_long("        This is the private inventor's board.\n"
	  + "\nUse it to share your inventions of new modules and "
	  + "machines with your fellow inventors and the "
	  + "Guildmaster or for discussion of odler subjects.\n"
	  + "You are welcome to post frequently "
	  + "but please do not abuse it.\n\n");
	board->set_silent(0);
	board->set_keep_discarded(1);
	board->set_num_notes(30);
	board->set_remove_str("Sorry, only the guildmaster may remove the "
	  + "notes.\n");
	board->set_short("Board for New Inventions");
	board->add_name("Board for New Inventions");
	board->add_name("board for new inventions");
	board->move(TO,1);
    }
    restore_object(GMASTER_SAVE);
    remove_cmd_item(({"poster", "red poster"}));
    tell_room(TO, "The door to the west slides open " 
	    + "noisily and the guildmaster's assistant comes in "
	    + "to put up a new poster. He then leaves again, the "
	    + "door shutting behind him.\n");
    if(gender == 1)
	title = GNOME_TITLES_F[14];
    else
	title = GNOME_TITLES[14];	
    add_cmd_item(({"poster", "red poster"}), "read", 
	"The poster reads: The office of " + title
	+ " of the Inventors Guild is currently "
	+ name() + ".\n");
}

void
init()
{
    ::init();
    ADA("knock");
}

void
update_file(int line, string *file)
{
    int i;

    rm(PROMOTELOG);
    for (i=0;i<sizeof(file);i++)
    {
	if (i != line)
	    write_file(PROMOTELOG, file[i] + "\n");
    }
}

int
knock(string str)
{
    NF("Knock where?\n");
    if (str != "door" && str != "on door" && str != "on the door")
	return 0;
    write("You knock on the door.\n");
    say(QCTNAME(TP) + " knocks on the door to the west.\n");
    set_alarm(4.0, -1.0, "do_knock", TP);
    return 1;
}

int
do_knock(object player)
{
    string *file, who, *dummy;
    int flag, i, old;

    file = explode(read_file(PROMOTELOG), "\n");
    who = implode(explode(player->query_nonmet_name(player), " "), "");
    tell_room(TO, "The door slides open noisily and the guildmaster's "
      + "assistant appears in the opening telling you:\n");
    flag = 0;
    for(i=0;i<sizeof(file);i++)
    {
	dummy = explode(file[i], " - ");
	if((player->query_name()) == dummy[0])
	{
	    if(flag == 0)
	    {
		tell_room(TO, "YouHaveEarnedYourselfAPromotion,"
		  + who + "!\n");
		player->catch_msg("\nYou have been promoted!\n\n");
		old = (player->query_skill(SS_PROMOTE));
		player->set_skill(SS_PROMOTE, old+1);
		if(old < 3 && (TP->query_stat(6) > ({L8,45,55})[old]))
		    TP->set_guild_stat(6, 
		      TP->stat_to_exp(({L8,45,55})[old]));
		update_file(i, file);
		flag = 1;
		write_file(GOT_PROMOTED, dummy[0] + " promoted "
		  + extract(ctime(time()), 4, 15) + " from "
		  + old + " to " + (old+1) + ". Guildmaster "
		  + "promoted " + dummy[1] + "\n");
	    }
	    else
		tell_room(TO, "He then adds: Ohh,ThereMayBeEvenFurther"
		  + "PromotionForYou!\n");
	}
    }
    if(!flag)
	tell_room(TO, "WhyShouldIPromoteYou," + who + "?Invent"
	  + "SomethingFirst.\n");
    tell_room(TO, "Then, as he steps back, the door noisily slides shut "
      + "again.\n");
    set_alarm(3.0, -1.0, "klick");
    return 1;
}

void
klick()
{
    tell_room(TO, "You hear a soft 'click' from the box over "
      + "the door.\n");
}
