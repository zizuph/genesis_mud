/* Food for Longbottom
 * Finwe, December 2019
 */

inherit "/std/food";

void
create_food()
{
    set_name(({"bread"}));
    set_pname(({"breads"}));
    set_short("buttered bread");
    set_pshort("buttered breads");
    set_adj(({"hot"}));
    set_long("This is a thick slice of bread. It is covered with bread " +
        "and looks tasty.\n");
    set_amount(75);
}
