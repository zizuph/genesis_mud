/*
 * File: /d/Gondor/common/guild2/idleness.c
 *
 * The orginal concept and implementation by Chmee
 *
 * This file contains functions tracking Nazgul and in some cases
 * non-Nazgul activity as described in the file idleness.txt
 *
 */

#define DEBUG(x) find_player("toby")->catch_msg("[DEBUG - nazgul idleness]: " + x + "\n")

inherit "/std/object.c";

#include <files.h>
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

// TRACKED_MAGES should be dynamic checking how many are on the rooster.
#define TRACKED_MAGES 6
#define RECORD_FIELDS 2
#define GAMES        60

#define NULL 0
#define CRITICAL 3

#define RESULT 0
#define TIME 1

#define HOUR (60.0*60.0)
#define DAY 24*60*60

/* 
 * Put the desired values here. A Nazgul with performance below WORRYING
 * gets a warning. When it falls below UNACCEPTABLE he loses the position.
 * A fresh Nazgul should get a bonus placing him or her somewhere between
 * WORRYING and ACCEPTABLE
 * A nazgul with performance score above OUTSTANDING should make a break
 * or devote a part of his or her energy to find a new candidate for
 * a ring. A nazgul who hits WORKOHOLIC should visit a doctor really soon.
 * I'm deadly serious now.
 */
#define WORKOHOLIC       10000
#define OUTSTANDING       6000
#define EXCELLENT         4000
#define VERY_GOOD         3000
#define GOOD              2000
#define ABOVE_AVERAGE     1500
#define ACCEPTABLE        1000
#define WORRYING           750 

/*
 * The JOINING_BONUS is calculated such a way so the new nazgul gets
 * effectively 1.1 * itof( ACCEPTABLE )
 */
#define JOINING_BONUS (ftoi(0.5+ (1.1* itof( ACCEPTABLE )* (itof(time()+\
    Current_game - SECURITY->query_start_time()))/(24.0*HOUR))))

#define HONEYMOON OUTSTANDING
 
mixed Nazgul_records;
string *Nazgul_index;
int Current_game;
int Game_length;
int *Current_stats;

static int Update_flag = 0;

nomask public void start_idling( void );
nomask private void calculate_stats( void );
nomask private int find_free_index( void );
nomask private int find_the_most_idle_non_nazgul( void );
nomask public int remove_from_roster( mixed mage );
nomask public int increase_activity( mixed mage, int activity );
nomask public int add_new_nazgul( mixed mage );
nomask public int stop_logging( mixed mage );
nomask public string mtos( mixed name );
nomask public int screen_nazgul( mixed mage );
nomask public string appraise_nazgul( object nazgul, object spectator );
nomask public int is_idle( mixed mage );
public void relaunch( void );
public void recalculate( void );
nomask public void create_nazgul_records( void );
nomask public int query_score( mixed mage );
nomask public void query_history( mixed mage );

/*
 * Function name: start_idling
 * Description  : Initializes the whole thing. This function should be
 *                called only once per reboot from preloaded death_room
 *                The RESULT is normalized to one hour.
 */
