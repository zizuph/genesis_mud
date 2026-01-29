inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"

/* SARR */


void
create_monster()
{
    ::create_monster();
    set_name("guard");
    set_adj("elite");
    set_race_name("human");
    set_short("elite guard of the High-Lord");
    set_long("This is one of the High-Lord's elite home guard. "+
    "He is very well trained and paid. He is in charge of keeping "+
    "the High-Lord's castle safe, so he must be very good. His "+
    "eyes look sharp, his weapons deadly, and his muscles strong.\n");
    set_alignment(500);
    set_knight_prestige(-300);
    add_speak("Don't cause trouble.\n");
    set_stats(({120,120,120,70,70,100}));
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_PARRY,100);
    set_act_time(3);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(LIVE_I_SEE_DARK,2);
    add_act("scratch chin");
    add_act("emote stares straight ahead.");
    add_act("say Watch yourself, stranger...");
    add_act("say This is the High-Lord's castle.");
    add_act("emote checks on his weapons.");
    add_act("emote checks on his armours.");
    set_cact_time(5);
    add_cact("say I shall protect my High-Lord!");
    add_cact("shout Fool! You will die now!");
    add_prop(LIVE_I_NEVERKNOWN,1);
}

string
ran_weapon()
{
        return NOBLE(wep/two-handed_longsword);
}


void
arm_me()
{
    object ob;
    seteuid(getuid());
    ob = clone_object(NOBLE(arm/os_helm));
    ob->move(TO);
    ob = clone_object(NOBLE(arm/os_breastplate));
    ob->move(TO);
    ob = clone_object(NOBLE(arm/os_bracers));
    ob->move(TO);
    ob = clone_object(NOBLE(arm/os_greaves));
    ob->move(TO);
    ob = clone_object(NOBLE(arm/sl_boots));
    ob->move(TO);
    ob = clone_object(ran_weapon());
    ob->move(TO);
    MONEY_MAKE_SC(random(35))->move(TO);
    command("wear all");
    command("wield all");
}

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;
    if(random(100) > 30)
        return 0;
    if(!sizeof(query_weapon(-1)))
        return 0;    
    hitres = ob->hit_me(random(300)+300,W_BLUDGEON,TO,-1);
    phurt = " with hardly any effect";
    switch(hitres[0])
    {
        case 1..20:
            phurt = "";
            break;
        case 21..40:
            phurt = " with a thud";
            break;
        case 41..60:
            phurt = " with a loud thud";
            break;
        case 61..80:
            phurt = " with a loud crack";
            break;
        default:
            phurt = " with a bone crushing sound";
    }
    if(random(2))
    {
    ob->catch_msg(QCTNAME(TO)+" parries your blow with his "+
    query_weapon(-1)[0]->short()+", then slams his shoulder into your "+
    "side"+phurt+".\n"); 
    tell_room(E(ob),QCTNAME(TO)+" parries "+QTNAME(ob)+"'s blow "+
    "with his "+query_weapon(-1)[0]->short()+", then slams his shoulder "+
    "into "+HIS(ob)+" side"+phurt+".\n",ob);
    }
    else
    {
    ob->catch_msg(QCTNAME(TO)+" dodges your swing, then brings "+
    "up the hilt of his "+query_weapon(-1)[0]->short()+" across your face"+
    phurt+".\n");
    tell_room(E(ob),QCTNAME(TO)+" dodges "+QTNAME(ob)+"'s swing, "+
    "then brings up the hilt of his "+query_weapon(-1)[0]->short()+" across "+
    HIS(ob)+" face"+phurt+".\n",ob);
    }
    if(ob->query_hp() <= 0)
        ob->do_die(TO);
    return 1;
}

