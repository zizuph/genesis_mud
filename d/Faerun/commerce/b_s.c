/*
 * Commerce NPC who buys and sells swords
 */

inherit "/std/monster";
inherit "/d/Genesis/lib/commerce";

void
create_monster()
{
    set_name("pest");
    set_short("blacksmith");
    set_long("He is a blacksmith.\n");

    config_default_trade();

    add_demanded_commodity("faerun_steel", 15, 100, 0.5);
    add_supplied_commodity("large_knife", 5,  50, 1.0);
    add_supplied_commodity("big_nasty_sword", 15,  50, 1.0);

    add_supply_requirement("big_nasty_sword", ({ "faerun_steel", 2 }));
    add_supply_requirement("large_knife", ({ "faerun_steel", 1 }));

    set_commerce_savefile("/d/Faerun/commerce/big_nasty_sword");
}

void
init_living()
{
    ::init_living();
    init_commerce();
}

string
stat_living()
{
    return ::stat_living() + stat_commerce();
}
