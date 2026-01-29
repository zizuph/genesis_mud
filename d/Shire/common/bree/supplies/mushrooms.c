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
    add_name("mushrooms");
    set_name("steamed mushrooms");
    set_short("basket of steamed mushrooms");
    set_pshort("baskets of steamed mushrooms");
    set_adj(({"steaming", "fresh"}));
    set_long("This is a basket of steamed mushrooms. The mushrooms " +
        "are large and a golden color. They are coated with some spices.\n");
    set_amount(200);
}
