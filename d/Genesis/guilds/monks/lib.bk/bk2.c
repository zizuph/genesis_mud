/*
 * File:     support.c
 * Created:  Cirion, 1998.4.25
 * Purpose:  General support functions for the monklib and the
 *           rest of the monk guild.
 */
#pragma strict_types

#include "defs.h"
#include <ss_types.h>  /* Skill types (SS_OCCUP, et. al.) */
#include <composite.h> /* COMPOSITE_WORDS                 */
#include <std.h>       /* SECURITY                        */

// the object used for creating and sending mail
#define MAIL_OBJECT               "/secure/mail_reader"

// the object used for creating and sending mail
#define RESET_EUID                seteuid(getuid(this_object()))

/*
 * Function name: m_get_name
 * Description:   returns the name of an object if an
 *                object was passed in.
 * Arguments:     the object for whom we will be returing a name
 * Returns:       the name (lowercase)
 */
static string
m_get_name (mixed for_who)
{
    if (stringp (for_who))
        return lower_case (for_who);

    if (objectp (for_who))
        return lower_case (for_who->query_real_name ());

    return 0;

}

/*
 * Function name: m_query_monk
 * Description:   Checks to see if the player passed in is
 *                a monk or not. Should be used for all
 *                filters, checks, etc.
 * Arguments:     who: the player to check (defaults to this_player())
 *                guild_type: SS_OCCUP to check for occupational
 *                            SS_LAYMAN to check for layman
 *                            -1 to check for either (default)
 * Returns:       1 if the player is a monk, 0 otherwise
 */
public int
m_query_monk(mixed who = this_player(), int guild_type = -1)
{
    string name = m_get_name(who);

    if (stringp (who))
        return MANAGER->query_monk (name, guild_type);

    // for NPCs, we need to check the shadow, since they
    // do not show up in the registry.
    if(interactive(who))
        return MANAGER->query_monk(name, guild_type);
    else
        return who->query_monk(guild_type);
}

/*
 * Function name: m_query_council_desc
 * Description:   Return a nice short description of
 *                the council member name passed in.
 * Arguments:     who - the name of the council member
 * Returns:       the short description of the member.
 */
string
m_query_council_desc(string who)
{
    mixed   info;

    who = lower_case(who);

    info = MANAGER->get_council_info(who);

    if(!pointerp(info))
        return "";

    if(sizeof(info) < 5)
        return "";

    return info[4];
}

/*
 * Function name: m_query_wizard_or_jr
 * Description:   Checks to see if the specified player is a wizard
 *                or a jr.
 * Arguments:     who: player to check for (default is this_player())
 * Returns:       1 if player is a wizard, 2 if they are a jr, 0 otherwise
 */
varargs static int
m_query_wizard_or_jr(object who = this_player())
{
    if(who->query_wiz_level())
        return 1;
    else if(wildmatch("*jr", who->query_real_name()))
        return 2;
    else
        return 0;
}

/*
 * Function name: m_query_guild_masters
 * Description:   Get the list of guild masters for the guild
 *                
 * Returns:       The string array of guild master names
 */
static string *
m_query_guild_masters()
{
    return MONK_GUILD_MASTERS;
}

/*
 * Function name: m_count_council_members
 * Description:   Returns the number of council members
 *                there currently are in the monks
 * Returns:       The number of council members
 */
static int
m_count_council_members()
{
    mapping mem;
    int     num_council, i;
    string  *ind, who;

    mem = MANAGER->query_members();

    num_council = 0;
    ind = m_indices(mem);

    for(i=0;i<m_sizeof(mem);i++)
    {
        who = ind[i];

        if(mem[who][1])
            num_council++;
    }

    return num_council;
}

/*
 * Function name: m_query_is_guild_master
 * Description:   Check to see if someone is a guild master
 *                
 * Arguments:     who: the person to check (default is this_player())
 * Returns:       1 if the wizard is a guild master, 0 otherwise
 * Note:          
 */
static int
m_query_is_guild_master(mixed who = this_player())
{
    string name = m_get_name(who);

    /* Now check the array of guild masters. */
    return (member_array(name,
        m_query_guild_masters()) != -1);
}

/*
 * Function name: m_query_auth_wizard
 * Description:   General function to check for wizard
 *                authorization for guild functions. Currently
 *                authorized wizards are:
 *                1. Genesis wizards
 *                2. Archwizards or higher
 *                3. Guild masters
 * Arguments:     string or object of the wizard
 * Returns:       1 if authorized, 0 if not
 */
static int
m_query_auth_wizard(mixed who)
{
    string name = m_get_name(who);

    // check for archs
    if(SECURITY->query_wiz_rank(name) >= WIZ_ARCH)
        return 1;

    // check for Genesis wizards
    if(SECURITY->query_wiz_dom(name) == "Genesis")
        return 1;

    // check for guild masters
    return m_query_is_guild_master(name);
}

