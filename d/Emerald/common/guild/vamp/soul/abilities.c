#pragma save_binary
#pragma strict_types
#pragma no_shadow
#pragma no_inherit

#include "../guild.h"

inherit VAMP_SOUL_DIR + "abilities_base";
inherit VAMP_LIB_DIR + "help";

#define NO_AURA
#define NO_EMBRACE 1

#ifndef NO_AMBUSH
#include "ambush.c"
#endif

#ifndef NO_ASSESS
#include "assess.c"
#endif

#ifndef NO_AURA
#include "aura.c"
#endif

#ifndef NO_CELERITY
#include "celerity.c"
#endif

#ifndef NO_CLEANSE
#include "cleanse.c"
#endif

#ifndef NO_CLING
#include "cling.c"
#endif

#ifndef NO_COVEN
#include "vcoven.c"
#endif

#ifndef NO_DASH
#include "dash.c"
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

#ifndef NO_INTRODUCE
#include "introduce.c"
#endif

#ifndef NO_EARTHMELD
#include "meld.c"
#endif

#ifndef NO_PROJECT
#include "project.c"
#endif

#ifndef NO_SLASH
#include "slash.c"
#endif

#ifndef NO_FLURRY
#include "flurry.c"
#endif

#ifndef NO_SUMMON
#include "summon.c"
#endif

#ifndef NO_TELEPATH
#include "telepath.c"
#endif

#ifndef NO_THIRST
#include "thirst.c"
#endif

#ifndef NO_UNSEEN
#include "unseen.c"
#endif

#ifndef NO_VAMPS
#include "vamps.c"
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

#ifndef NO_VLEAVE
#include "vleave.c"
#endif


string get_soul_id() { return GUILD_NAME + " (abilities)"; }

void create()
{
    set_help_type(({ "vampire", "vamp" }));
    read_help_dir(VAMP_HELP_DIR);

    cmdlist = ([
#ifndef NO_AMBUSH
                "prepare"    : "prepare",
                "vambush"    : "ambush",
#endif

#ifndef NO_ASSESS
                "vassess"    : "assess",
#endif

#ifndef NO_CLING
                "vcling"     : "cling",
#endif

#ifndef NO_COVEN
                "vcoven"     : "vcoven",
#endif

#ifndef NO_DESICCATE
                "vdesiccate" : "desiccate",
#endif

#ifndef NO_DRAIN
                "vdrain"     : "drain",
                "vdrink"  : "drink",
#endif

#ifndef NO_EMBRACE
                "vembrace"   : "embrace",
#endif

#ifndef NO_FADE
                "vfade"      : "fade",
#endif

                "videa"      : "videa",


#ifndef NO_INTRODUCE
                "intro"      : "introduce",
                "introduce"  : "introduce",
#endif

#ifndef NO_REGEN
                "vregenerate" : "regenerate",
                "vregen"      : "regenerate",
#endif

#ifndef NO_ROGUE
                "vrogue"     : "vrogue",
#endif

#ifndef NO_VSAY
                "vsay"       : "vsay",
#endif

#ifndef NO_SLASH
                "vslash"     : "slash",
#endif

#ifndef NO_FLURRY
                "vflurry"    : "flurry",
#endif NO_FLURRY

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

#ifndef NO_VLEAVE
                "vleave"     : "vleave",
#endif
              ]) + help_cmdlist();

#ifndef NO_CLING
    add_stop_cmd(({ "cling", "clinging", "vcling", "vclinging" }), stop_cling);
#endif

#ifndef NO_DRAIN
    add_stop_cmd(({ "vdrain", "vdraining", "vdrink", "vdrinking", 
        "drain", "draining", "drink", "drinking" }), stop_drain);
#endif

#ifndef NO_AURA
    add_vamp_cmd("vaura", aura, 65, 8, 70, 0, 5, ({ "aura", "vaura" }),
        stop_aura, break_aura);
#endif

#ifndef NO_CELERITY
    add_vamp_cmd("vcelerity", celerity, 0, 0, 0, 0, 2, 0, 0, 0);
#endif

#ifndef NO_CLEANSE
    add_vamp_cmd("vcleanse", cleanse, 90, 120, 100, 100, 8,
        ({ "cleanse", "cleansing", "vcleanse", "vcleansing" }),
         stop_cleanse, break_cleanse);
#endif

#ifndef NO_DASH
    add_vamp_cmd("vdash", dash, 45, 4, 0, 10, 0, 0, 0, 0);
#endif

#ifndef NO_EARTHMELD
    add_vamp_cmd(({ "vmeld", "vearthmeld" }), earthmeld, 0, 3, 10, 10, 2,
        ({ "vmeld", "vmelding", "vearthmelding", "vearthmeld", 
        "meld", "melding", "earthmeld", "earthmelding" }), stop_earthmeld,
        break_earthmeld);
#endif
              
#ifndef NO_PROJECT
    add_vamp_cmd("vproject", project, 10, 2, 8, 0, 1, 0, 0, break_project);
#endif

#ifndef NO_SUMMON
    add_vamp_cmd("vsummon", summon, 30, 10, 40, 0, 
         &operator(+)(5) @ &random(5), ({ "summon", "vsummon", "summoning",
         "vsummoning" }), stop_summon, break_summon);
#endif

#ifndef NO_TELEPATH
    add_vamp_cmd(({ "vtelepath", "vtpath" }), telepath, 15, 3, 10, 0, 0, 0,
        0, 0);
#endif

#ifndef NO_UNSEEN
    add_vamp_cmd("vunseen", unseen, 145, 30, 80, 0, 4,
        ({ "unseen", "vunseen" }), stop_unseen, break_unseen);
#endif
}

mixed
get_help(string subject)
{
#ifndef NO_FREE_EMOTES
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
#endif

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
