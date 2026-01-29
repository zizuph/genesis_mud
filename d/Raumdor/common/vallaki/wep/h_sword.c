inherit "/std/weapon";
#include "/d/Raumdor/defs.h"
/* Sarr */

// int holy_flame(object enemy);
void
create_weapon()
{
    ::create_weapon();
    set_name("sword");
    add_name("longsword");
    set_adj("holy");
    add_adj("silver");
    set_short("holy silver longsword");
    add_prop(OBJ_I_LIGHT,1);
    set_long("This longsword is made of blessed holy steel. It gleams "+
        "with its own inner light. The cross-piece is adorned with a golden "+
        "cross. Along the blade are golden runes, writen in some arcane "+
        "language you do not know. At the bottom of the hilt, you see a "+
        "large sapphire.  This is truly a beautiful weapon.\n");
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);
    set_wt(W_SWORD);
    set_wf(TO);
    set_hit(45);
    set_pen(40);
    set_likely_corr(10);
    set_likely_dull(4);
    set_likely_break(4);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(OBJ_S_WIZINFO,"This is a bless holy sword. It does extra "+
        "damage to undead. Only those holy enough can wield it.\n");
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This sword radiates a holy light. It "+
                "has been blessed by great holy powers, and those of evil would "+   
                "be warned not to come near it. Those of undead nature would be "+
                "hurt easily by it.\n",10}));
    add_prop(OBJ_I_WEIGHT,5000);
    add_prop(OBJ_I_VOLUME,4000);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_BUY,1);
}

mixed
wield(object obj)
{
    if(TP->query_alignment() < 1)
        {
        write("A white light shoots up from the sword, and burns your "+
            "hands!\n");
        write("Evil foul creature! You dare to wield me!?\n");
        say(QCTNAME(TP)+" tries to wield the holy silver longsword, "+
            "but a white light shoots out of the sword and burns "+HIM(TP)+
            "!\n");
        TP->heal_hp(TP->query_alignment());
        if(TP->query_hp() <= 0) 
            TP->do_die(TO);
        return "You could not wield the sword.\n";
    }
    if(TP->query_alignment() < 1000)
        {
        write("The sword pulses softly, but it resists you.\n");
        write("A voice in your head echos: You are not holy enough to "+
            "wield me, young warrior.\n");
        say(QCTNAME(TP)+" tries to wield the holy silver longsword, "+
            "but is not worthy and fails.\n");
        return "You could not wield the sword.\n";
    }
    write("You grip your hands around the hilt tightly.\n");
    write("A surge of power goes up your arms, and you feel blessed.\n");
    say(QCTNAME(TP)+" grips the hilt of the holy silver longsword "+
        "tightly, and a surge of energy goes up "+HIS(TP)+" arms.\n");
    TP->command("say I fear no evil.\n");
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
            holy_flame(enemy);
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
    if (!me) return 1;
    hitresult = enemy->hit_me(450 + random(250), MAGIC_DT, me, -1);
    how = " without effect";
    if (hitresult[0] > 10)
        how = "";
    if (hitresult[0] > 20)
        how = " badly";
    if (hitresult[0] > 30)
        how = " harshly";
    if (hitresult[0] > 40)
        how = " severely";
    me->command("shout Begone creature of Hell!");
    me -> catch_msg("A bright and holy flame leaps out of the sword and "+
        "engulfs "+QTNAME(enemy)+".\n"+
        C(HE(enemy))+" is burned"+how+".\n");
    enemy -> catch_msg("A bright and holy flame leaps out of the sword and "+
        "engulfs you.\n"+
        "You are burned "+how+".\n");
    tell_watcher("A bright and holy flame leaps out of "+QTNAME(me)+
        "'s sword and engulfs "+QTNAME(enemy)+".\n"+
        "'s sword and engulfs "+QTNAME(enemy)+".\n"+
        C(HE(enemy))+" is burned"+how+".\n",enemy);
    if (enemy->query_hp() <= 0)
        enemy -> do_die(me);
    return 1;
}
 */
