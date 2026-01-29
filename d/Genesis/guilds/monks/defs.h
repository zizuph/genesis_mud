/* General definitions for the Monks
 * Cirion April 14 1998
 */

#include "monk.h"

#include <macros.h>
#include <stdproperties.h>

#define TP this_player()
#define TO this_object()
#define NF(x) notify_fail(x)

// MONK_ERROR is mostly for debugging. E.g.,
// MONK_ERROR(TP, "The soul did not load properly!\n", "Something went
//      wrong...\n");
#define MONK_ERROR(x, y, z)            \
            (((x)->query_wiz_level() || wildmatch("*jr", (x)->query_real_name())) ? \
            (x)->catch_tell(y) : (x)->catch_tell(z))

// ONEOF gives a random element of the array x
#define ONEOF(x)  x[random(sizeof(x))]

