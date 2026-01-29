/* Christmas drink for Bree
 * Finwe, Dec 2002
 */

inherit "/std/drink";

void
create_drink()
{
    set_name("wine");
    add_name("mulled wine");
    add_name("mug of mulled wine");
    set_pname("wines");
    add_pname("mulled wines");
    add_pname("mugs of mulled wine");
    set_short("mug of mulled wine");
    set_pshort("mugs of mulled wine");
    set_long("This is a mug of hot mulled wine. It is dark and " +
        "smells sweet. The scents of ginger, cinnamon, and nutmeg " +
        "waft up from the drink, along with a hint of orange peel.\n");
    set_soft_amount(90);
    set_alco_amount(25);
}
