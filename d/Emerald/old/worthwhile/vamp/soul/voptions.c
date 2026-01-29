#include "../voptions.h"

static mapping m_options = 
    ([ "automeld"         : VOPT_AUTOMELD,
       "notify sunlight"  : VOPT_NOTIFY_SUNLIGHT,
       "notify light"     : VOPT_NOTIFY_LIGHT,
       "notify login"     : VOPT_NOTIFY_LOGIN,
       "darkvision"       : VOPT_DVIS,
       "prowl"            : VOPT_PROWL,
       "intro title"      : VOPT_INTRO_TITLE,
       "intro honourary"  : VOPT_INTRO_PTITLE,
       "vamp attacks"     : VOPT_VAMP_ATTACKS,
       "brief attacks"    : VOPT_BRIEF_ATTACKS,
       "vsay"             : VOPT_VSAY,
    ]);

int
voptions(string str)
{
    string option_name, val, *opts, *split;
    int i = -1, opt;
    mapping opt_map;

    opt_map = m_options;

    if (!strlen(str))
    {
        opts = m_indices(opt_map);
        for (i = 0; i < sizeof(opts); i++)
        {
            write(sprintf("%-18s %s\n", opts[i] + ":",
                this_player()->query_vamp_option(opt_map[opts[i]]) ? 
                "on" : "off"));
	}

        return 1;
    }

    split = explode(str, " ") - ({ "" });
    if (sizeof(split) >= 2)
    {
        option_name = implode(split[..sizeof(split) - 2], " ");
        val = split[sizeof(split) - 1];

	if (val == "on")
	{
	    i = 1;
	}
	else if (val == "off")
	{
	    i = 0;
	}
        else
        {
            option_name = str;
            i = -1;
	}
    }
    else
    {
        option_name = str;
        i = -1;
    }

    if (!(opt = opt_map[option_name]))
    {
        notify_fail("No such option: " + option_name + ".\n");
        return 0;
    }

    if (i == -1)
    {
        write(sprintf("%-18s %s\n", option_name + ":",
            this_player()->query_vamp_option(opt_map[option_name]) ? 
            "on" : "off"));
        return 1;
    }

    this_player()->set_vamp_option(opt, i);
    return voptions(option_name);
}
        
    
