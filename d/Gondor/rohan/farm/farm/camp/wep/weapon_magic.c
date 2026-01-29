/*
 * /d/Gondor/rohan/farm/farm/camp/wep/weapon_magic.c
 *
 * Varian - 2016
 *
 * - Modified with help from Arman to save random factors
 *   Varian - April 2020
 *
 *  Shamelessly stolen for Dunlendings. This is intended to
 *  be the default weapon for dunlending warriors.
 *
 *  This weapon is intended to be a rare drop. It has a special
 *  attack that scales with discipline. The axe itself becomes
 *  both lighter and has higher hit/pen when the player who 
 *  wields it has more discipline. It also emits up to 3 
 *  levels of light.
 *
 *  The normal max is 45 hit and pen, but for knives it's capped
 *  at 40 to keep within the rules.
 *
 *  Raymundo, Spring 2020
 */

#pragma strict_types

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

inherit "/std/weapon";
inherit "/lib/keep";


#define ADJ ({"nasty", "vicious", "cruel", "blood-spattered", "deadly"})
#define SHARP_ADJ2 ({"mithril-inlaid"})
#define BLUNT_ADJ2 ({"mithril-inlaid"})
#define TYPE ({"W_AXE", "W_CLUB", "W_POLEARM", "W_SWORD", "W_KNIFE"})
string adj, adj2, wep, type;
string head();

/*
 * Function Name:   set_weapon_data
 * Description:     Sets type of weapon and adjectives for the weapon.
 * Returns:         The type of weapon and associated adjectives.
 */
void
set_weapon_data()
{
    seteuid(getuid());

    if(!strlen(adj))
    {
        type = one_of_list(TYPE);
        adj = one_of_list(ADJ);
        if(type == "W_CLUB")
        {
            adj2 = one_of_list(BLUNT_ADJ2);
        }
        else
        {
        adj2 = one_of_list(SHARP_ADJ2);
        }
        
    }
     //sets the weapon type, etc.
    switch(type)
    {
    case "W_SWORD":
    {
        set_dt(W_SLASH);
        wep = "longsword";
        add_name("sword");
        set_hands(W_BOTH);
        if(adj2 == "double-bladed")
        {
            adj2 = "double-edged";
        }
        set_wt(W_SWORD);
        break;
    }
    case "W_AXE":
    {
        set_dt(W_SLASH);
        wep = "battleaxe";
        add_name("axe");
        set_hands(W_BOTH);
        set_wt(W_AXE);
        break;
    }
    case "W_KNIFE":
    {
        set_dt(W_SLASH);
        set_hands(W_ANYH);
        wep = "dagger";
        add_name("knife");
        set_wt(W_KNIFE);
        break;        
    }
    case "W_POLEARM":
    {
        set_dt(W_IMPALE);
        wep = "spear";
        set_hands(W_BOTH);
        set_wt(W_POLEARM);
        break;
    }
    case "W_CLUB":
    {
        set_dt(W_BLUDGEON);
        wep = "mace";
        add_name("club");
        set_hands(W_BOTH);
        set_wt(W_CLUB);
        break;
    }
    }
    
    set_name(wep);
    add_name("weapon");
    set_short(adj + " " + adj2 + " " + wep);
    set_adj(adj);
    add_adj(adj2);

    set_long("@@my_long@@");
    add_item( ({"inlay", "inlays"}), "The inlays look like they should "
        + "pulse with light.\n");
   
   add_prop(OBJ_S_WIZINFO, 
        "This weapon improves with a player's discipline. As your discipline "
        + "improves, the axe emits more light. Special fires random(100) "
        + "< (skill/10) of the time each combat round. "
        + "At 100 skill, the special is effectively a 10% haste because "
        + "it is equivalent to an extra vanilla hit attempt 10% of "
        + "the time.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"This is a weapon that rewards those who "
        + "are self-disciplined.", 10, "It will light your path in the dark."
        }) );
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE,(1728*5));

}



void
create_weapon()
{
    set_weapon_data();
    set_wf(this_object());
}

