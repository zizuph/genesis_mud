/* Ale for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("ale");
        add_name("glass");
        add_name("tall glass");
        set_pname("ales");
        add_pname("glasses");
        add_pname("tall glasses");
        set_adj("glass");
        set_short("tall glass of ale");
        set_pshort("glasses of ale");
        set_long("The tall glass of ale looks inviting.\n");
        set_soft_amount(100);
        set_alco_amount(14);
        
}
