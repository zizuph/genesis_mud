/* Indoors base file for Haven.
 * By Aridor, Feb 98
 *
 *
 * Modifications:
 * Descriptions modified to be haven-town specific, Tibbit,
 *     17 Feb 1998
 */

#include "../local.h"

inherit IN;

public void
reset_haven()
{

}

public void
reset_haven_room()
{
    reset_haven();
}

public void
create_haven()
{

}

nomask void
create_haven_room()
{
    
    INSIDE;
    
    seteuid(getuid(TO));
    
    create_haven();
    reset_room();

}

