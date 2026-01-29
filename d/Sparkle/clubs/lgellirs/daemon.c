/* ========================================================================== */

/* 
 *  Daemon for The Gellirs of Lars
 *
 *  Vitwitch 2022
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

inherit "/std/object";

#include <std.h>
#include "defs.h"
#include "/d/Sparkle/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <math.h>
#include <mail.h>
#include <time.h>
#include <state_desc.h>
#include <formulas.h>
#include <language.h>

/* DEFINITIONS ============================================================== */

// (for reference: seconds in an Arma period = 1209600) 
#define FREQ_TIME_DIVISOR 20
#define RELAX_RATE_DIVISOR 3

#define THRESHOLD_SCORE_UNITBOON 100000
#define BOON_DECAY_RATE_PCT 5

/* DAEMONmap index strings and data definitions
"DLASTTM"  :  time() string from last reset
"DLASTMF"  :  string number of galdrar added last reset
"DGELLRS"  :  spaced string of scoring gellirs at last reset
"DSCORES"  :  spaced string of scoring gellir scores at last reset 
"DSCOXPL"  :  spaced string of scoring gellir exp pt losses at last reset 
"DMXPOWR"  :  string of int maximum galdr power at last reset
"DPOWGAL"  :  string index of maxmium powered galdr at last reset
"DWINNER"  :  string winning gellir's name at last reset
"DWINSCR"  :  string winning gellir's score at last reset
"DWINGAL"  :  spaced string of indices of all winner's galdrar at last reset
"DWINBON"  :  string of winners experience point boon won at last reset
"DSUSPND"  :  string indicating time when map processing was suspended...(unusual)
*/

/* GELLIRMap index strings and data definitions
"GACTIVE"  : int 0 or 1 is an active member
"GXPLOSS"  : int total experience lost
"GNUMDTH"  : int number of hearings before Lars
"GNUMWIN"  : int number of wins at daemon resets
"GLRBOON"  : int balance of boon experience points 
"GLASTTM"  : int time index of last activity
"GBANNED"  : int 0 or 1 is banned from club
*/

/* pGALDRmap index strings and data defintitions
"MDEFINED" : string 0 or 1 galdr is defined (ie. bound)
"MFULLTXT" : string full text of galdr
"MLSTKRAF" : string spaced list of kraftords
"MLSTNTKR" : string spaced list of non-kraft words
"MHEARDTM" : string time() when galdr was heard by Lars
"MHEARDXL" : string experience point loss at hearing
"MARTVOTE" : string number of artistry votes by Wizards
*/

/* GLOBAL VARIABLES ==================================================== */

static int gProcessEnabled = 1;
static int gQuestEnabled = LGELLIR_QUEST_DEFAULT_ACTIVE;
static int g; 

static mapping GLOBWDmap = ([]);
static mapping WDTIMEmap = ([]);
static mapping DAEMONmap = ([]);
static mapping EXCPTNmap = ([]);

static int gNumEtherMsg;
static string *gEtherMsg = ({});
static mapping gDomainWords = ([]);


/* PROTOTYPES =========================================================== */

void reset_object();
void create_object();
int is_lgellir_daemon();
int process_is_enabled();
int quest_is_enabled();

public int club_admin_level( object player );
public int query_quest();
public int enable_quest();
public int disable_quest();
public int introduce_kraftord( string word, string reference_word );
public int suspend_kraftord( string kraftord );
public int except_player_names( string words );
public void show_excepted_names();
public int query_process();
public int process_suspension();
public int process_resumption();
string format_daemon_log( string filedescr, mapping daemonmap );
public void show_daemon_log();
public void more_daemon_logs();
string format_galdr_report( string filedescr, mapping gmap );
public void more_galdrar( string gname );
public int vote_for_galdr_merit( string filedescr );
string format_gellir_report( string filedescr, mapping gmap );
public void more_gellirs();
public void ban_gellir( string gname );
public void unban_gellir( string gname );

void get_globwdmap();
void put_globwdmap();
void get_wdtimemap();
void put_wdtimemap();
void get_excnamemap();
void put_excnamemap();
int get_daemonmap( int index );
int put_daemonmap( int index );
int import_write_globalwd_map( string inpfilepath );

mapping fnget_map( string fileORname );
void fnput_map( mapping mpg, string fileORname );
string *explode_strip_string( string str );
int is_valid_tester( object plyr );
int access_granted( object plyr );

int word_frequency( string word );
int kraftord_power( string word );
int galdr_power( string words );
int is_a_kraftord( string word );
int is_a_heard_galdr( string filename );
int is_gellirs_heard_galdr( string filename, string gname );
int is_an_ether_word( string word );
int is_an_excepted_name( string word );

void set_larsether_messages();
string get_larsether_message( int index );

void notify_gellir_of_outcome( string name, int iwinplace, int winttlxp );
void notify_gellir_of_stop_start( string name, string wizname, int stopstart );
void notify_gellir_of_ban_unban( string gname, string wizname, int bantime );

int gellir_ether_access( object plyr );
string *current_winners_galdrar();
void update_gellir_deaths( string gname );
string last_highpower_galdr( object gellir );
string *last_cycle_galdrar();
string *ordered_voted_galdrar();
string gellir_last_galdr( object plyr );
void set_boon_increment( object plyr );
void log_boon_completion( object plyr );
int is_a_larsgellir( object plyr );
string gellir_petname( string gname );
string gellir_boon_descrip( int boon );
string gellir_description( string gname );
int inspire_gellir( object plyr );
int expire_gellir( object plyr );

void init_first_maps();
void process_maps_after_reset();

/* FUNCTIONS ============================================================== */


void reset_object()
{
    process_maps_after_reset();

    get_excnamemap();

    set_alarm( 1.0, 3600.0, set_larsether_messages );

    return;
}


void
create_object()
{
    set_name( "lgellirdaemon" );

    set_short("Daemon of the Gellirs of Lars");
    set_long("This is the Daemon of the Gellirs of Lars.\n");

    setuid();
    seteuid(getuid());

    gNumEtherMsg = 1 + LARSETHER_MAXNUMIDX;
    gEtherMsg = allocate( gNumEtherMsg );

    reset_object();

    return;
}


int
is_lgellir_daemon()
{
    return 1;
}


int
quest_is_enabled()
{
   return gQuestEnabled;
}


int
process_is_enabled()
{
   return gProcessEnabled;
}


// WIZARD-ONLY FUNCTIONS ---------------------------------------------------


int
club_admin_level( object plyr )
{
    if ( !plyr->query_wiz_level() ) return 0;
    return (2 + member_array(plyr->query_real_name(),LGELLIR_WIZ_DEFAULT_ADMIN));
}


public int
query_quest()
{
   if ( !club_admin_level(this_player()) )
   {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
   }
   if ( !gQuestEnabled )
       write("The quest (" + LGELLIR_QUEST_NAME + ") is disabled.\n");
   else
       write("The quest (" + LGELLIR_QUEST_NAME + ") is enabled.\n");
   return 1;
}


public int
enable_quest()
{
   if ( club_admin_level(this_player()) < 2 )
   {
        write("You do not have sufficient club-admininstration permissions.\n");
        return 0;
   }
   gQuestEnabled = 1;
   query_quest();
   return 1;
}


public int
disable_quest()
{
   if ( club_admin_level(this_player()) < 2 )
   {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
   }
   gQuestEnabled = 0;
   query_quest();
   return 1;
}


public int
introduce_kraftord( string word, string reference_word )
{
    object p = this_player();

    if ( club_admin_level(p) < 2 )
    {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
    }

    string kraftord = lower_case(word);
    string refrword = lower_case(reference_word);

    if ( !GLOBWDmap[kraftord] )
    {
        if ( !GLOBWDmap[refrword] )
            refrword = LGELLIR_DEFAULT_RARITY_WORD;

        GLOBWDmap[kraftord] = GLOBWDmap[refrword];
        write("The kraftord (" + kraftord + ") has been introduced " +
	        "with same power as (" + refrword + ").\n");
        write_file( LGELLIRLOGS + "kraftords", ctime(time()) + " " 
                    + p->query_real_name() + " has added the word " 
                    + upper_case(word) + " as a kraftord with the "
		    + "same power as " + upper_case(refrword) + ".\n");
        put_globwdmap();
    }
    else
        write("The kraftord (" + kraftord + ") already exists.\n");

    return 1;
}


