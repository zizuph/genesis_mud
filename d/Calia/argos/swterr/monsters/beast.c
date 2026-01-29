// BEAST : Lilith 
// 30 aug 1996

// IDEAS:
// give it an object...spectacles?...to see invis :)
// denis wants the lair (pentagram) to be a place where the cenobites
// could find summoning/banishing/portal spells 
// lair: small, magic laboratory, pentagram, books.

/* have him curse his killer:
I curse you with loneliness and sorrow, palsy and pain;
(unable to lead or join a team, spontaneously unwield stuff, phantom pain)
Water will soothe you not, and food will strenghten you not; 
(cannot eat or drink)
And the doors of your home will not admit you to rest. 
(set startloc somewhere and not allow it to reset until curse is lifted). 
*/

inherit "/d/Avenir/inherit/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Avenir/common/common.h"

// rename hitlocs
#define A_BITE   TS_HEAD 
#define A_LCLAW  TS_LHAND
#define A_RCLAW  TS_RHAND
#define A_RFOOT  TS_RFOOT
#define A_LFOOT  TS_LFOOT
#define A_HORN   TS_HEAD

#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_WING   (TS_RARM | TS_LARM)
#define H_LFQ    TS_LFOOT
#define H_RHQ    TS_RFOOT

#define ETO         environment(this_object())
#define CURSE_OBJ   "/d/Avenir/lilith/temp/beast/cu"

public string
query_combat_file()
{
    return "/d/Avenir/lilith/temp/conquer";
}

void re_attack();
void do_heal();
void break_worn();
int check_invis=0;

