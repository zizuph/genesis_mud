/*  
 * Castle entrance 
 * Called by ~telseron/rd31
 * Coded Finwe, December 1996
 */
 
inherit "/std/door";
 
#include "/d/Emerald/defs.h" 
 
void
create_door()
{
    set_door_id("castlegate");
    set_pass_command( ({ "s", "south" }) );
    set_door_name( ({ "silver ornamental gate", "gate" }) );
    set_door_desc("The gate is a wonder to behold. It is made from " +
        "silver with intricate floral designs. It is inlaid with " +
        "many jewels. They twinnkle in the sunlight.\n");
    set_other_room( TOWNSHIP_DIR + "castle/out_court");
    set_open(0);
}
