/*
 * Base Test Room
 *
 * Create test npcs here and have them fight each other.
 * Can specify multiple battles at once.
 *
 * Created by Petros, February 2009
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
 
inherit "/std/room";
inherit "/d/Sparkle/area/city/lib/utility_functions";
inherit "/d/Genesis/specials/lib/calculations";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define TEST_NPC    "/d/Genesis/specials/guilds/test/test_npc"
#define DATA_DIR    "/d/Genesis/specials/guilds/test/data/"
#define ROOM_I_SUNLIGHT "_room_i_sunlight"
#define DAMAGE_TRACKER_SH   "/d/Genesis/specials/guilds/test/damage_tracker_sh"

public mapping      opponents = ([ ]);
public int          total_duration = 3600;
public int          total_fights   = 10;
public int          test_alarm;
public string       opponent_one = "default";
public string       opponent_two = "default";
public int          fight_to_death = 0;
public int          deathmatch_mode = 0;
public mixed        deathmatch_list = ({ 
    "/d/Sparkle/area/goblin_caves/npcs/l2_spider.c", // Goblin Caves spider
    "/d/Gondor/arnor/npc/massive_troll.c", // Barash-Gund
    "/d/Ansalon/kalaman/living/captain.c", // Baxter
    "/d/Ansalon/kalaman/living/calof.c", // Calof
    "/d/Ansalon/kalaman/living/half-elf.c", // Ealanus
    "/d/Ansalon/balifor/flotsam_forest/living/g_dragon.c", // Emerald
    "/d/Gondor/fangorn/npc/ent.c", // Ent
    "/d/Krynn/icewall/castle2/npc/fael-thas.c", // Fael-Thas
    "/d/Ansalon/taman_busuk/mountains/living/fallen_knight.c", // Garren
//    "/d/Gondor/ithilien/camp/npc/hathamir.c", // Hathamir
    "/d/Gondor/fangorn/npc/huorn.c", // Huorn
    "/d/Gondor/rohan/edoras/npc/innguard.c", // Inn Guard
    "/d/Avenir/common/bazaar/NPCS/jadestone.c", // Jadestone
    "/d/Krynn/qualinesti/npc/qualthas.c", // Qualthas
    "/d/Krynn/solace/new_village/town_square/thimah/npc/thimah.c", // Thimah
    "/d/Ansalon/goodlund/nethosak/forest/npc/trollShaman.c", // Thorr-kan
    "/d/Krynn/icewall/castle2/npc/arcticyeti.c", // Yeti
    "/d/Krynn/solace/new_village/town_square/npcs/zahrtok.c", // Zahrtok 
    });
// We store the mapping information for the two npcs so that they can be
// customized inside the room.
public mapping first_npc_data = ([
    "track_damage"              : 1,
    "prevent_damage"            : 1,
    "guilds"                    : ({ }),
    "commands"                  : ({ }),
    "equipment"                 : ({"/d/Genesis/specials/guilds/test/armours/standard_armour_40","/d/Genesis/specials/guilds/test/armours/standard_shield_40","/d/Genesis/specials/guilds/test/armours/standard_shield_40",}),
    "names"                     : ({ "test_npc_one" }),
    "short_desc"                : "first test npc",
    "long_desc"                 : "This is the first test npc.\n",
    "base_stats"                : ({ 170, 170, 170, 170, 170, 170, 170, 170, 170, 170 }),
    "base_race"                 : "human",
    "setup_function"            : "",
    "special_attack_function"   : "",
    "spell_notify_function"     : "",
    "alignment"                 : 0,
    ]);
public mapping second_npc_data = ([
    "track_damage"              : 1,
    "prevent_damage"            : 1,
    "guilds"                    : ({ }),
    "commands"                  : ({ }),
    "equipment"                 : ({"/d/Genesis/specials/guilds/test/armours/standard_armour_40","/d/Genesis/specials/guilds/test/armours/standard_shield_40","/d/Genesis/specials/guilds/test/armours/standard_shield_40",}),
    "names"                     : ({ "test_npc_two" }),
    "short_desc"                : "second test npc",
    "long_desc"                 : "This is the second test npc.\n",
    "base_stats"                : ({ 170, 170, 170, 170, 170, 170, 170, 170, 170, 170 }),
    "base_race"                 : "human",
    "setup_function"            : "",
    "special_attack_function"   : "",
    "spell_notify_function"     : "",
    "alignment"                 : 0,
    ]);
    
// Prototypes
public int          stop_tests(string arg);
public void         set_opponent_files();
public int          sunlight(object room);
private void        start_next_deathmatch();


public string
npc_desc(int position, string opponent)
{
    if (!strlen(opponent))
    {
        return "not specified";
    }
    
    if (opponent == "default" && position == 1)
    {
        return "Test NPC 1 (default)";
    }
    else if (opponent == "default" && position == 2)
    {
        return "Test NPC 2 (default)";
    }
    
    if (file_size(DATA_DIR + opponent + ".o") >= 0)
    {
        return "Test NPC: " + opponent + " (data file)";
    }

    if (file_size(opponent) >= 0)
    {
        return opponent;
    }
        
    return "unavailable";
}

public object
clone_test_npc(int position, string opponent)
{
    setuid();
    seteuid(getuid());

    object npc;
    if (file_size(DATA_DIR + opponent + ".o") >= 0)
    {
        send_debug_message("testroom_base", "Cloning a test npc for position " + position + " with data file " + DATA_DIR + opponent + ".o.");
        if (position == 1)
        {
            npc = clone_object(TEST_NPC);
            npc->load_from_mapping(first_npc_data);
        }
        else if (position == 2)
        {
            npc = clone_object(TEST_NPC);
            npc->load_from_mapping(second_npc_data);
        }
    }
    else if (file_size(opponent) >= 0)
    {
        send_debug_message("testroom_base", "Cloning a test npc for position " + position + " with file " + opponent + ".");        
        npc = clone_object(opponent);
        clone_object(DAMAGE_TRACKER_SH)->shadow_me(npc);
        npc->set_is_tracking(1);
        npc->add_prop(NPC_I_NO_UNARMED, 0);
        npc->arm_me();
        npc->equip_me();
    }
    else
    {
        send_debug_message("testroom_base", "Cloning a default test npc for position " + position + ".");
        if (position == 1)
        {
            npc = clone_object(TEST_NPC);
            npc->load_from_mapping(first_npc_data);
        }
        else if (position == 2)
        {
            npc = clone_object(TEST_NPC);
            npc->load_from_mapping(second_npc_data);
        }
    }

    if (!objectp(npc))
    {
        write("Unable to create a test npc from opponent " + opponent + ".\n");
    }
    return npc;
}

public string
long_desc()
{
    string long_desc = "";
    long_desc += 
          "This is a bare room that is used primarily for testing "
        + "guilds against each other.\n\n"
        + "   Basic Commands:\n"
        + "      setup npcs                     - Create the pairs of opponents.\n"
        + "      start tests                    - Begin the actual testing.\n"
        + "      start matches                  - Begins the gamut of tests with Opponent 1\n"
        + "      stop tests                     - Stop all the fighting.\n"
        + "      report                         - Generates a report of the current stats.\n"
        + "\n"
        + "   Test Options Commands:\n"
        + "      opponents                      - List the available predefined opponents\n"
        + "      opponent <num> <file>          - Set the opponent (file in data directory)\n"
        + "                                         1. " + npc_desc(1, opponent_one) + "\n"
        + "                                         2. " + npc_desc(2, opponent_two) + "\n"
        + "      duration <seconds>             - Sets a duration to end the test [" + total_duration + "]\n"
        + "      numtests <number>              - Sets up number of fights [" + total_fights + "]\n"
        + "      death [true/false]             - Sets up whether testroom allows death [" + (fight_to_death ? "true" : "false") + "]\n"
        + "\n"
        + "   Default NPC Customization:\n"
        + "      showopponent <num>             - Shows the customized information for the opponent\n"
        + "      changeprop <num> <prop> <val>  - Changes the property of the opponent\n"
        + "      copyprops <num> <file>         - Copies the properties from a data file to the opponent\n"
        + "      addeq <num> <file>             - Adds an equipment file to load for the opponent\n"
        + "      remeq <num> <file>             - Removes an equipment file to load for the opponent\n"
        + "\n";
     
     return long_desc;    
}

public void
create_room()
{
    ::create_room();
    
    set_short("Guild Testing Room");
    set_long(&long_desc());
        
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_SUNLIGHT, sunlight);
    set_opponent_files();    
}

public void
create_opponent_pair()
{
    object one, two;

    setuid();
    seteuid(getuid());
    one = clone_test_npc(1, opponent_one);
    if (!objectp(one))
    {
        write("Unable to clone the first npc in the npc pair.\n");
        return;
    }

    two = clone_test_npc(2, opponent_two);
    if (!objectp(two))
    {
        write("Unable to clone the second npc in the npc pair.\n");        
        one->remove_object();
        return;
    }
    
    one->move(this_object());
    two->move(this_object());
    opponents[one] = two;
}

public void
set_opponent_files()
{
}

public void
create_pairs_delayed(int remaining)
{
    string error = catch(create_opponent_pair());
    if (strlen(error))
    {
        send_debug_message("testroom_base", "An error occurred while creating the opponent pair: " + error);
    }
    
    if (--remaining > 0) {
        set_alarm(0.1, 0.0, &create_pairs_delayed(remaining));
    }
}

public int
create_test_npcs(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    if (!arg || lower_case(arg) != "npcs")
    {
        notify_fail("Setup npcs?\n");
        return 0;
    }
    
    opponents = ([ ]); // reset the mapping.
    create_pairs_delayed(total_fights);
    return 1;
}

public void
do_extra_actions(object attacker, object target)
{
}

private int
start_tests_helper()
{
   foreach (object fighter : m_indices(opponents))
    {
        if (!objectp(fighter) || !objectp(opponents[fighter]))
        {
            continue;
        }
        
        int disallow_damage = fight_to_death ? 0 : 1;
        fighter->set_prevent_damage(disallow_damage);
        opponents[fighter]->set_prevent_damage(disallow_damage);
        fighter->attack_object(opponents[fighter]);
        do_extra_actions(fighter, opponents[fighter]);
    }
    
    test_alarm = set_alarm(itof(total_duration), 0.0, &stop_tests("tests"));
}

private int
start_deathmatches()
{
    fight_to_death = 1;
    total_fights = 1;
    deathmatch_mode = 1;
    start_next_deathmatch();
}

public int
start_tests(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    if (!arg || (arg != "tests" && arg != "matches"))
    {
        notify_fail("Start tests or matches?\n");
        return 0;
    }
    
    switch (arg)
    {
    case "tests":
        start_tests_helper();
        break;
    
    case "matches":
        // We want to set the following properties
        // num_tests = 1
        // death = true
        // Then begin the death matches
        start_deathmatches();
        break;
    }
    
    return 1;
}

public string
generate_report()
{
    string result = "";    
    mixed totals = ({  });
    int damage1, time1, damage2, time2;
    
    foreach (object fighter : m_indices(opponents))
    {
        if (!objectp(fighter) || !objectp(opponents[fighter]))
        {
            continue;
        }
        
        mixed data = fighter->query_damage_data()
                     + opponents[fighter]->query_damage_data();
        totals += ({ data });
    }
    
    result += "\n";
    result += "Opponent 1: " + opponent_one + "\n";
    result += "Opponent 2: " + opponent_two + "\n";
    result += "===================================================================================\n";
    result += sprintf("%s\t%s\t%s\t\t\t%s\t%s\t%s\n",
        "Damage", "Time (seconds)", "Std Dev",
        "Damage", "Time (seconds)", "Std Dev");
    result += "-----------------------------------------------------------------------------------\n";

    foreach (mixed line : totals)
    {
        damage1 += line[0];
        time1 += line[1];
        damage2 += line[3];
        time2 += line[4];
        float stddev1 = standard_deviation(line[2]);
        float stddev2 = standard_deviation(line[5]);
        result += sprintf("%d\t%d\t\t%.2f\t\t\t%d\t%d\t\t%.2f\n", 
            line[0], line[1], (floatp(stddev1) ? stddev1 : itof(0)),
            line[3], line[4], (floatp(stddev2) ? stddev2 : itof(0)));
    }
    result += "-----------------------------------------------------------------------------------\n";
    result += damage1 + "\t" + time1 + "\t\t\t\t\t" + damage2 + "\t" + time2 + "\n";
    if (time1 != 0 && time2 != 0)
    {
        result += "Opponent 1 DPS: " + sprintf("%.2f", itof(damage1) / itof(time1)) + "\n";
        result += "Opponent 2 DPS: " + sprintf("%.2f", itof(damage2) / itof(time2)) + "\n";
    }
    else
    {
        result += "DPS not defined.\n";
    }
    
    return result;
}

public int
stop_tests(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }
    
    if (!arg || arg != "tests")
    {
        notify_fail("Stop tests?\n");
        return 0;
    }
    
    foreach (object fighter : m_indices(opponents))
    {
        if (!objectp(fighter) || !objectp(opponents[fighter]))
        {
            continue;
        }
        
        fighter->stop_fight(opponents[fighter]);
        opponents[fighter]->stop_fight(fighter);
    }
    
    send_debug_message("dps_reports", generate_report(), 
        "/d/Genesis/specials/guilds/test/log/dps_reports.txt");
    remove_alarm(test_alarm);
    test_alarm = 0;
    deathmatch_mode = 0;
    
    return 1;
}

public int
set_duration(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int duration;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: duration <seconds>\n");
        return 0;
    }
    
    duration = atoi(arg);
    if (!duration || duration < 0)
    {
        notify_fail("Please specify a valid duration.\n");
        return 0;
    }
    
    total_duration = duration;
    write("Ok.\n");
    return 1;
}

public int
set_numtests(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int num;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: numtests <number>\n");
        return 0;
    }
    
    num = atoi(arg);
    if (!num || num < 0)
    {
        notify_fail("Please specify a valid number to test.\n");
        return 0;
    }
    
    total_fights = num;
    write("Ok.\n");
    return 1;
}

public int
set_opponent(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int oppnum;
    string filename;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: opponent <number> <file>\n");        
        return 0;  
    }
    
    if (sscanf(arg, "%d %s", oppnum, filename) != 2)
    {
        notify_fail("Please specify a number and a filename or datafile.\n");
        return 0;
    }
    
    if (file_size(DATA_DIR + filename + ".o") >= 0)
    {
        // If we are looking at a predefined data file, we load the info into
        // the appropriate mapping.
        switch (oppnum)
        {
        case 2:
            write("Setting second opponent to " + filename + "\n");
            second_npc_data = restore_map(DATA_DIR + filename);
            opponent_two = filename;
            break;
        default:
            write("Setting first opponent to " + filename + "\n");
            first_npc_data = restore_map(DATA_DIR + filename);
            opponent_one = filename;
        }
        return 1;
    }
    
    // At this point, we are looking for an actual filename of the npc,
    // rather than a predefined data file.
    if (file_size(filename) < 0
        && file_size(filename + ".c") < 0)
    {
        notify_fail("Please specify a valid filename.\n");
        return 0;
    }
    
    // If the file specified doesn't have .c, we add it here.
    if (file_size(filename + ".c") > 0)
    {
        filename = filename + ".c";
    }
    
    switch (oppnum)
    {
    case 2:
        write("Setting second opponent to " + filename + "\n");
        opponent_two = filename;
        break;
    
    default:
        write("Setting first opponent to " + filename + "\n");
        opponent_one = filename;
    }
    
    return 1;
}

public int
report_totals(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }
    write(generate_report());
    return 1;
}

public int
deathfight(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    if (!strlen(arg))
    {
        notify_fail("Do you wish to allow death? True or false?\n");
        return 0;
    }
    
    if (arg == "true")
    {
        fight_to_death = 1;
    }
    else if (arg == "false")
    {
        fight_to_death = 0;
    }
    
    write("Ok!\n");
    return 1;
}

private void
start_next_deathmatch()
{
    // Only start the next death match if we're in deathmatch mode
    if (!deathmatch_mode)
    {
        return;
    }
        
    // First clean all the objects from the room
    object * all_objects = all_inventory(this_object());
    foreach(object target : all_objects)
    {
        if (query_interactive(target))
            continue;

        /* Try to remove it the easy way if possible. */
        catch(target->remove_object());

        /* Destruct if the hard way if it still exists. */
        if (objectp(target))
        {
            SECURITY->do_debug("destroy", target);
        }
    }    

    // We continue onto the next death match if there is one
    if (sizeof(deathmatch_list))
    {
        opponent_two = 0;
        while (!strlen(opponent_two)
               || file_size(opponent_two) <= 0)
        {
            opponent_two = deathmatch_list[0];
            deathmatch_list = deathmatch_list[1..];
            if (strlen(opponent_two))
            {
                send_debug_message("testroom_base", "Selecting death match opponent " + opponent_two);
            }
            if (sizeof(deathmatch_list) == 0)
            {
                send_debug_message("testroom_base", "This is the last death match opponent.");
                break;
            }
        }
        opponents = ([ ]); // reset the mapping
        catch(create_opponent_pair());
        remove_alarm(test_alarm);
        test_alarm = set_alarm(5.0, 0.0, start_tests_helper);
    }
    else
    {
        deathmatch_mode = 0;
    }
}

