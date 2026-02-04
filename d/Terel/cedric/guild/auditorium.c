#pragma save_binary

inherit "/std/room";

#include "/d/Terel/common/terel_defs.h"
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/cedric/guild/guild_funs.c"


#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <composite.h>

#define ADJARRAY  ({"a perky","a frivolous","a funny","a silly", \
		    "a popular","a catchy","a happy","an annoying", \
		    "a clever","a cute","a mournful","a sad","an amusing"})


/*
 * The Minstrel Guild Headquarters: The Performance Hall.
 * Cedric 2/93
 */

int occupied;
string whosonstage;

string room_str;
string on_stage_str;

object requestbox;

/* add some prototypes */

varargs int do_perform(string str, string special_verb);
int tell_whosonstage(string whoson);

reset_room()
{
/*
    if (!present("requestbox", TO()))
    {
        requestbox=clone_object("/d/Terel/vader/reqbox");
        requestbox->move(TO());
    }
*/
     
}


/*********************************************************
 * This section to add redirects for the commands enabled
 * in this room, as well as to disable says, shouts, etc
 * while someone is on stage.
 *********************************************************/

void init()
{
    ::init();
    add_action("do_improv", "enter");
    add_action("do_finished", "exit");
    add_action("do_bothersome", "say");
    add_action("do_bothersome", "shout");
    add_action("do_bothersome", "'", 1);
    add_action("do_perform", "play");
    add_action("do_perform", "perform");
    add_action("do_perform", "sing");
    add_action("do_bothersome", "whisper");
    add_action("do_bothersome", "mumble");
/*  add_action("do_sign_up", "sign");
*/
/*
    add_action("do_request", "request");
*/

}
/*
 ****************************************************************************
 * Function:     comment_filter
 * Description:  Filters out lines begining with a "#" sign
 * 
 * Usage:        ARR = filter(ARR, "comment_filter", this_object);
 *               where ARR is the array of lines you wish to filter.
 */

int
comment_filter(string line)
{
    if (line[0] == '#') 
	return 0;
    else 
	return 1;
}


/***********************************************************
 * code to allow a player to request a song be played.  
 * NPC's, as well as players, can take a request from the
 * board and choose whether or not to honor that request.
 * The request board will be similar to a standard board, 
 * but with no text, only subject lines.  Player and NPC
 * alike must take them in the order in which they arrive.
 ***********************************************************/
int
do_request(string reqstr)
{
    if(TP()->query_met_name() == whosonstage)
    {
        write("Your the one on stage.  You don't need to request "
        + "that!!\n");
        return 1;
    }
    else
    {
        write("You request that " + reqstr + " be performed.\n");
        say(QCTNAME(TP()) + " requests a song be performed.\n");      
  
        /* insert neat code here */

        return 1;
    }
}     

/***********************************************************
 * small bit to capture the open and close command.  If    
 * the player tries to open the box, but is not on the 
 * stage, the command is trapped.  Otherwise, they are 
 * allowed to continue opening whatever it is they are
 * opening
 ***********************************************************/
public int
tell_whosonstage(string whoson)
{
    if(whoson == whosonstage)
        return 1;
    else
        return 0;   
}

/***********************************************************
 * code to disable some of the annoying things players can 
 ***********************************************************/

int
do_bothersome()
{   
    if (occupied == 1)
    {
        if (TP()->query_met_name() == whosonstage)
        {   
            if (present(find_player(lower_case(whosonstage))))
            {
               return 0;
            }
            else
            { 
               occupied = 0;
               whosonstage = "";
               return 0;
            }
        }
        else
        {
         write("Knowing that it would be rude to interrupt the "
         + "performer on stage, you decide to remain quiet.\n");
         return 1;
        }
    }

return 0;

} 


