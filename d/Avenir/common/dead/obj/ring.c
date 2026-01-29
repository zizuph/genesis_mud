
// file name: /d/Avenir/common/dead/obj/ring.c
// creator(s): Lilith, June 2021
// purpose: Jewelry for the crypt residents
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
    mapping types = ([ "silver" : ({ 150, 150, 180 }),
                   "amber" : ({150, 140, 170 }),
                   "gold" : ({ 150, 300, 300 }),
                   "platinum" : ({ 150, 260, 300 }),
                   "bloodstone" : ({ 150, 160, 200 }),
                   "emerald" :  ({ 150, 260, 300 }),
                   "pearl" :  ({ 150, 160, 200 }),				   
				   ]);

        /* adj : value mod, size mod, weight mod */
   mapping adjs = ([ "thin" : ({ 1.0 / 2.0, 2.0 / 3.0, 2.0 / 3.0 }),
                  "heavy" : ({ 2.0, 2.0, 2.0 }),
                  "braided" : ({ 1.0, 1.0, 1.0 }),
                  "elegant" : ({ 2.0, 1.0, 1.0 }) ]);

    int   val;

    if(!strlen(type) || !sizeof(types[type]))
       type = ONEOF(m_indexes(types));

    if(!strlen(adj) || !sizeof(adjs[adj]))
       adj = ONEOF(m_indexes(adjs));

    set_adj(({adj, type}));
    set_short(adj + " " + type + " ring");
    set_long("It is a lovely " + adj + " ring, crafted simply "
       + "from " + type + ".\nThe inner band has the trefoil "
	   + "symbol of Sybarus stamped upon it.\n");
    
    val = ftoi(itof(types[type][0]) * adjs[adj][0]);
    add_prop(OBJ_I_VALUE, val);

    val = ftoi(itof(types[type][1]) * adjs[adj][1]);
    add_prop(OBJ_I_VOLUME, val);

    val = ftoi(itof(types[type][2]) * adjs[adj][2]);
    add_prop(OBJ_I_WEIGHT, val);

    set_at(NAME_TO_RANDOM(query_short(), 32789, 2) ?
        A_R_FINGER : A_L_FINGER);
}

void
create_armour()
{
    set_name("ring");
    set_ac(5);

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


