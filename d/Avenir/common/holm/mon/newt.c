// newt
// Creator:      Lilith Oct 2003

inherit "/d/Avenir/inherit/creature";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/deities.h"

#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_TAIL   (TS_RARM | TS_LARM)

void
create_creature()
{
    set_name("newt");
    set_pname("newts");
    set_race_name("newt");
    set_adj(({"small", "orange"}));
    set_short("small orange newt");
    set_long("This small, brightly coloured fellow "+
        "is a semi-aquatic salamander known as a newt. "+
        "It has four toes on each foot.\n");
    set_alignment(0);

//  Sets the stats for us, its a simple npc 
    default_config_creature(1 + random(3));

    remove_prop(OBJ_M_NO_GET);
    add_prop(CONT_I_VOLUME, 60);
    add_prop(CONT_I_WEIGHT, 50);
    add_prop(LIVE_I_NEVERKNOWN, 1); 

    set_hitloc_unarmed(H_HEAD, ({ 10 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 10 }), 40, "body");
    set_hitloc_unarmed(H_TAIL, ({ 10 }), 10, "tail");

    add_leftover("/d/Avenir/common/bazaar/Obj/misc/toe", "toe",4, "", 0,0);
}

