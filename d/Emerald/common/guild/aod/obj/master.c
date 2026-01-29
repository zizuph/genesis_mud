/*
 *  /d/Emerald/common/guild/aod/obj/master.c
 *
 *  This is the master file for the Army of Darkness guild in Emerald. It
 *  controls many aspects of the guild, including the save files for
 *  counting the number of skulls a player has collected.
 *
 *  Copyright (c) March 2006, by Cooper Sherry (Gorboth)
 *      Special thanks to: Raven and Mercade
 *
 * Changes:
 * Cotillion - 2020-02-23
 *  - Massive rewrite of all sorting functions to cut down on CPU usage.
 */
#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/d/Emerald/lib/data_manager";
inherit "/d/Genesis/lib/sorted_list";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "../defs.h"
#include "../aod_titles.h"
#include <language.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include <time.h>


/* Global Variables */
public string  *Skull_Accounts = ({ });
public string  *Races = ({ "Human", "Elf", "Hobbit", "Dwarf", "Gnome" });
public mapping  Accounts = ([ ]); // stores all and members_only accounts
public int      Accounts_updated = 1;

/* Prototypes */
public void    create_data_manager();
public int     deposit_skull(mixed who, string skulltype, int amount);
public int     collect_skull(mixed who, string skulltype, int amount);
public int     query_skull_total(object player, int sack = 1);
public void    print_skull_list(object player, int sack = 1);
public void    print_total_line(object player, int line);
public int     check_leader_update(int assign_positions = 0);
public void    print_big_list(object player);
public void    print_particular_list(string type, object player,
                                     int length = 0, int members = 0);
public mixed   scan_accounts(int members_only = 0);
public int     query_guild_total(string race = "total");
public int     compute_title(object player);
public int     set_join_age(mixed who);
public int     membership_duration(mixed who);
public int     skulls_per_hour(mixed who);
public void    print_member_list(object player);
public void    aod_who_list(mixed player);
public int     query_productivity(mixed player);
public void    display_worthless(object player);
public void    set_membership_status(mixed player, int aod_status);
public int     query_membership_status(mixed player);
public string *query_sorted_totals(string race, int members_only = 1);
public int     is_ogre(object who);
public void    tell_ogres(string arg, int darktell = 0);
public void    check_milestones(int preguild, int preplayer, object player, int oldrank, int preoffense, int preadv_offense, int predefense, int preelite);
public void    write_milestone(string mtxt, object mwho);
public void    refresh_sorted_totals();

public mixed   query_skull_accounts() { return Skull_Accounts; }
// Used to keep track of whether the All_Accounts variable needs to be refreshed
public int     query_accounts_updated() { return Accounts_updated; }
public void    set_accounts_updated(int updated = 1) { Accounts_updated = updated; }
// Used to keep track of whether Sorted_data variable needs to be refreshed

/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    set_save_dir(AOD_SAVE_DIR);
    set_garbage_dir(AOD_SAVE_DIR + "old/");

    refresh_sorted_totals();
} /* create_data_manager */


/*
 * Function name:        deposit_skull
 * Description  :        deposit the correct amount to the skull count of a
 *                       particular race for the player
 * Arguments    :        mixed who        - the player,
 *                       string skulltype - the race of the skull,
 *                       int amount       - the number deposited
 * Returns      :        1 - successfully written,
 *                       0 - fail?
 */
public int
deposit_skull(mixed who, string skulltype, int amount)
{
    string number_desc,
           skull_desc = " skulls";
    int    previous_amount = 0;

    if (skulltype == "Other")
    {
        skulltype = "Miscellaneous";
    }

    switch(amount)
    {
        case 1:
            number_desc = "a single ";
            skull_desc = " skull";
            break;
        case 2:
            number_desc = "a couple of ";
            break;
        case 3..6:
            number_desc = "a few ";
            break;
        case 7..19:
            number_desc = "a bunch of ";
            break;
        case 20..49:
            number_desc = "dozens of ";
            break;
        case 50..99:
            number_desc = "a whole slew of ";
            break;
        default:
            number_desc = "a gigantic cascade of ";
            break;
    }

    if (amount)
    {
        who->catch_tell(number_desc + lower_case(skulltype)
          + skull_desc + ", ");
    }

    if (skulltype == "Miscellaneous")
    {
        skulltype = "Other";
    }

    if (previous_amount = get_info(who, skulltype))
    {
        amount += previous_amount;
    }

    set_info(who, "Sack-" + skulltype, 0);
    set_info(who, skulltype, amount);
    set_info(who, "Total", query_skull_total(who, 0));
    return amount;
} /* deposit_skull */


/*
 * Function name:        collect_skull
 * Description  :        collect the correct amount to the skull count of a
 *                       particular race for the player's sack
 * Arguments    :        mixed who        - the player,
 *                       string skulltype - the race of the skull,
 *                       int amount       - the number collected, default
 *                                          is 1.
 * Returns      :        1 - successfully written,
 *                       0 - fail?
 */
public int
collect_skull(mixed who, string skulltype, int amount = 1)
{
    int    previous_amount = 0;

    if (previous_amount = get_info(who, skulltype))
    {
        amount += previous_amount;
    }

    return set_info(who, skulltype, amount);
} /* collect_skull */


/*
 * Function name:        query_skull_total
 * Description  :        determine the total amount of skulls that the
 *                       player has either collected in their sack, or
 *                       deposited to the repository.
 * Arguments    :        mixed player - the player to check
 *                       int sack - true if we are checking the sack
 *                                  rather than the repository (default)
 * Returns      :        int - the numnber of skulls
 */
public int
query_skull_total(mixed player, int sack = 1)
{
    string s = "";

    if (sack)
    {
        s = "Sack-";
    }

    return   get_info(player, s + "Other")
           + get_info(player, s + "Human")
           + get_info(player, s + "Elf")
           + get_info(player, s + "Hobbit")
           + get_info(player, s + "Dwarf")
           + get_info(player, s + "Gnome");
} /* query_skull_total */


/*
 * Function name:        print_skull_list
 * Description  :        show a list of skulls either in the sack or in
 *                       the repository
 * Arguemnts    :        object player - who's file to search
 *                       int sack - true if we want to check the contents
 *                                  of the sack (true by default)
 */
