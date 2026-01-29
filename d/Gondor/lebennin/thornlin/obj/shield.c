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
public void alter_w_v();

public void
create_armour()
{
    set_name("shield");
    set_pname("shields");
    set_adj("large");
    set_adj("light");
    set_short("large light shield");
    set_pshort("large light shields");
    set_long("This shield is quite extraordinary.  It is so large that, from " +
      "the front you'd think it'd weigh a ton!  On closer inspection, you " +
      "find that it is very light steel except for the rim, covered with " +
      "hardened leather and supported by a finely carved hardwood frame.  " +
      "It may not protect any of you totally, but it should help to protect " +
      "all of you.  It looks like it was made for a right-handed person.  " +
      "It bears the emblem of Lossarnach.\n");
    set_at(A_SHIELD);
    set_keep(1);
    set_alarm(0.1, 0.0, &alter_w_v());
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30) + 100 + (random(100)));
    /* Intentionally overpriced to compensate for slots covered */
    set_ac(25 + (random(3)));

}
public void
alter_w_v()
{
    add_prop(OBJ_I_WEIGHT, 3200 + (random(100)));
    add_prop(OBJ_I_VOLUME, 2000 + (random(200)));
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS, A_HEAD, A_R_ARM }) );
}    

varargs int
query_ac(int hid)
{
    if (hid & A_R_ARM)
	return (::query_ac(hid) - 18);
    if (hid & A_HEAD)
	return (::query_ac(hid) - 3);
    if (hid & A_LEGS)
	return (::query_ac(hid) - 2);
    if (hid & A_BODY)
	return (::query_ac(hid) -1);
    return ::query_ac(hid);

}  
