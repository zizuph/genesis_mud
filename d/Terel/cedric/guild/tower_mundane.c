/** tower_mundane.c **/

#pragma save_binary

inherit "/std/room.c";

#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"

#ifdef INDEX_OPEN
#include <macros.h>
#include <options.h>


#define EDIT_OBJ        "/obj/edit"
#define MORE_OBJ        "/std/board/board_more"
#define PUT_SONGS       MUNDANEDIR

/*
 ****************************************************************************
 * The Minstrel Guild Headquarters:  Foot of the Tower.
 * The Tower is the famous Library of Songs; at the foot of the tower 
 * are the layman's or Mundane Songs.
 *
 * Cedric 1/93
 */

/*
 * About Songs:  The Songs accessible in this room are Mundane Songs. These
 *               are purely for atmosphere and accessible to all minstrels. 
 *               They are stored in ~cedric/guild/Mundanes and have the 
 *               suffix .song.  The first line of each song contains the 
 *               title and the author separated by '**'.  Stanzas are 
 *               separated by a blank line.  Text which is meant to comment
 *               a song but is not meant to be sung is noted with a '#'.  
 *               The last line of each song contains only the string '**'.
 *               Example:  Row, Row, Row Your Boat**Cedric
 *                         # A catchy little tune I like.     
 *                              <text of verse 1>
 *                              <text of verse 1>
 *              
 *                              <text of verse 2>
 *                              <text of verse 2>
 *
 *                         **                         
 */

/*
 * Globals:
 */
int silenced = 0;
int new_song;
string song_header;
string filename;
string global_pattern;


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
#endif INDEX_OPEN

void
init()
{
    ::init();
#ifdef INDEX_OPEN
    add_action("do_delete", "delete");
    add_action("do_compose", "compose");
#endif
    add_action("do_read", "read");
    add_action("do_read", "mread");
#ifdef INDEX_OPEN
    add_action("do_copy", "copy");
    add_action("do_say", "say");
    add_action("do_say", "shout");
    add_action("do_say", "'", 1);
    add_action("do_say", "sing");
    add_action("do_say", "play");
    add_action("do_say", "perform");
#endif
}

/*
 ****************************************************************************
 * Name:         check_enter
 * Description:  
 *
 * Arguments:
 * Returns:
 */

int
check_enter()
{
    if (MEMBER(this_player()) || this_player()->query_wiz_level())
    {
        return 0;
    }
    else
    {
        write("That way lies the inner sanctum of the Minstrels; " +
              "only the initiated may pass.\n");
        return 1;
    }
}

#ifdef INDEX_OPEN
/*
 ****************************************************************************
 * Name:         do_say
 * Description:  
 *
 * Arguments:
 * Returns:
 */

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

/*
 ****************************************************************************
 * Name:         mundane_list
 * Description:  
 *
 * Arguments:
 * Returns:
 */

string    
mundane_list()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "mundane.titles";

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo mundane songs\n";
    }

    return sprintf("%-#*s\n", scrw, str);
#if 0
    string *title_list;

    say (BS(QCTNAME(TP()) + " studies the index.\n"));
    
    title_list = get_dir(MUNDANEDIR+"*.song");
    
    return "The index lists " + sizeof(title_list) + " songs by title "
        + "and author, too many to list. You can restrict "
        + "songs by author, title, or date:\n"
        + "\t'read authors X' lists all songs by authors whose names begin with X.\n"
        + "\t'read titles X' lists all songs whose titles begin with X.\n"
        + "\t'read recent [num] X' lists the [num] most recent songs whose \n"
        + "\t\tauthor's names begin with X. Specifying [num] is optional;\n"
        + "\t\tthe default is to list 20 songs.\n"
        + "X may be a range; e.g. 'read titles [a-f]' will list all songs "
        + "whose titles begin with the letters A through F. If you get an "
        + "error try narrowing the range.\nYou can also 'delete' songs "
        + "of your own creation.\n";
#endif
}

/*
 ****************************************************************************
 * Name:        alpha_author_list
 * Description: returns a list of all the songs written by a particular 
 *              author.
 * Arguments:   first - the first letter of the author's name.
 * Returns:     the list
 */

