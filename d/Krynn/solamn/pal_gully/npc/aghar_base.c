#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>
inherit M_FILE

int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string CAPheshe = "";
string CAPhisher = "";

void
do_die(object killer)
{
    int goldfactor = 100;
    int kstat = killer->query_average_stat();
    string golddamage = "";
    if (kstat > 115)
    {
        goldfactor = 65;
        golddamage = "Your killing blow destroys your foe sending bits "
            + "of shattered gold and jewelry flying.";
    }
    if (kstat > 125)
    {
        goldfactor = 45;
        golddamage = "Your killing blow massacres your foe spraying the "
            + "area with bits of gold and jewelry.";
    }
    if (kstat > 135)
    {
        goldfactor = 20;
        golddamage = "Your mighty killing blow overpowers the skeleton's "
            + "form destroying it along with most of its belongings in a "
            + "haze of gold and silver.";
    }
    if (kstat > 145)
    {
        goldfactor = 0;
        golddamage = "Your massive killing blow vaporizes the skeleton "
            + "and nearly all its belongings.";
    }
	
	if (golddamage != "" && present(killer, E(TO)))
    {
        killer->catch_msg(golddamage + "\n");
    }    
    if (random(1) == 1)
    {
        command("emote shatters into bone and dust.");
    }
    else if (goldfactor == 0) // Skip this if we vaporized them.
    {
        command("emote collapses into a heap of bone and dust.");
    }
    ::do_die(killer);
}