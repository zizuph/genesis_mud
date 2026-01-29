inherit "/std/weapon";
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Cirath/common/defs.h"

void
create_weapon()
{
    set_name("axe");
    set_adj("blackened-iron");
    add_adj("massive");
    set_short("massive blackened-iron axe");
    set_long("Crafted of deep black iron, this axe looks like "
    	+"a shadowy copy of a real axe.  It almost seems "
    	+"insubstantial in your hands, but you can feel the "
    	+"incredible weight that signals its presence.  Some "
    	+"form of dark magic must have gone into the forging "
    	+"of this weapon, you can feel some sort of dark "
    	+"presence within trying to escape.\n");
    set_hit(47);
    set_pen(52);
    set_wt(W_AXE);
    set_dt(W_SLASH);
     set_hands(W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, "I'll just keep that, sorry.");
    add_prop(OBJ_I_WEIGHT, 25000);
    add_prop(OBJ_I_VOLUME, 9000);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 50, "necromantic" }));
    add_prop(MAGIC_AM_ID_INFO, ({"Pure defiler magic has infected this "
    		+"fell weapon, granting it the power to easily hit and "
    		+"damage your opponent.", 10,"In addition, this evil "
    		+"magery has added the power to damage foes with the "
    		+"power of the realm of death.",25,}));

        add_prop(OBJ_S_WIZINFO, "Special attack based on wielder's DIS.  "
        	+"it also has a wield restriction of a 160 STR and CON, as "
        	+"well of 90 axe skill.\n");
}
int
did_hit(int aid, string hdesc, int phurt,
        object enemy, int dt, int phit, int dam)
{
        object me = ENV(TO);
        mixed* hitresult;
        string how;

        ::did_hit();

        if(random(6)) return 0;

        hitresult=enemy->hit_me(TP->query_base_stat(SS_DIS)+
                random(TP->query_base_stat(SS_DIS)), W_SLASH, me, -1);

        how = "lightly";
        if (hitresult[0] > 1) how = "mildly painfully";
        if (hitresult[0] > 5) how = "painfully";
        if (hitresult[0] > 15) how = "very painfully";
        if (hitresult[0] > 20) how = "very severely";
        if (hitresult[0] > 25) how = "leaving permanent damage";

        if(enemy->query_hp()<= 0)
        {
                me->catch_msg("Your axe imbeds itself handle deep in "
                	+"the chest of "+QCTNAME(enemy)+".  Like a "
                	+"tidal wave, dark energy spews from the blade "
 		+"corrupting completely "+HIS_HER(enemy)+
                	" body and soul.\n");
		me->tell_watcher(QCTNAME(me)+ " wickedly imbeds "+
			HIS_HER(me) +" axe into the flesh of "+
                	QCTNAME(enemy)+", completely burying the axe head "
                	+"in "+ HIS_HER(enemy)+" soft flesh.  Thick "
                	+"tendrils of utter darkness spew forth from the "
                	+"blade, instantly crushing the small spark of life "
		 +"that remained in "+ HIM_HER(enemy)+".\n", me, enemy);
                enemy->catch_msg("You feel your breath blast from your body "
                	+"as "+QCTNAME(me)+" slams his axe deep into your "
                	+"chest.  You look down long enough to see inky "
                	+"black shadows creeping into your chest cavity, "
                	+"then your vision fades away....\n");
                enemy->do_die(me);
                return 1;
        }

        me->catch_msg("You slam the axe into " + QTNAME(enemy) + 
                ", feeling the power of darkness envelope " +
                HIM_HER(enemy) + " completely.\n");
        enemy->catch_msg("The coldness of the grave slices into "
                	+"your flesh as the massive blackened-iron axe "
                	+"cuts into you!.\n");

        me->tell_watcher(QCTNAME(me)+ " slams his axe into " + 
                	QTNAME(enemy)+ ".  You see wispy tendrils of "
                	+"shadow seep up the axe head and into "+
                        HIS_HER(enemy)+" his flesh.\n", me, enemy);

        return 1;
}

public mixed
wield(object ob)
{
    object  tp = this_player();

    if((TP->query_base_stat(SS_CON) > 159) &&
       (TP->query_base_stat(SS_STR) > 159) &&
       (TP->query_skill(SS_WEP_AXE) > 89))
   {
    TP->catch_msg("Black shadows creep up your arms as you wield the "
    	+"massive blackened-iron axe in both hands.  You feel the power "
	+"of darkness seep into your body, chilling your flesh to "
	+"the bone.\n");
    say(QCTNAME(this_player()) + " grips the haft of the massive "
    	+"blackened-iron axe in both hands, a dark glint sparkling in "
		+HIS_HER(TP) +" eye.\n");
	return 1;
    }

    TP->heal_hp(-(50 + random(100)));
    return "A powerful ripple of darkness spirals up your arm, causing "
    	+"you to gasp in pain.\n";
    
}

public mixed
unwield(object ob)
{
    object  tp = this_player();

    // sanity checks.
    if ((ob != this_object()) || (tp != query_wielded()))
        return -1;

    if (!living(tp))
        return 0;

    TP->catch_msg("With reluctance you release your grip on the "
    	+"massive blackened-iron axe.  Your body feels weaker as "
    	+"the dark force leaves your body.\n");
    say(QCTNAME(this_player()) + " releases "+HIS_HER(TP)+" grip on the "
	+"massive blackened-iron axe, the shadowy spark in "+
	HIS_HER(TP) + " eye vanishing abruptly.\n");
    return 1;
}

