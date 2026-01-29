
/**********************************************************************
 *   LARSREYKR                                                        *
 *                                                                    *
 * - /d/Sparkle/clubs/lgellirs/mbrobj.c                             - *
 * - membership object of the (club) Gellir of Lars                 - *
 * - functions provided for musing, forming and binding LARSGALDRAR - *
 * - critical functionality for handling gellir deaths              - * 
 * - extensive help functionality                                   - *
 *                                                                    *
 * - Vitwitch 2022                                                  - *
 **********************************************************************/

#define EDITOR "/obj/edit"

#define STDPARALY "/std/paralyze.c"
#define MUSEPARALYSISTIME 5
#define MUSEPARALYSIS "_lgellirs_musing_paralysis_"

#include "defs.h"

#include <formulas.h>
#include <files.h>
#include <language.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <macros.h>
#include <math.h>
#include <flags.h>
#include <const.h>
#include <time.h>

inherit "/std/object";

/*
pGALDRmap and gPhraseMap index strings and data definitions

"MDEFINED" : string 0 or 1 galdr is defined (ie. bound)
"MFULLTXT" : string full text of galdr
"MLSTKRAF" : string spaced list of kraftords
"MLSTNTKR" : string spaced list of non-kraft words
"MHEARDTM" : string time() when galdr was heard by Lars
"MHEARDXL" : string experience point loss at hearing
"MARTVOTE" : string number of artistry votes by Wizards
*/

/* GLOBAL VARIABLES ==================== */

static int gMaxWords = 100; 
static int gNumColumns = 80;
static int gMaxRows = 16; 
static int gNumRows;

static string *gDefaultWords = ({ "a", "i", "male", "female", "neuter", 
  "an", "and", "or", "first", "second", "third", 
  "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", 
  "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", 
  "fifteenth", "sixteenth", "seventeenth", "nineteenth", 
  "twentieth", "thirtieth", "fortieth", "fiftieth", "sixtieth", 
  "seventieth", "eightieth", "ninetieth", "hundreth", "thousandth", 
  "one", "two", "three", "four", "five", "six", "seven", "eight", 
  "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", 
  "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "thirty", 
  "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred", 
  "thousand", "orc", "goblin", "gnome", "gnomish", "hobbit", "halfling", 
  "human", "elf", "elven", "dwarf", "dwarven", "man", "woman", "men", 
  "women", "humans", "elves", "goblins", "gnomes", "dwarves", 
  "hobbits", "orcs", "orcish", "gnomish", "you", "he", "she", "it", 
  "his", "her", "its", "no", "not", "o", "oh", "say", "said", "yes", 
  "can", "will", "could", "would", "does", "did", "do", "done", "has", 
  "have", "had", "world", "domain", "realm", "these", "this", "that", 
  "of", "all", "is", "was", "what", "who", "why", "when", "where", 
  "then", "s", "es", "if", "so", "the", "in" });

// words *found* in the Realms and useable by the Larsreykr holder
// ... recording whether the mused word is a KRAFTORD or not
static mapping gMuseWordMap = ([]);   

// phrase (potential GALDRAR) ... has same structure
static mapping gPhraseMap = ([]);

// help information for commands
static mapping gHelpMap = ([]);

// rule information for GALDRAR
static string gHelpTagGal = "galdrar";
static mapping gRuleMap = ([]);

// information on purpose/joining/leaving/etc Larsgellirs
static string gHelpTagGel = "gellirs";
static mapping gClubMap = ([]);

static int gGALDRLoaded = 0;

// completed <bind>ed GALDR for owner-player
mapping pGALDRmap = ([]);


/* PROTOTYPES ====================  */

string lrgw( string str );
string lrgwh( string str );
string lrgwhg( string str );
string lrgwhc( string str );
int is_larsreykr();
void create_object();
string long_description();
string fill_row( string rump, string char );
string list_wordmap( string char, mapping mpg );
string query_auto_load();
string query_recover();
varargs void message_from_npc( string str, string *adjl );
public void get_mapping_data();
public void put_mapping_data();
void init_words_maps( object plyr );
string fill_row( string rump, string char );
string *explode_strip_string( string str );
int is_death_chamber( object room );
mapping musemap_string_update( string str );
string muse_search( object e, string str );
int muse_outcome( string str, object plyr );
void muse_words( object plyr, string str );
string powr_difference_descr( int val0, int val1 );
int is_a_player_name( string word );
void done_forming_phrase( string phrase );
void form_phrase();
void bind_galdr( object plyr );
void sing_galdr( object plyr, int tried_to_yell );
void lars_hearing_messaging( int count, object plyr );
void lars_unbound_messaging( int count, object plyr );
void lars_tooweak_messaging( int count, object plyr );
void process_gellir_death( object plyr );
void yell_galdr( object plyr );
string gellir_rule( string str );
string galdr_rule( string str );
void command_help( object plyr, string str );
int larsreykr_action( string str );
void init();
void enter_env( object dest, object old );

/* FUNCTIONS =============== */

string
lrgw( string str )
{
    return "<"+ LARSREYKR_ACTION_WORD + " " + str + ">"; 
}


string
lrgwh( string str )
{
    return "<"+ LARSREYKR_ACTION_WORD + " help " + str + ">"; 
}


string
lrgwhg( string str )
{
    return "<"+ LARSREYKR_ACTION_WORD + " help galdrar " + str + ">"; 
}


string
lrgwhc( string str )
{
    return "<"+ LARSREYKR_ACTION_WORD + " help gellirs " + str + ">"; 
}


int
is_larsreykr()
{
    return 1;
}

void
reset_object()
{
   setuid();
   seteuid(getuid());
}


void
create_object()
{
    if (!IS_CLONE)
      return;

    set_name("larsreykr");
    set_pname("larsreykr");

    add_name(LGELLIR_OBJ_ID);
    add_pname(LGELLIR_OBJ_ID + "s");

    set_short("stream of Larsreykr");
    set_pshort("streams of Larsreykr");

    set_long("@@long_description");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);

    add_prop(OBJ_I_INVIS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_GET, 1);

    reset_object();
}

string
long_description()
{
    return "This is a stream of Larsreykr -- "+
           "the smoke come from burning the wood of "+
           "the original trees of creation. It swirls in and "+
           "about one's essence. It grants the ability to "+
           "yell up to Lars in Extremis -- chanting "+
           "galdrar in order to find favour with him.\n\n";
}


string
fill_row( string rump, string char )
{
    int i;
    int icol0 = strlen(rump);
    if ( icol0 > 80 ) return "";
    if ( strlen(char) != 1 ) return "";

    string outstr = rump;
    for ( i=icol0;i<80;i++) outstr += char;
    return outstr + "\n";
}


string
list_wordmap( string char, mapping mpg )
{
    if ( m_sizeof(mpg) > 0 )
    {
        if ( strlen(char) != 1 ) char = "-";
        string line = fill_row("", char);
        string str = line;
        foreach ( string word : sort_array(m_indices(mpg)) )
        {
            if ( mpg[word] == 1 ) word = upper_case(word);
            str += word + " ";
        }
        str += "\n";
        return str + line + "\n\n";
    }
    else
        return "";
}


string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":";
}


string
query_recover()
{
    // already auto_loading
    return 0;
}


varargs void
message_from_npc( string msg, string *adjl )
{
    int i;
    string str = "";
    object plyr = this_player();
    string gname = plyr->query_real_name();

    str += one_of_list(adjl) + "... ";

    for ( i=0;i<gNumColumns;i++ )
        str += "~";

    str += "\n" + msg + "\n";

    for ( i=0;i<gNumColumns;i++ )
        str += "~";

    str += " ..." + one_of_list(adjl)+ "\n";

    string tellstr = sprintf("\n\n%s\n\n%s...\n\n%s\n...%s\n\n",
          LGELLIR_NPC_MESGSTART,
          capitalize(one_of_list(LGELLIR_NPC_MORTALADDR)) + " " +
	  LGELLIR_PETNAME(gname),
          str, capitalize(LGELLIR_NPC_ADJ0) + "-" +
	  capitalize(LGELLIR_NPC_ADJ1));

   plyr->catch_msg(tellstr);

   return;
}


public void
get_mapping_data()
{
    object p = this_player();
    // "0" prefix denotes current bound map
    string galdrmapname = sprintf("%d_%s",0,p->query_real_name());

    setuid();
    seteuid(getuid());

    pGALDRmap = restore_map( LGELLIRGALDRAR + galdrmapname );

    if ( !mappingp(pGALDRmap) || !m_sizeof(pGALDRmap) ) 
    {
        // initialise a blank map
        pGALDRmap["MDEFINED"] = "0";
        pGALDRmap["MFULLTXT"] = "";
        pGALDRmap["MLSTKRAF"] = "";
        pGALDRmap["MLSTNTKR"] = "";
	pGALDRmap["MHEARDXL"] = "";
	pGALDRmap["MHEARDTM"] = "";
	pGALDRmap["MARTVOTE"] = "";
    }

    gGALDRLoaded = 1;
    return;
}


public void
put_mapping_data()
{
    object p = this_player();
    // "0" prefix denotes current bound map
    string galdrmapname = sprintf("%d_%s",0,p->query_real_name());
    setuid();
    seteuid(getuid());
    save_map( pGALDRmap, LGELLIRGALDRAR + galdrmapname );
    return;
}


