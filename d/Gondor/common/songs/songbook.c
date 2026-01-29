/*
 * /d/Gondor/gnadnar/obj/songbook.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * Ok, so it's a wiz toy ... but Gorboth's "We Three G's" is soooooo
 * cool, a small wiz toy is justified.
 *
 * most songs are in ~gondor/common/songs/
 */

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>	/* for OBJ_I_*	 	*/
#include "/d/Gondor/defs.h"	/* always ...	 	*/


#define	SONG_DELAY	5.0	/* delay between alarm actions	*/
#define	SONGDIR		"/d/Gondor/common/songs/"

/* prototypes */
public void	create_object();
public void	enter_env(object dest, object from);
public void	init();
public int	songdir(string dir);
public int	read(string arg);
public int	sing(string arg);
public int	stop(string arg);
public void	sing_the_song(int count);
public void	ponder_the_tune(string s);
public void	remove_object();
public int	check_drop();


static string	Directory;	/* directory holding songs		*/
static string	*Songs;		/* all the songs			*/
static int	Nsongs;		/* # of songs in book			*/
static string	*Stanzas;	/* stanzas of current song		*/
static int	Song_alarm;	/* so we don't start two songs at once	*/
static object	TheWiz;		/* who's holding us			*/


/* 
 * Function name:	create_object
 * Description	:	set up the songbook
 */
public void
create_object()
{
    FIX_EUID;
    set_name("songbook");
    add_name( ({ "song book", "book" }) );
    set_adj( ({ "slim", "leatherbound" }) );
    set_short("songbook");
    set_long(BSN("The slim leatherbound songbook looks fairly new."));
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, check_drop);
    songdir(SONGDIR);
} /* create_object */


/*
 * Function name:	enter_env
 * Description	:	after parent, be sure our env is a wizard
 * Arguments	:	object dest -- destination
 *			object from -- where we came from
 */
public void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);

    if ( !objectp(ENV()) ||
	 !ENV()->query_wiz_level() )
    {
	set_alarm(1.0, 0.0, &remove_object());
    }
} /* enter_env */


/*
 * Function name:	init
 * Description	:	add verbs
 */
public void
init()
{
    add_action(songdir,	"songdir");
    add_action(read,	"read");
    add_action(sing,	"sing");
    add_action(stop,	"stop");
} /* init */


/*
 * Function name:	songdir
 * Description	:	set the directory containing song files
 * Arguments	:	string dir -- the directory
 * Returns	:	1 if good dir, 0 if not
 */
public int
songdir(string dir)
{
    if ( !strlen(dir) )
    {
	if ( QVB == "songdir" )
	{
	    notify_fail("USAGE: songdir directory\n");
	}
	return 0;
    }
    if ( !sizeof(get_dir(dir)) )
    {
	if ( QVB == "songdir" )
	{
	    write(BSN("ERROR: directory '"+dir+"' does not exist, or is empty."));
	}
	return 1;
    }
    Directory = dir;
    if ( extract(dir, -1) != "/" )
    {
	Directory += "/";
    }
    Songs = get_dir(Directory);
    Nsongs = sizeof(Songs);
    if ( QVB == "songdir" )
    {
	write(BSN("Set songs directory to '"+Directory+"'"));
    }
    return 1;
} /* songdir */


/*
 * Function name:	read
 * Description	:	read the songbook
 * Arguments	:	string arg -- whatever the wizard typed
 * Returns	:	1 on success, 0 on failure
 */
public int
read(string arg)
{
    object	ob;
    int		i;

    if ( !strlen(arg) )
    {
	NF0("Read what?\n");
    }
    if ( parse_command(LOW(arg), ({ TO }), "[the] %o", ob) )
    {
	if ( !Nsongs )
	{
	    write("The songbook, which refers to '"+Directory+"', is empty.\n"+
	          "You may refer to a different directory via the command:\n"+
		  "	songdir directory_name\n");
	}
	else
	{
	    write("The songbook, which refers to '"+Directory+
		  "', holds the following songs:\n");
	    for ( i = 0; i < Nsongs; ++i )
	    {
		write("	"+Songs[i]+"\n");
	    }
	    write("You may refer to a different directory via the command:\n"+
		  "	songdir directory_name\n");
	}
	return 1;
    }

    if ( (i = member_array(arg, Songs)) >= 0 )
    {
	write(read_file(Directory+Songs[i]));
	return 1;
    }

    NF0("Read what?\n");
} /* read */


/*
 * Function name:	sing
 * Description	:	sing a song
 * Arguments	:	string arg -- presumably the song name
 * Returns	:	1 if we know the song, 0 if not
 */
