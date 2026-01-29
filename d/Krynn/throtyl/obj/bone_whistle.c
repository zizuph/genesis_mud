#pragma strict_types

inherit "/std/object";
inherit "/lib/keep";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"

#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>

#define WORG "/d/Krynn/throtyl/steed/worg"
#define STEED_ROOM "/d/Krynn/throtyl/steed/steed_room"

object worg;
int summoning = 0;
int summoned = 0;

public string
whistle_short()
{
    if(this_object()->query_prop(OBJ_I_BROKEN))
        return "broken bone whistle";

    return "bone whistle";
}

void
create_object()
{
    set_name("whistle");
    set_short(whistle_short());
    set_adj("bone");

    set_long("This is a long whistle, carved from a human bone! These " +
        "whistles have been carved by hobgoblins of the Throtyl moors, " +
        "and are used to summon evil worgs that are trained as steeds " +
        "for raiding the lands of Solamnia and Estwilde. Carved along " +
        "the side of the whistle are some words you could read.\n");

    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 86400); // 50 platinum cost
    add_prop(OBJ_M_NO_SELL, "No merchant is interested in buying " +
        "a used bone whistle!\n");

    add_cmd_item(({"words","words on whistle"}),"read",
       "Carved along the side of the whistle are some basic " +
       "instructions on how to summon and control a worg mount:\n" +
       "    'blow bone whistle'          - summons a worg.\n" +
       "    'feed worg with <food type>  - keep your worgs belly full,\n" +
       "                                   helps with its fatigue.\n" +
       "    'mount/dismount worg'        - mount and dismount your worg.\n" +
       "    'automount/autodismount'     - enable or disable automount.\n" +
       "    'lead worg'                  - lead your worg when dismounted.\n" +
       "    'dismiss worg'               - sends your worg away.\n\n");

    //Enable default item expiration
    set_item_expiration();
}


void
summon_worg(object player)
{
    setuid();
    seteuid(getuid());

    string worg_desc;

    if(!objectp(worg))
    {
        object *stable_steeds = all_inventory(find_object(STEED_ROOM));

        foreach(object stabled: stable_steeds)
        {
            if(stabled->query_owner() == player->query_real_name())
                worg = stabled;
        }

        if(!worg)
        {
            worg = clone_object(WORG); 
            worg->refresh_steed(500);
        }
    }  
 
    worg_desc = worg->query_short();
    worg->set_owner(player);

    tell_room(environment(worg), "The " +worg_desc+ " lopes swiftly away.\n");
    worg->move(environment(player), 1);
    tell_room(environment(player), capitalize(LANG_ART(worg_desc))+ 
        " " +worg_desc+ " prowls in.\n");

    summoning = 0;
    return;
}

void
summon_worg_msg(object player)
{
    tell_room(environment(player), "You hear a malevolent howl " +
        "in the distance.\n");

    if(objectp(worg))
    {
        worg->command("emote suddenly looks up and listens intently.");
        worg->command("howl malevolent");
    }

    set_alarm(5.5, 0.0, &summon_worg(player));

    return;
}

/*
 * Function name: do_blow
 * Description:   The player tries to blow the whistle
 * Arguments:	  str - the string describing what he wants to blow
 * Returns:	  1/0
 */
public int
do_blow(string str)
{
    string vb;
    object player = this_player();

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!strlen(str))
        return 0;

    if(str == "whistle" || str == "bone whistle")
    {
        if(this_object()->query_prop(OBJ_I_BROKEN))
        {
            write("The bone whistle is broken. No " +
                "sound comes from it.\n");
            return 1;
        }

        if(summoning)
        {
            write("You are in the process of summoning " +
                "a worg... be patient!\n");
            return 1;
        }

        if(present(worg, environment(this_player())))
        {
            write("The worg is here with you!\n");
            return 1;
        }

        write("You blow a piercingly loud " +
            "and dissonant note on the bone whistle.\n");
        say(QCTNAME(this_player())+ " blows a piercingly loud " +
            "and dissonant note on a bone whistle.\n");

        set_alarm(5.5, 0.0, &summon_worg_msg(player));
        summoning = 1;

        return 1;
    }

    return 0;
}

/*
 * Function name: do_blow
 * Description:   The player tries to blow the whistle
 * Arguments:	  str - the string describing what he wants to blow
 * Returns:	  1/0
 */
public int
do_dismiss(string str)
{
    string vb, target_name;
    object * oblist;
    object player = this_player();
    object alt_rider;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!strlen(str))
        return 0;

    oblist = parse_this(str, "[the] %o");

    if (!sizeof(oblist))
    {
        notify_fail("Dismiss what?\n");
        return 0;
    }

    foreach(object steed: oblist)
    {
        if(steed->query_throtyl_worg() &&
            (steed->query_owner() == player->query_real_name()))
        {
            if(summoning)
            {
                write("You are in the process of summoning " +
                    "a worg... be patient!\n");
                return 1;
            }

            write("You dismiss the " +steed->query_short()+ ".\n");
            say(QCTNAME(this_player())+ " dismisses the " +
                steed->query_short()+ ".\n");

            steed->dismount_all(1);
            set_alarm(0.5, 0.0, &tell_room(environment(steed), 
                "The " +steed->query_short()+ " lopes off.\n"));
            set_alarm(0.6, 0.0, &steed->move(STEED_ROOM, 1));

            return 1;
        }

        if(steed->query_throtyl_worg())
        {
            alt_rider = find_living(steed->query_owner());

            if(alt_rider)
            {
                write("The master of the " +steed->query_short()+ 
                    " is still in the realms. You can not dismiss " +
                    "it.\n");
                return 1;
            }

            write("With it's master no longer in the realms, you " +
                "chase the " +steed->query_short()+ " away.\n");
            say(QCTNAME(this_player())+ " chases the " +
                steed->query_short()+ " away.\n");

            steed->dismount_all(1);
            set_alarm(0.5, 0.0, &tell_room(environment(steed), 
                "The " +steed->query_short()+ " lopes off.\n"));
            set_alarm(0.6, 0.0, &steed->move(STEED_ROOM, 1));

            return 1;
        }

        notify_fail("Dismiss what?!\n");
        return 0;

    }

    notify_fail("Dismiss what? Your worg?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_blow, "blow");
    add_action(do_dismiss, "dismiss");
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this herb is recoverable. If you
 *                have variables you want to recover yourself, you have to
 *                redefine this function, keeping at least the filename and
 *                the herb recovery variables, like they are queried below.
 *                If, for some reason, you do not want your herb to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
string
query_recover()
{
    return MASTER + ":" + query_item_expiration_recover();
} /* query_recover */
 
void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}

