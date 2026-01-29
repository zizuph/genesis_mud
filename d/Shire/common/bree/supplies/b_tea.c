/* Coffee for the Prancing Pony Inn
 * Finwe, January 2002
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("tea");
        set_short("black tea");
        set_pname("black teas");
        set_pshort("black teas");
        set_long("This is a steamimg cup of black tea. It's made " +
            "of fermented leaves and has a black color. The tea " +
            "has a dark fragrance.\n");
        set_soft_amount(100);
}
