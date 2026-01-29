#pragma strict_types

#include <const.h>
#include "/d/Shire/sys/files.h"

inherit "/std/domain_link.c";

public void
preload_link()
{
    //  Preload all the important rooms within the Shire
    preload("/d/Shire/common/bree/inn");
    preload("/d/Shire/common/greyhaven/shore");
    preload("/d/Shire/common/greyhaven/pier1");
    preload("/d/Shire/common/greyhaven/pier2");
    preload("/d/Shire/common/greyhaven/pier3");
    preload("/d/Shire/common/greyhaven/pier4");
    preload("/d/Shire/common/greyhaven/pier5");
    preload("/d/Shire/common/greyhaven/pier6");
    preload(HERB_MASTER);
    preload(QUEST_MASTER);
    //preload("/d/Shire/common/herbs/obj/control_room");

    // Preload guild master objects
    preload("/d/Shire/clubs/huntclub/huntclub_joinrm");
    preload("/d/Shire/guild/smiths/rooms/manager_room");
    preload("/d/Shire/guild/smiths/lib/master");
    preload("/d/Shire/herald/join");
    preload("/d/Shire/guild/noldor/foyer");
    preload("/d/Shire/trickster/join.novouching");
    preload("/d/Shire/rivendell/room/valley/stable");
    preload("/d/Shire/guild/orc_guild/rooms/join");	
    //preload("/d/Shire/trickster/join");

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
    "/d/Shire/clubs/huntclub/manager/huntclub_manager"->rename_account(oldname, newname);
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
    switch(level)
    {
        case ARMAGEDDON_ANNOUNCE:
        {
            break;
        }
        case ARMAGEDDON_CANCEL:
        {
            break;
        }
        case ARMAGEDDON_SHUTDOWN:
        {
            "/d/Shire/clubs/huntclub/manager/huntclub_manager"->armageddon();               
            break;
        }
    }
}



string query_commodity(string name)
{
    return ([
        "wheat" : "/d/Shire/common/commodity/wheat",
        "whflour" : "/d/Shire/common/commodity/flour_wh",
        ])[name];
}    
