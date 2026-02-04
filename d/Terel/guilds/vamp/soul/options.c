
#include "../guild.h"
#include "../voptions.h"

static mapping v_options = 
    ([ 
       "notify sunlight"        : VOPT_NOTIFY_SUNLIGHT,
       "notify light"           : VOPT_NOTIFY_LIGHT,
       "notify login"           : VOPT_NOTIFY_LOGIN,
       "vampyr race"            : VOPT_VAMPIRE_RACE,
       "intro title"            : VOPT_INTRO_TITLE,
       "intro honourary"        : VOPT_INTRO_PTITLE,
       "notify thirst"          : VOPT_NOTIFY_THIRST,
       "vsay"                   : VOPT_VSAY,
       "use drain skills"       : VOPT_DRAIN_SKILL_MODE,
       "use drain resistance"   : VOPT_DRAIN_RESIST_MODE,
       "use drain haste"        : VOPT_DRAIN_HASTE_MODE,
    ]);

static mapping bg_options = 
    ([ 
       "intro title"            : VOPT_INTRO_TITLE,
       "intro honourary"        : VOPT_INTRO_PTITLE,
       "notify thirst"          : VOPT_NOTIFY_THIRST,
       "use drain skills"       : VOPT_DRAIN_SKILL_MODE,
       "use drain resistance"   : VOPT_DRAIN_RESIST_MODE,
    ]);


int
voptions(string str)
{
    string option_name, val, *opts, *split;
    int i = -1, opt;
    mapping opt_map;

    opt_map = TP->query_bloodguard() ? 
        bg_options : v_options;

    if (!strlen(str))
    {
        opts = sort_array(m_indices(opt_map));
        for (i = 0; i < sizeof(opts); i++)
        {
            write(sprintf("%-25s %s\n", opts[i] + ":",
                TP->query_vamp_option(opt_map[opts[i]]) ? 
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
        write(sprintf("%-25s %s\n", option_name + ":",
            TP->query_vamp_option(opt_map[option_name]) ? 
            "on" : "off"));
        return 1;
    }

    TP->set_vamp_option(opt, i);
    return voptions(option_name);
}
        
    
