inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_room()
{
  set_short("You cannot see anything since you are blindfolded.\n");
  set_long("You cannot see anything since you are blindfolded.\n");
  add_prop(ROOM_M_NO_MAGIC,"That is impossible since you are bound and blindfolded.\n");
  add_prop(ROOM_M_NO_MAGIC_ATTACK,"That is impossible since you are bound and blindfolded.\n");
}

int
catch_all()
{
  string action;

  action = query_verb();

  switch(action)
  {
  case "quit":
    write("You cannot reach the keyboard to quit, since your hands are tied.\n");
    return 1;
  case "look":
  case "i":
  case "inventory":
  case "read":
  case "eyebrow":
  case "peer":
    write("That is impossible since you are blindfolded.\n");
    return 1;
  case "fondle":
  case "greet":
  case "hug":
  case "poke":
  case "finger":
  case "clap":
    write("That is impossible since your hands are tied.\n");
    return 1;
  case "whistle":
  case "sing":
  case "shout":
  case "scream":
  case "whine":
  case "complain":
  case "cry":
  case "moan":
  case "love":
  case "yodel":
    if(TP->query_prop("_is_gagged"))
    {
      write("You cannot do that, you are gagged!\n");
    }
    else if(TP->query_prop("_gag_warned"))
    {
      write("An angry voice whispers into your ear: Well, you have been warned!\n");
      write("A piece of cloth is pressed into your mouth - you are gagged!\n");
      TP->add_prop("_is_gagged",1);
    }
    else
    {
      write("An angry voice whispers into your ear: Be silent, or we will gag you!\n");
      TP->add_prop("_gag_warned",1);
    }
    return 1;
  case "n":
  case "north":
  case "s":
  case "south":
  case "w":
  case "west":
  case "e":
  case "east":
  case "ne":
  case "northeast":
  case "se":
  case "southeast":
  case "sw":
  case "southwest":
  case "nw":
  case "northwest":
  case "u":
  case "up":
  case "d":
  case "down":
    write("Since you are blindfolded you cannot see where you want to go.\n");
    write("When you make the first step, you painfully run into some obstacle.\n");
    TP->heal_hp(-100);
    if(TP->query_hp() == 0) TP->do_die(find_living("faramir"));
    write("You are hurt.\n");
    return 1;
  case "kill":
  case "knee":
  case "kick":
    write("Don't be stupid. You cannot see anything, you're hands are tied.\n");
    write("One wrong move, and you're dead meat.\n");
    return 1;
  case "glance":
    return 1;
  case "arrive":
  case "depart":
  case "help":
  case "bug":
  case "typo":
  case "sysbug":
  case "idea":
  case "praise":
  case "who":
  case "date":
  case "present":
  case "introduce":
  case "say":
  case "rsay":
  case "whisper":
  case "commune":
  case "listen":
  case "sigh":
  case "think":
  case "ponder":
    case "v":
  case "vitals":
    case "health":
    case "h":
  case "stats":
  case "hiccup":
  case "shiver":
  case "brighten":
  case "smirk":
  case "gasp":
  case "stomp":
  case "grin":
  case "chuckle":
    return 0;
  }
  write("That is impossible since you are bound and blindfolded.\n");
  write("If you believe that your action should be possible nevertheless, then make a bug report.\n");
  if(TP->query_wiz_level())
  {
    write("On the other hand, you are a wizard, so perhaps its possible anyway.\n");
    return 0;
  }
  return 1;
}

void
seq1(object player)
{
  if(!present(player,TO) || !living(player)) return;
  player->catch_msg("You feel a rope being tied around your body.\n");
  player->catch_msg("Suddenly, you lose the hold under your feet.\n");
  player->catch_msg("You are let down from the tree hanging at the end of the rope.\n");
  player->catch_msg("After a few terrible moments you land at the bottom of the tree.\n");
}

void
seq2(object player)
{
  if(!present(player,TO) || !living(player)) return;
  player->catch_msg("You hear someone climbing down the tree.\n");
  player->catch_msg("Someone removes the rope that was tied around your body.\n");
  player->catch_msg("Leading you by your hands, someone gently steers you through some bushes.\n");
  player->catch_msg("Someone whispers: We will lead you to the Anduin now. \n");
  player->catch_msg("Someone whispers: Don't try anything foolish!\n");
  player->catch_msg("You feel someone pulling at the rope that binds you hands.\n");
  player->catch_msg("You follow, carefully setting each step to prevent stumbling.\n");
}

void
seq3(object player)
{
  if(!present(player,TO) || !living(player)) return;
  player->catch_msg("You are still being led by a constant pull on the rope that binds your hands.\n");
  player->catch_msg("You wonder how long the march will continue.\n");
  player->catch_msg("Someone whispers: Careful now, we will cross a small stream.\n");
  player->catch_msg("You feel around with your feet, and manage to cross the stream with dry feet.\n");
  player->catch_msg("On the other side of the stream, you notice the land rising.\n");
}

void
seq4(object player)
{
  if(!present(player,TO) || !living(player)) return;
  player->catch_msg("The march now goes over soft forest soil.\n");
  player->catch_msg("You are still being led by a constant pull on the rope that binds your hands.\n");
  player->catch_msg("You wonder how long the march will continue.\n");
  player->catch_msg("Suddenly you stumble over something hard.\n");
  player->catch_msg("A strong hand grasps your arm and prevents you from falling down.\n");
}

void
seq5(object player)
{
  if(!present(player,TO) || !living(player)) return;
  player->catch_msg("Someone whispers: We are there!\n");
  player->catch_msg("Someone whispers: You will have to cross the Anduin on your own.\n");
  player->catch_msg("Someone whispers: Don't return to Ithilien! It would be your death!\n");
  player->catch_msg("You can feel your hands being untied.\n");
  player->catch_msg("Then your blindfold is removed.\n");
  player->catch_msg("You suddenly get a push from behind and stumble forward through dense bushes.\n");
  player->catch_msg("You can hear someone disappearing into the bushes behind you.\n");
  player->add_prop("_no_pass_to_ithilien",1);
  player->remove_prop("_arrested");
  if(player->query_prop("_is_gagged"))
    player->remove_prop("_is_gagged");
  if(player->query_prop("_gag_warned"))
    player->remove_prop("_gag_warned");
  player->move_living("M",ITH_DIR + "road/rr6",1);
  tell_room(ENV(player), QCTNAME(player) + " arrives stumbling out of a bushy thicket.\n", player);
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(!ob || !interactive(ob)) return;
  if(!from) return;

  set_alarm(5.0, 0.0, &seq1(ob));
  set_alarm(20.0, 0.0, &seq2(ob));
  set_alarm(50.0, 0.0, &seq3(ob));
  set_alarm(90.0, 0.0, &seq4(ob));
  set_alarm(120.0, 0.0, &seq5(ob));
  return;
}

void
init()
{
  ::init();
  add_action("catch_all", "", 1);
}
