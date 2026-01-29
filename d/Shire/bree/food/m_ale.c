/* Mulled ale for Prancing Pony
 * Finwe, January 2002
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("ale");
        add_name("mulled");
        add_name("mulled ale");
        set_pname("ales");
        add_pname("mulled ales");
        set_short("mulled ale");
        set_pshort("mulled ales");
        set_long("It's a mug of ale that has been warmed until " +
            "it's steaming. The ale is a golden color and very " +
            "refreshing looking.\n");
        set_soft_amount(100);
        set_alco_amount(14);
        
}