void
create_creature()
{
    set_name("beast");
    add_name(({"devil", "demon", "being", "creature", "monster"}));
    set_race_name("beast");
    set_adj(({"sinister", "grotesque"}));
    set_short("sinister beast");
    set_pshort("sinister beasts");
    set_long("There is something sinister about this grotesque "+
       "creature. It stands upon the hind-legs of a goat, while "+
       "its torso is that of a giant and hairless humanoid. "+
       "It has talon-like claws and the leathery wings of a bat, "+
       "and upon its head are horns of every shape and size. "+
       "Within its gaping mouth are hook-like teeth. There is a "+ 
       "keen intelligence glimmering behind the slitted eyes, "+
       "and most worrisome of all, malevolent amusement as well. "+
       "\n");
   
             /*  str, con, dex, int, wis, dis  */
    set_stats(({ 150, 150, 150, 175, 175, 175 }));
   
    set_skill(SS_BLIND_COMBAT, 95);
    set_skill(SS_UNARM_COMBAT, 95);
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_AWARENESS, 95);

    set_alignment(-300);
    set_knight_prestige(500);                                                                                                 
               
    set_cact_time(3);
      add_cact("emote says: The sun is a most foul creation. It has "+
         "tainted you, and death by purification is your only "+
         "salvation.");
      add_cact("emote says: I will send you to Zaren! You will nurse "+
         "blood from her paps as she guts you with her claws, and her "+
         "children will feed upon your entrails!");
      add_cact("emote says: You cannot kill me. Ten of you cannot "+
         "kill me! Do you hear? Ten of you and then ten more!");
      add_cact("emote says: Suicide is the ultimate sacrificial "+
         "offering...To which god shall we dedicate you?");
      add_cact("emote says: You are almost too pathetic to be amusin"+
         "g but I am sure that you will squeal like a gutted pig as "+
         "you die, and so I will look forward with delight to that "+                                              "moment.");
      add_cact("emote says: Flee you fool! Flee for your life and I "+
         "will not follow.");
      add_cact("emote says: You will pay for your blasphemy! Mark "+
         "my words!\n");
      add_cact("emote says: Your gods were too sparing with the gift "+
         "of brains the day your mother whelped you.");
      add_cact("emote says: I met your mother once. I can see the "+
         "family resemblance. I gutted her with this horn right "+
         "here, and feasted upon her kidneys. She was a tasty "+
         "morsel, your mother. A pity she was so ugly...");
      add_cact("emote says: I am that which dwells in your dreadest "+
         "dreams, in that place of all places you fear most to go.");
      add_cact("emote says: I am of that which lives eternal. In "+
         "fighting me you seek your body's death, not mine.");
      add_cact("emote says: Shadow-elves on the Hunt are more "+ 
         "impressive opponents than you Outlanders.");
      add_cact("emote says: You will meet your maker when I've "+ 
         "tired of toying with you.");
      add_cact("emote says: How tiresome! Won't you die already?");
      add_cact("emote says: Thou art damned in this life and the "+
         "next.");
      add_cact("yawn");
      add_cact("emote say: Lars and I have a deal, crell. Perhaps "+
         "I shall ask him to give me you.");
         
    set_act_time(4);
      add_act("emote bares its hooked teeth in a menacing grin.");	
      add_act("breathes heavily, filling the air with the putrid "+
         "smell of death and decay.");
      add_act("emote flexes its muscles, making them ripple "+
         "disconcertingly in the half-light.");
      add_act("emote appears to be busy preparing for a ritual.");
      add_act("emote laughs at you.");
      add_act("emote says: You'd better have a good reason for "+
         "being here. I don't appreciate interruptions.");
      add_act("emote picks at the bits of flesh stuck in its teeth.");
      add_act("emote speaks to you in an arcane language.");
      add_act("emote rustles its leathery wings in irritation.");
      add_act("emote says: Leave me!");

    set_attack_unarmed(A_BITE,  35, 35, W_IMPALE,   15, "hooked teeth");
    set_attack_unarmed(A_HORN,  60, 40, W_IMPALE,    5, "curved horn");
    set_attack_unarmed(A_LCLAW, 20, 25, W_SLASH,    30, "left claw");
    set_attack_unarmed(A_RCLAW, 20, 25, W_SLASH,    30, "right claw");
    set_attack_unarmed(A_LFOOT, 50, 60, W_BLUDGEON, 10, "left hoof");
    set_attack_unarmed(A_RFOOT, 50, 60, W_BLUDGEON, 10, "right hoof");
   
    set_hitloc_unarmed(H_HEAD, ({ 70 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 90 }), 50, "upper-body");
    set_hitloc_unarmed(H_WING, ({ 90 }), 10, "wing");
    set_hitloc_unarmed(H_LFQ,  ({ 70 }), 15, "left forearm");
    set_hitloc_unarmed(H_RHQ,  ({ 70 }), 15, "right hind-quarter");
   
    add_prop(LIVE_I_SEE_DARK, 1 + random(10));
    add_prop(MAGIC_I_RES_FIRE, 40 + (random(35)));
    add_prop(MAGIC_I_RES_POISON, 40 + (random(35)));
    add_prop(LIVE_I_SEE_INVIS, 1);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_CORPSE, 1);
}

int
query_knight_prestige() { return 1000; }


int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
// put code in here so that there is a chance for a horn to come off
// when the beast impales a player with it.

   if (aid == A_BITE) 
   {
       tell_object(enemy, "Hook-like teeth sink "+
      		"into you, tearing your flesh!\n");
   }
   
   return 0;
}

void
re_attack()
{
    object *people;
       
    people = filter(all_inventory(ENV(TO)), interactive); // all players
    set_alarm(4.0,0.0,                                  &aggressive_attack(people[random(sizeof(people))]));
}

int 
uninvis_me()
{
    if (!check_invis) return 0;
    
    tell_room(ENV(TO), 
        "The form of a sinister beast appears before your "+
        "very eyes!");
    TO->remove_prop(OBJ_I_INVIS);  
    check_invis = 0;
    return 1;
}

