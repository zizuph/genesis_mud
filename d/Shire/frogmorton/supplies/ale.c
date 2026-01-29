/* Ale for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("pint of fresh ale", 1);
        add_pname("pints of fresh ale");
        //set_name("ale");
        add_name("ale");
        add_name("pint");
        //add_name("fresh ale");
        //add_name("pint of fresh ale");
        //set_pname("ales");
        //add_pname("pints");
        //add_pname("fresh ales");
        //add_pname("pints of fresh ale");
        //set_adj(({"pint", "mug"}));
        set_adj(({"pint", "fresh"}));
        set_short("pint of fresh ale");
        set_pshort("pints of fresh ale");
        set_long("The pint of fresh ale looks rich and " +
           "delicious.\n");
        set_soft_amount(100);
        set_alco_amount(14);
        
}     