public void
print_skull_list(object player, int sack = 1)
{
    string  s = "";

    if (!sack)
    {
        write("Your skull deposits now total:\n\n");
    }
    else
    {
        write("Your sack contains the following skulls:\n\n");
        s = "Sack-";
    }

    write("\tHuman:\t  "  + sprintf("%,d",
            get_info(player, s + "Human")) + "\n"
        + "\tElf:\t  "    + sprintf("%,d",
            get_info(player, s + "Elf")) + "\n"
        + "\tHobbit:\t  " + sprintf("%,d",
            get_info(player, s + "Hobbit")) + "\n"
        + "\tDwarf:\t  "  + sprintf("%,d",
            get_info(player, s + "Dwarf")) + "\n"
        + "\tGnome:\t  "  + sprintf("%,d",
            get_info(player, s + "Gnome")) + "\n"
        + "\tOther:\t  "  + sprintf("%,d",
            get_info(player, s + "Other")) + "\n\n"
        + "\tTotal:\t  "  + sprintf("%,d",
            query_skull_total(player, sack)) + "\n");

    return;
} /* print_skull_list */

/*
 * Function name:        print_total_line
 * Description  :        Lay out the Readerboard for members of the Army
 *                       of Darkness. This displays an at-a-glance overview
 *                       of the current collection leaders for each race.
 * Arguments    :        object player - the person who will see the
 *                                       output.
 *                       int    line   - the line number we are printing
 */
public void
print_total_line(object player, int line)
{
    string   format = "%-14s  %-14s  %-14s  %-14s  %-14s\n";
    string  *races  = ({ "human", "elf", "hobbit", "dwarf", "gnome" });
    int      tmpvar;
    mixed   *results_array = allocate(5),
            *human_array,
            *elf_array,
            *hobbit_array,
            *dwarf_array,
            *gnome_array,
            *races_arrays;
    int      i;

    human_array  = query_sorted_totals("human",  1);
    elf_array    = query_sorted_totals("elf",    1);
    hobbit_array = query_sorted_totals("hobbit", 1);
    dwarf_array  = query_sorted_totals("dwarf",  1);
    gnome_array  = query_sorted_totals("gnome",  1);

    races_arrays = ({ human_array,
                      elf_array,
                      hobbit_array,
                      dwarf_array,
                      gnome_array
                   });

    for (i = 0; i < 5; i++)
    {
        if (sizeof(races_arrays[i]) > (line - 1))
        {
            if (!strlen(races_arrays[i][line - 1]))
            {
                results_array[i] = line + ". " + "  ---";
            }
            else
            {
                results_array[i] = line + ". "
                  + capitalize(races_arrays[i][line - 1]);
            }
        }
        else
        {
            results_array[i] = line + ". " + "  ---";
        }
    }

    player->catch_tell(sprintf(format,
                               results_array[0],
                               results_array[1],
                               results_array[2],
                               results_array[3],
                               results_array[4]));
} /* print_total_line */


/*
 * Function name:        print_particular_list
 * Description  :        Display the top five ranking in a single
 *                       category of skulls only.
 * Arguments    :        string type   - the category to display
 *                       object player - the player to display to
 *                       int length    - the length we want the list to
 *                                       be (e.g. top 5 only)
 *                                     - default = 0 (display entire list)
 *                       int members   - true if we only want to display
 *                                       current members of the guild
 *                                     - default = 0
 */