void
init_words_maps( object plyr )
{
    // initialise muse-word map

    gMuseWordMap = ([]);

    if ( !gGALDRLoaded ) get_mapping_data();

    // add player name by default
    gMuseWordMap[plyr->query_real_name()] = -1;  // NOT a KraftOrd

    // add non-kraftord default words
    foreach ( string word : gDefaultWords )
        gMuseWordMap[word] = -1;  // NOT a KraftOrd

    // add words from GALDRmap
    if ( pGALDRmap["MDEFINED"] != "0" )
    {
        foreach ( string word : explode(pGALDRmap["MLSTKRAF"]," ") )
            gMuseWordMap[word] = 1;  // IS a KraftOrd
        foreach ( string word : explode(pGALDRmap["MLSTNTKR"]," ") )
            gMuseWordMap[word] = -1;  // NOT a KraftOrd
    }

    return;
}


string
*explode_strip_string( string str )
{
    int n = 0;
    string *outarr = ({""});

    if ( !strlen(str) ) return outarr;

    foreach ( string char : explode(lower_case(str),"") )
    {
        if ( wildmatch("[^abcdefghijklmnopqrstuvwxyz]",char) )
        {
           outarr += ({""});
           n++;
        }
        else
           outarr[n] = sprintf("%s%s",outarr[n],char);
    }

    outarr += ({""});
    n++;

    return outarr;
}


int
is_death_chamber( object room )
{
    return wildmatch( sprintf("%s*",LOGIN_DEATH), file_name(room) );
}


mapping
musemap_string_update( string str )
{
    // outmap only contains newly encountered words
    mapping outmap = ([]);

    if ( !strlen(str) ) return outmap;

    foreach ( string word : explode_strip_string(str) )
    {
        if ( gMuseWordMap[word] == 0 )
        {
            int isKO = IS_A_KRAFTORD(word); 
            outmap[word] = isKO; 
	    // want 1 or -1 for mused words
            gMuseWordMap[word] = 2*isKO-1;
        }
    }

    return outmap;
}


string
muse_search( object e, string str )
{
    string itmstr;

    if ( lower_case(str) == "here" ) 
        return e->long();
    else 
    {
        foreach ( mixed itm : e->query_item() )
            foreach ( string itmstr : itm[0] )
                if ( itmstr == str )
                {
                    return e->long(itmstr);
                }
    }
    return "";
}


int 
muse_outcome( string str, object plyr )
{
    string foundstr = muse_search( environment(plyr), str );

    if ( !strlen(foundstr) )
    {
        plyr->catch_msg("\nYour musing has NOT provided you any "+
	                "additional words.\n\n");
        return 0;
    }

    string outstr = list_wordmap( " ", 
                         musemap_string_update( foundstr ) );

    if ( !strlen(outstr) ) 
    {
        plyr->catch_msg("\nYour musing has NOT provided you any "+
	                "additional words.\n\n");
        return 0;
    }
    else
    {
        plyr->catch_msg("\nYour musing has provided you with additional "+
                "words (including KRAFTORDS):\n" + outstr + "\n\n");
        return 1;
    }
}


void
muse_words( object plyr, string inpstr )
{
    string outstr, objstr;
    string ls = lower_case(inpstr);

    if ( !gGALDRLoaded ) get_mapping_data();

    object room = environment(plyr);

    if ( is_death_chamber(room) )
    {
        if ( !pGALDRmap["MDEFINED"] )
            plyr->catch_msg("\nYou cannot " + lrgw("muse") + " words here -- "+
	                    "you are much too late.\n\n");
        else
            plyr->catch_msg("\nYou cannot " + lrgw("muse") + " words here. "+
	                    "You can try to " + lrgw("yell") + " the galdr "+
                            "you have bound to you.\n");
        return;
    }

    if ( room->is_lgellirroom() )
    {
        outstr = "You find nothing to muse upon in this place... "+
           "you must venture elsewhere.\n";
        plyr->catch_msg(outstr);
        return;
    }

    if ( !LGELLIR_PROCESS_ENABLED() )
    {
        plyr->catch_msg("You find yourself unable to muse... "+
	                "Lars is distracted... the Larsreykr is idle.\n");
        return;
    }

    int ttlexp = plyr->query_exp_combat() + plyr->query_exp_general();
    if ( F_DIE_REDUCE_XP(ttlexp) < LGELLIR_YELL_XPANTE ) 
    {
        plyr->catch_msg("You are too weak to " + lrgw("muse") + " words "+
	  "in Creation. You must hunt and herb in Creation to "+
	  "grow stronger before you try again.\n");
        return;
    }

    int nsec = MUSEPARALYSISTIME;

    // no argument signals, so recap existing mused words 

    if ( !strlen(ls) )
    {
        outstr = list_wordmap( " ", gMuseWordMap );

        if ( !strlen(outstr) ) 
        {
            plyr->catch_msg("\nMusing has NOT provided you any words " + 
                            "since waking.\n");
            return;
        }
        else
        {
            plyr->catch_msg("\nMusing has provided you these " +
                            "words (including KRAFTORDS) since waking:\n" +
			    outstr + "\n\n");
            return;
        }
    }

    // else spend some time musing for new words 

    objstr = inpstr;
    if ( ls == "here" ) objstr = "your surroundings";

    outstr = "You muse upon " + objstr 
           + " -- seeking words to form a Larsgaldr.\n";
    plyr->catch_msg(outstr);

    set_alarm( itof(nsec), 0.0, &muse_outcome(ls,plyr) );

    object obj = clone_object(STDPARALY);
    obj->set_standard_paralyze("musing");
    obj->set_fail_message("You are musing...\n");
    obj->set_stop_message("You stir from your musing...\n");
    obj->set_name(MUSEPARALYSIS);
    obj->set_remove_time(nsec + 1);
    obj->set_combat_stop(1);
    obj->move(plyr, 1);

    return;
}


string
powr_difference_descr( int val0, int val1 )
{
    int i, n;
    string str = "is";

    int idif01 = val0 - val1;

    n = abs(idif01)/3;
    for ( i=0;i<n;i++ )
        str += " much";

    if ( idif01 > 0 )
        str += " more powerful than";
    else
        str += " less powerful than";

    return str;
}


int
is_a_player_name( string word )
{
    // some players choose simple words as
    // names (eg. 'stone' 'rock') which are common
    // and useful in constructing galdrar so
    // they get no protection from being named
    // in galdrar

    if ( IS_AN_EXCEPTED_NAME(word) )
        return 0;

    // some players choose simple utility words as
    // names (eg. 'in' ... can you believe it?)
    // and get no protection from being named
    // in galdrar

    if ( member_array(word,gDefaultWords) != -1 );
        return 0;

    // some players choose names that 
    // are just adjectives (eg. 'light')
    // which are necessary for galdr
    // power determination, so they
    // get no protection from being
    // named in galdrar

    if ( IS_A_KRAFTORD(word) )
        return 0; 

    // to avoid being named in galdrar
    // players choose names that are
    // not common words...

    if ( SECURITY->exist_player(word) )
    {
        write_file( LGELLIRLOGS + "player_names", 
	    ctime(time()) + ": " + upper_case(word) + " excluded from " +
	    lrgw("form") + ".\n" );
        return 1;
    }

    return 0;
}


