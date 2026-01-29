/* 
 * Created by Mortis 08.2005
 */

inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("robe");
    set_adj("maroon");
	set_adj("long");
    set_short("long maroon robe");
    set_long("This simple cotton robe has been dyed a dark maroon and hangs "
	+ "down to the feet when worn.  A few cloth belt loops hold its wide, "
	+ "maroon, cloth belt in place.  The belt itself is little more than a "
	+ "length of cloth with border stitching to give it a bit of form.  It "
	+ "is worn knotted in the front.  A small, brown tag has been sewn "
	+ "inside the fold at the back of the neck.  Upon it is stitched a small "
	+ "map of a circular city.\n");
    set_ac(3);
    set_at(A_ROBE);
}