public int
suspend_kraftord( string word )
{
    object p = this_player();

    if ( club_admin_level(p) < 2 )
    {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
    }

    string kraftord = lower_case(word);

    if ( !GLOBWDmap[kraftord] )
        write("The kraftord (" + kraftord + ") does not exist.\n");
    else
    {
        write("The kraftord (" + kraftord + ") has been suspended " +
	        "from use.\n");
        write_file( LGELLIRLOGS + "kraftords", ctime(time()) + " " 
                    + p->query_real_name() + " has suspended the word " 
                    + upper_case(word) + " as a kraftord. " + 
                    val2str(GLOBWDmap[kraftord]) + "\n");
        GLOBWDmap = m_delete(GLOBWDmap,kraftord);
        put_globwdmap();
    }

    return 1;
}


public int
except_player_names( string words )
{
    object p = this_player();

    if ( club_admin_level(p) < 2 )
    {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
    }

    string wzname = p->query_real_name();

    foreach ( string word : explode(words," ") ) 
    {
        string nameword = lower_case(word);

        if ( !SECURITY->exist_player(nameword) )
            write("The word " + nameword + " is not a player name.\n");
        else if ( !is_an_excepted_name(nameword) )
	{
            int itime = time();

            write_file( LGELLIRLOGS + "player_names", ctime(itime) + " " 
                + wzname + " excepted " 
                + upper_case(word) + " from name-protection.\n");

            EXCPTNmap[nameword] = itime;
        }

    }

    put_excnamemap();

    return 1;
}


public void
show_excepted_names()
{
    object p = this_player();

    if ( club_admin_level(p) < 2 )
    {
        write("You do not have sufficient club-administration permissions.\n");
        return;
    }

    if (!m_sizeof(EXCPTNmap)) 
    {
       write("No excepted names found.\n");
       return;
    }

    string outstr = " ";
    foreach ( string xindx : sort_array(m_indices(EXCPTNmap)) )
        outstr += sprintf("%s ",xindx);

    write("Player-names excepted from general ban on names in galdrar:\n" +
            outstr + "\n");

    return;
}


public int
query_process()
{
   if ( !club_admin_level(this_player()) )
   {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
   }
   if ( !gProcessEnabled )
       write("Map processing is DISABLED.\n");
   else
       write("Map processing is ENABLED.\n");
   return 1;
}


public int
process_suspension()
{
    int ixploss;
    object p = this_player();
    string wizname = p->query_real_name();
    string tobjname = this_object()->query_name();

    if ( club_admin_level(p) < 2 )
    {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
    }

    write_file( LGELLIRLOGS + "stop_start", ctime(time()) + " " 
              + wizname + " executed a controlled SUSPENSION " 
              + "of map processing in the " + tobjname + ".\n");

    write("Map processing in " + tobjname + " is halting:\n");

    foreach ( string gfile : get_dir(LGELLIRGELLIRS) )
    { 
        mapping GELLIRmap = fnget_map( gfile );
	if ( GELLIRmap["GACTIVE"] > 0 ) 
            notify_gellir_of_stop_start( gfile, wizname, 0 );
    }

    write("...active Gellirs notified\n");

    get_daemonmap( 0 );  // recall most current map
    DAEMONmap["DSUSPND"] = val2str(time());
    put_daemonmap( 0 );

    gProcessEnabled = 0;

    write("...map processing has been suspended\n\n");

    return 1;
}


public int
process_resumption()
{
    int ixploss;
    object p = this_player();
    string wizname = p->query_real_name();
    string tobjname = this_object()->query_name();

    if ( club_admin_level(p) < 2 )
    {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
    }

    get_daemonmap( 0 );  // recall most current map
    if ( DAEMONmap["DSUSPND"] == "0" ) return 0;

    write_file( LGELLIRLOGS + "stop_start", ctime(time()) + " " 
              + wizname + " executed a controlled RESUMPTION " 
              + "of map processing in the " + tobjname + ".\n");

    write("Map processing in " + tobjname + " is resuming again:\n");

    foreach ( string gfile : get_dir(LGELLIRGELLIRS) )
    { 
        mapping GELLIRmap = fnget_map( gfile );
	if ( GELLIRmap["GACTIVE"] > 0 ) 
            notify_gellir_of_stop_start( gfile, wizname, 1 );
    }

    write("...active Gellirs notified\n");

    DAEMONmap["DSUSPND"] = "0";
    put_daemonmap( 0 );

    gProcessEnabled = 1;

    write("...map processing has been resumed\n\n");

    return 1;
}


string
format_daemon_log( string filedescr, mapping dmap )
{
    int i, n, m;

    string outstr = sprintf("\n%s ==========================\n",filedescr);

    outstr += sprintf("Started: %s (timestamp: %s)\n", 
                 ctime(atoi(dmap["DLASTTM"])), dmap["DLASTTM"]);

    if ( !strlen(dmap["DGELLRS"]) )
    {
        outstr += "NO Gellirs SCORED at this time.\n";
        return outstr + "\n";
    }

    string *snames = explode( dmap["DGELLRS"], " ");
    string *scores = explode( dmap["DSCORES"], " ");
    string *sxplos = explode( dmap["DSCOXPL"], " ");

    n = sizeof(snames);
    if ( n > 0 ) 
    {
        outstr += sprintf("Scoring Gellirs----------\n"); 

        for ( i=0;i<n;i++ )
            outstr += sprintf("Name:%s Score:%s XPLoss:%s\n", 
                snames[i], scores[i], sxplos[i] );

        outstr += sprintf("\nWinning Gellir-----------\n"); 

        outstr += sprintf("Name: %s\n",dmap["DWINNER"]); 
        outstr += sprintf("Boon: %s\n",dmap["DWINBON"]); 
        outstr += sprintf("Galdrar: %s\n",dmap["DWINGAL"]); 

        outstr += sprintf("\nGaldrar Data-----------\n"); 

        outstr += sprintf("Maximum Powered Galdr: %s\n",dmap["DPOWGAL"]); 
        outstr += sprintf("Maximum Galdr Power: %s\n",dmap["DMXPOWR"]); 
        outstr += sprintf("New Total Num. of Galdrar: %s\n", dmap["DLASTMF"]);
    }
    else
    {
        outstr += sprintf("\nGaldrar Data-----------\n"); 
        outstr += sprintf("Total Num. of Galdrar: %s\n", dmap["DLASTMF"]);
    }

    return outstr + "\n";
}


public void
show_daemon_log()
{
    object p = this_player();

    if (!p->query_wiz_level() )
    {
         write("You do not have sufficient club-administration permissions.\n");
         return;
    }

    p->more( format_daemon_log( "CURRENT", DAEMONmap ) );

    return;
}


public void
more_daemon_logs()
{
    object p = this_player();

    if (!p->query_wiz_level() )
    {
         write("You do not have sufficient club-administration permissions.\n");
         return;
    }

    int n, i;
    string outstr = ""; 
    string *files = sort_array(get_dir(LGELLIRDAEMOND));

    n = sizeof( files );
    for ( i=n-1;i>-1;i-- ) 
    {
        mapping daemonmap = fnget_map( LGELLIRDAEMOND + files[i] );
        outstr += format_daemon_log( files[i], daemonmap );
    }

    p->more( outstr + "\n" );

    return;
}


