/*
 *  /d/Gondor/common/npc/oliphaunt.c
 *
 *  The feared Mumak
 *
 *  Elessar, May 1995
 *  Modification log:
 *  May 19th 1995, Elessar: Added extra tests against non-present enemies.
 *  June 30, 2001, Serif: Fixed typos and name queries, updated
 *      line length, indentation, description, etc.
 *  April, 2002, Serif: Added worn trappings with get_armed();
 */
#pragma strict_types
 
inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/d/Gondor/common/lib/logkill.c";

inherit "/std/act/domove.c";
inherit "/std/act/action.c";
inherit "/std/act/attack.c";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define FRACTURE_OB "/d/Gondor/common/obj/fracture"

#define STOMP_PEN   90
#define BASH_PEN    70
#define THROWN_PEN  50
#define DROPPED_PEN 20

void
get_armed()
{
    FIX_EUID
    clone_object(HAR_ARM_DIR + "trappings")->move(TO);
    command("wear all");
    command("emote trumpets loudly!");
}

public void
create_creature()
{
    int    alig = random(200) - 100;
    set_name("oliphaunt");
    add_name( ({ "mumakil", "animal", "shape", "beast", "mumak", }) );
    set_adj( ({ "grey","large"}) );
    set_short("large grey oliphaunt");
    set_long("The large shape before you is an oliphaunt! Almost big as a "
        + "house, like a grey-clad moving hill, his great legs like trees, "
        + "enormous sail-like ears spread out, with a long snout swinging "
        + "like a huge serpent and small red eyes glaring intently at "
        + "all that moves. His upturned hornlike tusks are bound with "
        + "bands of gold, and trappings of scarlet and gold drape from "
        + "his back. You feel small next to this large animal.\n");

    add_item(({"legs"}), "The great grey legs look like solid trees, "
        + "crushing anything they land on.\n");
    add_item(({"tusks"}), "On each side of the long snout, long "
        + "up-turned, horn-like tusks stick out, bound with bands of "
        + "gold. The ends of the tusks look like they have been "
        + "sharpened to emphasize their murderous usage.\n");

    set_race_name("oliphaunt");
    set_alignment(- alig);
    set_stats( ({ 180, 110, 190, 80, 80, 100 }));
    set_attack_chance( MAX(10, (random(999) - alig) / 20));
    set_skill(SS_UNARM_COMBAT, 90 + random(11));
    set_skill(SS_CLIMB,        10 + random(11));
    set_skill(SS_SWIM,         40 + random(21));
    set_skill(SS_DEFENCE,      60 + random(21));
    set_skill(SS_PARRY,        60 + random(21));

    add_prop(CONT_I_HEIGHT,        360);
    add_prop(CONT_I_WEIGHT,    2650000);
    add_prop(CONT_I_VOLUME,    2340000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_leftover(OBJ_DIR + "olitusk","tusk", 2, 0, 1, 1);

    set_act_time(15);
    add_act("emote raises his massive head and looks around.");
    add_act("emote sways back and forth slowly.");
    add_act("emote gathers some leaves from the treetops with his long "
        + "snout and eats them.");
    add_act("emote glares intently at you out of his small red eyes.");
    add_act("emote flaps his enormous ears wildly.");

    set_cact_time(10);
    add_cact("emote raises his long snout threateningly, trumpeting "
        + "loudly.");
    add_cact("emote swings his trunk wildly around.");
    add_cact("emote trumpets shrilly.");
    add_cact("emote stomps furiously with his enormous feet, "
        + "battering the ground.");
    set_alarm(2.0, 0.0, &get_armed());
}

/*
 * Define some attack and hitloc id's (only for our own benefit).
 */

#define A_TRUNK 0
#define A_RTUSK 1
#define A_LTUSK 2
#define A_RFOOT 3
#define A_LFOOT 4

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TRUNK 3

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */

public void
cr_configure()
{
   add_attack(random(20) + 60, random(20) + 80, W_IMPALE,   25, A_RTUSK);
   add_attack(random(20) + 60, random(20) + 80, W_IMPALE,   25, A_LTUSK);
   add_attack(random(20) + 60, random(20) + 60, W_BLUDGEON, 30, A_TRUNK);
   add_attack(random(20) + 60, random(20) + 60, W_BLUDGEON, 10, A_RFOOT);
   add_attack(random(20) + 60, random(20) + 60, W_BLUDGEON, 10, A_LFOOT);
 
   add_hitloc( ({ random(10) + 10, random(10) + 20, random(20) + 30}),
	   10, "head",  H_HEAD);
   add_hitloc( ({ random(10) + 10, random(10) + 10, random(20) + 30}), 
	   55, "body",  H_BODY);
   add_hitloc( ({ random(10) + 15, random(10) + 15, random(10) + 35}), 
	   30, "legs",  H_LEGS);
   add_hitloc( ({ random(10) + 10, random(10) + 10, random(15) + 45}),  
	   5, "trunk", H_TRUNK);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'.
 */

public string
cr_attack_desc(int aid)
{
   switch(aid)
   {
   case A_RTUSK:
   return "right tusk";
   case A_LTUSK:
   return "left tusk";
   case A_LFOOT:
   return "left foot";
   case A_RFOOT:
   return "right foot";
   case A_TRUNK:
   return "long trunk";
   }
   return "mind"; /* should never occur */
}

public mixed
non_aggressive_hit_me(int wcpen, object victim)
{
   object     *list, co;
   int        proc_hurt, hp,
              tmp, dam, phit,
              hloc, *hloc_id,
              j;
   string     msg;
   mixed      ac, *hloc_ac;
  
   tmp = random(100);
   co = victim->query_combat_object();
   hloc_id = co->query_hitloc_id();

   for (j = 0, hloc = 0; hloc < sizeof(hloc_id); hloc++)
   {
        hloc_ac = co->query_hitloc(hloc_id[hloc]);
        if (!sizeof(hloc_ac))
   break;
       j+= hloc_ac[1];
       if (j>= tmp)
   break;
   }
   if (hloc >= sizeof(hloc_ac))
   {
       hloc = sizeof(hloc_ac) - 1;
} 

   ac = hloc_ac[3];
   if (sizeof(ac))
   ac = ac[0];
   else if (!intp(ac))
   ac = 0;
  
   phit = random(wcpen);
   ac = random(ac);
   dam = F_DAMAGE(phit, ac);
   if (dam < 1)
   dam = 0;
   else
   {
       dam = 0;
       phit = (wcpen < 0 ? wcpen : -1);
   }
  
   hp = victim->query_hp();
  
    /*
     * Wizards are immortal. (Immoral??)
     */

   if ((int)victim->query_wiz_level() && dam >= hp)
   {
       tell_object(victim, "Your wizardhood protects you from death.\n");
       tell_room(environment(victim),
           QCTNAME(victim) + " is immortal and fails to die!\n", victim);
       return ({ 0, 0, 0, 0 });
   }
  
   /*
    * Ok, hurt me.
    */

   if (dam > 0 && hp)
   {
   proc_hurt = (100 * dam) / hp;
   if (dam && !proc_hurt)
       proc_hurt = 1;     /* Less than 1% damage. */
   }
   else if (dam > 0)
       proc_hurt = 100;
   else if (wcpen >= 0)
       proc_hurt = 0;
   else
       proc_hurt = -1;   /* Enemy missed. */

   if (dam > 0)
       victim->heal_hp(-dam);

   /*
    * Adjust the panic level.
    */

   if (proc_hurt >= 0)
        victim->add_panic(2 + proc_hurt / 5);
  
   if (random(dam) > random(victim->query_stat(SS_DIS)))
        victim->cmdhooks_break_spell();

   return ({ proc_hurt, hloc_ac[2], phit, dam });
}

int
do_foot_stomp()
{
   object *livs, *enemies, victim;
   mixed *sres;
   enemies = FILTER_PRESENT_LIVE(TO->query_enemy(-1));
   if (sizeof(enemies))
       victim = enemies[random(sizeof(enemies))];
   else return 0;
  
   if (ENV(victim) != ENV(TO)) return 0;
   sres = non_aggressive_hit_me(F_PENMOD(STOMP_PEN, 90), victim);

   if (sres[0] < 0) {
       victim->catch_msg("The large oliphaunt stomps a great foot "
           + "dangerously close to you! The ground quakes, but you are "
           + "unharmed!\n");
       say("The large oliphaunt stomps a foot dangerously close "
           + "to "+QTNAME(victim)+", who dodges away just in "
           + "time.\n",victim);
   }
   else if (sres[0] < 10) {
       victim->catch_msg("The large oliphaunt charges wildly at you, "
           + "bruising your "+sres[1]+" with one of his great legs!\n");
       say("The large oliphaunt charges, grazing "+QTNAME(victim)+" in "
           + "the "+sres[1]+" with one of his great legs.\n",victim);
   }
   else if (sres[0] < 100) {
       victim->catch_msg("The huge grey oliphaunt stampedes wildly in your "
           + "direction, and before you manage to dodge away, "
           + "a great weight crushes down on you. You hear bones "
           + "snapping, and then the pain washes over you.\n");
       say("The large oliphaunt stomps towards "+QTNAME(victim)+", who is "
           + "too slow to dodge the beast! The sound of bones snapping is "
           + "carried over the noise of battle.\n",victim);
       victim->command("$scream");
   seteuid(getuid(TO));
   if (!present("fracture",victim))
       clone_object(FRACTURE_OB)->move(victim, 1);
       log_file("curses", victim->query_name() 
           + " broke an arm fighting the "
           + "oliphaunt, " + ctime(time()) + ".\n");
   }
   else {
       victim->catch_msg("The great oliphaunt stampedes wildly towards "
           + "you, and before you can react you are knocked over "
           + "by the huge shape, feeling your life violently "
           + "crunched out of your disarrayed body.\n");
       say("The large oliphaunt rushes over "+QTNAME(victim)+", who has no "
	       + "time to react! Through the noise of battle you can hear the "
	       + "sound of "+victim->query_possessive()+" skull "
           + "crunching, and a scream of pain being brutally cut "
           + "short.\n",victim);
   }
   if (victim->query_hp() > 0 && member_array(victim, enemies))
       set_alarm(2.0,0.0,"do_trunk_bash",victim);
   return 1;
}

varargs int
do_trunk_bash(object victim)
{
   object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
   mixed  *bres;

   if (!objectp(victim) && !sizeof(enemies))
       return 1;
   if (!objectp(victim))
       victim = enemies[random(sizeof(enemies))];
   if (ENV(victim) != ENV(TO)) return 1;
   bres = victim->hit_me(F_PENMOD(BASH_PEN, 90), W_BLUDGEON, TO, -1);
   if (bres[0] < 0) {
       victim->catch_msg("The large oliphaunt swings his long trunk "
           + "dangerously close to you, but you manage to dodge it!\n");
       say("The large oliphaunt swings his long trunk "
	       + "at "+QTNAME(victim)+ ", but "
           + "the "+victim->query_objective()+" dodges successfully.\n",
	       victim);
  }
  else if (bres[0] < 5) {
       victim->catch_msg("The large oliphaunt swings his long snout at "
           + "you, attempting to knock you over. You dodge it, though "
	       + "the trunk knocks against your body, putting you a "
           + "little off balance.\n");
       say("The large oliphaunt swings his long snout at "+QTNAME(victim)+", "
	       + "knocking "+victim->query_objective()+" a little off "
           + "balance.\n",victim);
       victim->add_attack_delay(11+random(20));
   }
   else if (bres[0] < 100) {
       victim->catch_msg("The large oliphaunt swings his grey trunk into "
           + "your body, knocking you off your feet! You feel great "
	       + "pain in your "+bres[1]+" as you awkwardly hit the "
           + "ground.\n");
       say("The large oliphaunt swings his grey trunk squarely "
           + "into "+QTNAME(victim)+", knocking "
	       + victim->query_objective()+" a few meters through the air!\n",
	       victim);
       victim->add_attack_delay(21+random(bres[0]));
  }
  else {
       victim->catch_msg("The great oliphaunt swings his long snout hard "
           + "into your upper body, your neck snapping as the force of "
           + "the blow tosses your head in an impossible angle. "
           + "You never feel your body hitting the ground.\n");
       say("The large oliphaunt swings his grey trunk with incredible "
           + "force, hitting "+QTNAME(victim)+" in the chest, knocking "
           + victim->query_objective()+" along the ground with a "
           + "short snap. "
           + "The limp head twisted in an impossible angle indicates that "
           + QTNAME(victim)+" has died from the blow!\n",victim);
   }
   return 1;
}

int
do_snout_toss()
{
   object  victim = query_attack(),
           room = ENV(TO);
   mixed   oroom,
          *tres;
   int     n;

   if (!objectp(victim))
       return 1;

   if (ENV(victim) != ENV(TO)) return 1;
       victim->catch_msg("Before you can react, the large oliphaunt has "
           + "wrapped his long snout around you firmly! The great beast "
           + "swings you around a few times, then throws you away!\n");
       say("The great oliphaunt deftly wraps his long snout firmly "
           + "around "+QTNAME(victim)+" and "
           + "swings "+victim->query_objective()+ " around "
           + "in the air. Then the great beast tosses "
           + victim->query_objective()+" away as if "
           + "discarding a piece of garbage!\n",victim);
   if (sizeof(room->query_exit()))
   {
   n = random(sizeof(room->query_exit())/3);
   oroom = room->query_exit()[n*3];
   if (objectp(oroom))
       oroom = file_name(oroom);
       say(QCTNAME(victim)+" flies through the "
           + "air "+room->query_exit()[n*3+1]+ "wards!\n",victim);
       tell_room(oroom,"With a frightened yell, "+QNAME(victim)+" comes "
           + "flying through the air, landing with a crash just "
           + "beside you!\n");
       victim->catch_msg("You fly helplessly through the air, landing "
           + "painfully some distance away from the great beast!\n");
   tres = victim->hit_me(F_PENMOD(THROWN_PEN, 90), W_BLUDGEON, TO, -1);
   victim->move_living("M",oroom, 1, 1);
   }
   else {
       say(QCTNAME(victim)+" makes an arc through the air before crashing "
           + "into the ground nearby.\n",victim);
       victim->catch_msg("You fly helplessly through the air, then land "
           + "with a painful crash only some feet away from the huge "
           + "oliphaunt again.\n");
   tres = victim->hit_me(F_PENMOD(DROPPED_PEN, 90), W_BLUDGEON, TO, -1);
   }
   if (tres[0] < 1) {
       victim->catch_msg("Incredibly enough, you stand up again, shaken "
           + "but unhurt by the experience!\n");
       victim->add_attack_delay(6+random(10));
       say(QCTNAME(victim)+" looks shaken but unhurt by the rough "
           + "landing!\n",victim);
   }
   else if (tres[0] < 10) {
       victim->catch_msg("The landing leaves you with a few bruises, but "
           + "not seriously hurt.\n");
       victim->add_attack_delay(6+random(15));
       say(QCTNAME(victim)+" stands up a few bruises richer.\n",victim);
   }
   else if (tres[0] < 100) {
       victim->catch_msg("With a snap and a great pain, the landing has "
           + "given you a fractured bone!\n");
       victim->add_attack_delay(11+random(tres[0]));
       clone_object(FRACTURE_OB)->move(victim, 1);
       log_file("curses", victim->query_name()
           + " broke an arm fighting the "
           + "oliphaunt, " + ctime(time()) + ".\n");
       say(QCTNAME(victim)+" slowly stands up suffering from a fractured "
           + "bone.\n",victim);
   }
   else {
       victim->catch_msg("You hit the ground in an awkward position, and "
           + "with a crunching sound, you feel your life coming to an "
           + "end as your head is cracked against the hard ground.\n");
       say(QCTNAME(victim)+" stays in the position "
           + "that "+victim->pronoun()+" landed, and you realize with "
           + "horror that "+victim->possessive()+" head has cracked open "
           + "on the hard ground.\n",victim);
   }
   return 1;
}
      
int
special_attack(object new_victim)
{

  if (random(100) > 15) {
      return 0;
  }
  switch(random(10))
     {
     case 0..2:
         do_trunk_bash();
     break;
     case 3..5:
         do_foot_stomp();
     break;
     case 6..9:
         do_snout_toss();
     break;
     default:
         do_snout_toss();
     break;
     }
  return 1;
}

/* Solamnian prestige. */

int query_knight_prestige() {return 150;}
