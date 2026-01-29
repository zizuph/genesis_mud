// file name:        /d/Avenir/common/dark/obj/oaxe.c
// creator(s):       Cirion, May 1996, taken from examples by Boriska
// revision history: Denis, May'00: Recovery fix.
// purpose:          Random axe for the L5 Ogres.
// note:
// bug(s):
// to-do: 

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/d/Avenir/inherit/weapon";

static string *adjs = ({ "broad-bladed", "long-handled", "wide-headed" });
static string *materials = ({"copper", "bronze", "iron", "steel", "alloy", "adamantine" });
public int adj, mat;

varargs void configure_me(int num);

void create_weapon()
{
    set_name("axe");
    add_adj ("ogre");
    adj = random(sizeof(adjs));
    mat = random(3);
    configure_me();
}

varargs void configure_me(int num)
{
    int   hit = 21,   // per weapon_guide explanation of a broad axe
    pen = 37;

    if(num)
	mat = MIN(num, sizeof(materials) - 1);

    add_adj(adjs[adj]);
    add_adj(materials[mat]);
    set_short(adjs[adj] + " " + materials[mat] + " axe");
    set_pshort(adjs[adj] + " " + materials[mat] + " axes");

    set_long("It is a heavy, broad-bladed axe with a head made from " 
      + materials[mat] + ", and a very long handle that is meant to be "
      +"held in both hands.\n");

    hit += (mat - 3);
    pen += (mat - 3);
    set_default_weapon(hit, pen, W_AXE, W_SLASH, W_BOTH);

    add_prop(OBJ_I_WEIGHT, 3000 + 300 * mat );
    add_prop(OBJ_I_VALUE,  400 + (100 * mat));
    add_prop(OBJ_I_VOLUME, 7000 ); 
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "OGRE#" + adj + "#" + mat;
}

void init_recover(string arg)
{
    string foo;

    sscanf (arg, "%sOGRE#%d#%d", foo, adj, mat);
    init_wep_recover(foo);
    configure_me();  
}
