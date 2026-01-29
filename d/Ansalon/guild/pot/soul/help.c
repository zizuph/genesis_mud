/*
 */

#include "../guild.h"

int
show_helpfile(string helpfile)
{
    int x, size;
    string text, *arr;

    setuid();
    seteuid(getuid());
    
    if (file_size(helpfile) > 0)
    {
        arr = explode(read_file(helpfile), "\n");

        /* Print out the helpfile like a scroll. See any for how to
         * write them. The first line is the title, the remainder the
         * text.
         */

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
            sprintf(") %|72s (\n", arr[0]);
            
        for (x = 1, size = sizeof(arr) ; x < size ; x++)
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

        this_player()->more(text);

    	return 1;
    }

    return 0;
}

int
get_help_on(string arg)
{
    string helpfile;
    int lvl;

    if (arg == "topics" && member_array(this_player()->query_real_name(),
        GUILD_ADMIN->query_guild_council()) >= 0)
        arg = "topics_council";

    /* 1. Search in main help dir */
    helpfile = GUILDHELP + arg;
    if (show_helpfile(helpfile))
        return 1;

    /* 2. Search in common dir */
    helpfile = GUILDHELP + "common/" + arg;
    if (show_helpfile(helpfile))
        return 1;

    /* 3. Search in spell dir and check if the player has the spell */
    helpfile = GUILDHELP + "spells/" + arg;
    if (objectp(this_player()->find_spell(arg)) &&
        show_helpfile(helpfile))
        return 1;

    /* 4. Search in council dir and check if the player is of that position */
    helpfile = GUILDHELP + "council/" + arg;
    if (arg == "council" && member_array(this_player()->query_real_name(),
        GUILD_ADMIN->query_guild_council()) >= 0 && show_helpfile(helpfile))
        return 1;

    if (GUILD_ADMIN->query_council_seat(arg) == this_player()->query_real_name() &&
        show_helpfile(helpfile))
        return 1;

#ifdef 0
    /* If ever a need would arise for levelspecific
     * helpfiles, the ifdefs would be removed. For
     * only spells are levelspecific which are taken
     * care of as step 3 above nowadays.
     */
    /* 4. Search in level specific dir */
    lvl = TP->query_priest_level();
    while (lvl >= 0)
    {
        switch (lvl)
        {
    	    case GUILD_LEVEL_INITIATE:
    	        helpfile = GUILDHELP + "initiate/" + arg;
    	        break;

    	    case GUILD_LEVEL_PRIEST:
    	        helpfile = GUILDHELP + "priest/" + arg;
    	        break;

    	    case GUILD_LEVEL_HIGH_PRIEST:
    	        helpfile = GUILDHELP + "high_priest/" + arg;
    	        break;
        }
        if (show_helpfile(helpfile))
             return 1;
        lvl--;
    }
#endif

    /* If we got this far, there was no such helpfile */
    if (query_verb() == "phelp")
        notify_fail("phelp: No help on \"" + arg + "\" available.\n");

    return 0;
}

int
do_help(string arg)
{
    string vb;

    vb = query_verb();

    if (vb == "help" && !arg)
        return 0;

    if (vb == "help")
    {
    	string *words = explode(arg, " ");
    	if (words[0] != "priest")
    	    return 0;

        if (sizeof(words) > 1)
    	    arg = implode(words[1..]," ");
    	else
    	    arg = "";
    }

    setuid();
    seteuid(getuid());

    if (!stringp(arg) || arg == "")
        arg = "index";
    return get_help_on(arg);
}