public void
print_particular_list(string type, object player, int length = 0,
                      int members = 0)
{
    string  *person = query_sorted_totals(type, members);
    int      i,
             n = length;
    string   harvest_txt = "",
             paren1,
             paren2;

    if (members)
    {
        harvest_txt = " by existing Ogres";
    }

    if (!length ||
         length > sizeof(person))
    {
        n = sizeof(person);
    }

    /* We'll recycle the variable here. In this check we are going to
     * see if the top person in the count is actually a zero value for
     * this collection type. If so, we will want to print the proper
     * message later on.
     */
    if (sizeof(person))
    {
        if (get_info(person[i], capitalize(type)) == 0)
        {
            members = -1;
        }
    }

    if (type == "hourly")
    {
        player->catch_tell("\n" + sprintf("%|80s",
            "Skulls Per Hour Rankings:\n"));
        player->catch_tell(sprintf("%|80s",
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"));

        if (!sizeof(person))
        {
            player->catch_tell(sprintf("%|80s", "There are no"
              + " active collecters for the Harvest!\n"));
        }

        for (i = 0; i < n; i++)
        {
            if (query_membership_status(person[i]))
            {
                paren1 = " ";
                paren2 = "";
            }
            else
            {
                paren1 = "(";
                paren2 = ")";
            }

            if (skulls_per_hour(person[i]) > 0)
            {
                player->catch_tell("\t\t\t" + sprintf("%5s %-12s %-20s",
                    (i+1) + ".", paren1 + capitalize(person[i])
                  + paren2, sprintf("%,d", skulls_per_hour(person[i]))
                  + "\n"));
            }
            else if (n == 1)
            {
                player->catch_tell(sprintf("%|80s", "There are no"
                  + " records for hourly collection rates!\n"));
            }
        }

        return;

    }
    else
    {
        player->catch_tell("\n" + sprintf("%|80s",
            "Harvest Rankings of " + capitalize(type) + " Skulls:\n"));
        player->catch_tell(sprintf("%|80s",
            "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"));
    }

    if (!sizeof(person) || members == -1)
    {
        if (query_guild_total())
        {
            if (type == "total")
            {
                player->catch_tell(sprintf("%|80s", "No skulls"
                  + " have been harvested by current members!\n"));
            }
            else
            {
                player->catch_tell(sprintf("%|80s", "No "
                  + capitalize(type) + " Skulls have been"
                  + " harvested!\n"));
            }
        }
        else
        {
            player->catch_tell(sprintf("%|80s", "The Harvest"
              + " has not yet begun!\n"));
        }
    }

    if (type == "normal" || type == "magic")
    {
        for (i = 0; i < n; i++)
        {
            if (get_info(person[i], "Forge-" + capitalize(type)) > 0)
            {
                if (query_membership_status(person[i]))
                {
                    paren1 = " ";
                    paren2 = "";
                }
                else
                {
                    paren1 = "(";
                    paren2 = ")";
                }

                player->catch_tell("\t\t\t" + sprintf("%5s %-12s %-20s",
                    (i+1) + ".", paren1 + capitalize(person[i]) + paren2,
                    sprintf("%,d", get_info(person[i],
                    "Forge-" + capitalize(type))) + "\n"));
            }
        }
    }
    else
    {
        for (i = 0; i < n; i++)
        {
            if (get_info(person[i], capitalize(type)) > 0)
            {
                if (query_membership_status(person[i]))
                {
                    paren1 = " ";
                    paren2 = "";
                }
                else
                {
                    paren1 = "(";
                    paren2 = ")";
                }

                player->catch_tell("\t\t\t" + sprintf("%5s %-12s %-20s",
                    (i+1) + ".", paren1 + capitalize(person[i]) + paren2,
                    sprintf("%,d", get_info(person[i],
                    capitalize(type))) + "\n"));
            }
        }
    }

} /* print_particular_list */


/*
 * Function name:        check_leader_update
 * Description  :        This function checks whether or not a new
 *                       ledership update for the guild is due. If it
 *                       is, then the new Headhunter General and Lethal
 *                       Bloodmaster are assigned. The function is also
 *                       called to check low long it will be before the
 *                       new update is due.
 * Arguments    :        int - assign_positions: true if we want to
 *                                               force a new election
 *                                               regardless of whether
 *                                               or not it is time yet.
 * Returns      :        int - the time of the next update.
 */
public int
check_leader_update(int assign_positions = 0)
{
    int     next_update,
            election_interval,
            current_time,
            i,
            general_is_member,
            corporal_is_member,
            age;
    string  general = NOT_YET_ASSIGNED,
            corporal = NOT_YET_ASSIGNED,
           *totals_array,
           *hourly_array,
            general_sentence,
            corporal_sentence,
           *accounts;
    mixed   player;

    current_time = time();
    election_interval     = current_time + ELECTION_INTERVAL;
    next_update  = get_info(REPOSITORY_FILE, "DueDate");

    /* We make this check to see if there are any members in the
     * guild right now. If not, no need to process further.
     */
    if (!sizeof(query_sorted_totals("rank", 1)))
    {
        return 0;
    }

    if (sizeof(query_sorted_totals("total", 1)))
    {
        totals_array = query_sorted_totals("total", 1);
        general   = totals_array[0];
    }

    if (sizeof(query_sorted_totals("hourly", 1)))
    {
        hourly_array = query_sorted_totals("hourly", 1);
        corporal  = hourly_array[0];
    }

    if (!query_membership_status(get_info(REPOSITORY_FILE, "GENERAL")) ||
        current_time >= next_update || assign_positions)
    {
        set_info(REPOSITORY_FILE, "GENERAL", NOT_YET_ASSIGNED);

        if (general == corporal)
        {

            /* No point in continuing if there are no officers being
             * assigned.
             */
            if (corporal == NOT_YET_ASSIGNED)
            {
                return 0;
            }

            if (sizeof(hourly_array) > 1)
            {
                if (skulls_per_hour(hourly_array[1]) >= AOD_UNWORTHY)
                {
                    corporal = hourly_array[1];
                }
            }
            else
            {
                corporal = NOT_YET_ASSIGNED;
            }
            set_info(REPOSITORY_FILE, "CORPORAL", corporal);
        }

        if (query_skull_total(general, 0) > 9999)
        {
            /* Been getting odd bugs here, so one final sanity check
             * just for good measure.
             */
            if (general == corporal)
            {
                corporal = NOT_YET_ASSIGNED;
            }

            if (general == GENERAL_AWOL && current_time < next_update)
            {
                if (!assign_positions)
                {
                    general = NOT_YET_ASSIGNED;
                    corporal = NOT_YET_ASSIGNED;
                }
            }
            else
            {
                set_info(REPOSITORY_FILE, "General_Awol", 0);
            }

            set_info(REPOSITORY_FILE, "GENERAL", general);

            if (get_info(REPOSITORY_FILE, "GENERAL") == NOT_YET_ASSIGNED)
            {
                set_info(REPOSITORY_FILE, "CORPORAL", NOT_YET_ASSIGNED);
            }
            else
            {
                set_info(REPOSITORY_FILE, "CORPORAL", corporal);
            }

            accounts = scan_accounts();

            /* Time now to reset everyone's age in the army so that
             * we are only calculating s.p.h. averages from the time
             * of the most recent election. We also need to write
             * to each account the current skull total for each
             * member, including the contents of their sack for that
             * calculation to be valid.
             */
            for (i = 0; i < sizeof(accounts); i++)
            {
                if (accounts[i])
                {
                    if (!objectp(accounts[i]))
                    {
                        if (!(player = find_player(accounts[i])))
                        {
                            age    = get_info(accounts[i], "player_age");
                        }
                        else
                       {
                            age    = player->query_age();
                        }
                    }
                    else
                    {
                        age = accounts[i]->query_age();
                    }

                    set_info(accounts[i], "Join_Age", age);
                    set_info(accounts[i], "Election_Total",
                        query_skull_total(accounts[i], 0)
                      + query_skull_total(accounts[i]) );
                }
            }

            general_is_member = query_membership_status(general);
            corporal_is_member = query_membership_status(corporal);

            general_sentence = ((general_is_member == 0) ?
                "No one is currently Headhunter General. " :
                capitalize(general) + " is Headhunter General of"
              + " the Army!");

            corporal_sentence = ((corporal_is_member == 0) ?
                " The Black Corporal position stands empty. " :
                " The Black Corporal position has been assigned to "
              + capitalize(corporal) + ".");

            set_alarm(10.0, 0.0, &tell_ogres(
                "Behold the glory of the Harvest! The time has come,"
              + " and officer positions have been newly assigned for"
              + " the Army! " + general_sentence + corporal_sentence, 1));

            write_file(AOD_LOG_DIR + "officer_log",
                TIME2FORMAT(time(), "mm/dd") + " ("
              + ctime(time())[11..18] + ") Officer Update:\n\t"
              + general_sentence + "\n\t" + corporal_sentence + "\n");

            /* If there is a corporal for the first time, write the
             * milestone to the list.
             */
            if (get_info(REPOSITORY_FILE, "CORPORAL") != NOT_YET_ASSIGNED &&
                get_info(REPOSITORY_FILE, "first_corporal") == 0)
            {
                find_living(get_info(REPOSITORY_FILE, "CORPORAL"))->
                    catch_tell("Guild Milestone achieved! You are the"
                  + " first Black Corporal of the Army! Your name shall"
                  + " live forever!\n");
                write_file(MILESTONE_FILE,
                    sprintf("%-16s%-47s%-11s",
                    TIME2FORMAT(time(), "mm/dd/yyyy"),
                    "First Black Corporal of the Army",
                    capitalize(get_info(REPOSITORY_FILE, "CORPORAL"))
                  + "\n"));
                set_info(REPOSITORY_FILE, "first_corporal",
                    get_info(REPOSITORY_FILE, "CORPORAL"));
            }

            set_info(REPOSITORY_FILE, "DueDate", election_interval);

            return election_interval;
        }
    }

    if (get_info(REPOSITORY_FILE, "GENERAL") == NOT_YET_ASSIGNED)
    {
        set_info(REPOSITORY_FILE, "CORPORAL", NOT_YET_ASSIGNED);
    }

    return next_update;
} /* check_leader_update */

/*
 * Function name:        print_big_list
 * Description  :        Lay out the Readerboard for members of the Army
 *                       of Darkness. This displays an at-a-glance overview
 *                       of the current collection leaders for each race.
 * Arguments    :        object player - the person who will see the
 *                                       output.
 */
public void
print_big_list(object player)
{
    int      i,
             duedate;
    string   chief,
             blood;

    duedate = check_leader_update() - time();

    chief = get_info(REPOSITORY_FILE, "GENERAL");
    blood = get_info(REPOSITORY_FILE, "CORPORAL");

    player->catch_tell(sprintf("%|80s",
            "THE HARVEST OF SKULLS\n"));
    player->catch_tell(sprintf("%|80s",
            "~~~~~~~~~~~~~~~~~~~~~\n\n"));

    if (chief && chief != NOT_YET_ASSIGNED)

    {
        if (query_membership_status(chief))
        {
            player->catch_tell(sprintf("%|80s",
                capitalize(chief) + " is the Headhunter General with "
              + sprintf("%,d", query_skull_total(chief, 0))
              + " heads collected!\n"));
        }
        else
        {
            player->catch_tell(sprintf("%|80s",
                "There is currently no Headhunter General!\n"));
        }

        if (blood)
        {
            if (query_membership_status(blood))
            {
                player->catch_tell(sprintf("%|80s",
                    capitalize(blood) + " is the Black Corporal, currently"
                  + " rating at " + sprintf("%,d", skulls_per_hour(blood))
                  + " skulls per hour!\n"));
            }
            else
            {
                player->catch_tell(sprintf("%|80s",
                    "There is currently no Black Corporal!\n"));
            }
        }

        player->catch_tell("\n"
          + sprintf("%|80s", "The Darklings will assign new officers in:\n")
          + sprintf("%|80s", CONVTIME(duedate) + "\n"));
    }
    else
    {
        player->catch_tell(sprintf("%|80s",
            "The first Harvester of 10,000 skulls will become Headhunter"
          + " General!"));
    }

    player->catch_tell("\n");

    print_particular_list("total", player, 5, 1);

    player->catch_tell("\nHuman Skulls    Elf Skulls      Hobbit"
                     + " Skulls   Dwarf Skulls    Gnome Skulls\n"
                     + "~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~  "
                     + "~~~~~~~~~~~~~~  ~~~~~~~~~~~~~~  "
                     + "~~~~~~~~~~~~~~\n");

    for (i = 0; i < 5; i++)
    {
        print_total_line(player, i+1);
    }

    player->catch_tell("\n\n" + sprintf("%|80s", "Total Skulls Collected: "
      + sprintf("%,d", query_guild_total()) + "\n"));

    player->catch_tell("\n");
} /* print_big_list */


/*
 * Function name:        scan_accounts
 * Desctiption  :        print the names of all accounts
 * Arguments    :        int members_only - true if we want the array to
 *                                          contain only members who are
 *                                          still with the Army.
 *                                        - default = 0.
 * Returns      :        the array containing the account names
 */
public mixed
scan_accounts(int members_only = 0)
{
    if (query_accounts_updated())
    {
        // If the Accounts have been updated, we go to disk to fetch the names.
        // Otherwise, they should already be available in the Accounts variable.
        string * all_accounts = ({ });
        string * member_accounts = ({ });
        // We need to get the names of all the accounts from disk.
        string * all_files = get_dir(AOD_SAVE_DIR);
        foreach (string filename : all_files)
        {
            string account_name;
            sscanf(filename, "%s.o", account_name);
            if (!strlen(account_name) || account_name == REPOSITORY_FILE)
            {
                // We ignore the REPOSITORY_FILE and empty files
                continue;
            }
            all_accounts += ({ account_name });
            if (query_membership_status(account_name))
            {
                member_accounts += ({ account_name });
            }
        }
        Accounts["all"] = all_accounts;
        Accounts["members"] = member_accounts;
        set_accounts_updated(0); // unset the flag so we will not go to disk again
    }

    if (members_only)
    {
        return Accounts["members"];
    }

    return Accounts["all"];
/*
    string  *accounts = get_dir(AOD_SAVE_DIR),
             account,
            *all_array,
            *members_array;
    int      i,
             n = sizeof(accounts),
             j = 0,
             k = 0;

    all_array = allocate(sizeof(accounts));

    for (i = 0; i < n; i++)
    {
        sscanf(accounts[i], "%s.o", account);

        if (account != REPOSITORY_FILE)
        {
            if (query_membership_status(account))
            {
                j++;
            }
        }
    }

    members_array = allocate(j);

    for (i = 0; i < n; i++)
    {
        sscanf(accounts[i], "%s.o", account);

        if (account != REPOSITORY_FILE)
        {
            if (query_membership_status(account))
            {
                members_array[k] = account;
                k++;
            }

            all_array[i] = account;
        }
    }

    if (members_only)
    {
        return members_array;
    }

    return all_array;   */
} /* scan_accounts */


/*
 * Function name:        query_guild_total
 * Description  :        count the total number of skulls collected
 *                       by members, both past and present (default)
 *                       If an arg is passed then we check for the
 *                       guild total for a particular racetype.
 * Arguments    :        string race - The type of race to check
 *                              default = "total"
 * Returns      :        int - the total skull count
 */
public int
query_guild_total(string race = "total")
{
    int     i, n,
            total = 0;
    string *accounts = scan_accounts();

    n = sizeof(accounts);

    for (i = 0; i < n; i++)
    {
        if (accounts[i])
        {
            if (race != "total")
            {
                total += get_info(accounts[i],
                         capitalize(race));
            }
            else
            {
                total += query_skull_total(accounts[i], 0);
            }
        }
    }

    return total;
} /* query_guild_total */


/*
 * Function name:        compute_title
 * Description  :        Determine the title for a player based on
 *                       their total skull count.
 * Arguments    :        object player - the player
 * Returns      :        int - the rank for the title
 */
public int
compute_title(object player)
{
    int     total = query_skull_total(player, 0);

    switch(total)
    {
        case 0..9:
            return 0;
            break;
        case 10..49:
            return 1;
            break;
        case 50..99:
            return 2;
            break;
        case 100..199:
            return 3;
            break;
        case 200..249:
            return 4;
            break;
        case 250..299:
            return 5;
            break;
        case 300..349:
            return 6;
            break;
        case 350..399:
            return 7;
            break;
        case 400..449:
            return 8;
            break;
        case 450..499:
            return 9;
            break;
        case 500..599:
            return 10;
            break;
        case 600..699:
            return 11;
            break;
        case 700..799:
            return 12;
            break;
        case 800..899:
            return 13;
            break;
        case 900..999:
            return 14;
            break;
        case 1000..1499:
            return 15;
            break;
        case 1500..1999:
            return 16;
            break;
        case 2000..2999:
            return 17;
            break;
        case 3000..3999:
            return 18;
            break;
        case 4000..4999:
            return 19;
            break;
        case 5000..5999:
            return 20;
            break;
        case 6000..6999:
            return 21;
            break;
        case 7000..7999:
            return 22;
            break;
        case 8000..8999:
            return 23;
            break;
        case 9000..9999:
            return 24;
            break;
        case 10000..19999:
            return 25;
            break;
        case 20000..29999:
            return 26;
            break;
        case 30000..39999:
            return 27;
            break;
        case 40000..49999:
            return 28;
            break;
        case 50000..99999:
            return 29;
            break;
        case 100000..249999:
            return 30;
            break;
        case 250000..499999:
            return 31;
            break;
        case 500000..749999:
            return 32;
            break;
        case 750000..999999:
            return 33;
            break;
        default:
            return 34;
            break;
    }

    return 0; /* should never happen, but just in case. */
} /* compute_title */


/*
 * Function name:        set_join_age
 * Description  :        Write to the playerfile how old this player
 *                       was when they joined the Army, or update the
 *                       age to reflect the timestamp for the most
 *                       recent election (to calculate skulls-per-hour
 *                       correctly.)
 * Arguments    :        mixed who - the person who joined
 * Returns      :        int - the time they joined
 */
public int
set_join_age(mixed who)
{
    return set_info(who, "Join_Age", who->query_age());
} /* set_join_age */


/*
 * Function name:        membership_duration
 * Description  :        Compare the current player age to the age this
 *                       person was when they joined the guild to
 *                       determine how long they have been a member of
 *                       the Army.
 * Arguements    :        mixed who - the name of the person in question
 * Returns      :        int - the time in seconds
 */
public int
membership_duration(mixed who)
{
    int     age,
            extra_age = get_info(who, "Extra_Age");
    mixed   player;

    if (!who)
    {
        return 0;
    }

    if (!objectp(who))
    {
        if (!(player = find_player(who)))
        {
            age    = get_info(who, "player_age");
        }
        else
        {
            age    = player->query_age();
        }
    }
    else
    {
        age = who->query_age();
    }

//    return (age - get_info(who, "Join_Age")) + extra_age;
    return (age - get_info(who, "Join_Age"));
} /* membership_duration */


/*
 * Function name:        skulls_per_hour
 * Description  :        Determine how many skulls a person collects
 *                       (on average) per hour based on their duration
 *                       of time spent in the guild versus their total
 *                       skull collection.
 * Arguments    :        mixed who - the person in question
 * Returns      :        int - the number of skulls collected per hour
 */
public int
skulls_per_hour(mixed who)
{
    int     duration = membership_duration(who);
    int     collection = query_skull_total(who, 0)
                       - get_info(who, "Election_Total");
    float   minutes;

    /* Determine how minutes the player has been in the guild */
    minutes = itof(duration) / 60.0;

    /* Players who do not play 10 hours cannot qualify for SPH
     * ratings.
     */
    if (minutes < 600.0)
    {
        return 0;
    }

    if (collection)
    {
        if (itof(collection) / minutes > 0.0)
        {
            return ftoi((itof(collection) / minutes) * 60.0);
        }
    }

    return 0;
} /* skulls_per_hour */


/*
 * Function name:        print_member_list
 * Description  :        Print a list of all members of the guild,
 *                       along with their rate of productivity.
 * Arguments    :        player - the person who will see the list
 */
public void
print_member_list(object player)
{
    string *accounts = scan_accounts(),
            title,
            logged_in;
    int     i,
            n = sizeof(accounts);
    object  who;

    player->catch_tell(
        sprintf("%|80s",
            ".---------------------------------------------------.\n")
      + sprintf("%|80s",
            "|        The Roster for the Army of Darkness          |\n")
      + sprintf("%|80s",
            "|                                                     |\n")
      + sprintf("%|80s",
            "|  Name:        Title:                    S.P.H: (**) |\n")
      + sprintf("%|80s",
            "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"));

    for (i = 0; i <= (n - 1); i++)
    {
        logged_in = "*";

        if (!accounts[i])
        {
            continue;
        }

        if (!(who = find_player(accounts[i])))
        {
            if (!objectp(who = SECURITY->finger_player(accounts[i])))
            {
                continue;
            }

            logged_in = " ";
        }

        if (query_membership_status(who))
        {
            if (who->query_gender() == 1)
            {
                title = " " + AOD_TITLES_FEMALE[compute_title(who)];
            }
            else
            {
                title = " " + AOD_TITLES_MALE[compute_title(who)];
            }
        }
        else
        {
            title = "(former member)";
            logged_in = " "; /* we don't reveal info on non-members */
        }

        player->catch_tell(sprintf("%|80s",
            "| " + sprintf("%-12s %-26s %-11s %-2s",
            logged_in + capitalize(accounts[i]), title,
            sprintf("%,d", skulls_per_hour(who)), "|\n")));

        if (!interactive(who))
        {
            if (environment(who) != find_object("/d/Genesis/obj/statue"))
            {
                who->remove_object();
            }
        }
    }

    player->catch_tell(
        sprintf("%|80s",
            "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n")
      + sprintf("%|80s",
            "| (*) Currently On-Duty          (**) Skulls Per Hour |\n")
      + sprintf("%|80s",
            "'---------------------------------------------------'\n"));
} /* print_member_list */


/*
 * Function name:        aod_who_list
 * Description  :        Print a list of guild members who are online
 * Arguments    :        mixed player - who will see the list
 */
public void
aod_who_list(mixed player)
{
//  string *accounts = query_sorted_totals("rank", 1),
    string *accounts = scan_accounts(1),
            aod_title;
    int     i,
            j = 0,
            n = sizeof(accounts);
    object  who;

    player->catch_tell(
        sprintf("%|80s",
            ".---------------------------------------------------.\n")
      + sprintf("%|80s",
            "|     Active Duty Roster for the Army of Darkness     |\n")
      + sprintf("%|80s",
            "|                                                     |\n")
      + sprintf("%|80s",
            "| Name:        Title:                     S.P.H: (*)  |\n")
      + sprintf("%|80s",
            "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"));

    for (i = 0; i <= (n - 1); i++)
    {
        if (!accounts[i])
        {
            continue;
        }

        if (who = find_player(accounts[i]))
        {
            if (query_membership_status(who))
            {
                if (who->query_gender() == 1)
                {
                    aod_title = AOD_TITLES_FEMALE[compute_title(who)];
                }
                else
                {
                    aod_title = AOD_TITLES_MALE[compute_title(who)];
                }

                if (AOD_GENERAL(who))
                {
                    aod_title = "** Headhunter General **";
                }

                if (AOD_CORPORAL(who))
                {
                    aod_title = "** Black Corporal **";
                }

                if (who->query_real_name() == "gorboth")
                {
                    aod_title = "Duty Officer";
                }

                player->catch_tell(sprintf("%|80s", "| "
                  + sprintf("%-12s %-26s %-11s %-2s",
                    capitalize(accounts[i]),
                    aod_title,
                    sprintf("%,d", skulls_per_hour(who)), "|\n")));

                j++;
            }
        }
    }

    player->catch_tell(
        sprintf("%|80s",
            "|                                                     |\n")
      + sprintf("%|80s",
            "| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |\n")
      + sprintf("%|80s",
            "| Members On-Duty: "
      + sprintf("%-15s", j + " out of " + n)
                            + "(*) Skulls Per Hour |\n")
      + sprintf("%|80s",
            "'---------------------------------------------------'\n"));
} /* aod_who_list */


/* Function name:        query_productivity
 * Description  :        Determine, based on the number of skulls
 *                       per hour the member has collected, whether
 *                       they are either "worthless" or "worthy"
 *                       in the eyes of the Darklings.
 * Arguments    :        mixed player - the member to check
 * Returns      :        int:  2 - player is worthy,
 *                             1 - player is average,
 *                             0 - player is worthless
 */
public int
query_productivity(mixed player)
{
    int     productivity = skulls_per_hour(player);

    if (productivity < AOD_UNWORTHY)
    {
        return 0;
    }

    if (productivity > AOD_WORTHY)
    {
        return 2;
    }

    return 1;
} /* query_productivity */


/*
 * Function name:        display_worthless
 * Description  :        Print a list of Army Members who have not
 *                       collected the minimum requires Skulls Per
 *                       Hour.
 * Arguments    :        object player - who will see the message
 */
public void
display_worthless(object player)
{
    string *accounts = scan_accounts(),
            logged_in = "*",
            ttab = "\t\t\t";
    int     i,
            j = 0,
            n = sizeof(accounts);
    object  who;


    player->catch_tell(
        sprintf("%|80s",".-------------------------.\n")
      + sprintf("%|80s","|      The Worthless!       |\n")
      + sprintf("%|80s","|                           |\n")
      + sprintf("%|80s","|  Name:        S.P.H: (**) |\n")
      + sprintf("%|80s","| ~~~~~~~~~~~~~~~~~~~~~~~~~ |\n"));

    for (i = 0; i <= (n - 1); i++)
    {
        if (!accounts[i])
        {
            continue;
        }

        if (!(who = find_player(accounts[i])))
        {
            who = SECURITY->finger_player(accounts[i]);
            logged_in = " ";
        }

        if (query_membership_status(who) && !query_productivity(who))
        {
            player->catch_tell(sprintf("%|80s",
                "| " + sprintf("%-12s  %-11s %-2s",
                logged_in + capitalize(accounts[i]),
                sprintf("%,d", skulls_per_hour(who)), "|\n")));

            j++;
        }

        if (who->query_finger_player())
        {
            who->remove_object();
        }
    }

    if (!(j))
    {
        player->catch_tell(
        sprintf("%|80s","|  None. The Darklings are  |\n")
      + sprintf("%|80s","|      most pleased ...     |\n")
      + sprintf("%|80s","|                           |\n"));
    }

    player->catch_tell(
        sprintf("%|80s","| ~~~~~~~~~~~~~~~~~~~~~~~~~ |\n")
      + sprintf("%|80s","|    (**) Skulls Per Hour   |\n")
      + sprintf("%|80s","|     (*) On-Duty           |\n")
      + sprintf("%|80s","'-------------------------'\n"));
} /* display_worthless */


/*
 * Function name:        set_membership_status
 * Description  :        add a flag to the account file to determine if
 *                       the account belongs to a current member of
 *                       the guild
 * Arguments    :        mixed player - the account to write to,
 *                       int aod_status: 1 - current member, 0 - non-member
 */
public void
set_membership_status(mixed player, int aod_status)
{
    set_info(player, "Membership_Status", aod_status);

    // Membership status has changed for one of two reasons
    // 1. Member has joined and new file is being created.
    // 2. Member has left and should no longer belong in the members_only
    //    queries
    // We set the update flag so that the next call to scan_accounts
    // will retrieve from disk.
    set_accounts_updated(1);
    set_alarm(1.0, 0.0, &refresh_sorted_totals());
} /* set_membership_status */


/*
 * Function name:        query_membership_status
 * Description  :        determine if this account belongs to a current
 *                       member of the guild
 * Arguments    :        mixed player - the account to check
 * Returns      :        int: 1 - current member, 0 - non-member
 */
public int
query_membership_status(mixed player)
{
    return get_info(player, "Membership_Status");
} /* query_membership_status */

int
cmp(int a, int b)
{
    if (a > b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}

mapping sorted_list_all= ([
    "elf": init_sorted_list(cmp, &get_info(, "Elf")),
    "dwarf": init_sorted_list(cmp, &get_info(, "Dwarf")),
    "human": init_sorted_list(cmp, &get_info(, "Human")),
    "hobbit": init_sorted_list(cmp, &get_info(, "Hobbit")),
    "gnome": init_sorted_list(cmp, &get_info(, "Gnome")),
    "other":  init_sorted_list(cmp, &get_info(, "Other")),
    "total":  init_sorted_list(cmp, &query_skull_total(, 0)),
    "hourly":  init_sorted_list(cmp, skulls_per_hour),
    "rank":  init_sorted_list(cmp, compute_title),
    "normal":  init_sorted_list(cmp, &get_info(, "Forge-Normal")),
    "magic":  init_sorted_list(cmp, &get_info(, "Forge-Magic"))
]);


mapping sorted_list_members = ([
    "elf": init_sorted_list(cmp, &get_info(, "Elf")),
    "dwarf": init_sorted_list(cmp, &get_info(, "Dwarf")),
    "human": init_sorted_list(cmp, &get_info(, "Human")),
    "hobbit": init_sorted_list(cmp, &get_info(, "Hobbit")),
    "gnome": init_sorted_list(cmp, &get_info(, "Gnome")),
    "other":  init_sorted_list(cmp, &get_info(, "Other")),
    "total":  init_sorted_list(cmp, &query_skull_total(, 0)),
    "hourly":  init_sorted_list(cmp, skulls_per_hour),
    "rank":  init_sorted_list(cmp, compute_title),
    "normal":  init_sorted_list(cmp, &get_info(, "Forge-Normal")),
    "magic":  init_sorted_list(cmp, &get_info(, "Forge-Magic"))
]);

/*
 * Resets the sorted lists from scratch.
 * Uses alot of cpu.
 */
public void
refresh_sorted_totals()
{
    string * all_accounts = scan_accounts(0);
    string * member_accounts = scan_accounts(1);

    foreach (string type: m_indexes(sorted_list_all)) {
        sorted_list_set(sorted_list_all[type], all_accounts);
        sorted_list_set(sorted_list_members[type], member_accounts);
    }
}

/*
 * Resets the sorted lists from scratch.
 * Uses alot of cpu.
 */
public void
update_sorted_totals(string who)
{
    foreach (string type: m_indexes(sorted_list_all)) {
        sorted_list_update(sorted_list_all[type], who);
        sorted_list_update(sorted_list_members[type], who);
    }
}

/*
 * Function name:        query_sorted_totals
 * Description  :        this function checks the existing army accounts
 *                       for players and determines the rank order of
 *                       those players based on their collection of the
 *                       specified item.
 * Arguments    :        string race - what race to sort for,
 *                       int members_only - true if we only want to sort
 *                                          active army members.
 *                                        - default = 1
 * Returns               string array - the array of sorted members.
 */
public string *
query_sorted_totals(string race, int members_only = 1)
{
    if (members_only)
    {
        return sorted_list_get(sorted_list_members[race]);
    }

    return sorted_list_get(sorted_list_all[race]);
} /* query_sorted_totals */


/*
 * Function name:        is_ogre
 * Description  :        check to see if this person is an ogre
 * Arguments    :        object who - the person to check
 * Returns      :        1 - is an ogre, 0 - not an ogre
 */
public int
is_ogre(object who)
{
    return IS_OGRE(who);
} /* is_ogre */


/*
 * Function name:        tell_ogres
 * Description  :        Send a tell to all guild members who are logged
 *                       on currently.
 * Arguments    :        string arg: the text to send them
 *                       int darktell: should this be a darkling tell?
 *                                     default is set to 0 (false)
 */
public void
tell_ogres(string arg, int darktell = 0)
{
    object  *ogres;
    int      i;

    ogres = filter(users(), is_ogre);

    for (i = 0; i < sizeof(ogres); i++)
    {
        if (darktell)
        {
            DTELL_MOD->darkling_tell(arg, ogres[i], "xyzzyX");
        }
        else
        {
            ogres[i]->catch_tell(arg);
        }
    }
} /* tell_ogres */


/*
 * Function name:        check_milestones
 * Description  :        see whether or not the current deposit has
 *                       achieved any new milestones either for the
 *                       player or for the guild. If milestones have
 *                       been achieved for the guild, we write to a
 *                       history log that players themselves will be
 *                       able to refer to for the sake of posterity.
 * Arguments    :        int *preguild - array of skullcounts for the
 *                                       guild before the last deposit,
 *                       int *preplayer- array of skullcounts for the
 *                                       player before the last deposit.
 *                       object player - the player who made the deposit.
 *                       int   oldrank - the former title rank of the
 *                                       player,
 *                       int predefense,
 *                           preoffense,
 *                           preadv_offense,
 *                           pre_elite - these are all former skill levels
 *                                       of the player for various
 *                                       training rooms.
 */
public void
check_milestones(int *preguild, int *preplayer, object player, int oldrank, int preoffense, int preadv_offense, int predefense, int preelite)
{
    int    *postguild =  ({ query_guild_total("human"),
                            query_guild_total("elf"),
                            query_guild_total("hobbit"),
                            query_guild_total("dwarf"),
                            query_guild_total("gnome"),
                            query_guild_total("total") }),
           *postplayer = ({ get_info(this_player(), "Human"),
                            get_info(this_player(), "Elf"),
                            get_info(this_player(), "Hobbit"),
                            get_info(this_player(), "Dwarf"),
                            get_info(this_player(), "Gnome"),
                            query_skull_total(player, 0) }),
            postdefense,
            postoffense,
            postadv_offense,
            postelite,
            skulls;
    string  which_txt = "handle more";

    set_this_player(player);

    skulls = AOD_MASTER->query_skull_total(this_player(), 0);

    postoffense     = AOD_TRAINING->aod_training_check(
                      SS_WEP_CLUB, skulls);
    postadv_offense = AOD_TRAINING->aod_training_check(
                      SS_AOD_WALLOP, skulls);
    postdefense     = AOD_TRAINING->aod_training_check(
                      SS_PARRY, skulls);
    postelite       = AOD_TRAINING->aod_training_check(
                      SS_2H_COMBAT, skulls);

    /* okay ... first, lets check for player title milestones */
    if (compute_title(player) > oldrank)
    {
        write("Your rank has increased in the Army!\n");
    }

    /* now, lets look at individual skill training milestones
     * Note: in the original construct, club was the offensive
     * skill and crush the advanced offensive. I've since changed that,
     * but I didn't want to muck around changing all these variable
     * names ... so, it looks a bit confusing to see "advanced"
     * in the message for pre-postoffense and not in pre-postadv_offense
     * but that is as it should be.
     */
    if (preoffense < postoffense)
    {
        if (!preoffense)
        {
            which_txt = "begin";
        }

        write("You feel smart enough to " + which_txt + " advanced"
          + " offensive training!\n");
    }

    if (preadv_offense < postadv_offense)
    {
        if (!preadv_offense)
        {
            which_txt = "begin";
        }

        write("You feel smart enough to " + which_txt + " offensive"
          + " training!\n");
    }

    if (predefense < postdefense)
    {
        if (!predefense)
        {
            which_txt = "begin";
        }

        write("You feel smart enough to " + which_txt + " defensive"
          + " training!\n");
    }

    if (preelite < postelite)
    {
        if (!preelite)
        {
            which_txt = "begin";
        }

        write("You feel smart enough to " + which_txt + " elite"
          + " training!\n");
    }

    /* next, lets see if the player has achieved any milestones at
       the the forge */
    if (preguild[1] < postguild[1]) /* elves = weapon upgrades */
    {
        if (postguild[1] > 499 && postguild[1] < 1000 &&
            preguild[1] < 500)
        {
            write("A forge upgrade has been achieved in weaponry!\n");
        }
        if (postguild[1] > 999 && postguild[1] < 5000 &&
            preguild[1] < 1000)
        {
            write("A forge upgrade has been achieved in weaponry!\n");
        }
        if (postguild[1] > 4999 && postguild[1] < 10000 &&
            preguild[1] < 5000)
        {
            write("A forge upgrade has been achieved in weaponry!\n");
        }
        if (postguild[1] > 9999 && postguild[1] < 25000 &&
            preguild[1] < 10000)
        {
            write("A forge upgrade has been achieved in weaponry!\n");
        }
        if (postguild[1] > 24999 && postguild[1] < 50000 &&
            preguild[1] < 25000)
        {
            write("Guild Milestone achieved! Magical weapons are now"
                  + " available at the Forge!\n");
            write_milestone("Guild Upgrade Achieved in Magic Weaponry",
                            this_player());
        }
        if (postguild[1] > 49999 && postguild[1] < 75000 &&
            preguild[1] < 50000)
        {
            write("A forge upgrade has been achieved in weaponry!\n");
        }
        if (postguild[1] > 74999 && postguild[1] < 100000 &&
            preguild[1] < 75000)
        {
            write("A forge upgrade has been achieved in weaponry!\n");
        }
        if (postguild[1] > 99999 && preguild[1] < 100000)
        {
            write("Guild Milestone achieved! The Smith now has"
              + " complete knowledge of Weaponcrafting!\n");
            write_milestone("Forge now has a Master Weaponsmith",
                            this_player());
        }
    }
    if (preguild[3] < postguild[3]) /* dwarves = armour upgrades */
    {
        if (postguild[3] > 499 && postguild[3] < 1000 &&
            preguild[3] < 500)
        {
            write("A forge upgrade has been achieved in armour!\n");
        }
        if (postguild[3] > 999 && postguild[3] < 5000 &&
            preguild[3] < 1000)
        {
            write("A forge upgrade has been achieved in armour!\n");
        }
        if (postguild[3] > 4999 && postguild[3] < 10000 &&
            preguild[3] < 5000)
        {
            write("A forge upgrade has been achieved in armour!\n");
        }
        if (postguild[3] > 9999 && postguild[3] < 25000 &&
            preguild[3] < 10000)
        {
            write("A forge upgrade has been achieved in armour!\n");
        }
        if (postguild[3] > 24999 && postguild[3] < 50000 &&
            preguild[3] < 25000)
        {
            write("Guild Milestone achieved! Magical armours are now"
                  + " available at the Forge!\n");
            write_milestone("Guild Upgrade Achieved in Armours",
                            this_player());
        }
        if (postguild[3] > 49999 && postguild[3] < 75000 &&
            preguild[3] < 50000)
        {
            write("A forge upgrade has been achieved in armour!\n");
        }
        if (postguild[3] > 74999 && postguild[3] < 100000 &&
            preguild[3] < 75000)
        {
            write("A forge upgrade has been achieved in armour!\n");
        }
        if (postguild[3] > 99999 && preguild[3] < 100000)
        {
            write("Guild Milestone achieved! The Smith now has"
              + " complete knowledge of Armourcraft!\n");
            write_milestone("Forge now has a Master Armoursmith",
                            this_player());
        }
    }

    /* Now, lets check the other racial milestones */
    if (postguild[0] > 24999 && preguild[0] < 25000) /* humans */
    {
        write("Guild Milestone achieved! The Army of Darkness Shop is"
          + " now open for business!\n");
        write_milestone("Guild Upgrade Achieved in Selling Goods",
                        this_player());
    }
    if (postguild[2] > 24999 && preguild[2] < 25000) /* hobbits */
    {
        write("Guild Milestone achieved! The Army of Darkness Mess"
          + " Hall is now open for business!\n");
        write_milestone("Guild Upgrade Achieved in Cooking",
                        this_player());
    }
    if (postguild[4] > 24999 && preguild[4] < 25000) /* gnomes */
    {
        write("Guild Milestone achieved! The Army of Darkness Bank is"
          + " now open for business!\n");
        write_milestone("Guild Upgrade Achieved in Banking",
                        this_player());
    }

    /* Finally, lets mark some other general milestones ... */
    if (preguild[5] == 0 && postguild[5] > 0)
    {
        write("Guild Milestone achieved! You have collected the first"
          + " skull of the Harvest! Your name shall live forever!\n");
        write_milestone("First Skull Harvested",
                        this_player());
    }
    if (preplayer[5] < 10000 && postplayer[5] > 9999 &&
        get_info(REPOSITORY_FILE, "first_general") == 0)
    {
        write("Guild Milestone achieved! You are the first General of"
          + " the Army! Your name shall live forever!\n");
        set_info(REPOSITORY_FILE, "first_general",
            this_player()->query_real_name());
        write_milestone("First Headhunter General of the Army",
                        this_player());
    }
    if (preplayer[5] < 1000000 && postplayer[5] > 999999 &&
        get_info(REPOSITORY_FILE, "first_million") == 0)
    {
        write("Guild Milestone achieved! You are the first ogre to"
           + " Harvest one million skulls! Glory is eternally"
           + " yours, mighty one!\n");
        set_info(REPOSITORY_FILE, "first_million",
            this_player()->query_real_name());
        write_milestone("First Harvester of One Million Skulls",
                        this_player());
    }

} /* check_milestones */


/*
 * Function name:        write_milestone
 * Description  :        Permenantly write a milestone that has been
 *                       achieved to the "milestones" file that players
 *                       can access using <ogrehelp>.
 * Arguments    :        string mwhat - the milestone that was achieved.
 *                       object mwho  - who achieved it.
 */
public void
write_milestone(string mwhat, object mwho)
{
    string mtxt;

    TELL_G("write_milestone() called.!\n");
    if (!file_time(MILESTONE_FILE))
    {
        /* the milestone file does not yet exist, so we need to create
         * a heading for the file milestone list.
         */
        mtxt = "\t\t   MILESTONES FOR THE ARMY OF DARKNESS:\n"
             + "\t\t   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
             + "Date:           Milestone:                               "
             + "      Name:       \n"
             + "========================================================="
             + "==================\n";

        write_file(MILESTONE_FILE, mtxt);
    }

    mtxt = sprintf("%-16s%-47s%-11s", TIME2FORMAT(time(), "mm/dd/yyyy"),
                  mwhat, mwho->query_name() + "\n");

    write_file(MILESTONE_FILE, mtxt);
} /* write_milestone */


mapping refresh_alarms = ([ ]);
/*
 * Function:    set_info
 * Description: Mask of set_info so we know when the data has been
 *              changed.
 */
int
set_info(mixed index_val, string info, mixed val)
{
    int ret = ::set_info(index_val, info, val);

    // This attempts to identify updates to players and trigger an update of
    // their sort information.
    if (!objectp(index_val) || !is_ogre(index_val)) {
        return ret;
    }

    string who = index_val->query_real_name();
    if (!refresh_alarms[who] || !get_alarm(refresh_alarms[who]))
    {
        refresh_alarms[who] = set_alarm(1.0, 0.0, &update_sorted_totals(who));
    }
    return ret;
}
