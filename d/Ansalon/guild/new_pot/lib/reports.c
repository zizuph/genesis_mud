/* Stralle @ Genesis 041221
 */
#pragma strict_types

/* Guild ------> <guild name>            <- >=Priest access
 *        \----> General
 * Meetings ---> Council                 <- Council access
 *           \-> PoT
 * Pilgrims ---> <per name of pilgrim>   <- >=Second cleric step access
 * Mentor -----> <per name of cleric>    <- >=Priest access
 *         \---> General
 * Travel -----> <per name of member>    <- Clerics can read their own 
 *         \---> General                    Priests can read priests and clerics
 *                                          High priests everything
 *
 * File structure (numbers are time() values):
 * <path>/guild/general/r1234567890
 * <path>/guild/Priests of Takhisis/r1234567890
 * <path>/meetings/council/r1234567890
 * <path>/meetings/council/r1234567891
 * <path>/pilgrims/strallejr/r1234567890
 * <path>/mentor/general/r1234567890
 * <path>/travel/strallejr/r1234567890
 * <path>/travel/strallejr/r1234567891
 *
 * Reports are generated at runtime by concatenating the files in the
 * directory of choice. Should be a function to pipe the output to a
 * file instead for added comfort for snooping wizards :)
 *
 * Use:
 *
 * inherit "/path/to/this/file";
 * ...
 * void
 * create_xxx()
 * {
 *    set_path("/path/to/reports");
 *    ...
 * }
 * ...
 * void
 * init()
 * {
 *     ::init();
 *
 *     init_reports();
 * }
 */ 

#include "../guild.h"
#include <files.h>

#define R_COUNCIL       (1 << 0)
#define R_PRIEST        (1 << 1)
#define R_2NDCLERIC     (1 << 2)
#define R_INDIVIDUAL    (1 << 3)

#define R_GUILDS        (1 << 0)
#define R_MEMBERS       (1 << 1)
#define R_PILGRIMS      (1 << 2)
#define R_CLERICS       (1 << 3)

mapping gSections = ([ "guild" : ({ R_PRIEST, ({ "general", R_GUILDS }) }),
                       "meetings" : ({ R_COUNCIL, ({ "council", "pot" }) }),
                       "pilgrims" : ({ R_2NDCLERIC, ({ R_PILGRIMS }) }),
                       "mentor" : ({ R_PRIEST, ({ "general", R_CLERICS }) }),
                       "travel" : ({ R_INDIVIDUAL, ({ "general", R_MEMBERS }) }) ]);
string gPath;

/* Function name: name_list
 * Description:   Sections can be of different kind depending on what
 *                type of information is stored. This will return the
 *                associated array of their contents, for instance
 *                current members or pilgrims.
 * Arguments:     int what - what type of section it is
 * Returns:       string * - the array of their contents.
 */
string *
name_list(int what)
{
    string *arr;
    int x, size;

    switch (what)
    {
        case R_GUILDS:
            /* Need support functions in admin and the guildshadow
             * to save new guildnames whenever a member is introduced
             * to a new player
             */
            break;
        case R_MEMBERS:
            /* All registered members save for wizards and their jr's
             */
            for (x = 0, arr = GUILD_ADMIN->query_guild_list() ;
                 x < sizeof(arr) ; x++)
            {
                if (wildmatch("*jr", arr[x]) ||
                    SECURITY->query_wiz_level(arr[x]))
                {
                    arr = exclude_array(arr, x, x);
                    x--;
                }
            }

            arr = sort_array(arr);

            return arr;
        case R_PILGRIMS:
            /* All pilgrims
             */
            return (sort_array(GUILD_ADMIN->query_pilgrims()));
        case R_CLERICS:
            /* All members who are still on the cleric step save for
             * wizards and their jr's
             */
            for (x = 0, arr = GUILD_ADMIN->query_guild_list() ;
                 x < sizeof(arr) ; x++)
            {
                if (GUILD_ADMIN->query_guild_level(arr[x]) >= 50 ||
                    wildmatch("*jr", arr[x]) ||
                    SECURITY->query_wiz_rank(arr[x]))
                {
                    arr = exclude_array(arr, x, x);
                    x--;
                }
            }

            arr = sort_array(arr);

            return arr;
    }

    return 0;
}

