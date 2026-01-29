// file name:        /d/Avenir/common/dark/obj/oshield.c
// creator(s):       Cirion, May 1996, taken from examples by Boriska
// revision history: Denis, May'00: Tried to fix runtime error.
// purpose:          Random shield for the L5 Ogres.
//                   The better the metals, the stronger the armour will be.
// Lilith Feb 2022: Per Arman, added AOD wear prop for ogre players

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

static string *adjs = ({ "wide", "heavy", "thick", "massive", "large" });
 
// make sure the quality improves for better materials
static string *materials = ({"copper", "bronze", "iron", "steel", "alloy", "adamantine" });

static int adj, mat;
 
varargs void configure_me(int num);
 
void
create_armour()
{
    set_name("shield");
    add_adj ("ogre");
    set_at(A_SHIELD);
    adj = random(sizeof(adjs));
    mat = random(3);
    configure_me();
}
 
varargs void configure_me(int num)
{
    if (num)
        mat = MIN(num, sizeof(materials) - 1);
 
    set_short(adjs[adj] + " " + materials[mat] + " shield");

    add_adj(adjs[adj]);
    add_adj(materials[mat]);
    set_long("It is a massive shield constructed of beaten plates of thin "
             + materials[mat] + " placed over a wide frame.\n");

    /* Based on the armour_guide definition for a metal shield */
    set_default_armour(20 + (mat - 3), A_SHIELD, 0, this_object());

    add_prop(OBJ_I_WEIGHT, 8000 + 200 * mat );
    add_prop(OBJ_I_VALUE,  200 + (200 * mat));
    add_prop(OBJ_I_VOLUME, 5000 );
	add_prop("_aod_wear_prop", 1);
}

string query_recover()
{
    return MASTER + ":" + query_arm_recover() + "OGRE#" + adj + "#" + mat;
}

void init_recover(string arg)
{
    string foo;
  
    sscanf(arg, "%sOGRE#%d#%d", foo, adj, mat);
    init_arm_recover(foo);
    configure_me();  
}

mixed wear(object ob)
{
    string   *races = ({ "elf", "hobbit", "gnome" }),
             *rnme = ({ "elvish", "hobbit", "gnomish" });
    int       num;

    if ((num = member_array(this_player()->query_race_name(), races)) != -1)
        return capitalize(LANG_THESHORT(this_object()))
               + " are too big to fit over your small "+rnme[num]+" arm.\n";
    else
        return 0;
}
