/*

Creator: Dimitry@Igor, G00Guy@IRC, #17332262@ICQ, s92bkose@avene.eef.rtu.lv
Date: 04-Feb-2001
Information: a magical club (white leather whip or WLW).
             This bloody whip was a property of Minas Morgul once.
             It has been stolen from the Dark Tower and used in
             the Army of Angmar.

Fixed: 25-Mar-2001 request from Jadavin. TO changed to TP in special kill.
Fixed: 26-Mar-2001 request from Jadavin. Weight and volume adjustments.
Fixed: 26-Mar-2001 Changed special damage type Bludgeon to Slash.
Added: 26-Mar-2001 Nice whip's emotes after it kills someone with its special.
Added: 26-Mar-2001 Accumulation for blood. Suck-Heal feature.
                   You can always check _sucked_blood property: Dump jadavin:whip props
Fixed: 17-Apr-2001 Now it takes random(blood) for calculating to_pen of the
                   special (used to be just blood, way too powerfull).
Added: 17-Apr-2001 I hope it will not going dull and break (since this weapon
                   is limited (only once per reboot) and whip is a whip :) it can't dull or
                   break.
Added: 18-Apr-2001 Now it will suck mana :)

*/


inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Ansalon/common/defs.h"
#include <options.h>
#include <filter_funs.h>

#define WHIP_STR "_sucked_blood"

int pen,blood;
mixed hitres;
string hitresult,penet,damage,heal,pulse;

void
create_weapon()
{

 blood=1;
 add_prop(WHIP_STR,blood);
 add_prop(OBJ_M_NO_BUY, 1);
 add_prop(OBJ_M_NO_SELL, 1);
 set_keep(1);
 set_hit(38+random(5));
 set_pen(42+random(9));
 set_wt(W_CLUB);
 set_dt(W_SLASH);
 set_hands(W_LEFT);
add_prop(OBJ_I_VOLUME, 4000+random(2000));
add_prop(OBJ_I_WEIGHT, 4000+random(2000));
  set_adj("white");
 set_adj("leather");
 set_short("white leather whip");
 set_pshort("white leather whips");
 set_name(({"whip","club","weapon"}));
 set_pname(({"whips","clubs","weapons"}));
 set_long("This is a nasty looking whip which is made of "+
          "unknown white leather. It is not white though. "+
          "The whip is covered with a red blood. The blood "+
          "is dripping down from the whip leaving a "+
          "bloody path on the ground. You can imagine "+
          "how many tortures this weapon attended and "+
          "how many souls it took away. \n");
 add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
 add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
 add_prop(MAGIC_AM_ID_INFO,({"This whip has been enchanted "+
          "in the Dark Tower of Minas Morgul.\n",5,"The " +
          "enchantment makes this whip shred flesh and " +
          "cut bones easily if you are strong enough.\n",15,"The " +
          "whip has a soul which likes fresh blood and time " +
          "from time it sucks blood out on its own from your " +
          "enemies.\n",30}));
          seteuid(getuid(TO));
         
    set_likely_corr (0);
    set_likely_break(0);
    set_likely_dull(0);
          
          
}

void
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object me = query_wielded();
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

set_dull(0);
if (enemy->query_hp() <= 0) {enemy->do_die(me);return 0;}




blood=query_prop(WHIP_STR);


	if ((random(100)<10) && (blood>20))
	{
	TP->heal_hp(random(10)+blood);
	TP->add_mana((-1)*(random(10)+1));
	heal=" heals you a little bit with its power.";
	if (blood>50) heal=" heals you with its power.";
	if (blood>100) heal=" makes you feel healthier.";
	if (blood>150) heal=" injects some fresh blood into your veins!";
	if (blood>200) heal=" heals some of your wounds!!!";
	if (blood>250) heal=" makes you feel much more healthier!!!";
	me->catch_msg("The "+short()+heal+"\n");
	enemy->catch_msg("The "+short()+" wraps gently around "+QCTNAME(TP)+"'s left arm for a moment.\n");
	tell_room(E(me),"The "+short()+" wraps gently around "+QCTNAME(TP)+"'s left arm for a moment.\n",({enemy,me}));
	}



