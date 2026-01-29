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

#pragma save_binary
#pragma strict_types

inherit "/std/drink"; 

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_drink()
{
    set_name("red ale");
    add_name("ale");
    set_pname("red ales");
    set_adj("delicious");
    set_short("red ale");
    set_pshort("red ales");
    set_long("A deep red-brown ale, which smells like it was made with plenty " +
      "of high quality hops.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(200);
    set_alco_amount(7);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}                                  
