/*

Creator: Dimitry@Igor
Date: 04-Feb-2001
Information: a magical club (white leather whip).
             This bloody whip was a property of Minas Morgul once.
             It has been stolen from the Dark Tower and used in
             the Army of Angmar.

Fixed: 25-Mar-2001 request from Jadavin.
             
*/


inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Ansalon/common/defs.h"

int pen;
mixed hitres;
string hitresult,penet,damage;

void
create_weapon()
{
 add_prop(OBJ_M_NO_BUY, 1);
 add_prop(OBJ_M_NO_SELL, 1);
 set_keep(1);
 set_hit(38+random(5));
 set_pen(42+random(9));
 set_wt(W_CLUB);
 set_dt(W_SLASH);
 set_hands(W_ANYH);
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
}

void
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
  int dam)
{
    object me = query_wielded();

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

 if(random(1000/(random(100)+TP->query_base_stat(SS_WIS)))) return 0;
  pen = 100 + random(TP->query_base_stat(SS_STR)) + random(200);
  hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);

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

me->catch_msg("You swing your "+short()+penet+" "+damage+QTNAME(enemy)+"'s body"+hitresult+".\n");
enemy->catch_msg(QCTNAME(me)+" swings "+POSSESSIVE(TO)+" "+short()+penet+" "+damage+"your body"+hitresult+".\n");
tell_room(E(me),QCTNAME(me)+" swings "+POSSESSIVE(TO)+" "+short()+penet+" "+damage+QTNAME(enemy)+"'s body"+hitresult+".\n",({enemy,me}));

    if (me->query_wiz_level())
me->catch_msg("Hitresult = "+hitres[0]+" "+"Pen = "+pen+" "+"Damage ="+hitres[3]+"\n");

  if (enemy->query_hp() <= 0)
   {
     enemy->do_die(TP);
     return 0;
   }

}
