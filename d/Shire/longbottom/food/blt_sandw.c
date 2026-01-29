/* Food for Longbottom
 * Finwe, December 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name(({"sandwich"}));
    set_pname(({"sandwiches"}));
    set_short("blt sandwich");
    set_pshort("blt sandwiches");
    set_adj(({"fresh", "tasty"}));
    set_long("This is a bacon, lettuce, and tomato sandwich. It is " +
        "made with two pieces of toasted bread.\n");
    set_amount(200);
}
