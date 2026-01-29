/* Whiskey for Shire Inns
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("whiskey");
        set_pname("whiskeys");
        set_short("strong whiskey");
        set_pshort("strong whiskeys");
        set_long("Greenholm is famous for its strong, but foul-tasting "+
                     "whiskey.\n");
        set_soft_amount(50);
        set_alco_amount(30);
        set_adj("strong");
}        
 
