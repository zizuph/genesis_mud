/*
 * Wine on level 2
 * Boreaulam, Nov 2012
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("wine");
        set_pname("wines");
        set_short("red wine");
        set_pshort("red wines");
        set_adj("red");
        set_long("This is a small glass of rich red wine.\n");
        set_soft_amount(50);
        set_alco_amount(12);
}
