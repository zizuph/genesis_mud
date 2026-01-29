inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
/* by Antharanos */
int heal;
void
create_monster()
{
    set_name("viconia");
    add_name("priestess");
    add_name("matron");
    set_race_name("drow");
    set_adj("ancient");
    add_adj("withered");
    set_long("A venerable drow female, judging from her withered features, "+
      "she must be well into her sixth century of existence. It is truly a "+
      "mark of her cunning and ingenuity to have survived this long.\n");
    set_extra_long("Her left hand is covered with a glove as black as death.\n");
    set_gender(G_FEMALE);
    set_all_hitloc_unarmed(20); /* A permanent protective ac spell */
    set_stats(({120,150,120,25,25,100}));
    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_WEP_POLEARM,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_SPELLCRAFT,90);
    set_skill(SS_HIDE,50);
    set_skill(SS_SNEAK,50);
    set_alignment(-1000);
    set_knight_prestige(1000);
    set_act_time(3);
    add_act("smirk");
    add_act("grin menacingly all");
    add_act("cackle dem");
    add_act("laugh evil");
    add_act("hide");
    add_act("say Wael!");
    set_cact_time(3);
    add_cact("grin mer all");
    set_title("Noquar, the Matron Mother of House Noquar, Eighth House of Undraeth");
    add_speak("The glory of Lolth is supreme, soon all our enemies shall "+
      "fear Duiss Aszbhar!\n");
    add_ask(({"duiss aszbhar"}),
      "They are the Streeakh.\n");
    add_ask(({"streeakh"}),
      "Wael! Every Drow knows what a Streeakh is!\n");
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    trig_new("%w 'starts' 'to' 'search' %s","react_attack");
}
void
emote_hook(string emote, object actor, string ad)
{
    if(emote == "spit")
	set_alarm(3.0,0.0,&command("kill "+lower_case(actor->query_name())));
}

int
react_attack(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(2.0,0.0,"return_attack",who);
	return 1;
    }
}
void
return_attack(string who)
{
    object obj;
    int ran;
    if(obj = present(who, environment()))
    {
	command("say Iblith!");
	command("kill " + (obj->query_real_name()));
    }
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
    wep = clone_object(CPASS(drow/wep/h8_mm_halberd));
    wep -> move(TO);
    command("wield all");
    arm = clone_object(CPASS(drow/obj/h8_insignia));
    arm -> move(TO);
    MONEY_MAKE_PC(random(2))->move(TO,1);
    MONEY_MAKE_GC(random(10))->move(TO,1);
}
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;
    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i=0;i<sizeof(ob);i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    int i;
    me = TO;
    if(random(20)==0)
    {
	TO->command("emote calls upon the unholy power of Lolth.");
	TO->command("say Quarvalsharess ultrin!");
	set_alarm(3.0,0.0,"get_dead");
	return 0;
    }
    if(random(4))
	return 0;
    hitresult = enemy -> hit_me(300 + random(300), MAGIC_DT, me, -1);
    if (hitresult[0]>0)
    {
	me->catch_msg("You touch your enemy with the hand of death.\n");
	enemy->catch_msg(QCTNAME(me)+" touches you with the hand of death!\n");
	tell_watcher(QCTNAME(me)+" touches "+QTNAME(enemy)+" with the hand of death!\n",enemy);
	if (enemy->query_hp()<=0)
	{
	    enemy->catch_msg("You feel your soul being wrenched from your body!\n");
	    tell_watcher(QCTNAME(enemy)+" collapses as "+enemy->query_possessive()+" soul is wrenched from "+enemy->query_possessive()+" body!\n",enemy);
	    enemy->command("scream");
	    enemy->do_die(me);
	}
	return 0;
    }
    me->catch_msg("You try to touch your enemy with the hand of death but miss.\n");
    enemy->catch_msg(QCTNAME(me)+" tries to touch you with the hand of death but misses.\n");
    tell_watcher(QCTNAME(me)+" tries to touch "+QTNAME(enemy)+" with the "+
      "hand of death but misses.\n",enemy);
    return 0;
}

void
get_dead()
{
    object dead;
    dead = clone_object(CPASS(drow/npc/dead));
    dead->move(E(TO));
    tell_room(E(dead),QCTNAME(dead)+" arrives from the pool of darkness.\n");
    dead->command("assist drow");
}
