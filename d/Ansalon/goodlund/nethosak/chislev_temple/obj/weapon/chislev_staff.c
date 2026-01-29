/*
 *  chislev_staff.c
 *
 *  This is a nature and earth based staff for a druid
 *  who worship Chislev, his temple is located in Mithas.
 *  The staff bases its hit/pen on the wielders skill in
 *  life and earth spells, superior guru in both would
 *  result in a 60 hit/pen.
 *
 *  Created by Carnak, January 2016
 *
 *  Carnak July 1st 2017: Fixed a bug in wield, when changing to a club
 *                        it didnt update the combat object.
 *                        Altered the hit/pen conversion to give it a
 *                        minimum of 45 instead of 40, as having superior
 *                        guru in both life and earth is a steep req.
 *
 * Added spell power as part of the updated magic system.
 * Arman Kharas, December 2021
 */

#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/sys/global/cmdparse.c"
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"

#include "../../local.h"
/*
 * Function     : query_long
 * Description  : Returns long description
 */
string
query_long()
{
    return  "This is a short thick gnarled wooden pole, the shaft "+
            "is riddled with budding branches growing small wild "+
            "blossoms. The wood seems vivid and alive, almost "+
            "warm to the touch.\n";
}

/*
 * Function     : query_mod_wep
 * Description  : Returns hit and pen based on wielders skill
 */
public int
query_mod_wep()
{
    if (objectp(wielder))
        return 45 + min(15, ((wielder->query_skill(SS_ELEMENT_LIFE) + 
                              wielder->query_skill(SS_ELEMENT_EARTH)) / 12));
    
    return 45;
}

void
create_weapon()
{
    setuid();
    seteuid(getuid());
	
    set_name("staff");
    add_name("weapon");
    set_pname("staves");
    add_pname("weapons");
    set_adj("gnarled");
    add_adj("wooden");
    set_short("gnarled wooden staff");
    set_pshort("gnarled wooden staves");
    set_long("@@query_long");
    
    set_default_weapon(45, 45,
                       W_POLEARM,
                       W_BLUDGEON,
                       W_BOTH);
    set_magic_spellpower(45);
    set_spellpower_elements(({
        SS_ELEMENT_EARTH, SS_ELEMENT_LIFE
    }));
	  
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"The " + short() + " is enchanted.\n", 5,
    "Imbued with earth and life itself.\n", 35,
    "Its strength increases with the wielders affinity to nature.\n", 45 }));
	
    add_prop(OBJ_S_WIZINFO,"The " + short() + " has extra hit and pen " +
    "(and spellpower) depending on life and earth spells.\n");
    
    set_keep(1);
	
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(60, W_POLEARM) +
        random(250) + 1000);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(60, 60) + 100 + random(20));
	
    set_wf(this_object());
}

/*
 * Function     : wield
 * Description  : Initiates the staff and determines if it
 *                should be a club or a polearm weapon
 */
mixed
wield(object what)
{
    object cmbt;
    
    if (wielder->query_skill(W_CLUB) > wielder->query_skill(W_POLEARM))
        set_wt(W_CLUB);
    else
        set_wt(W_POLEARM);
    
    set_hit(query_mod_wep());
    set_pen(query_mod_wep());
    set_magic_spellpower(query_mod_wep());
    
    /* Updates the combat object, so it uses the correct skill */
    if (objectp(cmbt = wielder->query_combat_object()))
        cmbt->cb_update_weapon(this_object());
    
    if (file_size(TLOG + "staffwield") > 100000)
        rename(TLOG + "staffwield", TLOG + "staffwield.old");
    
    write_file(TLOG + "staffwield",
    ctime(time()) + ": " + wielder->query_name() + " - " +
    "avg: " + wielder->query_average_stat() + " - " +
    "hit: " + this_object()->query_hit() + " - " +
    "pen: " + this_object()->query_pen() + " - " +
    "type: " + query_wt() + "\n");
}


/*
 * Function     : unwield
 * Description  : Returns the staff to a polearm
 */
mixed
unwield (object what)
{
    set_wt(W_POLEARM);
    set_hit(query_mod_wep());
    set_pen(query_mod_wep());
    set_magic_spellpower(query_mod_wep());
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}