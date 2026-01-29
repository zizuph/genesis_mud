/*
 * pkey.c
 * By Skippern
 */
#pragma save_binary

inherit "/std/key";

create_key()
{
    ::create_key();
    set_long("This " + short() + " might fit in a lock somewhere.\n");
    set_adj("old rusty");
    set_pshort("old rusty keys");
    set_key("ErechTunnelTreasury");
}
