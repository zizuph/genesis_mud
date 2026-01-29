// file name:    Grub
// creator(s):   Cirion, April 1996
// last update:  Denis, Aug'96: Added check in come_back on the fact if the
//				corpse still exists.
//				Lowered the number of lives.
//               Cirion, Sept 97: Made it so it does not auto-attack
//                              in ROOM_I_NO_ATTACK rooms
//
// purpose:      Newbie Monster
// note:         Icky bug for the newbie area. It has 9 lives :)
//
//		 Nine?? Let it be three. Or we are getting the reports
//		 that there is a bug in it - it never dies.
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "../outpath.h"

#define A_TAIL       0
#define A_HEADS      1

#define H_HEADS      0
#define H_BODY       1
#define H_TAIL       2

int      lives;
object   corpse;

void aggro();

void create_creature()
{
    string *adjs = ({ "white", "sticky", "long", "grotesque",
                      "disgusting", "foul", "repugnant", "nasty", "icky" });

    set_name("grub");
    add_name("larva");
    set_race_name("grub");

    set_adj( adjs[random(sizeof(adjs))] );
    set_gender(G_NEUTER);

    set_long("It is a large, maggot-white creature, blind "
            +"and deaf, but very sensitive to vibrations "
            +"around it. Its skin is sticky and covered in "
            +"a translucent white film.\n");

    set_stats(({ 12, 10, 15, 1, 1, 10 }));

    set_skill(SS_UNARM_COMBAT,  10);
    set_skill(SS_DEFENCE,        5);
    set_skill(SS_AWARENESS,     50);

    set_alignment(0);

    set_attack_unarmed(A_TAIL, 2, 2, W_BLUDGEON, 60, "slimy tail");
    set_attack_unarmed(A_HEADS, 2, 2, W_BLUDGEON, 40, "head");

    set_hitloc_unarmed(H_HEADS,  ({ 4, 4, 2 }), 30, "head");
    set_hitloc_unarmed(H_BODY,   ({ 2, 2, 8 }), 40, "body");
    set_hitloc_unarmed(H_TAIL,   ({ 4, 4, 4 }), 30, "tail");

    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 25);
    add_prop(CONT_I_HEIGHT, 3);

    add_prop(LIVE_I_SEE_INVIS,  -1);  // They are blind
    add_prop(LIVE_I_NEVERKNOWN,  1);
    add_prop(NPC_I_NO_LOOKS,     1);
    add_prop(NPC_I_NO_RUN_AWAY,  1);

    set_act_time(10);
     add_act("emote curls itself into a ball.");
     add_act("emote makes a repulsive squishing noise.");
     add_act("lick grub");
     add_act("emote raises itself up, swaying back and forth.");

}

void init_living()
{
  ::init_living();
  set_alarm(itof(random(15) + 5), 0.0, aggro);
}

/* All this because I want to corpse pointer to be global, not local. */
object make_corpse()
{
   corpse = clone_object("/std/corpse");
    corpse->set_name(query_name());
    corpse->change_prop(CONT_I_WEIGHT, query_prop(CONT_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME, query_prop(CONT_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE, query_race_name());
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT,
	query_prop(CONT_I_MAX_WEIGHT));
    corpse->change_prop(CONT_I_MAX_VOLUME,
	query_prop(CONT_I_MAX_VOLUME));
    corpse->set_leftover_list(query_leftover());
    corpse->add_prop(OBJ_M_NO_GET, "It is too slimy to pick up.\n");

   return corpse;
}

void come_back()
{
  // What if there is no more corpse of myself already???
  // Or if someone has taken the corpse?
  // -=Denis
  if(!objectp(corpse) || !ENV(corpse)->query_prop(ROOM_I_IS))
  {
    remove_object();
    return;
  }
  else
  {
    move(ENV(corpse));

    tell_room(ENV(TO), "The "+corpse->short()+" wriggles and squirms, and starts "
       +"moving again!\n");
    corpse->remove_object();
    set_ghost(0); // Make him alive again
    set_alarm(itof(random(5) + 2), 0.0, aggro);
  }
}  

int second_life()
{
  lives++;
  stop_fight(query_enemy(-1)); // Stop all fighting.
  move(VOID);

  // Nine lives???
  // Three is more than enuff.
  if(lives > 1 + random(2))
  {
    remove_object();
    return 0; // No more lives for me...
  }

  set_alarm(itof(random(100) + 5), 0.0, come_back);
  return 1;
}

void aggro()
{
  object   *people = filter(all_inventory(ENV(TO)), interactive);
  object    who;
  
  if(!sizeof(people) || query_attack() || query_no_show())
    return;

  if(ENV(TO)->query_prop(ROOM_M_NO_ATTACK))
    return;

  who = people[random(sizeof(people))];

  who->catch_msg(QCTNAME(TO)+" starts to gnaw at your leg!\n");
  say(QCTNAME(TO)+" starts to gnaw at "+QTNAME(who)+"'s leg.\n", who);
  attack_object(who);
}

/* Let's not have it panicing ... */
int query_panic()
{
   return 0;
}
