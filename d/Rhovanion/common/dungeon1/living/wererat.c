inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/attack.c";
inherit "/std/combat/unarmed";

#include "/d/Rhovanion/defs.h"
#include <wa_types.h>

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_BCLAW 3
#define H_HEAD 0
#define H_BODY 1
#define H_RARM 2
#define H_LARM 3
#define H_RLEG 4
#define H_LLEG 5

static int morphed=0;
static int counter=0;
static int id;

void
create_monster() {
   set_name("rat");
   set_race_name("rat");
   set_long("@@dependent_morphed2");
   set_adj("red-eyed");
   set_adj("giant");
   set_stats(({ 75, 50, 80, 30, 55, 80 }));
   set_gender(0);
   set_aggressive(0);
   
   set_alignment(-500);
   set_hp(800);
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(CONT_I_WEIGHT, 85000);
   add_prop(CONT_I_VOLUME, 70000);
   set_attack_unarmed(A_BITE, 50, 45, W_IMPALE, 25, "festering bite");
   set_attack_unarmed(A_LCLAW, 35, 30, W_SLASH, 28, "left claw");
   set_attack_unarmed(A_RCLAW, 35, 30, W_SLASH, 28, "right claw");
   set_attack_unarmed(A_BCLAW, 35, 35, W_BLUDGEON, 19, "back claws");
   set_hitloc_unarmed(H_HEAD, (({ 60, 50, 55, 60 })), 10, "head");
   set_hitloc_unarmed(H_BODY, (({ 50, 55, 45, 60 })), 20, "body");
   set_hitloc_unarmed(H_RARM, (({ 65, 45, 50, 65 })), 15, "right arm");
   set_hitloc_unarmed(H_LARM, (({ 65, 45, 50, 65 })), 15, "left arm");
   set_hitloc_unarmed(H_RLEG, (({ 50, 35, 40, 50 })), 20, "right leg");
   set_hitloc_unarmed(H_LLEG, (({ 50, 35, 40, 50 })), 20, "left leg");
   set_cchat_time(10);
}

public void
attacked_by(object ob) {
   ::attacked_by(ob);
   
   /* Don't need to do it if it has already been done once. */
      if (morphed) return;
   
   morphed = 1;
   this_object()->set_race_name("wererat");
   this_object()->set_name("wererat");
   this_object()->set_aggressive(1);
   this_object()->remove_adj("red-eyed");
   this_object()->remove_adj("giant");
   this_object()->set_adj("hairy");
   this_object()->set_adj("vicious");
   this_object()->set_act_time(10);
   this_object()->add_act("emote thros back its head and lets " +
      "loose a beastly roar!\n" +
      "You think you feel the room quake.");
   this_object()->add_act("say I... will... rip... you... " +
      "to shreds!   in a very gutteral voice.");
   this_object()->add_act("emote grabs you by your neck and " +
      "hurls you against the wall!\n" +
      "You slide painfully down the wall and into the water.");
   set_alarm(3.0,0.0,"clone_rat");
}

/* most of these functions is not needed since you change things in
attacked_by
I suggest you do the same with the long description, since it's
a waste to use a VBFC (the @@ thing) in this case */

public string
dependent_morphed1() {
   if (!morphed)
      return "rat";
   else
      return "wererat";
}
public string
adj_morphed1() {
   if (!morphed)
      return "red-eyed";
   else
      return "hairy";
}
public string
adj_morphed2() {
   if(!morphed)
      return "giant";
   else
      return "vicious";
}
public string
aggressive_morphed() {
   if (!morphed)
      return "0";
   else
      return "1";
}
public string
dependent_morphed2() {
   if (!morphed)
      return "This oversized beast is seemingly ignoring you. " +
   "This rat has very unnerving and queer eyes, ratty slicked " +
   "down black fur, and some vicious looking rot-stained " +
   "claws.  This rat surely must be the carrier of some " +
   "heinous disease, not to mention its smell of rotting death.\n";
   else
      return "This horror of the dark powers is standing before " +
   "you half-man, half-rat creature staring at you with evil " +
   "red eyes and poising its vicious, rot and blood stained " +
   "claws to rip you to shreds.  Long, yellow fangs extend " +
   "from the beast's mouth and it reaks of its last kill.\n";
}

/* no need to have this function returning anything */
void
clone_rat() {
   command("emote grows taller and taller and shapeshifts into...\n" +
      "a rat-like humanoid form!");
   id = set_alarm(5.0,15.0,"clone_rat2");
}

clone_rat2() {
   seteuid(getuid());
   if (counter++ >= 10) 
      {
      remove_alarm(id);
   }
   /* Shouldn't this emote come from the new rat ? */
   command("emote emits a shrill scream and a form pops up from beneath the water.");
   clone_object("/d/Rhovanion/common/dungeon1/living/rat4.c")
   ->move(ENV(TO));
}
