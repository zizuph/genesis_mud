/* Wine for Shire Inns
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("wine");
        add_name("glass");
        set_pname("wines");
        add_pname("glasses");
        set_short("glass of red wine");
        set_pshort("glasses of red wine");
        set_long("You guess it's a Westfarthing from '76.\n");
        set_soft_amount(90);
        set_alco_amount(25);
}
