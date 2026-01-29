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
    set_name("wrath of the gods");
    add_name("wrath");
    set_pname("wraths");
    set_adj("");
    set_short("wrath of the gods");
    set_pshort("wraths of the gods");
    set_long("This local specialty looks and smells like mixed fruit juices, " +
      "if one then poured in enough double-distilled brandy to make it " +
      "flammable.  You suspect it must be popular among the dwarves.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(140);
    set_alco_amount(50);
    add_prop(OBJ_I_WEIGHT, 140);
    add_prop(OBJ_I_VOLUME, 140);
}                                  
