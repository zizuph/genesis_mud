/* Christmas drink for Bree
 * Finwe, Dec 2002
 */

inherit "/std/drink";

void
create_drink()
{
    set_name("eggnog");
    add_name("rich eggnog");
    add_name("mug of eggnog");
    add_name("mug of rich eggnog");
    set_pname("eggnogs");
    add_pname("mugs of rich eggnog");
    add_pname("mugs of eggnog");
    set_short("mug of rich eggnog");
    set_pshort("mugs of rich eggnog");
    set_long("This is a mug of rich eggnog. It is made of rich cream " +
        "and eggs whipped together and sweetened with sugar. Vanilla, " +
        "cinnamon, and nutmeg have added, with rum stirred in to give " +
        "it the traditional taste.\n");

    set_soft_amount(90);
    set_alco_amount(20);
}
