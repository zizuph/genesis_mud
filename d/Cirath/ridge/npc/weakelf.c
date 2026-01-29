/* These are the weaker members of the tribe of elven raiders camped
   in southern portion of the desert west of Tyr. 
   Code by Dethraine, April 1998. (c) Damian Horton.
*/
 
#pragma strict_types
#pragma save_binary
 
inherit "/d/Cirath/std/monster";
#include <wa_types.h>
#include "defs.h"
#include "/d/Cirath/common/defs.h"

#define EDESC ({"attentive", "suspicious", "unstrustworthy","young"})[random(4)]
#define EBODY ({"body_lth","body_pad"})[random(2)]
#define EHEIGHT ({"tall","tall","very tall","very tall","extremly tall"})[random(5)] 
#define QTENEMY  (me->query_the_name(enemy))
#define QCTENEMY (me->query_The_name(enemy))

void
arm_me()
{

    int wep;
    int arm;

    wep = random(3);
    arm = random(4);

    switch(wep)
      {
      case 1:
	    clone_object(RIDGE_WEP+"long_bone_dagger.c")->move(TO);
	    clone_object(RIDGE_WEP+"long_bone_dagger.c")->move(TO);
      case 2:
	    clone_object(TYR_WEP+"chipper.c")->move(TO);
	default:
   	    clone_object(RIDGE_WEP+"stone_spear.c")->move(TO);
      }
    
    switch (arm)
      {
      case 1:
          clone_object(TYR_ARM+"head_lth.c")->move(TO);
	case 2:
	    clone_object(TYR_ARM+"legs_lth.c")->move(TO);
	default:
      }

    clone_object("/d/Cirath/tyr/arm/"+ EBODY)->move(TO);
    command("wield all");
    command("wear all");
}
 
void
create_monster ()
{
    set_name("elf");
    add_prop (LIVE_I_NEVERKNOWN, 1);
    set_race_name("elf");
    set_adj(EDESC);
    set_long("This elf is a member of the Mikla Noth clan: "+
        "a tribe of elven raiders frequently sighted in the vicinity "+
        "of Tyr. They make their living by stealing what they can, "+
        "employing stealth, treachery and force as necessary.\n");

    set_height(EHEIGHT);
    set_random_weight();
    set_appearance_offset((-40)+random(80));

    set_stats(({50+random(20),60+random(20),55+random(20),
        55+random(20),55+random(20),55+random(20)}));

    set_skill(SS_WEP_KNIFE, 40+random(20));
    set_skill(SS_WEP_POLEARM, 40+random(20));
    set_skill(SS_WEP_CLUB, 40+random(20));
    set_skill(SS_DEFENCE, 42+random(20));
    set_skill(SS_PARRY, 35+random(20));
    set_skill(SS_UNARM_COMBAT, 40+random(20));
    set_skill(SS_BLIND_COMBAT, 15+random(30));
    set_skill(SS_2H_COMBAT, 35+random(25));
    set_alignment(300 -random(700));
    set_exp_factor(110);
    
    set_act_time(10);
    add_act("emote eyes you with suspicion.");
    add_act("emote laughs for a moment.");
    add_act("emote wipes the sweat from his brow.");
    add_act("says something in "+HIS_HER(TO)+" tribal language.");

    set_cact_time(7);
    add_cact("emote shouts loudly in the elven tongue!");
    add_cact("emote grips his weapon with determination.");
    add_cact("emote battles with swiftness and grace.");
}

/************************ PSIONIC BLAST ***************************/

/* This attack causes a small amount of mana damage to foes. However, if the
   foe has no mana left, 5 times that damage is dealt to the foes physical
   hit points... which would well result in death!
*/

int
special_attack(object enemy)
{
    object me;
    float hitresult;
    string how;
    int damage;
    int enemy_mana;
    int physical_damage;
 
    me=this_object();
 
    if(random(20)) return 0;

    damage = INT(me)+random(160)-DIS(enemy)-random(80);
    enemy_mana = enemy->query_mana();
    hitresult = damage/enemy_mana;

    if (hitresult <= 0)
    {
         enemy->catch_tell(QCTENEMY+" attempts to attack you mentally, but "+
             "your superior mental strength renders the attack harmless.\n");
         return 1;
    }

    if (hitresult > 1)
    {
         physical_damage = 5 * (damage - enemy_mana)
         enemy->catch_tell("Blinding agony erupts through your mind as "+
             QTENEMY+" strikes out at you mentally. You are too weak to "+
             "defend yourself against his mental onslaught and the mental "+
 		 "anguish quickly becomes a physical one, with the pain "+
             "becoming reality!\n");
         enemy->set_mana(0);
         enemy->heal_hp( -(physical_damage));

         if ((enemy -> query_hp()) <= 0)
         {
	       enemy->catch_tell("The pain becomes to great for you to bear "+
                 "and you lose consciousness...\n");
             enemy->do_die(me);
         }
         
         return 1;
    }

    if (hitresult > 0) how = "an insignifigant amount  ";
    if (hitresult > 5) how = "a little ";
    if (hitresult > 15) how = "some ";
    if (hitresult > 30) how = "a lot";
    if (hitresult > 50) how = "too much ";
 
    enemy->catch_msg("A sharp stabbing pain strikes the back of your mind "+
        "as "+QTENEMY+" attacks you mentally! You manage to defend "+
        "against "+HIS_HER(me)+" mental assault, but the effort drains "+
        how+"of your mental energies.\n");

    return 1;
} 
