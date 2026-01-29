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
    set_name("bread and cheese");
    add_name("bread");
    add_name("cheese");
    set_adj("");
    set_short("bread and cheese");
    set_pshort("plates of bread and cheese");
    set_long(
      "Half a loaf of bread and a quarter of a wax-dipped cheese.  "
      + "Simple fare, but enough to keep you on your feet for a few hours.\n");
    set_amount(70);
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,300);
}                           
