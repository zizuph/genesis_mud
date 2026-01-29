/*
 * This code is copyright (c) 2000 by Scott A. Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott Hardy has seen the 1991 document of Genesis' called 'legal',
 * and he does not forfeit any of his intellectual property rights
 * as that document supposes he would.  He is the sole and
 * complete owner of this code, which as of Jan. 2001 he is 
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of his code, Genesis acknowledges and agrees
 * to all of the above.
 */

inherit "/std/armour";
inherit "/lib/keep";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
public void alter_w_v();

public void
create_armour()
{
    set_name("gauntlets");
    set_pname("pairs of gauntlets");
    set_adj("sturdy");
    set_adj("steel");
    set_short("sturdy steel gauntlets");
    set_pshort("pairs of sturdy gauntlets");
    set_long("These gauntlets are unlike most you see around, they come " +
      "in an unmatched set, and bear the emblem of the Thornlin Militia.  " +
      "They seem like they would be good for use with a weapon and a shield, " +
      "since one doesn't really benefit much from a heavy vambrace under a " +
      "shield.  Hopefully you are right-handed, since the right gauntlet " +
      "is of thick and well-crafted high steel, but the left is of fine " +
      "chainmail mesh over soft leather.\n");
    set_at(A_ARMS | A_HANDS);
    set_keep(1);
    set_alarm(0.1, 0.0, &alter_w_v());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) +  (random(100)));
    /* Pricing is for avg. of left and right arm */
    set_ac(34 + (random(2)));

}
public void
alter_w_v()
{
    add_prop(OBJ_I_WEIGHT, 600 + (random(100)));
    add_prop(OBJ_I_VOLUME, 450 + (random(20)));
}

varargs int
query_ac(int hid)
{
    if (hid & A_HANDS)
	return (::query_ac(hid) - 26);
    if (hid & A_L_ARM)
	return (::query_ac(hid) - 10);
    return ::query_ac(hid);

}     

