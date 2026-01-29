/*******************************************************
* Kabal.c - A very dangerous npc, that can only be met
*           if the player insert a ghouls heart into
   *            the chest of a corpse placed in
*           /d/Kalad/common/wild/pass/dwarf/crypt/c26.c
*
*           Made by Korat, november 1996
*******************************************************/
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"

#define ACID_CLOUD "/d/Kalad/common/wild/pass/dwarf/obj/acid"
int num_of_hits = 0; /* times we are hit with damage */
int last_hp; /* what hp we had last attackround */

/***************************************
* Function: make_stun
* Will move a stun-object to the player <enemy>
* Arguments: enemy - the player to move the stun into
***************************************/
void
make_stun(object enemy)
{
   int i;
   object stun;
   object *ob = all_inventory(enemy);
   
   for(i=0;i<sizeof(ob);i++)
   {
      if(ob[i]->query_name()=="stun")
         {
         return;
       }
   }
   seteuid(getuid(TO));
   stun = clone_object(CPASS(dwarf/obj/stun_kabal));
   stun -> move(enemy);
   enemy->catch_msg("Your body freezes up from the terrible shock!\n");
   return;
}

create_monster()
{
   ::create_monster();
   set_name("kabal");
   set_living_name("kabal");
   set_race_name("human");
   set_adj("decaying");
   add_adj("remains of a");
   set_long("A mighty figure of death and destruction, this reincarnated "+
      "human towers above you in strenght, height and evilness. The flesh "+
      "seems to be decaying slowly in front of your eyes, but "+
      "you also realise this being will create much destruction "+
      "before it finally will fall apart. It is dressed in an old "+
      "but sturdy platemail that seems to be made of pure mithril. "+
      "Attached to his arm you see a battered old shield that "+
      "obviously cannot give much protection. It carries an emblem "+
      "that resembles a clenched fist.\n");
   
   /* This npc is a major foe */
   set_stats(({190,210,200,160,160,160}));
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_AWARENESS,100);
   set_skill(SS_SPELLCRAFT,100);
   add_prop(OBJ_I_RES_ACID,100);
   add_prop(LIVE_I_UNDEAD,100);
   add_prop(OBJ_I_RES_MAGIC,40);
   add_prop(OBJ_I_RES_DEATH,50);
   add_prop(OBJ_I_RES_FIRE,30);
   add_prop(LIVE_I_QUICKNESS, 200);
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_SEE_INVIS, 50);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   add_prop(NPC_M_NO_ACCEPT_GIVE,1);
   
   set_alignment(0);
   
   set_act_time(3);
   add_act("emote stares at you demonically.");
   add_act("emote stares at you with death in its eyes.");
   add_act("emote looks at you and grins with destruction in mind.");
   set_cact_time(3);
   add_cact("say Destruction of your lives will be my own salvation!");
   add_cact("emote points at you with a bony finger and laughs demonically.");
   add_cact("laugh dem");
   
   set_default_answer("Kabal answers you with a deadly silence.\n");
   set_random_move(10);
   set_title("the bane of lesser races and saviour of human kind, returned "+
      "from the grave to punish all");
   set_knight_prestige(2400);
   trig_new("%w 'attacks' 'you!\n' %s","react_attack");
}

void
arm_me()
{
   object mine;
   seteuid(getuid(TO));
   mine = clone_object(CPASS(dwarf/wep/cer_axe));
   mine -> move(TO);
   mine = clone_object(CPASS(dwarf/arm/kabal_ring));
   mine -> move(TO);
   mine = clone_object(CPASS(dwarf/arm/kabal_plate));
   mine -> move(TO);
   command("wield all");
   command("wear all");
   last_hp = TO->query_hp();
}

/************************************
* Function: Do_die
* Description: Does some commands before we kill this npc
************************************/
int
do_die(object killer)
{
   if(query_hp() > 0) return 0;
   TO->command("salute");
   TO->command("emote disintegrates into fleshless bones.");
   ::do_die(killer);
   return 1;
}

/************************************
* Function: react_attack
* Description: Prepares the npc for a reaction towards attacks
************************************/
int
react_attack(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(0.0,0.0,"return_attack",who);
      return 1;
   }
}

/************************************
* Function: return_attack
* Description: Acts towards the player <who> with a special attack
************************************/
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      tell_room(E(TO),"As the decaying remains of a human speaks, a foul "+
         "smell of decay and death reaches your nostrils.\n");
      TO->command("kill " + (obj->query_real_name()));
      obj->catch_msg("The decaying remains of a human snarls to you: Time to die!");
      set_alarm(1.0,0.0,"point_death",obj);
   }
}

void
attacked_by(object ob)
{
   ::attacked_by(ob);
}


