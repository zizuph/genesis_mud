/* Liquor for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/drink";

void
create_drink()
{
        set_name("liquor");
        set_pname("liquors");
        set_short("shot of liquor");
        set_pshort("shots of liquor");
		set_adj(({"shot of", "shots of"}));
        set_long("This is a stiff drink. It isn't for the faint of heart.\n");
        set_soft_amount(50);
        set_alco_amount(30);
}
