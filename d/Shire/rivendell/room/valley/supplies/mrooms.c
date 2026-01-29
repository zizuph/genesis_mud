/* Mushrooms for Imlandris Inn 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
   set_name("basket of steamed mushrooms");
   add_name("mushrooms");
   add_name("steamed mushrooms");
   add_name("basket");
   set_pname("baskets of steamed mushrooms");
   set_short("basket of steamed mushrooms");
   set_pshort("baskets of steamed mushrooms");
   set_adj(({"large", "steamed"}));
   set_long("A large basket full of large steamed " +
    "mushrooms, they are the best you've ever seen. Most " +
    "likely the mushrooms come from somewhere in the Shire. \n");
   set_amount(200);
}