nomask public void start_idling( void )
{
 int i;
 int Last_game_length;
 float T1;

    setuid();
    seteuid( getuid() );
                                /*No need to start the system if the game 
                                  is closed for mortals.                  */
    if (SECURITY->query_runlevel())
    {
        return;
    }
    restore_object( IDLENESS );

                                /*First we need to find out how long
                                  the previous game lasted.               */
    Last_game_length = TICKER->query_ticker() * ftoi( TICKER_LENGTH );
                                /*This is to prevent division by 0 when
                                  the system is started for the first time*/
    if (Last_game_length == 0)
    {
        Last_game_length = 1;
    }

    TICKER->start_ticker();
DEBUG("TICKER STARTED");
    if ((Game_length += Last_game_length) < DAY)
    {                           /*Don't switch the game in such case.     */
        save_object( IDLENESS );
        return;
    }
DEBUG("Fixing stuff");
    for (i=0; i < TRACKED_MAGES; i++)
    {                           /*Check whether the mage is a valid nazgul*/
        if ((Nazgul_records[i][TIME][Current_game] == 0) &&
            (MORGUL_NAZGUL_MASTER->query_is_nazgul( Nazgul_index[i] ) > 0))
        {
            T1 = itof( Game_length ) / HOUR;
            Nazgul_records[i][TIME][Current_game] = ftoi(0.5 + T1);
            T1 = HOUR / itof(Game_length);
            T1 *= itof( Nazgul_records[i][RESULT][Current_game] );
            Nazgul_records[i][RESULT][Current_game] = ftoi( 0.5 + T1 );
        }
        else if (Nazgul_records[i][TIME][Current_game] != 0)
        {
            T1 = itof( Nazgul_records[i][TIME][Current_game] )/ HOUR;
            Nazgul_records[i][TIME][Current_game] = ftoi( 0.5 + T1 );
            T1 = HOUR / itof( Nazgul_records[i][TIME][Current_game]);
            T1 *= itof( Nazgul_records[i][RESULT][Current_game] );
            Nazgul_records[i][RESULT][Current_game] = ftoi( 0.5 + T1 );
        }
    }
    
                                /*Now let us switch the cycle.            */
    Current_game++;
    if (Current_game == GAMES)
    {
        Current_game = 0;
    }
    for (i=0; i< TRACKED_MAGES; i++)
    {
        Nazgul_records[i][RESULT][Current_game] = 0;
        Nazgul_records[i][TIME][Current_game] = 0;
    }
    Game_length = 0;

    calculate_stats();
    for (i=0; i < TRACKED_MAGES; i++)
    {
        if (MORGUL_NAZGUL_MASTER->query_is_nazgul( Nazgul_index[i] ) > 0)
        {
            screen_nazgul( Nazgul_index[i] );
        }
    }
    save_object( IDLENESS );
    return;
}

/*
 * Function name: calculate_stats
 * Description  : Calculates all statistics taking into account all changes
 *                occured in the previous game. Called from
 *                start_idling() only.
 */
nomask private void calculate_stats( void )
{
 int i, j;
 float T1, T2;
 
    for (i=0; i < TRACKED_MAGES; i++)
    {
        if (Nazgul_index[i] != NULL)
        {
            T1 = 0.0;
            T2 = 0.0;
            for (j=0; j < GAMES; j++)
            {
                T1 += itof( Nazgul_records[i][RESULT][j]*
                    Nazgul_records[i][TIME][j] );
                T2 += itof( Nazgul_records[i][TIME][j] );
            }
            T1 -= itof( Nazgul_records[i][RESULT][Current_game]*
                Nazgul_records[i][TIME][Current_game] );
            if (T2 > 0.0)
            {
                   Current_stats[i] = ftoi( 0.5 + T1*24.0/T2 );
            }
            else
            {
                Current_stats[i] = 0;
            } 
        }
    }
    return;
}

/*
 * Function name: find_free_index
 * Description  : Finds a free index and if there is none discards someone.
 * Return values: the free index or -1 if none was found.
 */
nomask private int find_free_index( void )
{
 int i;
                                /*I assume that we measure only the activity
                                  of the Nine.                            */
    if (sizeof(MORGUL_NAZGUL_MASTER->query_nazgul()) == TRACKED_MAGES)
    {
        return -1;
    }

                                /*Let's try to find a free one first.     */ 
    for (i=0; i < TRACKED_MAGES; i++)
    {
        if (Nazgul_index[i] == NULL)
        {
            return i;
        }
    }
                                /*Now let's discard someone.              */
    i = find_the_most_idle_non_nazgul();
    remove_from_roster( i );
    return i;
}

/*
 * Function name: find_the_most_idle_non_nazgul
 * Description  : Finds the least active non active member of the roster.
 * Return values: The index in the Nazgul_index array.
 */
nomask private int find_the_most_idle_non_nazgul( void )
{
 string mage;
 int i, j = -1, k = 0;
    
    for (i=0; i < TRACKED_MAGES; i++)
    {
        if (((mage = Nazgul_index[i]) != NULL) &&
            ((MORGUL_NAZGUL_MASTER->query_is_nazgul( mage )) == 0))
        {
            if ((j > Current_stats[i]) || (j == -1))
            {                   /*At the moment we look for the one with
                                  the lowest mean value.                  */
                j = Current_stats[i];
                k = i;
            }
        }
    }
    return k;
}

