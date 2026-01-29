/*******************************************************************\
| DOMAIN_LINK.C                                                     |
\*******************************************************************/

/*
 * 01/02/2006 Arandir   Added monk preload
 *                      Added mercenary armageddon alarm
 * 14/02/2006 Arandir   Added domain server preload
 * 21/11/2010 Lavellan  Imbuement added
 * 07/09/2011 Lavellan  Imbuement transferred to Genesis
 * 29/03/2015 Mercade   Rename players link to tutorial
 */

#include <const.h>

inherit "/std/domain_link";

#include "sys/defs.h"
#include S_DOMAIN_SYS_MASTERS

void
preload_link ()
{
    // Domain Server
    preload (S_DOMAIN_MASTER);

    // Mercenaries Guild Server
    preload (S_DOMAIN_MASTER_MERCS);

    // Monks Guild Server
    preload (S_DOMAIN_MASTER_MONKS);

    // Actors Guild Server
    preload (S_DOMAIN_MASTER_RPG);

    // Rich Men Guild Server
    // Rich Men Pier & Ship
    preload (S_DOMAIN_MASTER_RMC);
    preload (S_DOMAIN_CLUBS_DIR + "rmc/ship/gship");
    preload (S_DOMAIN_CLUBS_DIR + "rmc/room/pier");

    // Auction House
    preload (S_DOMAIN_AREA_DIR + "city/auction/obj/auction_data_store");
    preload (S_DOMAIN_AREA_DIR + "city/auction/room/auction_house");
    
    // Faerie Shipline to VK
    preload (S_DOMAIN_AREA_DIR + "faerie/rooms/forest/pier01n");
}

void
armageddon (int level)
{
    switch (level)
    {
    case ARMAGEDDON_ANNOUNCE:
        S_LOAD (S_DOMAIN_ARMORY_MERCS);
        S_DOMAIN_ARMORY_MERCS->start_armageddon_alarm();
        break;
    case ARMAGEDDON_CANCEL:
        S_LOAD (S_DOMAIN_ARMORY_MERCS);
        S_DOMAIN_ARMORY_MERCS->stop_armageddon_alarm();
        break;
    case ARMAGEDDON_SHUTDOWN:
        "/d/Genesis/imbuement/imbuement_master"->save(1);
        (S_DOMAIN_AREA_DIR + "city/auction/obj/auction_data_store")->save();
    }
}

public void
rename_player(string oldname, string newname)
{
    (S_DOMAIN_AREA_DIR + "tutorial/obj/tutorial_master")->rename_player(oldname, newname);
}
