inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/d/Krynn/solace/graves/local.h"


create_weapon()
{
	set_name("sword");
	set_adj("bone");
	set_long("This sword is made completely of bone! Still it looks quite sharp.\n");
	set_default_weapon(20, 20, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
	add_prop(OBJ_I_VOLUME, 400);
}
 
string
query_recover()
{
    return OBJ + "skel_wep2.c:" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
