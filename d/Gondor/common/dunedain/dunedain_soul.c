/*
 * The soul of the Dunedain.
 * /d/Gondor/common/dunedain/dunedain_soul.c
 *
 * Created: Olorin, 07-nov-1994
 *
 * TODO: add souldesc!
 *
 * Modification log:
 *      Emotion 'ecry' added 30-jan-2002, Skippern
 *      The names of some emotions changed because of conflict between
 *      Dunedains/DA/Dancers commands, April 2004, Deagol
 *
 *      Removed the hidden names on the guild list when someone is
 *      invisible, it was being used to the detriment of people
 *      who could become invisible. March 4, 2021, Varian
 */
#pragma strict_types
#pragma save_binary

inherit "/cmd/std/command_driver";

#include <macros.h>
#include <std.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"
#include "/d/Gondor/common/dunedain/lib/dun_filters.h"
#include "/d/Gondor/common/dunedain/lib/emotes.h"

string get_soul_id() { return GUILD_NAME; }

int query_cmd_soul() { return 1; }

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
    return ([
            "amazed"      : "amazed",
            "bcry"        : "battle_cry",
            "behold"      : "behold",
            "dunedain"    : "list_active_dunedain",
            "ddlist"       : "list_active_dunedain",
            "ddlaugh"      : "dlaugh",
            "ddoffer"      : "doffer",
            "ddsalute"     : "dsalute",
            "ddsay"        : "speak_adunaic",
            "dunsay"      : "speak_adunaic",
            "ddsmile"      : "dsmile",
            "ddstare"      : "dstare",
            "ddrefuse"     : "drefuse",
	    "ecry"        : "ecry",
            "elfhail"     : "elfhail",
            "embrace"     : "embrace",
            "farewell"    : "farewell",
            "gleam"       : "gleam",
            "glitter"     : "glitter",
            "help"        : "help",
	    //	    "ncry"        : "ncry",
            "oath"        : "oath",
            "ddpace"       : "pace",
            "silence"     : "silence",
            "sing"        : "sing",
            "stop"        : "stop_singing",
            "steel"       : "steel",
            "tongue"      : "tongue",
            "turneyes"    : "turneyes",
            "uplift"      : "uplift",
            "wellmet"     : "wellmet",
         ]);
}

int
list_active_dunedain()
{
    int     i,
            cnt;
    object *list;
    string  name,
            rtitle,
            dun_list;

    dun_list = "The members of Houses of the Dunedain currently in " +
        "the realms:\n";

    list = filter(users(), query_is_dunadan);
    list = sort_array(list, "sort_dunadan_level");

    while (i < sizeof(list))
    {
        name = CAP(list[i]->query_real_name());
        rtitle = " " + list[i]->query_guild_title_race();
        if (list[i]->query_dunadan_level() == DL_LORD)
            rtitle = ", the " + (list[i]->query_gender() ? "Lady" : "Lord")
              + " of the House of " + list[i]->query_dunadan_house();
        /*
         *if (!list[i]->query_invis())
         * Removing this so that there is no easy cheat to check if
         * another player is invis or not.
         * Varian 3/4/21
         */
        {
            if (list[i]->query_wiz_level())
                dun_list += ": " + name + " " + list[i]->query_title();
            else
            {
                dun_list += ": " + name + rtitle;
                if (list[i]->query_ghost())
                    dun_list += " <dead>";
            }
            dun_list += ("\n");
            cnt++;
        }
        if (list[i]->query_invis()
            && TP->query_wiz_level())
        {
            dun_list += ": (" + name + ")";
            dun_list += ("\n");
            cnt++;
        }
        i++;
    }
    if(cnt == 1)
        dun_list += "There is presently only one Dunadan in the realms.\n";
    else if(cnt)
        dun_list += "There are now "+LANG_WNUM(cnt)+" Dunedain in the realms.\n";
    else
        dun_list = "There are currently no Dunedain in the realms.\n";

    write(dun_list);
    return 1;
}

int
help(string str)
{
    string subject, filename;

    if (!str)
        return 0;

    str = LOW(str);

    FIX_EUID

    if (str == "dunedain" || str == "race" || str == "race guild")
    {
        cat(GUILD_HELP + "commands");
        return 1;
    }
    if ((sscanf(str, "dunedain %s", subject) != 1) &&
        (sscanf(str, "race %s", subject) != 1) &&
        (sscanf(str, "race guild %s", subject) != 1))
        return 0;

    filename = GUILD_HELP + subject;
    if (file_size(filename) > 0)
    {
        cat(filename);
        return 1;
    }
    return 0;
}