/* Function name: has_access
 * Description:   Checks whether one has access
 * Arguments:     int access  - the R_ definition above
 *                object who  - the one who wants access
 *                string name - the one who wants information about
 * Returns:       int - 1/0, access or no access
 */
varargs int
has_access(int access, object who, string name = "")
{
    if (SECURITY->query_wiz_rank(who->query_real_name()))
        return 1;

    switch (access)
    {
        case R_COUNCIL:
            return (member_array(who->query_real_name(),
                GUILD_ADMIN->query_guild_council()) >= 0);
        case R_PRIEST:
            return (who->query_priest_level() >= GUILD_LEVEL_PRIEST);
        case R_2NDCLERIC:
            return (who->query_skill(PS_GUILD_LEVEL) >= 10);
        case R_INDIVIDUAL:
            return (who->query_priest_level() >= GUILD_LEVEL_PRIEST &&
                who->query_priest_level() >=
                who->query_priest_level(GUILD_ADMIN->query_guild_level(name)) ||
                who->query_real_name() == name);
    }
}

/* Function name: describe_access
 * Description:   Describes in textform what a certain access type is
 * Arguments:     int access - the access type
 * Returns:       string - the description of the access type
 */
string
describe_access(int access)
{
    switch (access)
    {
        case R_COUNCIL:
            return "council only";
        case R_PRIEST:
            return "priests and above";
        case R_2NDCLERIC:
            return "acolytes and above";
        case R_INDIVIDUAL:
            return "ones own entries and those below";
        default:
            return "<n/a>";
    }
}

/* Function name: print_index
 * Description:   Gets called for each value in the index to print it
 * Arguments:     string index - the report section
 *                object who   - what player wants it
 * Returns:       string - the line to print
 */
string
print_index(string index, object who)
{
    string str;
    
    str = sprintf("%-10s access given to %-21s\n",
        capitalize(index), describe_access(gSections[index][0]));

    return str;
}

/* Function name: list_index
 * Description:   Lists the index of the reports. This is what is
 *                given by the list command without argument.
 * Arguments:     object who - what player wants the listing
 * Returns:       string - the listing
 */
string
list_index(object who)
{
    string ret = "", *arr = m_indices(gSections);
    int x, size;
    
    for (x = 0, size = sizeof(arr) ; x < size ; x++)
    {
        switch (arr[x])
        {
            case "guild":
                /* No support quite yet
                 */
                continue;
            case "meetings":
            case "mentor":
            case "pilgrims":
                if (!has_access(gSections[arr[x]][0], who))
                    continue;
            case "travel":
                if (!has_access(gSections[arr[x]][0], who, ""))
                    continue;
            default:
                ret += print_index(arr[x], who) + "\n";
        }
    }
    
    return ret;
}

/* Function name: set_path
 * Description:   We need to set a path where to save report files
 * Arguments:     string path - the path
 */
void
set_path(string path)
{
    string gPath = path;
}

/* Function name: query_path
 * Description:   Returns the previously set path
 * Returns:       string - the path
 */
string
query_path()
{
    return gPath;
}

int
ls_sort_t(mixed file1, mixed file2)
{
    return file1[1] - file2[1];
}

/* Function name: report2files
 * Description:   For a given report by section and name, this
 *                function returns all the files associated with
 *                it in reverse filetime order.
 * Arguments:     string section - the section
 *                string name    - the reportname
 * Returns:       string * - the files or 0 if non-existant
 */
