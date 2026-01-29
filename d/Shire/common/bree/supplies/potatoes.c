/* Sauteed Potatoes
 * Finwe, September 2001
 */

inherit "/std/food";

void
create_food()
{
    add_name("potatoes");
    set_name("sauteed potatoes");
    set_short("bowl of sauteed potatoes");
    set_pshort("bowls of sauteed potatoes");
    set_adj(({"steaming", "fresh"}));
    set_long("This is a bowl of sauteed potatoes. They have been " +
        "cut into chunks and sauteed in butter. A rich, creamy " +
        "herb sauce has been poured over the potatoes.\n");
    set_amount(150);
}
