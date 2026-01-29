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
    set_name("red wine");
    add_name("wine");
    set_pname("wines");
    set_adj("red");
    set_short("red wine");
    set_pshort("red wines");
    set_long("A light red wine intended for immediate consumption.  It has " +
      "little scent, since it is a very young wine -- perhaps you should " +
      "taste a bit?\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(160);
    set_alco_amount(12);
    add_prop(OBJ_I_WEIGHT, 160);
    add_prop(OBJ_I_VOLUME, 160);
}                                  
