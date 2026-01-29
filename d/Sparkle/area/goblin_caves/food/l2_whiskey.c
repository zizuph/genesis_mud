/*
 * Whiskey on level 2
 * Boreaulam, Nov 2012
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("whiskey");
        set_pname("whiskeys");
        set_short("strong whiskey");
        set_pshort("strong whiskeys");
        set_adj("strong");
        set_long("This is a shot of strong whiskey.\n");
        set_soft_amount(30);
        set_alco_amount(40);
}
