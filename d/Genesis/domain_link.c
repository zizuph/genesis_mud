/*
 * /d/Genesis/domain_link.c
 *
 * This module is the link of the domain with the rest of the administrative
 * system. It is called at boot to preload some modules.
 *
 * 10/10/23 ?           Previous update
 * 11/09/07 Lavellan    Imbuement transferred from Sparkle
 */

inherit "/std/domain_link";

#include <const.h>
#include "/d/Genesis/obj/donation/donation.h"
#include "/d/Genesis/sys/gem.h"

#define EVENT_DISPATCHER "/d/Genesis/ateam/aoe/events/event_dispatcher"

/*
 * Function name: preload_link
 * Description  : This function is called at boot to preload some files.
 */
void
preload_link()
{
    /* Beginner files */
    preload("/d/Genesis/login/bodies");

    /* The common board. Don't touch this or the Genesis specific login
     * stuff in start_player() will fail.
     */
    preload("/d/Genesis/obj/common_master");

    /* The statue room is needed for the who-command. */
    preload("/d/Genesis/obj/statue");

    /* The circle line ship */
    preload("/d/Genesis/start/human/town/pier4");

    /* The master of the delivery offices. */
    preload("/d/Genesis/delivery/master");

    /* The gem manager */
    preload("/d/Genesis/gems/gem_manager");

    /* The mercenaries crest room */
    preload("/d/Genesis/guilds/merc/room/crest_room");

    /* Dragon Order guild server */
    preload("/d/Genesis/guilds/monks/monastery/sys/srvr_monk");

    /* The fury of Genesis.
    preload("/d/Genesis/wiz/fury");
     */

    /* Arch boards -> mudlib board for cross-posting mudlib updates. */
    preload("/d/Genesis/wiz/arch_room");

    /* The New Ship Control Center. */
    preload("/d/Genesis/gsl_ships/control/room");

    /* Events. */
    EVENT_DISPATCHER->preload_link();

    /* The Genesis Census */
    preload("/d/Genesis/census/census_master");

    /* The Item Recovery Handler. */
    preload("/d/Genesis/specials/lib/item_recovery_handler");    
    
    /* The AoB Item Database Handler. */
    preload("/d/Genesis/specials/lib/item_database_handler");    

    /* Imbuement handlers */
    preload("/d/Genesis/ateam/aod/imbuement/debugger_tell");
    preload("/d/Genesis/ateam/aod/imbuement/logger");
    preload("/d/Genesis/ateam/aod/imbuement/imbuement_master");
    preload("/d/Genesis/ateam/aod/imbuement/imbuement_generator");
    preload("/d/Genesis/ateam/aod/imbuement/imbue");
    
    /* Web client magic map generation. Not needed anymore as the maps are
     * now sent via GMCP directly /Mercade
    preload("/d/Genesis/ateam/aow/client/magicmap");
     */

    /* Player housing manager */
    preload("/d/Genesis/houses/house_manager");
}

/*
 * Function name: delete_player
 * Description  : This is called whenever a player is deleted. We use it to
 *                remove the account of the player from the GoG.
 * Arguments    : string name - the name of the player.
 */
void
delete_player(string name)
{
    "/secure/gog_accounts"->remove_account(name);
}

/*
 * Function name: rename_player
 * Description  : This is called whenever a player is renamed. We use it to
 *                rename the account of the player from the GoG.
 * Arguments    : string oldname - the old name of the player.
 *                string newname - the new name of the player.
 */
void
rename_player(string oldname, string newname)
{
    "/secure/gog_accounts"->rename_account(oldname, newname);
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

    if (DONATION_MASTER->query_restore_brooch(player))
    {
        items[DONOR_BROOCH_ID] = "The toroid brooch given to donors of Genesis.";
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
    case DONOR_BROOCH_ID:
        return DONATION_MASTER->restore_brooch(player);
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
    EVENT_DISPATCHER->armageddon(level);

    switch(level)
    {
        case ARMAGEDDON_ANNOUNCE:
        {
            // The mercenary's armour moves items from private to public
            // 5 minutes before shutdown
            "/d/Genesis/guilds/merc/room/armoury"->start_armageddon_alarm();
            
            // Saving Racks should refresh their content and be notified.
            "/d/Genesis/specials/lib/autosave_rack_master"->refresh_all_saving_racks();
            "/d/Genesis/specials/lib/autosave_rack_master"->notify_all_saving_racks();
            
            break;
        }
        case ARMAGEDDON_CANCEL:
        {
            "/d/Genesis/guilds/merc/room/armoury"->stop_armageddon_alarm();
            break;
        }
        case ARMAGEDDON_SHUTDOWN:
        {
            // Saving Racks need to be notified
            "/d/Genesis/specials/lib/autosave_rack_master"->notify_all_saving_racks();
            // Save imbuement database
            "/d/Genesis/ateam/aod/imbuement/imbuement_master"->save(1);
            break;
        }
    }
}

string *
query_gem_list()
{
    return map(get_dir(GEM_OBJ_DIR), &operator(+)(GEM_OBJ_DIR, ));
}

