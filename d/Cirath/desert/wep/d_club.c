#pragma save_binary
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/wa_types.h"
#include "/d/Cirath/common/defs.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <language.h>
#include "/sys/stdproperties.h"

void create_weapon()
{
        set_name("club");
        set_adj("massive");
        add_adj("datchi");
        set_short("massive datchi club");
        set_long("Crafted from a large piece of agafari wood, and studded "
        	+"with razor-sharp pieces of chitin, this is a fearsome "
        	+"weapon.  A skilled wielder is able to not slam the weight "
        	+"of the club into people, but slash them with the chitinous "
        	+"razors.\n");
        set_hit(39);
        set_pen(45);
        set_wt(W_CLUB);
        set_dt(W_SLASH | W_BLUDGEON);
        set_hands(W_ANYH);
        add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
        add_prop(MAGIC_AM_MAGIC, ({ 50, "psionic" }));
        add_prop(OBJ_M_NO_BUY, "No I don't want to sell this weapon. I'll "
                        +"keep it to my self.");
        set_likely_corr(0);
        set_likely_dull(-100);
        add_prop(OBJ_I_WEIGHT,9000);
        add_prop(OBJ_I_VOLUME,4200);
        add_prop(OBJ_I_VALUE, 2000);

        add_prop(OBJ_S_WIZINFO, "Has a special attack based on the wielders "
                +"club skill.\n");
        set_wf(TO);

}

int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
        object me = ENV(TO);
        mixed* hitresult;
        string how;

        ::did_hit();

        if(random(8)) return 0;

        hitresult=enemy->hit_me(TP->query_skill(SS_WEP_CLUB)+
                random(TP->query_skill(SS_WEP_CLUB)), W_SLASH, me, -1);

        how = "almost";
        if (hitresult[0] > 1) how = "slightly";
        if (hitresult[0] > 5) how = "mildly";
        if (hitresult[0] > 15) how = "painfully";
        if (hitresult[0] > 20) how = "severely";
        if (hitresult[0] > 25) how = "massively";

        if(enemy->query_hp()<= 0)
        {
                me->catch_msg("You slam your datchi club into the head of "
                	+QCTNAME(enemy)+", shredding the flesh from "+
                	HIS_HER(enemy) + " head.  "+ HE_SHE(enemy) + " wails "
                	+"in pain before collapsing to the ground, dead.\n");
                me->tell_watcher(QCTNAME(me)+ " smashes " + QCTNAME(enemy)+
                        " in the head with "+ HIS_HER(me)+" massive datchi "
                        +"club.  Ribbons of flesh are torn from "+ 
                        QCTNAME(enemy) +"'s head, leaving a gory mess where "
                        +HIS_HER(enemy)+" head used to be.\n", me, enemy);
                enemy->catch_msg(QCTNAME(TP) + " slams his massive datchi "
                	+"club into your head, tearing your flesh from your "
                	+"face and crushing your skull.  You manage to draw "
                	+"half a breath and gasp before your world turns "
                	+"black.\n");
                enemy->do_die(me);
                return 1;
        }

        me->catch_msg("The massive datchi club smashes into " 
        	+ QTNAME(enemy) +" powerfully, its sharpened blades "
	    +"slashing into "+ HIM_HER(enemy)+".\n");
        me->catch_msg(HE_SHE(enemy)+" looks " + how + " injured.\n");
        enemy->catch_msg("The massive datchi club smashes into you, "
        	+how+" injuring you.\n");

        me->tell_watcher(QCTNAME(me)+ " slams his massive datchi club into "
        	+ QCTNAME(enemy)+".\n", me, enemy);

        return 1;
}

