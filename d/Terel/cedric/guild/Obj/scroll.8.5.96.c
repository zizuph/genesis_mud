#pragma save_binary

inherit "/std/object.c";
#include <std.h>
#include "/d/Terel/cedric/guild/guild_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define EDIT_OBJ	"/std/edit"
#define MORE_OBJ "/std/board/board_more"

string *submit_songs; 
string new_award_file; 
string new_accept_file; 
string new_reject_file;
string new_banish_file;
string new_promote_file;
string new_demote_file;

void reset_object();

void init()
{
    ::init();
    add_action("do_award", "award");
    add_action("do_read", "peruse");
    add_action("do_reject", "reject");
    add_action("do_accept", "accept");
    add_action("do_banish", "banish");
    add_action("do_banished", "banished");
    add_action("do_demote","demote");
    add_action("do_promote","promote");
    add_action("do_demoted", "demotions");
    add_action("do_promoted", "promotions");
    add_action("do_reviews", "reviews");
    add_action("do_list", "list");
    add_action("do_cleanlog", "cleanlog");
}

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
	     + "of a song, and use 'reject #<number>' to mark a song "
	     + "unworthy. Also, use 'banish <playername>' to recommend "
	     + "banishing a player from the guild, 'award' <playername> "
	     + "to nominate a player for an award, and 'reviews' to "
	     + "review the recommendations already made. To demote a "
	     + "Minstrel from the Cycle use the command 'demote'; similarly, "
	     + "'promote' will promote a Minstrel to fill a vacancy in the "
	     + "cycle. The commands 'demotions' and 'promotions' will list "
	     + "the demotions and promotions already recommended. Finally, "
	     + "'banished' will list those players already banished from the "
	     + "guild, and 'members' will list every member of our August "
	     + "Order.\n");
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


void cleanlog(string *lines, string *names, object player)
{
    string logfile, *newlines = lines;
    int i, numlines = sizeof(lines);

    seteuid(getuid(TO())); 
    player->CM("Checking the following Minstrels:\n");
    for (i=numlines - 1;i > numlines - 21 && i > 0;i--)
    {
	string name; 

	name = explode(lines[i]+":", ":")[1];
	if (name == "")
	{
	    continue;
	}
	player->CM(name);

	if (!SECURITY->exist_player(lower_case(name)))
	{
	    /* player no longer exists */
	    player->CM(" PURGED. ");
	}
	else if (member_array(name,names) != -1)
	{
	    /* player occurs more than once */
	    player->CM(" REDUNDANT. ");
	}
	else 
	{
	    string historic = GUILD+"/Historic/"+name+".epic";
	    string current = BALLADDIR+"/"+name+".epic";
	    
	    newlines = exclude_array(newlines, i,i);
	    player->CM(" okay. ");
	    if (file_size(historic) > -1)
	    {
		string epic = read_file(historic);
		write_file(current, epic);
	    }
	    write_file(LOGFILE, lines[i] + "\n");
	    names += ({ name });
	}
	
	lines = exclude_array(lines, i, i);
    }
    player->CM("\n");
    /* now call cleanlog() recursively, using set_alarm */
    if (sizeof(lines))
    {
	set_alarm(2.0, 0.0, &cleanlog(lines, names, player));
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
    set_alarm(2.0, 0.0, &cleanlog(loglines, ({ }), TP()));
    return 1;
}

int do_list(string str)
{
    string *lines, logfile, names; 
    int i = 0;

    str = lower_case(str);
    if (str != "minstrels" && str != "recent minstrels")
    {
        NF("List what? Minstrels? Recent Minstrels?\n");
	return 0;
    }
    logfile = read_file(LOGFILE);
    lines = explode(logfile, "\n");
    if (str == "recent minstrels") 
    {
        i = sizeof(lines) - 20;
    }
    for (;i<sizeof(lines);i++)
    {
        names = names + explode(lines[i]+":", ":")[1] + "\n";
    }
    TP()->CM("The scroll lists the following members of the "
           + "August Order of Minstrels:\n"
           + sprintf("%-*#s\n", 76, names));
    return 1;
}
    
string submit_list()
{
   int i,j;
   int padding;
   string author, title, *title_words, text, line, numtext;
   string *reviews;
   
   seteuid(getuid(TO()));
   text=sprintf("%s\t\t\t%s\t\t%s\t\t%s\n",
		"Number:","Title","Author", "Reviewed by");
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
	  line = line + " " + explode(reviews[j],".")[2];
      }
      text = text + line + "\n";
   }
   return text;
}

