/* Soup for Shire Inns 
 * Taveren, January 2001
 *
 * 2001/01/26 Last update, but was unused
 * 2011/08/05 Lavellan - Now in use. Fixed up a little.
 */

inherit "/std/food";

void
create_food()
{
    set_name("soup");
    //set_pname("soups");
    //set_short("vegetable soup");
    //set_pshort("vegetable soups");
    set_adj("vegetable");
    set_long("This soup is made of carrots, onions, "+
//        "cabbage, potatoes and celery. The vegetable are in a " +
        "cabbage, potatoes and celery. The vegetables are in a " +
         "rich broth of seasonings.\n");
    set_amount(190);
    
}
    