/*
 ***************************************************************************
 * Function:	do_perform
 * Description: An outrageously complex function. Sings, plays, or performs
 *		a Mundane, Ballad, or Epic, softly or loudly.
 * Arguments:	str - the command line after the verb
 *		special_verb - used by do_loudly and do_softly to indicate
 *		whether the player is singing, playing, or performing.
 * Note:	terribly obfuscated code. Would benefit from being split into
 *		multiple functions.
 *
 * ** This is a slight modification by Vader for this room.  It disables
 *    the ability for others to hear the songs outside of the room, 
 *    as well as prevents songs of power from being used here.  No fighting
 *    is allowed.  The code was taken from /d/Terel/cedric/guild/soul.c
 *    and remains mostly intact for optimum similarity.
 */

varargs int
do_perform(string str, string special_verb)
{
   object  song_book; 
   mixed   songfile, *argarray, affected; 
   string  songstr, type, which, songtext, selftext;
   string  trash, newtitle, *title_words, verb, adverb, text;
   int     evocal, einstrumental, i, j, size;
   
   songfile =0; affected = 0; verb = "";
   
   NF("Usage: "+query_verb()+" <type> <song> OR "+query_verb()+" <song>\n"
      + BS("Where <type> is mundane, or ballad, and <song> is the "
	   + "title, the first word of the title, or the number of a song "
	   + "in your book.  Note that songs of power cannot take place "
         + "in this room.\n"));


    if (occupied == 1)
        {
            if (TP()->query_met_name() != whosonstage)
            {   
                if(present(find_player(lower_case(whosonstage))))
                {
                    write("Knowing that it would be rude to interrupt the "
                    + "performer on stage, you decide to remain quiet.\n");
                    return 1;
                }
            }
            else
                return 0; 
        }


       
/* Alignment check - added by HO */
    
    if(TP()->query_alignment() < -100)
    {
      TP()->CM("The Muses do not answer the call from your evil heart.\n");
      
      return 1;
    }

/*==========================================================================*
 * Parsing the command: first, extract the song and find its filename.
 */
   
   if (!str)
      return 0;
				   
   song_book = present("minstrel_song_book",TP());
   
   if (parse_command(str,TP(),"%s 'for' / 'at' %s",songstr,affected))
   {
      if (sscanf(songstr,"%s %s",type,which))
	 songfile = parse_song(type,which,song_book->query_mundane(),
			       song_book->query_ballad(),
			       song_book->query_epic(),
                               song_book->query_power());
			       
      
      if (!songfile)
	 if (!(songfile=parse_song("mundane",songstr,
				  song_book->query_mundane(), ({}),({}),({}))))
      
      if (!(songfile=parse_song("ballad",songstr,({}), 
			       song_book->query_ballad(),({}),({}))))
      
      if (!(songfile=parse_song("epic",songstr,({}), ({}),
			       song_book->query_epic(),({}))))
      
      
      {
	 NF("Usage: "+query_verb()+" <type> <song> OR "+query_verb()
	   + " <song>\n"+BS("Where <type> is "
	   + "mundane, or ballad, and <song> is the title, "
	   + "the first word of the title, or the number of a song "
	   + "in your book.\n"));
	 
	 return 0;
      }
      
      
   }
   
   else 
   {
      if (sscanf(str,"%s %s",type,which))
   {
   songfile = parse_song(type,which,song_book->query_mundane(),
			song_book->query_ballad(),
			song_book->query_epic(),
                        song_book->query_power());
			
   }
      if (!songfile)
      {
	 if (!(songfile=parse_song("mundane",str,
				  song_book->query_mundane(),({}),({}),({}))))
	 
	 if (!(songfile=parse_song("ballad",str,({}), 
				  song_book->query_ballad(),({}),({}))))
	 
	 if (!(songfile=parse_song("epic",str,({}), ({}),
				  song_book->query_epic(),({}))))
	 
	 if (!(songfile=parse_song("power",str, ({}), ({}), ({}), 
				  song_book->query_power())))
	 {
	    NF("Usage: "+query_verb()+" <type> <song> OR "+query_verb()
	      + " <song>\n"+BS("Where <type> is "
	      + "mundane, or ballad, and <song> is the title, "
	      + "the first word of the title, or the number of a song "
	      + "in your book.\n"));
	    
	    return 0;
	 }
      }
   }

/*==========================================================================*
 * Check the player's voice and instrument damage levels. If either is
 * greater than 5, disable it. If both are disabled, the player can't do it.
 */
   
   songtext = ""; selftext = "";
   
   switch (i = TP()->query_skill(SG_VOCAL_DAMAGE))
   {
      case 0: 
	   evocal = TP()->query_skill(SG_VOCAL);
      break;
      
      case 1..5: 
	   selftext += "somewhat handicapped by your weakened voice, ";
	   songtext += "somewhat handicapped by "+TP()->query_possessive()
		    + " weakened voice, ";
	   evocal = TP()->query_skill(SG_VOCAL)/i;
      break;
      
      default:
	      selftext += "unable to use your shattered voice, ";
	      songtext += "unable to use "+TP()->query_possessive()+" voice, ";
	      
	      evocal = 0;
	      verb = "play";
      break;
   }
   
   switch (j = present("minstrel_instrument", TP())->query_damage())
   {
      case 0:
	   einstrumental = TP()->query_skill(SG_INSTRUMENTAL);
      break;
      
      case 1..5: 
	   if (songtext!="") { selftext += "and "; songtext += "and "; }
	   selftext += "hindered by the poor tone of your damaged instrument, ";
	   songtext += "hindered by the poor tone of "+TP()->query_possessive()
		    + " instrument, ";
	   einstrumental = TP()->query_skill(SG_INSTRUMENTAL)/j;
      break;
      
      default:
	     if (songtext!="") { selftext += "and "; songtext += "and "; }
	     selftext += "unable to use your ruined instrument, ";
	     songtext += "unable to use "+TP()->query_possessive()
		      +" ruined instrument, ";
	     
	     einstrumental = 0;
	     verb = "sing";
      break;
   }
   
   if (i>5 && j>5)
      {
      NF(BS("Neither your voice nor your instrument is usable; you "
	    + "cannot perform the song.\n"));
      return 0;
   }

   if (TP()->query_prop("_minstrel_i_singing"))
   {
       NF("You are already performing a song!\n");
       return 0;
   }

/*==========================================================================*
 * Find an adverb appropriate to the minstrel's skill level.
 */
   if (verb == "sing")
       adverb = TP()->query_vocal_skill_adverb();
   else if (verb == "play")
       adverb = TP()->query_instrument_skill_adverb();
   else /* verb == "perform" */
       adverb = TP()->query_minstrel_skill_adverb();
   
   if (i>1 && j>1 && TP()->query_skill(SG_INSTRUMENTAL)
			   + TP()->query_skill(SG_VOCAL))
      adverb = "nevertheless "+adverb;
   
   /* 
    * At this point we have a valid song path+filename in songfile. Next, see
    * if the song attempted is a Mundane, or Ballad, and act upon that:
    */
   
   newtitle = "";
   size = sizeof(title_words = explode(explode(read_file(songfile, 1, 1),
					       "**")[0] + " "," "));
   
   for (j=0;j<size;j++)
       if (j<size-1)
	  newtitle+=capitalize(title_words[j])+" ";
       else
	  newtitle+=capitalize(title_words[j]);

   /* ---------------- Mundane ----------------- */
   if (wildmatch(MUNDANEDIR+"*",songfile))
   {
       if (special_verb && strlen(special_verb))
	   verb = special_verb;
       else if (verb=="") 
	   verb = query_verb();
      
       text = implode(filter(explode(read_file(songfile, 2)+"\n", "\n"), 
			     "comment_filter", TO()), "\n");
       argarray = ({});
       argarray += ({text, TP(), verb, 1});
      
       TP()->change_prop("_minstrel_i_singing", 1);
       if (TP()->query_prop(MINSTREL_I_VOLUME) == SOFT)
	   adverb = "softly and " + adverb;
       else if (TP()->query_prop(MINSTREL_I_VOLUME) == LOUD)
	   adverb = "loudly and " + adverb;
       TP()->CM(capitalize(selftext+"you "+adverb+" "+verb+" "
			   + newtitle+":\n"));
       
       say(capitalize(songtext+QTNAME(TP())+" "+adverb+" "+verb+"s a song: \""
		      + newtitle+"\".\n"), TP());

       if (verb != "play")
	   "/d/Terel/cedric/guild/soul.c"->sing_song(argarray);
       return 1;
   }
   /* ---------------- Ballad or Epic ----------------- */
   if (wildmatch(BALLADDIR+"*", songfile)) 
      {
      if (special_verb && strlen(special_verb))
	  verb = special_verb;
      else if (verb=="") 
	  verb = query_verb();
      
      argarray = ({});
      
      if (TP()->query_mana() < 7)
      {
	 write("You are mentally drained; the singing of a Ballad is "
	      + "beyond your powers right now.\n");
	 return 1;
      }
      text = implode(filter(explode(read_file(songfile, 2)+"\n", "\n"), 
	    "comment_filter", TO()), "\n");
      argarray += ({text, TP(), verb, 1});
      
      TP()->change_prop("_minstrel_i_singing", 1);
      if (TP()->query_prop(MINSTREL_I_VOLUME) == SOFT)
	  adverb = "softly and " + adverb;
      else if (TP()->query_prop(MINSTREL_I_VOLUME) == LOUD)
	  adverb = "loudly and " + adverb;
      TP()->CM(capitalize(selftext+"you "+adverb+" "+verb+" "
	      + newtitle+ ((verb != "play") ? ":\n" : ".\n")));
      
      say(capitalize(songtext+QTNAME(TP())+" "+adverb+" "+verb+"s a song: \""
	 + newtitle+"\".\n"), TP());
      
      if (verb == "play")
	    set_alarm(10.0, 0.0, &"/d/Terel/cedric/guild/soul.c"->stop_singing_now(TP()));
      else
	    "/d/Terel/cedric/guild/soul.c"->sing_song(argarray);
      
      
      if (TP()->query_prop(MINSTREL_I_VOLUME, SOFT))
	  TP()->add_mana(-3); /* Singing a ballad uses a little mana. */
      else
	  TP()->add_mana(-7);
      
      return 1;
   }
   
   
   return 0;
}
/*=========================================================================*/



