/*      /d/Raumdor/common/drakmere/wep/dl_scepter
 *      Created by:     Sarr   
 *      Purpose:        
 *      Modified:       Toby, 971009 (fixed typos, plus added a little random 
 *				      on hit/pen. Added name club)
 */



inherit "/std/weapon";
#include "/d/Raumdor/defs.h"

int charges = 3;

void
create_weapon()
{
    ::create_weapon();

    set_name("sceptre");
    add_name("club");
    set_adj("jewelled");
    add_adj("holy");

    set_short("holy jewelled sceptre");

    add_prop(OBJ_I_LIGHT,1);

    set_long("This is one of the holy sceptres of Raumdor, held only "+
      "by the lords of the cities. A gift to each of his lords by King "+
      "Raumdor, it possesses many holy powers. A large golden cross adorns "+
      "the jewelled silver haft.\n");

    set_dt(W_BLUDGEON);
    set_hands(W_RIGHT);
    set_wt(W_CLUB);
    set_wf(TO);
    set_hit(29+random(3));
    set_pen(39+random(3));

    set_likely_corr(0);
    set_likely_dull(0);

    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO,"This is a magical sceptre, able to heal, and "+
      "burn undead to dust. It can heal half of ones alignment.\n");
    add_prop(MAGIC_AM_MAGIC,({100,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This sceptre radiates a holy light. It "+
	"has been blessed by great holy powers, and those of evil would "+   
	"be warned not to come near it. Those of undead nature would be "+
	"hurt easily by it.\n",10}));

    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,1000);
}

mixed
wield(object obj)
{
    if(TP->query_alignment() < 1)
    {
	write("A white light shoots up from the sceptre, and burns your "+
	  "hand!\n");
	write("Evil foul creature! You dare to wield me!?\n");
	say(QCTNAME(TP)+" tries to wield the holy jewelled sceptre, "+
	  "but a white light shoots out of the sceptre and burns "+HIM(TP)+
	  "!\n");
	TP->heal_hp(TP->query_alignment());
	if(TP->query_hp() <= 0) 
	    TP->do_die(TO);
	return "You could not wield the sceptre.\n";
    }
    if(TP->query_alignment() < 1000)
    {
	write("The sceptre pulses softly, but it resists you.\n");
	write("A voice in your head echos: You are not holy enough to "+
	  "wield me, young warrior.\n");
	say(QCTNAME(TP)+" tries to wield the holy jewelled sceptre, "+
	  "but is not worthy and fails.\n");
	return "You could not wield the sceptre.\n";
    }
    write("You grip the haft of the weapon tightly in your hand.\n");
    write("A surge of power goes up your arm, and you feel blessed.\n");
    say(QCTNAME(TP)+" grips the haft of the holy jewelled sceptre "+
      "tightly, and a surge of energy goes up "+HIS(TP)+" arms.\n");
    TP->command("say For King Raumdor, forever banishing darkness.");
    return 0;
}



static void
tell_watcher(string str, object enemy)
{
    object mee,*ob;
    int i;
    mee = query_wielded();
    ob = FILTER_LIVE(all_inventory(environment(mee))) - ({ mee });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}
/*

public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    if(phurt>0)
	if(!(random(4)))
	{
	    if(enemy->query_prop(LIVE_I_UNDEAD))
		set_alarm(0.0,0.0,"holy_flame",enemy);
	}
    return;
}


int
holy_flame(object enemy)
{
    object me;
    mixed  *hitresult;
    string how;
    me = query_wielded();
    hitresult = enemy->hit_me(350 + random(150), MAGIC_DT, me, -1);
    how = " without effect";
    if (hitresult[0] > 10)
	how == "";
    if (hitresult[0] > 20)
	how = " badly";
    if (hitresult[0] > 30)
	how = " harshly";
    if (hitresult[0] > 40)
	how = " severely";
    me->command("shout Begone creature of Hell!");
    me -> catch_msg("A bright and holy flame leaps out of the sceptre and "+
      "engulfs "+QTNAME(enemy)+".\n"+
      C(HE(enemy))+" is burned"+how+".\n");
    enemy -> catch_msg("A bright and holy flame leaps out of the sceptre and "+
      "engulfs you.\n"+
      "You are burned "+how+".\n");
    tell_watcher("A bright and holy flame leaps out of "+QTNAME(TP)+
      "'s sceptre and engulfs "+QTNAME(enemy)+".\n"+
      C(HE(enemy))+" is burned"+how+".\n",enemy);
    if (enemy->query_hp() <= 0)
	enemy -> do_die(me);
    return 1;
}


init()
{
    ::init();
    add_action("command","command");
}

int
command(string s)
{
    log_file("sceptre",TP->query_real_name()+" used the command-word: "+s+
      " at time "+extract(ctime(time()),4,15)+".\n");
    if(!present(TO,TP))
    {
	NF("You don't have the "+TO->query_short()+"!\n");
	return 0;
    }
    if (!s)
    {
	NF("What?\n");
	return 0;
    }
    if (s != "holaminia")
    {
	NF("What?\n");
	return 0;
    }
    write("The "+TO->query_short()+" glows white and your body is "+
      "enveloped in white light!\n");


    return 1;
}


int
do_heal()
{
    if(!present(TO,TP))
    {
	NF("You don't have the "+TO->query_short()+"!\n");
	return 0;
    }
    if(charges == 0)
    {
	NF("The "+TO->query_short()+" is too weak to heal further.\n");
	return 0;
    }
    write("The "+TO->query_short()+" glows white and your body is "+
      "enveloped in a holy light that soothes your wounds.\n");
    write("You feel much better.\n");
    TP->heal_hp(TP->query_alignment());
    charges = charges - 1;
    say(QCTNAME(TP)+"'s "+TO->query_short()+" glows white and envelopes "+
      HIS(TP)+" body in a holy light that heals "+HIS(TP)+" wounds.\n");
    return 1;
}
*/
