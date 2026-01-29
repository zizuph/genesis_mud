inherit "/std/shadow";
inherit "/cmd/std/command_driver";

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <files.h>
#include "/d/Krynn/open/sys/combat.h"

#define KNIGHT_I_MANEUVERED "_knight_i_maneuvered"
#define ROOM_I_ALLOW_STEED "_room_i_allow_steed"
#define ROOM_I_NO_ALLOW_STEED "_room_i_no_allow_steed"
#define RIDER_SUBLOC "_live_i_mounted"
object horse;

void ste_steed(object mount) { horse = mount; }
object query_steed() { return horse; }

string query_m_in()
{
    return "arrives astride a "+query_steed()->short()+".";
}

string query_m_out()
{
    return "rides "+POSSESSIVE(shadow_who)+" "+query_steed()->short();
}

void remove_object()
{
    query_steed()->remove_prop(OBJ_M_NO_ATTACK);
    query_steed()->unset_no_show_composite();
    query_steed()->set_rider(0);
    ::remove_object();
}

void emergency_dismount()
{
    if (P("rider_object", shadow_who))
	P("rider_object", shadow_who)->remove_object();

    remove_shadow();
}

varargs int move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int in,tmp,tired, a = 1;
    object room, here = E(shadow_who);

    horse = query_steed();

    if (!query_steed() || query_steed() == 0)
    {
	shadow_who->catch_tell("Your horse seems to have disappeared.\n");
	emergency_dismount();
	return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    }

    if (E(horse) != E(shadow_who))
    {
	shadow_who->catch_tell("Your horse seems to have disappeared.\n");
	horse->do_dismount();
	return 0;
    }

    if (!objectp(to_dest))
    {
	to_dest->whatever_the_heck_we_want();
	to_dest = find_object(to_dest);
    }

    room = to_dest;

    if (room->query_prop(ROOM_I_INSIDE))
    {
	if (!here->query_prop(ROOM_I_INSIDE))
	{
	    a = (room->query_prop(ROOM_I_ALLOW_STEED) ? 1 : 0);
	}
	else
	{
	    a = (room->query_prop(ROOM_I_NO_ALLOW_STEED) ? 0 : 1);
	}
    }

    if (!room->query_prop(ROOM_I_INSIDE) && room->query_prop(ROOM_I_NO_ALLOW_STEED))
	a = 0;

    if (!a)
    {
	shadow_who->catch_tell("Your horse may not enter there.\n");
	return 7;
    }

    if (random(shadow_who->query_skill(SS_RIDING) * 2) == 0)
    {
	tell_object(shadow_who,"You lose your balance and fall off your "+
	  query_steed()->short()+", landing with a thud.\n");
	tell_room(E(shadow_who), QCTNAME(shadow_who)+" falls off "+
	  POSSESSIVE(shadow_who)+" "+query_steed()->short()+", landing "+
	  "with a thud.\n",shadow_who);
	horse->command(query_verb());
	query_steed()->do_dismount();
	return 7;
    }

    if (!shadow_who->move_living(how, to_dest, dont_follow, no_glance))
    {

	if((tmp = shadow_who->query_encumberance_weight()) > 20)
	{
	    tired = E(shadow_who)->query_tired_exit(in+2);
	    tired = ((tmp > 80) ? (tired * 2) : tired);
	    if (horse->query_fatigue() < tired)
	    {
		tell_object(shadow_who,"Your "+horse->short()+" is too "+
		  "tired to continue.\n");
		return 7;
	    }
	}

	E(horse)->add_prop(ROOM_S_DIR, ({how, "horse"}));
	horse->move_living("M", to_dest, 1, 1);
    }
}

string query_race_name()
{
    if (calling_function() == "move_living")
	return "horse";
    else
	return shadow_who->query_race_name();
}

void add_fatigue(int f)
{
    query_steed()->add_fatigue(f);
}

object armour_check()
{
    object *armours = shadow_who->query_armour(-1);
    object arm;

    if (!armours || sizeof(armours) <= 0)
	return 0;

    return armours[random(sizeof(armours) - 1)];
}

public varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    object armour;
    int i, phurt;
    mixed *hitres;

    hitres = shadow_who->hit_me(wcpen, dt, attacker, attack_id);
    phurt = hitres[0];

    if (phurt >= 5 && random(shadow_who->query_skill(SS_MOUNTED_COMBAT) * 3) < phurt)
    {
	if (!random(10) && armour_check())
	{
	    armour = armour_check();

	    if ((armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR) && !random(3)) ||
	      (!armour->query_prop(OBJ_I_IS_MAGIC_ARMOUR) && !random(2)) ||
	      armour->query_condition() != 0)
	    {
		shadow_who->catch_tell("As you are struck, you fall heavily to the "+
		  "ground and your "+armour->short()+" breaks!\n");
		tell_room(E(shadow_who), "As "+PRONOUN(shadow_who)+" is struck, "+
		  PRONOUN(shadow_who)+" falls heavily to the ground, breaking "+
		  POSSESSIVE(shadow_who)+" "+armour->short()+"!\n", shadow_who);
		armour->remove_broken(1);
		query_steed()->do_dismount();
	    }
	    else
	    {
		i = random(2) + 1;
		shadow_who->catch_tell("As you are struck, you fall heavily to the "+
		  "ground, damaging your "+armour->short()+".\n");
		tell_room(E(shadow_who), "As "+QTNAME(shadow_who)+" is struck, "+
		  PRONOUN(shadow_who)+" falls heavily to the ground, damaging "+
		  POSSESSIVE(shadow_who)+" "+armour->short()+".\n", shadow_who);
		armour->set_condition(i);
		query_steed()->do_dismount();
	    }
	}
	else
	{
	    shadow_who->catch_tell("As you are struck, you lose your balance "+
	      "and fall from your "+query_steed()->short()+".\n");
	    tell_room(E(shadow_who), "As "+PRONOUN(shadow_who)+" is struck, "+
	      QTNAME(shadow_who)+" loses "+POSSESSIVE(shadow_who)+" balance "+
	      "and tumbles from "+POSSESSIVE(shadow_who)+" "+
	      query_steed()->short()+".\n", shadow_who);
	    query_steed()->do_dismount();
	}
    }
    return hitres;
}

int maneuver(string str)
{
    object me = shadow_who, st = query_steed();
    object *enemies, *tmp;
    int duration, i;

    NF("You are unable to do that presently.\n");
    if (me->query_prop(KNIGHT_I_MANEUVERED))
	return 0;

    if (sizeof(st->query_enemy(-1)))
	enemies = st->query_enemy(-1);

    NF("Your "+st->short()+" is not under attack, there is no need.\n");
    if (!enemies)
	return 0;

    duration = (me->query_stat(SS_WIS) +
      me->query_skill(SS_RIDING) + me->query_skill(SS_MOUNTED_COMBAT))
    / 2;

    if (duration > 100)
	duration = 100;

    if (sizeof(enemies) >= 4)
    {
	me->catch_tell("The onslaught is too overwhelming, you "+
	  "cannot possibly save your steed from so many attackers "+
	  "at once.\n");
	me->add_prop(KNIGHT_I_MANEUVERED, 1);
	set_alarm(60.0, 0.0, "reset_maneuver", me);
	return 1;
    }

    if (duration - sizeof(enemies) * 25 <= 0)
    {
	me->catch_msg("You fail to maneuver your steed safely out "+
	  "of harm's way.\n");
	me->add_prop(KNIGHT_I_MANEUVERED, 1);
	set_alarm(60.0, 0.0, "reset_maneuver", me); 
	return 1;
    }

    me->add_prop(KNIGHT_I_MANEUVERED, 1);
    st->add_prop(OBJ_M_NO_ATTACK, "As you move to attack the "+
      st->short()+", "+QTNAME(me)+" whirls the steed around to "+
      "face you.\n");
    me->catch_tell("Recalling your training of mounted combat, you "+
      "spur your "+st->short()+" forward and whirl "+POSSESSIVE(st)+
      " around to face "+POSSESSIVE(st)+" assailents.\n");
    tmp = enemies;
    tmp += ({ me });
    tell_room(E(me), QCTNAME(me)+" spurs "+POSSESSIVE(me)+" "+
      st->short()+" forward and whirls around, facing "+
      POSSESSIVE(me)+" assailants head on.", tmp);

    for (i = 0; i < sizeof(enemies); i++)
    {
	enemies[i]->stop_fight(st);
	st->stop_fight(enemies[i]);
	enemies[i]->attack_object(me);
	enemies[i]->catch_tell(me->query_The_name(enemies[i])+
	  " spurs "+POSSESSIVE(me)+" "+st->short()+" forward and "+
	  "whirls around, facing you head on.\n");
    }

    set_alarm(60.0, 0.0, "reset_maneuver", me);
    set_alarm(itof(duration / 2), 0.0, "remove_maneuver", st);
    return 1;
}

