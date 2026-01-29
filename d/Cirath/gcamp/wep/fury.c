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
        set_name(({"sword", "fury", "stormblade","longsword"}));
        set_adj("long-handled");
        add_adj("blue-steel");
        set_short("long-handled blue-steel longsword");
        set_long("Crafted of some form of blue tinged steel, this "
        	+"longsword is a work of art.  Intricate runes run down "
        	+"the length of the slightly curved blade.  The handle "
        	+"seems to be longer than that on a typical longsword for "
        	+"some reason, and the handle itself seems to formed from "
        	+"some sort of steel wrapped in tightly wound cords.  On "
        	+"the butt of the sword is a small ring, which has two "
        	+"intricately carved lightning bolts inside it.  Every "
        	+"so often a tiny arc of electricity runs up the length of "
        	+"the blade making a dull humming sound.\n");
        set_hit(40);
        set_pen(50);
        set_wt(W_SWORD);
        set_dt(W_SLASH | W_IMPALE);
        set_hands(W_ANYH);
        add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
        add_prop(MAGIC_AM_MAGIC, ({ 50, "psionic" }));
        add_prop(OBJ_M_NO_BUY, "No I don't want to sell this weapon. I'll "
                        +"keep it to my self.");
        set_likely_corr(0);
        set_likely_dull(-100);
        add_prop(OBJ_I_WEIGHT,4000);
        add_prop(OBJ_I_VOLUME,1200);
        add_prop(OBJ_I_VALUE, 4000);
        add_prop(MAGIC_AM_ID_INFO, ({"You detect that some psionics have been "+
                "employed on this weapon. ", 10,"Psionic energy has been "
                +"used to give this weapon the ability to harness the power "
                +"of lightning.",25,}));

        add_prop(OBJ_S_WIZINFO, "Has a special attack based on the wielders "
                +"constitution. Provides a MAGIC_I_RES_ELECTRICITY of 30.\n");
        set_wf(TO);

}


int
did_hit(int aid, string hdesc, int phurt,
        object enemy, int dt, int phit, int dam)
{
        object me = ENV(TO);
	int att, pen, res;
        mixed* hitresult;
        string how;

        ::did_hit();

	if (random(6)) return 0;

        att = me->query_base_stat(SS_CON) + random(me->query_base_stat(SS_CON));
	res = enemy->query_magic_res(MAGIC_I_RES_ELECTRICITY);	
 	pen = att * (100 - res) /100;
	hitresult = enemy->hit_me(pen, MAGIC_DT, me, -1);

        how = "lightly";
        if (hitresult[0] > 1) how = "mildly painfully";
        if (hitresult[0] > 5) how = "painfully";
        if (hitresult[0] > 15) how = "very painfully";
        if (hitresult[0] > 20) how = "very severely";
		if (hitresult[0] > 25) how = "and leaving permanent damage";

        if(enemy->query_hp()<= 0)
        {
                me->catch_msg("Making contact with " + QTNAME(enemy) + 
                ", arcs of blue electricty lash out into " +
                 HIS_HER(enemy) + " " + hdesc + ".\n");
                me->tell_watcher(QCTNAME(me)+ " strikes " + QTNAME(enemy)+
                        " with "+ HIS_HER(me)+" long-handled blue-steel "
                        +"longsword.  Bolts of electricity arc from the "
                        +"blade into "+HIM_HER(enemy)+".\n", me, enemy);
                enemy->catch_msg("Electricity crackles around the blade of "
                	+"the long-handled blue-steel longsword and slams "
                	+"into you!\n");
                enemy->do_die(me);
                return 1;
        }

        me->catch_msg("The stormblade releases bolts of electricity into " 
        	+ QTNAME(enemy) +", burning "+HIS_HER(enemy)+ " " + hdesc +
        	" "+how + ".\n");
        enemy->catch_msg("The long-handled blue-steel longsword burns " 
         +"your " + hdesc + " "+how + ".\n");

        me->tell_watcher(QCTNAME(me)+ " slices the "+ hdesc+" of "
	   + QTNAME(enemy)+" with his stormblade.\n", me, enemy);

        return 1;
}

mixed
query_magic_protection(string prop, object what)
{
    if (what == query_wielded())
    {
        switch (prop)
        {
	     case MAGIC_I_RES_ELECTRICITY:    return ({ 30, 1 });
        }
    }

    return ::query_magic_protection(prop, what);
}

public mixed
wield(object ob)
{
    object  tp = this_player();

    // sanity checks.
    if ((ob != this_object()) || (tp != environment(this_object())))
        return -1;

    tp->add_magic_effect(this_object());
   TP->catch_msg("Electricity crackles through you as you wield Fury.\n");
   say(QCTNAME(this_player()) + " wields the long-handled blue-steel longsword.\n");
    return 1;
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

    TP->remove_magic_effect(this_object());
    TP->catch_msg("You feel the electricity flow from your body back into "
     +"the stormblade as you release your grip on it.\n");
    say("As "+QCTNAME(this_player()) + " unwields the long-handled "
    	+"blue-steel longsword, a small spiral of electricity radiates "
    	+"out from his eyes, dissipating in the air.\n");
    return 1;
}

string
query_recover()
{
return 0;
}
