/*
 * The object that handles Minstrel performances at 
 * pre-determined venues.
 *
 * This object handles the success of such performances,
 * the chance of reputation gain, and general xp and 
 * coin payment of minstrel.
 *
 * Arman Kharas, October 2019
 * 
 * Changes:
 * 2020-01-09 - Cotillion
 * - Added a number of return; after the perform object was removed to
 *   fix runtime errors.
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <money.h>
#include "/d/Terel/common/terel_defs.h"
#include "../guild_defs.h"

#define SINGING       "_minstrel_i_singing"
#define HIS(x)        ((x)->query_possessive())

object performer;
string location, songstr, song1, song2, song3;
int loc_size;
int no_repeat = 1;
int perform_score = 0;
int perform_payout = 0;

public void
set_performer(object minstrel, string loc, int size)
{
    performer = minstrel;
    location = loc;
    loc_size = size;
}

public void
set_perform_score(int score, string song)
{
    perform_score += score;
    songstr = song;
}

public string
query_minstrel_performer()
{
    return performer->query_real_name();
}

public void
force_end_performance()
{
    remove_object();
}

void
create_object()
{
    set_name("_minstrel_performance_object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_GET, 1);

    // redundancy in case object gets stuck
    set_alarm(3600.0, 0.0, &force_end_performance());
    set_no_show();
}

/*                  Performance payout formula:
 * 
 * The number of musical renditions you need to give before the performance
 * is complete depends on the size of the establishment... between one to
 * three. The owner of the establishment pays the performer at the end of a 
 * successful performance for each rendition based on how well they performed,
 * measured by the 'chance' value returned for each rendition:
 * 
 *                                     Payout influenced by performer's skills
 *                                 Sup craftsman skills:     Superior guru skills:
 * 1 rendition: Drinking Hole:       120cc - 219cc             200cc - 299cc
 * 2 rendition: Average venue:       240cc - 438cc             400cc - 598cc 
 * 3 rendition: Prominent venue:     480cc - 657cc             800cc - 1196cc 
 * 
 * So the maximum payout for a layman member with max lay skills (superior
 * craftsman) is around:
 * - 1 gold, 6 silver, 3 copper in a dive/drinking hole
 * - 3 gold 6 copper in an average venue
 * - 4 gold 6 silver in a prominent venue
 * 
 * General experience is also provided based on the total payout value using
 * the F_EXP_PERFORM(perform_payout) formula outlined in guild_defs.h
 *
 * A performance can occur every 15 minutes.
 *
 * A performer can only play at a location once every 20 hours.
 */

void
end_performance(object minstrel, string loc)
{
    int *coins = MONEY_SPLIT(perform_payout);
    int expiry;
    string minstrel_name, minstrel_prop;
    string location = file_name(environment(minstrel));
    string payout_text = "The owner of " + capitalize(loc) + " pays you ";

    tell_room(environment(this_object()), "With the completion of " +
        QTPNAME(minstrel)+ " performance, the patrons of " +loc+ 
        " go back to their drinks and conversations.\n", ({ minstrel }));  
    minstrel->catch_tell("With your performance over, the patrons " +
        "of " +loc+ " go back to their drinks and " +
        "conversations.\n");

    if(coins[3])
    {
       MONEY_MAKE_PC(coins[3])->move(minstrel, 1);
    }
    if(coins[2])
    {
       MONEY_MAKE_GC(coins[2])->move(minstrel, 1);
    }
    if(coins[1])
    {
       MONEY_MAKE_SC(coins[1])->move(minstrel, 1);
    }
    if(coins[0])
    {
       MONEY_MAKE_CC(coins[0])->move(minstrel, 1);
    }

    minstrel->catch_tell(payout_text + MONEY_TEXT(coins) + 
        " for your performance.\n");

    environment(this_object())->remove_prop(MIN_PERFORMING);

    expiry = time() + FIFTEEN_MINUTES;
    environment(this_object())->add_prop(NEXT_PERFORM, expiry);

    expiry = time() + TWENTY_HOURS;
    minstrel_name = minstrel->query_real_name();
    minstrel_prop = LAST_PERFORMED + minstrel_name;
    environment(this_object())->add_prop(minstrel_prop, expiry);

    /* Reward the minstrel for the performance. */
    minstrel->add_exp_general(F_EXP_PERFORM(perform_payout));

    /* Check whether any songs should decay from the top 20 */
    PERFORM_MANAGER->master_song_ranking_decay();

    /* Add performance stats for this location */
    PERFORM_MANAGER->increase_venue_level(minstrel, location, 1);

    remove_object();
}

/* Performance functions follow */

// This function is only called for PROMINENT_LOC locations

