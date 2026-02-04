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
 *  great Epics
 * Cedric 1/93
 */

/*
 * About Songs: The Songs accessible in this room are Epics. Epics, 
 * like Ballads, are heard by Minstrels the world over whenever one
 * is sung. Each Minstrel may write one Epic describing his or her
 * exploits. The title is always 'The Epic Of XXX' where XXX is the
 * name of the composer. Epics need not be approved by the GuildMaster
 * and may be changed at any time. Since they are in fact Ballads, the
 * Epics are placed in ~cedric/guilf/ballad and have the suffix .epic
 * appended. The first line of every Epic follows the pattern:
 * The Epic of Cedric**Cedric
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
    add_action("do_say", "sing");
    add_action("do_say", "play");
    add_action("do_say", "perform");
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
epic_list()
{
    int	i, j, size;
    string *title_list, *first_line, *title_words;
    string title, author, newtitle, return_text;
    
    say (BS(QCTNAME(TP()) + " studies the index.\n"));
    title_list = get_dir(BALLADDIR+"*.epic");
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
		
	    return_text = return_text + (i+1) +"-"+ newtitle +"\n";
    }
    return BS("The index lists " + sizeof(title_list) + " Epics:\n\n")
	+sprintf("%-*#s\n", 76, return_text);
}

int
do_read(mixed str)
{
    string *title_list, song_file;
    int	i, j, intvar;
    
    if (!str) 
	return 0;
    str = lower_case(str);
    if (str=="index"||str=="book")
    {
	write(epic_list());
	return 1;
    }
    if (TP()->query_skill(SG_READ_MUSIC)<11)
    {
	notify_fail(BS("You have not advanced far enough in the skill of reading "
	+ "music to read the Epics. Why not visit the Training "
	+ "Room?\n"));
	return 0;
    }
    title_list = get_dir(BALLADDIR+"*.epic");
    if (song_file = parse_song("epic", str, ({}), title_list, ({})))
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
    notify_fail("You needn't copy the Epics into your song book..they are "
    + "already there!\n");
    return 0;
}

string
more_list()
{
    seteuid(getuid(TO()));
    clone_object(MORE_OBJ)->more(epic_list());
    return "";
}

void
create_room()
{
    seteuid(getuid(this_object()));
    set_short("The Minstrels Tower");
    set_long(BS("You stand on the second level of the Minstrel's Tower, "
    + "in a alcove set aside from the rest of the Ballads. Here you "
    + "find the Epics, hallowed Ballads written by each Minstrel to "
    + "describe the exploits of his or her life. Compose here the Epic "
    + "which shall immortalize you and your deeds in song. And since "
    + "people change, and deeds accrue over the course of an adventurous "
    + "life, come back often and compose your Epic anew! As with the "
    + "Ballads, an Epic sung by one will be heard by Minstrels the world "
    + "over. As with all levels of the Tower, a magical silence "
    + "shall descend when a Minstrel begins composing, that none may disturb "
    + "the creative process.\n")+"A handsome index to the Epics.\n");
    add_item(({"index", "book", "handsome index"}), "This leather-bound tome "
    + "lists every Epic ever written by a Minstrel. Feel free to "
    + "<read> any Epic you please, or to <compose> your own.\n");
    add_exit(GUILD+"tower_2", "west");
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
    if (str != "the epic of "+TP()->query_name() && 
	str != "the epic of "+TP()->query_real_name() &&
	str != "epic of "+TP()->query_name() &&
	str != "epic of "+TP()->query_real_name())
    {
	TP()->CM("Realize that in this room you may only compose "
	+ "The Epic Of "+TP()->query_name()+".\n");
    }
    call_out("silence", 1, TP());
    setuid(); seteuid(getuid(TO()));
    clone_object(COMPOSE_OBJ)->new_song("the epic of "
    +TP()->query_real_name(), BALLADDIR, 1);
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
}