void
done_forming_phrase( string phrase )
{
    object plyr = this_player();

    int iw, ii, iiN, ip, jj, irow, icol, foundname;

    int in_a_word = 0;
    int nw = 0;
    int nmissw = 0;
    int nnamew = 0;
    int mxrepw = 0;
    int nkrftw = 0;
    int valid = 1;

    string w, lcc;
    string *grid = ({});
    string *words = ({});
    string *adjl;
    string PhraseReport = "";

    string pname = plyr->query_real_name();

    mapping editmap = ([]);

    gPhraseMap["MDEFINED"] = "0";  // signalling a new phrase

    if( !strlen(phrase) )
    {
        plyr->catch_msg("Aborted " + lrgw("form") + "ing...\n");
        return;
    }

    // scan the phrase for words and form the 2D grid

    icol = -1;
    irow = 0;

    foreach ( string char : explode(phrase,"") )
    {
        icol++;
        ii = gNumColumns * irow + icol;

        lcc = lower_case(char);

        grid += ({lcc});

        if ( wildmatch("[^abcdefghijklmnopqrstuvwxyz]",lcc) )
        {
            // character NOT a letter... word termination, possible new line

            if ( in_a_word && nw > 0 )
            {
                w = words[iw];

                if ( gMuseWordMap[w] == 0 )
                {
                    nmissw++;
                    editmap[w] = -1;
                    for ( jj=ii-strlen(w);jj<ii;jj++ )
                        grid[jj] = "_";
                }
                else if ( is_a_player_name(w) )
                {
                    nnamew++;
                    editmap[w] = -2;
                    for ( jj=ii-strlen(w);jj<ii;jj++ )
                        grid[jj] = "_";
                }
                else
                {
                    int m = editmap[w]; 
                    editmap[w] = m + 1;
                    mxrepw = max( mxrepw, editmap[w] ); 
                    if ( gMuseWordMap[w] > 0 ) nkrftw++;
                }
            }

            if ( in_a_word )
	       in_a_word = 0; 

            if ( char == "\n" )
            {
                // newline handling

                if ( icol != (gNumColumns-1) )
		{
                    // overwrite the newline
                    grid[ii] = " ";

                    // fill out the row ... leaving room
		    // to replace the newline at the end

                    int iiN = ii + gNumColumns - 1 - icol;
                    for ( ip=ii+1;ip<iiN;ip++) grid += ({" "});

                    // replace the newline
		    grid += ({"\n"});
		}

                icol = -1;
                irow++;
            }

        }
        else
        {
            // character IS a letter... word continuation, grid entry

            if ( !in_a_word )
	    {
	        in_a_word = 1;
		words += ({""});
		iw = nw;
		nw++;
            }

            words[iw] = sprintf("%s%s",words[iw],lcc);
        }

    }

    gNumRows = irow;
    words += ({""});
    iw = nw;
    nw++;

    if ( gNumRows > gMaxRows )
    {
        PhraseReport += "\n! more than " + LANG_NUM2WORD(gMaxRows) +
	                " lines !";
        valid = 0;
    }

    // check for excessive words
    if ( nw > gMaxWords )
    {
        PhraseReport += "\n! more than " + LANG_NUM2WORD(gMaxWords) 
                + " words !";
        valid = 0;
    }

    // check for excessive word repetition
    int maxfreq = max(nw/10,3);
    if ( mxrepw > maxfreq )
    {
        PhraseReport += "\n! same word more than " + 
                      LANG_NUM2WORD(maxfreq) + " times !";
        valid = 0;
    }

    // check for un-mused words
    if ( nmissw > 0 )
    {
        PhraseReport += "\n! " + capitalize(LANG_NUM2WORD(nmissw)) +
	                 " words un-<muse>d: "; 

        foreach ( string w : sort_array(m_indices(editmap)) )
        {
            if ( editmap[w] == -1 )
                PhraseReport += w + " "; 
        }
        PhraseReport += "!\n"; 
        valid = 0;
    }

    // check for player-name words
    //  ... blocked here instead of during musing to avoid CPU overhead
    if ( nnamew > 0 )
    {
        PhraseReport += "\n! " + capitalize(LANG_NUM2WORD(nnamew)) +
             " Names borne by others : "; 

        foreach ( string w : sort_array(m_indices(editmap)) )
        {
            if ( editmap[w] == -2 )
                PhraseReport += w + " "; 
        }
        PhraseReport += "!\n"; 
        valid = 0;
    }

    // check for at least one KRAFTORD present
    if ( !nkrftw ) 
    {
        PhraseReport += "\n! no Kraftord; powerless !"; 
        valid = 0;
    }
    
    // check for player name in the 'MESOSTIC' direction

    foundname = 0;

    // extract column words and try to wildmatch

    for ( icol=0;icol<gNumColumns;icol++ )
    {
        w = "";
        for ( irow=0;irow<gNumRows;irow++ ) 
            w = sprintf("%s%s",w,grid[gNumColumns * irow + icol]);

        if ( wildmatch(sprintf("*%s*",pname),w) )
        {
            foundname = 1;
            break;
        }
    }

    if ( !foundname ) 
    {
        PhraseReport += "\n! Name is not spelled !";
        valid = 0;
    }

    // return now if not valid

    if ( !valid ) 
    {
        PhraseReport += "\n\n!! Not a Larsgaldr !!";

        w = "";
        for ( irow=0;irow<gNumRows;irow++ ) 
        {
            for ( icol=0;icol<gNumColumns;icol++ )
               w += grid[gNumColumns * irow + icol];
        }

        adjl = ({"false","tricksy","invalid","delinquent","fallacious",
                   "erroneous","unruly","disorderly"});

        PhraseReport = sprintf( "\n%s\n\n%s\n\n", w, PhraseReport );
        message_from_npc( PhraseReport, adjl );

        return;
    }

    // else, set gPhraseMap fields

    gPhraseMap["MDEFINED"] = val2str(time());
    gPhraseMap["MFULLTXT"] = phrase;
    gPhraseMap["MLSTKRAF"] = "";
    gPhraseMap["MLSTNTKR"] = "";

    foreach ( string w : m_indices(editmap) ) 
    {
         if ( editmap[w] > 0 )
         {
             if ( gMuseWordMap[w] > 0 )
                 gPhraseMap["MLSTKRAF"] += sprintf(" %s",w);
             else
                 gPhraseMap["MLSTNTKR"] += sprintf(" %s",w);
         } 
    }

    // compare scores between PHRASE and <bind>ed GALDR

    if ( !gGALDRLoaded ) get_mapping_data();

    if ( !m_sizeof(pGALDRmap) )  
    {
       PhraseReport += "\n...can <bind> this Larsgaldr...\n";
    }
    else
    {
       PhraseReport += "\n...new Larsgaldr " +
          powr_difference_descr( LGELLIR_GALDR_POWER(gPhraseMap["MLSTKRAF"]),
                               LGELLIR_GALDR_POWER(pGALDRmap["MLSTKRAF"]) )
         + " than old one..."; 

       PhraseReport += "\n\n...could <bind> this new "+
	    "Larsgaldr instead of the old one...";
    }

    w = "";
    for ( irow=0;irow<gNumRows;irow++ ) 
    {
        for ( icol=0;icol<gNumColumns;icol++ )
           w += grid[gNumColumns * irow + icol];
    }

    adjl = ({"correct","worthy","unerring","abiding","true",
               "faultless","veracious","right"});

    PhraseReport = sprintf( "\n%s\n\n%s\n\n", w, PhraseReport );

    message_from_npc( PhraseReport, adjl );

    return;
}


void
form_phrase()
{
    object plyr = this_player();

    if ( !gGALDRLoaded ) get_mapping_data();

    if ( is_death_chamber( environment(plyr) ) )
    {
        if ( !pGALDRmap["MDEFINED"] )
            plyr->catch_msg("\nYou cannot " + lrgw("form") + " a new galdr -- "+
	                    "you are much too late.\n\n");
        else
            plyr->catch_msg("\nYou cannot " + lrgw("form") + " a new galdr. "+
	                    "You can try to " + lrgw("yell") + " the galdr "+
                            "you have bound to you.\n");
        return;
    }

    if ( !LGELLIR_PROCESS_ENABLED() )
    {
        plyr->catch_msg("You find yourself unable to form a galdr... "+
	                "Lars is distracted... the Larsreykr is idle.\n");
        return;
    }

    int ttlexp = plyr->query_exp_combat() + plyr->query_exp_general();
    if ( F_DIE_REDUCE_XP(ttlexp) < LGELLIR_YELL_XPANTE ) 
    {
        plyr->catch_msg("You are too weak to " + lrgw("form") + " a new "+
	  "Larsgaldr. You must hunt and herb in Creation to "+
	  "grow stronger before you try again.\n");
        return;
    }

    setuid();
    seteuid(getuid());

    object editor = clone_object(EDITOR);
    editor->set_activity("a message.");
    editor->edit("done_forming_phrase","");

    return;
}


void
bind_galdr( object plyr )
{
    if ( !gGALDRLoaded ) get_mapping_data();

    if ( is_death_chamber( environment(plyr) ) )
    {
        if ( !pGALDRmap["MDEFINED"] )
            plyr->catch_msg("\nYou cannot " + lrgw("bind") +
	                    " yourself to a new galdr -- "+
	                    "you are much too late.\n\n");
        else
            plyr->catch_msg("\nYou cannot " + lrgw("bind") +
	                    " yourself to a new galdr. "+
	                    "You can try to " + lrgw("yell") + " the galdr "+
                            "you have already bound.\n");
        return;
    }

    if ( !LGELLIR_PROCESS_ENABLED() )
    {
        plyr->catch_msg("You find yourself unable to bind a galdr... "+
	                "Lars is distracted... the Larsreykr is idle.\n");
        return;
    }

    int ttlexp = plyr->query_exp_combat() + plyr->query_exp_general();
    if ( F_DIE_REDUCE_XP(ttlexp) < LGELLIR_YELL_XPANTE ) 
    {
        plyr->catch_msg("You are too weak to " + lrgw("bind") + " a new "+
	  "Larsgaldr. You must hunt and herb in Creation to "+
	  "grow stronger before you try again.\n");
        return;
    }

    if ( !m_sizeof(gPhraseMap) || gPhraseMap["MDEFINED"] == "0" )
        plyr->catch_msg("You have no new Larsgaldr to which "+
          "you can <bind>. You must " + lrgw("form")
           + " one first.\n");
    else
    {
        pGALDRmap["MDEFINED"] = gPhraseMap["MDEFINED"];
        pGALDRmap["MFULLTXT"] = gPhraseMap["MFULLTXT"];
        pGALDRmap["MLSTKRAF"] = gPhraseMap["MLSTKRAF"];
        pGALDRmap["MLSTNTKR"] = gPhraseMap["MLSTNTKR"];
	pGALDRmap["MHEARDXL"] = "0";  // defined after death when yelled 
	pGALDRmap["MHEARDTM"] = "0";  // defined after death when yelled
	pGALDRmap["MARTVOTE"] = "0";  // defined by wizards... non-essential

        gPhraseMap["MDEFINED"] = "0";

        put_mapping_data();

        plyr->catch_msg("You <bind> yourself to your new Larsgaldr. It "+
          "sings in your essence. You can try to " + lrgw("yell") +
	  ".\n");
    }

    return;
}


