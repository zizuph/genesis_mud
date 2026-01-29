#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/abilities";
inherit "/cmd/std/command_driver";
inherit DRAGONARMY_SPECIALS + "dragonarmy_utility";
inherit DRAGONARMY_LIB + "help";
inherit DRAGONARMY_LIB + "idea";
inherit DRAGONARMY_LIB + "promotions";
inherit DRAGONARMY_LIB + "demotions";
inherit DRAGONARMY_LIB + "dlist";
inherit DRAGONARMY_LIB + "general";
inherit DRAGONARMY_LIB + "fund";

#include "emotes.c"
#include <filter_funs.h>
#include <composite.h>
#include <language.h>

#define AREA_PATH   ("/d/Krynn/common/warfare/areas/")

string 
get_soul_id()
{
    return GUILD_NAME;
}

int
query_cmd_soul() 
{
    return 0; /* this is not to be used as soul, should be only inherited */
}

public mapping
query_ability_map()
{
    return ([
    "dswoop"        : DRAGONARMY_SPECIALS + "dragon_swoop",
    "dbreath"       : DRAGONARMY_SPECIALS + "dragon_breath",
    "dsteed"        : DRAGONARMY_SPECIALS + "summon_dragon_steed",
    "dfear"         : DRAGONARMY_SPECIALS + "summon_strike_dragon",
    "summon"        : DRAGONARMY_SPECIALS + "summon_strike_dragon",
     ]);
}

mapping
query_cmdlist()
{
    return ([
      "dscout"  : "dscout",
      "didea"   : "_idea",
      "promote" : "promote_soldier",
      "demote"  : "demote_soldier",
#ifndef NO_DLIST
      "list"   : "list",
      "mlist"  : "list",
#endif

      "relinquish" : "make_general",
      "punish"	: "punish_soldier",
      "ban"	: "ban_from_dragonarmy",
      "lift"	: "remove_ban",
      "submit"	: "submit_life",
      "exterminate" : "exterminate",

      "add"	: "add_master_title",
      "remove"	: "remove_master_title",
      "charge"	: "set_master",
      "revoke"	: "remove_master",
      "check"	: "query_masters",

      "fundraising" : "fundrising",

      
      "dswoop"  : "do_ability",
      "dbreath" : "do_ability",
      "dfear"   : "do_ability", "summon"	: "do_ability",
      "dsteed"  : "do_ability",

    ]) + help_cmdlist() + emotes_cmdlist();
}

string
query_warfare_location(string str)
{
    if(str == "Newports Area")
        return "newports";
    if(str == "Western Solamnian Plains")
        return "west_solamnia";
    if(str == "Estwilde Plains")
        return "estwilde";
    if(str == "Solace Area")
        return "solace";
    if(str == "Central Abanasinian Plains")
        return "central_abanasinia";
    if(str == "North Abanasinian Plains")
        return "north_abanasinia";
    if(str == "Nightlund Plains")
        return "nighlund";
    if(str == "Guardlund Plains")
        return "guardlund";
    if(str == "Throtyl Pass")
        return "throtyl";
    if(str == "Icewall Plains")
        return "icewall";
    if(str == "Trelgorn Forest")
        return "trelgorn";
    if(str == "Abanasinian Plains")
        return "central_abanasinia";
    if(str == "Eastern Solamnian Plains")
        return "nighlund";

    return "solace";
}

mixed 
check_warfare_object(mixed foe)
{
    if(objectp(foe))
        return foe;
}

int
dscout(string str)
{
    object player = this_player();

    if (!objectp(query_summoned_dragon(player)))
    {
        player->catch_tell("You don't see a dragon present that can "
                + "be called upon!\n");
        return 1;
    }

    object dragon = query_summoned_dragon(player);

    if (strlen(environment(player)->query_area_name()) < 2)
    {
        player->catch_msg("You are not on a Krynn battlefield, " +
            "so " +QTNAME(dragon)+ " doesn't know what to look for.\n");
        return 1;
    }

    

    string area_name = environment(player)->query_area_name();
    string area = query_warfare_location(area_name);
    int foe_count = 0;

    if(!sizeof(find_object(AREA_PATH + area)->query_actual_units()))
    {
        player->catch_tell("Strangely there are no defenders that " +
            "your dragon can find.\n");
        return 1;
    }

//    mixed * locations = map(find_object(AREA_PATH + area)->query_actual_units(),  
//        environment);

    mixed * locations = map(find_object(AREA_PATH + area)->query_actual_units(),  
        check_warfare_object);

    locations -= ({ 0 });
    locations = map(locations, environment);

    foreach(mixed foe: locations)
    {
        if(!objectp(foe))
            locations -= ({ foe });
         else
             foe_count += 1;
    }

    if(!sizeof(locations))
    {
        player->catch_msg(QCTNAME(dragon)+ " scouts the battlefields, but " +
            "cannot find any defenders remaining.\n");
        tell_room(environment(player), QCTNAME(dragon)+ " circles the battlefield, " +
            "searching for defenders.\n", ({ player }), player);

        return 1;
    }

    int locs = sizeof(locations);
    int ran_loc = random(locs);

    object location = locations[ran_loc];
    object * inv = all_inventory(location);    
    object * live = FILTER_LIVE(inv);
    object * dead = FILTER_DEAD(inv);

    player->catch_msg("With a predatory shriek, " +QTNAME(dragon)+ " circles " +
        "the battlefield, noting that there are still " +LANG_NUM2WORD(foe_count)+ 
        " defenders of the " +area_name+ " remaining.\n");
    tell_room(environment(player), "With a predatory shriek, " +QTNAME(dragon)+
        " circles the battlefield, searching for defenders.\n", ({ player }), player);

    return 1;
}

void
create()
{
    set_help_type(({ "dragonarmy" }));
    read_help_dir(DRAGONARMY_HELP);
}

