/*
 *  /d/Genesis/census/player_module.c
 *
 *  This module will contain analytics tools for the players themselves
 *  to see what sort of trends are being carried by the people playing
 *  Genesis. 
 *
 *  Created October 2017, by Gorboth (Cooper Sherry)
 */
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <state_desc.h>

#define  TELL_G(x) find_living("gorboth")->catch_msg("DEBUG: " +x+ "\n");

/* Global Variables */
public mapping           Race_Stats = ([]);


/* Prototypes */
public void        init_race_stats();
public int         filter_window(string player, int time_cutoff);
public void        generate_race_stats(int days);
// public string      print_stats();


/*
 * Function name:        init_race_stats
 * Description  :        initialize the race_stats mapping properly
 */
public void
init_race_stats()
{
    Race_Stats = ([]);

    foreach (string title: SD_AV_TITLES)
    {
        Race_Stats += ([ title : ({}) ]);
    }
} /* init_race_stats */


/*
 * Function name:        filter_window
 * Description  :        filter the playerfiles so that only those
 *                       with a timestamp more recent than our cutoff
 *                       are processed.
 * Arguments    :        string player - the player's filename
 *                       int time_cutoff - the timestamp window
 * Returns      :        boolean: 1 - the file is to be used
 *                                0 - the fill is filtered out
 */
public int
filter_window(string player, int time_cutoff)
{
    return (file_time(player) <= time_cutoff);
} /* filter_window */


/*
 * Function name:        generate_race_stats
 * Description  :        populate our Race_Stats mapping with the data
 *                       we need to properly display stats on races, or
 *                       other things.
 *
 * Argumements  :        int days - we only use players who have
 *                         logged as recently as the number of days
 *                         we wish to see. This allows us to see things
 *                         in a given window of time. (i.e. the last
 *                         week, month, year)
 */
public void
generate_race_stats(int days)
{
    int     time_cutoff = time() - (days * 86400);
    string *alphabet = ({ "a","b","c","d","e","f","g","h","i","j",
                          "k","l","m","n","o","p","q","r","s","t",
                          "u","v","w","x","y","z" });
    string *dir_contents = ({});
    string  dir_pathname;
    object  player;
    string  player_name;
    string  player_race;
    int     player_gender;
    string  player_level;
    string *temp_array;
    mapping level_races;

    TELL_G("generate_race_stats called");

    init_race_stats();

    foreach (string letter: alphabet)
    {
TELL_G("letter = " + letter);
        dir_pathname = "/data/players/" + letter + "/";
TELL_G("batch size = " + sizeof(dir_contents));
        dir_contents = filter(get_dir(dir_pathname), filter_window);
TELL_G("dir_pathname = " + dir_pathname);
// TELL_G("batch size = " + sizeof(dir_contents));
        foreach(string the_playerfile : dir_contents)
        {
            player_name = explode(the_playerfile, ".")[0];
            player = SECURITY->finger_player(player_name);
            player_race = player->query_race();
            player_gender = player->query_gender();
            player_level = GET_EXP_LEVEL_DESC(
                               player->query_average_stat(),
                               player_gender);
            level_races = Race_Stats[player_level];

            if (!sizeof(m_indices(level_races)))
            {
                level_races = ([ "dwarf"  : 0,
                                 "elf"    : 0,
                                 "gnome"  : 0,
                                 "goblin" : 0,
                                 "hobbit" : 0,
                                 "human"  : 0, ]);
            }

            level_races[player_race] += 1;
            Race_Stats[player_level] = level_races;
        }
    }

//  dump_array(Race_Stats);
} /* generate_race_stats */
                

/*
 * Function name:        print_stats
 * Description  :        prints the number of players of each
 *                       mortal level currently logged in, and
 *                       calculates the stat ave of them all.
 *                       I stole it from Olorin's workroom.
 * Returns      :        int -- the info
 *
public string
print_stats()
{
    int     st = sizeof(SD_AV_TITLES),
            s,
            i,
            sum;
    object *all = filter(users(), not @ &->query_wiz_level());
    string  msg = "";

    if (!TP->query_wiz_level())
    {
        return 0;
    }

    for (i = 0; i < st; i++)
        msg += sprintf("%-16s %5d\n", 
                       CAP(SD_AV_TITLES[i]),
                       sizeof(filter(all, &operator(==)(SD_AV_TITLES[i]) @
                                     &->query_exp_title())));

    for (i = 0, s = sizeof(all); i < s; i++)
        sum += all[i]->query_average_stat();

    sum /= s;
    msg += "Average stat of all mortals = " + sum;

    msg += " (" + GET_EXP_LEVEL_DESC(sum, 0) + ").\n";

    return msg;
/*
} /* print_stats */