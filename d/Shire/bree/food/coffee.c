/* Coffee for the Prancing Pony Inn
 * Finwe, January 2002
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("coffee");
        set_short("steaming cup of coffee");
        set_pname("steaming cups of coffee");
        set_pshort("steaming cups of coffee");
        set_long("This is a steaming cup of coffee. It's been made " +
            "from a blend of roasted coffee beans and smells " +
            "intoxicating.\n");
        set_soft_amount(100);
}