/*
 * Function name: m_query_council_member
 * Description:   Check to see if the specified player
 *                is a council member.
 * Arguments:     who - string or object to check
 *                allow_wizards - if this flags is set, we
 *                    will also return true if the wizard
 *                    is a valid Genesis wizard
 * Returns:       1 if they are a council member, 0 if not
 */
static varargs int
m_query_council_member(mixed who = 0, int allow_wizards = 0)
{
    if(allow_wizards && m_query_auth_wizard(who))
        return 1;

    if (m_query_is_guild_master(m_get_name (who)))
        return 1;

    return MANAGER->query_council_member(who);
}

/*
 * Function name: m_append_newline
 * Description:   appends a newline to a string, if there
 *                is not one already
 * Arguments:     the string
 * Returns:       the string with a newline appended
 */
static string
m_append_newline(string str)
{
    int    len;

    len = strlen(str);

    if(!len)
        return 0;

    if(str[len-1] != '\n')
        str += "\n"; // append a newline if there is not one already

    return str;
}

/*
 * Function name: m_log
 * Description:   interface to logging messages
 * Arguments:     log_entry - the string to log
 *                log_file - the file in the MONK_LIB to
 *                    log to. Default is "guild_log".
 * Returns:       1 if successful
 */
static varargs int
m_log(string log_entry, string log_file = "guild_log")
{
    string  file;

    if(!strlen(log_entry)) // we need to have something to log!
        return 0;

    RESET_EUID;

    file = MONK_LIB + log_file;

    if(file_size(file) > (50 * 1000)) // if greater than 50K, move over the log file
        rename(file, file + ".old"); // note this will overwrite the old backup

    // write it out to the file
    return write_file(file, ctime(time())
        + ": " + m_append_newline(log_entry));
}


/*
 * Function name: m_query_is_player
 * Description:   Cover function to check if a player
 *                exists
 * Arguments:     name - string or object
 * Returns:       1 if the person is a player
 */
static int
m_query_is_player (mixed who)
{
    if(objectp(who))
        return interactive(who); // check if the object is interactive
    else if(stringp(who)) // check to see if the name is a player's name
        return SECURITY->exist_player(lower_case(who));
    else
        return 0;

}

/*
 * Function name: m_get_living_ob
 * Description:   returns the object of a living, if logged ib
 * Arguments:     the object or string name
 * Returns:       the object
 */
static object
m_get_living_ob (mixed for_who)
{
    if (stringp (for_who))
        return find_living (lower_case (for_who));

    if (objectp (for_who))
        return for_who;

    return 0;

}

/*
 * Function name: m_plural_array
 * Description:   Append the plurals to all elements of a string
 *                array. This will mainly be used for add_item()'s,
 *                to simplify the adding of items to objects. Example
 *                usage would be:
 *
 *                add_item(m_plural_array(({"floor", "tile"})), "description...")
 *
 *                This will be evaluated as:
 *
 *                add_item(({"floor","tile","floors","tiles"})), "description...")
 *
 *                Sure, it put in the 'floors', but IMO it is better to
 *                have too many objects described than too few.
 * Arguments:     The array to pluralize
 * Returns:       The original array, plus all the plurals.
 */
static string *
m_plural_array(string *ar)
{
    int i;

    for(i=0;i<sizeof(ar);i++)
    {
        ar += ({ LANG_PWORD(ar[i]) });
    }

    return ar;
}


/*
 * Function name: m_pretty_text
 * Description:   Make some text passed in surrounded by pretty
 *                borders, for use in auto-posting on boards, etc.
 * Arguments:     message - the text to make pretty
 *                doublespace - 1 for double spaces between lines,
 *                    0 for single space.
 * Returns:       the pretty text
 */