/*
 * Function:    notify_death_occurred
 * Description: This is the function called by the damage tracker shadow
 *              when a death occurs. We use this to report the results
 *              and also start the next death match
 */
public void
notify_death_occurred(object killer, object killed)
{
    tell_room(this_object(), QCTNAME(killer) + " killed " + QTNAME(killed)
        + " in " + killer->query_damage_data()[1] + " seconds with "
        + killer->query_hp() + " (" 
        + (killer->query_hp() * 100 / killer->query_max_hp()) + "%) hit points left.\n");
    send_debug_message("dps_reports", killer->short() + " killed " + killed->short()
        + " in " + killer->query_damage_data()[1] + " seconds with "
        + killer->query_hp() + " (" 
        + (killer->query_hp() * 100 / killer->query_max_hp()) + "%) hit points left.\n", 
        "/d/Genesis/specials/guilds/test/log/dps_reports.txt");
    
    start_next_deathmatch();
}

private string
format_data_property(mixed property)
{
    if (pointerp(property))
    {
        property = implode(property, ",");
    }
    
    if (!strlen(property))
    {
        return "Unspecified";
    }
    
    // remove the newline at the end (trim)
    sscanf(property, "%s\n", property);
    
    if (property == "")
    {
        return "Unspecified";
    }
    
    return property;
}

