/* Christmas drink for Bree
 * Finwe, Dec 2002
 */

inherit "/std/drink";

void
create_drink()
{
    set_name("cider");
    add_name("spiced cider");
    add_name("mug of spiced cider");
    set_pname("ciders");
    add_pname("spiced ciders");
    add_pname("mug of spiced ciders");
    set_short("mug of spiced cider");
    set_pshort("mugs of spiced cider");
    set_long("This is a mug of hot spiced cider made from freshly " +
        "pressed apples. Whole cloves and cinammon have been added, " +
        "and the cider warmed until it's steaming hot.\n");

    set_soft_amount(90);

}
