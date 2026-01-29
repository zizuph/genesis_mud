/*
 * Beer on level 2
 * Boreaulam, Nov 2012
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("beer");
        set_pname("beers");
        set_short("dark beer");
        set_pshort("dark beers");
        set_adj("dark");
        set_long("This is a glass of rich dark beer, brewed by the goblins " +
            "who inhabit the caves near Sparkle.\n");
        set_soft_amount(100);
        set_alco_amount(4);
}
