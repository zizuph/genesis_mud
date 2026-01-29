/* start.c created by Shiva@Genesis.
 * This is the vampire guild's start room
 */

#pragma save_binary
#include "../guild.h"

inherit "/std/room";
#ifdef TEMP_TRAINER
inherit "/d/Emerald/lib/train";
//inherit "/lib/skill_raise";
#endif


#include "lockout.c"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

#define DEBUG_WHO this_player()
#define DEBUG_ON
#include "/d/Emerald/sys/debug.h"

#ifdef TEMP_TRAINER
#include <ss_types.h>
#include "/d/Emerald/sys/skills.h"

void set_up_skills()
{
  create_skill_raise();

  sk_add_train(SS_TRADING, "make deals", "trading", 0, 70);
  sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 90);
  sk_add_train(SS_SNEAK, "sneak", "sneak", 0, 80);
  sk_add_train(SS_HIDE, "hide", "hide", 0, 80);
  sk_add_train(SS_LANGUAGE, "speak foreign and archaic languages",
      "language", 0, 75);
  sk_add_train(SS_CLIMB, "climb", "climb", 0, 40);
  sk_add_train(SS_LOC_SENSE, "avoid getting lost", "location sense", 0, 60);
  sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 90);
  sk_add_train(SS_UNARM_COMBAT, "fight while unarmed", "unarmed combat", 
      0, 20);
  sk_add_train(SS_HUNTING, "hunt", "hunting", 0, 90);
  sk_add_train(SS_BLIND_COMBAT, "fight while blind",
      "blindfighting", 0, 50);
  sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 70);
  sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat",
      0, 90);
  sk_add_train(SS_VAMP_FOCUS, "focus power", "focus",
      200, 50);
  sk_add_train(SS_VAMP_SLASH, "slash a victim", "slash", 80, 100);
}

int sk_no_train(object who)
{
  if (!IS_MEMBER(who) && !EMRLD_WIZ(who))
  {
    command("say Only true vampires may train here!");
    return 1;
  }

/*
  if (CHECK_PUNISHMENT(BAR, TP->query_real_name()))
  {
    command("say Sorry " + TP->query_name() + ", but you are " +
        "considered unworthy to train here.");
    return 1;
  }
*/

  return 0;
}
#endif

varargs public mixed long(string str, object for_obj)
{
  string who, desc;

  /* check to see if we're looking for a coffin description */
  if (strlen(str) && sscanf(str, "%s's coffin", who))
  {
    if (!strlen(desc = COFFIN_MANAGER->query_coffin_desc(who)))
    {
      return "You examine the distinct coffins, but don't " +
          "recognize the one you are looking for.\n" +
          "Looking around, you realize it would be almost " +
          "impossible to find a particular coffin among the " +
          "other, virtually identical coffins.\n";
    }

    return desc + "\n";
  }

  return ::long(str, for_obj);
}

int item_id(string str)
{
  string beans;

  if (sscanf(str, "%s's coffin", beans))
  {
    return 1;
  }

  return ::item_id(str);
}

void create_room()
{
#ifdef TEMP_TRAINER
  set_up_skills();
#endif

  set_short("Temple Crypt");
  set_long("   You find yourself in a large, underground crypt. " +
      "Dozens of coffins, most of which are open and empty, " +
      "line the walls, which seem to emit a strange, dark " +
      "aura.\n");

  add_prop("_room_s_light_desc", "It's extremely dark in here!\n");

  add_exit("/d/Emerald/kroad/vamp/hall1", "up");
}

static int coffin_enter(object who)
{
  object coffin;
  int ret;

  if (!present(who))
  {
    return 0;
  }

  if (!(coffin = present(who->query_real_name() + "'s coffin")))
  {
    setuid();
    seteuid(getuid());

    if (!(coffin = clone_object(VAMP_ROOM_DIR + "coffin")))
    {
      return 0;
    }
    else if (coffin->move(TO, 1))
    {
      coffin->remove_object();
      return 0;
    }
  }

  coffin->set_owner(who);
  coffin->open();

  ret = who->move_living("M", coffin, 1, 1);

  coffin->close();

  return !ret;
}

int enter(string str)
{
  object env;

  if (!strlen(str) ||
    !parse_command(str, ({ }), "[into] [my] / [the] / [" +
    TP->query_real_name() + "'s] 'coffin'"))
  {
    NF("Enter what?\n");
    return 0;
  }

  env = environment(TP);
  if (coffin_enter(TP))
  {
    write("You lie down inside your coffin and close the lid " +
        "above you.\n");
    tell_room(env, ({ TP->query_name()  + " lies down in " + POS(TP) + 
        " coffin, closing the lid securely.\n",
        TP->query_nonmet_name()  + " lies down in " + POS(TP) + 
        " coffin,  closing the lid securely.\n", "" }));
  }
  else
  {
    write("You can't seem to get the lid open!\nPlease leave a bug report\n");
  }

  return 1;
}

int start(string str)
{
    if (str != "here") 
    {
        notify_fail("Start here?\n");
        return 0;
    }

    this_player()->set_default_start_location(file_name(this_object()));
    write("Ok.\n");
    return 1;
}

void init()
{
  if (lockout())
  {
    DEBUG("LOCKOUT");
    return;
  }

  // move this_player() to his/her/its coffin, if appropriate
  if (QP(TP, VAMP_I_MOVING_TO_COFFIN) && coffin_enter(TP))
  {
    RP(TP, VAMP_I_MOVING_TO_COFFIN);
    AP(TP, LIVE_I_ENTERED_VAMP_STARTLOC, 1);

    if (coffin_enter(TP))
    {
      return;
    }
  }

  if (!QP(TP, LIVE_O_LAST_ROOM) &&
      !QP(TP, LIVE_I_ENTERED_VAMP_STARTLOC) &&
      coffin_enter(TP))
  {
    AP(TP, LIVE_I_ENTERED_VAMP_STARTLOC, 1);
    return;
  }

  AP(TP, LIVE_I_ENTERED_VAMP_STARTLOC, 1);

  ::init();

#ifdef TEMP_TRAINER
  init_skill_raise();
#endif

  add_action(start, "start");
  add_action(enter, "enter");
}
