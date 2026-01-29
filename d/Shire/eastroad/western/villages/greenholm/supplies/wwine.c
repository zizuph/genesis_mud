/* Wine for Shire Inns
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("wine");
        add_name("white wine");
        add_name("glass");
        set_pname("wines");
        add_pname("white wines");
        add_pname("glasses");
        set_short("glass of white wine");
        set_pshort("glasses of white wine");
	set_adj("glass");
        set_long("This white wine has a touch of yellow to it,, "+
                 "and not completely white.\n");
        set_soft_amount(90);
	set_alco_amount(18);
}
