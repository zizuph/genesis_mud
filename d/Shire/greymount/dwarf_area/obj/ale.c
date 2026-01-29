/* Ale for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("ale");
        add_name("pint of ale");
        set_pname("ales");
        set_short("pint of ale");
        set_pshort("pints of ale");
		set_adj(({"pint of", "pints of"}));
        set_long("This is a pint of ale. It's not very big, but it's good for the weak stomached.\n");
        set_soft_amount(100);
        set_alco_amount(14);
        
}
