/* 
 * Outer road of Telberin
 * By Finwe, January 1997
 */
 
#include "default.h"
 
/* #include "/d/Emerald/telberin/choreo/choreo.h" */
inherit AVENUE;
 
 
void
create_avenue()
{
    add_my_desc("\n\n");                
    /*
    add_exit(CHOREO_DIR + "foyer", "south", "@@block");
    */
    add_exit(AVENUE_DIR + "ave09", "west");
    add_exit(AVENUE_DIR + "ave11", "southeast");
    set_alarm(1.0,0.0,"reset_room");
}

/* 
int
block()
{
    write("The choreographer's club will soon be open south of here "+
        "but for now you will have to wait.\n");
    return 1;
}
*/

void
reset_room()
{
}