/*
 * Function name: remove_from_roster
 * Description  : Removes a mage mage from the Nazgul_records.
 * Argument     : Name, object pointer or an index in the Nazgul_index.
 * Return values: -1 in the case of failure, 1 otherwise.
 */
nomask int remove_from_roster( mixed mage )
{
 int i, j;

    if (objectp( mage ))
    {
        mage = member_array( mage->query_real_name(), Nazgul_index );
    }
    else if (stringp( mage ))
    {
        mage = member_array( lower_case( mage ), Nazgul_index );
    }
    else if (!((intp(mage)) && (mage >= 0) && (mage < TRACKED_MAGES)))
    {
        return -1;
    }

    Current_stats[mage] = 0;
    Nazgul_index[mage] = NULL;
    for (i=0; i < GAMES; i++)
    {
        for (j=0; j < RECORD_FIELDS; j++)
        {
            Nazgul_records[mage][j][i] = 0;
        }
    }
    save_object( IDLENESS );
    return 1;
}

public void log_obsolete_call()
{
    string result = sprintf("idlenss/%O called, Interactive: %s\n",
        calling_function(), (objectp(this_interactive()) ? this_interactive()->query_real_name() : ""));
    int i = -1;
    while(objectp(calling_object(i))) {
        result += sprintf("  - %O->%O()\n", calling_object(i), calling_function(i));
        i--;
    }
    log_file("mage_obsolete", result, -1);
}

/*
 * Function name: increase_activity
 * Description  : Adds the desired amount of activity points to
 *                Nazgul_records.
 * Arguments    : mage - the name or the object pointer of a target
 *                activity - one of valid activities as described in
 *                defines in the beginning of this file.
 * Return values: > 0 amount of points added
 *                0 target is not tracked
 *                -1 error
 */
nomask public int increase_activity( mixed mage, int activity )
{
    log_obsolete_call();
    return "/d/Gondor/guilds/morgulmage/master/master"->increase_activity(mage, activity);
    
 int index, error = MORGUL_MASTER->query_ISE_counter();

    if (error == CRITICAL)
    {
        write_file( "/d/Gondor/log/bugs", ctime( time() )+ "The idleness "+
            "system detected an error: Critical failure, morgul data are "+
            "not in sync with the idleness system. Administrator's "+
            "attention is requested!\n\n" );
        return -1;    
    }
    else if (error > CRITICAL)
    {
        return -1;        
    }
    //if (activity <= 0)
    if (activity < 0)
    {
        return -1;
    }
    
    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    }

    if (MORGUL_NAZGUL_MASTER->query_is_nazgul( mage ))
    {
        if ((index = member_array( mage, Nazgul_index )) == -1)
        {
            write_file("/d/Gondor/log/bugs", ctime( time() )+
                "The idleness system detected an error: Nazgul "+
                capitalize( mage )+ " is not in the roster. ISE level: ("+
                error+ "). Relaunch initialized.\n\n" );
            relaunch();
            MORGUL_MASTER->incr_ISE_counter();
            return increase_activity( mage, activity );
        }
        Nazgul_records[index][RESULT][Current_game] += activity;
                                /*In order to optimize the excessive disk
                                 *access by the system, the variables are
                                 *not dumped here (via save_object()) but
                                 *is periodicaly commited in ticker.c.    */
        Update_flag = 1;
        return activity;
    }
    return 0;
}

/*
 * Function name: add_new_nazgul
 * Description  : Adds a new nazgul to the roster. This function should
 *                be called from the MORGUL_NAZGUL_MASTER (throne_room.c)
 *                from promote_nazgul()
 * Arguments    : A name or an object pointer to a player.
 * Return values: 1 if o.k. -1 if something screwed up.
 */
nomask public int add_new_nazgul( mixed mage )
{
 int Index;

    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    }
    if (MORGUL_NAZGUL_MASTER->query_is_nazgul( mage ) == 0)
    {
        return -1;
    }
    
    if ((Index = member_array( mage, Nazgul_index )) == -1)
    {
        Index = find_free_index();
        Nazgul_index[Index] = mage;
    }

                                /*Special gift for a rookie nazgul.       */
    if (Current_stats[Index] == 0)
    {
        Nazgul_records[Index][RESULT][Current_game] += HONEYMOON;
        Current_stats[Index] = ACCEPTABLE + 1;
    }
    else
    {                           /*JOINING_BONUS is granted each time
                                  a nazgul gets a ring.                   */
        Nazgul_records[Index][RESULT][Current_game] += JOINING_BONUS;
    }
                                /*This is done to prevent errors if the
                                  Nazgul regains the ring during the same
                                  game it was lost.                       */
    Nazgul_records[Index][TIME][Current_game] = 0;
    save_object( IDLENESS );
    return 1;
}