string
format_galdr_report( string filedescr, mapping gmap )
{
    int i, n, m;

    string outstr = sprintf( 
       "\n===========================================\n%s\n\n",filedescr);

    outstr += gmap["MFULLTXT"]; 
    outstr += sprintf("\n\nKraftords:(%s )",gmap["MLSTKRAF"]); 
    outstr += sprintf("\nExperience Loss at Hearing: %s",gmap["MHEARDXL"]); 
    outstr += sprintf("\nNumber of Artistic Merit Votes: %s",gmap["MARTVOTE"]); 

    return sprintf("%s\n===========================================\n",outstr);
}


public void
more_galdrar( string gname )
{
    mapping galdrmap = ([]);
    object p = this_player();

    if ( !club_admin_level(p) )
    {
         write("You do not have sufficient club-administration permissions.\n");
         return;
    }

    string *files;

    if ( !gname || !strlen(gname) ) 
        files = sort_array( get_dir(LGELLIRGALDRAR) );
    else
        files = sort_array( 
	   filter( get_dir(LGELLIRGALDRAR), &wildmatch("*_" + gname,) ) );

    int i;
    string outstr = "";
    int n = sizeof(files);
    for ( i=n-1;i>-1;i-- ) 
    {
        galdrmap = fnget_map( LGELLIRGALDRAR + files[i] );
        outstr += format_galdr_report( files[i], galdrmap );
    }

    p->more( outstr );

    return;
}


public int
vote_for_galdr_merit( string filedescr )
{
   object p = this_player();

   if ( !club_admin_level(p) )
   {
        write("You do not have sufficient club-administration permissions.\n");
        return 0;
   }

   string fd = lower_case(filedescr);

   if ( !fd || !strlen(fd) )
   {
        write("No galdr file index has been provided.\n");
        return 0;
   }

   mapping galdrmap = fnget_map( LGELLIRGALDRAR + fd );

   if ( !galdrmap )
   {
        write("No valid galdr file has been found for the index " + fd + ".\n");
        return 0;
   }

   galdrmap["MARTVOTE"] = val2str(atoi(galdrmap["MARTVOTE"]) + 1);

   fnput_map( galdrmap, LGELLIRGALDRAR + fd );

   return 1;
}


string
format_gellir_report( string filedescr, mapping gmap )
{
    string gname;
    int n = sscanf(filedescr,"%s.o",gname);
    if ( !n ) gname = filedescr;

    return sprintf(
   "\n%s\nactive=%d banned=%d nheard=%3d nwins=%2d boonpts=%6d lastt=%s (%d)\n\n",
       capitalize(gname),gmap["GACTIVE"],gmap["GBANNED"],gmap["GNUMDTH"],
       gmap["GNUMWIN"],gmap["GLRBOON"],ctime(gmap["GLASTTM"]),gmap["GLASTTM"]);
}


public void
more_gellirs()
{
    object p = this_player();

    if (!p->query_wiz_level() )
    {
         write("You do not have sufficient club-administration permissions.\n");
         return;
    }

    string outstr = "GELLIR LISTING ==========================="+
                  "=======================================================";

    foreach ( string file : sort_array(get_dir(LGELLIRGELLIRS)) )
    {
        mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + file );
        outstr += format_gellir_report( file, GELLIRmap );
    }

    outstr += "============================================"+
              "=====================================================\n";

    p->more( outstr );

    return;
}


public void
ban_gellir( string pn )
{
    // gellir will be is rendered inactive
    // and will not be able to re-activate
    // they will however be counted in the
    // scoring at next Arma if they have
    // had a galdr heard... but if they
    // win, their inactive/banned status
    // will prevent collecting any boon

    object p = this_player();

    if ( club_admin_level(p) < 2 )
    {
         write("You do not have sufficient club-administration permissions.\n");
         return;
    }

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pn );

    if ( !m_sizeof(GELLIRmap) ) return;
    if ( GELLIRmap["GBANNED"] > 0 ) return;
        
    int itimenow = time();

    GELLIRmap["GBANNED"] = itimenow; 
    GELLIRmap["GACTIVE"] = 0;

    fnput_map( GELLIRmap, LGELLIRGELLIRS + pn );

    string wizname = p->query_real_name();

    write_file( LGELLIRLOGS + "ban_unban", ctime(itimenow) + " (" 
              + val2str(itimenow) + ") " + wizname + 
	      " BANNED " + pn + " from the Gellirs of Lars.\n");

    notify_gellir_of_ban_unban( pn, capitalize(wizname), itimenow );

    return;
}


public void
unban_gellir( string pn )
{
    // gellir will be is able to become active
    // again by rejoining... any boons owing
    // to them will be redeemable

    object p = this_player();

    if ( club_admin_level(p) < 2 )
    {
         write("You do not have sufficient club-administration permissions.\n");
         return;
    }

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pn );

    if ( !m_sizeof(GELLIRmap) ) return;
    if ( !GELLIRmap["GBANNED"] ) return;
        
    int itimenow = time();

    GELLIRmap["GBANNED"] = 0; 

    fnput_map( GELLIRmap, LGELLIRGELLIRS + pn );

    string wizname = p->query_real_name();

    write_file( LGELLIRLOGS + "ban_unban", ctime(itimenow) + " (" 
              + val2str(itimenow) + ") " + wizname + 
	      " UNBANNED " + pn + " from the Gellirs of Lars.\n");

    notify_gellir_of_ban_unban( pn, capitalize(wizname), 0 );

    return;
}


// MAP FUNCTIONS ------------------------------------------------------------
 
void
get_globwdmap()
{
   string inpfilepath = LGELLIRWORDREF + "globadjmap";

   GLOBWDmap = fnget_map( inpfilepath );

   if ( !m_sizeof(GLOBWDmap) )
       write("Zero-size GLOBWDmap in " + inpfilepath + "\n");
   else
       write("Loaded GLOBWDmap from " + inpfilepath + "\n");

   return;
}


void
put_globwdmap()
{
   setuid();
   seteuid(getuid()); 
   fnput_map( GLOBWDmap, LGELLIRWORDREF + "globadjmap" );
   return;
}


void
get_wdtimemap()
{
   string inpfilepath = LGELLIRWORDREF + "adjtimemap";

   WDTIMEmap = fnget_map( inpfilepath );

   if (!m_sizeof(WDTIMEmap)) 
       write("Zero-size WDTIMEmap in " + inpfilepath + "\n");
   else
       write("Loaded WDTIMEmap from " + inpfilepath + "\n");

   return;
}


void
put_wdtimemap()
{
   fnput_map( WDTIMEmap, LGELLIRWORDREF + "adjtimemap" );
   return;
}


void
get_excnamemap()
{
   string inpfilepath = LGELLIRWORDREF + "excnamemap";

   EXCPTNmap = fnget_map( inpfilepath );

   if (!m_sizeof(EXCPTNmap)) 
       write("Zero-size EXCPTNmap in " + inpfilepath + "\n");
   else
       write("Loaded EXCPTNmap from " + inpfilepath + "\n");

   return;
}


void
put_excnamemap()
{
   fnput_map( EXCPTNmap, LGELLIRWORDREF + "excnamemap" );
   return;
}


int
fq( int v )
{
    int i;
    int n = ( v / g ) % g;
    for (i=-1;i<n;i++) v = v / g; 
    return v;
}


int
get_daemonmap( int index )
{
   // if index == 0 then find highest timestamp in dir and use that
   // else index must correspond to a timestamp in a file name

   int n;
   string mfile, inpfilepath;
   string *files = sort_array(get_dir(LGELLIRDAEMOND));

   n = sizeof(files);

   if ( !n ) 
       return 0;

   if ( !index )
       mfile = files[n-1];
   else
   {
       n = member_array(sprintf("daemonmap_%d",index),files);
       if ( n == -1 )
           return 0;
       mfile = files[n];
   }

   inpfilepath = LGELLIRDAEMOND + mfile;
   DAEMONmap = fnget_map( inpfilepath );

   if ( !m_sizeof(DAEMONmap) )
       write("Zero-size DAEMONmap in " + inpfilepath + "\n");
   else
       write("Loaded DAEMONmap from " + inpfilepath + "\n");

   return 1;
}


