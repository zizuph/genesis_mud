/* 
 *  Goblin Special attacks modual
 *
 *  This file contains all the functions used for the goblin
 *  special attacks!  So if you want to find all the hit/pen 
 *  values for the specials that this npc does this would be
 *  the file to look into.
 *
 *  Created by Igneous@Genesis, aka Chad Richardson 
 *  July 1998
 *
 *  Modifactions:
 *
 */
#include "goblin.h"
#include "/d/Khalakhor/sys/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <formulas.h>

#define DEBUG_WHO   find_player("igneous")

#ifdef DEBUG_WHO
#define DEBUG(x)    DEBUG_WHO->catch_tell(x + "\n");
#else
#define DEBUG(x)
#endif

// Global vars
static mapping Weapon_skills =
([
  W_SWORD   : SS_WEP_SWORD,
  W_KNIFE   : SS_WEP_KNIFE,
  W_AXE     : SS_WEP_AXE,
  W_POLEARM : SS_WEP_POLEARM,
  W_CLUB    : SS_WEP_CLUB,
]);

string
desc_many(mixed oblist)
{
    if (objectp(oblist))
        oblist = ({oblist});
    return COMPOSITE_WORDS(map(oblist, &->query_the_name()));
}

string
desc_many_for(mixed oblist, object for_who)
{
    if (objectp(oblist))
        oblist = ({oblist});
    return COMPOSITE_WORDS(map(oblist, &->query_the_name(for_who)));
}

int
find_valid_enemies(object enemy, object me)
{
    // I can't attack what I can't see!
    if (!CAN_SEE(enemy, me) || !CAN_SEE_IN_ROOM(me))
	return 0;
    // We might be fighting someone we can't fight back against?
    if (enemy->query_prop(OBJ_M_NO_ATTACK))
	return 0;
    return 1;
}

int
find_valid_friends(object friend, object enemy)
{
    // Are we too stunned to help out?
    if (friend->query_prop(LIVE_I_STUNNED) ||
      friend->query_prop(LIVE_I_ATTACK_DELAY))
	return 0;
    // Can't be any help if we can't see can we?
    if (!CAN_SEE(friend, enemy) || !CAN_SEE_IN_ROOM(friend))
	return 0;
    // Are we even attacking this person?
    if (member_array(enemy, friend->query_enemy(-1)) == -1)
	return 0;
    return 1;
}

void
check_status(object me, object *friends, object *enemies, int type)
{

}

/* Function name: shove_attack
 * Description:   Two goblins team up against a player and try to
 *                shove them to the ground and stun them.
 * Arguments:     object me:       The goblin starting the attack.
 *                object enemy:    The poor sap getting the shove!
 *                object *friends: The group of friends helping me.
 */
int
shove_attack(object me, object enemy, object *friends)
{
    int hit;
    object helper;

    // No need to stun them again if they already are!
    if (enemy->query_prop(LIVE_I_STUNNED) ||
      enemy->query_prop(LIVE_I_ATTACK_DELAY))
	return 0;

    friends = filter(friends, &find_valid_friends(, enemy));

    if (!sizeof(friends))
	return 0;

    helper = ONE_OF(friends);
    hit = 2 * (me->query_stat(SS_DEX) + helper->query_skill(SS_SNEAK)) / 3 
    - enemy->query_skill(SS_AWARENESS);
    hit = MAX(60, MIN(10, hit));

    if (me->query_combat_object()->cb_tohit(-1, hit, enemy) < 0)
    {
	 enemy->catch_tell(me->query_The_name(enemy) +" attempted to "+
          "shove you to the ground while "+helper->query_the_name(enemy)+
          " was laying down behind you, in an effort to aid in your fall.\n");
	me->tell_watcher(QCTNAME(TO)+" attempts to shove "+ QTNAME(enemy)+
          " to the ground, while "+QTNAME(helper)+" lays down behind "+
	  QTNAME(enemy) +", but fails to do so.\n", enemy);      
    }
    else
    {
	enemy->catch_tell(me->query_The_name(enemy) +" manages to shove "+
          "you into "+helper->query_the_name(enemy)+", who had sneaked up "+
          "behind you, causing you to trip over "+HIM_HER(helper)+" and "+
          "fall helplessly to the ground!\n"); 
	me->tell_watcher(QCTNAME(TO)+" manages to shove "+ QTNAME(enemy)+
          " to the ground, with the help of "+QTNAME(helper)+", who had "+
	  "managed to sneak up behind "+QTNAME(enemy)+".\n", enemy);
	// Replace with a stun object.      
	enemy->add_attack_delay(10 + random(6));
    }
    // Stun the helper for a combat round for helping
    helper->add_attack_delay(5);
    return 1;
}