/*
 * Function:    print_npc_data
 * Description: This function prints the npc data that is associated
 *              and provided by the mapping. This is useful for allowing
 *              the observers to see what is currently configured for
 *              a particular test npc.
 */
public string
print_npc_data(mapping data)
{
    string output = "";
    output += sprintf("%35-s%s\n", "Track Damage [track]:", (data["track_damage"] ? "Yes" : "No"));
    output += sprintf("%35-s%s\n", "Prevent Damage [prevent]:", (data["prevent_damage"] ? "Yes" : "No"));
    output += sprintf("%35-s%s\n", "Guilds [guilds]:", format_data_property(data["guilds"]));
    output += sprintf("%35-s%s\n", "Default Commands [commands]:", format_data_property(data["commands"]));
    output += sprintf("%35-s%s\n", "Names [names]:", format_data_property(data["names"]));
    output += sprintf("%35-s%s\n", "Short Desc [short]:", data["short_desc"]);
    output += sprintf("%35-s%s\n", "Long Desc [long]:", format_data_property(data["long_desc"]));
    if (sizeof(data["base_stats"]) >= 6)
    {
        int stat_avg = (data["base_stats"][0] + data["base_stats"][1] + data["base_stats"][2] + data["base_stats"][3] + data["base_stats"][4] + data["base_stats"][5]) / 6;
        output += sprintf("%35-s%d\n", "Stat Avg [stat]:", stat_avg);
    }
    output += sprintf("%35-s%s\n", "Race [race]:", data["base_race"]);
    output += sprintf("%35-s%s\n", "Setup Function [setup]:", format_data_property(data["setup_function"]));
    output += sprintf("%35-s%s\n", "Specials Function [special]:", format_data_property(data["special_attack_function"]));
    output += sprintf("%35-s%s\n", "Spell Notify Function [notify]:", format_data_property(data["spell_notify_function"]));
    output += sprintf("%35-s%d\n", "Alignment [alignment]:", data["alignment"]);
    if (sizeof(data["equipment"]))
    {
        output += "Equipment:\n";
        int index = 1;
        foreach (string eq_item : data["equipment"])
        {
            if (objectp(safely_load_master_file(eq_item)))
            {
                output += sprintf("  %d. %s [%s]\n", index, eq_item->short(), eq_item);
            }
            else
            {
                output += sprintf("  %d. Invalid or Unloaded Item [%s]\n", index, eq_item);
            }
            ++index;
        }
    }
    
    return output;       
}

