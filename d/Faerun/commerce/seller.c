/*
 * Commerce NPC who sells swords
 */

inherit "/std/monster";
inherit "/d/Genesis/lib/commerce";

void
create_monster()
{
    set_name("mip");
    set_short("sword seller");
    set_long("He is a humble sword seller.\n");

    config_default_trade();

    add_supplied_commodity("big_nasty_sword", 30, 50, 0.5);
    add_supplied_commodity("large_knife", 10, 50, 0.5);

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