int do_read(string str)
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
	write("There aren't that many submissions.\n");
	return 0;
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
		write("There aren't any reviews of that song.\n");
		return 0;
	    }
	    for (j=0;j<sizeof(reviews);j++)
	    {
		int authorloc = sizeof(explode(reviews[j],".")) - 1;
		string reviewer = explode(reviews[j],".")[2];

		text = text + "Reviewed by "+reviewer+":\n"
		    + read_file(SUBMITDIR+reviews[j]);
	    }
	    seteuid(getuid(TO()));
	    clone_object(MORE_OBJ)->more(text);
	    return 1;
	}
	write("There aren't that many submissions.\n");
	return 0;
    }
    NF("Use 'peruse scroll' or 'peruse #<number>' "
       + "to read the scroll. Use 'peruse reviews #<number>' to "
       + "read the reviews of a song written by your fellow Cycle "
       + "members. Use 'accept #<number>' to signify your approval "
       + "of a song, and 'reject #<number>' to mark those songs "
       + "you deem unworthy.\n");
    return 0;
}

int do_banished(string str)
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

int do_reviews(string str)
{
    string *reviews = get_dir(BANISHDIR+"*.*.review");
    string *already;
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

    reviews = get_dir(AWARDDIR+"??*.*");

    if (sizeof(reviews))
    {
	text = text + "Currently the following players have been nominated "
	    + "for an award:\n";
    }
    else
    {
	text = text + "Currently no players have been nominated for an "
	    + "award.\n";
    }

    for (i=0;i<sizeof(reviews);i++)
    {
	string *tmp_array = explode(reviews[i], ".");
	string schmuck, accuser;
	
	write(reviews[i]);
	schmuck = tmp_array[0];
	accuser = tmp_array[1];
	if (schmuck == "Awarded") { continue; }
	text = (text + accuser + " has nominated "
		+ schmuck + " for an award :\n----------------\n"
		+ read_file(AWARDDIR+reviews[i]) + "\n----------------\n");
    }

    clone_object(MORE_OBJ)->more(text);
    return 1;
}

int do_banish(string str)
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

void done_banishing(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_banish_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_banish_file, comments);
}
    
int do_reject(string str)
{
    string from_song, bytes, to_song;
    string *reject_files;
    int sn, i;

    NF("Syntax: reject #<songnumber>\n");
    if(!strlen(str)) { return 0; }
    if (sscanf(str, "#%d", sn) == 1)
    {
        if(sn <= sizeof(submit_songs) && sn > 0)
        {
            from_song = SUBMITDIR+submit_songs[sn-1];
	    new_reject_file = from_song+"."+TP()->query_name()+".reject";
	    if (sizeof(get_dir(new_reject_file)))
	    {
		write(BS("You have already registered your disapproval of "
			      + "that song; the other members of the Cycle "
			      + "must pass judgement on it now.\n"));
			return 1;
	    }
	    reject_files = get_dir(from_song+".*.reject");
	    if (sizeof(reject_files) >= 1)
	    {
		write("You mark the song as unacceptable.\n");
		write(BS("Two members of the Cycle have deemed this "
			 + "song unworthy of the Ballads; so shall it "
			 + "be!\n"));
		/* erase all the reject_files and move the song to Ballads */
		for (i=0;i<sizeof(reject_files);i++)
		{
		    if (TP()->query_wiz_level())
			TP()->CM("Erasing file "+reject_files[i]+"\n");
		    rm(SUBMITDIR+reject_files[i]);
		}
		if (TP()->query_wiz_level())
		    write("Deleting file: "+from_song+"\n");
		seteuid(getuid(TO()));
		bytes = read_file(from_song);
		to_song = REJECTDIR+submit_songs[sn-1];
		write_file(to_song,bytes);
		rm(from_song);
		return 1;
	    }
	    else /* sizeof reject_files < 1 */
	    {
		string comments;
		
		write("You mark the song as unworthy of the Ballads. "
		      + "Please enter any comments you might have "
		      + "about why the song does not deserve such status.\n");
		clone_object(EDIT_OBJ)->edit("done_rejecting", comments);
		return 1;
	    }
	}
        NF("There aren't that many submissions.\n");
    }
    return 0;
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
		clone_object(EDIT_OBJ)->edit("done_accepting", comments);
		return 1;
	    }
	}
        NF("There aren't that many submissions.\n");
    }
    return 0;
}

