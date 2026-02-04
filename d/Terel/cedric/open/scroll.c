#pragma save_binary

inherit "/std/object.c";
#include "/d/Terel/cedric/guild/guild_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define EDIT_OBJ	"/std/edit"
#define MORE_OBJ "/std/board/board_more"

string *submit_songs, new_accept_file, new_banish_file;
void reset_object();

void
create_object()
{
    int i;
    set_name("scroll");
    add_name("minstrel_scroll");
    set_short("minstrel scroll");
    add_adj("minstrel");
    set_long("This is a scroll that contains the submitted ballads for the "
	     + "Minstrel Guild. Use 'peruse scroll' or 'peruse #<number>' "
	     + "to read the scroll. Use 'peruse reviews #<number>' to "
	     + "read the reviews of a song written by your fellow Cycle "
	     + "members. Use 'accept #<number>' to signify your approval "
	     + "of a song. Also, use 'banish <playername>' to recommend "
	     + "banishing a player from the guild, and use 'reviews' to "
	     + "review the recommendations already made. Finally, 'banished' "
	     + "will list those players already banished from the guild, "
	     + "and 'members' will list every member of our August Order.\n");
    add_prop(OBJ_M_NO_DROP,1);
    enable_reset();
    
    /* Init submit_songs and accepted */
    seteuid(getuid());
    submit_songs = get_dir(SUBMITDIR+"*.song");
}

void
reset_object()
{
    int i;
    
    seteuid(getuid());
    submit_songs = get_dir(SUBMITDIR+"*.song");
}

string
query_auto_load()
{
    return MASTER_OB(TO());
}

void
init()
{
    ::init();
    add_action("do_read","peruse");
    add_action("do_accept", "accept");
    add_action("do_banish", "banish");
    add_action("do_banished", "banished");
    add_action("do_demote","demote");
    add_action("do_promote","promote");
    add_action("do_reviews", "reviews");
    add_action("do_members", "members");
    add_action("do_cleanlog", "cleanlog");
}

void cleanlog(string *lines, object player)
{
    string logfile, *newlines;
    int i, numlines = sizeof(lines);

    seteuid(getuid(TO())); 
    player->CM("Checking the following Minstrels:\n");
    for (i=numlines - 1;i > numlines - 21 && i > 0;i--)
    {
	string name; 
	mixed minstrel;

	name = explode(lines[i]+":", ":")[1];
	if (name == "")
	{
	    lines -= ({ lines[i] });	 
	    continue;
	}
	player->CM(name);
	minstrel = "/secure/master"->finger_player(name);

	if (objectp(minstrel))
	{
	    /* Print out the names of purged minstrels */
	    player->CM(" PURGED. ");
	}
	else 
	{
	    newlines += ({ lines[i] });
	    player->CM(" okay. ");
	    write_file(LOGFILE, lines[i] + "\n");
	}
	
	lines -= ({ lines[i] }); 
    }
    player->CM("\n");
    /* now call cleanlog() recursively, using set_alarm */
    if (sizeof(lines))
    {
	set_alarm(2.0, 0.0, &cleanlog(lines, player));
    }
}

/*
 * Function:	do_cleanlog
 * Description:	goes through the Minstrel log and removes all players
 *		who /secure/master no longer thinks exist.
 */
int do_cleanlog(string str)
{
    string logfile, *loglines;

    seteuid(getuid(TO()));
    logfile = read_file(LOGFILE);
    loglines = explode(logfile, "\n");
    rm(LOGFILE);
    TP()->CM("Initiating purge...\n");
    set_alarm(2.0, 0.0, &cleanlog(loglines, TP()));
    return 1;
}

int do_members(string str)
{

}
    
string
submit_list()
{
   int i,j;
   int padding;
   string author, title, *title_words, text, line, numtext;
   string *reviews;
   
   seteuid(getuid(TO()));
   text=sprintf("%s\t\t\t%s\t\t%s\t\t%s\n",
		"Number:","Title","Author", "Accepted by");
   text+="------------------------------------------------------------"
       +"-------------\n";
   for(i=0;i<sizeof(submit_songs);i++)
   {
      title=explode(read_file(SUBMITDIR+submit_songs[i],1,1), "**")[0];
      title_words = explode(title+" "," ");
      author=explode(explode(read_file(SUBMITDIR+submit_songs[i],1,1),
			     "**")[1],"\n")[0];
      line = "";
      for(j=0;j<sizeof(title_words);j++)
	  line = line + capitalize(title_words[j])+" ";
      numtext = sprintf("%d",i+1);
      line = sprintf("%=2s - %=30s %=12s:",numtext,line, author);
      reviews = get_dir(SUBMITDIR+submit_songs[i]+".*");
      for (j=0;j<sizeof(reviews);j++)
      {
	  int authorloc = sizeof(explode(reviews[j],".")) - 1;

	  line = line + " " + explode(reviews[j],".")[authorloc];
      }
      text = text + line + "\n";
   }
   return text;
}

