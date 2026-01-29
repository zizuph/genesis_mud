/*
 * Shanoga, 2021 May 19:
 *   Fixed shadow removal on unwield. Added the funtion
 *   "remove_kit_sword_shadow" which ensures that the
 *   correct shadow is removed.
 *   Previously was removing the most recently-added shadow
 *   rather than just the sword shadow.
 */
inherit "/std/shadow";

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

object gSword;

#define PARRY_CHANCE (500 / shadow_who->query_skill(SS_PARRY))


void set_sword(object sw)
{
    gSword = sw;
}


object query_sword()
{
    return gSword;
}


/* can't wield any other weapons */
/*
mixed wield(object weapon)
{
    if (weapon != gSword && gSword->query_wielded() == shadow_who)
    {
	return "The emerald set in the hilt of your "+gSword->short()+
	" suddenly flares up, casting a pale green glow along the "+
	"blade. You look with indifference at the "+weapon->short()+
	" you were about to wield, and realize you have no need for "+
	"it.\n";
    }

    return shadow_who->wield(weapon);
}
*/


/* If opponent is wielding a magical weapon, the sabre will show
* off more, trying to prove itself superior
*/
int query_not_attack_me(object who, int aid)
{
    object weapon, *weapons = who->query_weapon(-1);
    object combat_object = who->query_combat_object();
    int attack = combat_object->query_attack(aid);
    int magic = 0, i;
    string tmp;

    if (!attack)
	return shadow_who->query_not_attack_me(who, aid);

    if (!sizeof(weapons))
	return shadow_who->query_not_attack_me(who, aid);

    for (i = 0; i < sizeof(weapons); i++)
    {
	if (!weapons[i]->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	{
	    weapon = weapons[i];
	}
	else
	{
	    weapon = weapons[0];
	    magic = 1;
	}
    }

    if (!magic && random(PARRY_CHANCE *2))
	return shadow_who->query_not_attack_me(who, aid);

    if (magic && random(PARRY_CHANCE))
	return shadow_who->query_not_attack_me(who, aid);

    switch(random(13))
    {
    default:
	tmp = "A green blur fills your vision, and you realize "+
	"that your "+gSword->short()+" struck the "+weapon->short()+
	" of "+who->query_the_name(shadow_who)+", sending the "+
	"blow out wide. The sword pulses reassuringly, and you "+
	"regain your composure.";
	break;
    case 1..3:
	tmp = "On instinct, you bring your "+gSword->short()+" up, "+
	"knocking aside "+who->query_the_name(shadow_who)+"'s "+
	weapon->short()+".";
	break;
    case 4..6:
	tmp = "Without thinking, you raise your "+gSword->short()+
	", blocking "+who->query_the_name(shadow_who)+"'s "+
	weapon->short()+".";
	break;
    case 7..9:
	tmp = "With speed not your own, you parry aside "+
	who->query_the_name(shadow_who)+"'s "+weapon->short()+
	" with your "+gSword->short()+".";
	break;
    case 10..12:
	tmp = "Seemingly of its own accord, the "+gSword->short()+
	" flashes in front of you, averting the "+weapon->short()+
	" of "+who->query_the_name(shadow_who)+".";
    }

    shadow_who->catch_msg(tmp+"\n");
    who->catch_msg("A green blur flashes in front of you, knocking aside "+
      "your "+weapon->short()+".\n");
    tell_room(E(who), "A green blur flashes in front of "+QTNAME(shadow_who)+
      ", knocking aside "+QTNAME(who)+"'s "+weapon->short()+".\n",
      ({ who, shadow_who }));

    return 1;
}


