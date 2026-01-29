/*
 * This code is copyright (c) 2000 by Scott A. Hardy.
 * Genesis is a game currently run through Chalmers University.
 * Scott Hardy has seen the 1991 document of Genesis' called 'legal',
 * and he does not forfeit any of my intellectual property rights
 * as that document supposes he would.  He is the sole and
 * complete owner of this code, which as of Jan. 2001 he is 
 * loaning to Genesis.  Genesis does not own this code, or
 * have any right to transfer it to anyone.  By its ongoing
 * use and storage of my code, Genesis acknowledges and agrees
 * to all of the above.
 */
inherit "/std/food";
#include <stdproperties.h>

void 
create_food() 
{
    set_name("half a chicken");
    add_name("half");
    add_name("chicken");
    add_name("roasted");
    set_adj("roasted");
    set_short("half a roasted chicken");
    set_pshort("halves of roasted chickens");
    set_long("Half of a small chicken, which has been skinned and roasted " +
      "over a fragrantly smoky fire.\n");
    set_amount(150);
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,350);
}                           
