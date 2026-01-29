/*
 *  /d/Sparkle/area/city/obj/wrestling_master.c
 *
 *  This is an object to keep track of the arm-wrestling that goes on in
 *  the lounge of the Sparkle Pub, including betting/rankings, etc. I am doing
 *  it with an object, rather than a data file so that when the game resets,
 *  we are not trying to keep track of a bunch of old data, but also so that
 *  if the room resets we do not lose the data.
 *
 *  The location and code for the wrestling is at:
 *
 *      /d/Sparkle/area/city/rooms/inside/sparkle_pub_lounge.c
 *
 *  Created December 2018, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#pragma no_clone

inherit "/d/Emerald/lib/data_manager";

#include <composite.h>
#include <macros.h>
#include <time.h>
#include "../defs.h"


/* Definitions */
#define            W_DATA         "wrestling_data"
#define            LOUNGE         (INSIDE_DIR + "sparkle_pub_lounge")

/* Global Variables */
public mapping     Victors = ([]);
public string      Current_Day = "";
public mapping     Champion_Totals = ([]);

public void        set_victors(mixed m)      { Victors = m;        }
public mixed       query_victors()           { return Victors;     }
public void        set_current_day(string s) { Current_Day = s;    }
public string      query_current_day()       { return Current_Day; }


/* Prototypes */
public void        create_data_manager();
public void        add_victor(string who, string odds, string loser,
                              int rounds);
public int         streak_check(string who, string loser);
public void        print_victors(object who, object *wrestlers);
public int         sort_victors(string a, string b);
public void        wrestling_data_check(int from_flip = 0);
public void        flip_wrestling_day();
public void        assign_yesterday_champion(string *daily_champion);
public mixed      *current_champion(int from_flip = 0);
public void        generate_data(int i = 20);
public mapping     all_time_record_check(string who = 0, int total = 0,
                                         int u_dog = 0, int rounds = 0,
                                         string loser = 0, int streak = 0);
public void        coin_tally(string which, int amount, string coin_type);
public void        print_monies(object who);
public string      net_haul();
public void        print_columns(mapping champion_map, object who);
public int         sort_champions(string a, string b);
public int         has_been_champion(int who);
public void        tally_betters(string winners);
public int         query_bets_won(string who);


/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    setuid();
    seteuid(getuid());

    set_save_dir(DATA_DIR);
    set_garbage_dir(DATA_DIR + "old/");

    wrestling_data_check();
} /* create_data_manager */


/*
 * Function name:        add_victor
 * Description  :        When someone wins an arm-wrestling match,
 *                       we add them to the mapping of victors, with
 *                       details of their favorite/equal/underdog
 *                       status.
 * Arguments    :        string who    - the victor's name
 *                       string odds   - their likelihood to have won
 *                       string loser  - name of the defeated opponent
 *                       int    rounds - how many rounds the match went
 */
public void
add_victor(string who, string odds, string loser, int rounds)
{
    mapping odds_map = ([ "hopeless"   : 0,
                          "equal"      : 1,
                          "dominating" : 2, ]);
    int    *wins;
    int     streak_num;

    wrestling_data_check();

    if (!Victors[who])
    {
        wins = allocate(3);
    }
    else
    {
        wins = Victors[who];
    }

    if (!pointerp(wins))
    {
        wins = allocate(3);
    }

    wins[odds_map[odds]]++;

    Victors[who] = wins;
    set_info(W_DATA, "victors", Victors);

    streak_num = streak_check(who, loser);

    all_time_record_check(who,
                          wins[0] + wins[1] + wins[2],
                          wins[2],
                          rounds,
                          loser,
                          streak_num);

    wrestling_data_check();
} /* add_victor */


/*
 * Function name:        streak_check
 * Description  :        Check the winning streaks and see
 *                       if this victory grants additional to
 *                       this player's streak, and if this player
 *                       has beaten the top streak. If the loser has
 *                       a win streak, delete it from the streak
 *                       mapping.
 * Arguments    :        string who - the victor's name
 *                       string loser - the loser's name
 * Returns      :        int - the size of their streak
 */
