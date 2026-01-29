/* Salad for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/01 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
    //set_name("vegetable");
    set_name("salad");
    //add_name("salad");
    set_adj("vegetable");
    //set_pname("vegetable");
    //add_pname("salads");
    //set_short("vegetable salad");
    //set_pshort("vegetable salads");
    //set_adj("vegetable");
    set_long("It is a mixture of lettuce, carrots, " +
//     "purple cabbage, and cucumbers sliced and tossed together.\n");
     "purple cabbage, and cucumber, sliced and tossed together.\n");
    set_amount(150);
    
}    