int
put_daemonmap( int index )
{
   string mfile, outfilepath;

   if ( !index )
       mfile = sprintf("daemonmap_%s",DAEMONmap["DLASTTM"]);
   else
       mfile = sprintf("daemonmap_%d",index);

   outfilepath = LGELLIRDAEMOND + mfile;
   fnput_map( DAEMONmap, outfilepath );
   write("Saving DAEMONmap to " + outfilepath + "\n");

   return 1;
}


int
import_write_globalwd_map( string inpfilepath )
{
    string inp, word;
    int n, freq, success, linepos, nwds;
    mapping importGLOBWDmap = ([]);

    if (!this_player()->query_wiz_level() )
    {
        write("You do not have wizard-level permissions.\n");
        return 0;
    }

    nwds = 0;
    linepos = 0;
    success = 1;

    while ( success )
    {
        inp = read_file( inpfilepath, linepos, 1 );
        success = stringp(inp);
        if ( success )
        {
            n = sscanf( inp, "%s %d", word, freq );
            if ( n < 2 ) success = 0;
            if ( freq < 1 ) success = 0;
        }
        if ( success )
	{
	    importGLOBWDmap[lower_case(word)] = freq;
	    nwds++;
        }
        linepos++;
    }

    if ( !nwds )
    {
        write("No words were imported from " + inpfilepath + ".\n");
        return 0;
    }
    else
    {
	string outfile = LGELLIRWORDREF + sprintf("globadjmap_%d",time());
        fnput_map( importGLOBWDmap, outfile );
        write(val2str(nwds) + " words were imported from " + inpfilepath +
	      " and written to " + outfile + ".\n");
    }

    return nwds;
}


// UTILITY FUNCTIONS ----------------------------------------------------


mapping
fnget_map( string fileORname )
{
    string mapname;
    int n = sscanf(fileORname,"%s.o",mapname);
    if ( !n ) mapname = fileORname;

    setuid();
    seteuid(getuid()); 

    return restore_map( mapname );
}


void
fnput_map( mapping mpg, string fileORname )
{
    string outname;
    int n = sscanf(fileORname,"%s.o",outname);
    if ( !n ) outname = fileORname;

    save_map( mpg, outname );

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
is_valid_tester( object plyr )
{
    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) return 0;

    string pname = plyr->query_real_name();
    if ( !SECURITY->exist_player(pname) ) return 0;

    // check that player is a second of a wizard or a listed beta tester

    foreach( string sname : SECURITY->query_player_seconds(pname) )
        if ( member_array(sname,SECURITY->query_wiz_list(-1)) != -1 ) return 1;

    if ( member_array(pname,LGELLIR_MORTAL_BETAS) != -1 ) return 1;

    return 0;
}


int
access_granted( object plyr )
{
    if ( !LGELLIR_BETA_TEST_01 ) return 1;
    return is_valid_tester( plyr );
}


// WORD FREQUENCY FUNCTIONS ----------------------------------------------


int
word_frequency( string word )
{
    string lw = lower_case(word);

    if ( wildmatch("*-*",lw) ) return 0;
    if ( !GLOBWDmap[lw] ) return 0;
    int freq = fq(GLOBWDmap[lw]);

    if ( !WDTIMEmap[lw] ) return freq;
    return freq + WDTIMEmap[lw] / FREQ_TIME_DIVISOR;
}


int
kraftord_power( string word )
{
    int freq = word_frequency(word);

    if ( !freq ) return 0;

    float rlogf = 6.845 - 0.4343 * log(itof(freq));

    int power = max( 1, ftoi(rlogf * rlogf) );

    return power;
}


int
galdr_power( string words )
{
    int wdpw = -1;

    foreach ( string word : explode_strip_string(words) )
        wdpw = max( wdpw, kraftord_power(word) );

    return wdpw;
}


int
is_a_kraftord( string word )
{
    if ( !GLOBWDmap[word] ) return 0;
    return 1;
}


int
is_a_heard_galdr( string filename )
{
    string gname;
    int n = sscanf(filename, "0_%s.o", gname); 
    return 1-n;
}


int
is_gellirs_heard_galdr( string filename, string gname )
{
    int itime;
    string fname;
    int n = sscanf(filename, "%d_%s.o", itime, fname); 
    if ( itime > 0 && fname == gname ) return 1; 
    return 0;
}


int
is_an_ether_word( string word )
{
    if ( LANG_IS_OFFENSIVE(word) ) 
        return 0;

    if ( SECURITY->exist_player(word) )
        return 0;

    return 1;
}


int
is_an_excepted_name( string word )
{
    if ( m_sizeof(EXCPTNmap) ) return 0;

    if ( EXCPTNmap[word] > 0 )
        return 1;

    return 0;
}


// LARSETHER SUPPORT FUNCTIONS ------------------------------------------


void
set_larsether_messages()
{
    // Search for folk on the surface 
    // of the Donut... scan their 
    // environment for adjectives
    // to populate lists for each
    // domain; to be viewed during
    // the journey through the
    // Larsether

    int idom, ik, nk, nkl, imsg, isindx;
    string idstr, locname, domainname;
    string valstr;
    string *kraftords;
    string *dwds;
    object envwf;

    object *wokefolk = users();

    foreach ( object wf : wokefolk )
    {
        envwf = environment(wf);

        if ( !objectp(envwf) )
            continue;

        // if there is anyone in the ether already,
	// do not (re)set the messaging... set
	// an alarm to try again in 60 secs.

        if ( envwf->is_lgellirroom_larsether() )
	{
            set_alarm(60.0,0.0,&set_larsether_messages());
            return;
        }

        if ( wf->query_wiz_level() > 0 )
            continue;

        string longstr = envwf->long();
        if ( !stringp(longstr) || !strlen(longstr) )
            continue;

        locname = file_name(envwf); 
        domainname = "";
        if (wildmatch("/d/*", locname))
            domainname = lower_case(explode(locname,"/")[2]);

        idom = member_array(domainname,LARSETHER_DOMAINLIST);
        if ( idom < 0 ) idom = 0;  // assign to 'ether'
        idstr = val2str(idom);

        kraftords = ({});
        if ( !gDomainWords[idstr] )
            gDomainWords[idstr] = ({});
        else
            kraftords = gDomainWords[idstr];
    
        string *longwds = filter( explode_strip_string(longstr),
                                    is_an_ether_word );
        foreach ( string word : longwds )
        {
            if ( IS_A_KRAFTORD(word) )
	    {
                if ( member_array(word,kraftords) == -1 )
                    kraftords += ({word});
            }
        }

        gDomainWords[idstr] = kraftords; 
    }

    // Sort and insert nsidx indices into available
    // gNumEtherMsg outputs... spacing out
    // or bunching up as appropriate
    // ... sorting primarily by domain index
    //   then player name (not diclosed)

    for ( imsg=0;imsg<gNumEtherMsg;imsg++ )
        gEtherMsg[imsg] = ""; 

    string *sindx = sort_array(m_indices(gDomainWords));
    int nsindx = sizeof(sindx);

    float stride = itof(gNumEtherMsg-1)/itof(nsindx);
    float rsindx = 0.0;

    for ( isindx=0;isindx<nsindx;isindx++ )
    {
       rsindx += stride;
       imsg = ftoi(rsindx);
       gEtherMsg[imsg] += implode(gDomainWords[sindx[isindx]]," ");
    }

    return;
}


string
get_larsether_message( int index )
{
    if ( index < 0 || index > gNumEtherMsg ) 
        return "";

    return gEtherMsg[index];
}


// PLAYER NOTIFICATION FUNCTIONS ------------------------------------------


