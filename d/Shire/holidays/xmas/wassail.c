/* Christmas drink for Bree
 * Finwe, Dec 2002
 */

inherit "/std/drink";

void
create_drink()
{
    set_name("wassail");
    add_name("mug of wassail");
    set_pname("wassails");
    add_pname("mugs of wassail");
    set_short("mug of wassail");
    set_pshort("mugs of wassail");
    set_long("This is a mug of wassail, a traditional holiday drink. " +
        "It is made from fermented apples, with allspice, mace, nutmeg, " +
        "and cinnamon added. The drink is rather strong, so it's " +
        "recommended for the hardy drinkers.\n");

    set_soft_amount(120);
    set_alco_amount(75);

}
