// eel
// Creator:      Lilith Oct 2003

inherit "/d/Avenir/inherit/creature";
#include "/d/Avenir/common/common.h"

#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_TAIL   (TS_RARM | TS_LARM)

void
create_creature()
{
    set_name("eel");
    set_pname("eels");
    set_race_name("eel");
    set_adj(({"small", "slippery"}));
    set_short("small slippery eel");
    set_long("Its an eel. Slippery, long, and narrow. "+
        "Its eyes are wiggling around a lot. Maybe it "+
        "doesn't like being out of water for so long?\n");
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

    add_leftover("/d/Avenir/common/bazaar/Obj/misc/eye", "eye",1, "", 0,0);
}