public int
streak_check(string who, string loser)
{
    mapping  win_streaks = get_info(W_DATA, "win_streaks");
    mixed   *current_streak = get_info(W_DATA, "current_streak");
    int      this_streak;

    if (!mappingp(win_streaks))
    {
        win_streaks = ([]);
    }

    this_streak = win_streaks[who];
    this_streak++;

    if (sizeof(current_streak) < 2)
    {
        current_streak = ({ "nobody", 0 });
    }

    set_info(W_DATA, "current_streak", ({ who, this_streak }) );

    if (IN_ARRAY(loser, m_indices(win_streaks)))
    {
        m_delkey(win_streaks, loser);
    }

    win_streaks[who] = this_streak;
    set_info(W_DATA, "win_streaks", win_streaks);

    return this_streak;
} /* streak_check */


/*
 * Function name:        print_victors
 * Description  :        Display a list of the victors and their
 *                       types of wins.
 * Arguments    :        object who - the person to print to
 */
public void
print_victors(object who, object *wrestlers)
{
    int    *victor_wins;
    int     total_wins;
    string  header;
    string  footer;
    string  line;
    string  vic;
    int     tot;
    int     fav;
    int     equ;
    int     und;
    string *challengers = ({ "", "(nobody yet)" });
    mixed  *streak_data = get_info(W_DATA, "current_streak");
    string  streak_who = "(none right now)";
    int     streak_num = 0;
    string  lineup;
    string  dateline;
    string  streakline;
    string  yesterdayline;
    int     i = 0;
    int     ri;
    string  pad;
    string  rank = "  1. ";
    int     rank_offset = 0;
    string *champion_arr = current_champion();
    string *yesterday = get_info(W_DATA, "champ_yesterday");
    string  last_champ = "nobody!";
    string  plural = ((sizeof(yesterday) > 1) ? "s" : "");

    wrestling_data_check();

    if (sizeof(yesterday))
    {
        last_champ = implode(explode(COMPOSITE_WORDS(yesterday),
                     " and "), " & ");

        if (strlen(last_champ) > 44)
        {
            last_champ = "too many to list!";
        }
    }

    foreach (object wrestler: wrestlers)
    {
        challengers[i] = upper_case(capitalize(wrestler->query_real_name()));
        i++;
    }

    if (sizeof(streak_data) > 1)
    {
        streak_num = streak_data[1];
    }

    if (streak_num > 1)
    {
        streak_who = capitalize(streak_data[0]) + " with "
                   + streak_num + " wins!";
    }

    lineup = sprintf("%|25s", ( (strlen(challengers[0]))
               ? challengers[0] + " vs. " + challengers[1]
               : "(nobody yet)"));

    dateline = sprintf("%|75s", "Today is: " + Current_Day + ". Scores reset"
                              + " at midnight Netherworld-time!");
    streakline = sprintf("%|59s", "Current Win-Streak: "
               + capitalize(streak_who));

    yesterdayline = sprintf("%|75s", upper_case(
                    "yesterday's champion" + plural + ": " + last_champ));

    header = "       .------------------------------------------------------"
           + "----------.\n"
           + "      |       Current Challengers:     "
           + lineup + "         |\n"
           + "  .-----------------------------------------------------------"
           + "--------------.\n"
           + " |             Today's Glorious Arm-Wrestling Victors So-Far: "
           + "               |\n"
           + " | /----------------------------------------------------------"
           + "-------------\\ |\n"
           + " | | Ranked As:    Total Wins:    As Favorite:   As Equal:   "
           + "As Underdog:  | |\n"
           + " | |=========================================================="
           + "=============| |\n";

    footer = " | \\---------------------------------------------------------"
           + "--------------/ |\n"
           + " |" + yesterdayline + "|\n"
           + " |" + dateline + "|\n"
           + " |                                                            "
           + "          __   |\n"
           + " |        " + streakline + "-.:-.-  |\n"
           + "  `-----------------------------------------------------------"
           + "--------------'\n"
           + "            Beneath the board is a small list of all-time"
           + " records.\n"
           + "                Beneath that is a chart of betting payouts.\n"
           + "            Something is also scrawled in the corner of the"
           + " board.\n";

    who->catch_tell(header);
    i = 0;

    foreach(string this_victor : sort_array(m_indices(Victors), sort_victors))
    {
        i++;
        ri = i + rank_offset;
        pad = " " * abs(3 - strlen(ri + ""));

        /* The idea here is that if more than one person is tied for
         * the top rank, we display all of those people as rank 1.
         * and then begin the numbering at 2. for the next person
         * to be displayed after all of those who are tied. The
         * rank_offset var takes care of this.
         */
        if (i > 1 && IN_ARRAY(this_victor, champion_arr))
        {
            rank = "     ";
            rank_offset--;
        }
        else
        {
            rank = pad + ri + ". ";
        }        

        victor_wins = Victors[this_victor];
        vic = capitalize(this_victor);
        fav = victor_wins[0];
        equ = victor_wins[1];
        und = victor_wins[2];
        tot = fav + equ + und;

        line = " | | " + rank
             + sprintf("%-14s", capitalize(vic))
             + sprintf("%5d", tot)
             + sprintf("%12d", fav)
             + sprintf("%13d", equ)
             + sprintf("%15d", und)
             + "      | |\n";

        who->catch_tell(line);
    }

    if (!i)
    {
        who->catch_tell(" | |" + sprintf("%|71s",
            "(who will be the first to <challenge> the room?)")
          + "| |\n");
    }

    who->catch_tell(footer);

    wrestling_data_check();
} /* print_victors */


