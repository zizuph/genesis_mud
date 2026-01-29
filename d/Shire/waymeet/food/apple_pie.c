/* Pie for the hobbit kitchen.
 * Raymundo, Jan 2020
 */

inherit "/std/food";

void
create_food()
{
    set_name("pie");
    set_pname("pies");
    set_short("fresh-made apple pie");
    set_pshort("fresh-made apple pies");
    set_adj("fresh-made");
    set_adj("apple");
    add_adj("delicious");
    add_adj("hobbit-made");
    set_long("A large apple pie made by hobbits, the pie looks almost "
		+ "perfect. It has a golden brown crust with little slats on the "
		+ "top.\n");
		
    add_item("crust", "It's golden brown and flaky!\n");
    add_item( ({"slat", "slats"}), "The slats have been cut in the shape "
		+ "of an apple.\n");
    set_amount(100);
}
