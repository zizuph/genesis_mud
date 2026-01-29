inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Genesis/race/racial_abilities.h"
#include "/d/Genesis/login/login.h"

#define HERITAGES   ([ "human" : "human", \
                       "elf" : "elven", \
                       "dwarf" : "dwarven", \
                       "hobbit" : "hobbit", \
                       "gnome" : "gnomish", \
                       "goblin" : "goblin" ])


public string get_soul_id()
{
    return "Generic Race";
}

public int query_cmd_soul()
{
    return 1;
}

void
create()
{
    setuid();
    seteuid( getuid() );
}

public mapping
query_cmdlist()
{
    return ([
        "ra"              : "racial_abilities",
        "rabilities"      : "racial_abilities",
        "select"          : "select_racial_benefits",
    ]);
}

int racial_abilities(string str)
{
    if (!this_player()->query_skill(RACIAL_ABILITY_SKILL))
    {
        write("You do not have any racial abilities yet. " +
            "Try <select abilities> to choose them.\n");
        return 1;
    }

    string race = this_player()->query_race();
    
    if (this_player()->query_race_name() == "ogre")
    {
        write("YOU OGRE NOW! OLD ABILITIES GONE! YOU ABLE TO EAT MANY " +
        "FOODS! MAGICS AND POISON HURT LESS! ALSO OTHER THINGS! SEE " +
        "<help race-ogre>!!\n");
        return 1;
    }
    
    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
        write("Since being undead is a complete transformation of your " +
        "mind and body you remember nothing of your old racial abilities. " +
        "As an undead you will be granted the following preset racial " +
        "abilities instead:\n\n");
    }
    else
    {
        write("Your " + HERITAGES[race] + " heritage is granting you the " +
            "following racial abilities:\n\n");
    }
    foreach (int ability, string name : ABILITIES_TO_NAME)
    {
        if (!HAS_RACIAL_ABILITY(this_player(), ability))
        {
            continue;
        }

        string desc;
        switch (ability) {
            case SCAVENGER: desc =
                "You are a SCAVENGER. This means that you will occasionally " +
                "find more coins on fallen enemies compared to other people.";
                break;
            case OPPORTUNISTIC: desc =
                "You are OPPORTUNISTIC. This means that you have a slightly " +
                "higher chance of scoring a critical hit (additional damage) " +
                "on your enemy.";
                break;
            case SCOTOPIC_VISION: desc =
                "You have SCOTOPIC VISION. This means that you will be able " +
                "to see inside many areas covered in non-magical darkness.";
                break;
            case  LIGHT_FOOTED: desc =
                "You are LIGHT-FOOTED. This means that you have a ten " +
                "percent chance to not leave any tracks behind when moving.";
                break;
            case WELL_CONNECTED: desc =
                "You are WELL-CONNECTED. This means that you will get a " +
                "twenty-five percent discount when exchanging coins at all " +
                "Gnomes of Genesis (GoG) banks.";
                break;
            case EYE_FOR_DETAIL: desc =
                "You have an EYE FOR DETAIL. This means you have a twenty " +
                "skill level bonus (up to superior guru) in trading, " +
                "appraise object, and appraise value.";
                break;
            case LIGHT_FINGERED: desc =
                "You are LIGHT-FINGERED. This means that you have a twenty " +
                "skill level bonus (up to superior guru) in pick pocket.";
                break;
            case STEALTHY: desc =
                "You are STEALTHY. This means that you have a ten skill " +
                "level bonus (up to superior guru) in sneak and hide.";
                break;
            case EXPLORER: desc =
                "You are an EXPLORER. This means that you have a ten skill " +
                "level bonus (up to superior guru) in herbalism, awareness, " +
                "location sense, and tracking.";
                break;
            case GOOD_MEMORY: desc =
                "You have a GOOD MEMORY. This means that you can remember " +
                "twenty-five percent more names compared to other people.";
                break;
            case APOTHECARY: desc =
                "You are an APOTHECARY. This means that the cooldown time " +
                "between using herbs will be slightly reduced for you.";
                break;
            case RESILIENT: desc =
                "You are RESILIENT. This means that your resistance to " +
                "magic, and especially poison, is stronger than other people.";
                break;
            case FLEET_FOOTED: desc =
                "You are FLEET-FOOTED. This means that if are not in " +
                "combat, you will be able to recover your energy quicker " +
                "after you get tired.";
                break;
            case STALWART: desc =
                "You are STALWART. This means that you can carry heavier " +
                "loads than other people before becoming encumbered by it.";
                break;
            case TENACIOUS: desc =
                "You are TENACIOUS. This means that you will recover lost " +
                "experience (from death, leaving guilds, etc.) faster than " +
                "other people.";
                break;
            case STRONG_LIVER: desc =
                "You have a STRONG LIVER. This means that you heal slightly " +
                "faster due to your ability to consume more alcohol than " +
                "other people.";
                break;
            case INSATIABLE: desc =
                "You are INSATIABLE. This means that you can eat more food " +
                "than other people and therefore not tire as easily.";
                break;
            default:
                desc = "This ability is undefined.";
        }
        write(desc);
        write("\n\n");
    }
    if (this_player()->query_prop(LIVE_I_UNDEAD))
    {
        write("The undead race also comes with many other benefits and " +
            "drawbacks. See <help race-undead> for more information.\n\n");

        write("If you stop being undead and return to your old body you " +
            "will lose all the undead-specific abilities and get back the " +
            "two racial abilities you previously had selected.\n");
    }
    else
    {
        write("These abilities can be reselected by choosing a new body when " +
         "you die. See <help races> and <help race-" + race + "> for more " +
         "information.\n");
    }
    return 1;
}

int select_racial_benefits(string str)
{
    if (this_player()->query_skill(RACIAL_ABILITY_SKILL))
        return 0;
    if (!this_player()->query_prop(SELECT_BENEFITS_NOTIFY))
        return 0;
    if (str == "abilities" || str == "racial abilities")
    {
       setuid();
       seteuid(getuid());
       object ob = clone_object(LOGIN_MENU);
       ob->move(this_player(), 1);
       ob->start_racial();
       return 1;   
    }
    notify_fail("Select abilities?\n");
    return 0;
}