if(random(1000/(random(100)+TP->query_base_stat(SS_WIS)))) return 0;
  pen = random(blood)+100+random(TP->query_base_stat(SS_STR)) + random(200);
  hitres = enemy->hit_me(pen, W_SLASH, TP, -1);

 if (hitres[0] <= 0) hitresult=" and leaving almost no track of the attack";
 if (hitres[0] > 0)  hitresult=" and removing some of the skin";
 if (hitres[0] > 10) hitresult=" and removing some of the flesh";
 if (hitres[0] > 25) hitresult=" and leaving a gaping wound on it";
 if (hitres[0] > 45) hitresult=" and leaving a deep bleeding wound on it";
 if (hitres[0] > 60) hitresult=" and causing hot pain and desperate fear";
 if (hitres[0] > 80) hitresult=" and splattering blood and flesh";

 if ( pen <= 50) penet=" weakly,";
 if ( pen > 50)  penet=" moderately,";
 if ( pen > 100) penet=" powerfully,";
 if ( pen > 150) penet=" forcefully,";
 if ( pen > 200) penet=" with a great might,";
 if ( pen > 300) penet=" with a destructive motion,";
 if ( pen > 400) penet=" with a merciless grin,";

 if ( hitres[3] <= 30) damage="barely scratching ";
 if ( hitres[3] > 30)  damage="scratching ";
 if ( hitres[3] > 50)  damage="raking ";
 if ( hitres[3] > 70)  damage="cutting ";
 if ( hitres[3] > 100) damage="seriously cutting ";
 if ( hitres[3] > 200) damage="cutting deeply ";
 if ( hitres[3] > 300) damage="ripping into ";         

TP->add_mana((-1)*(random(3)+1));

me->catch_msg("You swing your "+short()+penet+" "+damage+QTNAME(enemy)+"'s body"+hitresult+".\n");
enemy->catch_msg(QCTNAME(me)+" swings "+POSSESSIVE(TP)+" "+short()+penet+" "+damage+"your body"+hitresult+".\n");
tell_room(E(me),QCTNAME(me)+" swings "+POSSESSIVE(TP)+" "+short()+penet+" "+damage+QTNAME(enemy)+"'s body"+hitresult+".\n",({enemy,me}));

if (me->query_wiz_level()) me->catch_msg("Hitresult = "+hitres[0]+" "+"Pen = "+pen+" "+"Damage ="+hitres[3]+" Blood:"+blood+"\n");

if (enemy->query_hp() <= 0)
   {
me->catch_msg("The "+short()+" cracks happily in your hand and sucks some blood from "+QTNAME(enemy)+"'s corpse.\n");
tell_room(E(me),"The "+short()+" cracks happily in "+QCTNAME(me)+"'s hand and sucks some blood from "+QTNAME(enemy)+"'s corpse.\n",({enemy,me}));

if (blood<100) blood=blood+random(4)+1;
if (blood>=100) blood=blood+random(2)+1;
TP->add_mana((-1)*(random(10)+1));
	
	add_prop(WHIP_STR,blood);

	pulse=" shivers a little.";
	if (blood>20) pulse=" shivers and pulses with a pale red color.";
	if (blood>50) pulse=" shivers and pulses with a red color.";
	if (blood>100) pulse=" shivers and pulses with an intense red color!";
	if (blood>150) pulse=" shivers and pulses with a bloody red color!!!";
	if (blood>200) pulse=" shivers and pulses with a demonic red color!!!";
	me->catch_msg("The "+short()+pulse+"\n");
	tell_room(E(me),"The "+short()+pulse+"\n",({enemy,me}));

     enemy->do_die(me); 
   }

}
