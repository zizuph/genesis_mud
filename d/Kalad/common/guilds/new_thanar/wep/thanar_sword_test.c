/*
*  This is a knife dropped by the new Thanar Boss fight:
*  (/d/Kalad/common/guilds/new_thanar/npc/thanar.c)
*
*  The Hit/Pen is modified on a calculation of Physical vs. Mental on 
*  enter_env (This is done in STDIR + thanar_weapon_std.c). The weapon
*  doesn't break or dull.
*
*  There is also a second modifier based on the reverse calculation to
*  hit/pen (Mental vs. Physical) that then applies a damamge modifier
*  in a mask of did_hit. Players will never get the full benefit of
*  both, but if evenly stated (Humans for example) they will get some 
*  of both.
*
*  Coded by Mirandus (Tim Breen) - June 2020
*/

#include "../local.h"
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
inherit STDIR + "thanar_wep_std_test";


/*
 * Function name: create_weapon()
 * Description  : Constructor, redefine this to configure your weapon
 */
void
create_weapon() 
{
    
    set_name(({"sword","longsword"}));
    set_adj("blackened");
    add_adj("magnificent");
    set_short("blackened magnificent longsword");
    set_long("This is "+LANG_ASHORT(this_object())+". It bears the mark "
    +"of the Thanarian order, a black serpent. It has reverberates as though"
    +"it contains some essence within. The edge is sharp and the handle "
    +"bound for extreme comfort in black leather. Overall it feels " 
    +"quite well-made.\n");
         
    set_default_weapon(35, 35, W_SWORD, W_SLASH | W_IMPALE, W_NONE,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 35) + random(20) -10);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35, W_SWORD) +
        random(50) - 25);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon was forged by Thanar himself "+
        "in order to serve his most prized and valued priests. No priest has "+
        "yet earned the right to wield it. Thus Thanar had held himself. " +
        "It is incredibly durable. The sword judges the wielder on what they "+
        "prize. If they prize physical feats, they will find the blade better "+
        "to strike. If they prize mental they will find when it does hit the "+
        "strike hurts more. Those who favour neither will benefit from "+
        "both.\n",15}));
    add_prop(OBJ_S_WIZINFO, "This weapon hit/pen based on the percent  " +
        "difference between physical and mental stats. It also deals  " +
        "additional damage to non-humans modified by the percent difference " +
        "in mental and physical stats. Max multiplier is 1.7. Players will " +
        "never be able to get both modifiers to their max because of the "+
        "calculations. Humans (Thanar you know) will get some of both.\n");
        
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    int stat_percent2, stat_phys_avg2, stat_ment_avg2, *phys_stats2, 
    *ment_stats2;
    float stat_mod2;
    object wielder;

    wielder = query_wielded();

    phys_stats2 = ({ SS_STR, SS_CON, SS_DEX });
    stat_phys_avg2 = reduce(&operator(+)(,), map(phys_stats2, 
        wielder->query_stat)) / sizeof(phys_stats2);

    ment_stats2 = ({ SS_WIS, SS_INT, SS_DIS });
    stat_ment_avg2 = reduce(&operator(+)(,), map(ment_stats2, 
        wielder->query_stat)) / sizeof(ment_stats2);
    
    stat_percent2 = min(110,(stat_ment_avg2 *100)/ stat_phys_avg2);

    switch(stat_percent2) 
    {
    case 110:  
        stat_mod2 = 1.7;
        break;
    
    case 107..109:
        stat_mod2 = 1.65;
        break;
        
    case 104..106:
        stat_mod2 = 1.6;
        break;
        
    case 101..103:
        stat_mod2 = 1.5;
        break;
    
    case 99..100:
        stat_mod2 = 1.45;
        break;

    case 97..98:
        stat_mod2 = 1.4;
        break;        

    case 95..96:
        stat_mod2 = 1.35;
        break;

    case 93..94:
        stat_mod2 = 1.3;
        break;
        
    case 91..92:
        stat_mod2 = 1.2;
        break;
    
    default:
        stat_mod2 = 1.0;
        break;
    }

    if ((phurt >= 0) && (enemy->query_race_name() != "human") && (random(10)
    > 5))
    {
        int new_dam = ftoi(itof(dam) * (stat_mod2));
        enemy->heal_hp(-(new_dam));
        MIR_DEBUG("Damage " +new_dam+".");
        enemy->catch_tell("You feel the " +short()+" slice deeper than "+
        "expected.\n" );
        wielder->catch_tell("You feel the "+short()+" slice deeper than "+
        "expected.\n");
        wielder->tell_watcher(QTNAME(wielder)+" grins with grim satisfaction "
        +"as the "+short()+" slices deeply into "+QTNAME(enemy)+".\n");

    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}