/* Function Name:   head
 * Returns:         'head' for clubs or 'blade' for all other weapons.
 *                  To be used in the long description.
 */
string
head()
{
    if(type == "W_CLUB")
    {
        return("head");
    }
    else
    {
        return("blade");
    }
}

/*
 * Function Name:   dis
 * Type:            int
 * Returns:         player's discipline
 */
int
dis()
{
    return(TP->query_stat(SS_DIS));
}

/*
 * Function Name:   how_light
 * Description:     Provides a description of how much light the 
 *                  weapon provides for a player.
 * Returns:         A string describing the ammount of light.
 */
string
how_light()
{
    if(dis() <= 100)
    {
        return("a faint");
    }
    else if (dis() <= 200)
    {
       
        return("a moderate");
    }
    else if(dis() >= 201)
    {
        
        return("an intense");
    }
    
    
}

/*
 * Function Name:   my_long
 * Type:            string
 * Returns:         The long description of the weapon, which varies
 *                  depending on the player's discipline and whether
 *                  or not the weapon is being wielded.
 */ 
string
my_long()
{
   if(TO->query_wielded() == 0)
   {
       return("This is a " + query_short() + ". It is a rather short " 
        + wep + ", measuring about the two-thirds of what you'd expect. The "
        + head() + " is " + adj2 + ", and although it looks like it should "
        + "shine, the " + wep
        + " appears to be dull.\n");
   }
   else
   {
       return("The " + query_short() + " seems to be almost pulsing with "
        + "a life of its own. Although the " + wep + " itself is short, it feels "
        + "much longer, as if its spirit is bigger than its size. The "
        + head() + " of the " + wep + " glows with a " 
        + how_light() + " shine.\n");
   }
    
    
}

void init()
{
    ::init();
 
}

/* Function Name:   wep_skill
 * Arguments:       none
 * Description:     queries the weapon skill for the type of weapon this is.
 *
 */