/*
 * A sort filter for listing victors in rank order according to total
 * victories.
 */
public int
sort_victors(string a, string b)
{
    int     a_total = Victors[a][0] + Victors[a][1] + Victors[a][2];
    int     b_total = Victors[b][0] + Victors[b][1] + Victors[b][2];

    return b_total - a_total;
} /* sort_normal */


/*
 * Function name:        wrestling_data_check
 * Description  :        make sure our data is up to date for the
 *                       wrestling master, securing variable values
 *                       and making sure the day does not need to
 *                       be flipped.
 * Arguments    :        int from_flip = 0; (default)
 *                         flag as true if the call comes from the
 *                         flip_wrestling_day function, to avoid
 *                         infinite recursion.
 */
public void
wrestling_data_check(int from_flip = 0)
{
    string  current_day_data = get_info(W_DATA, "current_day");

    Current_Day = ctime(time())[0..9];

    if (!strlen(current_day_data))
    {
        set_info(W_DATA, "current_day", Current_Day);
    }

    if (current_day_data != Current_Day)
    {
        if (!from_flip)
        {
            flip_wrestling_day();
        }
    }

    Victors = get_info(W_DATA, "victors");

    if (!Victors)
    {
        Victors = ([]);
    }
} /* wrestling_data_check */


/*
 * Function name:        flip_wrestling_day
 * Description  :        perform the cleanup/init necessary
 *                       when we pass midnight RL and get a new
 *                       day going. Here, we wipe the scoreboard
 *                       for a new day's efforts by players.
 * Arguments    :        int warning - We sometimes want to trigger
 *                                     this function ahead of time
 *                                     to give players in the lounge
 *                                     a warning of an impending flip.
 *                                     If so, the int passed should
 *                                     be the number of minutes left
 *                                     before midnight.
 */
