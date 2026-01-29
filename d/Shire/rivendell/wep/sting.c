/*
 *  Sting, for Bilbo Baggins in Imladris
 *  Made by Finwe, July 1998
 */
 
inherit "/std/weapon";
inherit "/lib/keep";
 
#include <options.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Shire/sys/defs.h"
 
#define WC  25
#define PEN 25
 
 
create_weapon()
{
    set_name(({"ancient knife", "knife", "sting"}));
    set_pname("knives");
    set_short("ancient knife");
    set_pshort("ancient knives");
    set_adj(({"long", "ancient"}));
    set_long("This " + short() +  " was " +
        "manufactured in Gondolin in the First Age and carried " +
        "away as spoil by the creatures of Morgoth. Bilbo " +
        "Baggins discovered it in some troll hoard and " +
        "named it Sting during one of his many journies. " +
        "Because of the knife's length, hobbits and gnomes " +
        "often use it a sword rather than a knife.\n");
 
    set_default_weapon(
        WC,
        PEN,                      /* penetration value */
        W_KNIFE,                /* weapon type       */
        W_IMPALE | W_SLASH,     /* damage type       */
        W_ANYH,                 /* nr of hands       */
        0);           /* object that defines wield and unwield functions */
 
 
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WC,PEN));

// magical props
    add_prop(OBJ_S_WIZINFO,
        "This is the knife Bilbo named 'Sting' in the Hobbit. For " +
        "most races, the weapon operates as a decent knife. To " +
        "smaller races--hobbits and gnomes--the hit and pen " +
        "increases and the weapon type changes to a sword when the " +
        "knife is wielded. When unwielded, weapon returns to its " +
        "original values and becomes a knife again.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment"}));

    add_prop(MAGIC_AM_ID_INFO,({"This small knife feels enchanted by ancient elven magics.", 20}));

    set_keep(1);
 
}
 
mixed wield(object to)
{
    if (TP->query_race_name() == "hobbit" || TP->query_race_name() == "gnome")

    {
        set_hit(45);
        set_pen(40);
        set_wt(W_SWORD);
        return QCTPNAME(TP) + "confidently wields " +short()+".\n";
        return 1;
    }
    else    
    {
        set_hit(WC);
        set_pen(PEN);
        return QCTPNAME(TP) + "wields " +short()+".\n";
        return 1;
    }
}

mixed unwield(object weapon)
{
    set_hit(WC);
    set_pen(PEN);
    set_wt(W_KNIFE);
}