void
notify_gellir_of_outcome( string gname, int iwinplace, int winttlxp )
{
    string msgstr, mailstr;

    msgstr = "By the Litillgap, last empty crack of the Mikillgap, "+
             "in the Askelund, last remnant grove of the Askverold; "+
	     "the tinder has sparkled -- the Fire is tended anew! "+
             "The Covenant with the Two Ravens and the Woodsman is "+
             "restored -- may mortals bear the fire of thought "+
             "and action across the Realms in this Age as in "+
             "ages past.\n\n";

    switch (iwinplace)
    {
	default:
            msgstr += "The Woodsman chuckles beside the Fire at the "+
                      "mention of your name. You have not been favoured "+
                      "in the remaking of the world.";
            break;
        case 1:
            msgstr += "The Two Ravens caw in the branches above the Fire "+
                      "at the mention of your name. Your passing in "+
                      "in the last age was noticed. You have been granted "+
                      "a trivial boon in the world remade. The Ether of "+
		      "Lars rises from the Litillgap.";
            break;
        case 2:
            string magn = gellir_boon_descrip(winttlxp);
            if ( strlen(magn) > 0 ) 
            magn += "great";
            msgstr += "The Two Ravens coo and crow in the branches "+
                      "above the Fire at the mention of your name. "+
                      "Your Larsgaldrar found " + magn + " favour in the last "+
                      "age. You have been granted a boon in keeping with "+
		      "this in the world remade. The Ether of Lars rises "+
		      "from the Litillgap.";
            break;
    }

    // mail

    mailstr = sprintf("\n\n%s, %s...\n\n%s\n\n%s\n\n",
              capitalize(gname),gellir_description(gname),
	      msgstr,
	      capitalize(LGELLIR_NPC_NAME));

    CREATE_MAIL("The Fire is tended anew", LGELLIR_NPC_NAME,
                gname, "", mailstr );

    return;
}


void
notify_gellir_of_stop_start( string gname, string wizname, int stopstart )
{
    string msgstr, mailstr, tellstr, titlestr;

    object p = find_player(gname);

    switch (stopstart)
    {
	default:
            titlestr = "";
            msgstr = "The Wizard " + capitalize(wizname) + " has advised "+
              "Lars is too busy doing His thing to grant boons to Larsgellirs "+
	      "at the next Armageddon... or any Armageddon until further "+
              "notice. Best not to spend time yelling to Him until His " + 
	      "Wizards advise He is free again. There will be an "+
	      "accounting of all current Larsgaldrar when he returns.";
            break;
        case 1:
            titlestr = "";
            msgstr = "The Wizard " + capitalize(wizname) + " has advised "+
              "Lars is back to granting boons to Larsgellirs as of "+
	      "the next Armageddon. There will be an "+
	      "accounting of all current Larsgaldrar at that time.";
            break;
    }

    // mail

    mailstr = sprintf("\n\n%s, %s...\n\n%s\n\n%s\n\n",
              capitalize(gname), gellir_description(gname),
	      msgstr,
	      capitalize(LGELLIR_NPC_NAME));

    CREATE_MAIL( titlestr, LGELLIR_NPC_NAME, gname, "", mailstr );

    // catch_msg if awake

    if ( !p || !interactive(p) ) return;
     
    tellstr = sprintf("\n\n%s\n%s...\n\n%s\n%s\n\n",
              LGELLIR_NPC_MESGSTART,
	      one_of_list(LGELLIR_NPC_MORTALADDR) + " " + gellir_petname(gname),
	      msgstr,
	      LGELLIR_NPC_ADJ0 + "-" + LGELLIR_NPC_ADJ1);

    p->catch_msg(tellstr);

    return;
}


void
notify_gellir_of_ban_unban( string gname, string wizname, int bantime )
{
    string titlestr, msgstr, mailstr, tellstr;

    object p = find_player(gname);

    if ( !bantime )
    {
        msgstr = "\nThe Wizard " + capitalize(wizname) + " has lifted "+
	      "your ban from participating in the Gellirs of Lars. "+
	      "You may rejoin at a time of your choosing and claim "+
	      "any boon of Lars that is owing to you.\n";
        titlestr = "Your ban from the Gellirs of Lars is lifted";
    }
    else
    {
        msgstr = "The Wizard " + capitalize(wizname) + " has banned "+
              "you from participating in the Gellirs of Lars until "+
	      "further notice.\nAny of your Larsgaldrar heard in the "+
              "current Armageddon cycle will still be eligible for " + 
	      "gaining a boon from Lars. However, your ban prevents "+
	      "you from claiming any boon until the ban is lifted.\n"+
	      "You can contact the Arch of Players (AoP) for a review "+
	      "of this action.\n";
        titlestr = "You have been banned from the Gellirs of Lars";
    }

    CREATE_MAIL(titlestr, LGELLIR_NPC_NAME,
                gname, "", msgstr );

    // catch_msg if awake

    if ( !p || !interactive(p) ) return;
     
    p->catch_msg(msgstr);

    return;
}


// GELLIR INFO/ACTION FUNCTIONS ------------------------------------------------


string
*current_winners_galdrar()
{
    string *galdrar = ({}); 

    foreach ( string gfile : explode(DAEMONmap["DWINGAL"]," ") )
    {
        mapping pGALDRmap = fnget_map( LGELLIRGALDRAR + gfile );
	if ( !m_sizeof(pGALDRmap) )
	    continue;
        galdrar += ({pGALDRmap["MFULLTXT"]});
    }

    return galdrar;
}



void
update_gellir_deaths( string gname )
{
    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + gname );

    if ( !m_sizeof(GELLIRmap) )
        return;

    int n = 0;
    foreach ( string gfile : get_dir(LGELLIRGALDRAR) )
        if ( is_gellirs_heard_galdr(gfile,gname) ) n++;

    GELLIRmap["GNUMDTH"] = n;
    GELLIRmap["GLASTTM"] = time();

    fnput_map( GELLIRmap, LGELLIRGELLIRS + gname );

    return;
}


string
last_highpower_galdr( object gellir )
{
    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + 
                                gellir->query_real_name() );

    if ( !m_sizeof(GELLIRmap) )
        return "";

    if ( !GELLIRmap["GACTIVE"] || 
          GELLIRmap["GLASTTM"] < atoi(DAEMONmap["DLASTTM"]) ) 
        return "";

    if ( !strlen(DAEMONmap["DPOWGAL"]) )
        return "";

    mapping pGALDRmap = fnget_map( LGELLIRGALDRAR + DAEMONmap["DPOWGAL"] );

    if ( !m_sizeof(pGALDRmap) )
        return "";

    return pGALDRmap["MFULLTXT"] + "\n";
}


string
*last_cycle_galdrar()
{
    // galdr from the most recent Arma cycle

    int igmf;
    int ngmf = atoi(DAEMONmap["DLASTMF"]);
    string *galdrmapfiles = sort_array(
              filter(get_dir(LGELLIRGALDRAR),is_a_heard_galdr));

    ngmf = min( ngmf, sizeof(galdrmapfiles) );
    string *outstr = ({});

    for ( igmf=0;igmf<ngmf;igmf++ ) 
    {
        mapping pGALDRmap = fnget_map( LGELLIRGALDRAR + galdrmapfiles[igmf] );
        outstr += ({pGALDRmap["MFULLTXT"]});
    }

    return outstr;
}


int
num_galdrar_this_cycle()
{
    // number of galdr so far this Arma cycle

    int jtime;
    string foo;
     
    int ioldtime = atoi(DAEMONmap["DLASTTM"]);

    string *galdrmapfiles = sort_array(
              filter(get_dir(LGELLIRGALDRAR),is_a_heard_galdr));
    int ngmf = sizeof(galdrmapfiles);
    int igmf = ngmf - 1;

    sscanf(galdrmapfiles[igmf],"%d_%s.o",jtime,foo);

    while ( jtime > ioldtime && igmf > 0 )
    {
	igmf--;
        sscanf(galdrmapfiles[igmf],"%d_%s.o",jtime,foo);
    }

    return (ngmf - igmf - 1);
}


