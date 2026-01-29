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

#define BOAR "/d/Ansalon/estwilde/steed/warboar"
#define STEED_ROOM "/d/Ansalon/estwilde/steed/steed_room"

object boar;
int summoning = 0;
int summoned = 0;

public string
whistle_short()
{
    return "pig whistle";
}

void
create_object()
{
    set_name("whistle");
    set_short(whistle_short());
    set_adj("pig");

    set_long("This short flat reeded instrument is a pig whistle " +
        "of the hill dwarves. When blown it creates a loud grunting " +
        "noise, mimicking the mating call of an Estwilde sow. Carved along " +
        "the side of the whistle are some words you could read.\n");

    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 34560);
    add_prop(OBJ_M_NO_SELL, "No merchant is interested in buying " +
        "a used pig whistle!\n");

    add_cmd_item(({"words","words on whistle"}),"read",
       "Carved along the side of the whistle are some basic " +
       "instructions in dwarven on how to summon and control a war boar:\n" +
       "    'blow pig whistle'           - summons a war boar mount.\n" +
       "    'feed boar with <food type>  - keep your pig's belly full,\n" +
       "                                   helps with its fatigue.\n" +
       "    'mount/dismount boar'        - mount and dismount your boar.\n" +
       "    'automount/autodismount'     - enable or disable automount.\n" +
       "    'lead boar'                  - lead your boar when dismounted.\n" +
       "    'dismiss boar'               - sends your boar away.\n\n");

    //Enable default item expiration
    set_item_expiration();
}


void
summon_boar(object player)
{
    setuid();
    seteuid(getuid());

    string boar_desc;

    if(!objectp(boar))
    {
        object *stable_steeds = all_inventory(find_object(STEED_ROOM));

        foreach(object stabled: stable_steeds)
        {
            if(stabled->query_owner() == player->query_real_name())
                boar = stabled;
        }

        if(!boar)
        {
            boar = clone_object(BOAR); 
            boar->refresh_steed(500);
        }
    }  
 
    boar_desc = boar->query_short();
    boar->set_owner(player);

    tell_room(environment(boar), "The " +boar_desc+ " trots swiftly away.\n");
    boar->move(environment(player), 1);
    tell_room(environment(player), capitalize(LANG_ART(boar_desc))+ 
        " " +boar_desc+ " trots in.\n");

    summoning = 0;
    return;
}

void
summon_boar_msg(object player)
{
    tell_room(environment(player), "You hear a squeal " +
        "in the distance.\n");

    if(objectp(boar))
    {
        boar->command("emote suddenly looks up and listens intently.");
        boar->command("emote squeals loudly.");
    }

    set_alarm(5.5, 0.0, &summon_boar(player));

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

    if(str == "whistle" || str == "pig whistle")
    {
        if(this_object()->query_prop(OBJ_I_BROKEN))
        {
            write("The pig whistle is broken. No " +
                "sound comes from it.\n");
            return 1;
        }

        if(summoning)
        {
            write("You are in the process of summoning " +
                "a boar... be patient!\n");
            return 1;
        }

        if(present(boar, environment(this_player())))
        {
            write("The boar is here with you!\n");
            return 1;
        }

        write("You blow a loud grunting " +
            "note on the pig whistle.\n");
        say(QCTNAME(this_player())+ " blows a loud " +
            "grunting note on a pig whistle.\n");

        set_alarm(5.5, 0.0, &summon_boar_msg(player));
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
        if(steed->query_estwilde_boar() &&
            (steed->query_owner() == player->query_real_name()))
        {
            if(summoning)
            {
                write("You are in the process of summoning " +
                    "a boar... be patient!\n");
                return 1;
            }

            write("You dismiss the " +steed->query_short()+ ".\n");
            say(QCTNAME(this_player())+ " dismisses the " +
                steed->query_short()+ ".\n");

            steed->dismount_all(1);
            set_alarm(0.5, 0.0, &tell_room(environment(steed), 
                "The " +steed->query_short()+ " trots off.\n"));
            set_alarm(0.6, 0.0, &steed->move(STEED_ROOM, 1));

            return 1;
        }

        if(steed->query_estwilde_boar())
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
                "The " +steed->query_short()+ " trots off.\n"));
            set_alarm(0.6, 0.0, &steed->move(STEED_ROOM, 1));

            return 1;
        }

        notify_fail("Dismiss what?!\n");
        return 0;

    }

    notify_fail("Dismiss what? Your boar?\n");
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