/**************************************************
* Function: special_attack - called each combatround
* Description: Does either a death-spell attack (1/10 chance) or
*              a vampiric touch that damages enemy and heals this npc (1/4 chance)
*************************************************/
int
special_attack(object enemy)
{
   object me = this_object();
   object comb_obj = TO->query_combat_object();
   mixed* hitresult;
   string how;
   int i, my_hp;

   /* we first check if we have less hp than last time */
   my_hp = me->query_hp();
   if (my_hp < last_hp)
      {
      /* we got hit with damage, so we will bleed some acid */
      num_of_hits = num_of_hits + 1;
      if (num_of_hits > random(3)+2)
         {
         num_of_hits = 0;
         set_alarm(1.0,0.0,"make_acid");
      }
      tell_room(E(TO),"Some acidious smoke seeps out from "+
         "the small wounds of the decaying humans body.\n");
   }
   last_hp = my_hp; /* we need to remember the hp we have */


   /* a 1 to 15 chance of attacking with the toughest attack */
   if (random(15) == 0)
      {
      set_alarm(1.0,0.0,"point_death",enemy);
      return 0;
   }
   
   /* a 1 to 4 chance of attacking with a general special attack */
   if (random(4))
      return 0;
   
   /* we damage the player according to the players con since
   this is a vampiric kind of attack. */
   hitresult = enemy -> hit_me(random(enemy->query_base_stat(SS_CON))+
      200, MAGIC_DT, me, -1);
   
   if (hitresult[0]>0)
      {
      me->catch_msg("You touch your enemy with your chilling hands.\n");
      enemy->catch_msg(QCTNAME(me)+" touches you with its decaying "+
         "fingers. A deadly chill runs through your body!\n");
      tell_watcher(QCTNAME(me)+" touches "+QTNAME(enemy)+" with its "+
         "decaying fingers. "+QCTNAME(enemy)+" pales visibly!\n",enemy);
      
      if (enemy->query_hp()<=0)
         {
         enemy->catch_msg("The touch seems to draw out the rest of your "+
            "life-energy.\n");
         tell_watcher(QCTNAME(enemy)+" starts to shake as the rest of "+
            enemy->query_possessive()+" energy of life is drawn out of "+
            "the body.\n",enemy);
         enemy->command("scream");
         enemy->do_die(me);
       }
      
      /* This npc heals a bit of the damage given to the enemy (vampiric touch)  */
      TO->heal_hp(hitresult[3] / 5);
      tell_room(E(TO),QCTNAME(TO)+" seems to grow healthier as "+
         "it sucks the life-force out of "+QTNAME(enemy)+"\n");
      
      /* we stun the enemy if the attack was good enough */
         if (hitresult[0] > random (15))
         make_stun(enemy);
      
      return 0;
   }
   
   /* the npc missed with its attack */
   me->catch_msg("You try to touch your enemy but miss.\n");
   enemy->catch_msg(QCTNAME(me)+" tries to touch you with its decaying "+
      "fingers.\n");
   tell_watcher(QCTNAME(me)+" tries to touch "+QTNAME(enemy)+
      ".\n",enemy);
   return 0;
}

/*****************************************
* Function: Point_death
* Description: A special attack - a death spell - that will be
*              cast at all players attacking this npc.
*              It will also be used more seldom during combat.
*****************************************/
void
point_death(object enemy)
{
   mixed *hitresult;
   int time;
   object *ob;
   int i;
   object stun;
   object me = TO;
   
   hitresult = enemy -> hit_me(200 +
      (random(enemy->query_base_stat(SS_CON))*4), MAGIC_DT, me, -1);
   
   
   enemy->catch_msg(QCTNAME(TO)+" points at you with a crooked, bony finger.\n"+
      "A terrible force slams into you!!!\n");
   TO->catch_msg("You point at "+QTNAME(enemy)+" with your bony "+
      "finger, and feel the force of death flow in your veins.\n");
   tell_watcher(QCTNAME(TO)+" points at "+QTNAME(enemy)+" with a bony "+
      "finger. "+QCTNAME(enemy)+" seems to be struck by a terrifying "+
      "force!\n",enemy);
   if(enemy->query_hp()<=0)
      {
      tell_watcher(QCTNAME(enemy)+" is utterly devastated from "+
         "the deadly force!\n",enemy);
      enemy->catch_msg("The deadly force flows through your body like "+
         "the deep red blood in a newborn childs veins ... your sanity and "+
         "will to live dwindles away. You die ...\n");
      TO->catch_msg(QCTNAME(enemy)+" dies from your devastating force of death.\n");
      enemy->do_die(me);
   }
   
   /* ok, the living survived ... lets plex him *grin* */
   make_stun(enemy);
   return;
}

/*****************************************
* Function: make_acid
* Description: When this npc is hit with damage, acidious cloud
*              will start to seep out of its wound.
*****************************************/
void
make_acid()
{
   object acid;
   object *items;
   int i;
   
   items = FILTER_DEAD(all_inventory(E(TO)));
   for(i=0;i<sizeof(items);i++)
   {
      if (MASTER_OB(items[i]) == ACID_CLOUD) return; /* only one acid at a time */
   }
   
   tell_room(E(TO),"A rust-read acidious cloud starts to fill the area.\n");
   acid = clone_object(ACID_CLOUD);
   acid->move(E(TO));
   return;
}