string
alpha_author_list(string first)
{
    int i, j, k, size;
    string *titles, *alltitles;
    string *first_line, *title_words;
    string title, newtitle, author, return_text, dummy;

    if (TP()->query_special_title())
    {
        write("DEBUG - alpha_author_list called.\n");
    }
    say (QCTNAME(TP()) + " studies the index.\n");
    alltitles = get_dir(MUNDANEDIR+"*.song");
    
    return_text = "";
    k = 0;
    
    for (i=0;i<sizeof(alltitles);i++)
    {   
        first_line = explode(read_file(MUNDANEDIR + alltitles[i],1,1)
                            + "**","**");
        title = first_line[0];
        author = first_line[1];

        if (wildmatch(first+"*", lower_case(author)) ||
            wildmatch(first+"*", author))
        {
            k++;
            
            newtitle = "";
            size = sizeof(title_words = explode(title+" "," "));
            
            for (j=0;j<size;j++)
                newtitle+=capitalize(title_words[j])+" ";
            
            return_text = return_text + (i+1);
            return_text += "-"+newtitle+"by "+author;
        }
    }
    return ("The index lists " + sprintf("%d ",k)
            + "titles whose author's "
            + "names begin with \""+first+"\":\n\n"
            + sprintf("%-*#s\n", 76, return_text));
}

/*
 ****************************************************************************
 * Name:        alpha_title_list
 * Description: returns a list of all the songs written by a particular 
 *              author.
 * Arguments:   first - the first letter of the author's name.
 * Returns:     the list
 */

string
alpha_title_list(string first)
{
    int i, j, k, size;
    string *titles, *alltitles;
    string *first_line, *title_words;
    string title, newtitle, author, return_text, dummy;

    say (QCTNAME(TP()) + " studies the index.\n");
    alltitles = get_dir(MUNDANEDIR+"*.song");
    
    return_text = "";
    k = 0;
    
    for (i=0;i<sizeof(alltitles);i++)
    {   
        first_line = explode(read_file(MUNDANEDIR + alltitles[i],1,1)
                            + "**","**");
        title = first_line[0];
        author = first_line[1];

        if (wildmatch(first+"*", lower_case(title)) ||
            wildmatch(first+"*", title))
        {
            k++;
            
            newtitle = "";
            size = sizeof(title_words = explode(title+" "," "));
            
            for (j=0;j<size;j++)
                newtitle+=capitalize(title_words[j])+" ";
            
            return_text = return_text + (i+1);
            return_text += "-"+newtitle+"by "+author;
        }
    }
    return ("The index lists " + sprintf("%d ",k)
            + "titles whose titles "
            + "begin with \""+first+"\":\n\n"
            + sprintf("%-*#s\n", 76, return_text));
}

int
filter_wildmatch(string str)
{
    return wildmatch(global_pattern, str) || wildmatch(global_pattern, lower_case(str));
}

/*
 * Function:    song_file_compare
 * Description: takes two songs and returns:
 *                      -1 if song1 is more recent than song2
 *                      0 if song1 is as old as song2
 *                      1 if song1 is older than song2
 */
int
compare_mundane_timestamps(string song1, string song2)
{
    if (file_time(MUNDANEDIR+song1) > file_time(MUNDANEDIR+song2))
        return -1;
    if (file_time(MUNDANEDIR+song1) < file_time(MUNDANEDIR+song2))
        return 1;
    return 0;
}

/*
 ****************************************************************************
 * Name:        recent_list
 * Description: returns a list of the most recent songs
 *
 * Arguments:   numsongs - the number of songs
 *              authorfirst - the beginning of the song
 * Returns:     the sorted list of songs who's authors match "authorfirst*"
 */
