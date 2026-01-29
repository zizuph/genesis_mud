/* Mutton for the Meade and Mutton Inn 
 * Created By Leia
 * 9/13/2005
 */

inherit "/std/food";

void
create_food()
{
    set_name("steak");
    set_pname("steaks");
    set_short("leg of juicy mutton");
    set_pshort("legs of juicy mutton");
    set_adj(({"leg of", "legs of", "juicy"}));
    set_long("This is a hot, roasted leg of juicy mutton. The smell alone is enough to drive you wild over this tasty treat.\n");
    set_amount(300);
}