void
sing_galdr( object plyr, int tried_to_yell )
{
    if ( !gGALDRLoaded ) get_mapping_data();

    if ( !m_sizeof(pGALDRmap) || pGALDRmap["MDEFINED"] == "0" )
    {
        plyr->catch_msg("You have no Larsgaldr bound to you. "+
          "You can " + lrgw("form") + " and " + lrgw("bind") + " yourself "+
          "to one.\n");
        return;
    }
    else
    {

        if ( tried_to_yell )
            plyr->catch_msg("You try to " + lrgw("yell") + " the Larsgaldr, "+
	                "to which you are bound, but you make no sound! "+
                         "You can hear it sing in your essence:\n\n" +
                         pGALDRmap["MFULLTXT"] + "\n");
        else
            plyr->catch_msg("A bound Larsgaldr "+
                         "sings within your essence:\n\n" +
                          pGALDRmap["MFULLTXT"] + "\n");
    }

    int ttlexp = plyr->query_exp_combat() + plyr->query_exp_general();
    if ( F_DIE_REDUCE_XP(ttlexp) < LGELLIR_YELL_XPANTE ) 
    {
        plyr->catch_msg("You are too weak to " + lrgw("yell") + " this "+
	  "Larsgaldr in Extremis. You must hunt and herb in Creation to "+
	  "grow stronger before you die.\n");
    }

    if ( !LGELLIR_PROCESS_ENABLED() )
    {
        plyr->catch_msg("You sense that the Larsreykr is idle... "+
	                "Lars is distracted... it would be unwise to "+
			"try to " + lrgw("yell") + " this galdr in Extremis.\n");
        return;
    }

    return;
}


void
lars_hearing_messaging( int count, object plyr )
{
    string str;

    switch(count)
    {
        case 0:
            str = "Your yell is silent; Larsreykr streams out from "+
	          "you anyway.\n\n";
            break;
        case 1:
            str = "Lars arrives through a rift in the fabric of space.\n\n";
            break;
        case 2:
            str = "Larsreykr returns from inside His ear -- to swirl in and "+
	          "about your essence.\n\n";
            break;
        case 3:
            str = "Lars nods at you in silent acknowledgement.\n\n";
            break;
        case 4:
            str = "Lars leaves.\n\n";
            break;
        default:
	    // no alarm set... messaging is complete
	    return;
    }

    plyr->catch_msg(str);

    count++;

    set_alarm(2.0, 0.0, &lars_hearing_messaging(count,plyr) );

    return;

}


void
lars_unbound_messaging( int count, object plyr )
{
    string str;

    switch(count)
    {
        case 0:
            str = "You try to yell for Lars, but nothing happens.\n\n";
            break;
        case 1:
            str = "Alone in Extremis, without a galdr bound, "+
	          "you ponder your choices.\n\n";
            break;
        default:
	    // no alarm set... messaging is complete
	    return;
    }

    plyr->catch_msg(str);

    count++;

    set_alarm(2.0, 0.0, &lars_unbound_messaging(count,plyr) );

    return;

}


void
lars_tooweak_messaging( int count, object plyr )
{
    string str;

    switch(count)
    {
        case 0:
            str = "You try to yell for Lars...\n\n";
            break;
        case 1:
            str = "Your essence is too weak to send forth the Larsreykr...\n\n";
            break;
        case 2:
            str = "You must hunt and herb in Creation to grow stronger!\n\n";
            break;
        default:
	    // no alarm set... messaging is complete
	    return;
    }

    plyr->catch_msg(str);

    count++;

    set_alarm(2.0, 0.0, &lars_tooweak_messaging(count,plyr) );

    return;

}


void
process_gellir_death( object plyr )
{
    int count;
    int itime = time();
    string pname = plyr->query_real_name();

    // determine combat+general experience lost in dying prior
    // to reaching this location (LOGIN_DEATH : post-death chamber)
    // by first inferring the death-exp-loss fraction (fxlfrc)
    // and assuming that it applies at all experience values
    // ie. ... for floats:
    // exp_post = exp_before - exp_loss
    // exp_loss = exp_before * fxlfrac 
    // --> exp_before = exp_post / ( 1.0 - fxlfrac ) 
    // --> exp_loss = exp_post * fxlfrac / ( 1.0 - fxlfrac )

    float fxlfrc = 0.001 * itof( F_DIE_REDUCE_XP(1000) );
    float fexppt = itof(plyr->query_exp_combat() + plyr->query_exp_general());
    int exp_loss = ftoi( fexppt * fxlfrc / ( 1.0 - fxlfrc ) );

    if ( exp_loss < LGELLIR_YELL_XPANTE ) 
    {
        // not enough exp pts lost for the yell
        count = 0;
        set_alarm(1.0, 0.0, &lars_tooweak_messaging(count,plyr) );
	return;
    }

    string exp_loss_str = val2str( exp_loss );

    if ( !gGALDRLoaded ) get_mapping_data();

    if ( !mappingp(pGALDRmap) || !m_sizeof(pGALDRmap) || 
          pGALDRmap["MDEFINED"] == "0" )
    {
        // gellir has no bound galdr at time of death... :(

        count = 0;
        set_alarm(1.0, 0.0, &lars_unbound_messaging(count,plyr) );

        write_file( LGELLIRLOGS + "unheard_deaths", 
	    ctime(itime) + " " + pname + " killed " +
	    "with exploss " + exp_loss_str + " unheard.\n" );
        return;
    }
    else
    {
        if ( exp_loss == atoi(pGALDRmap["MHEARDXL"]) )
	{
            // Suspect an attempt to "yell" again 
	    // in the death_chamber after a single death

	    plyr->catch_msg("\n\nYou are satisfied that your "+
	                    "galdr has already been heard by Lars.\n");
	    return;
	}
	else
	{
            pGALDRmap["MHEARDXL"] = exp_loss_str;
            pGALDRmap["MHEARDTM"] = val2str(itime);
	}

    }

    // save bound galdrmap into :
    //
    //   1. timestamped location for asynchronous handling by the
    //         daemon at reset/Armageddon
    //   2. current (0_..) location for future word reference and
    //         preventing multiple yells in Extremis for the same
    //         death

    setuid();
    seteuid(getuid());
    save_map( pGALDRmap, LGELLIRGALDRAR + sprintf("%d_%s",itime,pname) );
    save_map( pGALDRmap, LGELLIRGALDRAR + sprintf("0_%s",pname) );

    // update gellir map death
    // count and time of death
    LGELLIR_UPDATE_DEATHS(pname);

    count = 0;
    set_alarm(1.0, 0.0, &lars_hearing_messaging(count,plyr) );

    return;
}


void
yell_galdr( object plyr )
{
    if ( is_death_chamber(environment(plyr)) )
        process_gellir_death( plyr );
    else
        sing_galdr( plyr, 1 );

    return;
}


