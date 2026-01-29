/*
 * Scimitar for tougher Haradrim
 * By Finwe, July 2005
 *
 * -- Toby, 10th-Sept-2007: Fixed with MAGIC_AM_ID_INFO and /lib/keep
 */

inherit "/std/weapon";
inherit "/lib/keep.c";


#include "/d/Gondor/defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"sword", "tulwar"}));
    set_pname(({"swords", "tulwars"}));
    set_adj("elongated");
    set_adj("curved");
    set_short("elongated curved tulwar");
    
	set_long("This " + short() + " was forged of steel by the blacksmiths " +
        "of Harad. The blade is long and slightly curved, and polished " +
        "to a dull grey. The outer edge of the blade is sharpened " +
        "and designed to flex slightly during battle. The hilt is made " +
        "of black metal and inlaid with gold.\n");

    add_item(({"blade"}),
        "The blade is long and slightly curved. It is sharpened and " +
        "forged of steel. It is polished to a dark grey and flexible " +
        "enough to be deadly in the right hands.\n");
    add_item(({"handle", "hilt"}),
        "The handle is long and made of black steel, and inlaid with " +
        "golden images of charging oliphaunts. On the bottom of the handle " +
        "is a round pommel with a spur of metal exending from it.\n");
    add_item(({"pommel"}),
        "The pommel of the sword extends from the base of the handle. A " +
        "round disk is attached to the bottom. On the bottom of the disk, " +
        "a rounded spur of metal extends outward.\n");
    add_item(({"disk", "bottom of the disk", "disk bottom"}),
        "The bottom of the disk is inlaid with gold in the image of a " +
        "sun. Extending from the center is a rounded spur of metal.\n");
    add_item(({"spur", "spur of metal", "metal spur"}),
        "The spur of metal is the length of a finger. It is smooth and " +
        "rounded, and extends from the bottom of the pommel.\n");

    set_default_weapon(40,50, W_SWORD, W_SLASH | W_IMPALE, W_BOTH);
    set_wf(TO);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(45,50)); /* magic sword */

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
        "This sword is wielded by the captains of the Haradrim. It has " +
        "no special abilities other than higher hit and pen.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This "+short()+" was forged by the Haradrim. A strong sense " +
          "of evil seems to radiate from it.", 20,
          "The revealing magic let you know that it is made by a very " +
          "skilled hand as is shown to you by the detailes in the blade. ", 30,
          "The wielder of this fine blade should hit quite easily and " +
          "penetrate armour really well.", 40,
          "\n",1}));
}

mixed 
wield(object weapon)
{
	write("You wield the " + short() + " and shout a battlecry!\n");
	say(QCTNAME(TP) + " wields a " + short() + " and shouts a battlecry!\n");
	return 1;
}


int
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    string *move_desc, *pmove_desc, *swing_desc, *pswing_desc;
    string hit_msg, dam_msg;
    mixed *hitresult;
    object wielder = query_wielded();
    int x, y;

    move_desc = (({"spin", "leap", "lunge", "spin, lunge,"}));
    pmove_desc = (({"spins", "leaps", "lunges", "spins, lunges,"}));
    swing_desc = (({"swing", "slash", "stab" }));
    pswing_desc = (({"swings", "slashes", "stabs" }));


    x = random(sizeof(move_desc));
    y = random(sizeof(swing_desc));
 

    switch(phurt)
    {
        case -1:
            hit_msg = "missing";
            dam_msg = "no";
            break;
        case 0:
            hit_msg = "barely missing";
            dam_msg = "no";
            break;
        case 1..5:
            hit_msg = "scratching";
            dam_msg = "hardly any";
            break;
        case 6..10:
            hit_msg = "nicking";
            dam_msg = "very little";
            break;
        case 11..19:
            hit_msg = "cutting";
            dam_msg = "a little";
            break;
        case 20..29:
            hit_msg = "slicing";
            dam_msg = "some";
            break;
        case 30..39:
            hit_msg = "carving";
            dam_msg = "some";
            break;
        case 40..49:
            hit_msg = "scoring";
            dam_msg = "alot of";
            break;
        case 50..59:
            hit_msg = "hacking";
            dam_msg = "alot of";
            break;
        case 60..69:
            hit_msg = "slashing";
            dam_msg = "a considerable amount of";
            break;
        case 70..79:
            hit_msg = "hewing";
            dam_msg = "a great deal";
            break;
        default:
            hit_msg = "sundering";
            dam_msg = "a deadly amount of";
            break;
    }

    wielder->catch_msg("You " + move_desc[x] + " and " +swing_desc[y] + 
        " your " + short() + ", " + hit_msg + " " + QTNAME(enemy) + 
        "'s " + hdesc + ", and do " + dam_msg + " damage.\n");
    wielder->tell_watcher_miss(QCTNAME(wielder) + " " + pmove_desc[x] + 
        " and " + pswing_desc[y] + " " + HIS_HER(wielder) + " " + short() + 
        " at " + QTNAME(enemy) + ", " + hit_msg + " " + HIS_HER(wielder) + 
        " " + hdesc + ", and doing " + dam_msg + " damage.\n",enemy);
    enemy->catch_msg(QCTNAME(wielder) + " " + pmove_desc[x] + " and " +
        pswing_desc[y] + " " + HIS_HER(wielder) + " " + short() + 
        " at you, " + hit_msg + " your " + hdesc + ", and does " + 
        dam_msg + " damage.\n");
   
    return 1;
}


