inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define MORE_OBJ 	"/std/board/board_more"
#define PUT_SONGS	GUILD+"mundane/"
#define COMPOSE_OBJ	GUILDOBJ+"compose_input"

/*
 * The Minstrel Guild Headquarters: Foot of the Tower
 * The Tower is the famous Library of Songs; at the foot of the tower are the
 *   layman's or Mundane Songs.
 * Cedric 1/93
 */

/*
 * About Songs: The Songs accessible in this room are Mundane Songs. These
 * are purely atmosphere and accessible to all minstrels. They are stored
 * in ~cedric/guild/mundane and have the suffix .song attached. The first
 * line of each song contains the title and the author separated by '**' :
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
mundane_list()
{
    int	i, j, size;
    string *title_list, *first_line, *title_words;
    string title, author, newtitle, return_text;
    
    say (BS(QCTNAME(TP()) + " studies the index.\n"));
    title_list = get_dir(GUILD + "mundane/"+"*.song");
    return_text = "";
    for (i=0;i<sizeof(title_list);i++)
    {	
	    first_line = explode(read_file(GUILD + "mundane/"+title_list[i],1,1)+"**","**");
	    title = first_line[0];
	    author = first_line[1];
	    newtitle = "";
	    size = sizeof(title_words = explode(title+" "," "));
	    for (j=0;j<size;j++)
		newtitle+=capitalize(title_words[j])+" ";
		
	    return_text = return_text + (i+1);
            return_text += "-"+newtitle+"by "+author;
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
	write(mundane_list());
	return 1;
    }
    if (TP()->query_skill(SG_READ_MUSIC)<5)
    {
	notify_fail(BS("You have not advanced far enough in the skill of reading "
	+ "music even to read the Mundane Songs. Why not visit the Training "
	+ "Room?\n"));
	return 0;
    }
    title_list = get_dir(MUNDANEDIR+"*.song");
    if (song_file = parse_song("mundane", str, title_list, ({}), ({}), ({})))
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
    string *title_list, *title_words, title, song_file, song_short;
    int	i, intvar;
    object song_book;
    
    title_list = get_dir(MUNDANEDIR+"*.song");
    song_book = present("minstrel_song_book", TP());
    if (TP()->query_skill(SG_READ_MUSIC)<5)
    {
	notify_fail(BS("You have not advanced far enough in the skill of reading "
	+ "music even to read the Mundane Songs. Why not visit the Training "
	+ "Room?\n"));
	return 0;
    }
    if (!song_book)
    {
	notify_fail("You don't have your song book to copy the songs into!\n");
	return 0;
    }
    if (song_file=parse_song("mundane",str,title_list,({}), ({}), ({})))
    {
	sscanf(song_file, MUNDANEDIR+"%s", song_short);
	if (song_book->add_mundane(song_short))
	{
	    notify_fail("Your song book is full; no more Mundane Songs will fit!\n");
	    return 0;
	}
	write(BS("You successfully copy "+cap_title(song_file)+ "into your song book.\n"));
	return 1;
    }
    notify_fail(BS("Which song would you like to copy? Try 'copy <xxx>' where xxx "
    +" is the number, title (in lowercase), or first word of the title.\n"));
    return 0;
}

string
more_list()
{
    seteuid(getuid(TO()));
    clone_object(MORE_OBJ)->more(mundane_list());
    return "";
}

void
create_room()
{
    seteuid(getuid(this_object()));
    set_short("The Foot of the Minstrels Tower");
    set_long(BS("You stand at the foot of the Minstrel's Tower. Within the "
    + "Tower is located the famous Library of Songs. Here, at the base of "
    + "the Tower, are catalogued the Mundane Songs. These are the limericks "
    + "and cantos of the layman, written by Minstrels to amuse or sadden the "
    + "commoners, as the occasion requires. Compose here the frivolous songs "
    + "you wish to share with your fellow minstrels. As with all levels  of "
    + "the Tower, a magical silence shall descend when a Minstrel begins "
    + "composing, that none may disturb the creative process.")+"\nA handsome "
    + "index to the Mundane Songs.\n");
    add_item(({"index", "book", "handsome index"}), "This cloth-bound tome "
    + "lists every Mundane Song ever written by a Minstrel. Feel free to "
    + "<read> or <copy> any song you please.\n");
    add_exit(GUILD+"tower_2", "up");
    add_exit(GUILD+"conservatoire", "northeast");
    add_exit(GUILD+"auditorium", "northwest");
}

int
do_mread(string str)
{
    if (str == "index"||str == "book")
    {
	TP()->catch_msg("@@more_list");
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
    call_out("silence", 1);
    setuid(); seteuid(getuid(TO()));
    clone_object(COMPOSE_OBJ)->new_song(str, PUT_SONGS);
    /* unsilence is called by the COMPOSE_OBJ */
    return 1;
}

void
silence()
{
    silenced = 1;
}

void
unsilence()
{
    silenced = 0;
}