string
gellir_rule( string str )
{
    string outstr, inpstr, lab;
    string *arr = explode(str," ");

    if ( !sizeof(arr) || arr[0] != gHelpTagGel )
        return ""; 

    if ( m_sizeof(gClubMap) == 0 )
    { 
        lab = lrgwhc("overview");
        gClubMap["overview"] = "\n" +
              lab + " : Larsgellirs " + lrgw("form") + " and " +
	      lrgw("bind") + " Larsgaldrar. At "+
	      "the time of death of a gellir, the <bind>ed "+
	      "galdr is yelled, borne on Larsreykr from their soul, "+
	      "into the 'hearing' of Lars.\n\n At Armageddon, "+
	      "Lars confers "+
	      "his favour on the gellir he has 'heard' with the "+
	      "highest 'standing' since the "+
	      "previous Armageddon. The favoured gellir wins the 'boon' "+
	      "of Lars -- "+
	      "the experience lost by all gellirs who died since "+
	      "the previous Armageddon.\n\n" +
	      "The 'standing' for each gellir is equal to the sum of "+
	      "the POWER x TIME for each galdr heard since last Armageddon. "+
	      "The POWER of each galdr is determined by its composition. "+
	      "The TIME of each galdr is the length of time between its "+
	      "hearing and the time of hearing of the next galdr of the same "+
	      "gellir, or the time of Armageddon.\n"+
	      "Also see " +
	      lrgwh("form") + ", " +
	      lrgwh("bind") + ", " +
	      lrgwhc("armageddon") + ", " +
	      lrgwhc("boon") + ", " +
	      lrgwhc("larsreykr") + ", " +
	      lrgwhc("hearing") + " and" +
	      lrgwhg("overview") + ".\n";

        lab = lrgwhc("joining");
        gClubMap["joining"] = "\n" +
              lab + " : All mortal folk can become Gellirs of Lars "+
	      "by inspiring the Larsreykr at the Fire in the Askelund. "+
	      "If for some reason, a gellir has become unbound from their "+
	      "draught of Larsreykr, they can inspire it again at the "+
	      "same place. Larsgellirs can leave the calling by expiring "+
	      "the Larsreykr, also by the Fire. Also see " +
	      lrgwhc("larsreykr") + " and " +
	      lrgwhc("rooms") + " and " +
	      lrgwhc("leaving") + ".\n";

        lab = lrgwhc("leaving");
        gClubMap["leaving"] = "\n" +
              lab + " : Larsgellirs can leave their calling by "+
	      "expiring the Larsreykr beside the Fire which burns in "+
	      "the Askelund. All mortal folk can join again in the same " +
	      "place by inspiring the Larsreykr anew. "+
	      "Also see " +
	      lrgwhc("larsreykr") + " and " +
	      lrgwhc("rooms") + " and " +
	      lrgwhc("joining") + ".\n";

        lab = lrgwhc("titles");
        gClubMap["titles"] = "\n" +
              lab + " : Larsgellirs have simple titles. They are "+
	      "addressed by " + capitalize(LGELLIR_NPC_NAME) + ", according "+
	      "to the number of their hearings and the size of their "+
	      "unclaimed boons, whenever they renew inspiration of the "+
	      "Larsreykr from the Fire. She will otherwise address "+
	      "gellirs by their personal kraftords, in person and in "+
	      "messages. "+ 
	      "Also see " +
	      lrgwhc("rooms") + " and " +
	      lrgwhc("tender") + ".\n";

        lab = lrgwhc("rooms");
        gClubMap["rooms"] = "\n" +
              lab + " : Larsgellirs, more than other mortals, place "+
	      "significance on the Askelund, the ancient remnant ash grove "+
	      "in the wilds of Sparkle. The Fire of the Covenant burns there "+
	      "in a clearing, in the care of its tender, " +
	      capitalize(LGELLIR_NPC_NAME) + ". Following trails uphill "+
	      "through the Askelund, one finds the Litillgap -- the remnant "+
	      "abyss of the great Mikillgap which once girdled the world. "+ 
	      "From the precipice, Larsgellirs can <jump> to be taken up "+
	      "by the ether and so recieve the boon of Lars. Otherwise "+
	      "to <jump> is to visit Death and yell a Larsgaldr in the "+
	      "depths of the abyss. In travelling between "+
	      "the clearing of the Askelund and the Litillgap, gellirs "+
	      "encounter the Woodsman and the Ravens Two. Lastly, gellirs "+
	      "revere Extremis, the only place in all the World "+
	      "where the hearing of Lars can be reached by a yelled galdr. "+
	      "Also see " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("death") + ", " +
	      lrgwhc("extremis") + ", " +
	      lrgwh("yell") + ", " +
	      lrgwhc("boon") + ", " +
	      lrgwhc("joining") + ", " +
	      lrgwhc("leaving") + ", " +
	      lrgwhg("checks") + ", " +
	      lrgwhc("fire") + " and " +
	      lrgwhc("tender") + ".\n";

        lab = lrgwhc("tender");
        gClubMap["tender"] = "\n" +
              lab + " : "+ capitalize(LGELLIR_NPC_NAME) + " tends the "+
	      "Fire in the Askelund. She has been changed by her duties "+
	      "down through the Ages. The Fire symbolizes the Covenant " +
	      "between all mortal folk and Lars and Death. The Covenant "+
	      "allows mortals to know things and do things. "+
              capitalize(LGELLIR_NPC_NAME) + " was perhaps the first "+
	      "Larsgellir, having learned how to gain and benefit "+
	      "from the attention of Lars. "+
	      "Also see " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("death") + ", " +
	      lrgwhc("fire") + ", " +
	      lrgwhc("rooms") + " and" +
	      lrgwhc("covenant") + ".\n";

        lab = lrgwhc("covenant");
        gClubMap["covenant"] = "\n" +
              lab + " : The Covenant is the ancient agreement between "+ 
	      "the Creator -- Lars, the Destroyer -- Death, and all mortal "+
	      "folk. The Covenant grants mortal folk the ability to know "+
	      "and do things of their own choosing. These thoughts "+
	      "and deeds amuse and entertain Lars and Death. Before "+
	      "the Covenant, mortal things were mindless and simple " +
	      "and the mortal realms were dull and monotonous. " +
	      capitalize(LGELLIR_NPC_NAME) + " tends the Fire in the "+
	      "Askelund as the enduring symbol of the Covenant. " +
	      "Also see " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("death") + ", " +
	      lrgwhc("fire") + ", " +
	      lrgwhc("rooms") + " and" +
	      lrgwhc("tender") + ".\n";

        lab = lrgwhc("lars");
        gClubMap["lars"] = "\n" +
              lab + " : Lars created all the world in the beginning. "+ 
	      "The Covenant between Lars, Lord of Creation, "+
	      "and Death, and all mortal kind allowed folk to make their "+
	      "own way in the world. Their decisions and actions provide "+
	      "a source of distraction for Lars and Death. Despite this, "+
	      "Lars is often distant -- only very rarely do the affairs of "+
	      "mortals capture his attention. Only at the point of death, "+
	      "in the presence of Death, will Lars attend. His "+
	      "heralds, the Two Ravens, taught mortal kind how to yell "+
	      "Larsgaldrar in the hearing of Lars at these times. Mortals "+
	      "who carefully craft their galdrar, with kraftords found among "+
	      "his works "+
	      "of Creation, win his favour. Having won favour, they may "+
	      "claim his boon when the "+ 
	      "world is remade anew after Armageddon. "+
	      "Also see " +
	      lrgwhg("overview") + ", " +
	      lrgwhg("kraftord") + ", " +
	      lrgwhc("overview") + ", " +
	      lrgwhc("hearing") + ", " +
	      lrgwhc("boon") + ", " +
	      lrgwhg("checks") + ", " +
	      lrgwhc("covenant") + " and" +
	      lrgwhc("death") + ".\n";

        lab = lrgwhc("death");
        gClubMap["death"] = "\n" +
              lab + " : Death stalks the world created by Lars, as the ever "+
	      "necessary Lord of Destruction. Death and Lars are balanced "+ 
              "in the world. Through ever present, Death is little known "+
	      "and often misunderstood. It is only in the presence of Death, "+
	      "that mortals encounter Lars and seek the favour of the "+
	      "Lord of Creation. Death also hears their Larsgaldrar at these "+
	      "times, oft repeated afterwards by the Woodsman, his harbinger "+
	      "in the Askelund. Also see " +
	      lrgwhc("hearing") + ", " +
	      lrgwhc("rooms") + ", " +
	      lrgwhg("checks") + ", " +
	      lrgwhc("covenant") + " and" +
	      lrgwhc("lars") + ".\n";

        lab = lrgwhc("larsreykr");
        gClubMap["larsreykr"] = "\n" +
              lab + " : The Larsreykr is the smoke which rises from the Fire "+
	      "of the Askelund. It rises from the burning of the ancient wood "+
	      "of the sacred trees of Lars. It binds to the essence "+
	      "of Larsgellirs. It is the inspiration by which gellirs "+
	      "can muse upon the world, and form and bind their galdrar. "+
	      "It is the Larsreykr which issues from the essence of a gellir "+
	      "at point of death which carries galdrar into the hearing "+
	      "of Lars, so to win his favour. "+
	      "Also see " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("hearing") + ", " +
	      lrgwhc("joining") + ", " +
	      lrgwhg("overview") + " and" +
	      lrgwhc("rooms") + ".\n";

        lab = lrgwhc("fire");
        gClubMap["fire"] = "\n" +
              lab + " : Fire strikes the balance between creation and "+
	      "destruction necessary for mortal folk to make their way "+
	      "in the world. The Fire which burns in the Askelund, symbolizes "+
	      "this Covenant between Lars and Death and mortalkind. Its "+
	      "tender is " + capitalize(LGELLIR_NPC_NAME) + ". "+
	      "Also see " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("larsreykr") + ", " +
	      lrgwhc("death") + ", " +
	      lrgwhc("covenant") + ", " +
	      lrgwhc("rooms") + " and" +
	      lrgwhc("tender") + ".\n";

        lab = lrgwhc("extremis");
        gClubMap["extremis"] = "\n" +
              lab + " : Extremis is the name Larsgellirs give to the "+
	      "large circular chamber that lies after Death and before life. "+
	      "At the center of Extremis stands a shimmering blue portal, "+
	      "beside which a column of white light rises from the ground. "+
	      "The portal and column allow all Folk of the Fire to choose "+
	      "between bodies old and new in their Return. It is only from "+
	      "Extremis, that bound galdrar can be yelled, to carry to "+
	      "the hearing of Lars -- who is usually close by. " +
	      "Also see " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("hearing") + ", " +
	      lrgwh("bind") + " and " +
	      lrgwh("yell") + ".\n";

        lab = lrgwhc("hearing");
        gClubMap["hearing"] = "\n" +
              lab + " : Larsgellirs can have as many hearings "+
	      "as they wish during the time between Armageddons. "+
	      "A hearing occurs after the death of the gellir, "+
	      "when in Extremis, *if* they have a galdr <bind>ed "+
	      "at the time. Additional "+
	      "hearings allow more and more powerful galdrar to be "+
	      "heard before Armageddon in the hope to win the "+
	      "favour of Lars at Armageddon. After the hearing, the "+
	      "heard gellir gains 'standing' at a rate of the 'power' "+
	      "of the galdr with every passing second -- until the next "+
	      "hearing, or Armageddon, whichever comes first. "+ 
	      "A hearing can involve "+
	      "a galdr that has already been heard in the same "+
	      "Armageddon-period. The bound galdr also heard by all "+
	      "mortals present at the time and place of death of a gellir. "+
	      "Also see " +
	      lrgwhc("overview") + ", " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("extremis") + ", " +
	      lrgwh("yell") + ", " +
	      lrgwhc("armageddon") + ", " +
	      lrgwhg("checks") + " and " +
	      lrgwhg("power") + ".\n";

        lab = lrgwhc("boon");
        gClubMap["boon"] = "\n" +
              lab + " : At Armageddon, Lars confers favour on the "+
	      "Larsgellir, heard since last Armageddon, who has the "+
	      "highest standing. Gellirs can claim these boons "+
	      "of Lars at the Litillgap at any time of their choosing. "+
	      "Such a boon causes growth in any gellir who receives "+
	      "it. This growth does not attract guild taxes. "+
	      "The unclaimed boons of each gellir accumulate "+
	      "with Lars until they are claimed. The size of unclaimed boons "+
	      "decrease slightly with each passing Armageddon. The size of "+
	      "unclaimed boons forms part of the title of a Larsgellir. "+
	      "Also see " +
	      lrgwhc("rooms") + ", " +
	      lrgwhc("tax") + ", " +
	      lrgwhc("titles") + ", " +
	      lrgwhc("overview") + ", " +
	      lrgwhc("armageddon") + ", " +
	      lrgwhc("hearing") + " and" +
	      lrgwhc("lars") + ".\n";

        lab = lrgwhc("tax");
        gClubMap["tax"] = "\n" +
              lab + " : When a Larsgellir claims a boon that is owed "+
	      "to them, they grow. Unlike other non-quest experience, "+
	      "this growth is not taxed by the guilds to which the gellir "+
	      "belongs. This is because the lost experience "+
	      "which makes up the boon was taxed when it was first earned. "+
	      "Also see " +
	      lrgwhc("boon") + ", " +
	      lrgwhc("overview") + ", " +
	      lrgwhc("armageddon") + ", " +
	      lrgwhc("hearing") + " and" +
	      lrgwhc("lars") + ".\n";

        lab = lrgwhc("armageddon");
        gClubMap["armageddon"] = "\n" +
              lab + " : At Armageddon, Lars confers favour on the "+
	      "Larsgellir, heard since last Armageddon, who has the "+
	      "highest standing. That gellir can claim this boon "+
	      "from the Litillgap after Armageddon or not as they see "+
	      "fit. Unclaimed boons accumulate over time, with only "+
	      "a slight decrease in their size with each passing Armageddon. "+
	      "The galdr <bind>ed to each "+
	      "gellir is **unbound** at Armageddon. Larsgellirs "+
	      "must <bind> again to a galdr, new or old, if they wish "+
	      "to enjoy a hearing at the time of their next meeting "+
	      "with Lars and Death. At Armageddon, the power of "+
	      "kraftords changes as Lars becomes bored with those words "+
	      "that he hears too often. "+
	      "Also see " +
	      lrgwhc("overview") + ", " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("death") + ", " +
	      lrgwhc("boon") + ", " +
	      lrgwhc("hearing") + ", " +
	      lrgwhg("power") + ", " +
	      lrgwhg("kraftord") + ", " +
	      lrgwhg("overview") + " and" +
	      lrgwh("bind") + ".\n";

    }

    outstr = "\n";

    if ( sizeof(arr) < 2 )
    {
        outstr += "\nAvailable " + upper_case(gHelpTagGel) + " Topics:\n";
        outstr += lrgwhc("overview") + "\n";
        mixed othrules = m_indices(gClubMap);
        othrules -= ({"overview"});
        othrules = sort_array(othrules);
	foreach ( string othrule : othrules )
            outstr += lrgwhc(othrule) + "\n";
    }
    else
    {
        inpstr = lower_case(arr[1]);
        if ( member_array(inpstr,m_indices(gClubMap)) != -1 )
        {
            if ( strlen(gClubMap[inpstr]) > 0 )
                outstr += "\n" + gClubMap[inpstr] + "\n";
        }
	else
	{
            // string not recognised
	    outstr += lrgwhc(inpstr) + " is not recognised.\n";
	}
    }

    return outstr;
}


