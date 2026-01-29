 /* Maniac 27/3/95 
    This room contains the statue that blocks enemies of Calia from 
    proceeding to the palace. 
    Charming of statue added for kroug raids, Maniac, 28/9/95
 */
 /* Slip code by Overlord */
 /* Modified, Maniac 19/9/95 */

inherit "/d/Calia/std/std_plateau";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

int charmed;
object hurn;

void
reset_room()
{
    if (!objectp(hurn)) { 
        hurn = clone_object(MOUNTAIN_MONSTERS + "hurn"); 
        hurn->move_living("onto the plateau", this_object()); 
    } 
}

void
create_room()
{
    make_the_room("\n", 3);
    add_exit(CROAD+"croad27","north");
    add_exit(CROAD+"croad25","south", "@@slip");
    reset_room();
    charmed = 0;
}

void
kroug_raid_charm_statue()
{
    if (charmed) 
        return;

    charmed = 1;
    tell_room(this_object(), "Kroug appears, casts a charm spell on the " +
                             "statue, gives an evil grin, then vanishes.\n");
}