/*********************************************************
 * code to enable a player to take the stage, if not
 * already occupied.  Also silences the room so that he or
 * she can perform in peace.
 *********************************************************/


int
do_improv(string str1)
{
    if (str1 == "stage")
    {
        if (occupied == 0)          /* is it empty? */
        {
            occupied = 1;
            whosonstage = TP()->query_met_name();
            room_str = "The stage is currently occupied " 
            + "by someone named " + TP()->query_met_name()
            + ".\n";
            set_long(on_stage_str + room_str);  
            write("Seeing that noone is on stage, you take it "
           + "yourself.  To exit, just 'exit stage'.\n");
            say("Seeing that noone is on stage, " + QCTNAME(TP())
            + " takes the stage.\n");
            return 1;
        }
        else                 /*  its not empty   */
        {   
            if (TP()->query_met_name() == whosonstage)   
            {
                write("You are already on stage.\n");
                return 1;
            }
            else
            {   
                if(present(find_player(lower_case(whosonstage))))
                {
                    write("Someone else is there already.  Wait your "
                    + "turn!.\n");
                    return 1;
                }
                else
                {
                    whosonstage = TP()->query_met_name();
                    room_str = "The stage is currently occupied " 
                    + "by someone named " + TP()->query_met_name()
                    + ".\n";
                    set_long(on_stage_str + room_str);  
                    write("Seeing that noone is on stage, you take it "
                    + "yourself.\n");
                    say("Seeing that noone is on stage, " + QCTNAME(TP())
                    + " takes the stage.\n");
                    return 1; 
                 }
            }
        } 
    }
    else
    {
        write("Enter what?\n");
        return 1;
    }         
    
    
}

