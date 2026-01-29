/*
 * /d/Sparkle/area/city/rooms/quest_control_room.c
 *
 * Quest Control Room for all quest bits
 *
 * Created by Petros, April 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

// Defines
#define COL_DOMAIN      0
#define COL_DESC        1
#define COL_GROUP       2
#define COL_BIT         3
#define COL_HINT        4
#define COL_VALIDATION  5
#define COL_ARGUMENTS   6
#define COL_LAST        COL_VALIDATION

// Inheritance
inherit "/std/room";

// Global Variables
mapping quests;

// Prototypes
public void             create_room();
public void             init();
public void             reset_room();
public mixed *          get_quests(string domain);
public string *         get_domains();
public void             read_quest_data_files();
public void             read_quest_data_file(string datafile);
public int              list_cmd(string arg);

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();
    
    add_action(list_cmd, "list");
} // init

/* 
 * Function name:       create_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_room()
{
    set_short("Genesis Quest Control Room");
    set_long("This is the main control room for all the quests in "
           + "the Donut of Genesis.\n\n");
    // Room Item Section                              

    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    
    // Exits Section

    // Read in the quest db file
    read_quest_data_files();
        
    reset_room();
} // create_room

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
} // reset_room

/*
 * Function name:        read_quest_data_files
 * Description  :        Loads all the quest data files in the
 *                       QUEST_DATA_DIR directory
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
read_quest_data_files()
{
    string * datafiles;
    
    datafiles = get_dir(QUEST_DATA_DIR);
    foreach (string datafile : datafiles)
    {
        read_quest_data_file(datafile);
    }
}

private string *
replace_escaped_commas(string * fields)
{
    string * result;
    string last_field;
    
    result = ({ });
    last_field = "";
    foreach (string field : fields)
    {
        if (field && strlen(field) > 0 && field[-1..] == "\\")
        {
            last_field += field[..-2] + ",";
            continue;
        }
        
        result += ({ last_field + field });
        last_field = "";
    }
    
    return result;
}

/*
 * Function name:        read_quest_data_file
 * Description  :        Loads specified and puts the results
 *                       in the global variable "quests"
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
read_quest_data_file(string datafile)
{
    string      filecontent;
    string *    questlines;
    string *    details;
    string      domain;
    
    if (!quests)
    {
        quests = ([ ]);
    }
    
    if (!file_size(datafile)
        || !wildmatch("*.txt", datafile))
    {
        // Quest data file is empty or doesn't exist
        return;
    }
    
    // Read the file
    filecontent = read_file(QUEST_DATA_DIR + datafile);
    questlines = explode(filecontent, "\n")[1..];
    domain = lower_case(datafile[..-5]);
    foreach (string questline : questlines)
    {
        details = explode(questline, ",");
        details = replace_escaped_commas(details);
        if (sizeof(details) < 5)
        {
            // Faulty data line. Simply continue.
            continue;
        }
        
        if (!IN_ARRAY(domain, m_indices(quests)))
        {
            // Initialize the key entry if it's not there
            quests[domain] = ({ });
        }
        
        // Quest hints can be stored either in the COL_HINT column directly, or
        // by referencing a file.
        string hintfile;
        if (wildmatch("*.txt", details[COL_HINT])
            && stringp(hintfile = QUEST_HINTS_DIR + domain + "/" + details[COL_HINT])
            && file_size(hintfile))
        {
            details[COL_HINT] = read_file(hintfile);            
        }
        
        // "quests" is an mapping of domain to detail arrays.
        quests[domain] += ({ details });
    }
}

/*
 * Function name:        get_quests
 * Description  :        Returns the "quests" global variable
 * Arguments    :        none
 * Returns      :        array of arrays containing quest information
 */
public mixed *
get_quests(string domain)
{
    if (!domain || domain == ""
        || !IN_ARRAY(lower_case(domain), m_indices(quests)))
    {
        return ({ });
    }
        
    return quests[lower_case(domain)];
}

/*
 * Function name:        get_domains
 * Description  :        Returns the domains that the quest orb current
 *                       has information for
 * Arguments    :        none
 * Returns      :        string array of the domains
 */
public string *
get_domains()
{
    return m_indices(quests);
}

/*
 * Function name:        print_domain_quests
 * Description  :        Print Information stored in the quest db
 * Arguments    :        details - array of quest lines
 * Returns      :        nothing
 */
public void
print_domain_quests(string domain, mixed * details)
{
    string validation_text;
    
    if (!details || sizeof(details) == 0)
    {
        write("Not able to find any domain quest information.\n");
        return;
    }
    
    write(capitalize(domain) + " Quest Information\n\n");
    write(sprintf("%-34s %|20s %|20s\n", 
          "----------------------------------", 
          "--------------------",
          "--------------------"));                                              
    write(sprintf("%|34s %|20s %|20s\n", "Quest Desc", "Bit Location", 
                  "Validation/Arguments"));
    write(sprintf("%-34s %|20s %|20s\n", 
          "----------------------------------", 
          "--------------------",
          "--------------------"));                                              
    foreach (string * quest : details)
    {
        if (sizeof(quest) < (COL_LAST + 1))
        {
            write("Error with detail data: " + implode(quest, ",") + "\n");
            continue;
        }
        validation_text = quest[COL_VALIDATION];
        if (sizeof(quest) > COL_ARGUMENTS)
        {
            // Means there are arguments
            validation_text += "," + implode(quest[COL_ARGUMENTS..], ",");
        }
        write(sprintf("%-34s %|20s %|20s\n", 
              quest[COL_DESC], 
              quest[COL_DOMAIN] + ": " + quest[COL_GROUP] + "," 
              + quest[COL_BIT], validation_text));
    }
    
    return;
}

/*
 * Function name:        list_cmd
 * Description  :        List the quest informatio by domain
 * Arguments    :        arg - argument
 * Returns      :        0/1 - whether successful or not
 */
public int
list_cmd(string arg)
{    
    string help_message;
    
    if (!arg)
    {
        notify_fail("List what?\n");
    }
    
    arg = lower_case(arg);
    
    if (IN_ARRAY(arg, get_domains()))
    {
        print_domain_quests(arg, get_quests(arg));
    }
    else
    {
        help_message = "Usage: list <domain>\n\n";
        help_message += "Domains with Quest Information:\n";
        foreach (string domain : get_domains())
        {
            help_message += "   " + domain + "\n";
        }
        help_message += "\n";
        
        notify_fail(help_message);
        return 0;
    }
    
    return 1;
}