string *
report2files(string section, string name)
{
    int x, size;
    mixed tmp;
    string *files = ({});

    if (member_array(section, m_indices(gSections)) < 0)
        return 0;
    if (member_array(name, name_list(gSections[section][0])) < 0 &&
        member_array(name, gSections[section][1]) < 0)
        return 0;
        
    if (file_size(query_path() + "/reports/" + section + "/" + name) == -2)
    {    
        files = get_dir(query_path() + "/reports/" + section + "/" + name);
        files -= ({ ".", ".." });
    }
    
    for (tmp = ({ }), x = 0, size = sizeof(files) ; x < size ; x++)
    {
        tmp += ({ ({ files[x], file_time(files[x]) }) });
    }
    
    tmp = sort_array(tmp, "ls_sort_t", this_object());
    
    for (x = 0 ; x < size ; x++)
    {
        files[x] = tmp[x][0];
    }
    
    return files;
}

string
mon_full(string m)
{
    switch (m)
    {
        case "Jan":
            return "January";
        case "Feb":
            return "February";
        case "Mar":
            return "March";
        case "Apr":
            return "April";
        case "May":
            return m;
        case "Jun":
            return "June";
        case "Jul":
            return "July";
        case "Aug":
            return "August";
        case "Sep":
            return "September";
        case "Oct":
            return "October";
        case "Nov":
            return "November";
        case "Dec":
            return "December";
    }
}

string
ord_short(int num)
{
    switch (num)
    {
        case 1:
        case 21:
        case 31:
            return "st";
        case 2:
        case 22:
            return "nd";
        case 3:
        case 23:
            return "rd";
        default:
            return "th";
    }
}

string
print_filedate(string file)
{
    string m;
    int d, y, x;
    
    sscanf(ctime(file_time(file))[4..], "%s %d %d:%d:%d %d",
        m, d, x, x, x, y);

    return d + ord_short(d) + " of " + mon_full(m) + " " + y;
}

/* Function name: print_date
 * Description:   Turns a filetime into something human readable
 * Arguments:     string section - the section
 *                string name    - the reportname
 *                int type       - >0; time for a specific entry
 *                                  0; time for the last entry
 * Returns:       string - the time or "n/a" if an non-existant entry
 */
varargs string
print_date(string section, string name, int type = 0)
{
    string m, *files = report2files(section, name);
    int d, y, x;

    if (!files || !sizeof(files))
        return "n/a";
    
    return print_filedate(files[type]);
}
    
/* Function name: print_section
 * Description:   Gets called for each value in the section to print it
 * Arguments:     string section - the report section
 *                string name    - the report name
 * Returns:       string - the line to print
 */
string
print_section(string section, string name)
{
    string str;

#ifdef 1
    dump_array(section);
    dump_array(name);
#endif
    
    /* So that already capitalised entries will be left untouched
     * while others will be capitalised
     */
    str = sprintf("%-15s last entry on %-16s\n",
        (lower_case(name) == name ? capitalize(name) : name),
        print_date(section, name));
    
    return str;
}

/* Function name: list_section
 * Description:   Lists the contents of a section. This is what is
 *                given by the list command with argument.
 * Arguments:     string section - the section
 *                object who     - what player wants the listing
 * Returns:       string - the listing
 */
string
list_section(string section, object who)
{
    int x, size, nlist = -1;
    string *arr, ret = "";

    if (member_array(section, m_indices(gSections)) < 0)
        return 0;
    
    switch (section)
    {
        case "guild":
            /* No support quite yet
             */
            break;
        case "meetings":
        case "mentor":
        case "pilgrims":
            if (!has_access(gSections[section][0], who))
                return 0;
        case "travel":
            if (!has_access(gSections[section][0], who, ""))
                return 0;
        default:
            break;
    }

    for (x = 0 ; x < sizeof(gSections[section][1]) ; x++)
    {
        if (intp(gSections[section][1][x]))
            nlist = gSections[section][1][x];
        else
            ret += print_section(section, gSections[section][1][x]);
    }

    if (nlist == -1)
        return ret;
    
    for (x = 0, arr = name_list(nlist), size = sizeof(arr) ; x < size ; x++)
    {
        ret += print_section(section, arr[x]);
    }

    return ret;
}