string
*ordered_voted_galdrar()
{
    // galdrar which have received votes from Wizards
    // for artistic merit in order

    string *outarr = ({});

    int nvotes, inum;
    int nhash = 1000;
    mapping galdrmap = ([]);
    mapping votemap = ([]);

    foreach ( string filename : get_dir(LGELLIRGALDRAR) )
    {
        galdrmap = fnget_map( LGELLIRGALDRAR + filename );
	nvotes = atoi(galdrmap["MARTVOTE"]); 
	if ( !nvotes ) continue;
	string vscore = val2str(nhash * nvotes + random(nhash)); 
	votemap[vscore] = galdrmap["MFULLTXT"];
    }

    int nvotemap = m_sizeof(votemap);

    if ( !nvotemap ) return outarr;

    mixed scoreidx = sort_array(m_indices(votemap));

    inum = nvotemap;

    while ( inum > 0 )
    {
        inum--;
        outarr += ({votemap[scoreidx[inum]]});
    }

    return outarr;
}


string
gellir_last_galdr( object plyr )
{

    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) return "";
    string pname = plyr->query_real_name();
    if ( !SECURITY->exist_player(pname) ) return "";

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pname );

    if ( !m_sizeof(GELLIRmap) )
        return "";

    if ( !GELLIRmap["GACTIVE"] || 
          GELLIRmap["GLASTTM"] < atoi(DAEMONmap["DLASTTM"]) ) 
        return "";

    string *herdgmapfiles = ({});
    foreach ( string gfile : sort_array(get_dir(LGELLIRGALDRAR)) )
        if ( is_gellirs_heard_galdr(gfile,pname) )
	    herdgmapfiles += ({gfile});

    int n = sizeof(herdgmapfiles);
    if ( !n ) return "";
    mapping pGALDRmap = fnget_map( LGELLIRGALDRAR + herdgmapfiles[n-1] );

    return pGALDRmap["MFULLTXT"];
}


int
gellir_ether_access( object plyr )
{

    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) return 0;
    string pname = plyr->query_real_name();
    if ( !SECURITY->exist_player(pname) ) return 0;

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pname );

    if ( !m_sizeof(GELLIRmap) || !GELLIRmap["GACTIVE"] )
        return 0;

    if ( GELLIRmap["GLRBOON"] > 0 ) return 1;
    return 0;
}


void
set_boon_increment( object plyr )
{
    int boon, gxp;
    int itime = time();
    string logstr;

    int perror = 0;

    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) perror = 1;
    string pname = plyr->query_real_name();
    if ( !SECURITY->exist_player(pname) ) perror = 1;

    if ( perror )
    {
	string errstr = ctime(time()) + " " + pname + 
	      " ERROR in awarding general XP at outset. " +
	      "Gellir is unexpectedly absent. Gellir can " +
	      "try to claim these points again without aid.\n";

        write_file( LGELLIRLOGS + "experience", errstr);
        write_file( LGELLIRLOGS + "errors", errstr);

        return;
    }

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pname );

    if ( !m_sizeof(GELLIRmap) )
        return;

    if ( !GELLIRmap["GACTIVE"] || !GELLIRmap["GLRBOON"] )
        return;

    boon = GELLIRmap["GLRBOON"];
    GELLIRmap["GLRBOON"] = 0;
    fnput_map( GELLIRmap, LGELLIRGELLIRS + pname );

    // determine the GXP addition from the boon amount 
    // ... including an upward adjustment to offset player
    //  guild taxes... the rationale being that tax has
    //  already been paid on the all lost experience that
    //  went into creating the boon in the first place

    int total_tax_pct = plyr->query_guild_pref_total();
    gxp = ftoi( itof(boon) / ( 1.0 - 0.01 * itof(max(0,total_tax_pct)) ) );

    // increment in general xp to be added over N stages
    // rather than in a single hit... to allow player
    // brutality effects to do their thing

    int nstages = 1 + ( 1 + LARSETHER_MAXNUMIDX ) / LARSETHER_AWARDSDIV;
    int gxppst = gxp / nstages;

    // gxp remainder
    plyr->add_exp_general( (gxp % nstages) );

    // rest of gxp delivery will occur by stages in larsether rooms
    if ( !gxppst )   
        logstr = ctime(itime) + " " + pname + 
	         " was awarded " + val2str(gxp) +
	         " general XP.\n";
    else
    {
        plyr->add_prop(LGELLIR_PROP_GXP_INCREMENT,gxppst);
        logstr = ctime(itime) + " " + pname + " is set to be awarded " +
	         val2str(gxp) + " general XP in " + val2str(nstages) + 
	         " stages. Check this log for possible delivery errors.\n";
    }

    write_file( LGELLIRLOGS + "experience", logstr );

    return;
}


void
log_boon_completion( object plyr )
{
    int boon, gxp;
    int itime = time();
    string logstr;

    int perror = 0;

    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) perror = 1;
    string pname = plyr->query_real_name();
    if ( !SECURITY->exist_player(pname) ) perror = 1;

    if ( !plyr->query_prop(LGELLIR_PROP_GXP_INCREMENT) )
        return;

    if ( perror )
    {
	string errstr = ctime(time()) + " " + pname + 
	      " ERROR in awarding general XP at endpoint. " +
	      "Gellir is unexpectedly absent.\n";

        write_file( LGELLIRLOGS + "experience", errstr);
        write_file( LGELLIRLOGS + "errors", errstr);

        return;
    }

    int nincr = plyr->query_prop(LGELLIR_PROP_INCR_COUNT);
    int nstages = 1 + ( 1 + LARSETHER_MAXNUMIDX ) / LARSETHER_AWARDSDIV;

    if ( nincr == nstages )
        logstr = ctime(itime) + " " + pname + " has been SUCCESSFULLY awarded "+
             "general XP over " + val2str(nincr) + " stages.\n";
    else
        logstr = ctime(itime) + " " + pname + " has been not been awarded "+
             "general XP over the correct number of stages... wanted ("+
	     val2str(nstages) + " stages, but got " + val2str(nincr) + ") "+
	     "instead.\n";

    write_file( LGELLIRLOGS + "experience", logstr );

    plyr->remove_prop(LGELLIR_PROP_INCR_COUNT);
    plyr->remove_prop(LGELLIR_PROP_GXP_INCREMENT);

    return;
}


int
is_a_larsgellir( object plyr )
{
    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) return 0;

    string pname = plyr->query_real_name();
    if ( !SECURITY->exist_player(pname) ) return 0;

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pname );

    if ( !m_sizeof(GELLIRmap) )
        return 0;

    if ( GELLIRmap["GBANNED"] )
        return -1;

    if ( !GELLIRmap["GACTIVE"] )
        return 0;

    return 1;
}


string
gellir_petname( string gname )
{
    object plyr = find_player(gname);
    if ( !objectp(plyr) ) return "";

    string *adjs = plyr->query_adjs();
    if ( !sizeof(adjs) )
    {
        adjs[0] = sprintf("%s-ed",gname);
        adjs[1] = sprintf("%s-y",gname);
    }

    string cname = capitalize(adjs[0]);
    if ( strlen(adjs[1]) > 0 )  
        cname = sprintf("%s-%s",cname,capitalize(adjs[1]));

    return cname;
}


string
gellir_boon_descrip( int boon )
{
    int i, n;
    string outstr = "";

    if ( boon < 1 )
        return "";

    // ln(boon)/ln(100)
    n = ftoi( 0.2172 * log(itof(boon)) );

    for ( i=0;i<n;i++ )
        outstr += "very ";

    return outstr;
}


