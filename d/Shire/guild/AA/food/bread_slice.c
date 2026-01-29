/* 
 * Food for XXX
 * Finwe, XXX
 */

inherit "/std/food";

void
create_food()
{
    add_name("bread");
    set_name("slice");
    set_short("slice of bread");
    set_pshort("slices of bread");
    set_adj(({"wheat"}));
    set_long("This is a slice of wheat bread. It is thick and a little " +
        "stale, but still a hearty snack.\n");
    set_amount(50);
}
