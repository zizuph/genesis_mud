/*
 * Commerce NPC who buys swords
 */

inherit "/std/monster";
inherit "/d/Genesis/lib/commerce";

void
create_monster()
{
    set_name("mike");
    set_short("sword collector");
    set_long("He is a humble sword collector.\n");

    config_default_trade();

    add_demanded_commodity("big_nasty_sword", 1, 50, 1.5);
    add_demanded_commodity("large_knife", 1, 50, 1.5);

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
