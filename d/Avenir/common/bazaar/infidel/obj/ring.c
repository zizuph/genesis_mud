inherit "/std/armour";

#include "../infidel.h"
#include <math.h>

string type, adj;

void
config()
{
        /* material : value, size, weight, */
    mapping types = ([ "gold" : ({ 350, 150, 180 }),
                   "silver" : ({ 200, 140, 170 }),
                   "brass" : ({ 96, 100, 120 }),
                   "copper" : ({ 20, 60, 100 }),
                   "adamantine" : ({ 400, 160, 200 }) ]);

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
       + "from " + type + ".\n");
    
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
    set_ac(2);

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


