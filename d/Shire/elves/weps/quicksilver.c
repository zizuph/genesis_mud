#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
inherit "/std/weapon";


/*
 * /d/Shire/elves/weps/speed sword.c
 * Purpose    : sword of quickness
 * Located    : 
 * Created By : Tomas
 */


void
create_weapon()
{
    int     wh = 50 + random(6),
            wp = 30 + random(5);

    set_name("sword");
    add_name("gim");
    set_pname(({"swords", "gims"}));
    set_adj("rosewood-handled");
    set_adj("elegant");
    set_short("elegant rosewood-handled sword");
    set_long("The blade of the " + short() + " is forged from carbon steel and " +
    "expertly heat treated. The fuller or 'blood groove separates twin sharp edges "+
    "and a strong, useful point, the " + short() + " is as elegant as it is effective. " +
    "The traditional guard and pommel are adorned in royal filigree.\n");

   
    set_default_weapon(wh,wp,W_SWORD,W_SLASH | W_IMPALE,W_ANYH, TO);

    add_prop(OBJ_I_LIGHT,1);

    add_prop(OBJ_I_WEIGHT,10000); /* These used to be set by mudlib if no value *
                                   * was provided according to hit/pen          */
    add_prop(OBJ_I_VOLUME,8200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(42,40));     

    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"You sense that the magic imbued within the " +
    short()+ "has something to do with time.\n",25,"You sense that this "+
    "sword has been imbued with quickness!",50}));
    add_prop(OBJ_S_WIZINFO,"This is a quickness sword adds +100.\n");
}

mixed
wield(object what)
{
    TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop_setting(LIVE_I_QUICKNESS) + 100);
    write("Suddenly, you feel as if the world seems a lot slower.\n");
    return 0;
}

   
int
unwield()
{
    set_this_player(query_wielded());
    write("Suddenly, the world seems to speed up, returning to normal.\n");    
    TP->change_prop(LIVE_I_QUICKNESS, TP->query_prop_setting(LIVE_I_QUICKNESS) - 100);

    return 0;
}
