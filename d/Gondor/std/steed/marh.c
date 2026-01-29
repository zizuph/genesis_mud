/*
   meahr.c

   Standard marh.

   The mearas are a wild race of horses. The father of all mearas is named
   Felarof, a beautiful and powerful horse. In the early days Leod tried
   to tame the horse, but Felarof would not have any rider and threw him
   off when Leod tried to mount him. Unfortunately the king fell with his
   head on a rock and died.
   After his death Leod's son Eorl hunted for the beast for years looking for
   revenge, but in vain. One day they encountered each other again though.
   But when he saw the horse he could not kill the horse anymore. In stead
   he beckoned the horse to come closer and said that he owed him greatly
   for the death of his father. From then on the horse had to serve him for his
   whole life. The descendants of Felarof would have none other than kings
   as their riders.
   The leader of all mearas is Shadowfax, an exceptional swift horse,
   ridden by Gandalf the Grey. Also he is the only marh to understand
   the language of humans.

   Fysix@Genesis, August 1997

   Cotillion - 2007-12-28
   - Fixed set_cact_time to correctly use ints.
 */
#pragma save_binary
#pragma strict_types

#include "/d/Gondor/defs.h"

inherit STEED_OBJECT;
inherit "/std/act/action.c";

#include <macros.h>
#include <ss_types.h>

public void add_actions();

// meahr creation function
public void
create_marh()
{
}

public nomask void
create_steed()
{
   set_race_name("marh");
   set_pname("mearas");
   add_name(({"animal", "horse"}));
   add_pname(({"animals", "horses"}));
   set_stats(({120, 120, 120, 100, 100, 120}));

   create_marh();
   add_actions();
}

// Add some actions to the meahr
public void
add_actions()
{
   set_act_time(10);
   add_act("emote snorts violently while shaking " + query_possessive() +
      " head.");
   add_act("emote looks defiantly at you from a distance.");
   add_act("emote watches " + query_possessive() + " environment " +
      "vigilantly.");
   add_act("emote restlessly moves about tossing " + query_possessive() +
      " manes backwards.");
   add_act("emote raises " + query_possessive() + " head silently " +
      "and listens attentively.");
   add_act("emote flaps " + query_possessive() + " tail loosely on " +
      query_possessive() + " flanks.");
   add_act("emote suddenly rears on " + query_possessive() +
      " hindlegs displaying a great power.");

   set_cact_time(15);
   add_cact("emote comes charging at you with thundering hoofs.");
   add_cact("emote looks at you in utter contempt with flaming eyes.");
}

// Player cannot mount for now,
// do a little bit of damage when player tries to mount.
int
can_mount(object player)
{
int    damage, total_hp;
string msg;

   tell_room(environment(player), QCTNAME(player) + " tries to mount the " +
      short() + " but the " + short() + " stalls violently and " +
      player->query_pronoun() + " is thrown ruthlessly on the ground.\n",
      player);
   notify_fail("");
      
   // Do a bit of damage
   damage =  50 + random(50);
   total_hp = player->query_hp();
   if (total_hp <= 0)
      total_hp = 1;
   switch ((damage * 100) / total_hp)
   {
     case 0..20 :
      msg = "You are slightly hurt by the fall.\n";
      break;
     case 21..40 :
      msg = "You are hurt by the fall.\n";
      break;
     case 41..60 :
      msg = "You are rather hurt by the fall.\n";
      break;
     case 61..80 :
      msg = "You are badly injured by the fall.\n";
      break;
     case 81..100 :
      msg = "You are terribly injured by the fall.\n";
      break;
   }
   player->catch_tell("You try to mount the " + short(player) +
      " but the " + short(player) + " stalls violently and you are " +
      "thrown ruthlessly on the ground.\n" + msg);
   player->heal_hp(-damage);
   if (!player->query_hp())
      player->do_die(this_object());
   return 0;
}

// Add a special attack here
public int
special_attack(object victim)
{
   // do a special in 10% of the cases
   if (random(10) > 2)
      return 0;

   victim->catch_tell("The " + short(victim) + " charges and hits " +
      "you with great force.\n");
   tell_room(environment(), "The " + short(victim) + " charges and " +
      "hits " + QCTNAME(victim) + " with great force.\n", victim);
      
   victim->heal_hp(-victim->query_stat(SS_STR));
   if (!victim->query_hp())
      victim->do_die(this_object());
   return 1;
}