void
done_accepting(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_accept_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_accept_file, comments);
}

void 
done_rejecting(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_reject_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_reject_file, comments);
}

int
do_demote(string str)
{
    string *files;
    int i, which;
    string *members, committee, comments = "";
    object loser, scroll;
    
    seteuid(getuid(TO()));
    if (strlen(TP()->query_special_title()))
    {
	write("Hey! You don't seem to be a member of the Cycle!\n");
	remove_object();
	return 1;
    }
    committee = read_file(COMMITTEE_FILE);
    members = explode(committee, "**");
    which = member_array(str, members);   
    if (which == -1)
    {
        write("Are you sure "+capitalize(str)+" is a member of "
	      + "the Cycle at all?\n");
	return 1;
    }
    if (sizeof(get_dir(DEMOTEDIR+str+"."+TP()->query_name())))
    {
	write("You have already voted to demote " +capitalize(str) 
	      + " from the Cycle. The other members of the Cycle "
	      + "must now pass judgement on the matter.\n");
	return 1;
    }
    files = get_dir(DEMOTEDIR+str+".*");
    if (sizeof(files) == 2)
    {
	write("Three members of the Cycle have cast a vote to demote "
	      +str+" from the Cycle. So shall it be!\n");
        loser = find_player(str);
        if (loser)
        {
            loser->CM("You have been demoted from the Cycle. Thanks "
	              + "for your service to the guild and good luck "
	              + "in your future endeavors.\n");
	    present("minstrel_scroll", loser)->remove_object();
        }
        members[which] = GUILDMASTERJR;
        committee = implode(members, "**");
        rm(COMMITTEE_FILE);
        write_file(COMMITTEE_FILE, committee);
	
	for (i=0;i<sizeof(files);i++)
	{
	    if (TP()->query_wiz_level())
		write("Removing file "+files[i]+"\n");
	    rm(DEMOTEDIR+files[i]);
	}
	return 1;
    }
    write("Please explain your reasons for wishing to demote "
          + capitalize(str) + " from the Cycle. Realize that it "
	  + "takes three members of the Cycle to demote or promote "
	  + "a Minstrel from the Cycle.\n");
    new_demote_file = DEMOTEDIR+str+"."+TP()->query_name();
    clone_object(EDIT_OBJ)->edit("done_demoting", comments);
    return 1;
}

int
do_promote(string str)
{
    string *files;
    int i, which;
    string comments = "", *members, committee;
    object niceguy, scroll;
    
    seteuid(getuid(TO()));
    if (strlen(TP()->query_special_title()))
    {
	write("Hey! You don't seem to be a member of the Cycle!\n");
	remove_object();
	return 1;
    }
    committee = read_file(COMMITTEE_FILE);
    members = explode(committee, "**");
    which = member_array(GUILDMASTERJR, members);   
    if (which == -1)
    {
        write("There doesn't seem to be a vacancy on the Cycle. "
	      + "Do you need to demote somebody first?\n");
	return 1;
    }
    str = lower_case(str);
    if (sizeof(get_dir(PROMOTEDIR+str+"."+TP()->query_name())))
    {
	write("You have already voted to promote " +capitalize(str) 
	      + " to the Cycle. The other members of the Cycle "
	      + "must now pass judgement on the matter.\n");
	return 1;
    }
    files = get_dir(PROMOTEDIR+str+".*");
    if (sizeof(files) >= 2)
    {
	write("Three members of the Cycle have cast a vote to promote "
	      +str+" to the Cycle. So shall it be!\n");
        niceguy = find_player(str);
        if (niceguy)
        {
            niceguy->CM("You have been promoted to the Cycle! Thanks "
	              + "for your willingness to serve and good "
	              + "luck in your new duties!\n");
	    scroll = clone_object(GUILDOBJ+"scroll");
	    scroll->move(niceguy);
        }
        members[which] = str;
        committee = implode(members, "**");
        rm(COMMITTEE_FILE);
        write_file(COMMITTEE_FILE, committee);
	
	for (i=0;i<sizeof(files);i++)
	{
	    if (TP()->query_wiz_level())
		write("Removing file "+files[i]+"\n");
	    rm(PROMOTEDIR+files[i]);
	}
	return 1;
    }
    write("Please explain your reasons for wishing to promote "
          + capitalize(str) + " to the Cycle. Realize that it "
	  + "takes three members of the Cycle to demote or promote "
	  + "a Minstrel to the Cycle.\n");
    new_promote_file = PROMOTEDIR+str+"."+TP()->query_name();
    clone_object(EDIT_OBJ)->edit("done_promoting", comments);
    return 1;
}
    
