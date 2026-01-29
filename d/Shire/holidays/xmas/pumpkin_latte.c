/* Christmas drink for Bree
 * Finwe, November 2017
 */

inherit "/std/drink";

void
create_drink()
{
    set_name("pumpkin-spice latte");
    add_name("mug of pumpkin-spice latte");
    add_name("latte");
    add_name("pumpkin latte");
    set_pname("pumpkin-spice lattes");
    add_pname("mugs of pumpkin-spice lattes");
    set_short("mug of pumpkin-spice latte");
    set_pshort("mugs of pumpkin-spice lattes");
    set_long("This is a mug of pumpkin-spice latte. It is made with pumpkin, " +
        "aromatic spices, coffee, and whipped milk. Rich whipped cream " +
        "covers the top, and is dusted with pumpkin spices.\n");

    set_soft_amount(90);
}
