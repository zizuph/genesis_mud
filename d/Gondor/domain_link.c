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

/* Global variable with the potion ingredients. */
static mapping Potion_Ingr;

#include <const.h>

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
    /* Rooms that are needed frequently by other objects */
    preload(CLOCK);
    preload("/d/Gondor/workroom");
    preload("/d/Gondor/minas/lib/master");
    preload("/d/Gondor/common/herbs/herb_master");
    preload("/d/Gondor/common/lib/weather_master");

    /* Rooms that start ships */
    preload("/d/Gondor/pelargir/docks/dock2");
    preload("/d/Gondor/pelargir/docks/dock3");
    preload("/d/Gondor/pelargir/docks/dock5");
    preload("/d/Gondor/pelargir/docks/dock7");
    preload("/d/Gondor/pelargir/docks/dock8");
    preload("/d/Gondor/tharbad/pier/pier1");
    preload("/d/Gondor/ithilien/poros/pier");
    preload("/d/Gondor/ithilien/poros/pier2");

    preload("/d/Gondor/rhovanion/mirkwood/master");

    /* Guild master objects */
    preload("/d/Gondor/guilds/morgulmage/master/master");
    preload("/d/Gondor/common/guild2/idleness");
    preload("/d/Gondor/common/guild2/death_room");
    preload("/d/Gondor/common/guild/recruithall");
    preload("/d/Gondor/common/guild/gondor/gondor_council");
    preload("/d/Gondor/common/dwarf_guild/join");
    preload("/d/Gondor/guilds/militia/room/join");
    preload("/d/Gondor/clubs/anghoth/manager");
    preload("/d/Gondor/clubs/nisse/manager");
    preload("/d/Gondor/guilds/rangers/manager/manager");
    preload("/d/Gondor/guilds/rangers/shadow/rangers_shadow");
    preload("/d/Gondor/guilds/rangers/ithilien/window");
    preload("/d/Gondor/guilds/rangers/north/great_hall");
    preload("/d/Gondor/guilds/rangers/hq/join");
    preload("/d/Gondor/guilds/rangers/hq/recruiter_office");

    /* Stern's christmas tree dispenser. */
    preload("/w/stern/obj/christmasdispenser");

    /* Guild, club etcetera souls: */
    preload("/d/Gondor/common/dwarf_guild/dwarf_shadow");

    /* Rohim's workroom, which in turn loads the XP poller */
    //preload("/w/rohim/workroom");
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
 * Function name: armageddon
 * Description  : This function is called from SECURITY when it is time to
 *                close down the game. Note that this function should only
 *                be used for some basic domain administration as all domains
 *                should be processed in one run.
 * Arguments    : int level - the status of Armageddon, see the definitions
 *                     in <const.h>.
 *                ARMAGEDDON_ANNOUNCE - Armageddon wakes up and announces.
 *                ARMAGEDDON_CANCEL   - No shut down after all.
 *                ARMAGEDDON_SHUTDOWN - Game shuts down NOW.
 */
void armageddon(int level)
{
    if (level == ARMAGEDDON_SHUTDOWN) {
        "/d/Gondor/guilds/morgulmage/master/master"->armageddon_shutdown();
    }
}
