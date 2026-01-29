inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>

inherit IM_TELL_FILE;
inherit IM_MESSAGE_FILE;

#define A_BITE	  0
#define A_LFCLAW  1
#define A_RFCLAW  2
#define A_LBCLAW  3
#define A_RBCLAW  4
#define A_LFKNEE  5
#define A_RFKNEE  6
#define A_LBKNEE  7
#define A_RBKNEE  8
#define A_TAIL	  9
#define A_HORNS  10

#define H_BODY	  0
#define H_BACK	  1
#define H_HEAD	  2
#define H_LFFOOT  3
#define H_RFFOOT  4
#define H_LBFOOT  5
#define H_RBFOOT  6
#define H_TAIL	  7
#define H_BREAST  8
#define H_SPOT	  9


create_creature() {
    set_name("dragon");
    set_race_name("dragon");
    set_short("@@my_short@@");
    set_long("@@my_long@@");

    add_item("nostrils",
	     "They are about 3 feet wide, each. Out of them comes fire and "+
	     "sulfur. Yuck! It smells terrible! Let's get out of here, eh?\n");

    add_prop(CONT_I_WEIGHT, 50000000); /* 50 tons */
    add_prop(CONT_I_VOLUME, 10000000);
    set_stats(
	({ 99, 99, 99, 99, 99, 99 }) ); /* Don't mess with this one */

    set_hp(100000);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE,	45);
    set_skill(SS_PARRY,        100);
    set_skill(SS_AWARENESS,	90);
    set_skill(SS_BLIND_COMBAT, 100);

    set_attack_unarmed(A_BITE,	  40,  90, W_IMPALE,  10, "jaws");
    set_attack_unarmed(A_LFCLAW,  80,  30, W_SLASH,    8, "left front claw");
    set_attack_unarmed(A_RFCLAW,  80,  30, W_SLASH,    8, "right front claw");
    set_attack_unarmed(A_LBCLAW,  50,  30, W_SLASH,    7, "left back claw");
    set_attack_unarmed(A_RBCLAW,  50,  30, W_SLASH,    7, "right back claw");
    set_attack_unarmed(A_LFKNEE,  70,  45, W_BLUDGEON, 5, "left front knee");
    set_attack_unarmed(A_RFKNEE,  70,  45, W_BLUDGEON, 5, "right front knee");
    set_attack_unarmed(A_RFKNEE,  60,  85, W_BLUDGEON, 5, "left back knee");
    set_attack_unarmed(A_RFKNEE,  60,  85, W_BLUDGEON, 5, "right back knee");
    set_attack_unarmed(A_TAIL,	 100,  99, W_SLASH,   30, "tail");
    set_attack_unarmed(A_HORNS,  130, 200, W_IMPALE,  10, "horns");

    set_hitloc_unarmed(H_BODY,	 100,		      20, "body");
    set_hitloc_unarmed(H_BACK,	  80,		       5, "back");
    set_hitloc_unarmed(H_HEAD, ({ 50, 80, 100 }),      5, "head");
    set_hitloc_unarmed(H_LFFOOT,  50,		       8, "left front foot");
    set_hitloc_unarmed(H_RFFOOT,  50,		       8, "right front foot");
    set_hitloc_unarmed(H_LBFOOT,  50,		       7, "left back foot");
    set_hitloc_unarmed(H_RFFOOT,  50,		       7, "right back foot");
    set_hitloc_unarmed(H_TAIL,	  90,		      18, "tail");
    set_hitloc_unarmed(H_BREAST, 200,		      20, "breast");
    set_hitloc_unarmed(H_SPOT,	   1,		       2, "weak spot");

    set_act_time(10);
    add_act("@@do_growl@@");

/*    set_aggressive(1);
      set_attack_chance(100); */

    add_prop(NPC_I_NO_LOOKS, 1);
   set_alignment(-777);
}

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, 
	   int dt, int phit, int dam)
{
    string wepstr = query_combat_object()->cb_attack_desc(aid);

    return message(TO, enemy, dt, hdesc, phurt, wepstr);
}

string
query_nonmet_name() { return "red dragon"; }

int
is_home()
{
    return ENV(TO) && ENV(TO)->query_dragons_lair();
}

string
my_short()
{
    if(is_home())
	return "sleeping red dragon";
    else
	return "angry fuming red dragon";
}


string
my_long()
{
    if(is_home())
	return
	  "A dragon, fifty yards long, lies here sleeping in a huge room. "+
	  "Fire and sulfur streams out of its big nostrils as it breathes. "+
	  "It grunts and stirs asleep, but if you value your life, you "+
	  "should not disturb it. Instead of passing it, consider "+
	  "retreating slowly to the south, through the opening. It looks "+
	  "like there is an opening northwards too, behind the dragon, "+
	  "but I do not advice you to try to go there!\n";
    else
	return
	  "A huge dragon, fifty yards long, is in the room in which you "+
	  "are standing!! Fire and sulfur streams out of its big nostrils "+
	  "as it breathes. Wow if you are not prepared of its stunning "+
	  "breath and pray that it is not in an ill mood!!\n";
}

