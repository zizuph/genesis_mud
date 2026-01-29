inherit "/std/monster";

#include <stdproperties.h>
#include "/d/Emerald/defs.h"
#include <macros.h>
#include "default.h"

void give_torque(object who);

void equip_me()
{
}

void create_monster()
{
  set_name("wizard");
  add_name("wiz");
  add_name("restoration_wiz");
  set_adj("bored");
  set_race_name("elf");

  set_stats(({ 40, 150, 90, 200, 200, 100 }));
  refresh_mobile();

  set_long("Resplendent in flowing robes adorned with magical symbols,\n" +
      "this elf is obviously a magic-user of some sort.  His\n" +
      "capacity here is to restore lost objects to adventurers.\n" +
      "From the look on his face, it doesn't seem that he is\n" +
      "very excited by his vocation.\n" +
      "If you are missing something precious, perhaps you should\n" +
      "ask him to restore it....\n");

  add_ask(({ "restore torque", "restore my torque", "to restore torque",
      "to restore my torque", "restore crystal torque", 
      "restore my crystal torque", "to restore crystal torque", 
      "to restore my crystal torque" }), "@@restore_torque@@", 1);

  set_default_answer("@@restore_nothing@@");

  set_dont_answer_unseen(1);

  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(MAGIC_I_RES_MAGIC, 30);
  
  set_skill(SS_UNARM_COMBAT, 50);
  set_skill(SS_DEFENCE, 70);
  
  equip_me();
}

string restore_torque()
{
  if (this_player()->test_bit("Emerald", 2, 1) &&
      this_player()->test_bit("Emerald", 2, 2))
  {
    if (present("phase_torque", this_player()))
    {
      return "say You have one already!  Now stop bothering me.";
    }

    set_alarm(1.0, 0.0, &give_torque(this_player()));
    return "sigh";
  }

  return "say You'll have to earn it first.\n";
}

void give_torque(object who)
{
  object torque;

  if (!present(who, environment(this_object())))
  {
    return;
  }

  command("emote wiggles his index finger.\n");

  if (torque = clone_object(CTOWER_DIR + "obj/torque"))
  {
    who->catch_msg("A crystal torque materializes among your " +
        "possessions.\n");
    torque->move(who, 1);
  }
  else
  {
    who->catch_msg("A crystal torque begins to materialize among your " +
        "possessions, buts fades back into nothingness....\n");
    command("blush");
    command("say perhaps you should mail Shiva about this incident.");
  }
}
 
string restore_nothing()
{
  string q = query_question();

  if (strlen(q) && parse_command(q, ({ }), "[to] 'restore' [my] / " +
      "[the] %s"))
  {
    command("say I don't know anything about that.");
    command("emote mumbles something about other people's problems.");
    return "";
  }

  command("emote ignores you.");
  return "";
}

void answer_question(string msg, int cmd)
{
  if (!cmd)
  {
    msg = check_call(msg, this_player());
  }

  ::answer_question(msg, cmd);
}

void move_random(object ob)
{
  string *rooms, this_room;
  object room_ob;

  setuid();
  seteuid(getuid());
  
  rooms = get_dir(THIS_DIR);
 
  while (sizeof(rooms))
  {
    this_room = rooms[random(sizeof(rooms))];

    call_other(THIS_DIR + this_room, "??");
   
    if (!(room_ob = find_object(THIS_DIR + this_room)) ||
        !room_ob->query_prop(ROOM_I_IS) ||
        room_ob->query_prop(ROOM_M_NO_MAGIC) ||
        room_ob->query_prop(ROOM_I_NO_TELEPORT))
    {
      rooms -= ({ this_room });
      continue;
    }

    ob->add_prop("_live_i_no_encounter_telberin_wiz", 1);
  
    ob->move_living("X", room_ob, 1);
    return;
  }
}

void goodbye(object ob)
{
  if (!present(ob, environment(this_object())))
  {
    return;
  }

  ob->catch_msg("The wizard speaks a few strange words and quickly " +
      "extends his hand toward you!\n");
  tell_room(environment(this_object()), "The wizard speaks a few " +
      "strange words and quickly extends his hand toward " + 
      QTNAME(ob) + "!\n", ({ this_object(), ob }));

  move_random(ob);
}
 
void attacked_by(object ob)
{
  ::attacked_by(ob);

  set_alarm(1.0, 0.0, &goodbye(ob));
}

void goodbye2(object ob)
{
  if (!present(ob, environment(this_object())))
  {
    return;
  }

  if (CAN_SEE(ob, this_object()) && CAN_SEE_IN_ROOM(ob))
  {
    ob->catch_msg("As soon as you set eyes upon the wizard, you feel " +
        "yourself magically transferred.\n");
  }
  else
  {
    ob->catch_msg("You feel yourself magically transferred.\n");
  }

  move_random(ob);
}

void init_living()
{
  ::init_living();

  if (this_player()->query_prop("_live_i_no_encounter_telberin_wiz"))
  {
    if (member_array(this_object(), this_player()->query_enemy(-1)) >= 0 ||
        member_array(this_player(), query_enemy(-1)) >= 0)
    {
      set_alarm(0.5, 0.0, &goodbye2(this_player()));
      return;
    }
   
    this_player()->remove_prop("_live_i_no_encounter_telberin_wiz");
  }
}


