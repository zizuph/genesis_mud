/* Brownies for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/food";

void
create_food()
{
    set_name("brownies");
    set_pname("brownies");
    set_short("short stack of brownies");
    set_pshort("short stacks of brownies");
	set_adj(({"short", "stack of", "stacks of"}));
    set_long("This is a short stack of warm, moist brownies. These brownies must have came straight from the oven.\n");
    set_amount(50);
  
}
