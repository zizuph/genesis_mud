/* Meade for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("meade");
        set_pname("meades");
		set_adj(({"fifth of", "fifths of"}));
        set_short("fifth of meade");
        set_pshort("fifths of meade");
        set_long("This is a hefty fifth of strong meade. This is guaranteed to take the edge off anything.\n");
        set_soft_amount(175);
        set_alco_amount(100);
}
