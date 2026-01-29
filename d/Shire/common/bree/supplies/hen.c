/* Sauteed Potatoes
 * Finwe, September 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("hen");
    set_short("game hen");
    set_pname("game hens");
    set_adj(({"roasted", "game"}));
    set_long("This is a whole game hen. It has been slow cooked " +
        "and looks juicy. It's a golden color and looks appetizing. " +
        "It is coated with rich herbs.\n");
    set_amount(300);
}
