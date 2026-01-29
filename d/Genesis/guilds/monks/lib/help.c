/*
 * File:     help.c
 * Created:  Cirion, 1999.03.07
 * Purpose:  Just add the clear_help_info to /d/Genesis/lib/help so
 *           we can offer different help lists to council members
 *           and normal members.
 * Modification Log:
 *
 */
inherit "/d/Genesis/lib/help";
#include "defs.h";
inherit MONKLIB;

void
clear_help_info()
{
    help_map = ([]);
}


/*
 * Function name: _help
 * Description:   Masked help command to check for council
 *                membership.
 * Arguments:     the argument passed to the command
 * Returns:       1 if successful
 */
int
_help(string str)
{
    string s1, s2;

    clear_help_info();
    read_help_dir(MONK_HELP);

    // check to see if they entered council
    if(wildmatch("* council*", str))
    {
        // only council members have access to the council
        // help files
        if(!m_query_council_member(this_player()))
            return ::_help(str);

        if(sscanf(str, "%s council%s", s1, s2))
            str = s1 + s2;

        clear_help_info();
        read_help_dir(MONK_HELP + "council/");

        return ::_help(str);
    }

    // check to see if they entered elder
    if(wildmatch("* elder*", str))
    {
        // only council members have access to the council
        // help files
        if(!m_query_council_or_elder(this_player()))
            return ::_help(str);

        if(sscanf(str, "%s elder%s", s1, s2))
            str = s1 + s2;

        clear_help_info();
        read_help_dir(MONK_HELP + "elder/");

        return ::_help(str);
    }

    if (::_help(str))
    {
        if(m_query_council_member(this_player()))
            write("You may also enter do 'help monk council'"
                + " for council commands or 'help monk elder'"
		+ " for Elder commands.\n");
        if(m_query_elder(this_player()))
            write("You may also enter do 'help monk elder'"
		+ " for Elder commands.\n");
        return 1;
    }
    else
        return 0;
}

