#pragma save_binary

inherit "/std/object.c";
#include <macros.h>
#include <options.h>

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "../guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"

/*
 * The Minstrel's SongBook
 * Here the minstrel scribes the songs he or she wishes to carry though life.
 * This object contains pointers to each song the minstrel knows. There are
 * three types of songs - Mundane Songs, Ballads, and Songs of Power. Mundane
 * Songs are simply emotes, with no other effects. Ballads are more regulated
 * songs (each must be approved by the Cycle) with such musical potency
 * that a minstrel singing a Ballad is heard by all others in the game. They
 * are intended for use as a sort of guild-line. Songs of Power are basically
 * spells. The filenames stored in the Song Book are accessed by the Minstrel
 * soul commands 'sing', 'play', and 'perform'.
 */

object owner;

object
query_owner()
{
    return owner;
}

void 
set_owner(object ob)
{
    owner = ob;
}

void
create_object()
{
    set_name("songbook");
    add_name("minstrel_song_book");
    add_adj("song");
    set_short("Minstrel's songbook");
    set_long(BS("This small book is along with your instrument the badge "
    + "of your membership in the August Order of Minstrels. The songs of "
    + "the Minstrels are their lifeblood, and those shall you "
    + "store in this book. Every Ballad available to the Minstrels shall "
    + "be written by its own magic into this book. But choose carefully "
    + "the Mundane Songs and Songs of Power you copy into these pages, "
    + "for the number of each that may be written within is limited. As "
    + "your days in the guild increase, so shall the pages in your song "
    + "book.\n")
    + "\nYou may always type <help minstrels> for more information.\n");
    add_prop(OBJ_M_NO_DROP, BS("You needn't drop the song book of the "
    + "Minstrels.\n"));
}

/*
 * Function:	int add_mundane(string str)
 * Description: Tries to add a song filename to mundane_songs. The max
 *		number of Mundanes is (guild_stat/2) + 4.
 * Arguments:	str - the filename of the song, minus the path.
 * Returns:	0 if successful, 1 if unsuccessful.
 */
int
add_mundane(string str)
{
    string *mundanes = SONGBOOK_MANAGER->query_mundane_songs(owner);
    if ((sizeof(mundanes) > owner->query_stat(SS_LAYMAN) / 5 + 4) &&
	(owner->query_special_title() == 0))
    {
	return 0;
    }

    SONGBOOK_MANAGER->add_mundane_songs(owner, str);
}

/*
 * Function:    int add_power(string str)
 * Description: Tries to add a song filename to power_songs. The max          
 *              number of  Songs of Power is (guild_stat/20) + 1.
 * Arguments:   str - the filename of the song, minus the path.
 * Returns:     0 if successful, 1 if unsuccessful.
 * Note:	It is the responsibility of the calling object to insure
 *		that other requirements (such as guild membership, read
 * 		music skill ability, and so on) are satified! This 
 * 		function only checks the number of allowed songs.
 */            
int            
add_power(string str)            
{            
    string *powers = SONGBOOK_MANAGER->query_power_songs(owner);
    if ((sizeof(powers) > owner->query_stat(SS_LAYMAN) / 20 + 1) &&
	(owner->query_special_title() == 0))
    {
	return 0;
    }

    SONGBOOK_MANAGER->add_power_songs(owner, str);
}
         

/*
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in mundane_songs.
 */
string
list_mundane()
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
}

/*
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in ballad_songs, and that end with ".song".
 */
string
list_ballad()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "ballad.titles";

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo ballads\n";
    }

    return sprintf("%-#*s\n", scrw, str);
}

/*
 * list_epic():
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in ballad_songs, and that end with ".epic".
 */
string
list_epic()
{
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    string str;
    string file = SONG_ROOT + "epic.titles";

    setuid();
    seteuid(getuid());

    if ((file_size(file) <= 0) ||
        !strlen(str = read_file(file)))
    {
        return "\tNo epic ballads\n";
    }

    return sprintf("%-#*s\n", scrw, str);
}

/*
 * Return a formatted, tabulated list of the songs whose filenames
 * are listed in power_songs. Note that the title of a Song of Power
 * is the same as it's filename...this implies that Songs of Power
 * all have 1-word titles..Blast, Soothe, Shield, Vibrato, etc.
 * Note also that the first line of a Power looks like:
 * /**Blast**Cedric
 */