string
recent_list(int numsongs, string authorfirst)
{
    int i,j;
    string *songlist, *first_line, *title_words, *sorted;
    string return_text, author, title, newtitle;
    int size;

    global_pattern = authorfirst+"*";
    songlist = filter(get_dir(MUNDANEDIR+"*.song"), filter_wildmatch);
    sorted = sort_array(songlist, "compare_mundane_timestamps", TO());
    TP()->add_prop("_minstrel_sa_recent_list", sorted); 

    for (i=0;i<numsongs && i<sizeof(sorted);i++)
    {
        first_line = explode(read_file(MUNDANEDIR + sorted[i],1,1)
                            + "**","**");
        title = first_line[0];
        author = first_line[1];

        newtitle = "";
        size = sizeof(title_words = explode(title+" "," "));
        
        for (j=0;j<size;j++)
            newtitle+=capitalize(title_words[j])+" ";
        
        return_text = return_text + (i+1);
        return_text = return_text + "-"+newtitle+"by "+author;
    }
    return ("The index lists the following " + sprintf("%d ",i)
            + "recent titles whose author's "
            + "names begin with \""+authorfirst+"\". Songs are listed "
            + "from most to least recent:\n\n"
            + sprintf("%-*#s\n", 76, return_text));
}
#endif INDEX_OPEN

int
do_read(mixed str)
{
#ifdef INDEX_OPEN
    string *title_list;
    string first, song_file, text;
    int i, j, intvar, num;
    mixed songs;
#endif

    if (!str)
    {
        return 0;
    }

    if (str=="index"||str=="book")
    {
#ifdef INDEX_OPEN
        string list = mundane_list();
        if (query_verb() == "mread" || (strlen(list) > 2500))
        {
            this_player()->more(list);
        }
        else
        {
            write(list);
        }
        return 1;
#else
        write("The index is magically sealed shut and cannot be read.\n");
        return 1;
    }
    
#ifdef INDEX_OPEN
    if (sscanf(str, "authors %s", first) == 1)
    {
        TP()->remove_prop("_minstrel_sa_recent_list");
        if (query_verb() == "mread")
        {
            clone_object(MORE_OBJ)->more(alpha_author_list(first));
        }
        else
        {
            write(alpha_author_list(first));
        }
        return 1;
    }

    if (sscanf(str, "titles %s", first) == 1)
    {
        TP()->remove_prop("_minstrel_sa_recent_list");
        if (query_verb() == "mread")
        {
            clone_object(MORE_OBJ)->more(alpha_title_list(first));
        }
        else
        {
            write(alpha_title_list(first));
        }
        return 1;
    }

    if (sscanf(str, "recent %s", first) == 1)
    {
        int numsongs;
        
        if (sscanf(first, "%d %s", numsongs, first) != 2)
        {
            numsongs = 20;
        }
        if (query_verb() == "mread")
        {
            clone_object(MORE_OBJ)->more(recent_list(numsongs, first));
        }
        else
        {
            write(recent_list(numsongs, first));
        }
        return 1;
    }

    if (!MEMBER(TP()) && !this_player()->query_wiz_level())
    {
        NF(BS("Untrained in the ways of music, you cannot even begin to "
        + "decipher the songs.\n"));
        return 0;
    }
    
    if (TP()->query_skill(SG_READ_MUSIC)<5)
    {
        NF(BS("You have not advanced far enough in the skill "
          + "of reading music even to read the Mundane Songs. "
          + "Why not visit the Training Room?\n"));
        return 0;
    }

    setuid();
    seteuid(getuid());

    if (sscanf(str, "%d", num))
    {
        songs = SONG_INDEX->find_song(num, "mundane");
    }
    else
    {
        songs = SONG_INDEX->find_song(str, "mundane");
    }

    if (!pointerp(songs))
    {
        notify_fail("Which song would you like to read? Try 'read <xxx>' where xxx "
            + "is the number or title (in lowercase).\n");
        return 0;
    }        

    if (sizeof(songs) > 1)
    {
        write("More than one song matches.  Please be more specific.\n");
        return 1;
    }
    else
    {
        songs = songs[0];
    }

    if (!stringp(songs))
    {
        write("Unable to read song.\n");
        return 1;
    }

    text = read_file(songs, 2);
    if (text == 0)
    {
        write("Unable to read song.\n");
        return 1;
    }

    this_player()->more(text);
    return 1;

    title_list = TP()->query_prop("_minstrel_sa_recent_list");
    if (!title_list || !sizeof(title_list))
    {
        title_list = get_dir(MUNDANEDIR+"*.song");
    }
    if (song_file = parse_song("mundane", str, title_list, ({}), ({}), ({})))
    {
        clone_object(MORE_OBJ)->more(read_file(song_file, 2));
        return 1;
    }


    
    NF("Which song would you like to read? Try <read xxx> where xxx "
      + " is the number, title (in lowercase), or first word of "
      + "the title.\n");
    return 0;
#endif

}