public int
do_showopponent(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int oppnum;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: showopponent <number>\n");        
        return 0;  
    }
    
    if (sscanf(arg, "%d", oppnum) != 1 || (oppnum != 1 && oppnum != 2))
    {
        notify_fail("Please specify a opponent number of either 1 or 2\n");
        return 0;
    }
    
    switch (oppnum)
    {
    case 1:
        write(print_npc_data(first_npc_data) + "\n");
        break;
        
    case 2:
        write(print_npc_data(second_npc_data) + "\n");
        break;
        
    default:
        return 0;
    }
    
    return 1;
}

public int
do_changeprop(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int oppnum;
    string propname, propvalue;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: changeprop <num> <prop> <val>\n");        
        return 0;  
    }
    
    if (sscanf(arg, "%d %s %s", oppnum, propname, propvalue) != 3)
    {
        notify_fail("Usage: changeprop <num> <prop> <value>.\n");
        return 0;
    }
    
    if (oppnum != 1 && oppnum != 2)
    {
        notify_fail("Please specify a opponent number of either 1 or 2.\n");
        return 0;
    }
    
    if (!strlen(propname))
    {
        notify_fail("Please specify a valid property name.\n");
        return 0;
    }
    
    mapping data_to_modify;
    if (oppnum == 1)
    {
        data_to_modify = first_npc_data;
    }
    else
    {
        data_to_modify = second_npc_data;
    }
    
    propname = lower_case(propname);
    switch (propname)
    {
    case "track":
        {
            if (propvalue == "yes")
            {
                data_to_modify["track_damage"] = 1;
            }
            else if (propvalue == "no")
            {
                data_to_modify["track_damage"] = 0;
            }
            else
            {
                int bTrack;
                if (sscanf(propvalue, "%d", bTrack) != 1)
                {
                    notify_fail("Please enter either \"Yes\" or \"No\" for this property.\n");
                    return 0;
                }
                bTrack = min(1, max(0, bTrack));
                data_to_modify["track_damage"] = bTrack;
            }
        }
        break;
        
    case "prevent":
        {
            if (propvalue == "yes")
            {
                data_to_modify["prevent_damage"] = 1;
            }
            else if (propvalue == "no")
            {
                data_to_modify["prevent_damage"] = 0;
            }
            else
            {
                int bPrevent;
                if (sscanf(propvalue, "%d", bPrevent) != 1)
                {
                    notify_fail("Please enter either \"Yes\" or \"No\" for this property.\n");
                    return 0;
                }
                bPrevent = min(1, max(0, bPrevent));
                data_to_modify["prevent_damage"] = bPrevent;
            }
        }
        break;
        
    case "alignment":
        {
            int alignment;
            if (sscanf(propvalue, "%d", alignment) != 1)
            {
                notify_fail("Please enter a valid number between -1200 and 1200.\n");
                return 0;
            }
            alignment = min(1200, max(-1200, alignment));
            data_to_modify["alignment"] = alignment;
        }
        break;

    case "stat":
        {
            int average;
            if (sscanf(propvalue, "%d", average) != 1)
            {
                notify_fail("Please enter a valid number between 1 and 500.\n");
                return 0;
            }
            average = min(500, max(1, average));
            data_to_modify["base_stats"] = ({ average, average, average, average, average, average, average, average, average, average });;
        }
        break;

    case "guild":
    case "guilds":
        data_to_modify["guilds"] = explode(propvalue, ",");
        break;
        
    case "command":
    case "commands":
        data_to_modify["commands"] = explode(propvalue, ",");
        break;
    
    case "name":
    case "names":
        data_to_modify["names"] = explode(propvalue, ",");
        break;

    case "short":
        data_to_modify["short_desc"] = propvalue;
        break;
        
    case "long":
        data_to_modify["long_desc"] = propvalue;
        break;
        
    case "race":
        data_to_modify["base_race"] = propvalue;
        break;
        
    case "setup":
        data_to_modify["setup_function"] = propvalue;
        break;
        
    case "special":
        data_to_modify["special_attack_function"] = propvalue;
        break;
        
    case "notify":
        data_to_modify["spell_notify_function"] = propvalue;
        break;
    
    default:
        notify_fail("Please specify a valid property name.\n");
        return 0;
    }
    if (oppnum == 1)
    {
        first_npc_data = data_to_modify;
    }
    else
    {
        second_npc_data = data_to_modify;
    }
    
    // Changes have been persisted.
    write("Ok!\n");
    return 1;    
}

