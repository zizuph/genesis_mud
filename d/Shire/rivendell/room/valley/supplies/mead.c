/* Mead for Imlandris Inn 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("mead");
        set_pname("mead");
        set_short("fresh golden mead");
        set_pshort("fresh golden meads");
        set_adj(({"fresh", "golden"}));
        set_long("The mead is cool and refreshing, with " +
            "distinctive flowery scent.\n");
        set_soft_amount(110);
        set_alco_amount(4);
}
