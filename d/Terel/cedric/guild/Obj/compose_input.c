#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

string header,title,dest_dir,filename,text = "";
int line = 1;
int blankline = 0;
object caller;

/*
 * Function:	new_song
 * Description:	starts a new song. Picks a unique filename, forces the
 *		title to lowercase, and calls get_msg().
 * Arguments:	title_text - the title string.
 *		put_dir - where the final song file should go.
 *		check_dir [optional] - if a string, specifies a directory
 *		to check while picking a unique name. If an integer, acts
 *		as a flag -- if 1, song file will end with ".epic" rather
 *		than ".song"  (an ugly hack, I know).
 */
void
new_song(string title_text, string put_dir,mixed check_dir)
{
    string name, *title_words;
    int i, filenumber;

    setuid(); seteuid(getuid(TO()));
    dest_dir = put_dir;
    name = capitalize((string) this_player()->query_real_name());
    if (!check_dir) check_dir = dest_dir;
    if (check_dir == 1)
    {
	filename = name+".epic";
	title = "the epic of "+this_player()->query_real_name();
    }
    else
    {
	caller = previous_object();
	name = capitalize((string) this_player()->query_real_name());    
	/*
	 * Figure out a good filename. Format will be name_xx.song where
	 * xx is the number of songs that person has composed.
	 */
	filenumber = sizeof(get_dir(check_dir+name+"_*.song"))+1;
	if (check_dir != dest_dir)
	{
	    filenumber += sizeof(get_dir(dest_dir+name+"_*.song"));
	}
	filename = name+"_"+filenumber+".song";
	
	title_words = explode(title_text+" ", " ");
	title = "";
	for (i=0;i<sizeof(title_words);i++)
	{
	    if (i) 
		title = title + " ";
	    title = title + lower_case(title_words[i]);
	}
    }
    header = title + "**" + name;
    write("Enter song text. End with '**', list with '~l', abort with '~q'.\n"
    + "The lines will be automatically indented; "
    + "separate stanzas with a single blank line. Text which isn't to "
    + "be sung can be commented out by prefacing the line with a # character.\n");
    write(line + ">>");
    input_to("get_msg");
}

void
get_msg(string str)
{
    /* We do not want hand-written VBFC.
    while(wildmatch("*@@*", str))
    {
        str = implode(explode(str, "@@"), "#");
    }

    if (str == "~q")
    {
        say(QCTNAME(this_player()) + " aborts writing a song.\n");
        write("Song aborted.\n");
	environment(TP())->unsilence(TP());
	remove_object();
        return;
    }
    
    if (str == "~l")
    {
        write(text + "\n" + line + ">>");
        input_to("get_msg");
        return;
    }
    
    if (str == "**")
    {
        if (line == 1)
        {
            write("No text entered. Song discarded.\n");
            say(QCTNAME(this_player()) + " quits writing.\n");
            environment(TP())->unsilence(TP());
	    remove_object();
            return;
        }
        say(QCTNAME(this_player()) + " has completed a song : " +
            title + "\n");
        write("Ok.\n");
	text = text + "\n**";
	rm(dest_dir+filename);
        write_file(dest_dir+filename, header+"\n");
	write_file(dest_dir+filename, text);
        environment(TP())->unsilence(TP());
	remove_object();
        return;
    }
    if (str[0]=='#')
	text = text + str + "\n";
    else 
	if (!strlen(str))
	{
	    if (blankline)
	    {
		line--;
		write("<ignoring uneccessary blank line>\n");
	    }
	    else
	    {
		blankline = 1;
	    }
	}
	else
	{
	    if (blankline)
	    {
		text = text + "\n";
		blankline = 0;
	    }
	    text = text + "\t" + str + "\n";
	}
    line++;
    write(line + ">>");
    input_to("get_msg");
}
