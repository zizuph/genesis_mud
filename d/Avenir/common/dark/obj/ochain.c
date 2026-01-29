// file name:        /d/Avenir/common/dark/obj/ochain.c
// creator(s):       Cirion, May 1996, taken from examples by Boriska
// revision history: Denis, Mar'01: Recovery fix.
// purpose:          Random chainmail for the L5 Ogres.
//                   The better the metals, the stronger the armour will be.
// Lilith Feb 2022: Per Arman, added AOD wear prop for ogre players

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

static string *adjs = ({ "stinking", "wide-ringed", "heavy", "long" });

// make sure the quality improves for better materials
static string *materials = ({"copper", "bronze", "iron" });

static int adj, mat;

varargs void configure_me(int num);

void
create_armour()
{
    set_name("chainmail");
    add_name(({"shirt","chain"}));
    add_adj ("ogre");
    adj = random(sizeof(adjs));
    mat = random(sizeof(materials));
    configure_me();
}

varargs void configure_me(int num)
{
    if(num)
	mat = MIN(num, sizeof(materials) - 1);

    set_short(adjs[adj] + " shirt of " + materials[mat] + " chainmail");
    set_pshort(adjs[adj] + " shirts of " + materials[mat] + " chainmail");
    add_adj(adjs[adj]);
    add_adj(materials[mat]);

    set_long("It is a long and heavy shirt of chainmail, constructed from "
      +"wide rings of "+materials[mat]+" linked together to form "
      +"good protection for the torso.\n");

    // Based on the armour_guide definition for chain mail
    set_default_armour(25 + (mat - 3), A_TORSO, ({ -2, 3, -1 }), this_object());

    add_prop(OBJ_I_WEIGHT, 9800 + 300 * mat );
    add_prop(OBJ_I_VALUE,  400 + (100 * mat));
    add_prop(OBJ_I_VOLUME, 9500 );
	add_prop("_aod_wear_prop", 1);
}

string query_recover()
{
    return MASTER + ":" + query_arm_recover() + "OGRE#" + adj + "#" + mat;
}

void init_recover(string arg)
{
    string foo;

    sscanf( arg, "%sOGRE#%d#%d", foo, adj, mat);
    init_arm_recover(arg);
    configure_me();  
}

mixed wear(object ob)
{
    string   *races = ({ "elf", "hobbit", "gnome" }),
    *rnme = ({ "elvish", "hobbit", "gnomish" });
    int       num;

    if( (num = member_array(this_player()->query_race_name(), races)) != -1)
	return capitalize(LANG_THESHORT(this_object()))
	+ " are too big to fit over your small "+rnme[num]+" body.\n";
    else
	return 0;
}
