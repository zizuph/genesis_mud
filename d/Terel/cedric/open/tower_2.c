inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define MORE_OBJ 	"/std/board/board_more"
#define PUT_SONGS	GUILD+"submit/"
#define CHECK_DIR	BALLADDIR
#define COMPOSE_OBJ	GUILDOBJ+"compose_input"

/*
 * The Minstrel Guild Headquarters: Midway up the Tower
 * The Tower is the famous Library of Songs; on the second level are the
 *  great Ballads
 * Cedric 1/93
 */

/*
 * About Songs: The Songs accessible in this room are Ballads. A Ballad
 * sung by a Minstrel shall be heard by all other Minstrels in the game.
 * Since ballads also write themselves automatically into the song-books of
 * every Minstrel, they serve as a sort of guild-line, accessible to the entire
 * guild. Ballads written by players are placed in ~cedric/guild/submit
 * until the Guildmaster has a chance to review them. If accepted as Ballads,
 * they are placed in ~cedric/guild/ballad and have the suffix .song attached. 
 * The first line of each contains the title and the author separated by '**' :
 * Row, Row, Row Your Boat**Cedric
 */

int silenced = 0;

void
init()
{
    ::init();
    add_action("do_compose", "compose");
    add_action("do_read", "read");
    add_action("do_mread", "mread");
    add_action("do_copy", "copy");
    add_action("do_say", "say");
    add_action("do_say", "shout");
    add_action("do_say", "'", 1);
}

int
do_say(string str)
{
    if (silenced)
    {
	write("The room is silenced; you move your mouth but no sound "
	+ "emerges.\n");
	return 1;
    }
    return 0;
}

string    
ballad_list()
{
    int	i, j, size;
    string *title_list, *first_line, *title_words;
    string title, author, newtitle, return_text;
    
    say (BS(QCTNAME(TP()) + " studies the index.\n"));
    title_list = get_dir(BALLADDIR+"*.song");
    return_text = "";
    for (i=0;i<sizeof(title_list);i++)
    {	
	    first_line = explode(read_file(BALLADDIR+title_list[i],1,1),"**");
	    title = first_line[0];
	    author = first_line[1];
	    newtitle = "";
	    size = sizeof(title_words = explode(title+" "," "));
	    for (j=0;j<size;j++)
		newtitle+=capitalize(title_words[j])+" ";
		
	    return_text = return_text + (i+1);
            return_text += "-"+newtitle+"by "+author+"\n";
    }
    return BS("The index lists " + sizeof(title_list) + " songs by title "
    + "and author:\n\n")+sprintf("%-*#s\n", 76, return_text);
}

int
do_read(mixed str)
{
    string *title_list, song_file;
    int	i, j, intvar;
    
    if (!str) 
	return 0;
    if (str=="index"||str=="book")
    {
	write(ballad_list());
	return 1;
    }
    if (TP()->query_skill(SG_READ_MUSIC)<11)
    {
	notify_fail(BS("You have not advanced far enough in the skill of reading "
	+ "music to read the Ballads. Why not visit the Training "
	+ "Room?\n"));
	return 0;
    }
    title_list = get_dir(BALLADDIR+"*.song");
    if (song_file = parse_song("ballad", str, ({}), title_list, ({})))
    {
	clone_object(MORE_OBJ)->more(read_file(song_file, 2));
	return 1;
    }
    notify_fail(BS("Which song would you like to read? Try <read xxx> where xxx "
    +" is the number, title (in lowercase), or first word of the title.\n"));
    return 0;
}

int
do_copy(string str)
{
    notify_fail("You needn't copy the Ballads into your song book..they are "
    + "already there!\n");
    return 0;
}

string
more_list()
{
    seteuid(getuid(TO()));
    clone_object(MORE_OBJ)->more(ballad_list());
    return "";
}

void
create_room()
{
    seteuid(getuid(this_object()));
    set_short("The Minstrels Tower");
    set_long(BS("You stand on the second level of the Minstrel's Tower. Within the "
    + "Tower is located the famous Library of Songs. Here, halfway up the Tower, "
    + "are catalogued the Ballads. These are songs of such musical potency that "
    + "when one Minstrel performs a Ballad all the guild shall hear it. "
    + "In addition, the Ballads automagically write themselves into each Minstrel's "
    + "song book, so there is no need to copy these.  The Minstrels are "
    + "known to use the Ballads as a form of communication over great distances. "
    + "Due to the great power of these songs, each Ballad a Minstrel composes must be "
    + "approved by the Guildmaster. When you compose a song here, it shall be "
    + "submitted to the master; if approved, the song shall be added "
    + "to the Library. As with all levels of the Tower, a magical silence "
    + "shall descend when a Minstrel begins composing, that none may disturb "
    + "the creative process.\n")+"A small alcove is set aside in the "
    + "eastern portion of the room.\nA handsome index to the Ballads.\n");
    add_item(({"index", "book", "handsome index"}), "This leather-bound tome "
    + "lists every Ballad ever written by a Minstrel. Feel free to "
    + "<read> any song you please.\n");
    add_exit(GUILD+"tower_3", "up");
    add_exit(GUILD+"tower_1", "down");
    add_exit(GUILD+"tower_2a", "east");
    add_prop(ROOM_I_INSIDE, 1);
}

int
do_mread(string str)
{
    if (str == "index"||str == "book")
    {
	write("@@more_list@@");
	say(QCTNAME(TP())+" studies the index.\n");
	return 1;
    }
    return 0;
}

int
do_compose(string str)
{
    if (!str)
    {
	notify_fail("Usage: compose <title of song>. The author's name (yours) "
	+ "will be appended.\n");
	return 0;
    }
    call_out("silence", 1, TP());
    setuid(); seteuid(getuid(TO()));
    clone_object(COMPOSE_OBJ)->new_song(str, PUT_SONGS, BALLADDIR);
    /* unsilence is called by the COMPOSE_OBJ */
    return 1;
}

void
silence(object composer)
{
    say(BS("Your skin tingles a though a spell were being cast, yet you hear "
    + "no magic words. In fact you hear nothing at all.."), composer);
    silenced = 1;
}

void
unsilence(object composer)
{
    silenced = 0;
    composer->catch_msg(BS("Thanks for your submission! The guildmaster will review your song "
    + "and decide whether it is worthy to be deemed a Ballad.\n"));
}
