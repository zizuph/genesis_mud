/** tower_power.c **/

#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"

#define MORE_OBJ        "/std/board/board_more"
#define COMPOSE_OBJ     GUILDOBJ+"compose_input"

/*
 * The Minstrel Guild Headquarters: Top of the Tower
 * The Tower is the famous Library of Songs; on the top level is the
 * music most sacred to the Minstrels: the Songs of Power.
 * Cedric 1/93
 */

/*
 * About Songs: The Songs accessible in this room are Songs of Power. These
 * are essentially spells, though many of them rely not so much on magic as
 * on the beauty and power of sound for their effect. Naturally mortals 
 * cannot contribute Songs of Power, as they can Mundane Songs and Ballads, 
 * so no 'compose' function is supported here. 
 * The first line of each contains the title and the author separated by '**':*/
                /**Row, Row, Row Your Boat**Cedric**/

int silenced = 0;

void
init()
{
    ::init();
    add_action("do_compose", "compose");
    add_action("do_read", "read");
    add_action("do_mread", "mread");
    add_action("do_copy", "copy");
}

string    
power_list()
{
    int     i, j, size;
    string  *title_list, *first_line, *title_words;
    string  title, author, newtitle, return_text;
    
    say (BS(QCTNAME(TP()) + " studies the index.\n"));
    title_list = get_dir(POWERDIR+"*.c");
    return_text = "";
    for (i=0;i<sizeof(title_list);i++)
    {   
            first_line = explode(read_file(POWERDIR+title_list[i],1,1),"**");
            title = first_line[1];
            author = first_line[2];
            newtitle = "";
            size = sizeof(title_words = explode(title+" "," "));
            for (j=0;j<size;j++)
                newtitle+=capitalize(title_words[j])+" ";
                
            return_text = return_text + (i+1);
            return_text += "-"+newtitle + "\n";
    }
    return BS("The index lists " + sizeof(title_list) + " songs by title "
    + "only:\n\n")+sprintf("%-*#s\n", 76, return_text);
}

int
do_read(mixed str)
{
    string *title_list, song_file;
    int i, j, intvar;
    object the_song;
    
    seteuid(getuid(TO()));
    if (!str) 
        return 0;
    if (str=="index"||str=="book")
    {
        write(power_list());
        return 1;
    }
    title_list = get_dir(POWERDIR+"*.c");
    if (song_file = parse_song("power", str, ({}), ({}), ({}), title_list))
    {
        the_song = clone_object(song_file);
        if (song_file->query_read_skill() > TP()->query_skill(SG_READ_MUSIC))
        {
            write(BS("You pore over the music, but it is too complex; "
            + "the Song of Power is beyond your skills and your careful study "
            + "is in vain.\n"));
            the_song->remove_object();
            return 1;
        }
        else
        {
            write(BS(the_song->query_purpose()));
            the_song->remove_object();
            return 1;
        }
    }
    NF(BS("Which song would you like to read? Try <read xxx> where xxx "
    +" is the number, title (in lowercase), or first word of the title.\n"));
    return 0;
}

int
do_copy(string str)
{
    string *title_list, *title_words, title, song_file, song_short;
    string *songs;
    int i, intvar;
    object song_book;

    setuid();
    seteuid(getuid());

    songs = map(get_dir(POWER_SONGS_DIR + "*.c"), &operator(+)(POWER_SONGS_DIR));
    title_list = map(songs, &->query_name());

    song_book = present("minstrel_song_book", TP());
    if (!song_book)
    {
        NF("You don't have your song book to copy the songs into!\n");
        return 0;
    }
    if ((i = member_array(str, title_list)) >= 0)
    {
        song_file = songs[i];
        if (song_file->query_read_skill() > TP()->query_skill(SG_READ_MUSIC))
        {
            NF(BS("You pore over the music, but it is too complex; "
            + "this Song of Power is beyond your skills and your attempt to "
            + "copy is in vain.\n"));
            return 0;
        }
        else
        {
            if (!song_book->add_power(song_file[strlen(POWER_SONGS_DIR)..-3]))
            {
                NF("Your song book is full; no more Songs of Power will fit!\n");
                return 0;
            }
            write(BS("You successfully copy "+cap_title(song_file)+ "into your song book.\n"));
            return 1;
        }
    }
    NF(BS("Which song would you like to copy? Try 'copy <xxx>' where xxx "
    +" is the number, title (in lowercase), or first word of the title.\n"));
    return 0;
    
}

void
create_room()
{
    seteuid(getuid(this_object()));
    set_short("The Minstrels Tower");
    set_long(BS("You stand on the third level of the Minstrel's Tower which "
    + "houses the famous Library of Songs. Here, on the top level of the Tower, "
    + "are catalogued the most sacred songs of all: the Songs of Power. These "
    + "are the songs of Muses; "
    + "music and magic fused together with such artistry that the "
    + "Muse herself may work wonders through the notes. Use the Songs "
    + "of Power with care, for one does not invoke a Muse lightly. Also "
    + "be aware that the Songs of Power vary greatly in complexity; the "
    + "ability to copy and perform a particular Song depends not only on "
    + "skill but on health, discipline, and devotion to one's Muse. \n")
    + "An ancient index to the Songs of Power.\n");
    
    add_item(({"index", "book", "ancient index"}), BS("This ancient tome "
    + "lists every Song of Power available to the Minstrels. Feel free to "
    + "<read> any song you please to get an idea of its purpose.\n"));
    
    add_exit(GUILD+"tower_roof", "up");
    add_exit(GUILD+"tower_ballad", "down");
    add_prop(ROOM_I_INSIDE, 1);
}

string
more_list()
{
    seteuid(getuid(TO()));
    clone_object(MORE_OBJ)->more(power_list());
    return "";
}

int
do_mread(string str)
{
    if (str == "index"||str == "book")
    {
	more_list();
        say(QCTNAME(TP())+" studies the index.\n");
        return 1;
    }
    return 0;
}

int
do_compose(string str)
{
    NF(BS("Due to their great musical and magical power, only the "
      + "Guildmaster, with the help of the Muses, may compose a Song " 
      + "of Power.\n"));
    return 0;
}
