/* Platter for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/food";

void
create_food()
{
    set_name("platter");
    set_pname("platters");
    set_short("gigantic meat platter");
    set_pshort("gigantic meat platters");
	set_adj(({"gigantic", "meat"}));
    set_long("A feast in a bag, meant for travellers.\n");
    set_amount(350);
 }
