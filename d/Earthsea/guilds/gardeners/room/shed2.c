#pragma strict_types
#pragma no_clone
#pragma no_inherit

#include "../defs.h"
#include <ss_types.h>

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/guilds/gardeners/guild_room";
inherit "/lib/skill_raise";

#define JOHANNA ("/d/Earthsea/guilds/gardeners/npc/johanna")

private object gardener;

public void
create_earthsea_room()
{
    set_short("Garden shed");
    set_long("This is a simple wooden shed. The walls are covered with " +
        "holes, from which countless dozens of pegs protrude, many of " +
        "them used to hang various gardening implements. There is a " +
        "small workbench in the corner that is scattered with dirty " +
        "papers and pots.\n");
    add_item(({"implements", "garden implements", "gardening implements",
        "pot", "pots"}),
        "Standard issue gardeners' equipment.\n");
    add_item(({"wall", "walls", "holes", "peg", "pegs"}),
        "The walls are made of what one might call pegboard.\n");
    add_item(({"bench", "small bench", "workbench", "work bench",
        "small workbench"}),
        "A small, sturdy wooden bench, covered with dirty papers " +
        "and pots.\n");
    add_item(({"dirty paper", "paper", "dirty papers", "papers"}),
        "The papers seem to contain notes on breeding various plants.\n");
    add_cmd_item(({"dirty paper", "paper", "dirty papers", "papers"}),
          ({ "read" }), "The papers seem to contain notes on breeding " +
          "various plants.\n");
    add_exit("wall", "out");
    reset_room();

    add_config_guild_room(GARDENER_NAME, GARDENER_SOUL, GARDENER_SHADOW_LAY,
        GARDENER_STYLE, "layman", 
        "init_new_gardener", "remove_gardeners_guild", "switch_gardeners_guild",
        ({ "join" }), ({ "leave" }), ({ "switch" }),
        "layman", "layman", "layman");
    add_config_guild_room(GARDENER_NAME, GARDENER_SOUL, GARDENER_SHADOW_CFT,
        GARDENER_STYLE, "craft", 
        "init_new_gardener", "remove_gardeners_guild", "switch_gardeners_guild",
        ({ "join" }), ({ "leave" }), ({ "switch" }),
        "craft", "craft", "craft");
    
    sk_add_train(SS_HERBALISM, "find herbs", "herbalism", 0, 60);
    sk_add_train(SS_AWARENESS, "detect hidden details", "awareness", 0, 50);
    sk_add_train(SS_LOC_SENSE, ({ "sense details about the environment", 
        "sense details about the environment" }),
        "location sense", 0, 50);
    sk_add_train(SS_HUNTING, "hunt", "hunting", 0, 30);
    sk_add_train(SS_TRACKING, "track", "tracking", 0, 30);
    sk_add_train(SS_TRADING, "trade", "trading", 0, 30);
    sk_add_train(SS_FR_TRAP, "find and remove traps", 0, 0, 20);
    sk_add_train(SS_SPELLCRAFT, "cast spells", "spellcraft", 0, 30);
    sk_add_train(GARDENER_SKILL_TITLE, "__gardener_title", "gardener title", 0, 0);
}

public void
reset_room()
{
    if(!gardener)
    {
        gardener = clone_object(JOHANNA);
    }

    gardener->move(this_object(), 1);
}

public int
try_join(string str)
{
    if(!gardener || !gardener->query_done_all_tasks(this_player()))
    {
        return 0;
    }

    return _join(str);
}

public void
init()
{
    ::init();
    init_skill_raise();
    add_action(try_join, "join");
    add_action(_leave, "leave");
    add_action(_switch, "switch");
}

public int
sk_improve(string str)
{
    if(!this_player()->query_wiz_level() &&
        this_player()->query_guild_name_lay() != GARDENER_NAME &&
			this_player()->query_guild_name_craft() != GARDENER_NAME)
    {
        return notify_fail("What gives you the idea that you " +
            "can do that here?\n");
    }

    return ::sk_improve(str);
}
