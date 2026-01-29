/* Liquor for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("liquor");
        set_pname("liquors");
        set_short("prime liquor");
        set_pshort("prime liquors");
        set_adj("prime");
        set_long("Don't drink this unless you are a real boozer.\n");
        set_soft_amount(50);
        set_alco_amount(30);
}
