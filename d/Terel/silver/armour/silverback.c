/* File         : /d/Terel/silver_new/armour/silverback.c
 * Creator      : Pasqua
 * Date         : April 2006         
 * Purpose      : Silverback Pelt
 * Related Files: 
 * Comments     : 
 * Modifications: Udana - added cold weather protection.
 */
 
inherit "/std/armour.c";
 
#include <wa_types.h>
#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

#ifndef OBJ_COLD_WEATHER_PROTECT
#define OBJ_COLD_WEATHER_PROTECT "_obj_cold_weather_protect"
#endif

private object pelt_shadow;

int wear;

create_armour()
{
    set_name("pelt"); 
    set_pname("pelts");
    set_adj("silverback");
    set_long("A silverback pelt, thats originally from the enormous " +
       "silverback gorilla in the silver forest. it seems to protect " +
       "very well.\n");
    set_short("silverback pelt");
    set_pshort("silverback pelts");
    set_default_armour(37, A_ROBE, 0, 0);
    set_am(({ 2, -3, 2}));
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 5000);
    set_wf(TO);
    add_prop(OBJ_COLD_WEATHER_PROTECT, 2);
}

public int
wear()
{
    object tp = this_player();

    if(objectp(pelt_shadow));
    {
        pelt_shadow->remove_shadow();
    }

    setuid();
    seteuid(getuid());

    pelt_shadow = clone_object(ARMOUR + "pelt_shadow");
    pelt_shadow->set_pelt_shadow_owner(this_object());
    pelt_shadow->shadow_me(tp);
	write("You slide the " + short() + " over your head and body " +
             "and you look more and more like a gorilla.\n");
    say(QCTNAME(TP) + " slides the " + short() + " over " + 
             HIS_HER + " head and body and " + QTNAME(TP) + " looks more " +
             "and more like a gorilla in " + HIS_HER + " pelt.\n");
}


public int
remove()
{
    pelt_shadow->remove_shadow();
    return 0;
}

