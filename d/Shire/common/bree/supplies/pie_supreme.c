/* Supreme Lover's Pizza, aka meat and vegetable pie
 * Coded while after the game crashed Sept 8, 2001
 * I mean, I had to do something since Genesis
 * wasn't up...
 * Finwe, September 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("pie");
    add_name("meat and vegetable pie");
    set_short("meat and vegetable pie");
    set_adj(({"golden-brown", "square"}));
    set_long("This is a meat and vegetable pie. The dough is topped " +
        "with tomato sauce, grated cheeses, spiced meats, bacon, " +
        "ground beef, ham, sliced mushrooms, green peppers, onions, " +
        "and tomatoes. The pie's edges are turned up, forming a " +
        "crust that has been cooked to a delicious golden-brown color.\n");
    set_amount(350);
}