string
galdr_rule( string str )
{
    string inpstr, outstr, lab;

    string *arr = explode(str," ");

    if ( !sizeof(arr) || arr[0] != gHelpTagGal )
        return ""; 

    if ( m_sizeof(gRuleMap) == 0 )
    { 
        lab = lrgwhg("overview");
        gRuleMap["overview"] = "\n" +
              lab + " : Larsgellirs " + lrgw("form") + " and " +
	      lrgw("bind") + " Larsgaldrar. At "+
	      "the time of death of a gellir, the <bind>ed "+
	      "galdr is yelled, borne on Larsreykr from their soul, "+
	      "into the 'hearing' of Lars.\n\n At Armageddon, "+
	      "Lars confers "+
	      "his favour on the gellir he has 'heard' with the "+
	      "who has gained the highest standing since the "+
	      "previous Armageddon. "+
	      "The 'standing' for each gellir is equal to the sum of "+
	      "the POWER x TIME for each galdr heard since last Armageddon. "+
	      "The power of each galdr is determined by the rareness of the "+
	      "rarest adjective ('kraftord') that the galdr contains. All "+
	      "adjectives and other words used to <form> galdrar must be "+
	      "found (ie. <muse>d) in room and "+
	      "room-item descriptions within the Realms. "+ 
	      "Also see " + 
	      lrgwhg("power") + ", " +
	      lrgwhg("kraftord") + ", " +
	      lrgwhg("checks") + ", " +
	      lrgwh("muse") + ", " +
	      lrgwh("form") + ", " +
	      lrgwh("bind") + ", " +
	      lrgwhg("overview") + ", " +
	      lrgwhc("hearing") + " and " +
	      lrgwhc("armageddon") + ".\n";

        lab = lrgwhg("checks");
        gRuleMap["checks"] = "\n" +
              lab + " : The inhabitants of the Askelund provide "+
	      "Larsgellirs with information on current and past galdrar. "+
	      capitalize(LGELLIR_NPC_NAME) + " provides "+
	      "guidance in creating a legal galdr -- she will check "+
	      "each newly <form>ed galdr and make sure it is fit to <bind>. "+
	      "She does this by messaging -- you do not need to be in "+
	      "the Askelund with her to do this. When by her side, however "+
	      "you can show her your possessions and she may muse upon "+
	      "the power of the kraftords in their descriptions. You yourself "+
	      "cannot <muse> upon objects, only rooms and room items. "+
	      "The Woodsman will tell you the last galdr he heard *you* "+
	      "yell as well as how many galdrar have been yelled by all "+
	      "since last Armageddon. This lets you check that your galdr "+
	      "has been heard from Extremis and gauge how many other gellirs "+
	      "have been yelling. The Two Ravens "+
	      "will tell you a random old galdr as well as the one "+
	      "galdr, heard in the last Armageddon "+
	      "cycle, which was the most powerful. "+
	      "By <muse>ing the same words contained in the powerful galdr, "+
	      "you can determine how your current galdr compares to "+
	      "the best before the most recent Armageddon. Be warned "+
	      "that the power of kraftords in old galdr is diminished "+
	      "by Lars having heard them recently. "+
	      "Also see " + 
	      lrgwh("form") + ", " +
	      lrgwh("bind") + ", " +
	      lrgwhc("rooms") + ", " +
	      lrgwhg("power") + ", " +
	      lrgwhg("overview") + " and " +
	      lrgwhc("hearing") + ".\n";

        lab = lrgwhg("length");
        gRuleMap["length"] = "\n" +
              lab + " : There can be no more than " + val2str(gMaxWords) +
              " words in the galdr. There can be no more than " +
	      val2str(gMaxRows) + " rows in the galdr. There can be no "+
	      "more than " + val2str(gNumColumns) + " columns in the galdr."+
	      "Also see " + lrgwhg("format") + " and " +
	      lrgwhg("words") + ".\n";

        lab = lrgwhg("format");
        gRuleMap["format"] = "\n" +
              lab + " : There can be no leading spaces on any row "+
              "of the galdr. The galdr can have any number of "+
	      "columns less than or equal to (<=) " + val2str(gNumColumns) +
	      ". All groups of letters of any case are interpreted as "+
	      "being a word. Non-letter characters other than the space "+
	      "character can be used to arrange the galdr so that "+
	      "the gellir's name is spelled out vertically downwards "+
	      "somewhere in the galdr. Not every word needs to be "+
	      "part of the spelled name. Not every line needs to "+
	      "contain words which are part of the spelled name. "+
	      "Also see " +
	      lrgwhg("naming") + ", " +
	      lrgwhg("words") + ", " +
	      lrgwhg("comment1") + ", " +
	      lrgwhg("length") + " and " + 
	      lrgwhg("comment2") + ".\n";

        lab = lrgwhg("naming");
        gRuleMap["naming"] = "\n" +
              lab + " : The name of the gellir must be spelled out "+
              "vertically downward by horizontal words of the galdr. "+
	      "The letters which spell out he name can be in any position "+
	      "within their words. "+
	      "character can be used to arrange the galdr so that "+
	      "the gellir's name is spelt out vertically downwards "+
	      "somewhere in the galdr. "+
	      "Also see " +
	      lrgwhg("format") + " and " +
	      lrgwhg("comment3") + ".\n";

        lab = lrgwhg("words");
        gRuleMap["words"] = "\n" +
              lab + " : Every word in the galdr must have been <muse>d. "+
	      "Other players' names can be <muse>d, "+
	      "but are excluded when <form>ing a galdr. Words can be "+
	      "repeated three or sometimes more times in a galdr. Race-words, "+
	      "number-words, common small words, "+
	      "and the name of the gellir do not require <muse>ing. " +
	      "All words from an existing bound galdr are automatically "+
	      "<muse>d when waking. "+
	      "At least one adjective ('kraftord') is required to "+
	      "be present in the galdr. "+
	      "Also see " +
	      lrgwhg("kraftord") + ", " +
	      lrgwhg("repetition") + ", " +
	      lrgwhg("comment4") + ", " +
	      lrgwhg("length") + ", " +
	      lrgwh("muse") + ", " +
	      lrgwh("form") + " and " +
	      lrgwh("bind") + ".\n";

        lab = lrgwhg("repetition");
        gRuleMap["repetition"] = "\n\n" +
              lab + " : Each word in the galdr can be repeated, if "+
              "needed, up to three or more times. Galdr with more "+
	      "words in total allow more repeated words." +
	      "Also see " +
	      lrgwhg("words") + ".\n";

        lab = lrgwhg("kraftord");
        gRuleMap["kraftord"] = "\n" +
              lab + " : Kraftords, or power-words, are adjectives "+
              "<muse>d from room and room-item descriptions like all "+
	      "other words. A galdr must contain at least one "+
	      "kraftord. The power of the galdr is determined "+
	      "by the rareness of the rarest kraftord that it contains. "+
	      "Kraftord power changes with the passage of Armageddon as "+
	      "Lars tires of hearing the same worrds too often. "+
	      "Also see " +
	      lrgwhg("overview") + ", " +
	      lrgwhc("armageddon") + ", " +
	      lrgwhg("power") + " and " +
	      lrgwhg("words") + ".\n";

        lab = lrgwhg("power");
        gRuleMap["power"] = "\n" +
              lab + " : The rareness of adjectives (kraftords) "+
              "in a galdr determine its power. "+
	      "Adjectives have a 'base' rareness value determined "+
	      "from standard english language word frequency. "+
	      "This 'base' rareness is modified by the usage of "+
	      "the word by Larsgellirs. The more an adjective is used in "+
	      "galdrar heard by Lars, the more its rareness (power) will "+
	      "decrease. "+
	      "The rareness of an adjective increases again slowly over "+
	      "time when it is not being used by any gellirs. When "+
	      "a galdr is <form>ed, the rareness of its rarest "+
	      "adjective is compared with the rarest adjective in "+
	      "that Larsgellir's existing <bind>ed galdr. If the newly "+
	      "<form>ed galdr is less powerful than their existing "+
	      "galdr, they should <form> another new galdr instead "+
	      "of <bind>ing it. That way, Larsgellirs can "+
	      "improve the power of the galdrar they <bind> for "+
	      "a hearing with Lars. "+
	      "Also see " +
	      lrgwhg("overview") + ", " +
	      lrgwh("form") + ", " +
	      lrgwh("bind") + ", " +
	      lrgwhg("checks") + ", " +
	      lrgwhc("hearing") + " and " +
	      lrgwhg("kraftord") + ".\n";

        lab = lrgwhg("comments");
        gRuleMap["comments"] = "\n" +
              lab + " Comments and examples illustrate aspects "+
	      "of Larsgaldr composition. Each comment (eg. " +
	      lrgwhg("comment1") + " ) has a corresponding example (eg. " +
	      lrgwhg("example1") + " ).\n";

        lab = lrgwhg("examples");
        gRuleMap["examples"] = "\n" +
              lab + " Comments and examples illustrate aspects "+
	      "of Larsgaldr composition. Each comment (eg. " +
	      lrgwhg("comment1") + " ) has a corresponding example (eg. " +
	      lrgwhg("example1") + " ).\n";

        lab = lrgwhg("comment1");
        gRuleMap["comment1"] = "\n" +
              lab + " Dots (.) and other\n"+
              "non-letter characters must be\n"+
              "used to space out the words so\n"+
              "that the your name is spelled\n"+
              "correctly along a vertical line."+
	      "\n(See " + lrgwhg("example1") + "\n";

        lab = lrgwhg("example1");
        gRuleMap["example1"] = "\n" +
              lab + " (name: vitwitchjr | kraftord: just)\n"+
              "#@!!#@!!#@!!#@!!@#!!@#\n"+
              "#@!!...revenge....!!@#\n"+
              "#@!!.....is.......!!@#\n"+
              "#@!!...often......!!@#\n"+
              "#@!!.....weighed..!!@#\n"+
              "#@!!.....in.......!!@#\n"+
              "#@!!.....the......!!@#\n"+
              "#@!!.....centre...!!@#\n"+
              "#@!!.of.the.heart.!!@#\n"+
              "#@!!..as.just.....!!@#\n"+
              "#@!!.....reward...!!@#\n"+
              "#@!!#@!!#@!!#@!!@#!!@#\n"+
	      "\n(See " + lrgwhg("comment1") + "\n";

        lab = lrgwhg("comment2");
        gRuleMap["comment2"] = "\n" +
              lab + " Non-letter characters can\n"+
              "be used as ascii-art in the galdr, which\n"+
              "can add to its style, but does not affect\n"+
              "its validity or scoring. Be careful NOT\n"+
              "to include letters in the ascii-art."+
	      "\n(See " + lrgwhg("example2") + "\n";

        lab = lrgwhg("example2");
        gRuleMap["example2"] = "\n" +
              lab + " (name: volvaskr | kraftords: relieved,mortal,"+
	      "familiar,cold)\n"+
              ".....................................\n"+
              ".......................(       ).....\n"+
              ".....................(      )    )...\n"+
              "....................(   (         )..\n"+
              "......................(          )...\n"+
              "........................'--\\ `\\--`...\n"+
              ".......Relieved.again......_\\ _\\.....\n"+
              "............of.............`\\ \\......\n"+
              ".......Mortal.form...........\\ \\.....\n"+
              ".........as.victim.over......_\\_\\....\n"+
              "......familiar.to.the.touch..`\\.....\n"+
              ".....of.the.Scythe.so.cold.....\\....\n"+
              ".......I.seek.Your.favour.and..`\\....\n"+
              "........power.on.my.Return.......\\|..\n"+
              "................................`\\|/'\n"+
              "----------------------------------*--\n"+
	      "\n(See " + lrgwhg("comment2") + "\n";

        lab = lrgwhg("comment3");
        gRuleMap["comment3"] = "\n" +
              lab + " Not every line needs to\n"+
              "have words which form part of your\n"+
              "name. Be careful that no additional\n"+
              "letters are placed immediately above\n"+
              "or below the vertical name."+
	      "\n(See " + lrgwhg("example3") + "\n";

        lab = lrgwhg("example3");
        gRuleMap["example3"] = "\n" +
              lab + " (name: finwe | kraftords: esteemed,first,high)\n"+
	      ".........................\n"+
              "...||,...................\n"+
              ".\\.`',/..................\n"+
              ".= ,. =...Esteemed.......\n"+
              "./.||.\\..................\n"+
              "...||.....First..........\n"+
              "...||....High.King.of....\n"+
              "...||.the.Noldor...then..\n"+
              "...||.....Wizard.in.this.\n"+
              "...||...Age.of.Men.......\n"+
              "...||....................\n"+
              "...||....................\n"+
	      ".........................\n"+
	      "\n(See " + lrgwhg("comment3") + "\n";

        lab = lrgwhg("comment4");
        gRuleMap["comment4"] = "\n" +
              lab + " Your own name can be used\n"+
              "up to three times in the plain text,\n"+
              "to fill in letters that may be a\n"+
              "bit harder to find in words."+
	      "\n(See " + lrgwhg("example4") + "\n";

        lab = lrgwhg("example4");
        gRuleMap["example4"] = "\n" +
              lab + " (name: vitwitjr | kraftords: obvious,hot)\n"+
              "..............................................\n"+
              ".....Not.obvious................^^^^....^^^^..\n"+
              "........is.it.that..............|  |....|  |..\n"+
              ".......creation.by.............^|   ^^^^   |^.\n"+
              "...Men.and.Women.of.Walls.....| |          | |\n"+
              ".of.Stone.will.still..........| |          | |\n"+
              ".....the.hot.goblin.passion.to.Rock.the.World;\n"+
              "..so.Vitwitjr.stands.to.for...................\n"+
              "......the.breaches.to.come....................\n"+
              "........  ====)-------------  ................\n"+
              "..............................................\n"+
	      "\n(See " + lrgwhg("comment4") + "\n";

        lab = lrgwhg("comment5");
        gRuleMap["comment5"] = "\n" +
              lab + " A galdr can be very simple but\n"+
              "still perfectly valid. It does not need\n"+
              "to form a sentence, or even make any\n"+
              "sense."+
	      "\n(See " + lrgwhg("example5") + "\n";

        lab = lrgwhg("example5");
        gRuleMap["example5"] = "\n" +
              lab + " (name: arman | kraftord: magic)\n"+
              ".all\n"+
              ".rabbits\n"+
              ".magic\n"+
              "tavern\n"+
              ".now\n"+
	      "\n(See " + lrgwhg("comment5") + "\n";

        lab = lrgwhg("comment6");
        gRuleMap["comment6"] = "\n" +
              lab + " You can't always <muse> the words\n"+
	      "you would like. Often a substitution is\n"+
	      "needed. In example6, the wanted word\n"+
              "'Keeper' could not be found so 'King'\n"+
	      "was used instead." +
	      "\n(See " + lrgwhg("example6") + "\n";

        lab = lrgwhg("example6");
        gRuleMap["example6"] = "\n" +
              lab + " (name: cherek | kraftords: constant,real)\n"+
              "~~~~~~~~~~~~~~~~~~~~~\n"+
              "......Constant.......\n"+
              "..is.the.............\n"+
              ".....tension.between.\n"+
              "lives.real...........\n"+
              ".and.realms.for.the..\n"+
              "......King...........\n"+
              "~~~~~~~~~~~~~~~~~~~~~\n"+
	      "\n(See " + lrgwhg("comment6") + "\n";
    }

    outstr = "\n";

    if ( sizeof(arr) < 2 )
    {
        outstr += "\nAvailable " + upper_case(gHelpTagGal) + " Topics:\n";
        outstr += lrgwhg("overview") + "\n";
        mixed othrules = m_indices(gRuleMap);
        othrules -= ({"overview"});
        othrules = sort_array(othrules);
	foreach ( string othrule : othrules )
            outstr += lrgwhg(othrule) + "\n";
    }
    else
    {
        inpstr = lower_case(arr[1]);

        if ( member_array(inpstr,m_indices(gRuleMap)) != -1 )
        {
            if ( strlen(gRuleMap[inpstr]) > 0 )
                outstr += "\n" + gRuleMap[inpstr] + "\n";
        }
	else
	{
            // string not recognised
	    outstr += lrgwhg(inpstr) + " is not recognised.\n";
	}
    }

    return outstr;
}


