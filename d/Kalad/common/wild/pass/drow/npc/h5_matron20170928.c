inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
/* by Antharanos */
#define QUEST_NAME "kilsekquest"
int heal;
int skin;
string long;
object matron;
void
create_monster()
{
    set_name("shrineerune");
    add_name("priestess");
    add_name("matron");
    set_race_name("drow");
    set_adj("aged");
    add_adj("merciless");
    set_long("An old and vicious looking drow female, unlike most of the "+
        "drow women you've seen, her face is not a vision of beauty, but "+
        "rather it is old and worn with centuries of strife and hatred. Despite "+
        "her advanced age, she is not one to be taken lightly, for her to have "+
        "survived this long in the world of drow, she must be an "+
        "individual of incredible resourcefulness.\n");
    set_gender(G_FEMALE);
    set_all_hitloc_unarmed(50); /* A permanent protective ac spell */
    set_stats(({120,125,100,25,25,100}));
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_AWARENESS,90);
    set_skill(SS_SPELLCRAFT,90);
    set_skill(SS_HIDE,50);
    set_skill(SS_SNEAK,50);
    set_alignment(-1200);
    set_knight_prestige(1200);
    set_act_time(3);
    add_act("smirk");
    add_act("grin menacingly all");
    add_act("cackle dem");
    add_act("snarl all");
    add_act("hide");
    add_act("say Wael!");
    set_cact_time(3);
    add_cact("laugh dem");
    add_cact("cackle devil");
    add_cact("grin mercilessly all");
    add_cact("utter z'ressuluquarvalsharess");
    set_title("Kilsek, the Matron Mother of House Kilsek, Fifth House of Undraeth");
    add_speak("You have proven resourceful to have gotten this far...I shall offer "+
        "you a task now, instead of slaying you outright for daring to invade "+
        "my home. If you are too weak to take him yourself, I suggest you meet "+
        "with the merchant in the city's bazaar.\n");
    set_default_answer("I won't answer foolish questions.\n");
    add_ask("task","It is a simple request really, all you must do is slay the "+
        "deep dragon for me, then bring me back his skin.\n");
    add_ask("merchant","He is located in the bazaar!\n");
    add_ask("bazaar","It is in the center of Undraeth, this city.\n");
    add_ask(({"dragon","shadowgloom"}), "The deep dragon's name is "+
        "Shadowgloom. His " +
        "den is located within the Dark Dominion, guarded by a veil of " +
        "sulfur and a being of metal.\n");
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(LIVE_I_SEE_INVIS,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    set_alarm(1.0,0.0,"arm_me");
}
skin_return()
{
    skin = 1;
}
public void
enter_inv(object ob, object from)
{
    if(MASTER_OB(ob) != "/d/Kalad/common/wild/pass/obj/dragon_skin")
        {
        ::enter_inv(ob, from);
        set_alarm(2.0,0.0,"drop_the_object",ob);
        return;
    }
    if(!interactive(from))
        return;
    else
        set_this_player(from);
    if(from->test_bit("Kalad",0,18))
        {
        write(query_The_name(from) + " grins demonically.\n");
        TP->catch_msg("You do not feel more experienced.\n");
    }
    else
        {
        command("grin dem");
        command("say Well done my unwitting ally!");
        TP->catch_msg("You feel more experienced.\n");
        TP->add_exp(7500);
        TP->set_bit(0,18);
        seteuid(getuid(TO));
        log_file(QUEST_NAME, extract(ctime(time()),4,15)+ " " +
            capitalize(TP->query_real_name()) + " rewarded with 7500 xp, "+
            "<"+TP->query_average_stat()+"> average stats.\n");
    }
    ::enter_inv(ob,from);
    set_alarm(2.0,0.0,"remove_the_object",ob);
}
void
remove_the_object(object ob)
{
    command("emote grasps the deep dragon skin and chants a mighty prayer "+
        "to Lolth!");
    command("exa thesummoningspellforthedrowraiders");
    command("emote laughs triumphantly as a portal opens to the surface "+
        "world!");
    command("say Come forth my raiders, and savage the surface world!!!");
    command("emote cackles demonically as she disappears in a puff of "+
        "acrid-smelling smoke!\n");
    if(matron = present("shrineerune",environment(TP)));
    {
        matron -> remove_object();
    }
}

void
init_living()
{
    ::init_living();
    if(interactive(TP))
        command("grin "+TP->query_name());
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(CPASS(arm/piwafwi));
    arm -> move(TO);
    arm = clone_object(CPASS(arm/dw_boots));
    arm -> move(TO);
    command("wear all");
    arm = clone_object(CPASS(drow/obj/dhwand));
    arm -> move(TO);
    wep = clone_object(CPASS(drow/wep/h5_mat_whip));
    wep -> move(TO);
    command("wield all");
    command("grin dem");
    MONEY_MAKE_PC(random(4))->move(TO,1);
    MONEY_MAKE_GC(random(12))->move(TO,1);
}
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;
    
    me = TO;
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
    if (ob[i]->query_see_blood())
        ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = TO;
    
    attacktype = random(5);
    if (attacktype == 1)
        {
        
        ob =  FILTER_LIVE(all_inventory(environment(me))) - ({ me });
        
        for (i = 0; i < sizeof(ob); i++)
        {
            penet = 600 + random(400);
            penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_COLD) / 50;
            hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
            
            how = "not harmed";
            if (hitresult[0] > 0)                  
                how == "barely frozen";
            if (hitresult[0] > 10)
                how = "slightly frozen";
            if (hitresult[0] > 20)
                how = "frozen quite badly";
            if (hitresult[0] > 40)
                how = "frozen very badly";
            if (hitresult[0] > 60)
                how = "utterly frozen";
            
            ob[i]->catch_msg("You hear a rhythmic chanting and then a deadly eruption "+
                "of deathly cold shoots forth from the matron mother's hands at you!\n");
            ob[i]->catch_msg("You were " + how + " by the unnatural cold!\n");
            tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the unnatural cold!\n", ob[i]);
            
            if (ob[i]->query_hp() <= 0)
                ob[i]->do_die(me);
        }
        return 1;
    }
    
    if (attacktype == 2)
        {
        if (heal == 5)
            {
            return 0;
        }
        heal += 1;
        write("The matron mother chants a prayer to Lolth.\n"+
            "She is surrounded in a brilliance of red and now looks much better!\n");
        say("The matron mother chants a prayer to Lolth.\n"+
            "She is surrounded in a brilliance of red and now looks much better!\n");
        me->heal_hp(1000);
        return 1;
    }
    return 0;
}