/*******************************************************
 * Code to allow the performer to leave the stage,  
 * so that others may enter it.
 *******************************************************/

int
do_finished()
{
    if (occupied == 1)        /* is it full?  */
    {
        if (whosonstage == TP()->query_met_name())
        {
            write("You step down from the stage, having had enough.\n");
            say(QTNAME(TP()) + " steps down from the stage.\n");
            occupied = 0;
            whosonstage = "";
            room_str = "There is currently noone on stage.\n"; 
            set_long(on_stage_str + room_str); 
            return 1;
        }
    }
    write("But you are not on stage!!\n");
    return 1;
}

int
check_enter()
{
    if (MEMBER(this_player()) || this_player()->query_wiz_level())
	return 0;
    else
	TP()->catch_msg(("That way lies the inner sanctum of the Minstrels; "
	+ "only the initiated may pass.\n"));
    return 1;
}

void 
create_room() 
{
    ::create_room();
    occupied = 0;
    whosonstage = "";
    room_str = "There is currently noone on stage.\n";

    on_stage_str = "A cozy little performance hall where the Minstrels "
    + "come to display their skills for others to see.  The guild "
    + "sponsors a performer daily to entertain the crowd, and "
    + "at selected times you can take the stage and improvise your "
    + "own performance.  The audience chamber is furnished with "
    + "lavish wooden chairs decked with ornate woven seat cushions, "
    + "each from a different continent.  The walls are decorated with "
    + "murals depicting actual Minstrels in everyday life.  Light "
    + "fills the room from the candles that surround the room, high "
    + "atop the walls.  The stage is simple, with a fake door painted "
    + "on the back wall.  "; 

    set_short("The Auditorium of the Minstrels"); 
    set_long(on_stage_str + room_str);

    add_item(({"stage", "simple stage"}),
      "This simple little stage is but a platform of fine oak floor "
    + "boards built onto the back wall.  The back wall itself is "
    + "plain, with the exception of the painted door.\n");

    add_item(({"back wall", "door", "painted door"}),
      "A painting of a door, quite unremarkable at that.\n");

    add_item(({"Audience Chamber", "seats", "chairs"}), 
      "This small auditorium, which can hold only twenty or thirty "
    + "people, is small yet cozy.  The chairs are lined up, five to "
    + "a row, with two columns, for two rows.  Extra chairs are stacked "
    + "in the rear of the chamber should their be a need.  Each of "
    + "these chairs is wide and sturdy, with armrests, and cushions.  "
    + "These cushions each have different patterns woven into them.  "
    + "some of the patterns remind you of those you have seem on "
    + "other continents.\n");

    add_item(({"candles", "candle", "light"}), 
      "At spots roughly three feet apart all throught this "
    + "auditorium, candles provide the light.  They are all white "
    + "in colour, and are placed high in the ceiling to prevent "
    + "accidentally or purposelly blowing them out.\n");

    add_item(({"wall", "walls", "murals", "paintings"}), 
      "Each of these murals depicts various scenes that Minstrels "
    + "from all walks of life are probably participating in right "
    + "now.  Carolers parading down the street during a festival, "
    + "a party of three questors using a song to tame a wild beast, "
    + "and even a lone Minstrel using music to heal the sick.\n");

    add_exit(GUILD+"courtyard", "north"); 
    add_exit(GUILD+"tower_mundane", "southeast"); 
    add_exit(GUILD+"office", "southwest", "@@check_enter");
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();

}
