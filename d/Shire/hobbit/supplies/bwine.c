/* Wine for Shire Inns
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("wine");
        add_name("glass");
        add_name("brandywine");
        set_pname("wines");
        add_pname("glasses");
        add_pname("brandywines");
        set_short("glass of brandywine");
        set_pshort("glasses of brandywine");
	set_adj("glass");
        set_long("This brandywine is reddish brown in color, "+
         "reflecting its blend of brandy with wine, thus the name.\n");
        set_soft_amount(90);
	set_alco_amount(18);
}