void
command_help( object plyr, string str )
{
    string outstr, substr, lab;

    if ( m_sizeof(gHelpMap) == 0 )
    { 
        lab = lrgw("help xx");
        gHelpMap["help"] = "\n\n" +
              lab + " provides information about the command or rule 'xx'. " +
	      "If 'xx' is blank, then all available commands are listed. "+
	      lrgwh(gHelpTagGel) + 
	      " gives rules for all Larsgellirs (club members) "+
              lrgwh(gHelpTagGal) +
	      " gives rules on format and usage of Larsgaldrar. "+
	      "\n";

        lab = lrgw("muse xx");
        gHelpMap["muse"] = "\n\n" +
              lab + " collects all words in a description for " +
              "use in composing a new galdr. 'xx' can be 'here' or the name " +
              "of an item in a room. Using this command takes a period of "+
	      "time similar to a normal <search>. To others, musing appears "+
	      "as normal searching. If 'xx' is left blank, then the list "+
              "of words <muse>d since waking is displayed. Words "+
	      "collected by <muse> do not remain between gellir log-ins. "+
	      "Some common words, and words contained in <bind>ed galdr "+
	      "do remain available between log-ins. Player names can be "+
	      "<muse>d, where they occur in room or room-item descriptions, "+
	      "but almost all are excluded when trying to <form> galdrar. "+
	      "You cannot <muse> "+
	      "words when in Extremis -- you will be too late. "+
              "See also " +
	      lrgwh("galdrar") + ", " +
	      lrgwhc("extremis") + ", " +
	      lrgwh("form") + ", " +
	      lrgwh("bind") + " and " +
	      lrgwh("yell") + ".\n";

        lab = lrgw("form");
        gHelpMap["form"] = "\n\n" +
              lab + " starts an editor to create a new galdr. All words " +
	      "used in the new galdr must already have been collected "+
	      "using the <muse> command or be contained within the "+
	      "existing <bind>ed galdr. Player names that have been " +
	      "<muse>d will be excluded from the galdr at this point. "+
	      capitalize(LGELLIR_NPC_NAME) +
	      " assists gellirs in ensuring that new galdrar are are fit " +
	      "to <bind> and will be acceptable in the hearing of Lars. "+
	      "She will also compare the power of the new galdr with "+
	      "the power of the gellir's <bind>ed galdr, if one exists. "+
	      "If the new galdr is less powerful than the <bind>ed one, "+
	      "it is probably not worth <bind>ing. The gellir should "+
	      "instead seek to <form> a more powerful galdr and <bind> "+
	      "that one instead. You cannot <form> new galdrar "+
	      "when in Extremis -- you will be too late. "+
              "See also " +
	      lrgwh("galdrar") + ", " +
	      lrgwhc("extremis") + ", " +
	      lrgwhg("words") + ", " +
	      lrgwh("muse") + ", " +
	      lrgwh("bind") + " and " +
	      lrgwh("yell") + ".\n";

        lab = lrgw("bind");
        gHelpMap["bind"] = "\n\n" +
              lab + " causes a newly <form>ed galdr to bind with a gellir's " +
              "essence. This will replace any galdr already bound "+
	      "in place. Only the bound galdr can be borne to the hearing of "+
	      "Lars from Extremis when you <yell>. You cannot <bind> a galdr "+
	      "when in Extremis -- you will be too late. All words contained in "+
	      "the bound galdr are available to <form> a new galdr without "+
	      "having to be <muse>d again. " +
              "See also " +
	      lrgwh("galdrar") + ", " +
	      lrgwhc("extremis") + ", " +
	      lrgwh("muse") + ", " +
	      lrgwh("form") + " and " +
	      lrgwh("yell") + ".\n";

        lab = lrgw("yell");
        gHelpMap["yell"] = "\n\n" +
              lab + " causes the galdr <bind>ed to the gellir's "+
	      "essence to be borne from Extremis into the hearing of Lars. "+
              "Sometimes, on arriving in Extremis, you will be reminded to "+
	      "<yell>. Other times you will have to remember for "+
	      "yourself. Trying to <yell> in the mortal realms " +
	      "only serves to hear for yourself the bound galdr. "+
              "See also " +
	      lrgwh("gellirs") + ", " +
	      lrgwhc("extremis") + ", " +
	      lrgwhc("lars") + ", " +
	      lrgwhc("hearing") + ", " +
	      lrgwh("muse") + ", " +
	      lrgwh("form") + " and " +
	      lrgwh("bind") + ".\n";

    }

    outstr = "\n\nLARSGELLIR Help";

    mixed cmds = m_indices(gHelpMap);

    if ( !strlen(str) )
    {
        outstr += "\n" + gHelpMap["help"] + "\nCommand help:\n";
	foreach ( string cmd : cmds )
            outstr += "\n" + lrgwh(cmd);
        outstr += "\n";
    }
    else
    {
        str = lower_case(str);

        // first see if subsidiary help
	// functions are relevant

        substr = "";
        substr += galdr_rule( str );
        substr += gellir_rule( str );

	if ( !strlen(substr) ) 
        {
            // process here in primary help

            if ( member_array(str,cmds) != -1 )
            {
                if ( strlen(gHelpMap[str]) > 0 )
                    outstr += "\n" + gHelpMap[str] + "\n";
            }
	    else
	    {
                // string not recognised
	        outstr += "\n" + lrgwh(str) + " is not recognised.\n\n";
	    }
        }
	else
	    outstr += substr + "\n";
    }

    plyr->catch_msg(outstr);

    return;
}