public int
sing(string arg)
{
    string	songtext,
		title,
		tune;
    int		i;

    if ( !strlen(arg) )
    {
	write("Sing what?\n");
	return 1;
    }

    if ( Song_alarm )
    {
	write("You are already singing.\n");
	return 1;
    }

    if ( (i = member_array(arg, Songs)) < 0 )
    {
	write("The songbook does not contain the song '"+arg+"'\n");
	return 1;
    }

    songtext = read_file(Directory+Songs[i]);
    if ( !strlen(songtext) )
    {
	write("Unfortunately, the song '"+arg+"' seems to have been "+
	    "expunged.\n");
	return 1;
    }

    TheWiz = TP;
    /* N.B. the "\n\n" separator means that all songs should
     * end in a blank line.
     */
    Stanzas = explode(songtext, "\n\n");
    write("You clear your throat for attention.\n");
    SAY(" clears "+TheWiz->query_possessive()+" throat for attention.");
    if ( sscanf(Stanzas[0], "%s::TUNE::%s", title, tune) == 2 )
    {
	Stanzas[0] = title;
	Song_alarm = set_alarm(SONG_DELAY, 0.0, &ponder_the_tune(tune));
    }
    else
    {
	Song_alarm = set_alarm(SONG_DELAY, 0.0, &sing_the_song(0));
    }
    return 1;
} /* sing */

/*
 * Function name:	ponder_the_tune
 * Description	:	ponder the tune of the song
 * Arguments	:	string s -- the tune
 */
public void
ponder_the_tune(string s)
{
    if ( strlen(s) )
    {
	write("You ponder the tune of \""+s+"\".\n");
	SAY(" ponders the tune of \""+s+"\".");
    }
    Song_alarm = set_alarm(SONG_DELAY, 0.0, &sing_the_song(0));
} /* ponder_the_tune */

/*
 * Function name:	sing_the_song
 * Description	:	do the actual singing
 * Arguments	:	int count -- where we are in the song
 */
public void
sing_the_song(int count)
{
    int		n;
    object	tp;
    string	author,
		title;

    Song_alarm = 0;
    if ( ENV() != TheWiz )
    {
	return;
    }

    /* called from alarm, so be sure this_player() is our wizzie */
    tp = this_player();
    set_this_player(TheWiz);

    if ( !(n = sizeof(Stanzas)) )
    {
	set_this_player(tp);
	return;
    }

    if ( count == 0 )
    {
    	if ( sscanf(Stanzas[0], "%s::AUTHOR::%s", title, author) == 2 )
	{
	    title = "\""+title+"\", by "+author;
	}
	else
	{
	    title = "\""+Stanzas[0]+"\"";
	}
	write(BSN("You begin the song "+title+"."));
	/* can use SAY here */
	SAY(" begins the song "+title+".");
    }
    else if ( count == 1 )
    {
	write("You sing:\n"+Stanzas[1]+"\n");
	/* don't use SAY() ... it calls BSN, which ruins the song format */
	say( ({ (G_METNAME(G_TP)+" sings:\n"+Stanzas[1]+"\n"), 
                (G_CTNONMET(G_TP)+" sings:\n"+Stanzas[1]+"\n"),
                ("Someone" + " sings:\n"+Stanzas[0]+"\n") }) );
    }
    else if ( count < n )
    {
	write("You continue to sing:\n"+Stanzas[count]+"\n");
	/* don't use SAY() ... it calls BSN, which ruins the song format */
	say( ({ (G_METNAME(G_TP)+" continues to sing:\n"+Stanzas[count]+"\n"), 
                (G_CTNONMET(G_TP)+" continues to sing:\n"+Stanzas[count]+"\n"),
                ("Someone" + " continues to sing:\n"+Stanzas[0]+"\n") }) );
    }
    else
    {
	write("You sing the final note and fall silent.\n");
	SAY(" sings the final note and falls silent.");
    }

    if ( count < n )
    {
	Song_alarm = set_alarm(SONG_DELAY, 0.0, &sing_the_song(++count));
    }
    set_this_player(tp);
} /* sing_the_song */

/*
 * Function name:	stop
 * Description	:	stop singing or brewing coffee
 * Arguments	:	string arg -- "shovel", "singing", "brewing", "coffee"
 * Returns	:	1 on success, 0 on failure
 */
public int
stop(string arg)
{
    if ( !Song_alarm ||
         ( arg != "singing" &&
	   arg != "song" ) )
    {
	return 0;
    }

    remove_alarm(Song_alarm);
    Song_alarm = 0;
    write("You stop singing.\n");
    return 1;
} /* stop */


/*
 * Function name:	remove_object
 * Description	:	remove outstanding alarm before destructing
 */
public void
remove_object()
{
    if ( Song_alarm )
    {
	remove_alarm(Song_alarm);
	Song_alarm = 0;
    }
    ::remove_object();
}


/*
 * Function name:	check_drop
 * Description	:	distinguish "drop" from "give", allow the latter.
 * Returns	:	0 if "give", 1 if "drop"
 */
public int
check_drop()
{
    if ( QVB == "give" )
    {
	return 0;
    }
    return 1;
}
