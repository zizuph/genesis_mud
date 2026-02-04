/* 
 * sniff.c
 *
 * This provides the sniff ability.
 *
 */

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <login.h>

#include "../defs.h"

inherit "/lib/commands.c";

#define TRAIL_LOSS_TIME  600

/*
 * Function name: sniff_now
 * Description:   Actually perform the sniffing
 * Arguments:     pl - the sniffer
 *                skill - the sniffing skill used
 */
void
sniff_now(object player, int track_skill)
{
    string *sniff_arr, * track_arr,
            track_result = "You do not find any tracks.\n",
            sniff_result = "You do not smell any fresh blood.\n",
            dir,
           *dir_arr,
            race,
           *races = RACES + ({ "animal" });
    int     i;
    mixed  *exits;

    track_arr = environment(TP)->query_prop(ROOM_S_DIR);
    sniff_arr = environment(TP)->query_prop(ROOM_S_BLOOD_DIR);

    track_skill /= 2;
    track_skill += random(track_skill);

    if (CAN_SEE_IN_ROOM(player) && pointerp(track_arr) && track_skill > 0)
    {
        dir = track_arr[0];
        if (dir == "X" || dir == "M")
            dir = "nowhere";
        if (strlen(dir)>3)
        {
            dir_arr = explode(dir," ");
            if (dir_arr[0] != "the" && dir_arr[0]!="down")
            dir = "the " + dir;
        }
        race = track_arr[1];

        track_result = "Your heightened senses notice that tracks ";

        switch(track_skill)
        {
            case  1..10:
                track_result+="are present.\n";
                break;
            case 11..20:
                if(random(2))
                {
                    exits = environment(player)->query_exit();
                    if(i = sizeof(exits))
                        dir = exits[random(i/3)*3+1];
                }
                track_result += "are probably leading towards " + 
                dir + ".\n";
                break;
            case 21..50:
                track_result += "are leading towards " + dir + ".\n";
                break;
            case 51..75:
                if(random(2))
                    race = one_of_list(races);
                track_result += "were probably made by " +LANG_ADDART(race) +
                    " and are leading towards " + dir + ".\n";
                break;
            case 76..150:
                track_result += "were made by " +LANG_ADDART(race) +
                    " and are leading towards " + dir + ".\n";
                break;
        }
    }

    if (pointerp(sniff_arr) && sniff_arr[2]>time()-TRAIL_LOSS_TIME
        && track_skill> 0)
    {
        dir = sniff_arr[0];
        if (dir == "X" || dir == "M")
            dir = "nowhere";

        if (strlen(dir)>3)
        {
            dir_arr = explode(dir," ");
            if (dir_arr[0] != "the" && dir_arr[0] != "down")
            dir = "the " + dir;
        }
        race = sniff_arr[1];

        if (pointerp(track_arr))
        {
            sniff_result = "You also smell a trail of fresh ";
        }
        else
        {
            sniff_result = "You smell a trail of fresh ";
        }

        switch(track_skill)
        {
            case  1..10:
                sniff_result+="blood.\n";
                break;
            case 11..20:
                if(random(2))
                {
                    exits = environment(player)->query_exit();
                    if(i = sizeof(exits))
                        dir = exits[random(i/3)*3+1];
                }
                sniff_result += "blood likely leading towards "+ 
                dir + ".\n";
                break;
            case 21..50:
                sniff_result += "blood leading towards " + dir + ".\n";
                break;
            case 51..150:
                sniff_result += race + " blood leading towards " + 
                dir + ".\n";
                break;
        }
    }

    object tp=TP;
    set_this_player(player);
    player->catch_msg(track_result);
    player->catch_msg(sniff_result);
    player->remove_prop(LIVE_S_EXTRA_SHORT);
    allbb(" rises again.");
    set_this_player(tp);
    return;
}

/*
 * Function name: sniff_room
 * Description:   Someone looks for sniffs in this room
 */
void
sniff_room()
{
    int     time,
            track_skill;
    object  paralyze;

    time = environment(this_player())->query_prop(OBJ_I_SEARCH_TIME);
    if (time < 1)
        time = 10;
    else
        time += 5;

    track_skill = this_player()->query_skill(SS_TRACKING);
    time -= track_skill/10;

    if (time < 1)
        sniff_now(this_player(), track_skill);
    else
    {
        setuid();
        seteuid(getuid());
        set_alarm(itof(time-1), 0.0, &sniff_now(this_player(), 
        track_skill));
        paralyze = clone_object("/std/paralyze");
        paralyze->set_standard_paralyze("sniffing");
        paralyze->set_stop_fun("stop_sniff");
        paralyze->set_stop_verb("stop");
        paralyze->set_stop_message("You stop searching for your prey.\n");
        paralyze->set_remove_time(time);
        paralyze->set_fail_message("You are busy searching for your "+
        "prey.  You must 'stop' to do something else.\n");
        paralyze->move(this_player(),1);
    }
 }

/*
 * Function name: stop_sniff
 * Description:   interrupt sniffing
 * Arguments:
 * Returns:
 */
varargs int
stop_sniff(mixed arg)
{
    if (!objectp(arg))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "sniff_now")
            {
                args = calls[i][4];
                if (args[0] == this_player())
                    remove_alarm(calls[i][0]);
            }
        }
    }
    allbb(" stops studying the ground.");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    return 0;
}



/*
 * Function name: track
 * Description:   look for tracks
 * Argument:      str - the string given to the command
 * Returns:       0 - failure
 */
int
sniff(string str)
{
    object  room = environment(this_player());

    if (this_player()->query_attack())
    {
        notify_fail("But you are in the middle of a fight!\n");
        return 0;
    }

    if (stringp(str) &&
        (str != "here"))
    {
        notify_fail("Sniff where?\n");
        return 0;
    }

    if (!room->query_prop(ROOM_I_IS))
    {
        notify_fail("You cannot look for your prey here!\n");
        return 0;
    }

    if (this_player()->query_mana() < 2*F_TRACK_MANA_COST)
    {
        notify_fail("You are mentally too exhausted to search.\n");
        return 0;
    }

    write("Using your preternatural senses, you study the room looking "+
    "for signs of your prey.\n");

    allbb(" studies the ground intently." );  

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, ", kneeling on the ground");
    this_player()->add_mana(-F_TRACK_MANA_COST);

    sniff_room();
    return 1;
}