/*
 ****************************************************************************
 * Name:         do_copy
 * Description:  
 *
 * Arguments:
 * Returns:
 */

int
do_copy(string str)
{
    mixed songs;
    string song_short;
    object song_book;
    int num;

    setuid();
    seteuid(getuid());

    if (sscanf(str, "%d", num))
    {
        songs = SONG_INDEX->find_song(num, "mundane");
    }
    else
    {
        songs = SONG_INDEX->find_song(str, "mundane");
    }

    if (!pointerp(songs))
    {
        notify_fail("Which song would you like to copy? Try 'copy <xxx>' where xxx "
            + "is the number, title (in lowercase), or first word of "
            + "the title.\n");
        return 0;
    }        

    if (sizeof(songs) > 1)
    {
        write("More than one song matches.  Please be more specific.\n");
        return 1;
    }
    else
    {
        songs = songs[0];
    }

    if (!stringp(songs))
    {
        write("Unable to copy song.\n");
        return 1;
    }

    if (this_player()->query_skill(SG_READ_MUSIC) < 5)
    {
        write("You have not advanced far enough in the skill of reading "
          + "music even to read the Mundane Songs. Why not visit the "
          + "Training Room?\n");
        return 1;
    }

    song_book = present("minstrel_song_book", this_player());    
    if (!song_book)
    {
        write("You don't have a song book to copy the songs into!\n");
        return 1;
    }

    song_short = songs[strlen(MUNDANE_SONGS_DIR)..];
    if (!song_book->add_mundane(song_short))
    {
        write("Your song book is full; no more Mundane Songs will fit!\n");
        return 1;
    }

    write("You successfully copy \"" + SONG_INDEX->query_title(songs) +
          "\" into your song book.\n");
    return 1;

#if 0
    string *title_list, *title_words, title, song_file, song_short;
    int    i, intvar;
    object song_book;
    
    title_list = TP()->query_prop("_minstrel_sa_recent_list");
    if (!title_list || !sizeof(title_list))
    {
        title_list = get_dir(MUNDANEDIR+"*.song");
    }
    song_book = present("minstrel_song_book", TP());
    if (TP()->query_skill(SG_READ_MUSIC)<5)
    {
        NF(BS("You have not advanced far enough in the skill of reading "
          + "music even to read the Mundane Songs. Why not visit the "
          + "Training Room?\n"));
        return 0;
    }
    
    if (!song_book)
    {
        NF("You don't have a song book to copy the songs into!\n");
        return 0;
    }
    if (song_file=parse_song("mundane",str,title_list,({}), ({}), ({})))
    {
        sscanf(song_file, MUNDANEDIR+"%s", song_short);
        
        if (song_book->add_mundane(song_short))
        {
            NF("Your song book is full; no more Mundane Songs will fit!\n");
            return 0;
        }
        write(BS("You successfully copy "+cap_title(song_file)
             + "into your song book.\n"));
        return 1;
    }
    
    NF(BS("Which song would you like to copy? Try 'copy <xxx>' where xxx "
      + "is the number, title (in lowercase), or first word of "
      + "the title.\n"));
    return 0;
#endif

    notify_fail("Temporarily disabled.\n");
    return 0;
}
#endif INDEX_OPEN