int
invis_me()
{
   if (check_invis) return 0;

   tell_room(ENV(TO), QCTNAME(TO)+" makes some complex gestures " +
         "in the air while chanting some words in an arcane "+
         "language.\nThe sinister beast disappears before your "+
         "very eyes!!\n");
   TO->add_prop(OBJ_I_INVIS, 1 + random(9));
   set_alarm(45.0, 0.0, uninvis_me);
   check_invis = 1;
   return 1;
}


// turn this into a real spell?, perhaps a real object having the spell?
void
do_heal()
{
    TO->heal_hp(random(40) + 150);
}

/*
 * Special attack code starts here
 */

int
is_valid_enemy(object who)
{
    if (environment(who) == environment(TO) && !who->query_ghost())
      return 1;
    return 0;
}

object*
valid_enemies()
{
    object *ene = query_enemy(-1);
    object *ene_list = ({ });
    int i;
    ene -= ({ TO });
    for(i=0;i<sizeof(ene);i++)
      if (is_valid_enemy(ene[i]))
	ene_list += ({ ene[i] });
      else
	{
	    stop_fight(ene[i]);
	    ene[i]->stop_fight(TO);
	}
    ene_list -= ({ 0 });
    return ene_list;
}

void
fireball_2(object livin)
{
    mixed *res;
    int hitp = 400;
    string str;
    if (!is_valid_enemy(livin))
      {
	  tell_room(ENV(TO),"The flames subside.\n");
	  return;
      }
    /*hitpoint modifier on RES_FIRE*/
    hitp -= hitp * livin->query_magic_res(MAGIC_I_RES_FIRE) / 100;
    res = livin->hit_me(hitp,MAGIC_DT, TO, -1);
    hitp = res[0];
    if (hitp < 10)
      str = "only slightly";
    else if (hitp < 20)
      str = "a bit";
    else if (hitp < 40)
      str = "quite a lot";
    else if (hitp < 60)
      str = "badly";
    else
      str = "terribly";
    tell_object(livin, "You are burned "+ str +" by the flames "+
            "jetting up from the ground!\n");
    tell_watcher(QCTNAME(livin) + " is burned "+ str +
            " by the flames.\n\n", livin);
}
void
fireball_1(object ene1, object ene2)
{
    object vic2 = ene2;
    if (ene1 == ene2)
      vic2 = 0;
    if (random(250) > DEX(ene1))
      fireball_2(ene1);
    else 
      {
	  tell_object(ene1,"\nYou succeed in dancing out of the flames "+
            "reach!\n");
	  tell_watcher(QCTNAME(ene1) + " manages to dance out of the "+
            "flames reach.\n\n", ene1);
	  if (vic2 && (random(250) > ene2->query_base_stat(SS_DEX)))
	    fireball_2(ene2);
	  else if (vic2)
	    {
		tell_object(ene2,
                "\nYou succeed in dancing out of the flames reach!\n");
		tell_watcher(QCTNAME(ene2) + 
                " manages to dance out of the flames reach.\n\n",ene2);
	    }
	  tell_room(ENV(TO),
            "The flames burn themselves out, leaving behind "+
		"the scent of sulphur.\n");

      }
}

void
fire_balls(object victim)
{
    object *ene = valid_enemies();
    object vic1,vic2;
    tell_watcher("\n"+QCTNAME(TO)+ " roars words that seem to weight " +
		 "the air with their utterance.\nThe ground erupts into "+
		 "flames that jet toward you!\n");
    if (random(4))
      vic1 = victim;
    else
      vic1 = ene[random(sizeof(ene))];
      vic2 = ene[random(sizeof(ene))];
    set_alarm(1.0,0.0,"fireball_1",vic1,vic2);
}

void 
fright_all()
{
    object *people;
    int num;
   
    num = (1 + random(9));
    if (num == 5)
    {
       people = filter(all_inventory(ENV(TO)), interactive);               people->add_panic(500);
       people->run_away(); 
    }
}