/*
 * Function name: stop_logging
 * Description  : This function is called from function demote_nazgul() in
 *                MORGUL_NAZGUL_MASTER. It only logs the time a nazgul
 *                lost the ring.
 * Arguments    : mixed mage - name or an object pointer to the mage.
 * Return values: -1 in the case of error, 1 if everyting's go smoothly.
 */  
nomask public int stop_logging( mixed mage )
{
 int Index, error = MORGUL_MASTER->query_ISE_counter();

    if (error == CRITICAL)
    {
        write_file( "/d/Gondor/log/bugs", ctime( time() )+ "The idleness "+
            "system detected an error: Critical failure, morgul data are "+
            "not in sync with the idleness system. Administrator's "+
            "attention is requested!\n\n" );
        return -1;    
    }
    if (error >= CRITICAL)
    {
        return -1;        
    }
    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    } 
    if ((Index = member_array( mage, Nazgul_index )) == -1)
    {
        write_file("/d/Gondor/log/bugs", ctime( time() )+ "The idleness "+
            "system detected an error: Nazgul "+ capitalize( mage )+
            " is not in the roster. ISE level: ("+ error+ "). Relaunch "+
            "initialized.\n\n" );
        relaunch();
        MORGUL_MASTER->incr_ISE_counter();
        return stop_logging( mage );
    }
    
    Nazgul_records[Index][TIME][Current_game] =
        time() + Game_length - SECURITY->query_start_time();
    save_object( IDLENESS );
    return 1;
}

/*
 * Function name: mtos
 * Description  : Makes sure that the argument name is a player's real name
 *                in lowercase.
 * Arguments    : An object pointer to a player or his(her) name.
 * Return values: A name in lowercase or NULL
 */
nomask public string mtos( mixed name )
{
    if (objectp( name ))
    {
        return name->query_real_name();
    }
    else if (stringp( name ))
    {
        return lower_case( name );
    }
    return NULL;
}

/*
 * Function name: screen_nazgul
 * Description  : This function is called from within start_idling() after
 *                the calculate_stats(). It rejects the Nazgul whose score
 *                is too low.
 * Arguments    : mixed mage - name or an object pointer to the mage.
 * Return values: -1 in the case of error, 1 if everyting's go smoothly.
 */
nomask public int screen_nazgul( mixed mage )
{
 int Index;
 
    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    }
    if ((Index = member_array( mage, Nazgul_index )) == -1)
    {
        return -1;
    }

    if (Current_stats[Index] < WORRYING)
    {
        STORAGE->send_message( mage, "\nAngered by your lack of "+
            "dedication the Dark Lord is on the verge of taking your powers away!\n\n");
/*
        MORGUL_NAZGUL_MASTER->demote_nazgul_alarm( mage,
            "Insufficient activity level: "+ Current_stats[Index] );
*/
    }
    else if (Current_stats[Index] < ACCEPTABLE)
    {
        STORAGE->send_message( mage, "\nThe Dark Lord is seriously "+
            "concerned about your lack of dedication to the service!\n\n");
    }
    else if (Current_stats[Index] < ABOVE_AVERAGE)
    {
        STORAGE->send_message( mage, "\nThe Dark Lord is somewhat "+
            "pleased with your dedication to the service!\n\n");
    }
    else if (Current_stats[Index] < GOOD)
    {
        STORAGE->send_message( mage, "\nYou feel the Dark Lord's presence "+
            "and realize He has noticed your dedication to the service!\n\n");
    }
    else if (Current_stats[Index] < VERY_GOOD)
    {
        STORAGE->send_message( mage, "\nYou feel the Dark Lord's presence "+
            "and realize He is pleased with your dedication to the service!\n\n");
    }
    else if (Current_stats[Index] > (VERY_GOOD-1))
    {
        STORAGE->send_message( mage, "\nYou feel the Dark Lord's presence "+
            "and realize He is rather pleased with your dedication to the "+
            "service and the Society!\n\n");
    }
    return 1;
}

