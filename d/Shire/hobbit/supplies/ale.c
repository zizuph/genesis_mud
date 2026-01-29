/* Ale for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("ale");
        add_name("pint");
        add_name("red ale");
        set_pname("ales");
        add_pname("pints");
        add_pname("red ales");
        set_adj("glass");
        set_short("pint of red ale");
        set_pshort("pints of red ale");
        set_long("The pint of red ale looks inviting.\n");
        set_soft_amount(100);
        set_alco_amount(14);
        
}