string
gellir_description( string pname )
{

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pname );

    if ( !m_sizeof(GELLIRmap) )
        return "";

    string astr = "";
    if ( !GELLIRmap["GACTIVE"] ) astr = "un";

    astr = sprintf("an %sinspired Larsgellir",astr);

    int pnumdth = GELLIRmap["GNUMDTH"];

    if ( !pnumdth )
        astr = sprintf("%s, unheard",astr);
    else if ( pnumdth == 1 )
        astr = sprintf("%s, of one hearing",astr);
    else
        astr = sprintf("%s, of %s hearings",astr,LANG_NUM2WORD(pnumdth));

    int pnumwin = GELLIRmap["GNUMWIN"];

    if ( !pnumwin )
        astr = sprintf("%s, ungifted",astr);
    else if ( pnumwin == 1 ) 
        astr = sprintf("%s, gifted a boon",astr);
    else
        astr = sprintf("%s, gifted %s boons",astr,LANG_NUM2WORD(pnumwin));

    if ( GELLIRmap["GLRBOON"] > 0 ) 
    {
        string fav = gellir_boon_descrip( GELLIRmap["GLRBOON"] );
        astr = sprintf("%s, and %sfavoured by Lars",astr,fav);
    }
    else
        astr = sprintf("%s, and unfavoured by Lars",astr);

    fnput_map( GELLIRmap, LGELLIRGELLIRS + pname );

    return astr;
}


int
inspire_gellir( object plyr )
{
    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) return 0;

    string pn = plyr->query_real_name();
    if ( !SECURITY->exist_player(pn) ) return 0;

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pn );

    if ( !m_sizeof(GELLIRmap) )
    {
        GELLIRmap["GNUMDTH"] = 0;
        GELLIRmap["GNUMWIN"] = 0;
        GELLIRmap["GLRBOON"] = -1;
        GELLIRmap["GXPLOSS"] = 0;
        GELLIRmap["GBANNED"] = 0;
    }
    else
        if ( GELLIRmap["GBANNED"] > 0 || GELLIRmap["GACTIVE"] > 0 )
            return 1;
        
    GELLIRmap["GACTIVE"] = 1; 
    GELLIRmap["GLASTTM"] = time(); 

    fnput_map( GELLIRmap, LGELLIRGELLIRS + pn );

    return 1;
}


int
expire_gellir( object plyr )
{
    if ( !objectp(plyr) || !IS_PLAYER_OBJECT(plyr) ) return 0;

    string pn = plyr->query_real_name();
    if ( !SECURITY->exist_player(pn) ) return 0;

    mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + pn );

    if ( !m_sizeof(GELLIRmap) || !GELLIRmap["GACTIVE"] ) return 1;
        
    GELLIRmap["GACTIVE"] = 0; 

    fnput_map( GELLIRmap, LGELLIRGELLIRS + pn );

    return 1;
}


// MAJOR ACTION FUNCTIONS -------------------------------------------------


void
init_first_maps()
{
    // only called when setting up the club
    // from scratch

    int inittime = time() - 10;
    int galdrtime = inittime - 10;

    // ..... import file containing global
    //  adjective frequency map and write 
    //  mapping file

    string inp, word, inpfilepath, outfilepath;
    int n, freq, success, linepos, nwds;
    mapping importGLOBWDmap = ([]);

    inpfilepath = LGELLIRWORDREF + "word_freq_import.txt";
    nwds = 0;
    linepos = 0;
    success = 1;

    while ( success )
    {
        inp = read_file( inpfilepath, linepos, 1 );
        success = stringp(inp);
        if ( success )
        {
            n = sscanf( inp, "%s %d", word, freq );
            if ( n < 2 ) success = 0;
            if ( freq < 1 ) success = 0;
        }
        if ( success )
	{
	    importGLOBWDmap[lower_case(word)] = freq;
	    nwds++;
        }
        linepos++;
    }
    if ( !nwds )
        write("No words were imported from " + inpfilepath + "\n");
    else
    {
	outfilepath = LGELLIRWORDREF + "globadjmap";
        fnput_map( importGLOBWDmap, outfilepath );
        write(val2str(nwds) + " words were imported from " + inpfilepath +
	      " and written to " + outfilepath + "\n");
    }

    // ..... initialise a GELLIRmap for the club NPC

    mapping GELLIRmap = ([]);

    GELLIRmap["GACTIVE"] = 1;
    GELLIRmap["GNUMDTH"] = 1;
    GELLIRmap["GNUMWIN"] = 1;
    GELLIRmap["GLRBOON"] = 1;
    GELLIRmap["GXPLOSS"] = 1;
    GELLIRmap["GBANNED"] = 0;
    GELLIRmap["GLASTTM"] = galdrtime;

    outfilepath = LGELLIRGELLIRS + LGELLIR_NPC_NAME;
    fnput_map( GELLIRmap, outfilepath );
    write("Saving null GELLIRmap to " + outfilepath + "\n");

    // ..... save a default galdr for the club NPC

    mapping pGALDRmap = ([]);

    pGALDRmap["MDEFINED"] = val2str(galdrtime);
    pGALDRmap["MFULLTXT"] = ".....................................\n"+
                          ".......................(       ).....\n"+
                          ".....................(      )    )...\n"+
                          "....................(   (         )..\n"+
                          "......................(          )...\n"+
                          "........................'--\\ `\\--`...\n"+
                          ".......Relieved.again......_\\ _\\.....\n"+
                          "............of.............`\\ \\......\n"+
                          ".......Mortal.form...........\\ \\.....\n"+
                          ".........as.victim.over......_\\_\\....\n"+
                          "......familiar.to.the.touch..`\\\\.....\n"+
                          ".....of.the.Scythe.so.cold.....\\\\....\n"+
                          ".......I.seek.Your.favour.and..`\\....\n"+
                          "........power.on.my.Return.......\\|..\n"+
                          "................................`\\|/'\n"+
                          "----------------------------------*--\n";
    pGALDRmap["MLSTKRAF"] = "relieved mortal familiar cold";
    pGALDRmap["MLSTNTKR"] = "again of form as victim over " +
                            "to the touch of the scythe so "+ 
			    "I seek your favour and power on my return";
    pGALDRmap["MHEARDXL"] = "1";
    pGALDRmap["MARTVOTE"] = "1";

    string galdrmapfile = sprintf("%d_%s",galdrtime,LGELLIR_NPC_NAME);
    outfilepath = LGELLIRGALDRAR + galdrmapfile;
    fnput_map( pGALDRmap, outfilepath );
    write("Saving null GALDRmap to " + outfilepath + "\n");

    // ...... create an initial DAEMONmap

    DAEMONmap["DLASTTM"] = val2str(inittime);
    DAEMONmap["DLASTMF"] = "1";
    DAEMONmap["DGELLRS"] = LGELLIR_NPC_NAME;
    DAEMONmap["DSCORES"] = "1";
    DAEMONmap["DSCOXPL"] = "1";
    DAEMONmap["DMXPOWR"] = "1";
    DAEMONmap["DPOWGAL"] = galdrmapfile;
    DAEMONmap["DWINNER"] = LGELLIR_NPC_NAME;
    DAEMONmap["DWINSCR"] = "1";
    DAEMONmap["DWINGAL"] = galdrmapfile;
    DAEMONmap["DWINBON"] = "1";
    DAEMONmap["DSUSPND"] = "0";

    put_daemonmap( inittime );
    put_daemonmap( 0 );

    return;
}


