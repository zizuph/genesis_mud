/*
 * Navarre, September 19th 2006.
 *
 * The object behind the Scop Confuse spell.
 *
 */
#pragma strict_types
inherit "/d/Genesis/newmagic/spell_effect_object";
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

#define DURATION 180
#define I_AM_MOVING "_syskotisi_confuse_move"
#define ONE_OF(x)     ((x)[random(sizeof(x))])

int confuse_alarm = 0;
int move_alarm_count = 0;
int move_alarm = 0;
void confuse(object player);
string* puzzled = ({"You don't know what just happened, you feel confused.\n",
                    "It seems as if the world is spinning.\n",
                    "You feel lightheaded.\n"});
                     
void
create_object()
{
    ::create_object();
    set_name("_scop_confuse_obj");
    set_no_show();

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "The object behind the " +
                            "Scop confuse spell.\n");
}


varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_msg("As if a blur lifts from your mind, you manage "+
                            "to regain control of your thoughts.\n");
    remove_alarm(confuse_alarm);
    remove_alarm(move_alarm);
    remove_spell_effect_object();
    spell_target->remove_prop(I_AM_MOVING);
    return 1;
}

public int
start()
{
   int bonus = (spell_caster->query_stat(SS_WIS) +
                spell_caster->query_stat(SS_OCCUP))/2;
   confuse_alarm = set_alarm(3.0, 20.0, &confuse(spell_target));
   set_alarm(itof(MIN(300, DURATION+random(bonus))),
                  0.0, &dispel_spell_effect(this_object()));

   return 1;
}


void 
confuse_attack(object player, object* enemies, object* team_members)
{
 
    object target;
 
    if(random(100)>50)
    {
       if(!enemies || sizeof(enemies) == 0)
       {
            return;
       }
       target = ONE_OF(enemies);

       // To avoid attacking someone that is not in the same room
       if(!present(target, environment(player)) ||
           target->query_attack() == player ||
          !CAN_SEE(player, target) || !CAN_SEE_IN_ROOM(player))
       {
           return;
       }


       target->catch_msg(QCTNAME(player)+" shakes "+HIS(player)+
                         " head frantically in confusion and finds " +
                         "a new enemy. YOU!\n");
       target->catch_msg(QCTNAME(player)+" attacks you!\n");

       player->catch_msg("You shake your head frantically in confusion " +
                         "and finds "+QTNAME(target)+" to be your new enemy.\n");
       player->catch_msg("You attack "+QTNAME(target)+".\n");

       tell_room(QCTNAME(player)+" shakes "+HIS(player)+" head frantically in "+
                 "confusion and finds "+ QTNAME(target)+" to be "+HIS(player)+
                 " new enemy.\n", ({target, player}));
       tell_room(QCTNAME(player)+" attacks "+QTNAME(target)+".\n", ({target, player}));

       player->attack_object(target);
       return;
    }

    if(!team_members || sizeof(team_members) == 0)
    {
        return;
    }
    target = ONE_OF(team_members);

    // To avoid attacking someone that is not in the same room
    if(!present(target, environment(player)) || target->query_attack() == player)
    {
         return;
    }
    target->catch_msg(QCTNAME(player)+" shakes "+HIS(player)+" head frantically "+
                      "in confusion and finds a new enemy. YOU!\n");
    target->catch_msg(QCTNAME(player)+" attacks you!\n");

    player->catch_msg("You shake your head frantically in confusion and finds "+
                       QTNAME(target)+" to be your new enemy.\n");
    player->catch_msg("You attack "+QTNAME(target)+".\n");

    tell_room(QCTNAME(player)+" shakes "+HIS(player)+" head frantically in "+
              "confusion and finds "+ QTNAME(target)+" to be "+HIS(player)+
              " new enemy.\n", ({target, player}));
    tell_room(QCTNAME(player)+" attacks "+QTNAME(target)+".\n", ({target, player}));

    player->attack_object(target);

    return;
}

int force_move(object player)
{
  string* all_exits;

  all_exits = environment(player)->query_exit_cmds();

  switch(move_alarm_count)
  {
    case 0:
            player->catch_tell("You just remembered that you need to be "+
                               "somewhere.\n");
            tell_room(environment(player), QCTNAME(player)+" looks around "+
                      "left and right.\n", player);  
	    player->add_prop(I_AM_MOVING, 1);
            break;
    case 1:
            player->catch_tell("Erh.. Where were you going again?\n");  
            tell_room(environment(player), QCTNAME(player)+" looks puzzled "+
                      "as if "+ HE(player)+" doesn't know where "+HE(player)+
                      " is going or where "+HE(player)+" has been.\n", player);  
            break;
    case 2:
            player->catch_tell("Ahh yes, now you remember.\n");  
            break;
    case 3:
            player->catch_tell("No. That wasn't it.\n");  
            break;
    case 4:
            player->catch_tell("Maybe it's this way.\n");  
            break;
    case 5:
            player->catch_tell("This way definitely can't be wrong.\n");  
            break;
    default: 
            player->catch_tell("Weren't you just here?\n");  
            move_alarm_count=-1;
            break;

  }
  // Added check to avoid runtime (navarre july 22nd 2007).
  if(sizeof(all_exits) > 0)
  {
      player->command(ONE_OF(all_exits));
  }
  move_alarm_count++;
  if(move_alarm_count==0)
  {
    remove_alarm(move_alarm);
    move_alarm = 0;
    player->remove_prop(I_AM_MOVING);
  }
}

void confuse_move(object player)
{
  if(player->query_prop(NPC_I_NO_RUN_AWAY) || player->query_prop(I_AM_MOVING))
  {
    return;
  }
  move_alarm = set_alarm(2.0, 3.5, &force_move(player));
}

void look_puzzled(object player)
{
  player->catch_tell(ONE_OF(puzzled));
  tell_room(environment(player), QCTNAME(player)+" looks utterly " +
            "confused.\n", player);
}


void
confuse(object player)
{
  object* enemies = player->query_enemy(-1);
  object* team_members = player->query_team_others();
  object target;

  // We don't want to interrupt our nice confuse move
  if(player->query_prop(I_AM_MOVING))
  {
      return;
  }

  int resolver = random(10);
  switch(resolver)
  {
    case 0..4:
        confuse_attack(player, enemies, team_members); 
        break;
    case 5..7:
        confuse_move(player);
        break;
    case 8..9:
        look_puzzled(player); 
        break;
    default: return;
  }
}
