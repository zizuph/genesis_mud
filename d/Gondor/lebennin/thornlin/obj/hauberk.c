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
    set_name("hauberk");
    set_pname("hauberks");
    set_adj("light");
    set_adj("padded");
    set_short("light padded hauberk");
    set_pshort("light padded hauberks");
    set_long("This is a hauberk which covers the shoulders, torso and upper " +
      "legs.  It is thick, studded leather on the outside, thin soft leather " +
      "on the inside, and some sort of padding in between.  The torso area " +
      "seems to have thicked padding, and has plates of very thin spring " +
      "steel between the outer leather and the padding.  Embossed into " +
      "the leather is the emblem of Lossarnach.\n");
    set_at(A_TORSO | A_LEGS);
    set_keep(1);
    set_alarm(0.1, 0.0, &alter_w_v());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(24) + 100 + (random(100)));
    /* Intentionally overpriced */
    set_ac(21 + (random(2)));

}
public void
alter_w_v()
{
    add_prop(OBJ_I_WEIGHT, 2900 + (random(100)));
    add_prop(OBJ_I_VOLUME, 3500 + (random(200)));
}

varargs int
query_ac(int hid)
{
    if (hid & A_LEGS)
	return (::query_ac(hid) - 4);
    return ::query_ac(hid);

}     

