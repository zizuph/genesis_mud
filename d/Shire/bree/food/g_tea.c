/* Coffee for the Prancing Pony Inn
 * Finwe, January 2002
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("tea");
        set_short("green tea");
        set_pname("green teas");
        set_pshort("green teas");
        set_long("This is a steamimg cup of green tea. It's made " +
            "from dried unfermented leaves and is a slight green " +
            "in color. It has a slight fruity fragrance.\n");
        set_soft_amount(100);
}
