#pragma save_binary
#pragma strict_types
#pragma no_shadow
#pragma no_inherit

#include "../guild.h"

inherit VAMP_SOUL_DIR + "abilities_base";
inherit "/d/Genesis/lib/help";

#ifndef NO_COVEN
#include "vcoven.c"
#endif

#ifndef NO_DESICCATE
#include "desiccate.c"
#endif

#ifndef NO_DRAIN
#include "drain.c"
#include "drink.c"
#endif

#ifndef NO_EMBRACE
#include "embrace.c"
#endif

#ifndef NO_FADE
#include "fade.c"
#endif

#ifndef NO_TELEPATH
#include "telepath.c"
#endif

#ifndef NO_THIRST
#include "thirst.c"
#endif

#ifndef NO_VAMPS
#include "vamps.c"
#endif

#ifndef NO_CELERITY
#include "celerity.c"
#endif

#include "sun.c"

#include "videa.c"

#include "voptions.c"

#ifndef NO_ROGUE
#include "vrogue.c"
#endif

#ifndef NO_VSAY
#include "vsay.c"
#endif


string get_soul_id() { return GUILD_NAME + " (abilities)"; }

void create()
{
    set_help_type(({ "vampire", "vamp" }));
    read_help_dir(VAMP_HELP_DIR);

    // These are abilities that don't require any skill/stat tests, or at
    // least ones that don't use the default ones
    cmdlist = ([
#ifndef NO_COVEN
                "vcoven"     : "vcoven",
#endif

#ifndef NO_DESICCATE
                "vdesiccate" : "desiccate",
#endif

#ifndef NO_DRAIN
                "vdrain"     : "drain",
                "vdrink"     : "drink",
#endif

#ifndef NO_EMBRACE
                "vembrace"   : "embrace",
#endif

#ifndef NO_FADE
                "vfade"      : "fade",
#endif

                "videa"      : "videa",

#ifndef NO_ROGUE
                "vrogue"     : "vrogue",
#endif

#ifndef NO_VSAY
                "vsay"       : "vsay",
#endif

                "stop"       : "_stop", 
                "vsun"       : "sun",

#ifndef NO_THIRST
                "vthirst"    : "thirst",
#endif

                "voptions"   : "voptions",

#ifndef NO_VAMPS
                "vamps"      : "vamps",
                "mvamps"     : "vamps",
#endif
              ]) + help_cmdlist();

#ifndef NO_DRAIN
    add_stop_cmd(({ "vdrain", "vdraining", "vdrink", "vdrinking", 
        "drain", "draining", "drink", "drinking" }), stop_drain);
#endif

#ifndef NO_CELERITY
    add_vamp_cmd("vcelerity", celerity, 0, 0, 0, 0, 2, 0, 0, 0);
#endif

#ifndef NO_TELEPATH
    add_vamp_cmd(({ "vtelepath", "vtpath" }), telepath, 15, 3, 10, 0, 0, 0,
        0, 0);
#endif
}

mixed
get_help(string subject)
{
    if (subject == "vemote")
    {
        setuid();
        seteuid(getuid());
        if (MANAGER->query_free_emotes_enabled(this_player()) ||
            this_player()->query_wiz_level() || IS_JR(this_player()))
	{
           return ::get_help(subject);
	}

        return 0;
    }

    return ::get_help(subject);
}

string *
query_subjects()
{
    setuid();
    seteuid(getuid());
    if (MANAGER->query_free_emotes_enabled(this_player()) ||
        this_player()->query_wiz_level() || IS_JR(this_player()))
    {
        return ::query_subjects();
    }

    return (::query_subjects() - ({ "vemote" }));
}
