/* Nectar for Imlandris Inn 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name(({"nectar", "pint", "pint of nectar"}));
        set_pname(({"pints", "pints of nectar"}));
        set_short("pint of nectar");
        set_pshort("pints of nectar");
        set_long("The pint of nectar is cold and looks good.\n");
        set_soft_amount(100);
        set_alco_amount(14);
}        