int
do_read(string str)
{
    int sn;
    object ob1;
    string which,is_song;
  
    if(!strlen(str))
	return 0;
    if(str == "scroll")
    {
	write("Submitted Ballads:\n"+
	submit_list()+"\n");
	return 1;
    }
    if (sscanf(str, "#%d", sn) == 1)
    {
	if(sn < (sizeof(submit_songs) + 1))
	{
	    is_song = SUBMITDIR+submit_songs[sn-1];
	    if (TP()->query_wiz_level())
		write("Song file name = "+is_song+"\n");
	    seteuid(getuid(TO()));
	    clone_object(MORE_OBJ)->more(read_file(is_song, 2));
	    return 1;
	}
	return_fail("There aren't that many submissions.\n");
    }
    if (sscanf(str, "reviews #%d", sn) == 1)
    {
	if(sn < (sizeof(submit_songs) + 1))
	{
	    int j;
	    string *reviews = get_dir(SUBMITDIR+submit_songs[sn-1]+".*");
	    string text="";

	    if (sizeof(reviews) < 1)
	    {
		return_fail("There aren't any reviews of that song.\n");
	    }
	    for (j=0;j<sizeof(reviews);j++)
	    {
		int authorloc = sizeof(explode(reviews[j],".")) - 1;
		string reviewer = explode(reviews[j],".")[authorloc];

		text = text + "Reviewed by "+reviewer+":\n"
		    + read_file(SUBMITDIR+reviews[j]);
	    }
	    seteuid(getuid(TO()));
	    clone_object(MORE_OBJ)->more(text);
	    return 1;
	}
	return_fail("There aren't that many submissions.\n");
    }
    NF("Use 'peruse scroll' or 'peruse #<number>' "
       + "to read the scroll. Use 'peruse reviews #<number>' to "
       + "read the reviews of a song written by your fellow Cycle "
       + "members. Use 'accept #<number>' to signify your approval "
       + "of a song.\n");
    return 0;
}

int
do_banished(string str)
{
    string *banished_files = get_dir(BANISHDIR+"*_banished");
    string *reviews = get_dir(BANISHDIR+"*.*");
    string text, banished_list, schmuck, tmp_text = "";
    int i, l;

    if (sizeof(banished_files) < 1)
	text = "Currently no players have been completely banished from "
	    + "the guild.\n";
    else
	text = "The following players have been completely banished from "
	    + "the guild:\n";

    for (i=0;i<sizeof(banished_files);i++)
    {
	schmuck = explode(banished_files[i], "_")[0];
	tmp_text = tmp_text + schmuck + " ";
    }

    banished_list = sprintf("%-*#s\n", 76, tmp_text);
    TP()->CM(text + banished_list);
    return 1;
}

int
do_reviews(string str)
{
    string *reviews = get_dir(BANISHDIR+"*.*.review");
    string text, tmp_text = "";
    int i;

    seteuid(getuid(TO()));
    if (sizeof(reviews) < 1)
	text = "Currently no players are being considered for banishment "
	    + "from the guild.\n";
    else
	text = "The following players are being considered for banishment "
	    + "from the guild:\n";


    for (i=0;i<sizeof(reviews);i++)
    {
	string *tmp_array = explode(reviews[i], ".");
	string schmuck = tmp_array[0];
	string accuser = tmp_array[1];

	text = (text + accuser + " has recommended that "
		+ schmuck + " be banished:\n----------------\n"
		+ read_file(BANISHDIR+reviews[i]) + "\n----------------\n");
    }

    TP()->CM(text);
    return 1;
}

int
do_banish(string str)
{
    string *files;
    int i;
    string schmuck, comments = "";
    object loser;

    if (!str || strlen(str) == 0)
    {
	NF("Usage: banish <playername>.\n");
	return 0;
    }
    seteuid(getuid(TO()));
    schmuck = "/secure/master"->finger_player(lower_case(str));
    if (!schmuck)
    {
	NF("Are you sure "+str+" is the name of a player?\n");
	return 0;
    }
    if (sizeof(get_dir(BANISHDIR+str+"."+TP()->query_name()+".review")))
    {
	write("You have already expressed your disapprobation of "
	      +capitalize(str) + ". The other members of the Cycle "
	      + "must now pass judgement on the matter.\n");
	return 1;
    }
    if (sizeof(get_dir(BANISHDIR+str+"_banished")))
    {
	write(capitalize(str)+" has already been banished from the "
	      + "August Order of Minstrels.\n");
	return 1;
    }
    files = get_dir(BANISHDIR+str+".*.review");
    if (sizeof(files) == 2)
    {
	write("Three members of the Cycle have cast a vote to banish "
	      +str+" from the society of the August Order of Minstrels. "
	      + "So shall it be!\n");
	(GUILD+"tower_roof")->minstrel_banished(str);
	loser = find_player(str);
	if (loser) loser->banish_me();
	for (i=0;i<sizeof(files);i++)
	{
	    if (TP()->query_wiz_level())
		write("Removing file "+files[i]+"\n");
	    rm(BANISHDIR+files[i]);
	}
	write_file(BANISHDIR+str+"_banished",
		   "Banished forever from the Minstrels.\n");
	return 1;
    }
    write("Please explain your reasons for wishing "+capitalize(str) + " "
	  + "banished completely "
	  + "from the guild. Be aware that the rest of the Cycle will "
	  + "probably require a detailed explanation before taking such "
	  + "a drastic step.\n");
    new_banish_file = BANISHDIR+str+"."+TP()->query_name()+".review";
    clone_object(EDIT_OBJ)->edit("done_banishing", comments);
    return 1;
}

