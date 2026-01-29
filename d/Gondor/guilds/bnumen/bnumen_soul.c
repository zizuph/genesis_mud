/*
 * The soul of the Black Numenoreans.
 * /d/Gondor/guilds/bnumen/bnumen_soul.c
 *
 * Based on some soul by Olorin, of course.
 *
 * Palmer, Toby Aug 2006
 */
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_filters.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_titles.h"
#include "/d/Gondor/guilds/bnumen/lib/emotes.h"

string get_soul_id() { return GUILD_NAME; }

int query_cmd_soul() { return 1; }

string query_internal_title(object tp);

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
    return ([
            "help"        : "bnhelp",
            "bnumen"      : "list_active_bnumen",
            "bnlist"      : "list_active_bnumen",
            "bnsay"       : "speak_ancient_adunaic",
            "dunsay"      : "speak_adunaic",
            "bnamazed"    : "bnamazed",
            "bnclench"    : "bnclench",
            "bneye"       : "bneye",
            "bngaze"      : "bngaze",
            "bngloat"     : "bngloat",
            "bngrin"      : "bngrin",
            "bnheckle"    : "bnheckle",
            "bnintro"     : "bnintro",
            "bnmock"      : "bnmock",
            "bnshake"     : "bnshake",
            "bnsilence"   : "bnsilence",
            "bntall"      : "bntall",
            "bnwellmet"   : "bnwellmet",
         ]);
}

int
list_active_bnumen()
{
    int     i,
            cnt;
    object *list;
    string  name,
            rtitle,
            bnumen_list;

    bnumen_list = "The members of Houses of the Black Numenoreans currently in " +
        "the realms:\n";

    list = filter(users(), query_is_bnumen);
    list = sort_array(list, "sort_bnumen_level");

    while (i < sizeof(list))
    {
        name = CAP(list[i]->query_real_name());
        rtitle = " " + list[i]->query_guild_title_race();

/*        if (list[i]->query_bnumen_lord())
            rtitle = ", the " + (list[i]->query_gender() ? "Lady" : "Lord")
              + " of the House of " + list[i]->query_bnumen_house();
*/
        if (list[i]->query_wiz_level())
           bnumen_list += ": " + name + " " + list[i]->query_title();
        else
        {
           bnumen_list += ": " + name + " the " + query_internal_title(list[i]);
        }
        bnumen_list += ("\n");
        cnt++;
        i++;
    }

    if(cnt == 1)
        bnumen_list += "There is presently only one Black Numenorean in the realms.\n";
    else if(cnt)
        bnumen_list += "There are now "+LANG_WNUM(cnt)+" Black Numenoreans in the realms.\n";
    else
        bnumen_list = "There are currently no Black Numenoreans in the realms.\n";

    write(bnumen_list);
    return 1;
}

int
bnhelp(string str)
{
    string subject, filename;

    if (!str)
        return 0;

    str = LOW(str);

    FIX_EUID

    if (str == "bnumen" || str == "race" || str == "race guild")
    {
        cat(GUILD_HELP + "commands");
        return 1;
    }
    if ((sscanf(str, "bnumen %s", subject) != 1) &&
        (sscanf(str, "race %s", subject) != 1) &&
        (sscanf(str, "race guild %s", subject) != 1))
        return 0;

    if(subject == "emotes")
       subject = "emotions";

    filename = GUILD_HELP + subject;

    if (file_size(filename) > 0)
    {
        cat(filename);
        return 1;
    }
    return 0;
}

string
query_internal_title(object tp)
{
   string sTitle = "";
   int irace,
       stat,
       stat_internal,
       stat_sum,
       title_length = sizeof(MALE_BNTITLES);
   

   irace = tp->query_stat(SS_RACE);

   /* Race guild stat of 120 gives the top rank */

   stat = ( (title_length * irace) / 120 );

   /*  Change later for support that only kills in ME 
    *  yields a bonus to the title. Should perhaps 
    *  15 % of the rank be dependant of regular exp?
    *
    *  Each kill in ME gives one point? Or different 
    *  gives different amounts? Scale of 1-5 perhaps?
    *
    *  If a player kills 'allied' substract much more
    *  I suggest 25-100 as a punishment.
    *
    *  How many points is max rank? 47328 points.
    */

   stat = stat * 15 / 100;

   stat_internal = tp->query_bnumen_level() / (12 * title_length);
   stat_internal = stat_internal * 85 / 100;

   stat_sum = (title_length * stat / 100) + (title_length * stat_internal / 100);

   if(stat_sum > title_length) 
   {
     stat_sum = sizeof(MALE_BNTITLES)-1;
   }

   if(strlen(tp->query_bnumen_house()) == 0 && stat_sum > BNUMEN_HOUSE_LEVEL)
   {
       stat_sum = BNUMEN_HOUSE_LEVEL;
   }
   else
   {
       if(stat_sum < BNUMEN_HOUSE_LEVEL)
       {
           stat_sum = BNUMEN_HOUSE_LEVEL;
       }
       sTitle = ", family " + tp->query_bnumen_house();
   }

   if(tp->query_gender() == G_MALE)
      return MALE_BNTITLES[stat_sum] + sTitle;
   else
      return FEMALE_BNTITLES[stat_sum] + sTitle;
}
