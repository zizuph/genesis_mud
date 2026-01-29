// /d/Avenir/common/obj/knife
// creator(s):   Lilith
// last update:  May 1997
// purpose:      Just your basic knife with random attributes
/*
 * Revisions:
 * 	Lucius, Jun 2017: Added W_SLASH.
 *
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";

#include "/d/Avenir/include/defs.h"
#include <formulas.h>           
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

string adj, mat, name;
string *mats = ({ "silver", "steel", "iron", "gold" }),
       *names = ({ "knife", "dagger", "main-gauche", "dirk" }),
       *adjs = ({ "sharp", "serrated", "narrow", "gleaming",
                  "oiled", "forked", "ornamental" });

void set_mat(string str)  {    mat = str;   }

void
configure_it()
{
    if (!name) name = names[random(sizeof(names))];
    if (!mat)  mat = mats[random(sizeof(mats))];
    if (!adj)  adj = adjs[random(sizeof(adjs))];

    set_name(name);
    set_adj(adj);
    set_mat(mat); 
    set_short(adj +" "+ mat +" "+ name);
    add_adj(({ adj, mat, "common" }));
    set_long("This "+ short() +" has been crafted with great "+
        "care, for all that it is a common knife. It is very "+ 
        "well-balanced, and should be quite deadly "+
        "in the right hands.\n");

}

void 
create_weapon ()
{
    add_name("knife");
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hit(10);
    set_pen(15);
    set_hands(W_ANYH);     

    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,15) + random(50) - 20);

    configure_it();
}

string 
query_recover()
{
    return MASTER + ":" + query_wep_recover() 
                  + "#MAT#"+mat+"#ADJ#"+adj+"#NAME#"+name+"#";
}

void 
init_recover(string arg)
{
    string foo;

    init_wep_recover(arg);
    sscanf(arg, "%s#MAT#%s#ADJ#%s#NAME#%s#", foo, mat, adj, name);

    configure_it();
}
