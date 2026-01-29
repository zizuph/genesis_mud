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
    set_name("roll");
    set_adj("wheat");
    set_short("wheat roll");
    set_pshort("wheat rolls");
    set_long(
      "This roll is small, but fresh and made from wheat flour instead of "
      + "a cheaper grain like rye.  Butter has been baked into its top.\n");
    set_amount(10);
    add_prop(OBJ_I_WEIGHT,35);
    add_prop(OBJ_I_VOLUME,45);
}                           