public void
flip_wrestling_day()
{
    mapping  champion_map;
    int      champion_wins = 0;
    string  *daily_champion;

    wrestling_data_check(1);

    Current_Day = ctime(time())[0..9];
    set_info(W_DATA, "current_day", Current_Day);

    champion_map = get_info(W_DATA, "champions");

    if (!mappingp(champion_map))
    {
        champion_map = ([]);
    }

    daily_champion = current_champion(1);

    foreach (string this_champion : daily_champion)
    {
        champion_wins = champion_map[this_champion];
        champion_wins++;
        champion_map[this_champion] = champion_wins;
    }

    set_info(W_DATA, "champions", champion_map);

    assign_yesterday_champion(daily_champion);

    set_info(W_DATA, "current_streak", ({}) );
    set_info(W_DATA, "win_streaks", ([]) );
    set_info(W_DATA, "paid_monies", ([]) );
    set_info(W_DATA, "taken_monies", ([]) );
    set_info(W_DATA, "bets_won", ([]) );

    Victors = ([]);
    set_info(W_DATA, "victors", Victors);
} /* flip_wrestling_day */


/*
 * Function name:        assign_yesterday_champion
 * Description  :        set yesterday's champ, but be sure
 *                       not to overwrite the person(s) if the call
 *                       gets made one time too many (and too late)
 * Arguments    :        string * daily_champion - the champion(s)
 */
public void
assign_yesterday_champion(string *daily_champion)
{
    int    right_now = time();
    int    last_assigned = get_info(W_DATA, "yesterday_assigned");
    int    time_elapsed = right_now - last_assigned;
    int    i = 0;

    foreach(string s : daily_champion)
    {
        i++;
    }

    /* Make sure it was assigned more than 30 minutes ago */
    if (right_now - last_assigned < 1800)
    {
        return;
    }

    set_info(W_DATA, "yesterday_assigned", right_now);
    set_info(W_DATA, "champ_yesterday",
        ((sizeof(daily_champion)) ? daily_champion
                                  : ({ "nobody!" }) ) );
} /* assign_yesterday_champion */


/*
 * Function name:        current_champion
 * Description  :        Determine the current champion(s) of the
 *                       daily arm wrestling totals.
 * Arguments    :        int from_flip = 0; (default)
 *                         flag as true if the call comes from the
 *                         flip_wrestling_day function, to avoid
 *                         infinite recursion.
 * Returns      :        string array - the names of the champions.
 *                                      There will only be more than
 *                                      one in the case of a tie.
 *                       int 0 - if no champions
 */
public mixed *
current_champion(int from_flip = 0)
{
    string  *sorted_victors;
    string  *daily_champion = ({});
    int      i = 0;
    int      done = 0;
    string   this_victor;
    int     *wins_arr;
    int      this_total = 0;
    string   next_victor;
    int      next_total = 0;

    wrestling_data_check(from_flip);

    sorted_victors = sort_array(m_indices(Victors), sort_victors);

    if (!sizeof(sorted_victors))
    {
        return 0;
    }

    if (sizeof(sorted_victors) == 1)
    {
        return sorted_victors;
    }

    while (!done)
    {
        this_victor = sorted_victors[i];
        wins_arr = Victors[this_victor];

        if (sizeof(wins_arr) > 2)
        {
            this_total = wins_arr[0] + wins_arr[1] + wins_arr[2];
        }

        daily_champion += ({ this_victor });

        if (sizeof(sorted_victors) > (i + 1))
        {
            i++;

            next_victor = sorted_victors[i];
            wins_arr = Victors[next_victor];

            if (sizeof(wins_arr) > 2)
            {
                next_total = wins_arr[0] + wins_arr[1] + wins_arr[2];
            }

            if (this_total > next_total)
            {
                done = 1;
            }
        }
        else
        {
            done = 1;
        }
    }

    return daily_champion;
} /* current_champion */



/*
 * Function name:        generate_data
 * Description  :        create some false data to test the lists
 * Arguments    :        int i - how many names to add?
 */
