/*
*Shaman Tent Base
*Created by Leia
*05/03/2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"

inherit R_FILE

#define CREATE2 "create_shaman_room"
#define RESET2  "reset_shaman_room"

nomask public int
query_reset()
{
    if (function_exists(RESET2, TO))
        return 1;
    return 0;
}

void
create_shaman_room()
{
}

nomask public void
create_krynn_room()
{
    create_shaman_room();
}

nomask public void
reset_krynn_room()
{
    call_other(TO, RESET2);
}