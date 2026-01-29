
/* 
 * Indoors base file for Gulfport in Ergoth
 * Copytweaked from the Haven version
 * Tibbit, 30 April 1998
 *
 */

#include "../local.h"

inherit IN;

public void
reset_gulfport()
{

}

public void
reset_gulfport_room()
{
    reset_gulfport();
}

public void
create_gulfport()
{

}

nomask void
create_gulfport_room()
{
    
    INSIDE;
    
    seteuid(getuid(TO));
    
    create_gulfport();
    reset_room();

}

