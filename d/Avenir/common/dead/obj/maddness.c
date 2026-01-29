// Ilyian (Oct 20, 1995)
// last update:
// purpose: Maddness as a punishment for failing the Cahor quest
// note:
// bug(s):
// to-do:


#include <poison_types.h>
#include <macros.h>
#include "/d/Avenir/common/common.h"

#define TR(x) tell_room(environment(poisonee), (x), poisonee);

inherit "/std/poison_effect";

void
create_poison_effect()
{
  remove_name("poison");
  set_name ("maddness");
  set_poison_type("mental");
  set_silent(2);
  set_interval(2);
//  set_interval(30);
  set_time(1800);
  add_prop(OBJ_M_NO_DROP,"Your maddness is yours alone.");
  set_strength(80);
  set_damage(({POISON_MANA, 100,
               POISON_USER_DEF,1}));
}


void
special_damage (int damage)
{
 int msg_num = random( 7 );
 string friend;
 string *friends;
 string *friendsay; 
 string *exits;

 friends = m_indexes(poisonee->query_remembered());
 friend = friends[random(sizeof(friends))];

 friendsay = ({"I've always hated you! Always!",
               "My God! What have you done?!?"});
 exits = ENV(poisonee)->query_exit_cmds();
 
 switch (msg_num)
  {
   case 0:
     poisonee->catch_msg ("You suddenly feel very dizzy.\n");
     TR(QCTNAME(poisonee) + " holds " + POSSESS(poisonee) +
          " hands to "+ POSSESS(poisonee) + " head.\n");
     break;
   case 1:
     poisonee->catch_msg ("Something suddenly seems "
         +"very funny.\n");
     poisonee->command("$laugh hyst");
     poisonee->command("$laugh uncon");
     break;
   case 2:
     poisonee->catch_msg ("You suddenly realize that " 
         +"they are all out to get you!\n");
     TR(QCTNAME(poisonee) + " looks around in a panic.\n");
     poisonee->run_away();    // Run 4 rooms away.
     poisonee->run_away();
     poisonee->run_away();
     poisonee->run_away();
     break;
   case 3:
     poisonee->catch_msg ("None of it seems worthwhile "
         +"anymore.\n");
     poisonee->command("$shout I give up!");
     poisonee->command("$drop weapons");
     poisonee->command("$drop armours");
     break;
   case 4:
     if(!sizeof(friends))
      {
       poisonee->catch_msg("An image of an old friend "
         +"appears before you.\nHe says: You were "
         +"wrong about me! You always were!");
       poisonee->command("$sob hyst");
       break;
      }
     else
      {
       poisonee->catch_msg(capitalize(friend)+" arrives.\n"
          +capitalize(friend)+" glares stonily at you.\n"
          +capitalize(friend)+" says: "
          +friendsay[random(sizeof(friendsay))]+"\n"
          +capitalize(friend)+" leaves "
          +ENV(poisonee)->query_exit_cmds()
              [random(sizeof(ENV(poisonee)->query_exit_cmds()))]
          +".\n");
       poisonee->command("$shout No! Please don't leave me!");
       poisonee->command("$sob uncon");
       break;
       }     

  default:
    poisonee->catch_msg ("Your head hurts.\n");
    poisonee->command("$moan soft");
    break;
        }
}

void start_poison()
{
  poisonee->catch_msg("Your mind feels strange.\n");
  ::start_poison();
}

void timeout()
{
  poisonee->catch_msg("Your mind feels healthy again.\n");
  ::timeout();
}
