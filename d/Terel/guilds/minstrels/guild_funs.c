/*
 * File:	guild_funs.c
 * Description: A few useful functions called by various files in the
 *		guild. See the macros in guild_defs.h.
 * Functions:	on_line 	- what minstrels are on-line
 *		parse_song	- what song does command refer to
 *		cap_title	- capitalize every word in a song title
 *		reset_books	- reset every Minstrel's song book
 */

#pragma save_binary

#include "guild_defs.h"

/*
 * Prototypes
 */
object *on_line();
int book_reset();
mixed parse_song(string type, string which, string *m_arr, string *b_arr,
		 string *e_arr,string *p_arr);
string cap_title(string songfile);
int query_banished(string name);    

/*
 * Function: 	book_reset
 * Description:	reset every Minstrel's song book.
 */
int
book_reset()
{
   object book,*minstrels;
   int i;
   
   minstrels = on_line();

   TP()->CM("Resetting all minstrel songbooks...\n");

   for(i=0;i<sizeof(minstrels);i++)
   {
      book = present("minstrel_song_book",minstrels[i]);
      book->reset_object();
   }

   TP()->CM("Done.\n");
   return 1;
}

/*
 ****************************************************************************
 * Function:    parse_song
 * Description: Takes a string of the pattern "<type> <which>", where <type> is
 *              the type (mundane, ballad, or power) of the song desired and
 *              <which> is the number, title, or first word of the title of
 *              that song, and returns the filename of the song.
 * Arguments:   
 *              type  - the type string. If empty, parse_song will attempt to
 *                      draw a type from the which string.
 *              which - the which string to be processed.
 *              m_arr - the array containing Mundane Songs to be looked up.
 *              b_arr - the array containing Ballads to be looked up.
 *              p_arr - the array containing Songs of Power to be looked up.
 * Returns:     0 if unsuccessful, else the path+filename of the song.
 * 
 * Note:        Sets own notify_fail messages.
 */

mixed
parse_song(string type, string which, string *m_arr, string *b_arr, string *e_arr,string *p_arr)
{
    int i;
    string  *the_arr, the_string, the_dir, last_part, 
	    title, first_word, second_word;

    setuid();
    seteuid(getuid());
    if (type=="")
	if(!sscanf(which,"%s %s",type,which))
	    return 0;
    if (type=="ballad"||type=="mundane"||type=="power"||type=="epic")
    {
	switch (type)
	{
	    case "epic":
		the_dir = BALLADDIR; the_arr = e_arr; the_string = "Epic";
		break;
	    case "ballad":
		the_dir = BALLADDIR; the_arr = b_arr; the_string = "Ballad";
		break;
	    case "mundane":
		the_dir = MUNDANEDIR; the_arr = m_arr; the_string = "Mundane Song";
		break;
	    case "power":
		the_dir = POWERDIR; the_arr = p_arr; the_string = "Song of Power";
		break;
	}
	if (!which)
	{
	    NF("Which "+the_string+" did you have in mind?");
	    return 0;
	}
	if (sscanf(which, "%d", i))
	{
	    if (i>sizeof(the_arr))
	    {
		NF("No "+the_string+" with that number!\n");
		return 0;
	    }
	    return the_dir+the_arr[i-1];
	}
	for (i=0;i<sizeof(the_arr);i++)
	{
	    if (strlen(title = read_file(the_dir+the_arr[i],1,1)))
	    {
		if (the_arr == p_arr)
		    title = explode(title,"**")[1];
		else
		    title = explode(title,"**")[0];
		if (the_arr == e_arr)
		{
		    first_word = explode(title+" ", " ")[2];
		    second_word = explode(title+" ", " ")[3];
		    last_part = first_word+" "+second_word;
		}
		else
		{
		    first_word = explode(title+" ", " ")[0];
		    if (member_array(first_word, ({"a", "an", "the","of"}))!=-1)
			second_word = explode(title+" ", " ")[1];
		    else
			second_word = "";
		    last_part = "";
		}
		if (title==which || which==first_word || 
		    which==second_word || which == last_part)
		{
		    return the_dir+the_arr[i];
		}
	    }
	}
    }
    NF("Refer to songs as: <type> <song>\n"
    + "where <type> is mundane, ballad, epic, or power,  and song is the number, title\n"
    + "(in lowercase), or first word of the title of the song..\n");
    return 0;
}

/*
 ****************************************************************************
 * Function:     cap_title
 * Description:  Takes a song file and returns the capitalized title of the 
 *               song, plus a trailing space.
 */

string
cap_title(string song_file)
{
    string trash, title, newtitle, *title_words;
    int size,j;
    
    if (sscanf(song_file, POWERDIR+"%s", trash))
	title = explode(read_file(song_file,1,1),"**")[1];
    else
	title = explode(read_file(song_file,1,1),"**")[0];
    newtitle = "";
    size = sizeof(title_words = explode(title+" "," "));
    for (j=0;j<size;j++)
	newtitle+=capitalize(title_words[j])+" ";
    return newtitle;
}

/*
 ****************************************************************************
 * Function:     on_line
 * Description:  Returns an array of every minstrel currently on-line. Used
 *               by a number of Minstrel abilities that reach the ears of 
 *               all guild members.
 * Returns:      Array of objects, each of which is an on-line minstrel.
 */

object
*on_line()
{
    object *folks, *guilds;
    int i;
    
    guilds = ({});
    folks = users();
    for (i=0;i<sizeof(folks);i++)
	if (MEMBER(folks[i]))
	    guilds += ({folks[i]});
    return guilds;
}

/*
 ****************************************************************************
 * Function:    query_member_banished
 * Description: Has the named player been banished by the Cycle?
 * Returns:	1 if the player has been banished, 0 otherwise
 */
int
query_banished(string name)
{
    if (sizeof(get_dir(BANISHDIR+name+"_banished")))
    {
	return 1;
    }
    else
    {
	return 0;
    }
}
/****************************** guild_funs.c *******************************/

