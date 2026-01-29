/*
 * This code is copyright (c) 2000 by Scott A. Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott Hardy has seen the 1991 document of Genesis' called 'legal',
 * and he does not forfeit any of his intellectual property rights
 * as that document supposes he would.  He is the sole and
 * complete owner of this code, which as of Jan. 2001 he is 
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of my code, Genesis acknowledges and agrees
 * to all of the above.
 */

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
alter_w_v()
{
    add_prop(OBJ_I_WEIGHT, 1900 + (random(100)));
    add_prop(OBJ_I_VOLUME, 2350 + (random(180)));
}  

public void
create_armour()
{
    set_name("cloak");
    set_pname("cloaks");
    set_adj("leather");
    set_adj("scalemail");
    set_short("leather scalemail cloak");
    set_pshort("leather scalemail cloaks");
    set_long("This cloak is one of the most unique you've ever seen, " +
      "the part covering the body being made of stiff, boiled leather scales, " +
      "with two large studs of high steel in each scale.  In place of a hood, " +
      "it has a light but well-made skullcap of high steel.  The coat of arms " +
      "of the Thornlin Militia adorns the chest area and middle of the back.\n");
    set_at(A_ROBE | A_HEAD);
    set_keep(1);
    add_prop(OBJ_I_VOLUME, 5000 + (random(200)));
    add_prop(OBJ_I_WEIGHT, 2000 + (random(600)));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(22) + 500 + (random(500)));
    /* Intentionally overpriced */
    set_ac(14 + (random (4)));
    set_alarm(0.1, 0.0, &alter_w_v());
}

varargs int
query_ac(int hid)
{
    if (hid & A_HEAD)
	return (::query_ac(hid) + 17);
    return ::query_ac(hid);

}     

