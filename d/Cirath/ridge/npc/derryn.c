/* Derryn: A powerful Mul gladiator, who escaped from the slave pits
   of one of the more powerful noble houses of Tyr. He must be overcome
   for the gladiator guru quest.
   Code (c) 1998 Damian Horton */

#pragma strict_types
#pragma save_binary 

inherit "/d/Cirath/std/monster.c";
#include <wa_types.h>
#include "defs.h"
#include <options.h>
#define LOCATION "/d/Cirath/ridge"
 
mixed attackers;
 
void
create_monster ()
{
    set_living_name("derryn");
    set_name("derryn");
   set_title("the Retired Master Gladiator of Athas");
   set_race_name("dwarf");
    set_adj("thoughtful");
    add_adj("heavy-set");
   set_long("Large, and well-built, even for a dwarf, his skin betrays the"+
             "brutal scars of a gladiator. Like all dwarves, he is completely "+
             "hairless. His steely grey eyes are set deeply into his "+
             "rough-hewn face. He displays an air of quiet "+
             "confidence, and contentment. He handles his "+
             "enormous obsidian battleaxe with practiced grace.\n");
   
   set_stats(({140,115,160,80,85,130}));
   set_skill(SS_WEP_AXE, 100);
    set_skill(SS_BLIND_COMBAT, 50);
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_PARRY, 86);
    set_skill(SS_UNARM_COMBAT,68);
    set_skill(SS_AWARENESS, 56);
    set_alignment(150);
    set_exp_factor(110);
   
    set_act_time(3);
    add_act("emote contemplates his existance as a hermit.");
    add_act("emote breathes deeply, at peace with himself.");
    add_act("emote twirls his enormous obsidian battleaxe idly.");
    add_act("say What brings you into these forsaken parts of Athas?");
    add_act("emote chuckles softly to himself, saying that they never "+
            "did catch him.");

    set_cact_time(3);
    add_cact("say If its a fight you want, I'll give it to ya!");
    add_cact("say It was unwise of you to challenge me.");
    add_cact("say Leave me in peace, and I will consider not leaving you "+
             "in pieces!");
    add_cact("emote 's eyes glaze over, reason being lost to bloodlust.");
    add_cact("emote works himself into a wild battlerage.");
    add_cact("emote breaks into a sweat as his breathing becomes heavier.");
}
 
void
arm_me()
{
    clone_object(LOCATION+"/wep/enormous_axe")->move(TO);
    clone_object(LOCATION+"/arm/leather_bands")->move(TO);
    clone_object(LOCATION+"/arm/skull_helmet")->move(TO);
    clone_object(LOCATION+"/arm/kank_greaves")->move(TO);
    clone_object(LOCATION+"/arm/scaled_shirt")->move(TO);
    clone_object(LOCATION+"/arm/worn_robe")->move(TO);
    command("wield all");
    command("wear all");
}

/* sets unarmed combat off, giving more axe attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}

/* **************** DERRYN CHARGES! ******************** */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
 
    me=this_object();
 
    if(random(8)) return 0;

        if (random(1000)<WIS(enemy))
        {
             enemy->catch_msg(QCTNAME(me)+" charges ferociously at you, "+
                 "but you somehow manage to get out of his way.\n");
             tell_watcher(QCTNAME(me)+" charges ferociously at "+
                 QTNAME(enemy)+", but "+HE_SHE(enemy)+" somehow manages "+
                 "to get out of his way.\n",me,enemy);
             return 1;
        }
 
   hitresult = enemy->hit_me(300 + random(200), W_BLUDGEON, me, -1);
        how = "unharmed";
        if (hitresult[0] > 0) how = "dazed";
        if (hitresult[0] > 15) how = "injured";
        if (hitresult[0] > 30) how = "hurt";
        if (hitresult[0] > 50) how = "severely hurt";
        if (hitresult[0] > 75) how = "on the verge of collapse";
 
        enemy->catch_msg(QCTNAME(me)+" strikes you with his ferocious "+
            "charge!\n");
        enemy->catch_msg("You are " + how + ".\n");
        tell_watcher(QCTNAME(me)+" strikes "+QCTNAME(enemy)+
            " with his ferocious charge!\n"+QCTNAME(enemy)+" is "+
            how+"!\n",me,enemy);
 
        if(enemy->query_hp() <= 0) enemy->do_die(me);
 
        return 1;
}