/*
 * Function name: appraise_nazgul
 * Description  : This function, being called  from show_subloc(), adds
 *                description accordingly to Nazgul performance.
 *                The following line should be attached there at some point:
 *                str += IDLENESS->appraise_nazgul( me, for_obj);
 *                This is also called from the v/vitals check.
 * Arguments    : me      - the object to which the subloc is linked.
 *                for_obj - the object that wants to see the subloc. 
 * Return values: String that will be attached to morgul sublocation.
 */
nomask public string appraise_nazgul( object me, object for_obj )
{
    log_obsolete_call();
    return "/d/Gondor/guilds/morgulmage/master/master"->appraise_nazgul(me, for_obj);
    
 string *description =
 ({
    ({
        " feel irreplacable.\n",
        " feel an immense burden of the ring.\n",
        " feel like competing with fellow Ringwraiths.\n",
        " get known in the Tower for your addiction to perfection.\n",
        " are sure of your place in the Society.\n",
        " are confident of your value for the Dark Lord.\n",
        " are doing fine.\n",
        " should seriously think about the retirement.\n",
        " consider your retirement a fact any unliving day...\n",
    }),
    ({ 
        " should be slowed down for "+ me->query_possessive()+
            " own good.\n",
        " is going to burn out soon.\n",
        " should share the duties with fellow Raiders.\n",
        " serves as an example for the Ringwraiths.\n",
        " proved "+ me->query_possessive()+
            " value in the eyes of the Dark Lord.\n",
        " works hard to be noticed by the Dark Lord.\n",
        " is doing fine.\n",
        " feels uncomfortable with the Nazgul's duties.\n",
        " is totally useless for the Dark Lord with the Nazgul's duties.\n",
    })
 });
 string outcome;
 int i, j, Performance, Index;
 
 
    if ((me == for_obj) && (MORGUL_NAZGUL_MASTER->query_is_nazgul( me )))
    {
        outcome = "";
        i = 0;
    }
    else if (MORGUL_NAZGUL_MASTER->query_is_nazgul( for_obj ) == 2)
    {
        outcome = capitalize( me->query_pronoun() );
        i = 1;
    }
    else
    {
        return "";
    }
    if ((Index = member_array( me->query_real_name(), Nazgul_index )) == -1)
    {
        return "";
    }

    Performance = Current_stats[ Index ];
//DEBUG("Performance = " + Performance);
    if (Performance > WORKOHOLIC)
    {
        j = 0; 
    }
    else if (Performance > OUTSTANDING)
    {
        j = 1; 
    }
    else if (Performance > EXCELLENT)
    {
        j = 2; 
    }
    else if (Performance > VERY_GOOD)
    {
        j = 3; 
    }
    else if (Performance > GOOD)        
    {
        j = 4; 
    }
    else if (Performance > ABOVE_AVERAGE)
    {
        j = 5; 
    }
    else if (Performance > ACCEPTABLE)
    {
        j = 6; 
    }
    else if (Performance > WORRYING)
    {
        j = 7; 
    }
    else if (Performance <= WORRYING)
    {
        j = 8;
    }
    else                        /*Weird. This shouldn't happen.           */
    {
        return " actually unable to pry any further information on your status.\n";
    }        

    outcome += description[i][j];
    return outcome;
}

/*
 * Function name: is_idle
 * Description  : Checks whether a mage's mage activity is below ACCEPTABLE
 *                Normally called from the throne room from do_promote()
 * Arguments    : mixed mage - object pointer of string with a name
 * Return values: -1 in the case of error, 0 if the mage is active (or not
 *                in the roster, 1 if (s)he is idle.
 */
nomask public int is_idle( mixed mage )
{
 int Index;

    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    }
    if ((Index = member_array( mage, Nazgul_index )) == -1)
    {
        return 0;
    }
    if ((Current_stats[Index] >= ACCEPTABLE) || (Current_stats[Index] == 0))
    {
        return 0;
    }
    //return 1;
    return 1;
}

/*
 * Maintenace functions.
 */
public nomask int query_udate( void )
{
    return Update_flag;
}

public nomask void reset_update( void )
{
    Update_flag = 0;
}