int
larsreykr_action( string str )
{
    string args;  
    object plyr = this_player();

    if ( !strlen(str) )
        plyr->catch_msg("\nThe Gellirs of Lars use two word commands, "+
	             "eg. " + lrgw("'xx'") + ", where 'xx' is the "+
                     "name of a desired action. See "+
                     lrgw("help") + ".\n");
    else
    {
        string *wd = explode(lower_case(str)," ");
        int n = sizeof(wd) - 1;
        args = implode(wd[1..n]," ");  

        switch (wd[0])
        {
        case "help":
            command_help( plyr, args );
            break; 
        case "muse":
            muse_words( plyr, args );
            break; 
        case "form":
            form_phrase();
            break; 
        case "bind":
            bind_galdr( plyr );
            break; 
        case "yell":
            yell_galdr( plyr );
            break; 
        default:
            plyr->catch_msg( lrgw(wd[0] + " etc.") +
	       " not recognised. For help, see " + lrgw("help") + ".\n");
            break; 
        }
    }

    return 1;
}


void
init()
{
    ::init();
    add_action( larsreykr_action, LARSREYKR_ACTION_WORD );
}


void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    mixed oblist;

    if (dest)
    {
        oblist = FIND_STR_IN_OBJECT("all " + LGELLIR_OBJ_ID + "s", dest);
        oblist -= ({ 0, this_object() });
        if( oblist && sizeof(oblist) > 0 )
            set_alarm( 2.0, 0.0, &remove_object() );
    }

    if ( !interactive(dest) || old )
        return;

    if ( LGELLIR_IS_DAEMON() == 1 && IS_A_LARSGELLIR( dest ) < 1 )
    {
        set_alarm( 0.1, 0.0, &remove_object()) ;
        return;
    }

    setuid();
    seteuid(getuid());

    if ( is_death_chamber( environment(dest) ) )
    {
        /*
	  When in the death chamber (aka Extremis), the player is
	  either a ghost_player.c or not but with set_ghost(GP_DEAD).
	  The latter case is meant to be the normal condition (?).
	  In this case, the player's auto-loading inventory
	  returns to them including this object ... so 
	  the call below is a reminder to try and <lg yell> here
	
          (The ghost_player.c case does not cause this object to 
           enter_env and so it is up to the player to remember to
           actively <lg yell> at the time of being in Extremis.
	*/

        dest->catch_msg("\n\n\nHere in Extremis, you remember "+
	                  "you should " + lrgw("yell") +
			  " for Lars\n                      "+
			 "            ... before you choose "+
			  "between the portal and the light.\n\n\n");
    }
    else
    {
        dest->catch_msg("\nLarsreykr swirls in and about "+
                    "your essence.\n\n");
        set_alarm( 3.0, 0.0, &init_words_maps(dest) );
        set_alarm( 6.0, 0.0, &sing_galdr(dest,0) );
    }

    return;
}


/* END OF FILE =============== */
