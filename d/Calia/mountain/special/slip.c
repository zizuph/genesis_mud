/* Slip code for the Crystalline road up Mount Kyrus.
   Coded by Overlord.

   History:
            10/5/95    Made less slippery            Maniac
*/

#include <ss_types.h>
#include <macros.h>
#include "/d/Calia/domain.h"

int
slip()
{
    if (!random(20))
    {
        object tp;

        tp = TP;
        if (random(100) < tp->query_stat(SS_DEX))
        {
            write(BS(
                "You almost slipped on the crystalline surface of the road, " +
                "but you deftly righted yourself just in time.  " +
                "\n"));
            return 0;
        }

        write("You slipped on the crystalline surface of the road.\n");
        say(QCNAME(tp) + " slipped on the crystalline surface of the road.\n");
        tp->heal_hp(-1);
        return 1;
    }

    return 0;
}