public void
generate_data(int i = 20)
{
    int      n;
    string  *pre_name = ({ "reg", "cor", "van", "rin", "sal", "tok",
                           "fard", "shlee", "pin" });
    string  *post_name = ({ "ington", "derbury", "ers", "inger",
                            "esto", "lard" });
    string  *used_names = ({});
    string   this_name;
    mapping  bank_mapping = get_info(W_DATA, "victors");
    mapping  champion_mapping = get_info(W_DATA, "champions");
    int     *wins_array = ({ 0, 0, 0 });

    if (!sizeof(m_indices(bank_mapping)))
    {
        bank_mapping = ([]);
    }

    if (!sizeof(m_indices(champion_mapping)))
    {
        champion_mapping = ([]);
    }

    while(i)
    {
        wins_array  = ({ random(40), random(40), random(40) });
        this_name = one_of_list(pre_name) + one_of_list(post_name);

        while (IN_ARRAY(this_name, used_names))
        {
            this_name = one_of_list(pre_name) + one_of_list(post_name);
        }

        bank_mapping += ([ this_name : wins_array ]);
        champion_mapping += ([ this_name : random(10) + random(20) ]);
        i--;
    }

    set_info(W_DATA, "champions", champion_mapping);
    set_info(W_DATA, "victors", bank_mapping);
} /* generate_data */


/*
 * Function name:        all_time_record_check
 * Description  :        Check our all-time records to see if any
 *                       have been broken.
 * Arguments    :        string who   - the victor
 *                       int total    - total victories so far today
 *                       int u_dog    - underdog victories so far today
 *                       int rounds   - how many rounds the match lasted
 *                       string loser - who the victor defeated
 *                       int streak   - current winning streak
 * Returns      :        mapping      - the mapping value
 */
public mapping
all_time_record_check(string who = 0, int total = 0, int u_dog = 0,
                      int rounds = 0, string loser = 0, int streak = 0)
{
    mapping  all_time_map = get_info(W_DATA, "all_time_records");
    mixed   *all_time_total;
    mixed   *all_time_u_dog;
    mixed   *all_time_rounds;
    mixed   *all_time_streak;
    int      new_records = 0;
    string   vs_txt;

    if (!all_time_map)
    {
        all_time_map = ([]);

        all_time_map["total"] = ({ "Pharazon", 5 });
        all_time_map["u_dog"] = ({ "Carlsan", 3 });
        all_time_map["rounds"] = ({ "Fatty vs. Marvin", 10 });
        all_time_map["streak"] = ({ "Jadestone", 4 });

        set_info(W_DATA, "all_time_records", all_time_map);
    }

    all_time_total = all_time_map["total"];
    all_time_u_dog = all_time_map["u_dog"];
    all_time_rounds = all_time_map["rounds"];
    all_time_streak = all_time_map["streak"];

    if (total > all_time_total[1])
    {
        LOUNGE->new_all_time_record("total", who, total);
        all_time_map["total"] = ({ capitalize(who), total });
        new_records++;
    }

    if (u_dog > all_time_u_dog[1])
    {
        LOUNGE->new_all_time_record("u_dog", who, u_dog);
        all_time_map["u_dog"] = ({ capitalize(who), u_dog });
        new_records++;
    }

    if (rounds > all_time_rounds[1])
    {
        vs_txt = capitalize(who) + " vs. " + capitalize(loser);

        LOUNGE->new_all_time_record("rounds", vs_txt, rounds);
        all_time_map["rounds"] = ({ vs_txt, rounds });
        new_records++;
    }

    if (streak > all_time_streak[1])
    {
        LOUNGE->new_all_time_record("streak", who, streak);
        all_time_map["streak"] = ({ who, streak });
        new_records++;
    }

    if (new_records)
    {
        set_info(W_DATA, "all_time_records", all_time_map);
    }

    return all_time_map;
} /* all_time_record_check */


