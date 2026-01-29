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
    set_name("lobster dinner");
    add_name("lobster");
    add_name("dinner");
    set_adj("");
    set_short("4-course lobster dinner");
    set_pshort("4-course lobster dinners");
    set_long(
      "A dinner consisting of a large steamed lobster, melted butter, "
      + "a green salad, sauteed mushrooms, and a small loaf of bread.\n");
    set_amount(400);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,550);
}                           
