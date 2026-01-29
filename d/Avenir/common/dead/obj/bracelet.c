
// file name: /d/Avenir/common/dead/obj/bracelet.c
// creator(s): Lilith, June 2021
// purpose: Jewelry for for the crypt residents burials
// note:      
// updates: Lilith Oct 2021: weight is really high, probably
//              because the AC was 15. Dropping to 5.
inherit "/std/armour";
inherit "/lib/keep";

#include "../dead.h"
#include <math.h>

string type, adj;

void
config()
{
        /* material : value, size, weight, */
    mapping types = ([ "mother of pearl" : ({ 150, 150, 180 }),
	               "amber" : ({ 100, 200, 250 }),                
                   "ivory" : ({ 100, 140, 170 }),
                   "silver" : ({ 100, 130, 120 }),
                   "gold" : ({ 100, 130, 190 }),
                   "platinum" : ({ 100, 160, 200 }), 
				   "kesoit" : ({ 100, 140, 140}) ]);

        /* adj : value mod, size mod, weight mod */
   mapping adjs = ([ "thin" : ({ 1.0 / 2.0, 2.0 / 3.0, 2.0 / 3.0 }),
                  "heavy" : ({ 2.0, 2.0, 2.0 }),
                  "etched" : ({ 1.0, 1.0, 1.0 }),
                  "carved" : ({ 2.0, 1.0, 1.0 }) ]);

    int   val;

    if(!strlen(type) || !sizeof(types[type]))
       type = ONEOF(m_indexes(types));

    if(!strlen(adj) || !sizeof(adjs[adj]))
       adj = ONEOF(m_indexes(adjs));

    set_adj(({adj, type}));
    set_short(adj + " " + type + " bracelet");
    set_long("It is an elegant " + adj + " bracelet, crafted simply "
       + "from " + type + ". It bears the trefoil stamp of Sybarus "
	   +"along the inner ring.\n");
    
    val = ftoi(itof(types[type][0]) * adjs[adj][0]);
    add_prop(OBJ_I_VALUE, val);

    val = ftoi(itof(types[type][1]) * adjs[adj][1]);
    add_prop(OBJ_I_VOLUME, val);

    val = ftoi(itof(types[type][2]) * adjs[adj][2]);
    add_prop(OBJ_I_WEIGHT, val);

    set_at(NAME_TO_RANDOM(query_short(), 32789, 2) ?
        A_ANY_WRIST : A_ANY_WRIST);
}

void
create_armour()
{
    set_name("bracelet");
    set_ac(5);
    set_af(TO);

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

mixed
wear()
{
    string hand = (query_at() == A_ANY_WRIST) ? "right" : "left";
    object wearing = ENV(TO);

    if(!living(wearing))
       return 0;

    wearing->catch_msg("You wear the "+ QSHORT(TO) + " over your "
       + hand + " wrist.\n");
    tell_room(ENV(wearing), QCTNAME(wearing) + " wears " + LANG_ASHORT(TO)
       + " over " + POSSESS(wearing) + " " + hand
       + " wrist.\n", wearing);
    return 1;
}

