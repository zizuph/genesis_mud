// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w4.c
// creator(s):       Cirion, July 1996
// revisions:        Lilith, June 2004: made plalgus curse more mild, but
//                   don't want to encourage recidivism, so blocking
//                   mass murderers entirely. The Union will find 
//                   them, I'm sure. Jun 4, 2004.
//                   Casca, 11/13/99
// purpose:          
// note:             
// bug(s):           
// to-do:            

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  
#include "/d/Avenir/include/relation.h"


/*
 * Function name: check_exit
 * Description:   Block recidivists from entering Sybarus. 
 *                We could do the old throw up a gate and pour boiling
 *                oil trick on them, like in Calathin...but for reasons
 *                of ambiance, the land will simply resist them.
 *                Anyone that tests as an infidel greater than ten 
 *                (killed > 10 citizens) is a mass murderer and so the 
 *                land is closed to them.
 * Returns:       1/0 - closed/open
 */
public int
check_exit()
{
    /* No accidents here, this person has killed > 10 citizens. 
     * They are looking for trouble, lets make sure they don't
     * find it where they expect to.
     */
/* Outcommented by Mercade.
 *  if (IS_INFIDEL(TP) > 10)
    {
        write("There is no obvious exit northwest.\n");
        return 1;
    }
 */

    /* Warn them they are wearing out their welcome */
    if (IS_INFIDEL(TP))
        write("A feeling of uneasiness weighs upon you, making you "+
            "feel unwelcome.\n");
    
    /* S/he may pass */
    return 0;
}
/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("smooth tunnel");
    set_long("A long, smooth tunnel stretches out to the northwest, "+
        "its rock sides finely chiseled. To the southeast, a "+
        "large onyx archway opens up into a large cavern.\nThe "+
        "silence here is complete.\n");

    add_exit("ut2","northwest", check_exit, 1, 1);
    add_exit("w8","southeast");

    /*
     * Put additional add_items below. 
     */

    add_w_tunnel();

    add_item(({"arch","archway"}),"It is smooth and made from some "
      +"black, onyx-like stone. It hase graceful, sweeping curves "
      +"that meet overhead in a slightly pointing apex.\n");
    add_item(({"cave","cavern"}),"It lies to the southeast.\n");

    reset_tunnel_room();
}