/*
 * Function name:        query_victories
 * Description  :        Tell us how many victories a given player
 *                       has so far today.
 * Arguments    :        string who - the player to check
 *                       string which - which type of victory:
 *                           - "total"    - all combined (default)
 *                           - "favorite" - as favorite
 *                           - "equal"    - as equal
 *                           - "udog"     - as underdog
 * Returns      :        int - the number of victories
 */
public int
query_victories(string who, string which = "total")
{
    int     *victor_wins = Victors[who];
    int      fav;
    int      equ;
    int      und;
    int      tot;
    mapping  m;
    int      victories;

    if (!IN_ARRAY(who, m_indices(Victors)))
    {
        return 0;
    }

    fav = victor_wins[0];
    equ = victor_wins[1];
    und = victor_wins[2];
    tot = fav + equ + und;
    m = ([ "favorite" : fav,
           "equal"    : equ,
           "udog"     : und,
           "total"    : tot
        ]);
    victories = m[which];

    return victories;
} /* query_victories */


/*
 * Function name:        coin_tally
 * Description  :        We track how much the house pays out and takes
 *                       in here.
 * Arguments    :        string which     - "paid" or "taken"
 *                       int amount       - how many coins
 *                       string coin_type - which coin type
 */
public void
coin_tally(string which, int amount, string coin_type)
{
    mapping  money_arr = get_info(W_DATA, which + "_monies");
    mapping  this_arr = ([ coin_type : amount ]);
    int      gcoins = 0;
    int      pcoins = 0;

    if (!sizeof(m_indices(money_arr)))
    {
        money_arr = ([ "gold" : 0, "platinum" : 0 ]);
    }

    gcoins = money_arr["gold"] + this_arr["gold"];
    pcoins = money_arr["platinum"] + this_arr["platinum"];

    money_arr = ([ "gold" : gcoins, "platinum" : pcoins ]);
    set_info(W_DATA, which + "_monies", money_arr);
} /* coin_tally */


/*
 * Function name:        print_monies
 * Description  :        Print out a list of how much monies have been
 *                       paid out (for players) and taken in (wizinfo
 *                       only) by the house.
 * Arguments    :        object who - who to print to
 *
 * Nota Bene: this function best viewed at > 80 screenwidth (bleh)
 */
public void
print_monies(object who)
{
    mapping  taken_monies = get_info(W_DATA, "taken_monies");
    mapping  paid_monies = get_info(W_DATA, "paid_monies");
    int      gcoins = 0;
    int      pcoins = 0;
    int      gnet;
    int      pnet;
    string   header;
    string   footer;
    string   taken_txt;
    string   net_txt;
    string   border = "   | |  ::|\n";
    string   blank;

    blank = 
        "                                                                | |  ::|\n";
    header = 
        "                                                                | |  ::|\n"
      + "                                                                | |  ::|\n"
      + "                                     TODAY'S HAUL:              | |  ::|\n"
      + "                               ------------------------         | |  ::|\n";

    footer = 
        "_______________________________________________________________/  |  ::|\n"
      + "__________________________________________________________________|_.='\n\n\n"
      + "The above lines of writing are scrawled in the corner of the"
      + " board.\n\n"
      + "You also notice a tally of champions written on a long scroll"
      + " nailed to the wall.\n";

    if (!sizeof(m_indices(paid_monies)))
    {
        paid_monies = ([ "gold" : 0, "platinum" : 0 ]);
    }

    gcoins = paid_monies["gold"];
    pcoins = paid_monies["platinum"];
    gnet -= gcoins;
    pnet -= pcoins;

    who->catch_tell(header);

    who->catch_tell(
        sprintf("%61s", "Payouts to betters: "
          + sprintf("%,d", pcoins) + " plats, "
          + sprintf("%,d", gcoins) + " gold") + border);
    who->catch_tell(blank);

    if (!sizeof(m_indices(taken_monies)))
    {
        taken_monies = ([ "gold" : 0, "platinum" : 0 ]);
    }

    gcoins = taken_monies["gold"];
    pcoins = taken_monies["platinum"];
    gnet = gcoins - paid_monies["gold"];
    pnet = pcoins - paid_monies["platinum"];

    taken_txt = ((who->query_wiz_level()) ? 
        "Today's coins taken in: "
          + sprintf("%,d", pcoins) + " plats, "
          + sprintf("%,d", gcoins) + " gold" :
        "(the rest is odd illegible scrawl)");

    who->catch_tell(sprintf("%61s", taken_txt) + border);
    who->catch_tell(blank);

    net_txt = ((who->query_wiz_level()) ? 
        "Net for the house: "
          + sprintf("%,d", pnet) + " plats, "
          + sprintf("%,d", gnet) + " gold" :
        "~-::-^-,.-~~-|3.--<.-;'-~::.-'`.");

    who->catch_tell(sprintf("%61s", net_txt) + border);
    who->catch_tell(footer);

} /* print_monies */