int
fright(object victim)
{
    object enemy;
    object *people;
    int num;
    mixed *wep;
   
    enemy = TO->query_attack();
    num = ( (enemy->query_stat(SS_DIS)) - (TO->query_stat(SS_INT)/2) + 
          random(50) );
   
    if (num < 100)
    {
      if (CAN_SEE(TO, enemy) && CAN_SEE(enemy, TO))
      {     
         enemy->catch_msg("The slitted eyes of "+QCTNAME(TO)+" stare "+
            "intently into yours. It smiles fleetingly, and in that "+
            "moment you are convinced that it is allowing you to live "+
            "because your pathetic efforts amuse it.\n");
         tell_room(ENV(TO), QCTNAME(TO)+" smiles briefly at " + 
            QCTNAME(enemy) + ".\n", enemy);
         enemy->add_panic(random(50));
	   enemy->command("$panic");
         wep = enemy->query_weapon(-1);
         if (wep == ({ }))
         { 
            enemy->command("$tremble");        
         }
         else
         enemy->command("$unwield all");
         return 1;
      }
    }
    enemy->catch_msg("Your ears ring with the sound of "+
       "disdainful laughter.\n");
    return 1;
}

break_worn(object victim)
{
    object *all;
    int i;

    all = all_inventory(victim);

    for (i=0; i<sizeof(all); i++) {
        if (!function_exists("create_armour", all[i])) continue;
        if (all[i]->query_worn() == victim) 
        {
          if (all[i]->query_prop(MAGIC_AM_MAGIC)) 
          {
           victim->catch_msg("A steel-shod hoof strikes your " +
               all[i]->short() + ", but does little damage.\n");
          }
          else
          {          
           victim->catch_msg("A steel-shod hoof strikes your " +
               all[i]->short() + " with tremendous force.\n");
           all[i]->remove_broken();
           return;
          }
        }
    }
    victim->catch_msg("The steel-shod hoof strikes you with " +
           "such force that you are thrown to the ground, "+
           "unable to breathe!\n");
    victim->add_attack_delay(30);
    victim->stop_fight(TO);
    TO->stop_fight(victim);
    set_alarm(2.0, 0.0, re_attack);
}


int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
      {
	  TO->stop_fight(victim);
	  return 1;
      }

    switch (random(9))
      {
	   case 0: fright(victim);
	        return 0;
         case 1: fire_balls(victim); 
	        return 0;
         case 2: break_worn(victim);
              return 0;
         case 3: fright_all();
              return 0;
	   case 4: do_heal();
	        return 0;
         case 5: invis_me();
              return 0;
	   default: 
      }
    return 0;
}

void
do_die(object killer)
{
   int i;
   string str;
   object *enemies;
    
   if (query_hp() > 0) 
      return;

   if (killer && ETO == environment(killer)) 
     {
    TO->remove_prop(OBJ_I_INVIS);  
       killer->catch_msg(QCTNAME(TO) + " smiles directly at you.\n" +
          QCTNAME(TO) + " calls out in terrible ringing tones:  "+
          "I curse you with loneliness and sorrow, palsy and pain; "+
          "water will soothe you not, food will strengthen you not, "+
          "and the doors of your home will not admit you to rest!\n");
       tell_room(ETO, QCTNAME(TO) + " smiles directly at " +
          QTNAME(killer) + ".\n" + QCTNAME(TO) + " calls out in "+
          "terrible ringing tones:  "+
          "I curse you with loneliness and sorrow, palsy and pain; "+
          "water will soothe you not, food will strengthen you not, "+
          "and the doors of your home will not admit you to rest!\n",
          ({TO, killer}));
       clone_object(CURSE_OBJ)->move(killer);
    }
   command("drop all");      
   tell_room(ENV(TO), QCTNAME(TO) + " moves to the center of the "+
      "pentagram.\nHe kneels there, speaking words which cause "+
      "the air to shimmer and twist.\nFlames rise from the floor, "+
      "and when they subside, the "+ QTNAME(TO) +" is gone.\n");
    
    // STATSERV_LOG_EVENT ?
    ::do_die(killer);
}

