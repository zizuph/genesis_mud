/*
 * Nov 7, 2017 - Finwe  Removed 'Promise to join' functionality, to allow
 *                      players to come and go as needed to check out the guild
 */
#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../guild.h"

inherit SHIRE_ROOM;

//#define PROMISED_TO_JOIN "_promised_to_join_army_"

/*
 * prototypes
 */
void reset_room();

/*
 * Global variables
 */
object *guards;

void
create_room()
{
  set_short("By the gates");
  set_long("You are standing on a small rocky opening. To the north is a "+
           "smooth mountain wall with a massive wooden gates. The opening "+
           "has been cleaned out of every tree, bush and even out of grass "+
           "so only bare rock remains leaving no place where even a mouse "+
           "could hide.\n");

// add_prop(ROOM_M_NO_HIDE, "There is no place where even a mouse could hide.\n");
  add_prop(ROOM_I_HIDE, -1);

  add_item(({"gates","gate"}), "These massive wooden gates lead "+
                "into the mountain.\n");

  add_exit(AA_DIR+"rooms/c3", "north", "@@block@@");
  add_exit(AA_DIR+"rooms/g3", "southwest");

  guards = allocate(2);
  // commented out at request of Arch of PLayers ALIA
   // clone_object("/d/Emerald/fysix/open/raffe_statue")->move(TO, 1);
  reset_room();
}

void
reset_room()
{
  int i;

  for(i=0; i<2; i++)
  {
    if(!guards[i])
    {
      guards[i] = clone_object(AA_DIR+"npc/shield_guard");
      guards[i]->set_guard_base_stat(95+random(20));
      guards[i]->arm_me();
      guards[i]->move(TO, 1);
      tell_room(TO, QCNAME(guards[i])+" arrives from the gates.\n");
      guards[i]->command("say O.K. now I am on duty!");
    }
    else if(!present(guards[i]))
    {
          guards[i]->command("oops");
      guards[i]->command("say I should be guarding the gates!");
      tell_room(ENV(guards[i]), QCTNAME(guards[i])+" runs away.\n");
      guards[i]->move(TO, 1);
      tell_room(TO, QCNAME(guards[i])+" arrives.\n");
      guards[i]->command("say Back on duty!");
      guards[i]->command("grin");
    }
  }
}

int
block()
{
    object guard;

    if(guards[0] && present(guards[0])) guard = guards[0];
    if(guards[1] && present(guards[1])) guard = guards[1];
    if(!guard) return 0;

    if(!TP->check_seen(guards[0]) && !TP->check_seen(guards[1])) return 0;

    if(sizeof(({guards[0],guards[1]}) & TP->query_enemy(-1)))
    {
        guard->command("say Coward! Now "+HE(TP)+" wants to run in!");
        guard->command("grin at "+TP->query_real_name());
        return 1;
    }

    if((TP->query_guild_name_occ() == "Gondorian Rangers Guild")
    || (TP->query_guild_name_occ() == "Solamnian Knights")
    || (TP->query_guild_name_occ() == "Calian warrior's guild"))
    //|| (TP->query_guild_name_occ() == "Vampires of Emerald"))
    {
        guard->command("shout Alarm!!!  Enemies wants to sneak in!");
        guard->command("kill "+TP->query_real_name());
        return 1;
    }

    if(TP->query_guild_member(GUILD_NAME))
    {
        if(!TP->query_incognito())
        {
            guard->command("say Welcome back home!");
            guard->command("bow to "+TP->query_real_name());
        }
        return 0;
    }
/*
  if(TP->query_race_name() == "elf")
  {
    guard->command("say An elf to our quarters? No way!!!");
    guard->command("kill "+TP->query_real_name());
    return 1;
  }
*/

/*
  if(TP->query_prop(PROMISED_TO_JOIN))
  {
    guard->command("say I hope you will join as you promised!");
    guard->command("grin at "+TP->query_real_name());
    return 0;
  }*/

/*
  guard->command("say I will let you in...");
  guard->command("say ...but only when you promise to join our army!");
  guard->command("say Do you promise?");
  guard->command("peer at "+TP->query_real_name());
*/
    return 0;
}

void
init()
{
  ::init();
//    add_action("promise","promise");
}
/*
int
promise(string str)
{
  object guard;
  string race = TP->query_race_name();

  NF("Promise what? To join army?\n");
  if((str != "to join army") && (str != "join army")) return 0;

  NF("There is no guard to promise it to...\n");
  if(guards[0] && present(guards[0])) guard = guards[0];
  if(guards[1] && present(guards[1])) guard = guards[1];
  if(!guard) return 0;

  write("You promised to join army.\n");
  say(QCTNAME(TP)+" promised to join army.\n");

  if(sizeof(({guards[0],guards[1]}) & TP->query_enemy(-1)))
  {
    guard->command("say Coward! We will kill you instead!");
    guard->command("grin at "+TP->query_real_name());
    return 1;
  }
  if(race == "elf")
  {
    guard->command("shout Alarm!!!  This elf wants to join us!");
    guard->command("shout Kill the spy!!!");
    guard->command("kill "+TP->query_real_name());
    return 1;
  }
  if((TP->query_guild_style_occ() == "ranger") &&
     ((random(100) < TP->query_stat(SS_OCCUP)) ||
      present("ranger_guild_object", TP)->query_worn()))
  {
    guard->command("shout Alarm!!!  Ranger wants to join us!");
    guard->command("shout Kill the spy!!!");
    guard->command("kill "+TP->query_real_name());
    return 1;
  }
  if(member_array(race, ({ "hobbit"})) != -1)
  {
    guard->command("shout Hey!!! This "+race+" wants to join us!!!!");
    guard->command("laugh at "+TP->query_real_name());
    return 1;
  }
  guard->command("smile at "+TP->query_real_name());
  TP->add_prop(PROMISED_TO_JOIN, 1);
  return 1;
}
*/
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

//  if(!living(ob) || !ob->query_prop(PROMISED_TO_JOIN) ||
//     ob->query_guild_member(GUILD_NAME)) return;
//  set_alarm(0.5,0.0,"kill_traitor",ob);
}
/*
void
kill_traitor(object ob)
{
  object guard;
  if(guards[0] && present(guards[0])) guard = guards[0];
  if(guards[1] && present(guards[1])) guard = guards[1];
  if(!guard) return;
  guard->command("shout Traitor! "+CAP(HE(ob))+" did not join as promised!");
  guard->command("kill "+ob->query_real_name());
}
*/