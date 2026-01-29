/* Vegetable for Waymeet field
 * Finwe, March 2019
 * Stolen for an apple
 * Raymundo, Jan 2020
 */

inherit "/std/food";

void
create_food()
{
   set_name("apple");
   
   set_short("juicy red apple");
   
   set_adj("juicy");
   add_adj("red");
   set_long("This is a juicy red apple, picked straight from the tree. "
	+ "Yum.\n");
   set_amount(130);
}
