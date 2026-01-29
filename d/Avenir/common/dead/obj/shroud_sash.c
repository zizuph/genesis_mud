
// file name: /d/Avenir/common/dead/obj/shroud_sash.c
// creator(s): Lilith, June 2021
// purpose: Used to bind shrouds to corpses
// note:      
// updates: 

inherit "/std/armour";

#include "../dead.h"
#include <math.h>

string type, adj;

void
config()
{
        /* material : value, size, weight, */
    mapping types = ([ "silver" : ({ 35, 150, 180 }),
                   "gold" : ({ 150, 300, 300 }),
                   "platinum" : ({ 150, 260, 300 }),
                   "braided" : ({ 35, 160, 200 }),
                   "webcloth" :  ({ 200, 260, 300 }),
                   "samite" :  ({ 150, 160, 200 }),				   
				   ]);

        /* adj : value mod, size mod, weight mod */
   mapping adjs = ([ "ruby-studded" : ({ 1.0, 2.0, 2.0 }),
                  "emerald-studded" : ({ 2.0, 2.0, 2.0 }),
                  "sapphire-studded" : ({ 1.0, 1.0, 1.0 }),
                  "diamond-studded" : ({ 2.0, 1.0, 1.0 }) ]);

    int   val;

    if(!strlen(type) || !sizeof(types[type]))
       type = ONEOF(m_indexes(types));

    if(!strlen(adj) || !sizeof(adjs[adj]))
       adj = ONEOF(m_indexes(adjs));

    set_adj(({adj, type}));
    set_short(adj + " " + type + " sash");
    set_long("This "+ TO->short() +" was made by master "
	   +"craftsmen in Sybarus. It is the type of ornamental "
       +"clothing that one wears to their final resting "
	   +"place, used to bind the funeral shroud to its "
	   +"owner.\n");
    
    val = ftoi(itof(types[type][0]) * adjs[adj][0]);
    add_prop(OBJ_I_VALUE, val);

    val = ftoi(itof(types[type][1]) * adjs[adj][1]);
    add_prop(OBJ_I_VOLUME, val);

    val = ftoi(itof(types[type][2]) * adjs[adj][2]);
    add_prop(OBJ_I_WEIGHT, val);
}

void
create_armour()
{
    set_name("sash");
	add_name("belt");
	add_adj("ornamental");
    set_ac(10 +random(20));
    set_at(A_WAIST);
    config();
}

string
query_arm_recover()
{
    return ::query_arm_recover() + "#TYPE#" + type + "#ADJ#" + adj;
}

void
init_arm_recover(string arg)
{
    string foo;

    ::init_arm_recover(arg);

    if(!strlen(arg))
      return;

    sscanf(arg, "%s#TYPE#%s#ADJ#%s", foo, type, adj);
    config();
}


