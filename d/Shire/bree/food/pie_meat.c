/* Meat Lovers Pizza, aka meat filled pie
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
    set_name("meat pie");
    set_pname("meat pies");
    set_short("meat pie");
    set_adj(({"golden-brown", "square"}));
    set_long("This is a meat filled pie. The dough is topped with tomato " +
        "sauce, grated cheeses, sliced hams, spiced meats, ground " +
        "beef, and bacon. The pie's edges are turned up, forming " +
        "a crust, and has been cooked to a delicious golden-brown " +
        "color.\n");
    set_amount(300);
}