public int
do_copyprops(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int oppnum;
    string filename;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: copyprops <num> <file>\n");        
        return 0;  
    }
    
    if (sscanf(arg, "%d %s", oppnum, filename) != 2)
    {
        notify_fail("Please specify a number and valid datafile.\n");
        return 0;
    }
    
    if (file_size(DATA_DIR + filename + ".o") < 0
        && file_size(filename) < 0)
    {
        notify_fail("Please specify a valid datafile.\n");
        return 0;
    }
    
    switch (oppnum)
    {
    case 2:
        write("Copying datafile properties from " + filename + " to second default npc\n");
        if (file_size(DATA_DIR + filename + ".o") <= 0)
        {
            notify_fail("Copying failed. Please check the filename.\n");
            return 0;
        }
        
        second_npc_data = restore_map(DATA_DIR + filename);        
        break;
            
    default:
        write("Copying datafile properties from " + filename + " to first default npc\n");
        if (file_size(DATA_DIR + filename + ".o") <= 0)
        {
            notify_fail("Copying failed. Please check the filename.\n");
            return 0;
        }
        
        first_npc_data = restore_map(DATA_DIR + filename);
        break;
    }
            
    return 1;
}

public int
do_addeq(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int oppnum;
    string filename;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: addeq <num> <file>\n");        
        return 0;  
    }
    
    if (sscanf(arg, "%d %s", oppnum, filename) != 2)
    {
        notify_fail("Usage: addeq <num> <file>\n");
        return 0;
    }
    
    if (oppnum != 1 && oppnum != 2)
    {
        notify_fail("Please specify a opponent number of either 1 or 2.\n");
        return 0;
    }
    
    if (!strlen(filename) || file_size(filename) == 0)
    {
        notify_fail("Please specify a valid equipment filepath.\n");
        return 0;
    }
    
    if (oppnum == 1)
    {
        first_npc_data["equipment"] += ({ filename });
    }
    else
    {
        second_npc_data["equipment"] += ({ filename });
    }
    
    write("Ok!\n");
    return 1;
}