int
do_promote(string str)
{
    NF("Not implemented yet, be patient...\n");
    return 0;
}
    
void
done_banishing(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_banish_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_banish_file, comments);
}
    
int
do_accept(string str)
{
    string bytes,from_song,to_song;
    string *accept_files;
    int sn, i;

    NF("Syntax: accept #<songnumber>\n");
    if(!strlen(str))
	return 0;
    if (sscanf(str, "#%d", sn) == 1)
    {
        if(sn <= sizeof(submit_songs) && sn > 0)
        {
            from_song = SUBMITDIR+submit_songs[sn-1];
	    new_accept_file = from_song+"."+TP()->query_name();
	    if (sizeof(get_dir(new_accept_file)))
	    {
		write(BS("You have already registered your praise of "
			      + "that song; the other members of the Cycle "
			      + "must pass judgement on it now.\n"));
			return 1;
	    }
	    else if (sizeof(accept_files = get_dir(from_song+".*")) > 1)
	    {
		write("You give the song the highest praise possible, "
		      + "recommending it for submission to the "
		      + "Ballads.\n");
		write(BS("Three members of the Cycle have deemed this "
			 + "song worthy to be a Ballad; so shall it "
			 + "be!\n"));
		/* erase all the accept_files and move the song to Ballads */
		for (i=0;i<sizeof(accept_files);i++)
		{
		    if (TP()->query_wiz_level())
			TP()->CM("Erasing file "+accept_files[i]+"\n");
		    rm(SUBMITDIR+accept_files[i]);
		}
		if (TP()->query_wiz_level())
		    write("Deleting file: "+from_song+"\n");
		seteuid(getuid(TO()));
		bytes = read_file(from_song);
		to_song = BALLADDIR+submit_songs[sn-1];
		write_file(to_song,bytes);
		rm(from_song);
		return 1;
	    }
	    else /* sizeof accept_files <= 1 */
	    {
		string comments;
		
		write("You give the song the highest praise possible, "
		      + "recommending it for submission to the "
		      + "Ballads. Please enter any comments you might have "
		      + "about why the song deserves such lofty status:\n");
		clone_object(EDIT_OBJ)->edit("done_editing", comments);
		return 1;
	    }
	}
        NF("There aren't that many submissions.\n");
    }
    return 0;
}

void
done_editing(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_accept_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_accept_file, comments);
}


int
do_demote(string str)
{
    string *files;
    int i;
    string schmuck, comments = "";
    object loser;
    
    seteuid(getuid(TO()));
    schmuck = "/secure/master"->finger_player(lower_case(str));
    if (!schmuck)
    {
	NF("Are you sure "+str+" is the name of a player?\n");
	return 0;
    }
    if (sizeof(get_dir(DEMOTEDIR+str+"."+TP()->query_name())))
    {
	write("You have already voted to demote " +capitalize(str) 
	      + " from the Cycle. The other members of the Cycle "
	      + "must now pass judgement on the matter.\n");
	return 1;
    }
    if (sizeof(get_dir(DEMOTEDIR+str+"_demoted")))
    {
	write(capitalize(str)+" has already been banished from the "
	      + "August Order of Minstrels.\n");
	return 1;
    }
    files = get_dir(BANISHDIR+str+".*");
    if (sizeof(files) == 2)
    {
	write("Three members of the Cycle have cast a vote to banish "
	      +str+" from the society of the August Order of Minstrels. "
	      + "So shall it be!\n");
	(GUILD+"tower_roof")->minstrel_banished(str);
	loser = find_player(str);
	if (loser) loser->banish_me();
	for (i=0;i<sizeof(files);i++)
	{
	    if (TP()->query_wiz_level())
		write("Removing file "+files[i]+"\n");
	    rm(BANISHDIR+files[i]);
	}
	write_file(BANISHDIR+str+"_banished",
		   "Banished forever from the Minstrels.\n");
	return 1;
    }
    write("Please explain your reasons for wishing "+capitalize(str) + " "
	  + "banished completely "
	  + "from the guild. Be aware that the rest of the Cycle will "
	  + "probably require a detailed explanation before taking such "
	  + "a drastic step.\n");
    new_banish_file = BANISHDIR+str+"."+TP()->query_name();
    clone_object(EDIT_OBJ)->edit("done_banishing", comments);
    return 1;
}
    
void
done_demoting(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_banish_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_banish_file, comments);
}