void
create_room()
{
    seteuid(getuid(TO()));
    
    set_short("The Foot of the Minstrels Tower");
    /*
    set_long("You stand at the foot of the Minstrel's Tower. Within the "
    + "Tower is located the famous Library of Songs. Here, at the base of "
    + "the Tower, are catalogued the Mundane Songs. These are the limericks "
    + "and cantos of the layman, written by Minstrels to amuse or sadden the "
    + "commoners, as the occasion requires. Compose here the frivolous songs "
    + "you wish to share with your fellow minstrels. As with all levels of "
    + "the Tower, a magical silence shall descend when a Minstrel begins "
    + "composing, that none may disturb the creative process.\nA handsome "
    + "index to the Mundane Songs sits here; you may read it for "
    + "instructions.\n");

    add_item(({"index", "book", "handsome index"}), "This cloth-bound tome "
            + "lists every Mundane Song ever written by a Minstrel. "
            + "Feel free to <read> or <copy> any song you please.\n");
    */
    set_long("You stand at the foot of the Minstrel's Tower. Within the "
    + "Tower is located the famous Library of Songs. Here, at the base of "
    + "the Tower, are catalogued the Mundane Songs. These are the limericks "
    + "and cantos of the layman, written by Minstrels to amuse or sadden the "
    + "commoners, as the occasion requires.\nA handsome "
    + "index to the Mundane Songs sits here, but it has been sealed shut " +
             " and is unavailable for reading.\n");

    add_item(({"index", "book", "handsome index"}), "This cloth-bound tome "
            + "lists every Mundane Song ever written by a Minstrel, but it " +
             "has been magically sealed shut.\n");

    add_prop(ROOM_I_INSIDE, 1);
    
    add_exit(GUILD+"tower_ballad", "up", "@@check_enter");
    add_exit(GUILD+"conservatoire", "northeast");
    add_exit(GUILD+"auditorium", "northwest");
}

#ifdef INDEX_OPEN
/*
 * Function:    done_editing
 * Description: This function is called by /std/edit after the player gets
 *              done editing the text of the file. We need to:
 *                      - Put a tab in front of any lines which do not
 *                        begin with a # mark or a tab.
 *                      - Make sure the ** is on the correct line.
 *                      - Prepend with the title**author line.
 *                      - Save to the appropriate file.
 */
void
done_editing(string text)
{
    string *lines, final;
    int i, blankline = 1;

    setuid(); seteuid(getuid());
    final = song_header;
    lines = explode(text+"\n", "\n");
    if (sizeof(lines) < 2)
    {
        TP()->CM("That is too short to be a valid song; canceling...\n");
        return;
    }
    /* step through the lines of the submitted text, filtering out      *
     * unwanted newlines and indenting all unindented lines.            */
    for (i=0;i<sizeof(lines);i++)
    {
        if (!strlen(lines[i]))
        {
            if (blankline)
            {
                write("<removing unnecessary blank line>\n");
            }
            else
            {
                blankline = 1;
                final += "\n";
            }
        }
        else if (lines[i][0] == '#')
        {
            final += lines[i] + "\n";
        }
        else 
        {
            blankline = 0;
            if (lines[i][0] != '\t')
                final += "\t" + lines[i] + "\n";
            else
                final += lines[i] + "\n";
        }       
    }
    /* prefix the text with the header and put ** at the end after      *
     * a single newline.                                                */
    if (blankline)
        final += "**";
    else
        final += "\n**";
    /* if the file exists, remove it */
    rm(filename);
    /* write the text to the appropriate file */
    if (write_file(filename, final))
        if (new_song)
            write("Thanks for adding to the Mundane Songs!\n");
        else
            write("Thanks for fixing up the Mundane Songs!\n");
    else
        write("Uh-oh. Problem writing the song; make a bug report.\n");
}

/*
 ****************************************************************************
 * Name:         do_compose
 * Description:  
 *
 * Arguments:
 * Returns:
 */