void done_promoting(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_promote_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_promote_file, comments);
}

void done_demoting(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_demote_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_demote_file, comments);
}

void done_awarding(string comments)
{
    if (TP()->query_wiz_level())
	TP()->CM("Creating file "+new_award_file+"\n");
    seteuid(getuid(TO()));
    write_file(new_award_file, comments);
}

int do_award(string str)
{
    string *files, filename;
    int i;
    string comments = "";
    object niceguy, fork;

    str = lower_case(str);
    seteuid(getuid(TO()));
    if (! strlen(TP()->query_special_title()))
    {
	write("Hey! You don't seem to be a member of the Cycle!\n");
	remove_object();
	return 1;
    }
    if (!SECURITY->exist_player(str))
    {
      write("Are you sure "+str+" is the name of a player?\n");
      return 1;
    }
    filename = AWARDDIR + str + "." + TP()->query_name();
    if (file_size(filename) != -1)
    {
	write("You have already expressed your sentiments; the other "
	      + "members of the Cycle must now pass judgement.\n");
	return 1;
    }
    if (file_size(AWARDDIR+"Awarded."+str) != -1)
    {
	write(capitalize(str)+" already seems to have been presented "
	      + "an award!\n");
	return 1;
    }
    
    files = get_dir(AWARDDIR+str+".*");
    if (sizeof(files) >= 2)
    {
        niceguy = find_player(str);
	write("Three members of the Cycle have cast a vote to award "
	      +str+" a platinum fork. ");
	if (niceguy)
	{
	    write("So shall it be!\n");
	}
	else
	{
	    write("But "+capitalize(str)+" is not in the game right now! "
		  + "Try again later.\n");
	    return 1;
	}
	niceguy->CM("Congratulations! For your "
		    + "contributions to the August Order of Minstrels, "
		    + "the Cycle has voted to award you that most "
		    + "prized Minstrel possession, the platinum "
		    + "tuning fork of Kyrsis!\n");
	fork = clone_object(GUILDOBJ+"fork_platinum");
	fork->move(niceguy);

	write_file(AWARDDIR+"Awarded."+str, "Awarded a platinum fork to "
		  + str + " on " + ctime(time())+ "\n");
	for (i=0;i<sizeof(files);i++)
	{
	    string tmp;
	    if (TP()->query_wiz_level())
	    {
		write("Copying file "+files[i]+" to Awarded."+str+"\n");
	    }
	    tmp = read_file(AWARDDIR+files[i]);
	    write_file(AWARDDIR+"Awarded."+str, files[i] +":\n"+tmp+"\n");
	    rm(AWARDDIR+files[i]);
	}
	return 1;
    }
    write("Please explain your reasons for wishing to award "
          + capitalize(str) + ". What outstanding contributions has "
	  + capitalize(str) + " made to the Minstrels? Realize that "
	  + "three Cycle members must vote to present such an award.\n");
    new_award_file = filename;
    clone_object(EDIT_OBJ)->edit("done_awarding", comments);
    return 1;
}

int 
do_demoted(string str)
{
    string *files = get_dir(DEMOTEDIR);
    int i;

    if (sizeof(files) == 0)
    {
	TP()->CM("No demotions have currently been recommended.\n");
	return 1;
    }
    for (i=0;i<sizeof(files);i++)
    {
	string demotee, critic;

	demotee = explode(files[i], ".")[0];
	critic = explode(files[i], ".")[1];
	TP()->CM("\t"+critic+" has recommended that " + capitalize(demotee)
	         + " be demoted because:\n" 
		 + read_file(DEMOTEDIR + files[i]));
    }
    return 1;
}

int 
do_promoted(string str)
{
    string *files = get_dir(PROMOTEDIR);
    int i;

    if (sizeof(files) == 0)
    {
	TP()->CM("No promotions have currently been recommended.\n");
	return 1;
    }
    for (i=0;i<sizeof(files);i++)
    {
	string promotee, fan;

	promotee = explode(files[i], ".")[0];
	fan = explode(files[i], ".")[1];
	TP()->CM("\t"+fan+" has recommended that " + capitalize(promotee)
	         + " be promoted because:\n" 
		 + read_file(PROMOTEDIR + files[i]));
    }
    return 1;
}