int
punch(object me, object enemy)
{
    return 1;
}


/* Function name: hack
 * Description:   A simple damage attack preformed with a weapon.
 * Arguments:     object me:       The goblin doing the hack
 *                object enemy:    The poor sap getting hacked at
 */
int
hack(object me, object enemy) 
{
    object *weapons = me->query_weapon(-1);
    int dt, hit, i, pen, skill, sz;
    string how;
    mixed *hitres;

    if (!(sz = sizeof(weapons)))
	return 0;
    i = -1;
    while(++i < sz)
    {
	hit += weapons[i]->query_hit();
	pen += weapons[i]->query_pen();
	skill += me->query_skill(Weapon_skills[weapons[i]->query_wt()]);
    }
    skill = skill / sz;
    hit = (hit / sz) + me->query_stat(SS_DEX) / 6;
    pen = (pen / sz) + me->query_stat(SS_STR) / 7;
    dt = weapons[0]->query_dt();
    if (me->query_combat_object()->cb_tohit(-1, hit, enemy) < 0)
    {
	enemy->catch_tell(me->query_The_name(enemy)+" takes a wild hack at "+
          "you with "+HIS_HER(me)+" "+COMPOSITE_WORDS(weapons->short())+
          " and misses you enitrely!\n");
	me->tell_watcher(QCTNAME(TO)+" takes a wild hack at "+QTNAME(enemy)+
          " with "+HIS_HER(me)+" "+COMPOSITE_WORDS(weapons->short())+
          " missing "+QTNAME(enemy)+" entirely!\n", enemy);
	return 1;
    }
    pen = F_PENMOD(pen, skill);
    hitres = enemy->hit_me(pen, dt, me, -1);
    switch(hitres[0])
    {
    case -1:
	if (dt == W_SLASH)
	    how = "unscratched";
	else if (dt == W_IMPALE)
	    how = "unharmed";
	else
	    how = "unhurt";
	break;
    case 0:
	if (dt == W_SLASH)
	    how = "unscratched";
	else if (dt == W_IMPALE)
	    how = "unharmed";
	else
	    how = "unhurt";
	break;
    case 1..10:
	if (dt == W_SLASH)
	    how = "lightly scratched";
	else if (dt == W_IMPALE)
	    how = "slightly hurt";
	else
	    how = "slightly winded";
	break;
    case 11..25:
	if (dt == W_SLASH)
	    how = "somewhat scratched";
	else if (dt == W_IMPALE)
	    how = "somewhat hurt";
	else
	    how = "fairly winded";
	break;
    case 26..45:
	if (dt == W_SLASH)
	    how = "deeply scratched";
	else if (dt == W_IMPALE)
	    how = "slightly pierced";
	else
	    how = "moderately bruised";
	break;
    case 46..70:
	if (dt == W_SLASH)
	    how = "painfully slashed";
	else if (dt == W_IMPALE)
	    how = "moderately pierced";
	else
	    how = "deeply bruised";
	break;
    case 71..90:
	if (dt == W_SLASH)
	    how = "badly slashed, with blood trickling from the wound,";
	else if (dt == W_IMPALE)
	    how = "deeply pierced, with blood trickling from the wound,";
	else
	    how = "badly crushed";
	break;
    default:
	if (dt == W_SLASH)
	    how = "horribly slashed, with blood pouring from the wound,";
	else if (dt == W_IMPALE)
	    how = "badly pierced, with blood pouring from the wound,";
	else
	    how = "on the verge of death";
    }
    enemy->catch_tell(me->query_The_name(enemy)+ " takes a wild hack at "+
      "you with "+HIS_HER(me)+" "+COMPOSITE_WORDS(weapons->short())+
      " striking your "+hitres[1]+" leaving you feeling "+how+
      " from the hack.\n");
    me->tell_watcher(QCTNAME(TO)+" takes a wild hack at "+QTNAME(enemy)+
      " with "+HIS_HER(me)+" "+COMPOSITE_WORDS(weapons->short())+
      " striking "+LANG_POSS(QTNAME(enemy))+" "+hitres[1]+" leaving "+
      HIM_HER(enemy)+" feeling "+how+" from the hack.\n", enemy);
    if (enemy->query_wiz_level())
	enemy->catch_tell("DAMAGE:  "+hitres[3]+"  PEN VALUE: "+pen+"\n");
    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

/* Function name: pummel
 * Description:   Goblins will all give the target a swift kick 
 *                while they are down on the ground and pretty much
 *                helpless :)
 * Arguments:     object me:       The goblin starting the attack.
 *                object enemy:   The poor sap getting the pummeling
 *                object *friends: The group of friends helping me.
 */
int
pummel(object me, object enemy, object *friends)
{
    object *attackers;
    int i = -1, pen = 0;
    string how;
    mixed *hitres;

    friends = filter(friends, &find_valid_friends(, enemy));
    if (!sizeof(friends))
	return 0;

    if (random(3))
	me->command("say "+ONE_OF(({"Ha kick em while they're down!!!", 
	      "Lets lay a beatin on this "+enemy->query_race_name()+"!",
	      "Go for the kidneys everyone!", "Time to kick some back!"})));

    if (sizeof(friends) > 3)
	attackers = ({friends[0], friends[1], friends[2]});
    else
	attackers = friends;
    attackers += ({me});
    while (++i < sizeof(attackers))
    {
	if (!random(4))
	    attackers[i]->command(ONE_OF(({"cackle", "grin at "+
		  OB_NAME(enemy), "say This will teach you to mess with us!",
		  "emote grins with delight.", "shout Die die die!!", 
		  "say I got first dibs on "+HIS_HER(enemy)+" corpse!"})));
	// See if we hit??
	if (attackers[i]->query_combat_object()->cb_tohit(-1,
	    attackers[i]->query_stat(SS_DEX) / 2, enemy) >= 0)
	    pen += attackers[i]->query_stat(SS_STR) / 6;
    }
    //  They attempted an attack so the attackers get a  
    //  small attack delay because they didn't call the attack.
    attackers -= ({me});
    attackers->add_attack_delay(5);

    // Use the goblins hunting skill (abilty to hunt in packs) for F_PENMOD
    pen = F_PENMOD(pen, me->query_skill(SS_HUNTING));

    hitres = enemy->hit_me(pen, W_BLUDGEON, me, -1, A_BACK);
    switch(hitres[0])
    {
    case -1:
	how = "unharmed";
	break;
    case 0:
	how = "relatively unharmed";
	break;
    case 1..10:
	how = "slightly hurt";
	break;
    case 11..25:
	how = "lightly bruised";
	break;
    case 26..45:
	how = "bruised";
	break;
    case 46..70:
	how = "bruised and battered";
	break;
    case 71..90:
	how = "heavily bruised and badly beaten";
	break;
    default:
	how = "nearly at deaths door";
    }
    enemy->catch_tell(me->query_The_name(enemy)+" with the help of "+
      desc_many_for(attackers, enemy)+" kick you repeatedly in the back "+
      "leaving you feeling "+how+" from the experience.\n");
    me->tell_watcher(QCTNAME(TO)+" with the help of "+desc_many(attackers)+
      " start to kick "+QTNAME(enemy)+" in the back leaving "+
      HIM_HER(enemy)+" feeling "+how +" from the experience.\n", enemy);
    if (enemy->query_wiz_level())
	enemy->catch_tell("DAMAGE:  "+hitres[3]+"  PEN VALUE: "+pen+"\n");
    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

int
wolf_attack(object rider, object enemy, object wolf)
{
    enemy->catch_tell("Wolf charged.\n");
    return 1;
}

int 
hack_many(object me, object *enemies)
{
    object *weapons = me->query_weapon(-1), *targets;
    int i, pen;

    if (!sizeof(weapons))
	return 0;

    // Can only do this attack with a slashing type weapon
    weapons = filter(weapons, &operator(==)(W_SLASH) @ &->query_dt());
    if (!sizeof(weapons))
	return 0;
    enemies = filter(enemies, &find_valid_enemies(, me));
    // If we don't have more than 1 enemy do not do this attack
    if (sizeof(enemies) < 1)
	return 0;

    if (sizeof(enemies) > 3)
    {
	i = -1;
	targets = allocate(3);
	while(++i < 3)
	{
	    targets[i] = ONE_OF(enemies);
	    enemies -= ({ targets[i] });
	} 
    }
    else
	targets = enemies;

    targets->catch_tell("Hack many.\n");
    return 1;
}

int
ordered_attack(object me, object *enemies, object *friends)
{

    return 1;
}

int
surround(object me, object enemy, object *friends)
{

    return 1;
}