void remove_maneuver(object st)
{
    st->remove_prop(OBJ_M_NO_ATTACK);
}

void reset_maneuver(object ob)
{
    ob->remove_prop(KNIGHT_I_MANEUVERED);
    ob->catch_tell("You may try to maneuver your horse out of "+
      "the range of attackers again, if you wish.\n");
}

object findcorpse(string killed, object killer)
{
    object *stuff;
    int i, index, most_recent, ob_num;

    stuff = all_inventory(environment(killer));
    /* get all corpses */
    stuff = filter(stuff, &operator(==)(CORPSE_OBJECT) @
      &function_exists("create_container"));
    /* get all corpses with the right name */
    stuff = filter(stuff, &->id("corpse of " + killed));
    /* get all corpses killed by the right person */
    stuff = filter(stuff, &operator(==)(killer->query_real_name()) @
      &operator([])(,0) @ &->query_prop(CORPSE_AS_KILLER));

    most_recent = 0;
    index = -1;
    for (i = 0; i < sizeof(stuff); i++)
    {
	if (ob_num = atoi(OB_NUM(stuff[i])) > most_recent)
	{
	    most_recent = ob_num;
	    index = i;
	}
    }

    if (index > -1)
    {
	return stuff[index];
    }

    return 0;
}

void sever_limb(string piece, string killed, object killer)
{
    object corpse, part, me = shadow_who;
    string *str, *message, tmp;
    int i;

    /* DEBUGGING ONLY */
    find_living("morrigan")->catch_msg("Hdesc - "+piece+"\n");

    corpse = P("corpse", E(shadow_who));
    if (corpse->query_npc())
	corpse = 0;

    /* corpse = findcorpse(killed, killer); */
    find_living("morrigan")->catch_msg("Corpse - "+(corpse ? "Yes" : "No")+"\n");

    switch(piece)
    {
    case "head":
	corpse->set_short("headless "+corpse->query_short());
	corpse->remove_leftover("scalp");
	corpse->remove_leftover("skull");
	part = clone_object("/std/leftover");
	part->leftover_init("head", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    case "legs":
	corpse->set_short("legless "+corpse->query_short());
	corpse->remove_leftover("thighbone");
	part = clone_object("/std/leftover");
	part->leftover_init("leg", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    case "right arm":
	corpse->set_short("armless "+corpse->query_short());
	part = clone_object("/std/leftover");
	part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    case "left arm":
	corpse->set_short("armless "+corpse->query_short());
	part = clone_object("/std/leftover");
	part->leftover_init("arm", corpse->query_prop(CORPSE_S_RACE));
	part->move(E(corpse));
	break;
    }
    return;
}

object query_kweapon(object liv)
{
    object *wielded_weapons;
    object wep, wep1, wep2;
    int i, wepstat, wep1stat, wep2stat, j;
    wielded_weapons = liv->query_weapon(-1);

    if (sizeof(wielded_weapons) == 1)
    {
	for (i = 0; i < sizeof(wielded_weapons); i++)
	    wep = wielded_weapons[i];
    }

    if (sizeof(wielded_weapons) == 2)
    {
	wep1 = wielded_weapons[0];
	wep2 = wielded_weapons[1];
    }

    if ((wep1) && (wep2))
    {
	wep1stat = ((wep1->query_hit()+wep1->query_pen()) / 2);
	wep2stat = ((wep2->query_hit()+wep2->query_pen()) / 2);

	if (wep1stat >= wep2stat)
	{
	    return wep1;
	}
	else
	{
	    return wep2;
	}
    }

    if (wep)
    {
	return wep;
    }
}

/* Added by Morrigan 11/14/1996 to make two-handed fighting more realistic */
/* See /d/Krynn/vin/knight/text/TAX_CHART for more information             */

object *query_two_weapons(object liv)
{
    object sup_wep, inf_wep;
    int i = random(100) + 1;
    int j, pr, sen;
    object medal = P("pal_med", shadow_who);

    pr = medal->query_primary();

    if (pr == 1)
    {
	sup_wep = liv->query_weapon(W_LEFT);
	inf_wep = liv->query_weapon(W_RIGHT);
    }
    else
    {
	sup_wep = liv->query_weapon(W_RIGHT);
	inf_wep = liv->query_weapon(W_LEFT);
    }

    if (liv->query_knight_level() == 3)
	j = (liv->query_skill(20) + 3 * liv->query_knight_sublevel() -
	  random(liv->query_knight_sublevel()));
    else if (liv->query_knight_level() > 3)
    {
	if (liv->query_knight_sublevel() < 10)
	    j = (liv->query_skill(20) + 30 - random(10));
	else
	    j = (liv->query_skill(20) + 3 * liv->query_knight_sublevel() -
	      random(liv->query_knight_sublevel()));
    }
    else if (liv->query_knight_level() == 2)
    {
	if (liv->query_skill(20) > 50)
	    sen = 50;
	else
	    sen = liv->query_skill(20);
	j = (liv->query_skill(20) + 2 * liv->query_knight_sublevel() -
	  random(liv->query_knight_sublevel()));
    }

    if (pr = 2)
	if (random(2))
	    return ({ sup_wep, inf_wep });
	else
	    return ({ inf_wep, sup_wep });

    if (i < j)
	return ({ sup_wep, inf_wep });
    else
	return ({ inf_wep, sup_wep });
}

int charge_special(string str)
{
    object ob, *obj, weapon, *weapons, horse = query_steed();
    object liv = TP, medal = P("pal_med", TP);
    string how;
    int tmp;

    if (!str)
	ob = liv->query_attack();
    else 
    {
	obj = parse_this(str, "%l");
	if (sizeof(obj) > 0)
	    ob = obj[0];
	if (sizeof(obj) > 1) 
	{
	    NF("Choose one enemy to attack.\n");
	    return 0;
	}
    }

    how = c_can_attack(ob, query_verb());
    if (stringp(how)) 
    {
	NF(how);
	return 0;
    }

    if (tmp = liv->query_prop("_kcharge_resetting"))
    {
	NF("You are not ready to charge again.\n");
	/* Safeguard to fix locked special attacks */
	if (time() > tmp + 20)
	    set_alarm(60.0, 0.0, "reset_charge_special", liv);
	return 0;
    }

    if (liv->query_prop(LIVE_I_ATTACK_DELAY) || liv->query_prop(LIVE_I_STUNNED))
    {
	NF("You are too stunned to charge.\n");
	return 0;
    }

    if (tmp = liv->query_prop("_kcharge_preparing")) 
    {
	NF("You are already preparing to charge.\n");
	/* Safeguard to fix locked special attacks */
	if (time() > tmp + 20)
	{
	    NF("You are not ready to charge again.\n");
	    liv->remove_prop("_kcharge_preparing");
	    liv->add_prop("_kcharge_resetting",time());
	    set_alarm(60.0,0.0, "reset_charge_special", liv);
	}
	return 0;
    }      

    NF("You have already engaged the "+ob->query_the_name(liv)+".\n");
    if (member_array(liv, ob->query_enemy(-1)) >= 0)
	return 0;

    NF("You are already engaged in battle, and cannot charge.\n");
    if (liv->query_attack())
	return 0;

    if (sizeof(liv->query_weapon(-1)) == 2)
	weapons = query_two_weapons(liv);
    else
	weapon = query_kweapon(liv);

    if (!weapon && !weapons)
    {
	NF("You cannot charge without a weapon.\n");
	return 0;
    }

    if (!weapon)
    {
	if (medal->query_primary() == 0)
	    weapon = liv->query_weapon(W_RIGHT);
	else if (medal->query_primary() == 1)
	    weapon = liv->query_weapon(W_LEFT);
	else
	    weapon = weapons[random(2)];
    }

    liv->add_prop("_kcharge_preparing", time());
    set_alarm(4.0, 0.0, "do_charge_prespecial1", ob, liv, horse);

    say(QCTNAME(liv)+" salutes "+QTNAME(ob)+" in the traditional Solamnic "+
      "manner with "+POSSESSIVE(liv)+" "+weapon->short()+
      ", then spurs "+POSSESSIVE(liv)+" "+horse->short()+" forward, "+
      "snapping the reigns.\n", ({ ob, liv }));
    ob->catch_tell(liv->query_The_name(ob)+" salutes you in the traditional "+
      "Solamnic manner with "+POSSESSIVE(liv)+" "+weapon->short()+
      ", then spurs "+POSSESSIVE(liv)+" "+horse->short()+
      " forward, snapping the reigns.\n");
    liv->catch_tell("You salute "+ob->query_the_name(liv)+" in the tradi"+
      "tional Solamnic manner with your "+weapon->short()+
      ", then spur your "+horse->short()+" forward, snapping the reigns.\n");
    return 1;
}

void do_charge_prespecial1(object them, object me, object horse)
{
    if (!present(them, environment(me))) 
    {
	me->catch_tell("You are unable to charge your target.\n");
	me->remove_prop("_kcharge_preparing");
	return;
    }

    if (horse->query_rider() != me)
    {
	me->catch_tell("Your charge comes to an abrupt halt, as you are no "+
	  "longer riding a horse!\n");
	me->remove_prop("_kcharge_preparing");
	return;
    }

    me->catch_tell("Your adrenaline begins to surge as you slap the reigns "+
      "back and forth as your "+horse->short()+" gains momentum.\n");
    them->catch_tell(me->query_The_name(them)+" slaps the reigns back and forth as "+
      POSSESSIVE(me)+" "+horse->short()+" gains momentum.\n");
    me->tell_watcher(QCTNAME(me)+" slaps the reigns back and forth as "+
      POSSESSIVE(me) + " " + horse->short() + " gains momentum.\n", them);
    set_alarm(4.0, 0.0, "do_charge_prespecial2", them, me, horse);
    return;
}

void do_charge_prespecial2(object ob, object liv, object horse)
{
    if (!present(ob, environment(liv))) 
    {
	liv->catch_tell("You are unable to charge your target.\n");
	liv->remove_prop("_kcharge_preparing");
	return;
    }

    if (horse->query_rider() != liv)
    {
	liv->catch_tell("Your charge comes to an abrupt halt, as you are no "+
	  "longer riding a horse!\n");
	liv->remove_prop("_kcharge_preparing");
	return;
    }

    liv->catch_tell("You lean forward in the saddle as your "+horse->short()+
      " thunders toward "+ob->query_the_name(liv)+". Preparing yourself for "+
      "the impact, you shout out a Solamnic battlecry, barely audible over "+
      "the earth-shaking rumble of your steed!\n");
    ob->catch_tell("The ground beneath your feet rumbles as "+
      liv->query_the_name(ob)+" thunders toward you, astride "+POSSESSIVE(liv)+
      " "+horse->short()+"! You feel fear creep over you as "+PRONOUN(liv)+
      " shouts out a Solamnic battlecry.\n");
    liv->tell_watcher("The ground rumbles beneath your feet as "+QTNAME(liv)+
      " thunders toward "+QTNAME(ob)+", astride "+POSSESSIVE(liv)+" "+
      horse->short()+". Leaning forward in the saddle, "+QTNAME(liv)+" shouts "+
      "out a Solamnic battlecry!\n", ob);
    set_alarm(4.0, 0.0, "do_charge_special", ob, liv, horse);
    return;
}

void do_charge_special(object ob, object liv)
{
    mixed hitresult;
    object weapon, horse;
    object *weapons;
    int hitres, weaponmod, statmod, pen, skill, weaponstat, levmod;
    int rcry, rcry2, horsemod;
    string tar, att, aud, cry, hdesc, *dam, str;
    int i = random(2);

    tar = "";
    att = "";
    aud = "";

    if (!present(ob, environment(liv))) 
    {
	write("You are unable to charge your target.\n");
	liv->remove_prop("_kcharge_preparing");
	return;
    }

    if (sizeof(liv->query_weapon(-1)) == 2)
    {
	weapons = query_two_weapons(liv);
	weapon = weapons[0];
    }
    else
	weapon = query_kweapon(liv);

    if (!weapon && !weapons)
    {
	write("Congratulations, you charged into battle without a weapon!\n");
	liv->remove_prop("_kcharge_preparing");
	return;
    }

    if (ob->query_prop(LIVE_I_NO_BODY) && !weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
	liv->catch_msg("Your "+weapon->short()+" passes through "+QTNAME(ob)+
	  ", leaving "+OBJECTIVE(ob)+" unharmed.\n");
	ob->catch_msg(QCTNAME(liv)+"'s "+weapon->short()+" passes through you, "+
	  "leaving you unharmed.\n");
	liv->tell_watcher(QCTNAME(liv)+"'s "+weapon->short()+" passes through "+
	  QTNAME(ob)+", leaving "+OBJECTIVE(ob)+" unharmed.\n");
	liv->remove_prop("_kcharge_preparing");
	liv->add_prop("_kcharge_resetting", time());
	set_alarm(60.0, 0.0, "reset_charge_special", liv);
	return;
    }

    switch(liv->query_knight_level)
    {
    case 5:
	if (liv->query_knight_sublevel() == 11)
	    levmod = 11;
	else
	    levmod = 10;
	break;
    case 4:
	if (liv->query_knight_sublevel() == 11)
	    levmod = 11;
	else
	    levmod = 10;
	break;
    case 3:
	levmod = liv->query_knight_sublevel();
	break;
    case 2:
	levmod = (liv->query_knight_sublevel() / 2);
	break;
    case 1:
	levmod = (liv->query_knight_sublevel() / 2);
	break;
    default:
	levmod = 0;
	break;
    }

    horse = query_steed();

    /* Weapon stat formula */
    weaponstat = ((weapon->query_hit()+weapon->query_pen()) / 2);
    if (weapon->query_wt() == W_POLEARM)
	weaponmod = (weaponstat * 3 / 2);
    else
	weaponmod = (weaponstat * 10 / 8);

    /* Stat formula */
    statmod = ((liv->query_stat(SS_STR)*2 + liv->query_stat(SS_WIS) + 
	liv->query_stat(SS_DIS))/8);

    /* Stat cap, currently at 200 (perhaps to be lowered?) */
    if (statmod >= 100)
	statmod = 100;

    /* Final formula */
    skill = TP->query_skill(SS_MOUNTED_COMBAT) + 25;
    pen = (statmod + weaponmod) / 2 + levmod * 2+20;
    hitres = F_PENMOD(pen, skill);
    hitresult = ob->hit_me(hitres, weapon->query_ht(), liv, -1);
    liv->attack_object(ob);
    hdesc = hitresult[1];

    switch(hitresult[0])
    {
    case 0:
	att = "Your attempt to strike "+ob->query_the_name(liv)+" with your "+
	weapon->short()+" misses. You tug on the reigns of your "+horse->short()+
	", turning to face your foe.";
	tar = liv->query_The_name()+"'s attempt to strike you with "+POSSESSIVE(liv)+
	" "+weapon->short()+" misses. "+C(PRONOUN(liv))+" tugs on the reigns "+
	"of "+POSSESSIVE(liv)+" "+horse->short()+", turning to face you.";
	aud = QCTNAME(liv)+"'s attempt to strike "+QTNAME(ob)+" with "+POSSESSIVE(liv)+
	" "+weapon->short()+" misses. "+C(PRONOUN(liv))+" tugs on the reigns "+
	"of "+POSSESSIVE(liv)+" "+horse->short()+", turning to face "+QTNAME(ob)+".";
	break;
    case 1..5:
	att = "As your "+horse->short()+" bears down upon "+ob->query_the_name(liv)+
	", you strike "+POSSESSIVE(ob)+" "+hdesc+" with a glancing blow of your "+
	weapon->short()+".";
	tar = "As "+POSSESSIVE(liv)+" "+horse->short()+" bears down upon you, "+
	liv->query_the_name(ob)+" strikes your "+hdesc+" with a glancing blow of "+
	POSSESSIVE(liv)+" "+weapon->short()+".";
	aud = "As "+POSSESSIVE(liv)+" "+horse->short()+" bears down upon "+
	QTNAME(ob)+", "+QTNAME(liv)+" strikes "+POSSESSIVE(ob)+" "+hdesc+
	" with a "+"glancing blow of "+POSSESSIVE(liv)+" "+weapon->short()+".";
	break;
    case 6..20:
	att = "The rumbling of the ground beneath your "+horse->short()+"'s feet "+
	"nearly drowns out the sound of the impact as you score a moderate "+
	"hit on the "+hdesc+" of "+ob->query_the_name(liv)+" with your "+
	weapon->short()+".";
	tar = "The rumbling of the ground beneath your feet nearly drowns out the "+
	"sound of the impact as "+liv->query_the_name(ob)+" scores a moderate "+
	"hit on your "+hdesc+" with "+POSSESSIVE(ob)+" "+weapon->short()+".";
	aud = "The rumbling of the ground beneath your feet nearly drowns out the "+
	"sound of the impact as "+QTNAME(liv)+" scores a moderate hit on the "+
	hdesc+" of "+QTNAME(ob)+" with "+POSSESSIVE(liv)+" "+weapon->short()+".";
	break;
    case 21..35:
	att = "Weapon meets foe as you heavily wound "+ob->query_the_name(liv)+
	"'s "+hdesc+" with your "+weapon->short()+", the momentum of your "+
	horse->short()+" lending its strength to the blow.";
	tar = liv->query_The_name(ob)+" heavily wounds your "+hdesc+" with "+
	POSSESSIVE(liv)+ " "+weapon->short()+", the momentum of "+POSSESSIVE(liv)+
	" "+horse->short()+" lending its strength to the blow.";
	aud = QCTNAME(liv)+" heavily wounds "+QTNAME(ob)+"'s "+hdesc+" with "+
	POSSESSIVE(liv)+" "+weapon->short()+" as the two collide, the momentum "+
	"of "+QTNAME(liv)+"'s "+horse->short()+" lending its strength to the "+
	"blow.";
	break;
    case 36..50:
	att = "Your "+horse->short()+" charges by "+ob->query_the_name(liv)+
	", and you land a perfectly placed blow on "+POSSESSIVE(ob)+" "+
	hdesc+" with your "+weapon->short()+", wounding "+OBJECTIVE(ob)+
	" badly.";
	tar = liv->query_The_name(ob)+"'s "+horse->short()+" charges by you, "+
	"and "+PRONOUN(liv)+" lands a perfectly placed blow on your "+hdesc+
	" with "+POSSESSIVE(liv)+" "+weapon->short()+", wounding you badly.";
	aud = QCTNAME(liv)+"'s "+horse->short()+" charges by "+QTNAME(ob)+", "+
	"and "+PRONOUN(liv)+" lands a perfectly placed blow on "+QTNAME(ob)+
	"'s "+hdesc+" with "+POSSESSIVE(liv)+" "+weapon->short()+", wounding "+
	OBJECTIVE(ob)+" badly.";
	break;
    case 51..100:
	att = "Your thundering "+horse->short()+" reaches "+ob->query_the_name(liv)+
	", and your "+weapon->short()+" smashes into "+POSSESSIVE(ob)+" "+hdesc+
	" with a tremendous thud and devastating power.";
	tar = liv->query_The_name(ob)+"'s thundering "+horse->short()+" reaches "+
	"you, and "+POSSESSIVE(liv)+" "+weapon->short()+" smashes into your "+
	hdesc+" with a tremendous thud and devastating power.";
	aud = QCTNAME(liv)+"'s thundering "+horse->short()+" reaches "+QTNAME(ob)+
	", and "+POSSESSIVE(liv)+" "+weapon->short()+" smashes into "+
	POSSESSIVE(ob)+" "+hdesc+" with a tremendous thud and devastang power.";
	break;
    }

    rcry = random(3);
    if (!rcry && hitresult[0] >= 20)
    {
	switch(random(10))
	{
	case 0:
	    cry = "For Vingaard and the Orders!";
	    break;
	case 1:
	    switch(liv->query_knight_level())
	    {
	    case 5:
		cry = "For the Order of the Rose!";
		break;
	    case 4:
		cry = "For the Order of the Sword!";
		break;
	    case 3:
		cry = "For the Order of the Crown!";
		break;
	    default:
		cry = "For the Knighthood!";
		break;
	    }
	    break;
	case 2:
	    switch(liv->query_knight_level())
	    {
	    case 4:
		cry = "Kiri-Jolith!";
		break;
	    case 3:
		cry = "Habbakuk!";
		break;
	    default:
		cry = "Paladine!";
		break;
	    }
	    break;
	case 3:
	    cry = "By the Measure!";
	    break;
	case 4:
	    cry = "For Vingaard!";
	    break;
	case 5:
	    cry = "By the Oath and the Measure!";
	    break;
	case 6:
	    cry = "Victory to the Knighthood!";
	    break;
	case 7:
	    cry = "For Solamnia!";
	    break;
	case 8:
	    cry = "For the Knighthood!";
	    break;
	case 9:
	    switch(liv->query_knight_level())
	    {
	    case 5:
		cry = "In the name of justice!";
		break;
	    case 4:
		cry = "In the name of courage!";
		break;
	    case 3:
		cry = "In the name of honour!";
		break;
	    default:
		cry = "In the name of Solamnia!";
		break;
	    }
	    break;
	}
	if (!TP->query_prop("_i_quiet_knight"))
	    liv->command("$shout "+cry);
    }

    liv->remove_prop("_kcharge_preparing");
    if (liv->query_wiz_level())
	liv->catch_msg("Hitresult = "+hitresult[0]+" : Damage = "+hitresult[3]+"\n");
    liv->add_prop("_kcharge_resetting", time());
    set_alarm(60.0, 0.0, "reset_charge_special", liv);

    switch(weapon->query_wt())
    {
    case W_SWORD:
	str = "slashes into";
	break;
    case W_AXE:
	str = "tears into";
	break;
    case W_KNIFE:
	str = "slices into ";
	break;
    case W_POLEARM:
	str = "impales";
	break;
    default:
	str = "crushes";
    }

    find_living("morrigan")->catch_tell("Hdesc - "+hdesc+"\n");
    i = ob->query_hp();

    if (i <= 0)
    {
	if (weapon->query_wt() == W_AXE || weapon->query_wt() == W_SWORD &&
	  hdesc != "body")
	{   
	    liv->catch_tell("The thundering crescendo of your "+horse->short()+" reaches "+
	      "its peak as you collide with "+ob->query_the_name(liv)+" in a deafening "+
	      "explosion of sound. Aided by your tremendous momentum, your "+weapon->short()+
	      " slices "+ob->query_the_name(liv)+"'s "+hdesc+" from "+
	      POSSESSIVE(ob)+" body.\n");
	    ob->catch_tell("The thundering crescendo of "+liv->query_the_name(ob)+"'s "+
	      horse->short()+" reaches its peak as "+PRONOUN(liv)+" collides with you "+
	      "in a deafening explosion of sound. Aided by "+POSSESSIVE(liv)+" tremendous "+
	      "momentum, "+POSSESSIVE(liv)+" "+weapon->short()+" slices your "+
	      hdesc+" from your body.\n");
	    liv->tell_watcher("The thundering crescendo of "+QTNAME(liv)+"'s "+horse->short()+
	      " reaches its peak as "+PRONOUN(liv)+" collides with "+QTNAME(ob)+"in a "+
	      "deafening explosion of sound. Aided by "+POSSESSIVE(liv)+" tremendous "+
	      "momentum, "+POSSESSIVE(liv)+" "+weapon->short()+" slices "+
	      QTNAME(ob)+"'s "+hdesc+" from "+POSSESSIVE(ob)+" body.\n", ({ ob }));
	    ob->do_die(liv);
	    sever_limb(hdesc, ob->query_real_name(), liv);
	    return;
	}
	else
	{
	    liv->catch_tell("The thundering crescendo of your "+horse->short()+" reaches "+
	      "its peak as you collide with "+ob->query_the_name(liv)+" in a deafening "+
	      "explosion of sound. Aided by your tremendous momentum, your "+weapon->short()+
	      " "+str+" "+ob->query_the_name(liv)+"'s "+hdesc+".\n");
	    ob->catch_tell("The thundering crescendo of "+liv->query_the_name(ob)+"'s "+
	      horse->short()+" reaches its peak as "+PRONOUN(liv)+" collides with you "+
	      "in a deafening explosion of sound. Aided by "+POSSESSIVE(liv)+" tremendous "+
	      "momentum, "+POSSESSIVE(liv)+" "+weapon->short()+" "+str+" your "+hdesc+".\n");
	    liv->tell_watcher("The thundering crescendo of "+QTNAME(liv)+"'s "+horse->short()+
	      " reaches its peak as "+PRONOUN(liv)+" collides with "+QTNAME(ob)+"in a "+
	      "deafening explosion of sound. Aided by "+POSSESSIVE(liv)+" tremendous "+
	      "momentum, "+POSSESSIVE(liv)+" "+weapon->short()+ " "+str+" "+QTNAME(ob)+"'s "+
	      hdesc+".\n", ob);
	    ob->do_die(liv);
	    return;
	}

    }
    liv->catch_tell(att+"\n");
    ob->catch_tell(tar+"\n");
    liv->tell_watcher(aud+"\n", ob);

    return;
}

void
reset_charge_special(object liv)
{
    liv->catch_msg("\nYour steed is ready to charge again.\n\n");
    liv->remove_prop("_kcharge_resetting");
}