int
wep_skill()
{
    object me;
    me = query_wielded();
     
    if(type == "W_AXE")
    {
        return(me->query_skill(SS_WEP_AXE));
    }
    if(type == "W_CLUB")
    {
        return(me->query_skill(SS_WEP_CLUB));
    }
    if(type == "W_POLEARM")
    {
        return(me->query_skill(SS_WEP_POLEARM));
    }
    if(type == "W_SWORD")
    {
        return(me->query_skill(SS_WEP_SWORD));
    }
    if(type == "W_KNIFE")
    {
        return(me->query_skill(SS_WEP_KNIFE));
    }
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    object me;
    string text, ptext;

    me = query_wielded();
    
    skill = wep_skill();
    stat = me->query_stat(SS_DIS);
    skill_e = enemy->query_skill(SS_DEFENCE);
    stat_e = enemy->query_stat(SS_DIS);




    if (random(100) < (skill/10) && 
        me->query_combat_object()->cb_tohit(query_attack_id(), 
        query_hit(), enemy) > 0)
    {
    pen = F_PENMOD(MIN(30+random(stat/8), query_pen()), skill);
    hitresult = enemy->hit_me(pen, W_IMPALE, me, one_of_list(query_slots()));
    perf = hitresult[2] * 100 / pen;
    pdam = hitresult[0];

    ptext = "a lousy";
    if (perf > 15)
        ptext = "an okay";
    if (perf > 30)
        ptext = "a good";
    if (perf > 45)
        ptext = "a very good";
    if (perf > 60)
        ptext = "a vicious";
    if (perf > 75)
        ptext = "a very vicious";
    if (perf > 90)
        ptext = "an extremely vicious";

    text = "unharmed";
    if (pdam > 0)
        text = "tickled";
    if (pdam > 2)
        text = "bruised";
    if (pdam > 5)
        text = "in pain";
    if (pdam > 10)
        text = "hurt";
    if (pdam > 17)
        text = "quite hurt";
    if (pdam > 25)
        text = "very hurt";
    if (pdam > 35)
        text = "beaten";
    if (pdam > 50)
        text = "crushed";
    if (pdam > 70)
        text = "pummeled";
    if (pdam > 90)
        text = "near death";

/*
    me->catch_msg("You strike "+ptext+" hit on "+QTNAME(enemy)+" with your "+
      query_short() +".\n"+capitalize(enemy->query_pronoun())+" looks "+
      " "+text+".\n");
    enemy->catch_msg(QCTNAME(me)+" strikes "+ptext+" hit on you with "+
      me->query_possessive()+" " + query_short() + ".\n"+
      "You feel "+text+".\n");
    me->tell_watcher(QCTNAME(me)+" strikes "+ptext+" hit on "+QTNAME(enemy)+
      " with "+me->query_possessive()+" " + query_short() + ".\n"+
      capitalize(enemy->query_pronoun())+" looks "+
      text+".\n", enemy);
*/
    switch(pdam)
    {
        case 0..4:
        me->catch_msg("Your " + wep + " rises up on its own to make "
            + ptext + " swing at " + QCTNAME(enemy) + ", but "
            + enemy->query_pronoun() + " is only " + text + ".\n");
        enemy->catch_msg(QCPNAME(me) + " " + wep + " rises up on its "
            + "own to make " + ptext + " swing at you, but you are "
            + "only " + text + ".\n");
        me->tell_watcher(QCPNAME(me) + " " + wep + " rises up on its "
            + "own to make " + ptext + " swing at " + QCTNAME(enemy) 
            + ", but " + enemy->query_pronoun() + " is only "
            + text + ".\n");
        break;
        
        case 5..10:
        me->catch_msg("The " + wep + " comes alive in your grip and "
            + "you strike " + QCPNAME(enemy) + " with a " + ptext
            + " blow. " + capitalize(enemy->query_pronoun()) 
            + " seems " + text + ".\n");
        enemy->catch_msg(QCPNAME(me) + " " + wep + " seems to come "
            + "alive in " + HIS_HER(me) + " hands. The " + wep 
            + " strikes you with " + ptext + " blow, leaving you "
            + "feeling " + text + ".\n");
        me->tell_watcher(QCPNAME(me) + " " + wep + " seems to come "
            + "alive in " + HIS_HER(me) + " hands. The " + wep 
            + " strikes " + QCTNAME(enemy) + " with " + ptext 
            + " blow, leaving " + HIM_HER(enemy) + " looking " 
            + text + ".\n");
        break;
            
        case 11..34:
        me->catch_msg("Quick as a snake, you make " + ptext
            + " strike with your " + wep + ", leaving "
            + QTPNAME(enemy) + " " + text + "!\n");
        enemy->catch_msg("Quick as a snake, " + QTNAME(me)
            + "makes " + ptext + " strike with " +HIS_HER(me)
            + " " + wep + ", leaving you " + text + "!\n");
        me->tell_watcher("Quick as a snake, " + QTNAME(me)
            + " makes " + ptext + " strike with " + HIS_HER(me)
            + " " + wep + ", leaving " + QTNAME(enemy) 
            + " " + text + ".\n");
        break;
        
        case 35..69:
        me->catch_msg("Your " + wep + " pulses in your hands, "
            + "and lashes out on its own, striking " + QTNAME(enemy)
            + " with " + ptext + " blow. " + QCTNAME(enemy) 
            + "looks " + text + " by your " + wep + ".\n");
        enemy->catch_msg(QCPNAME(me) + " " + wep + " pulses in "
            + HIS_HER(me) + " hands, and lashes out on its own, "
            + "striking you with " + ptext + " blow. You feel "
            + text + " by " + HIS_HER(me) + " " + wep + ".\n");
        me->tell_watcher(QCPNAME(me) + " " + wep + " pulses in "
            + HIS_HER(me) + " hands, and lashes out on its own, striking "
            + QNAME(enemy) + " with " + ptext + " blow. " + QCTNAME(enemy)
            + " looks " + text + " by " + QPNAME(me) + " " 
            + wep + ".\n");
        break;
        
        case 70..100:
        me->catch_msg("You feel a burst of power from your " + wep
            + " and you shout a raw battle cry. The " + wep
            + " rises up and smashes " + QNAME(enemy) + " with "
            + ptext + " blow, leaving " + HIM_HER(enemy) +  " "  + text
            + "!\n");
        enemy->catch_msg(QCTNAME(me) + " shouts a raw batle cry, "
            + "whilst " + HE_SHE(me) + " raises the " + wep
            + " above " + HIS_HER(me) + " head. The " + wep
            + " descends in " + ptext + " blow, leaving you "
            + text + "!\n");
        me->tell_watcher(QCTNAME(me) + " shouts a raw battle cry, "
            + "whilst " + HE_SHE(me) + " raises the " + wep
            + " above " + HIS_HER(me) + " head. The " + wep
            + " descends in " + ptext + " blow, leaving "
            + QNAME(enemy) + " " + text + "!\n");
            break;
            
        default:
        me->catch_msg("Quick as a snake, you make " + ptext
            + " strike with your " + wep + ", leaving "
            + QCPNAME(enemy) + " " + text + "!\n");
        enemy->catch_msg("Quick as a snake, " + QCTNAME(me)
            + "makes " + ptext + " strike with " +HIS_HER(me)
            + " " + wep + ", leaving you " + text + "!\n");
        me->tell_watcher("Quick as a snake, " + QCTNAME(me)
            + "makes " + ptext + " strike with " + HIS_HER(me)
            + " " + wep + ", leaving " + QCTNAME(enemy) 
            + " " + text + ".\n");
        break;
    }
            
        
        
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 0;
    }
    }
    return 1; /* Try hit */
}