/*
 * Function name:        net_haul
 * Description  :        Calculate and return a string of the
 *                       total haul of the current day's betting.
 * Returns      :        string - the haul description
 */
public string
net_haul()
{
    mapping  taken_monies = get_info(W_DATA, "taken_monies");
    mapping  paid_monies = get_info(W_DATA, "paid_monies");
    int      gcoins = 0;
    int      pcoins = 0;
    int      gnet;
    int      pnet;

    if (!sizeof(m_indices(paid_monies)))
    {
        paid_monies = ([ "gold" : 0, "platinum" : 0 ]);
    }

    gcoins = paid_monies["gold"];
    pcoins = paid_monies["platinum"];
    gnet -= gcoins;
    pnet -= pcoins;

    if (!sizeof(m_indices(taken_monies)))
    {
        taken_monies = ([ "gold" : 0, "platinum" : 0 ]);
    }

    gcoins = taken_monies["gold"];
    pcoins = taken_monies["platinum"];
    gnet = gcoins - paid_monies["gold"];
    pnet = pcoins - paid_monies["platinum"];

    return "Net for the house: "
          + sprintf("%,d", pnet) + " plats, "
          + sprintf("%,d", gnet) + " gold\n";
} /* net_haul */


/*
 * Function name:        print_columns
 * Description  :        Print a double-column alphabetized list of
 *                       a given array
 * Arguments    :        mapping champion_map - the mapping of champions
 *                                              and their number of times
 *                       object who - who to print it to
 */
public void
print_columns(mapping champion_map, object who)
{
    string  column1;
    string  column2;
    string *daily_champs = m_indices(champion_map);
    string  c_total;
    int     i,
            n,
            odd_true,
            half;

    /* Lets rank the array of champion's names by total times being
     * champion. */
    Champion_Totals = champion_map;
    daily_champs = sort_array(daily_champs, sort_champions);

    /* Now we determine the length of our columns and whether they are
     * equal, or if one is longer than the other.
     */
    n = sizeof(daily_champs);
    half = n / 2;
    odd_true = (n % 2 == 1);

    if (n)
    {
        for (i = 0; i < half + odd_true; i++)
        {
            c_total = sprintf("%,4d", champion_map[daily_champs[i]])
                    + " - ";
            column1 = c_total + capitalize(daily_champs[i]);
            column2 = "       ";

            if (!i)
            {
                column1 = upper_case(column1);
            }

            if (half > i)
            {
                /* This is a bit tricky. We have to know if the size
                 * of the list is odd. Since we are printing two columns,
                 * we want to begin the second column just past the
                 * halfway point (for correct ranking). If it
                 * is odd in length, though, we want to go one more
                 * place past that.
                 */
                c_total = sprintf("%,4d", champion_map[daily_champs[
                            i + half + odd_true]]) + " - ";
                column2 = c_total + capitalize(
                              daily_champs[i + half + odd_true]);
            }

            /* All set. So lets print out this line! */
            who->catch_tell("    |        " + sprintf("%|49s",
                sprintf(" %-19s            %-19s",
                column1, column2,)) +  "           |\n");
        }
    }
    else /* Nothing to list. */
    {
        who->catch_tell(sprintf("%|80s",
        "|                   (The scroll is currently blank)       "
      + "             |\n"));
    }
} /* print_columns */