void
process_maps_after_reset()
{
    int igmf, ngmf;
    int jtime, elapsed, wdpw, kpower, mxpower, winscore, winttlxp;
    int time_power_score, experience_loss;
    int iwinplace;
    string gellirn, galdrmx, wingellr;
    string scorernames, scorevalues, scorerxplss;
    string *galdrmapfiles;

    mapping pGALDRmap = ([]);
    mapping GELLIRmap = ([]);
    mapping ptimermap = ([]);
    mapping pscoremap = ([]);
    mapping pxlossmap = ([]);
    mapping pfilesmap = ([]);
    mapping kwdusemap = ([]);

    int itimenow = time();

    write_file( LGELLIRLOGS + "daemon_resets", ctime(itimenow) + 
       " Reset action initiated\n");

    g = 10;

    get_daemonmap( 0 );  // recall most current map

    if ( atoi(DAEMONmap["DSUSPND"]) > 0 ) 
    {
        gProcessEnabled = 0;
        return;
    }

    gProcessEnabled = 1;

    get_globwdmap();
    get_wdtimemap();

    if ( !m_sizeof(DAEMONmap) )
        init_first_maps();

    int ioldtime = atoi(DAEMONmap["DLASTTM"]);

    if ( ioldtime > itimenow )
    {
        write_file( LGELLIRLOGS + "errors", ctime(itimenow) + 
         " Previous timestamp " + val2str(ioldtime) + 
	 " > current timestamp " + val2str(itimenow) + "\n");
        return;
    }

    // process outcomes of gellir deaths since last call

    // galdr files in order: they lead with an integer timestamp
    // followed by gellir name

    galdrmapfiles = sort_array(
              filter(get_dir(LGELLIRGALDRAR),is_a_heard_galdr));
    ngmf = sizeof( galdrmapfiles );
    if ( !ngmf )
    {
        write_file( LGELLIRLOGS + "daemon_resets", ctime(itimenow) + 
           " Reset action completed -- no galdrar found\n");
        return;
    }

    // relax all entries in the WDTIMEmap
    // to let those which are not used
    // revert back to their natural level 

    int time_relax = ( itimenow - ioldtime ) / RELAX_RATE_DIVISOR;

    foreach ( string word : m_indices(WDTIMEmap) )
    {
        int usagetime = WDTIMEmap[word];
        usagetime -= time_relax; 
        WDTIMEmap[word] = max(0, usagetime);
    }

    // go through galdrar in order backwards
    // from itimenow timestamp to ioldtime timestamp

    wingellr = "_no_one_";
    pscoremap[wingellr] = 0;
    winttlxp = 0;

    mxpower = 0;
    galdrmx = "";

    igmf = ngmf - 1;

    sscanf(galdrmapfiles[igmf],"%d_%s.o",jtime,gellirn);

    if ( jtime <= ioldtime ) 
        write_file( LGELLIRLOGS + "errors", ctime(itimenow) + 
         " No new galdrar found to process\n");
    else
    {
        // there are new galdrar to process

        pfilesmap[gellirn] = galdrmapfiles[igmf];
        ptimermap[gellirn] = itimenow;
        pscoremap[gellirn] = 0;
        pxlossmap[gellirn] = 0;

        // loop over timestamped files...

        while ( jtime > max(1,ioldtime) && igmf > -1 )
        {
            if ( file_size(LGELLIRGALDRAR + galdrmapfiles[igmf]) > 0 )
	    {
                pGALDRmap = fnget_map( LGELLIRGALDRAR + galdrmapfiles[igmf] );

                pfilesmap[gellirn] += sprintf( " %s", galdrmapfiles[igmf] );

                elapsed = ptimermap[gellirn] - jtime;
                ptimermap[gellirn] = jtime;

                kpower = -1;

                foreach ( string word : 
		            explode_strip_string(pGALDRmap["MLSTKRAF"]))
                {
                    if ( (wdpw = kraftord_power(word)) != -1 ) 
                    { 
                        kpower = max( kpower, wdpw );
                        kwdusemap[word] += elapsed;
                    }
                }

                if ( kpower > mxpower )
	        {
	            mxpower = kpower;
		    galdrmx = galdrmapfiles[igmf];
	        }

                pscoremap[gellirn] += kpower * elapsed;

	        if ( pscoremap[gellirn] > pscoremap[wingellr] ) 
		    wingellr = gellirn;

	        experience_loss = atoi(pGALDRmap["MHEARDXL"]);
                pxlossmap[gellirn] += experience_loss;
	        winttlxp += experience_loss;
	    }

            igmf--;
            sscanf(galdrmapfiles[igmf],"%d_%s.o",jtime,gellirn);

            if ( !pfilesmap[gellirn] ) 
	    {
                pfilesmap[gellirn] = galdrmapfiles[igmf];
                ptimermap[gellirn] = itimenow;
                pscoremap[gellirn] = 0;
                pxlossmap[gellirn] = 0;
	    }

        } // loop over timestamped galdrar files

    }

    scorernames = "";
    scorevalues = "";
    scorerxplss = "";

    if ( wingellr == "_no_one_" )
    {
        write_file( LGELLIRLOGS + "errors", ctime(itimenow) + 
         " No winning gellir found\n");

        DAEMONmap["DWINNER"] = "";
        DAEMONmap["DWINSCR"] = "-1";
        DAEMONmap["DWINGAL"] = "";
    }
    else
    {
        // there is a winner...
	// so must have been at least one participating gellir
	// ... and some words used in at least one galdr

        // loop over all participating gellirs and update their maps 

        foreach ( string gellirn : m_indices(pscoremap)  )
        {
	    if ( gellirn == "_no_one_" ) continue;

            mapping GELLIRmap = fnget_map( LGELLIRGELLIRS + gellirn );

            iwinplace = 0; 

            if ( pscoremap[gellirn] > 0 )
            {
                scorernames += sprintf("%s ",gellirn);
                scorevalues += sprintf("%d ",pscoremap[gellirn]);
	        scorerxplss += sprintf("%d ",pxlossmap[gellirn]);

                if ( pscoremap[gellirn] > THRESHOLD_SCORE_UNITBOON )
	        {
		    if ( GELLIRmap["GLRBOON"] < 0 )
                        GELLIRmap["GLRBOON"] = 1;
		    else
                        GELLIRmap["GLRBOON"]++;
		    iwinplace = 1; 
                }

                if ( wingellr == gellirn )
	        {
                    GELLIRmap["GNUMWIN"]++;
                    GELLIRmap["GLRBOON"] += winttlxp;
		    iwinplace = 2; 
                }

                GELLIRmap["GXPLOSS"] += pxlossmap[gellirn];
            }

            fnput_map( GELLIRmap, LGELLIRGELLIRS + gellirn );

            // gellirs 'heard' in this reset are notified by mail...

            notify_gellir_of_outcome( gellirn, iwinplace, winttlxp );

        } // loop over participating gellirs 

        // update WDTIMEmap based on total usage
        // time in this past cycle

        foreach ( string word : m_indices( kwdusemap ) )
        {
            int numsecs = kwdusemap[word];

            if ( !WDTIMEmap[word] )
                WDTIMEmap[word] = numsecs;
            else
                WDTIMEmap[word] += numsecs;
        }

        DAEMONmap["DWINNER"] = wingellr;
        DAEMONmap["DWINSCR"] = val2str(pscoremap[wingellr]);
        DAEMONmap["DWINGAL"] = pfilesmap[wingellr];

    }

    DAEMONmap["DLASTTM"] = val2str(itimenow);
    DAEMONmap["DLASTMF"] = val2str(igmf+1);
    DAEMONmap["DGELLRS"] = scorernames;
    DAEMONmap["DSCORES"] = scorevalues;
    DAEMONmap["DSCOXPL"] = scorerxplss;
    DAEMONmap["DMXPOWR"] = val2str(mxpower);
    DAEMONmap["DPOWGAL"] = galdrmx;
    DAEMONmap["DWINBON"] = val2str(winttlxp);
    DAEMONmap["DSUSPND"] = "0";

    put_daemonmap( 0 );  // save current active map
    put_wdtimemap();  // still in memory also
    // globwdmap is not altered by this process 

    // loop over all gellirs to apply GLRBOON decay
    foreach ( string gfile : get_dir(LGELLIRGELLIRS) )
    { 
        mapping GELLIRmap = fnget_map( gfile );
        if ( !m_sizeof(GELLIRmap) ) continue;
	int glrboon = GELLIRmap["GLRBOON"];
	if ( glrboon > 0 ) 
	    GELLIRmap["GLRBOON"] = 
	        ( glrboon * ( 100 - BOON_DECAY_RATE_PCT ) ) / 100;
        fnput_map( GELLIRmap, LGELLIRGELLIRS + gfile );
    }

    write_file( LGELLIRLOGS + "daemon_resets", ctime(itimenow) + 
       " Reset action completed normally\n");

    return;
}


/* END OF FILE ============================================================= */