string
list_power()
{
    string *power;
    int scrw = this_player()->query_option(OPT_SCREEN_WIDTH);
    int i;
    string fmt, str, title;
    
    setuid();
    seteuid(getuid());

    power = SONGBOOK_MANAGER->query_power_songs(this_player());

    str = "";
    fmt = "%" + strlen(sizeof(power) + "") + "d. %s\n";
    for (i = 0; i < sizeof(power); i++)
    {
        title = (POWER_SONGS_DIR + power[i])->query_name();
	if (title == 0)
	{
	    title = "UNKNOWN";
	}
        title = SONG_INDEX->capitalize_title(title);
	str += sprintf(fmt, i + 1, title);
    }

    return sprintf("%-#*s", scrw, str);
}

int
do_erase(string str)
{
    notify_fail("Temporarily disabled.\n");
    return 0;

#if 0
    string type, which, is_song, songfile;
    int songnum;
    
    if (!str) return 0;
    if (sscanf(str, "%d", songnum))
    {
	if (is_song = parse_song("mundane", str, mundane_songs, ({}), ({}), ({})))
	{
	    songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
	    mundane_songs -= ({songfile});
	    TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
	    return 1;
	}
    }
    if (sscanf(str,"%s %s",type,which))
    {
	is_song = parse_song(type,which,mundane_songs,ballad_songs,query_epic(),power_songs);
	if (type == "power")
	{
	    songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
	    power_songs -= ({songfile});
	    TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
	    return 1;
	}
	if (type == "ballad")
	{
	    TP()->CM("You can't erase a Ballad! They are written by their own "
	    + "potent magic into each Minstrel's songbook. Nor need you erase a "
	    + "Ballad, for they do not affect the number of pages remaining in your "
	    + "songbook.\n");
	    return 1;
	}
	if (type == "epic")
	{
	    TP()->CM("You can't erase an Epic! They are Ballads, each written "
	    + "by its own "
	    + "potent magic into every Minstrel's songbook.\n");
	    return 1;
	}
	if (type == "mundane")
	{
	    songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
	    mundane_songs -= ({songfile});
	    TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
	    return 1;
	}
    }
    if (is_song=parse_song("mundane",str,mundane_songs, ({}), ({}), ({})))
    {
	songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
	mundane_songs -= ({songfile});
	TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
	return 1;
    }
    if (is_song=parse_song("ballad",str,({}), ballad_songs, ({}), ({})))
    {
	TP()->CM("You can't erase a Ballad! They are written by their own "
	+ "potent magic into each Minstrel's songbook. Nor need you erase a "
	+ "Ballad, for they do not affect the number of pages remaining in your "
	+ "songbook.\n");
	return 1;
    }
    if (is_song=parse_song("epic",str,({}), ({}), query_epic(), ({})))
    {
	    TP()->CM("You can't erase an Epic! They are Ballads, each written "
	    + "by its own "
	    + "potent magic into every Minstrel's songbook.\n");
	    return 1;
	}
    if (is_song=parse_song("power", str, ({}), ({}), ({}), power_songs))
    {
	songfile=explode(is_song, "/")[sizeof(explode(is_song, "/"))-1];
	power_songs -= ({songfile});
	TP()->CM("You erase "+CAP_TITLE(is_song)+"from your songbook.\n");
	return 1;
    }
    notify_fail(BS("Erase which song? The correct syntax is:\n")
    + "        erase <type> <song>\n"
    + "where <type> is mundane, ballad, or power,  and <song> is the number, title\n"
    + "(in lowercase), or first word of the title of the song you wish to erase.\n");  
    return 0;
#endif
}