public int
do_remeq(string arg)
{
    if (!this_player()->query_wiz_level())
    {
        notify_fail("You are not a wizard!\n");
        return 0;
    }

    int oppnum;
    string filename;
    
    if (!arg || !strlen(arg))
    {
        notify_fail("Usage: remeq <num> <file>\n");        
        return 0;  
    }
    
    if (sscanf(arg, "%d %s", oppnum, filename) != 2)
    {
        notify_fail("Usage: remeq <num> <file>\n");
        return 0;
    }
    
    if (oppnum != 1 && oppnum != 2)
    {
        notify_fail("Please specify a opponent number of either 1 or 2.\n");
        return 0;
    }
    
    if (!strlen(filename))
    {
        notify_fail("Please specify a valid equipment filepath.\n");
        return 0;
    }
    
    if (oppnum == 1)
    {
        first_npc_data["equipment"] -= ({ filename });
    }
    else
    {
        second_npc_data["equipment"] -= ({ filename });
    }
    write("Ok!\n");
    
    return 1;
}

public int
list_opponents(string arg)
{
    string * opponent_files = filter(get_dir(DATA_DIR), &wildmatch("*.o",));
    if (!sizeof(opponent_files))
    {
        notify_fail("There are no predefined opponents in " + DATA_DIR + ".\n");
        return 0;
    }
    
    write("Here is a list of all the predefined opponent files:\n");
    int index = 1;
    foreach (string opponent_file : opponent_files)
    {
        write(sprintf("%3d. %s\n", index, opponent_file[..-3]));
        ++index;
    }
    
    return 1;
}

