/* Soup for Shire Inns 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("soup");
    set_pname("soups");
    set_short("vegetable soup");
    set_pshort("vegetable soups");
    set_adj("vegetable");
    set_long("This soup is made of carrots, onions, "+
      "cabbage, potatoes and celery.\n");
    set_amount(190);
    
}