/*
 * A sort filter for listing champions in rank order according to
 * number of times they have achieved it.
 */
public int
sort_champions(string a, string b)
{
    /* quick sanity check */
    if (!mappingp(Champion_Totals))
    {
        Champion_Totals = ([]);
    }

    return Champion_Totals[b] - Champion_Totals[a];
} /* sort_normal */


/*
 * Function name:        print_champions
 * Description  :        Show a list of the people who have become
 *                       daily champion, sorted by the number of times
 *                       they have done it.
 */
public void
print_champions()
{
    object  who = this_player();
    string  header;
    string  footer;
    mapping champion_map = get_info(W_DATA, "champions");

    header = "  _______________________________________________________________________\n"
           + "/______________________________________________________________________/ \\\n"
           + "   \\                                                                      \\\n" 
           + "    |  (+)     THE GLORIOUS END-OF-DAY CHAMPIONS OF ARM-WRESTLING     (+)  |\n"
           + "    |             (ranked by how many times they've been champ)            |\n"
           + "    |  ==================================================================  |\n"
           + "    |                                                                      |\n";

    footer = "    |                                                                     /__\n"
           + "   /                                                                     / /_\\\n"
           + "  |                                                                     | _\\//\n"
           + "   \\_____________________________________________________________________\\__/\n";

    who->catch_tell(header);
    print_columns(champion_map, who);
    who->catch_tell(footer);
} /* print_champions */


/*
 * Function name:        has_been_champion
 * Description  :        see if a given player has ever been a champion
 *                       at the end of an arm-wrestling day.
 * Arguments    :        string who - the player to check
 * Returns      :        int - the number of times as champion
 */
public int
has_been_champion(int who)
{
    mapping  champion_map = get_info(W_DATA, "champions");
    int      who_total;

    if (!mappingp(champion_map))
    {
        return 0;
    }

    return champion_map[who];
} /* has_been_champion */


/*
 * Function name:        tally_betters
 * Description  :        update the data on the number of times people
 *                       have won bets each day.
 * Arguments    :        string winners - the array of names of people
 *                                        who just won a bet.
 */
public void
tally_betters(string winners)
{
    mapping  bets_map = get_info(W_DATA, "bets_won");
    int      bets_won;

    if (!bets_map)
    {
        bets_map = ([]);
    }

    foreach(string winner : winners)
    {
        bets_won = bets_map[winner] + 1;
        bets_map[winner] = bets_won;
    }

    set_info(W_DATA, "bets_won", bets_map);
} /* tally_betters */


/*
 * Function name:        query_bets_won
 * Description  :        Show us how many bets a given player has won
 *                       today.
 * Arguments    :        string who - the player to check for
 * Returns      :        int - the number of bets won
 */
public int
query_bets_won(string who)
{
    mapping  bets_won = get_info(W_DATA, "bets_won");

    if (!mappingp(bets_won))
    {
        return 0;
    }

    return bets_won[who];
} /* query_bets_won */


/*
 * Function name:        print_betters
 * Description  :        provide a list of the number of people who
 *                       have won bets so far today.
 * Arguments    :        object who - the player to print to
 */
public void
print_betters(object who)
{
    mapping  bets_map = get_info(W_DATA, "bets_won");
    string  *winners = sort_array(m_indices(bets_map));

    who->catch_tell("Betting winners today:\n"
                  + "======================\n");

    foreach(string winner : winners)
    {
        who->catch_tell(sprintf("%15s", capitalize(winner))
                      + sprintf("%5d", bets_map[winner]) + "\n");
    }
} /* print_betters */
