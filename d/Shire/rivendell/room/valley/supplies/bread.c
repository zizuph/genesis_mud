/* Bread for Imlandris Inn 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name(({"slice of bread", "slice", "bread"}));
    set_pname("slices of bread");
    set_short("slice of bread");
    set_pshort("slice of breads");
    set_long("This is a delicious slice of freshly " +
           "baked wheat bread.\n"); 
    /* Baked in the great forge? */
    set_amount(50);
}
