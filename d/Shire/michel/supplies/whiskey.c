/* Whiskey for Shire Inns
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("whiskey");
        set_pname("whiskeys");
        set_short("stout whiskey");
        set_pshort("stout whiskeys");
        set_adj("stout");
        set_long("The smell of this powerful whiskey nearly "+
             "knocks you down.\n");        
        set_soft_amount(50);
        set_alco_amount(30);
}     