public void
init()
{
    ::init();
    add_action("start_tests", "start");
    add_action("create_test_npcs", "setup");
    add_action("stop_tests", "stop");
    add_action("set_duration", "duration");
    add_action("set_numtests", "numtests");
    add_action("set_opponent", "opponent");
    add_action("list_opponents", "opponents");
    add_action("report_totals", "report");
    add_action("deathfight", "death");
    add_action("do_showopponent", "showopponent");
    add_action("do_changeprop", "changeprop");
    add_action("do_copyprops", "copyprops");
    add_action("do_addeq", "addeq");
    add_action("do_remeq", "remeq");
}

public int
sunlight(object room)
{
    // These rooms never have any sunlight so that vampires can walk
    // in them freely.
    return 0;
}

/*
 * List of NPC Enemies

Ashburz - /d/Shire/moria/npc/urukcap.c
Barash-Gund - /d/Gondor/arnor/npc/massive_troll.c
Baxter - /d/Ansalon/kalaman/living/captain.c
Calof - /d/Ansalon/kalaman/living/calof.c
Ealanus - /d/Ansalon/kalaman/living/half-elf.c
Emerald - /d/Ansalon/balifor/flotsam_forest/living/g_dragon.c
Ent - /d/Gondor/fangorn/npc/ent.c
Fael-Thas - /d/Krynn/icewall/castle2/npc/fael-thas.c
Garren (to kdie) - /d/Ansalon/taman_busuk/mountains/living/fallen_knight.c
Hathamir - /d/Gondor/ithilien/camp/npc/hathamir.c
Huorn - /d/Gondor/fangorn/npc/huorn.c
Inn Guard - /d/Gondor/rohan/edoras/npc/innguard.c
Jadestone - /d/Avenir/common/bazaar/NPCS/jadestone.c
Qualthas - /d/Krynn/qualinesti/npc/qualthas.c
Thimah - /d/Krynn/solace/new_village/town_square/thimah/npc/thimah.c
Thorr-kan - /d/Ansalon/goodlund/nethosak/forest/npc/trollShaman.c
Yeti - /d/Krynn/icewall/castle2/npc/arcticyeti.c
Zahrtok - /d/Krynn/solace/new_village/town_square/npcs/zahrtok.c
 
 
Alluring slender female human - 
Half-troll (shaws)
Minotaur King
Mithas Troll
Qualinesti elf
Shadow-elf
Terrible troll (Shaws)
Uruk-hai
*/