void
performance_four(object minstrel, string loc)
{
    string minstrel_name = minstrel->query_real_name();
    string * reaction, instrument;
    int chance, difficulty;

    if(perform_score != 3)
    {
        tell_room(environment(this_object()), "The patrons " +
            "of " +loc+  " grumble in disappointment " +
            "as the finale performance by " +QTNAME(minstrel)+ 
            " fails to eventuate.\n", ({ minstrel }));
        minstrel->catch_tell("The patrons of " +loc+  
            " grumble in disappointment as your finale performance " +
            "failed to eventuate.\n");
        environment(this_object())->remove_prop(MIN_PERFORMING);
        remove_object();
        return;
    }

    if(minstrel->query_prop(SINGING))
    {
        set_alarm(2.0, 0.0, &performance_four(minstrel, loc));
        return;
    }

    song3 = songstr;

    if((song3 == song2) || (song3 == song1) )
    {
        tell_room(environment(this_object()), "The patrons " +
            "of " +loc+  " grumble in disappointment " +
            "as the final musical rendition by " +QTNAME(minstrel)+ 
            " is the same as an earlier one. " +QCTPNAME(minstrel)+
            " performance ends ignominiously.\n", ({ minstrel }));
        minstrel->catch_tell("The patrons of " +loc+  
            " grumble in disappointment as your final rendition " +
            "is the same as an earlier one. Your performance ends " +
            "ignominiously, and you'll need to expand your " +
            "reportoire if you want to perform again in such a " +
            "venue.\n");
        environment(this_object())->remove_prop(MIN_PERFORMING);
        remove_object();
        return;
    }

    reaction = PERFORM_MANAGER->query_crowd_reaction(minstrel);
    instrument = minstrel->query_instrument_name();    

    if(!instrument)
    {
        if(present("minstrel_instrument", minstrel))
            instrument = present("minstrel_instrument", 
            minstrel)->short();  
        else
            instrument = "instrument";
    }

    tell_room(environment(this_object()), "After playing a " +
        "rendition of '" +songstr+ "' on " +HIS(minstrel)+ " " +
        instrument+ ", the patrons of " +loc + 
        reaction[1] + "\n", ({ minstrel }));  
    minstrel->catch_tell("After playing a rendition of '" +
        songstr+ "' on your " +instrument+ ", the patrons of " +
        loc+ reaction[0] +"\n");  

    chance = PERFORM_MANAGER->check_performance_chance(minstrel, loc_size);
    difficulty = PERFORM_MANAGER->check_performance_difficulty(minstrel);

    // The total coin payout is a reflection of how well the performer
    // plays based on the chance formula.
    perform_payout += chance;

    PERFORM_MANAGER->check_reputation_increase(minstrel, PROMINENT_LOC,
       chance, difficulty);
    PERFORM_MANAGER->increase_minstrel_mundane(songstr, chance, time());
    end_performance(minstrel, loc);

}

// This function is only called for PROMINENT_LOC and AVERAGE_LOC locations

void
performance_three(object minstrel, string loc)
{
    string minstrel_name = minstrel->query_real_name();
    string * reaction, instrument;
    int chance, difficulty;

    if(perform_score != 2)
    {
        tell_room(environment(this_object()), "The patrons " +
            "of " +loc+  " grumble in disappointment " +
            "as the second set by " +QTNAME(minstrel)+ 
            " fails to eventuate.\n", ({ minstrel }));
        minstrel->catch_tell("The patrons of " +loc+  
            " grumble in disappointment as your next second set " +
            "failed to eventuate.\n");
        environment(this_object())->remove_prop(MIN_PERFORMING);
        remove_object();
        return;
    }

    if(minstrel->query_prop(SINGING))
    {
        set_alarm(2.0, 0.0, &performance_three(minstrel, loc));
        return;
    }

    song2 = songstr;

    if(song1 == song2)
    {
        tell_room(environment(this_object()), "The patrons " +
            "of " +loc+  " grumble in disappointment " +
            "as the second rendition by " +QTNAME(minstrel)+ 
            " is the same as the first. " +QCTPNAME(minstrel)+
            " performance ends ignominiously.\n", ({ minstrel }));
        minstrel->catch_tell("The patrons of " +loc+  
            " grumble in disappointment as your second rendition " +
            "is the same as your first. Your performance ends " +
            "ignominiously, and you'll need to expand your " +
            "reportoire if you want to perform again in such a " +
            "venue.\n");
        environment(this_object())->remove_prop(MIN_PERFORMING);
        remove_object();
        return;
    }

    reaction = PERFORM_MANAGER->query_crowd_reaction(minstrel);
    instrument = minstrel->query_instrument_name();  

    if(!instrument)
    {
        if(present("minstrel_instrument", minstrel))
            instrument = present("minstrel_instrument", 
            minstrel)->short();  
        else
            instrument = "instrument";
    }  

    tell_room(environment(this_object()), "After playing a " +
        "rendition of '" +songstr+ "' on " +HIS(minstrel)+ " " +
        instrument+ ", the patrons of " +loc+ 
        reaction[1] + "\n", ({ minstrel }));  
    minstrel->catch_tell("After playing a rendition of '" +
        songstr+ "' on your " +instrument+ ", the patrons of " +
        loc+ reaction[0] +"\n");  

    chance = PERFORM_MANAGER->check_performance_chance(minstrel, loc_size);
    difficulty = PERFORM_MANAGER->check_performance_difficulty(minstrel);

    // The total coin payout is a reflection of how well the performer
    // plays based on the chance formula.
    perform_payout += chance;

    if(loc_size == AVERAGE_LOC)
    {
        PERFORM_MANAGER->check_reputation_increase(minstrel, AVERAGE_LOC,
            chance, difficulty);
        PERFORM_MANAGER->increase_minstrel_mundane(songstr, chance, time());
        end_performance(minstrel, loc);
        return;
    }

    minstrel->catch_tell("\nThe patrons expectantly wait for " +
        "your next rendition in your performance.\n");
    tell_room(environment(this_object()), "The patrons " +
        "expectantly wait for " +QTPNAME(minstrel)+
        " next rendition in " +HIS(minstrel)+ " performance.\n", 
        ({ minstrel }));
    set_alarm(12.0, 0.0, &performance_four(performer, location));
}