/*
 * Function Name:   wield
 * Description:     Updates the weight, hit, pen, and light that the
 *                  weapon has as the weapon is wielded.
 * Returns:         1. This weapon can be wielded by anyone.
 */
mixed
wield()
{
    tell_room(environment(TP), "As " + QCTNAME(TP) + " wields the " 
        + query_short() + ", the " + wep + " emits " + how_light() 
        + " glow!\n", TP);
    write("As you wield the " + query_short() + ", the "+ wep + " emits "
        + how_light() + " glow!\n");
    add_prop(OBJ_I_WEIGHT, (10000 - (dis() * 10)));
    
    set_hit((TP->query_stat(SS_DIS) / 4));
    set_pen((TP->query_stat(SS_DIS) / 4));
    switch(type)
    {
        case "W_KNIFE":
            if(TO->query_hit() > 40)
            {
                set_hit(40);
            }
            if(TO->query_pen() > 40)
            {
                set_pen(40);
            }
        break;
        default:
            if(TO->query_hit() > 45)
            {
                set_hit(45);
            }
            if(TO->query_pen() > 45)
            {
                set_pen(45);
            }
            break;
    }
    switch(dis())
    {
        case 0..99:
        break;
        case 100..199:
        add_prop(OBJ_I_LIGHT, 1);
        break;
        case 200..400:
        add_prop(OBJ_I_LIGHT, 3);
        break;
    }
    
    TP->update_weapon(TO);   
    return 1;
}

/*
 * Function Name:   unwield
 * Description:     sets the weapon stats back to normal.
 */
mixed
unwield()
{
    tell_room(environment(TP), "As " + QCTNAME(TP) + " releases the "
        + query_short() + " the " + wep + " becomes dull once more.\n", TP);
        
    write("As you release the " + query_short() + " the " + wep
        + " becomes dull once more.\n");

    set_hit(20);
    set_pen(20);
    add_prop(OBJ_I_WEIGHT,10000);
    remove_prop(OBJ_I_LIGHT);
    
    
    object wielder = query_wielded();
    return 1;
} 

/*
 * init_recover and query_recover ensure that the weapon doesn't change
 * types or adjectives when the weapon reloads.
 */
void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    
    if (sizeof(a) >= 4)
    {
        adj = a[1];
        adj2 = a[2];
        type = a[3];
        
    }

    init_wep_recover(arg);
    set_weapon_data();
}

string
query_recover()
{
    return ::query_recover() + "&&" + adj + "&&" + adj2 + "&&" + type;
}

