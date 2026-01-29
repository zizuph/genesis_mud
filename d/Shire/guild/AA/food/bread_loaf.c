/* 
 * Food for XXX
 * Finwe, XXX
 */

inherit "/std/food";

void
create_food()
{
    add_name("bread");
    set_name("loaf");
    set_short("loaf of bread");
    set_pshort("loaves of bread");
    set_adj(({"wheat"}));
    set_long("This is a loaf of wheat bread. It looks hearty and " +
        "filling.\n");
    set_amount(300);
}
