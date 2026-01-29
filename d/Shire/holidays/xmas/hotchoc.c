/* Christmas drink for Bree
 * Finwe, Dec 2002
 */

inherit "/std/drink";

void
create_drink()
{
    set_name("hot chocolate");
    add_name("mug of hot chocolate");
    set_pname("hot chocolates");
    add_pname("mugs of hot chocolates");
    set_short("mug of hot chocolate");
    set_pshort("mugs of hot chocolate");
    set_long("This is a mug of hot chocolate. It is made from chocolate " +
        "that has been stirred into hot milk. The drink is rich and " +
        "creamy.\n");

    set_soft_amount(90);
}