static varargs string
m_pretty_text(string message, int doublespace = 1)
{
    string header, footer, *lines, *filler, result;
    int i, findex, msgspace;

    // spacing in the middle of the borders for text
    msgspace = 46;

    // header and footer. Saldy, they look little like they will
    // when printed, because all the backslash characters need to be
    // quoted with extra backslash chars.
    header  = "      .--..--..--..--..--..--..--..--..--..--..--..--..--..--..--.\n";
    header += "     / .. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\\n";
    header += "     \\ \\/\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ \\/ /\n";
    header += "      \\/ /`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\\/ /\n";
    header += "      / /\\                                                    / /\\\n";
    footer  = "     / /\\ \\                                                  / /\\ \\\n";
    footer += "     \\ \\/ /                                                  \\ \\/ /\n";
    footer += "      \\/ /                                                    \\/ /\n";
    footer += "      / /\\.--..--..--..--..--..--..--..--..--..--..--..--..--./ /\\\n";
    footer += "     / /\\ \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\.. \\/\\ \\\n";
    footer += "     \\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `'\\ `' /\n";
    footer += "      `--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'`--'\n";
    filler = (({ "/ /\\ \\", "\\ \\/ /", " \\/ / ", " / /\\ " })); // borders

    message = break_string(message, msgspace - 2);
    lines = explode(message, "\n");

    if(doublespace)
        message = implode(lines, "\n\n"); // double-space it
    else
        message = implode(lines, "\n");

    lines = explode(message, "\n");
    
    for(i=0;i<sizeof(lines);i++)
    {
        // pad each line to msgspace characters in width
        while(strlen(lines[i]) < msgspace)
        {
            lines[i] += " ";
    
            if(strlen(lines[i]) < msgspace)
                lines[i] = " " + lines[i];
        }
    }
    
    findex = 0;
    
    result = header;
    
    for(i=0;i<sizeof(lines);i++)
    {
        result += "     " + filler[findex] + "  " + lines[i] + "  " + filler[findex] + "\n";
    
        if(++findex >= sizeof(filler))
            findex = 0;
    }
    
    // complete the possibly incomplete filler lines
    for(i=findex;i<sizeof(filler);i++)
        result += "     " + filler[i] + "  "
            + sprintf("%-" + msgspace + "s", " ")
            + "  " + filler[i] + "\n";
    
    result += footer;
    
    return result;    
}

/*
 * Function name: m_average_array
 * Description:   Get the average of an integer array
 * Arguments:     the array
 * Returns:       the average of all the elements
 */
static int
m_average_array (int *ar)
{
    int i,tot,size;

    tot = 0;

    size = sizeof(ar);

    if(!size)
        return 0;

    for(i=0;i<size;i++)
    {
        tot += ar[i];
    }

    return tot / size;
}

/*
 * Function name: m_most_values_array
 * Description:   Returns the element of an array that
 *                appears in the array the most number
 *                of times.
 * Arguments:     mixed arr - the array to check
 * Returns:       an array of the values with the highest count
 */
static mixed
m_most_values_array(mixed arr)
{
    mapping value_map = ([]);
    mixed   elem, indices;
    int     highest = 0;
    int     *vals, i;
    mixed   highest_val = ({});

    if(!pointerp(arr) || !(sizeof(arr)))
        return ({}); // invalid array -- return blank array

    for(i=0;i<sizeof(arr);i++)
    {
        elem = arr[i];

        if(member_array(elem, m_indices(value_map)) == -1)
        {
            value_map += ([ elem : 1 ]);

            if(!highest) // set the highest value, if not already set
                highest = 1;
        }
        else
        {
            if(++value_map[elem] > highest)
                highest = value_map[elem]; // set the highest value
        }

    }    

    // now check to see which is the highest value
    vals = m_values(value_map);
    indices = m_indices(value_map);

    for(i=0;i<sizeof(vals);i++)
        if(vals[i] == highest)
            highest_val += ({ indices[i] }); // add the index to the highest values

    return highest_val;
}

/*
 * Function name: m_tell_player
 * Description:   Catch tell, for use with alarms
 * Arguments:     who - the player to send the mesage to
 *                what - the string to send them
 * Returns:       void
 */
void
m_tell_player(object who, string what)
{
    who->catch_tell(what);
}

/*
 * Function name: m_describe_living
 * Description:   Returns a pretty description of the
 *                living.
 * Arguments:     who - the object to describe
 * Returns:       A nice long description of the living
 */
public string
m_describe_living(object who)
{
    string  str;
    string  tmp;
    string  desc;
    int     hdesc;

    desc = LANG_ADDART(who->query_nonmet_name());
    str = desc;
    hdesc = 0;

    // put the hair (from /d/Calia/gelan/specials/hair_shadow)
    // in the description, if they have it and their hair desc
    // is not already in the short desc.
    if((tmp = who->query_hair_style()) && !wildmatch("*hair*", desc))
    {
        str += " with ";

        if(!wildmatch("* *", tmp)) // there is a space in the hair style, don't use it
            str += who->query_hair_style();
        else
            str += who->query_hair_length();

        str += " " + who->query_hair_colour() + " hair";
        hdesc = 1;
    }

    if(tmp = who->query_eyes_colour() && !wildmatch("*eye*", desc))
    {
        if(hdesc)
            str += " and ";
        else
            str += " with ";

        str += who->query_eyes_type() + " " + who->query_eyes_colour() + " eyes";
    }

    return str;
}


/*
 * Function name: m_sendmail
 * Description:   Function which will send mail to
 *                the specified person
 * Arguments:     to_who - the player to whom to send the
 *                    message
 *                subject - the subject of the mail
 *                body - the body of the mail
 * Returns:       1 if successful in sending the mail
 * Note:          create_mail() does not seem to be working at
 *                    all. I have created a sysbug report.
 */
