/*
 * /d/Gondor/domain_link.c
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/domain_link.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dwarf_guild/dwarf.h"
#include "/d/Gondor/common/potions/potion_defs.h"

static mapping Potion_Ingr;


/*
 * Function name: preload_link
 * Description  : This function should be masked by domains that want to
 *                preload some files at boot time. It should contain only
 *                calls to the function preload().
 *                All files that are preloaded must have the prop
 *                ROOM_I_NO_CLEANUP set and must use #pragma save_binary.
 */
public void
preload_link()
{
    /*
     * Rooms that are needed frequently by other objects:
     */
    preload(CLOCK);
    preload("/d/Gondor/workroom");
    preload("/d/Gondor/minas/lib/master");
    preload("/d/Gondor/common/herbs/herb_master");
    preload("/d/Gondor/common/lib/weather_master");

    /*
     * Rooms that start ships:
     */
    preload("/d/Gondor/pelargir/docks/dock2");
    preload("/d/Gondor/pelargir/docks/dock3");
    preload("/d/Gondor/pelargir/docks/dock5");
    preload("/d/Gondor/pelargir/docks/dock7");
    preload("/d/Gondor/pelargir/docks/dock8");
    preload("/d/Gondor/tharbad/pier/pier1");
    preload("/d/Gondor/ithilien/poros/pier");

    /*
     * Guild master objects:
     */
    preload("/d/Gondor/common/guild/recruithall");
    preload("/d/Gondor/common/guild/gondor/gondor_council");
    preload("/d/Gondor/common/guild2/death_room");
//    preload("/d/Gondor/common/guild2/post");
    preload("/d/Gondor/common/dwarf_guild/join");
    preload("/d/Gondor/guilds/militia/room/join");
    preload("/d/Gondor/clubs/anghoth/manager");
    preload("/d/Gondor/clubs/nisse/manager");
    preload("/d/Gondor/guilds/rangers/manager/manager");
    preload("/d/Gondor/guilds/rangers/shadow/ranger_shadow");

    /* Stern's christmas tree dispenser. */
    preload("/w/stern/obj/dispenser");

    /*
     * Guild, club etcetera souls:
     */
    preload("/d/Gondor/common/dwarf_guild/dwarf_shadow");
}

/*
 * Function name: query_potion_map
 * Description  : Returns the mapping used in Gondor with ingredients for
 *                potions.
 * Returns      : mapping - the mapping with ingredients and potions.
 */
public mapping
query_potion_map()
{
    if (!mappingp(Potion_Ingr))
        Potion_Ingr = GONDOR_POTION_INGREDIENTS;
    return Potion_Ingr;
}

/*
 * Function name: query_restore_items
 * Description  : Find out which items can be restored to a player in this
 *                domain.
 * Arguments    : object player - the player to test for.
 * Returns      : mapping - the mapping with items that can be restored.
 */
public mapping
query_restore_items(object player)
{
    mapping items = ([ ]);

    if ((DWARF_DIR + "join")->query_restore_belt(player))
    {
        items[DWARVEN_RACE_GUILD_BELT_ID] = "The belt of the Rockfriend Guild.";
    }

    if (SCABBARD_RESTORE->check_restore(player))
    {
        items[SCABBARD_ID] = "The golden scabbard of Gondor.";
    }

    if ((MILITIA_DIR + "room/join")->query_boot_recover(player))
    {
        items[MILITIA_BOOTS_ID] = "The boots of a militia member.";
    }


    return items;
}

/*
 * Function name: restore_item
 * Description  : Called to restore a single item into a player.
 * Arguments    : object player - the player to which to restore an item.
 *                string item - the code of the item to restore.
 * Returns      : int 1/0 - success/failure.
 */
public int
restore_item(object player, string item)
{
    switch(item)
    {
    case DWARVEN_RACE_GUILD_BELT_ID:
        return (DWARF_DIR + "join")->restore_belt(player);
    case SCABBARD_ID:
        return (SCABBARD_RESTORE->cellar_restore(player));
    case MILITIA_BOOTS_ID:
        return ((MILITIA_DIR + "room/join.c")->restore_boots(player));
    }
    return 0;
}

/*
 * Function name: delete_player
 * Description  : This function is called every time a player is deleted from
 *                the game. It can be used for domain specific code that is
 *                called to clean up information about the player.
 * Notice       : Do NOT redefine this function if it is not used. For extra
 *                stability this function is called using an alarm, so if it
 *                is not used, let us not waste alarms on functions that do not
 *                do anything anyways.
 * Arguments    : string name - the name of the deleted player.
 */
public void
delete_player(string name)
{
    object man = find_object("/d/Gondor/guilds/rangers/manager/manager");

    if (man->query_ranger(name))
    {
        man->remove_ranger(name);
        man->rlog("rangers_log", capitalize(name) +
            ", non-existant Ranger removed.\n");
    }
}
