/*
 * This file used by the mudlib when the game boots and goes down.
 */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/potions/potion_defs.h"
#include CLOCKH

inherit "/std/domain_link";
inherit "/d/Krynn/common/special/restoration";

#include <const.h>

/* Global variable. */
static mapping Potion_Ingr;

/*
 * Function name: preload_link
 * Description:   Build a list of objects that should be loaded
 *                before the first player enters the game.
 */
public void
preload_link()
{
    /* General master files */
    preload(VOID);
    preload(CLOCK);
    preload("/d/Krynn/common/time_master");
    preload("/d/Krynn/common/herbs/herb_master");
    preload("/d/Krynn/common/warfare/armymaster");
    preload("/d/Krynn/common/warfare/freepeoplerecruit");
    preload("/d/Krynn/icewall/admin/dragonadmin");

    /* Guild masters */
    preload("/d/Krynn/solamn/vin/knight/admin/admin");
    preload("/d/Krynn/guilds/gnomes/lib/manager");
    
    /* WoHS are closed
       preload("/d/Krynn/wayreth/guild/admin/admin");
       preload("/d/Krynn/wayreth/tower/mage_skills");
    */
    preload("/d/Krynn/solamn/thief/guild/master");

    /* Other important rooms */
    preload("/d/Krynn/solamn/vin/room/sb2");

    preload("/d/Krynn/solace/forest/toedecave");
    preload("/d/Krynn/solace/road/xroad");
    preload("/d/Krynn/common/random_meet");
    preload("/d/Krynn/common/objects/bracelet/cloner");

    preload("/d/Krynn/throtyl/steed/steed_room");

    /* Shiplines */
    preload("/d/Krynn/que/newports/ship/pier");
    preload("/d/Krynn/solace/ship/pier");
    preload("/d/Krynn/solamn/palan/ship/pier");
    preload("/d/Krynn/solamn/palan/ship2/pier");
    preload("/d/Krynn/icewall/castle2/rooms/snow_plain11");
    preload("/d/Krynn/solamn/eplains/rooms/eplain-4-21-V");


    /* since the create_domain were removed from the domain link */
    /* one has to "Call domain_link preload_link" each time new  */
    /* commodity is inserted ,  by default commoditiies would be */
    /* configured after reboot                                   */
    
    add_commodity("iron bar"     , KCOMMERCE + "ironbar");
    add_commodity("carbon bar"   , KCOMMERCE + "carbonbar");
    add_commodity("silver bar"   , KCOMMERCE + "silverbar");
    add_commodity("gold bar"     , KCOMMERCE + "goldbar");
    add_commodity("hop"          , KCOMMERCE + "hop");
    add_commodity("malt"         , KCOMMERCE + "malt");
    add_commodity("scale"        , KCOMMERCE + "scale");
    add_commodity("leather scrap", KCOMMERCE + "leather_scrap");

    add_commodity("Sol.2H.lsword", 
  "/d/Krynn/solamn/vin/weapon/two_handed_sword");
    add_commodity("s_halberd"    , "/d/Krynn/solamn/vin/weapon/s_halberd");
    add_commodity("s_mace"       , "/d/Krynn/solamn/vin/weapon/s_mace");
    add_commodity("s_sword"      , "/d/Krynn/solamn/vin/weapon/s_sword");
    add_commodity("s_shortsword" , "/d/Krynn/solamn/vin/weapon/s_shortsword");

    add_commodity("scalearmour"  , "/d/Krynn/solamn/vin/armour/scalearmour");  
    add_commodity("full_armour" , "/d/Krynn/solamn/vin/armour/full_armour");
    add_commodity("s_armour"     , "/d/Krynn/solamn/vin/armour/s_armour");
    add_commodity("s_boots"      , "/d/Krynn/solamn/vin/armour/s_boots");
    add_commodity("s_gauntlets"  , "/d/Krynn/solamn/vin/armour/s_gauntlets");
    add_commodity("s_helm"       , "/d/Krynn/solamn/vin/armour/s_helm");
    add_commodity("s_shield"     , "/d/Krynn/solamn/vin/armour/s_shield");

    add_commodity("goldpiece"    , "/d/Krynn/solamn/thief/obj/goldpiece");
    add_commodity("silverpiece"  , "/d/Krynn/solamn/thief/obj/silverpiece");
    add_commodity("ironpiece"    , "/d/Krynn/solamn/thief/obj/ironpiece");
    add_commodity("carbonpiece"  , "/d/Krynn/solamn/thief/obj/carbonpiece");

    add_commodity("mw platemail"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_armour");
    add_commodity("mw chainmail"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_chainmail");
    add_commodity("mw lbreastplate"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_leather");
    add_commodity("mw tunic"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_tunic");
    add_commodity("mw helm"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_std_helm");
    add_commodity("mw chain hood"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_hood");
    add_commodity("mw coif"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_coif");
    add_commodity("mw shield"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_shield");
    add_commodity("mw buckler"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_buckler");
    add_commodity("mw pgauntlet"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_gauntlets");
    add_commodity("mw cgloves"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_cgloves");
    add_commodity("mw lgloves"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_lgloves");
    add_commodity("mw pgreaves"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_leggings");
    add_commodity("mw cleggings"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_cleggings");
    add_commodity("mw lleggings"  , 
        "/d/Krynn/common/warfare/rewards/armours/masterwork_warfare_lleggings");

    add_commodity("mw 1hspear"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_1hspear");
    add_commodity("mw 2hspear"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_2hspear");
    add_commodity("mw axe"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_axe");
    add_commodity("mw dagger"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_dagger");
    add_commodity("mw greataxe"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_greataxe");
    add_commodity("mw greatsword"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_greatsword");
    add_commodity("mw hoopak"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_hoopak");
    add_commodity("mw longsword"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_longsword");
    add_commodity("mw mace"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_mace");
    add_commodity("mw staff"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_staff");
    add_commodity("mw warhammer"  , 
        "/d/Krynn/common/warfare/rewards/weapons/masterwork_warfare_warhammer");

    add_commodity("mw bow"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_bow");

    add_commodity("mw wand"  , 
        "/d/Krynn/common/warfare/rewards/masterwork_warfare_wand");

    add_commodity("steel coin"  , 
        "/d/Krynn/common/warfare/rewards/krynn_steel_coin");
}

public mapping
query_potion_map()
{
    if (!mappingp(Potion_Ingr))
    Potion_Ingr = KRYNN_POTION_INGREDIENTS;
    return Potion_Ingr;
}

/*
 * Function name: armageddon
 * Description:   This function is called when the game is about
 *                to reboot. All it should do is to save certain
 *                objectdata. Nothing more and nothing less.
 * Arguments    : int level - the activity of armageddon.
 */
public void
armageddon(int level)
{
    if (level == ARMAGEDDON_SHUTDOWN)
    {
        CLOCK->save_clock();
        ARMYMASTER->save();
    }
}

string *
query_gem_list()
{
    return map(get_dir("/d/Genesis/gems/obj/krynn/"), 
        &operator(+)("/d/Genesis/gems/obj/krynn/", ));
}