int
do_compose(string str)
{
    string default_text, title, *title_words, name;
    int i, filenumber;
    
    NF("The GuildMaster has requested that no Mundanes be composed "
       +"until the new Library has been finished.\n");
    return 0;   
 
    setuid(); seteuid(getuid(TO()));
    if (!MEMBER(TP()))
    {
        NF("Don't flatter yourself. Only the Minstrels may compose "
          + "songs here.\n");
        return 0;
    }
    if (!str)
    {
        NF("Usage: compose <title of song>. The author's name (yours) "
          + "will be appended.\n");
        return 0;
    }

    silence();
    
    /* Does the song already exist? */
    name = capitalize((string) this_player()->query_real_name());    
    if (filename = parse_song("mundane", str, get_dir(MUNDANEDIR+"*.song"),
                   ({}), ({}), ({})))
    {   /* set song_header to be the first line of the file */
        string author;
        song_header = explode(read_file(filename), "\n")[0];
        author = explode(song_header, "**")[1];
        song_header += "\n";
        if (author != name && !TP()->query_special_title())
        {
            write("Another Minstrel has composed that song; only the author "
                  + "or the Cycle may edit it now.\n");
            return 1;
        }
        new_song = 0;
    }
    else
    {
        /*
         * Figure out a good filename. Format will be name_xx.song where
         * xx is the number of songs that person has composed.
         */
        filenumber = sizeof(get_dir(MUNDANEDIR+name+"_*.song"))+1;
        filename = MUNDANEDIR+name+"_"+filenumber+".song";
        
        title_words = explode(str+" ", " ");
        title = "";
        for (i=0;i<sizeof(title_words);i++)
        {
            if (i) 
                title = title + " ";
            title = title + lower_case(title_words[i]);
        }
        song_header = title + "**" + name + "\n";
        new_song = 1;
    }
    write("Enter song text. End with '**', list with '~l', abort with '~q'.\n"
          + "The lines will be automatically indented; "
          + "separate stanzas with a single blank line. "
          + "Text which isn't to be sung can be commented out by "
          + "prefacing the line with a # character. And please give "
          + "credit to the original artist, if any!\n");
    default_text = read_file(filename, 2);
    if (strlen(default_text))
    {
        default_text = extract(default_text, 0, strlen(default_text)-3);
        clone_object(EDIT_OBJ)->edit("done_editing", default_text);
    }
    else
        clone_object(EDIT_OBJ)->edit("done_editing");

    unsilence();
    return 1;
}

/*
 * Function:    do_delete
 * Description: allow the players to delete their own songs from the Library;
 *              allow the Cycle to delete any Mundanes.
 */
int
do_delete(string str)
{
    string name, filename, prefix, title, author, *title_words, song_header;
    int i, filenumber, songnumber;

    setuid(); seteuid(getuid());
    /* Does the song already exist? */
    name = capitalize((string) this_player()->query_real_name());    
    if (filename = parse_song("mundane", str, get_dir(MUNDANEDIR+"*.song"),
                   ({}), ({}), ({})))
    {   /* set song_header to be the first line of the file */
        song_header = explode(read_file(filename), "\n")[0];
        title = explode(song_header, "**")[0];
        author = explode(song_header, "**")[1];
        song_header += "\n";
        if (author != name && !TP()->query_special_title())
        {
            write("Another Minstrel has composed that song; only the author "
                  + "or the Cycle may delete it now.\n");
            return 1;
        }
        title = cap_title(filename);
        /* How many songs has this player written? */
        filenumber = sizeof(get_dir(MUNDANEDIR+name+"*.song"));
        /* Which of those songs is this? */
        sscanf(filename, "%s_%d.song", prefix, songnumber);
        
        write("Deleting "+title+"from the Index of Songs...\n");
        rm(filename);
        /* Now figure out if we've messed up the numbering of songs */
        if (songnumber < filenumber)
        {
            string temp, next_filename, this_filename;
            for (i=songnumber; i < filenumber; i++)
            {
                next_filename = sprintf("%s_%d.song", prefix, i+1);
                this_filename = sprintf("%s_%d.song", prefix, i);
                temp = read_file(next_filename);
                rm(this_filename);
                write_file(this_filename, temp);
            }
            this_filename = sprintf("%s_%d.song", prefix, filenumber);
            rm (this_filename);
        }
        BOOK_RESET();
        return 1;
    }
    else
    {
        NF("Delete which song from the Index? Try specifying the title "
           + "exactly...\n");
        return 0;
    }
}
#endif INDEX_OPEN