string
do_growl()
{
    switch(random(4)) {
	case 0:
	    return
		"The dragon twists and wriggles, and expels some plaintive growls, "+
		"but let you pass unhindered. Still, if I were you, I wouldn't tempt "+
		"your luck by walking here too much.";
	case 1:
	    return
		"The dragon snorls while it slowly opens one of its eyes!";
	case 2:
	    return
		"The dragon slaps his tail while sleeping loudly.\n";
	case 3:
	    return
		"The dragon coughs out a stinking stench of sulphur!!";
    }
}

void
do_fry()
{
    object *victim = FILTER_LIVE(all_inventory(ENV(TO))) - ({ TO });
    object *tmpvic;
    int succ, penetration, max_success, i;
    int d_res;
    mixed att_desc;
    mixed did_hurt;
    string how, good;
    int no, class;
    string vic_str;

    if (!sizeof(victim))
	return;
    no = sizeof(victim);
    vic_str = COMPOSITE_LIVE(victim);

    succ = random(700)+300;

    TO -> catch_msg("You breathe fire upon "+vic_str+".\n");
    tell_room(ENV(TO),
	      QCTNAME(TO)+" opens its nostrils and breathes fire upon " + 
	      vic_str+"!!\n",
	      victim + ({TO}));
    for(i=0; i<no; i++) {
	tmpvic = victim-({victim[i]});
	if(sizeof(tmpvic)==0)
	    vic_str = "you";
	else
	    vic_str = "you and "+FO_COMPOSITE_LIVE(tmpvic, victim[i]);
	victim[i]->catch_msg(QCTNAME(TO)+" breathes fire upon "+
			     vic_str+"!!\n");
    }
    for(i=0; i<no; i++) {
	d_res = victim[i]->query_magic_res(MAGIC_I_RES_FIRE);
	penetration  = random(succ * (100 - d_res) /100) + 1;

    /*	did_hurt =  ({ proc_hurt, hitloc description, phit, dam }) */
	did_hurt = victim[i]->hit_me(penetration, MAGIC_DT, TO, -1);

	switch(did_hurt[2])
	{
	    case 0..15:		good = "poor"; break;
	    case 16..30:	good = "weak"; break;
	    case 31..59:	good = "dangerous"; break;
	    case 60..75:	good = "powerful"; break;
	    case 76..91:	good = "nasty"; break;
	    case 92..110:	good = "awesome"; break;
	    case 111..200:	good = "devastating"; break;
	    case 201..500:good = "massacrating"; break;
	    default:	good = "deadly"; break;
	}

	tellem(TO, victim[i],
	    "$Your cone of fire hits #name with "+good+" flames!\n", 1);

	message(TO, victim[i], DT_HEAT, "", did_hurt[0]);

	if(victim[i]->query_hp() <=0)
	    victim[i]->do_die(TO);
    }
}

void
do_sulf()
{
    object *victim = FILTER_LIVE(all_inventory(ENV(TO))) - ({ TO });
    object *tmpvic;
    int succ, penetration, max_success, i;
    int d_res;
    mixed att_desc;
    mixed did_hurt;
    string how, good;
    int no, class;
    string vic_str;

    if(!sizeof(victim))
	return;
    no = sizeof(victim);
    vic_str = COMPOSITE_LIVE(victim);

    succ = random(700)+300;

    TO -> catch_msg("You breathe sulfur upon "+vic_str+".\n");
    tell_room(ENV(TO),
	    QCTNAME(TO)+" opens its nostrils and breathes sulfur upon "+vic_str+"!!\n",
	    victim + ({TO}));
    for (i=0; i<no; i++)
    {
	tmpvic = victim - ({victim[i]});
	if(sizeof(tmpvic))
	    vic_str = " and "+FO_COMPOSITE_LIVE(tmpvic, victim[i]);
	else
	    vic_str = "";
	victim[i]->catch_msg(
	    QCTNAME(TO)+" breathes sulfur upon you"+vic_str+"!!!!\n");
    }
    for (i=0; i<no; i++)
    {
	d_res = victim[i]->query_magic_res(MAGIC_I_RES_ACID);
	penetration  = random(succ * (100 - d_res) /100) + 1;

    /*	did_hurt =  ({ proc_hurt, hitloc description, phit, dam }) */
	did_hurt = victim[i]->hit_me(penetration, MAGIC_DT, TO, -1);

	switch(did_hurt[2])
	{
	    case 0..15:		good = "poorly"; break;
	    case 16..30:	good = "weakly"; break;
	    case 31..59:	good = "dangerously"; break;
	    case 60..75:	good = "powerfully"; break;
	    case 76..91:	good = "nastily"; break;
	    case 92..110:	good = "awesomely"; break;
	    case 111..200:	good = "devastatingly"; break;
	    case 201..500:	good = "massacratingly"; break;
	    default:		good = "deadly"; break;
	}

	tellem(TO, victim[i],
	    "$Your cone of sulfur hits #name "+good+"!\n", 1);

	message(TO, victim[i], DT_ACID, "", did_hurt[0]);

	if(victim[i]->query_hp() <=0)
	    victim[i]->do_die(TO);
    }
}

