// file name:        /d/Avenir/common/dark/obj/obracers.c
// creator(s):       Cirion, May 1996, taken from examples by Boriska
// revision history: Denis, Mar'01: Recovery fix.
// purpose:          Random bracers for the L5 Ogres.
//                   The better the metals, the stronger the armour will be.
// Lilith Feb 2022: Per Arman, added AOD wear prop for ogre players

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include <macros.h>

inherit "/std/armour";

static string *adjs =
    ({ "heavy", "large", "thick", "massive", "splint", "rigid" });

// make sure the quality improves for better materials
static string *materials = ({"copper", "bronze", "iron" });

static int adj, mat;

varargs void configure_me(int num);

void
create_armour()
{
    set_name("bracers");
    set_short("bracers");
    add_adj ("ogre");
    adj = random(sizeof(adjs));
    mat = random(sizeof(materials));
    configure_me();
}

varargs void configure_me(int num)
{
    if(num)
	mat = MIN(num, sizeof(materials) - 1);

    set_name("bracers");
    add_name(({"pair","bracer"}));

    set_short( "pair of " + adjs[adj] + " " + materials[mat] + " " + "bracers");
    set_pshort( "pairs of " + adjs[adj] + " " + materials[mat] + " " + "bracers");
    add_adj(adjs[adj]);
    add_adj(materials[mat]);

    set_long("It is a pair of large arm bracers, made from "
      +"veritcal strips of "+materials[mat]+" riveted to hard leather. They "
      +"look quite large, and would only fit on massive arms.\n");

    // Based on the weapon_guide definition for splint mail
    set_default_armour(21 + (mat - 3), A_ARMS, ({ 1, 1, -2 }), this_object());

    add_prop(OBJ_I_WEIGHT, 4500 + 400 * mat );
    add_prop(OBJ_I_VALUE,  100 + (200 * mat));
    add_prop(OBJ_I_VOLUME, 4000 );
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
    init_arm_recover(arg);
    configure_me();  
}

mixed wear(object ob)
{
    string   *races = ({ "elf", "hobbit", "gnome" }),
    *rnme = ({ "elvish", "hobbit", "gnomish" });
    int       num;

    if ((num = member_array(this_player()->query_race_name(), races)) != -1)
	return capitalize(LANG_THESHORT(this_object())) +
	" are too big to fit around your small " + rnme[num] + " arms.\n";
    else
	return 0;
}
