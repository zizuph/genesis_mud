/* Chicken Lover's Pizza, aka chicken filled pie
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
    set_name("chicken pie");
    set_short("chicken pie");
    set_adj(({"golden-brown", "square"}));
    set_long("This is a chicken filled pie. The dough is topped " +
        "with tomato sauce, grated cheeses, tender chunks of " +
        "grilled chicken breast, sliced mushrooms, green peppers, " +
        "and onions. The pie's edges are turned up, forming a " +
        "crust that has been cooked to a delicious golden-brown " +
        "color.\n");
    set_amount(300);
}