void
performance_two(object minstrel, string loc)
{
    string minstrel_name = minstrel->query_real_name();
    string * reaction, instrument;
    int chance, difficulty;

    if(!perform_score)
    {
        tell_room(environment(this_object()), "The patrons " +
            "of " +loc+  " grumble in disappointment " +
            "as the promised performance by " +QTNAME(minstrel)+ 
            " fails to eventuate.\n", ({ minstrel }));
        minstrel->catch_tell("The patrons of " +loc+  
            " grumble in disappointment as your promised performance " +
            "failed to eventuate.\n");
        environment(this_object())->remove_prop(MIN_PERFORMING);
        remove_object();
        return;
    }

    if(minstrel->query_prop(SINGING))
    {
        set_alarm(2.0, 0.0, &performance_two(minstrel, loc));
        return;
    }

    reaction = PERFORM_MANAGER->query_crowd_reaction(minstrel);
    instrument = minstrel->query_instrument_name(); 

    if(!instrument)
    {
        if(present("minstrel_instrument", minstrel))
            instrument = present("minstrel_instrument", 
            minstrel)->short();  
        else
            instrument = "instrument";
    }         

    tell_room(environment(this_object()), "After playing a " +
        "rendition of '" +songstr+ "' on " +HIS(minstrel)+ " " +
        instrument+ ", the patrons of " +loc+ 
        reaction[1] + "\n", ({ minstrel }));  
    minstrel->catch_tell("After playing a rendition of '" +
        songstr+ "' on your " +instrument+ ", the patrons of " +
        loc+ reaction[0] +"\n");  

    chance = PERFORM_MANAGER->check_performance_chance(minstrel, loc_size);
    difficulty = PERFORM_MANAGER->check_performance_difficulty(minstrel);

    // The total coin payout is a reflection of how well the performer
    // plays based on the chance formula.
    perform_payout += chance;

    if(loc_size == MINOR_LOC)
    {
        PERFORM_MANAGER->check_reputation_increase(minstrel, MINOR_LOC,
            chance, difficulty);
        PERFORM_MANAGER->increase_minstrel_mundane(songstr, chance, time());
        end_performance(minstrel, loc);
        return;
    }

    song1 = songstr;

    minstrel->catch_tell("\nThe patrons expectantly wait for " +
        "your next rendition in your performance.\n");
    tell_room(environment(this_object()), "The patrons " +
        "expectantly wait for " +QTPNAME(minstrel)+
        " next rendition in " +HIS(minstrel)+ " performance.\n", 
        ({ minstrel }));
    set_alarm(12.0, 0.0, &performance_three(performer, location));
}

void
performance_one(object minstrel, string loc)
{
    string minstrel_name = minstrel->query_real_name();
    string local_rep = PERFORM_MANAGER->query_patron_familiarity(minstrel);

    tell_room(environment(this_object()), capitalize(loc)+ 
        " falls silent in anticipation of hearing from " +
        LANG_ART(local_rep)+ " " +local_rep+ " performer.\n", 0, minstrel);  
    minstrel->catch_tell("You feel you have the crowd's " +
        "attention. It is time to perform!\n");  

    environment(this_object())->add_prop(MIN_PERFORMING, minstrel_name);

    set_alarm(10.0, 0.0, &performance_two(performer, location));
}

void
begin_performance(object minstrel, string loc)
{
    string rep = PERFORM_MANAGER->query_reputation_level_desc(minstrel);

    tell_room(environment(this_object()), "The owner " +
        "of " +loc+ " announces to the establishment's " +
        "patrons that the " +rep+ " minstrel " +
        capitalize(minstrel->query_real_name())+ " will " +
        "be performing for them.\n", ({ minstrel }), minstrel); 
    minstrel->catch_tell("The owner of " +loc+ " announces to the " +
        "establishment's patrons that you will be performing for them.\n");   

    set_alarm(4.0, 0.0, &performance_one(performer, location));
}

void init()
{
    ::init();

    if(no_repeat)
    {
        set_alarm(2.0, 0.0, &begin_performance(performer, location));
        no_repeat = 0;
    }

}
