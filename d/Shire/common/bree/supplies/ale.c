/* Ale for Dancing(?) Pony Inn 
 * Taveren, January 2001
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("ale");
        add_name("pint");
        add_name("pint of ale");
        set_pname("ales");
        add_pname("pints");
        add_pname("pints of ale");
        set_short("pint of ale");
        set_pshort("pints of ale");
        set_long("Yup. It's a pint of ale... and it's all yours.\n");
        set_soft_amount(100);
        set_alco_amount(14);
        
}
