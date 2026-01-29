/*  
 * Telseron northern gate include file
 * Called by TOWNSHIP + "n_gate.c"
 * Coded Finwe, September 1996
 */
 
inherit "/std/door";
 
#include "/d/Emerald/defs.h" 
 
void
create_door()
{
/* 'name' of the door */
    set_door_id("northgate"); 
 
    set_pass_command( ({ "se", "southeast" }) );
    set_door_name( ({ "solid brilliant", "gate" }) );
    set_door_desc("The gate is made of an unknown metal substance. " +
        "It doesn't show any signs of battle and yet is appears " +
        "to be freshly made. It is polished to a brilliant shine " +
        "and nearly blinds you.\n");
 
/* what room the door opens to */
    set_other_room( TOWNSHIP_DIR + "rd01");
 
/* closed by default */
    set_open(0); 
}
