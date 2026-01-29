/* Cheese for Imlandris Inn 
 * Taveren, January 2001
 */

inherit "/std/food";

void
create_food()
{
    set_name("brick of cheese");
    add_name("cheese");
    add_name("brick");
    set_pname("bricks of cheese");
    set_short("brick of cheese");
    set_pshort("bricks of cheese");
    set_adj("small");
    set_long("The brick of cheese is white with " +
          "flecks of orange in it.\n");
    set_amount(130);
}
