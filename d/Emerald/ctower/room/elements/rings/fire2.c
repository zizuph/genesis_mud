#include "../../../ctower.h"

inherit FIRESTD;
 
void
create_fire()
{
    add_exit("fire1", "south");
}
 
int
query_transform()
{
    return 1;
}