void
do_schmack(object who)
{
    string str;
    int dam;

    switch(random(4)) {
	case 0:
	    tellem(TO, who,
		"$N $grab after #n and $squeeze #o to death!\n");
	    dam = 100 + random(200);
	    break;
	case 1:
	    tellem(TO, who,
		"$N $pierce through #n's body with $p large horns!!\n");
	    dam = 200 + random(300);
	    break;
	case 2:
	    tellem(TO, who,
		"$N $slash #n's face with $p whipping tail!!\n");
	    dam = 300 + random(200);
	    break;
	case 3:
	    tellem(TO, who,
		"$N $fume in rage as $s $sweep #n's feet in a swing!!\n");
	    dam = 300 + random(300);
	    break;
    }
    switch(dam)
    {
	case 0..200:   str="very successful"; break;
	case 201..300: str="incredible"; break;
	case 301..400: str="devastating"; break;
	case 401..500: str="massacrating"; break;
	case 501..600: str="death-vasting"; break;
    }
    tellem(TO, who,
	"$N's attack on #n is " + str +
	"${, as always..; in strength. You are very hurt; indeed}!!!\n");

    who->heal_hp(-dam);
    if(who->query_hp() <= 0)
	who->do_die(TO);
}

varargs
do_send_out(object who, int sniff)
{
    if(who->query_ghost())
    {
	who->move_living("M", MINES_DIR + "big_hall");
	say(QCTNAME(who)+" is blown out of the room!\n",who);
	return 1;
    }

    who->catch_msg("The dragon fums with rage and sends a cloud of fire towards you.\n");

    say("The dragon fums with rage and sends a cloud of fire towards "
      + QTNAME(who) + ".\n" + CHE_SHE(who)
      + " lifts off ground and is sent out of the room!\n", who);

    who->hit_me(100, MAGIC_DT, TO, -1);

    who->move_living("M", MINES_DIR + "big_hall");

    who->catch_msg("\nYou're blown back into the big hall.\n\n");
    who->catch_msg("You are badly hurt as you hit the cold wall...\n");

    say("A cloud of fire emerges from the northern room!\n"
      + QCTNAME(who)+" comes riding on it!!\n"
      + CHE_SHE(who) + " gets badly hurt as "
      + HE_SHE(who) + " flies directly into the opposite wall.\n",who);

    if (sniff)
	who->catch_msg(
	   "It did not widen its eyes, so it is evident that it has a keen "+
	   "sense of smell. It is impossible to pass the dragon now, so I "+
	   "propose you find a way of fooling its nose, that is, if you "+
	   "really want to pass...\n");

    who->hit_me(40, W_BLUDGEON, TO, 1);
}

int
special_attack(object who)
{
    if (random(3))
	return 0;

    if (random(5)==2 && is_home())
    {
	do_send_out(who, 0);
	return 1;
    }

    switch (random(3))
    {
	case 0:
	    do_fry();
	    return 1;
	case 1:
	    do_sulf();
	    return 1;
	case 2:
	    do_schmack(who);
	    return 1;
    }
}

int
query_knight_prestige() { return 1000; }


varargs void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
{
    object wep;
    int ind;
    int better=0;
    mixed *magic;

    if (hid != H_SPOT)
    {
	::cr_got_hit(hid, ph, att, aid, dt, dam);
	return;
    }

    if (dam <= 0)
	return;

    wep = att->query_weapon(aid);
    if (!wep)
	return;

    magic = wep->query_prop(MAGIC_AM_MAGIC);
    if (stringp(magic)) {
	write_file("/d/Shire/moria/log/BAD_WEAPONS",
		   sprintf("%O has a bad MAGIC_AM_MAGIC prop!\n"+
			   "    MAGIC_AM_MAGIC=(string)%s\n",
			   wep, magic));
	return;
    }
    if (!sizeof(magic))
	return;

    ind = member_array("enchantment", magic);
    if (ind>0)
	better += magic[ind-1];
    ind = member_array("dragon-slaying", magic);
    if (ind>0)
	better += 100*magic[ind-1];

    heal_hp(-dam*10 - random(better * 10));

    tellem(TO, att,
	"$N $scream in pain as #n #penetrate $n's poorly armoured weak spot!!\n",1);
}


#ifdef 0

    load_a_chat(10,({"The dragon looks at you with an evil look!\n",
		     "Smoke drifts from the dragons nose.\n"}));

heart_beat() {
  object a;
  ::heart_beat();
  if(!environment()) 
    return;
  a=query_attack();
  if(!a) 
    return;
  // Chance lowered from 1/10 to 1/20 by Drev:
  if(present(a) && random(20)==0)
    environment(this_object())->send_out(a);
}

#endif