int
do_read(string str)
{
    object ob1;
    string type, which, is_song;
    int songnum;
    
    if (!strlen(str)) 
	return 0;
    if (str == "epics" || str == "Epics")
    {
	say(QCTNAME(TP())+" studies "+TP()->query_possessive()
	+ " song book.\n");
	if (query_verb() == "mread")
	{
	    this_player()->more("The songbook contains the following "
					 + "Epics:\n" + list_epic()+"\n");
	}
	else
	{
	    write("The songbook contains the following "
		  + "Epics:\n" + list_epic()+"\n");
	}
	return 1;
    }
    if (str == "ballads" || str == "Ballads")
    {
	say(QCTNAME(TP())+" studies "+TP()->query_possessive()
	+ " song book.\n");
	if (query_verb() == "mread")
	{
	    this_player()->more("The songbook contains the following "
					 + "Ballads:\n" + list_ballad()+"\n");
	}
	else
	{
	    write("The songbook contains the following "
		  + "Ballads:\n" + list_ballad()+"\n");
	}
	return 1;
    }
    if (str == "mundanes" || str == "Mundanes")
    {
	say(QCTNAME(TP())+" studies "+TP()->query_possessive()
	+ " song book.\n");
	if (query_verb() == "mread")
	{
	    this_player()->more("The songbook contains the " +
			        "following Mundane Songs:\n" + list_mundane());
	}
	else
	{
	    write("The songbook contains the following Mundane Songs:\n"
		  + list_mundane());
	}
	return 1;
    }
    if (str == "Songs of Power" || str == "songs of power" || str == "powers")
    {
	say(QCTNAME(TP())+" studies "+TP()->query_possessive()
	+ " song book.\n");
	write("The songbook contains the following Songs of Power:\n"
	+ list_power()+"\n");
	return 1;
    }
    if (parse_command(str, TP(), "%o", ob1))
    {
	if (ob1==TO())
	{
	    string text = "";
	    
	    say(QCTNAME(TP())+" studies "+TP()->query_possessive()
	    + " song book.\n");
	    text += "This songbook, which belongs to ";
	    text += query_owner()->query_name();
	    text += ", is dedicated to the Muse ";
	    text += query_owner()->query_muse_name() + ".\n";
	    text += "It contains the following:\n";
	    text += "<<Mundane Songs>>\n"+list_mundane();
	    text += "<<Ballads>>\n"+list_ballad();
	    text += "<<Songs of Power>>\n"+list_power();
	    text += "Also listed are the great Epics; in them the "
	    + "story of each Minstrel's life is immortalized in song.\n";
	    if (query_verb() == "mread")
	    {
	        this_player()->more(text);
	    }
	    else
	    {
	        write(text);
	    }
	    return 1;
	}
    }
#if 0
    if (sscanf(str, "%d", songnum))
    {
	if (is_song = parse_song("mundane", str, mundane_songs, ({}), ({}), ({})))
	{
	    this_player()->more("\n"+read_file(is_song, 2));
	    return 1;
	}
    }
    if (sscanf(str,"%s %s",type,which))
	is_song = parse_song(type,which,mundane_songs,ballad_songs,query_epic(),power_songs);
    if (type == "power")
    {
	TP()->catch_msg(BS(is_song->query_purpose()));
	return 1;
    }
    if (!is_song)
	if (!(is_song=parse_song("mundane",str,mundane_songs, ({}), ({}), ({}))))
	    if (!(is_song=parse_song("ballad",str,({}), ballad_songs, ({}), ({}))))
		if (!(is_song=parse_song("epic",str,({}), ({}), query_epic(), ({}))))
		    if (is_song=parse_song("power", str, ({}), ({}), ({}), power_songs))
		    {
			TP()->catch_msg(BS(is_song->query_purpose()));
			return 1;
		    }
    if (is_song)
    {
	this_player()->more("\n"+read_file(is_song, 2));
	return 1;
    }
#endif
    notify_fail(BS("Read what? The songbook, maybe? The Epics? Or did you mean to "
    + "read a certain song? In that case, the correct syntax would be:\n")
    + "        read <type> <song>\n"
    + "where <type> is mundane, ballad, or power,  and <song> is the number, title\n"
    + "(in lowercase), or first word of the title of the song you wish to read.\n");

    return 0;
}

string
query_auto_load()
{
    return MASTER + ":";
}

void
init()
{
    ::init();

    if (!query_owner())
    {
        set_owner(this_player());
    }

    add_action("do_read", "read");
    add_action("do_read", "mread");
    add_action("do_erase", "erase");
}