public nomask void remote_save( void )
{
    save_object( IDLENESS );
    return;
}

public void relaunch( void ) 
{
    setuid();
    seteuid( getuid() );
    restore_object( IDLENESS );
    return;
}

public void recalculate( void )
{
    calculate_stats();
    save_object( IDLENESS );
    return;
}

/*
 * Function name: create_nazgul_records
 * Description  : Allocates memory to the global variable Nazgul_records
 *                and dumps it to the file IDLENESS. This function is
 *                designed for debuging purposes only.
 */
nomask public void create_nazgul_records( void )
{
 int i,j;
    setuid();
    seteuid( getuid() );

    Nazgul_records = allocate( TRACKED_MAGES );
    for (i=0; i < TRACKED_MAGES; i++)
    {
        Nazgul_records[i] = allocate( RECORD_FIELDS );
        for (j=0; j < RECORD_FIELDS; j++)
        {
            Nazgul_records[i][j] = allocate( GAMES );
        }
    }
    
    Nazgul_index = allocate( TRACKED_MAGES );
    Current_stats = allocate( TRACKED_MAGES );
    save_object( IDLENESS );

    return;
}

/*
 * Function name: query_score
 * Description  : Returns the score of the mage mage accumulated during
 *                Current_game
 * Arguments    : mixed mage - object pointer of string with a name
 * Return values: -1 in the case of error, 0 if the mage is not
 *                in the roster or the desired value.
 */
nomask public int query_score( mixed mage )
{
 int Index;

    if ((mage = mtos(mage)) == NULL)
    {
        return -1;
    }
    if ((Index = member_array( mage, Nazgul_index )) == -1)
    {
        return 0;
    }
    return Nazgul_records[Index][RESULT][Current_game];
}

/*
 * Function name: query_history
 * Description  : Returns the history of the mage mage.
 * Arguments    : mixed mage - object pointer or string with a name
 */
nomask public void query_history( mixed mage )
{
 int Index, i, j, k;
                                /*Format length yields a string 38 chars
                                 *long.                                   */
 string Out, _format = "Game: %2d, length: %2d, score: %4d     ";

    if ((mage = mtos(mage)) == NULL)
    {
        write( "Wrong argument.\n" );
        return;
    }
    if ((Index = member_array( mage, Nazgul_index )) == -1)
    {
        write( capitalize( mage )+ " is not in the roster.\n" );
        return;
    }

    write( capitalize( mage )+ "'s history.\nThe score for each game "+
        "is the number of points per hour averaged over the game length. "+
        "The length is given in hours.\n\n" );
    j = GAMES/ 2;
    if (j* 2 < GAMES)
    {
        k = j+ 1;
    }
    else
    {
        k = j;
    }
    for (i=0;i<j;i++)
    {
        if (i == Current_game)
        {
            Out = sprintf( "Raw points accumulated today: %6d  ",
                Nazgul_records[Index][RESULT][Current_game]  );
            Out += sprintf( _format, i+k, Nazgul_records[Index][TIME][i+k],
                Nazgul_records[Index][RESULT][i+k] );
        }
        else if (i+k == Current_game)
        {
            Out = sprintf( _format, i, Nazgul_records[Index][TIME][i],
                Nazgul_records[Index][RESULT][i] );
            Out += sprintf( "Raw points accumulated today: %6d  ",
                Nazgul_records[Index][RESULT][Current_game]  );
        }
        else
        {
            Out = sprintf( _format, i, Nazgul_records[Index][TIME][i],
                Nazgul_records[Index][RESULT][i] );
            Out += sprintf( _format, i+k, Nazgul_records[Index][TIME][i+k],
                Nazgul_records[Index][RESULT][i+k] );
        }
        write( Out+ "\n" );
    }
    if (k != j)
    {
        if (j == Current_game)
        {
            Out = sprintf( "Raw points accumulated today: %6d  ",
                Nazgul_records[Index][RESULT][Current_game]  );
        }
        else
        {
            Out = sprintf( _format, j, Nazgul_records[Index][TIME][j],
                Nazgul_records[Index][RESULT][j] );
        }
        write( Out+ "\n" );
    }
    write( "\n"+ capitalize( mage )+ "'s current performance score is "+
        Current_stats[Index]+ " points per 24 hours.\n" );
}
