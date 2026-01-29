/* Veggie Lovers Pizza, aka vegetable filled pie
 * Coded while after the game crashed Sept 8, 2001
 * I mean, I had to do something since Genesis
 * wasn't up...
 * Finwe, September 2001
 */

inherit "/std/food";

void
create_food()
{
    add_name("pie");
    set_name("vegetable pie");
    set_pname("vegetable pies");
    set_short("vegetable pie");
    set_pshort("vegetable pies");
    set_adj(({"golden-brown", "square"}));
    set_long("This is a vegetable filled pie. The dough is topped " +
        "with tomato sauce, grated cheeses, slice tomatoes, " +
        "mushrooms, and green peppers. The pie's " +
        "edges are turned up, forming a crust, and has been " +
        "cooked to a delicious golden-brown color.\n");
    set_amount(300);
}
