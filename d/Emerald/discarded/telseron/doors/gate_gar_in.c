/*  
 * Garden entrance 
 * Called by ~telseron/garden_ent
 * Coded Finwe, September 1996
 */
 
inherit "/std/door";
 
#include "/d/Emerald/defs.h" 
 
void
create_door()
{
    set_door_id("gardengate");
    set_pass_command( ({ "s", "south" }) );
    set_door_name( ({ "golden filigree gate", "gate" }) );
    set_door_desc("The gate is a work of art. It is about " +
        "3 feet tall with a circular top. It is made of gold "+
        "filigree.\n");
    set_other_room( TOWNSHIP_DIR + "garden/path01");
    set_open(0);
}
