/* Chicken for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("chicken");
    set_pname("chickens");
    set_short("roast chicken");
    set_pshort("roast chickens");
    set_adj("whole");
    add_adj("roast");
    set_long("This whole roast chicken "+
      "is sizzling hot and golden-brown. Yum!\n");
    set_amount(575);
    
}  