static int
m_sendmail(string to_who, string subject, string body)
{
    find_living(to_who)->catch_tell("Simulated mail with "
        + "subject: " + subject + "\nContents:\n"
        + body + "\nEOF\n");

    return MAIL_OBJECT->create_mail(subject, to_who, "", body);
}

/*
 * Function name: m_query_hitloc_descs
 * Description:   Function to get the descriptions of
 *                all the hitlocs on a living
 * Arguments:     ob - the object on which to get the hitlocs
 * Returns:       array of string descriptions of the hitlocs
 */
varargs static string *
m_query_hitloc_descs(object ob = this_player())
{
    int     *hdesc, i;
    mixed    hdesc2;
    object   cobj;
    string   hstr, *descs = ({});

    cobj = ob->query_combat_object();

    if (!cobj)
        return ({ "somewhere" });

    hdesc = cobj->query_hitloc_id();

    if (!sizeof(hdesc))
        return ({ "somewhere" });

    for (i=0;i<sizeof(hdesc);i++)
    {
        hdesc2 = cobj->query_hitloc(hdesc[i]);

       // sanity check...
        if (sizeof(hdesc2) < 3)
            return ({ "somewhere" });

        hstr = hdesc2[2];

        descs += ({ hstr });
    }

    return descs;
}


/*
 * Function name: m_query_hitloc_str_id
 * Description:   function to obtain the hitloc ID
 *                from the textual description
 * Arguments:     ob - the object on which to check
 *                where - the string description of the hitloc
 * Returns:       the hitloc ID
 */
static int
m_query_hitloc_str_id (object ob, string where)
{
    int       mem;
    object    cobj;
    int      *hdesc;

    mem = member_array (where, m_query_hitloc_descs(ob));

    if (mem < 0)
        return -1;

    cobj = ob->query_combat_object();
    hdesc = cobj->query_hitloc_id();

    if (sizeof(hdesc) <= mem)
        return -1;

    return hdesc[mem];    
}

/*
 * Function name: m_translate_hitloc
 * Description:   Give a more interesting description of
 *                a humanoid's hitlocs. Will translate, e.g.,
 *                "legs" into "left thigh".
 * Arguments:     hitloc - the string hitloc
 *                enemy - if specified, we will first check to make
 *                    sure the enemy is a humanoid.
 * Returns:       the translated (new and improved) hitloc description
 */
varargs static string
m_translate_hitloc(string hitloc, object enemy = 0)
{
    string str;

    // do no translation if the enemy is not humanoid
    if (objectp (enemy) && !(enemy->query_humanoid ()))
        return hitloc;
    
    if(!hitloc || hitloc == "" || !stringp(hitloc))
        hitloc = "body"; // ??

    if(hitloc == "legs") // Get rid of the silly plurals
        hitloc = (random(2) ? "right" : "left") + " leg";

    if(hitloc == "head" && !random(5))
        hitloc = (random(2) ? "face" : "throat");
    if(sscanf(hitloc, "%s arm", str) && random(2))
        hitloc = (random(2) ? "lower " + hitloc : str + " shoulder");
    if(sscanf(hitloc, "%s leg", str) && random(2))
        hitloc = (random(2) ? "lower " + hitloc : str + " thigh");
    if(hitloc == "body" && random(2))
        hitloc = (random(2) ? "chest" : "stomach");

    return hitloc;
}

/*
 * Function name: m_post_board_msg
 * Description:   Function to post a note on the Monks
 *                board. Used for, e.g., posting the
 *                result of a note.
 * Arguments:     header - the subject of the post
 *                author - the author of the post
 *                body - the body of the post
 *                board - the board on which we will psot (default
 *                    is the static monk board)
 *                textfunc - the function through which the text
 *                    should be passed (default is m_pretty_text)
 * Returns:       1 if successful
 */
static varargs int
m_post_board_msg(string header, string author, string body,
        string board = MONKBOARD, function textfunc = m_pretty_text)
{
    RESET_EUID;

    // post the prettied text
    body = textfunc(body);

    return board->post_note_here(header, author, body);
}


/*
 * Function name: m_query_punishment
 * Description:   Returns either the entire punishment
 *                number of the player, or 1 if a specified
 *                punishment is currently in the bitwise
 *                list of punishment values.
 * Arguments:     who - string or name of the player
 *                punishment - -1 to return the entire
 *                    punishment, or the punishment
 *                    to check for.
 * Returns:       Either the entire punishment number, or
 *                    1 if the specified punishment is present
 *                    in the player's punishment specification.
 */
static varargs int
m_query_punishment(mixed who, int punishment = -1)
{
    return MANAGER->query_punishment(m_get_name(who), punishment);
}


