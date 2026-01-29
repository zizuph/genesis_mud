/* Mortis 9.2014
 */

#include "../../local.h"
#include CLOCKH

inherit TOA_ROOMBASE;

string
query_to_jail()
{
    return "north";
}

void
reset_palan_room()
{
}

void
create_palan_room()
{
    SHORT("An officer's bedroom on the ground floor of the Tower of Arms");
    LONG("This room is little more than an alcove with a cot sandwiched "
    + "between smooth marble walls.\n");

    ITEM(({"alcove", "cot"}), "The alcove is large enough for a simple cot. "
    + "The cot looks old and worn.\n");

    EXIT(TOA + "toa_lieutenant01", "north", 0, 0);

    reset_palan_room();
}