int
do_index(string arg)
{
    string str;
    
    if (!arg && !strlen(arg))
    {
        str = list_index(this_player());

        /* No access at all. Non-member possibly
         */
        if (!strlen(str))
            return 0;
            
        write(str);
        return 1;
    }
    
    str = list_section(arg, this_player());
    if (!str)
    {
        /* Or no access */
        notify_fail("No such index.\n");
        return 0;
    }
    
    write(str);
    return 1;
}

varargs string *
topic_contents(string section, object who = this_player())
{
    int x, size, nlist = -1;
    string *arr = ({ });

    /* No such section or no access
     */
    if (member_array(section, m_indices(gSections)) < 0 ||
        !has_access(gSections[section][0], who))
    {
        notify_fail("No such section available.\n");
        return 0;
    }
    
    for (x = 0 ; x < sizeof(gSections[section][1]) ; x++)
    {
        if (intp(gSections[section][1][x]))
            nlist = gSections[section][1][x];
        else
            arr += ({ gSections[section][1][x] });
    }

    if (nlist == -1)
        return arr;

    arr += name_list(nlist);
    
    return arr;
}

string
print_file(string file)
{
    int x, size;
    string text, *arr;
    
    setuid();
    seteuid(getuid());
    
    if (file_size(file) <= 0)
        return 0;
    
    arr = explode(read_file(file), "\n");

    text = "  _______________________________________________________" +
           "___________________\n" +
           "/\\                                                         " +
           "                 \\\n" +
           "\\/_________________________________________________________" +
           "_________________/\n" +
           ")                                                           " +
           "               (\n" +
           "(                    P R I E S T S   O F   T A K H I S I S  " +
           "               )\n" +
           sprintf(") %|72s (\n", print_filedate(file));

    for (x = 0, size = sizeof(arr) ; x < size ; x++)
    {
        if (x % 2)
            text += sprintf("(   %-70s )\n", arr[x]);
        else
            text += sprintf(")   %-70s (\n", arr[x]);
    }
    
    if (x % 2)
        text += "( __________________________________________________" +
                "_______________________)\n";
    else
        text += ") __________________________________________________" +
                "_______________________(\n";

    text += "/\\                                                     " +
            "                     \\\n" +
            "\\/_________________________________________________________" +
            "_________________/\n";

    return text;
}

int
do_read(string arg)
{
    string section, topic, ret, *files;
    int x, size;

    if (!arg)
    {
        notify_fail("Read in what section under what topic?\n");
        return 0;
    }
    
    if (!parse_command(arg, this_player(),
        "[in] [section] %s 'under' [topic] %s", section, topic))
    {
        notify_fail("Read in what section under what topic?\n");
        return 0;
    }
    
    if (member_array(topic, topic_contents(lower_case(section))) < 0)
    {
        notify_fail("No such topic available in " +
            capitalize(section) + "\n");
        return 0;
    }
    
    files = report2files(section, topic);
    if (!sizeof(files))
    {
        notify_fail("No content yet in that topic.\n");
        return 0;
    }
    
    for (ret = "", x = 0, size = sizeof(files) ; x < size ; x++)
    {
        ret += print_file(files[x]);
    }

    this_player()->more(ret);

    return 1;
}

int
do_write(string arg)
{
    return 0;
}

void
init_reports()
{
    add_action(do_index, "index");
    add_action(do_index, "list");
    add_action(do_index, "reports");
    
    add_action(do_read, "read");
    add_action(do_read, "rread");

    add_action(do_write, "write");
    add_action(do_write, "report");
}
