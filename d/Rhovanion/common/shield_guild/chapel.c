#pragma save_binary

inherit "/lib/guild_support"; 
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include <composite.h>
#include "guild.h"

#define TITLE_OBJ (THIS_DIR+"s_c_titles")

void
create_room()
{
  object board;

  set_short("Sacred room");
  set_long("This is the sacred room of the Angmar Army. You "+
           "can see many trophies from the old wars gathered by these "+
           "warriors. Though most of the things here look cruel the room "+
           "still emits an aura that might help you with your meditations. "+
           "If you are not a member of the Army, then this is the place "+
           "where you can join it. You might as well list guilds you "+
           "are member of. If you ever decide to leave the Army, you "+
           "can do it here too. Leaving is not a wise act because many "+
           "warriors will disapprove and become very angry at you "+
           "and they might even beat some experience and skills out of "+
           "your stupid head.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(THIS_DIR+"train", "south");

  seteuid(getuid());
  create_guild_support();

  clone_object(THIS_DIR+"book")->move(TO);

  board = clone_object("/d/Rhovanion/lib/board");
  board->set_board_name("/d/Rhovanion/common/boards/shield_club");
  board->move(TO);
  board->set_num_notes(13);
}

void
init() 
{
    add_action("gs_meditate", "meditate");
    add_action("join","join");
    add_action("leave", "leave");
    add_action("list", "list");
    ::init();
}

leave_inv(object who, object to)
{
    gs_leave_inv(who,to);
    ::leave_inv(who,to);
}

int
do_I_allow_join_my_guild(object player)
{
  string race = player->query_race_name();

  if(player->query_wiz_level())
  {
    player->catch_msg("Lucky wizard! No restrictions for you.\n");
    return 1;
  }
  if(player->query_guild_style("ranger"))
  {
    player->catch_msg("Someone shouts: Help!!! There is a ranger here! "+
                      "Kill him!!!\n");
    return 0;
  }
  if(member_array(race, ({"goblin","human","dwarf"})) == -1)
  {
    if(race == "elf")
      player->catch_msg("We hate elves! Get lost!!!\n");
    else
      player->catch_msg("You puny "+race+" can't swing club properly!\n");
    return 0;
  }
  if(player->query_guild_style("fighter") &&
     (player->query_alignment() > -100))
  {
    player->catch_msg("We don't want any holy warrior here!!!\n");
    return 0;
  }
  return 1;
}

int
join(string str)
{
  object shadow, soul;
  int result;
  string *soul_arr;
  string text;
  
  seteuid(getuid());

  NF("Join what? Army???\n");
  if((str != "army occupational") && (str != "army layman") && 
     (str != "army"))
    return 0;
  if(str == "army")
  {
    TP->catch_msg("You have two choices here:\n"+
                  "       join army occupational\n"+
                  "       join army layman\n");
    return 1;
  }
  if(TP->query_guild_member(GUILD_NAME))
  {
    if(str=="army layman")
    {
      TP->catch_msg("You are already member of our guild. Please do 'list' "+
                    "to check your memberships.\n");
      return 1;
    }
    else if(TP->query_guild_name_occ() == GUILD_NAME)
    {
      TP->catch_msg("You are already occupational member of our guild.\n");
      return 1;
    }
  }

  if(!do_I_allow_join_my_guild(TP)) return 1;

  if (str=="army layman")
  {
    shadow = clone_object(LAY_SHADOW);
    if((shadow->shadow_me(TP, "layman", GUILD_STYLE, GUILD_NAME)) != 1)
    {
      /* This is one of the few times you destruct is OK to use... */
      "secure/master"->do_debug("destroy",shadow);
      TP->catch_msg("Hmm... For some reason you can't join.\n");
      return 1;
    }
  }
  else
  {
    text = TP->query_s_c_level();
    shadow = clone_object(OCC_SHADOW);
    if((shadow->shadow_me(TP, "occupational", GUILD_STYLE, GUILD_NAME)) != 1)
    {
      /* This is one of the few times you destruct is OK to use... */
      "secure/master"->do_debug("destroy",shadow);
      TP->catch_msg("Hmm... For some reason you can't join.\n");
      return 1;
    }
    if(TP->query_guild_name_lay() == GUILD_NAME)
    {
      TP->remove_guild_lay();
      TP->catch_msg("You change from layman to occupational member.\n");
      TP->set_s_c_level(text);
      return 1;
    }
  }
  text = TP->query_race_name();
  if(member_array(SOUL, TP->query_cmdsoul_list()) == -1)
    TP->add_cmdsoul(SOUL);
  if(member_array(SOUL_E_NEW, TP->query_cmdsoul_list()) == -1)
    TP->add_cmdsoul(SOUL_E_NEW);
  if(member_array(SOUL_E_OLD+text, TP->query_cmdsoul_list()) != -1)
    TP->remove_cmdsoul(SOUL_E_OLD+text);
  TP->update_hooks();
  if(TP->query_wiz_level())
    TP->catch_msg("Remember to add cmdsoul '"+SOUL+"', '"+SOUL_E_NEW+
                  "' and remove '"+SOUL_E_OLD+"'.\n");
  TP->catch_msg("You joined the Angmar Army.\n");
  say(QCTNAME(TP)+" joined the Angmar Army.\n");
  return 1;
}

int
do_leave(object tp)
{
  int *skills, i, j;
  string text = tp->query_race_name();

  seteuid(getuid(TO));

  if(!tp->query_guild_member(GUILD_NAME))
  {
    tp->catch_msg("But you are not a member of the army!\n");
    return 1;
  }

  if(tp->query_guild_name_occ() == GUILD_NAME)
  {
    if(!tp->remove_guild_occ())
    {
      write("There was a strange error, I'm afraid you are stuck with us.\n");
      return 1;
    }
    /* drain occ-leave */
    tp->add_exp(-tp->query_exp_combat()/6,1);
  }
  else
  {
    if(!tp->remove_guild_lay())
    {
      write("There was a strange error, I'm afraid you are stuck with us.\n");
      return 1;
    }
    /* drain lay_leave */
    tp->add_exp(-tp->query_exp_combat()/9,1);
  }
  tp->catch_msg("As you leave the army, many angry warriors jump you "+
       "and beat you with their nasty clubs...\n"+
      "Fortunatelly you lose consciousness so you don't feel every hit.\n\n"+
     "When you wake up you notice that you have terrible headache "+
    "and that you feel less skillful.\n");
  tell_room(ENV(tp), "As "+QTNAME(tp)+" leaves the army, many angry warriors jump at "+
      HIM(tp)+" and beat "+HIM(tp)+" with their nasty clubs...\n"+
      QCTNAME(tp)+" is soon knocked down but the cruel warriors continue "+
      "beating "+HIM(tp)+", aiming mainly for "+HIS(tp)+" head.\n"+
      "After they are satisfied they leave the room leaving "+
      QTNAME(tp)+" laying on the floor...\n\n"+
      "After a long time "+QTNAME(tp)+" regains his sense and touches "+HIS(tp)+
      " sore head. "+CAP(HE(tp))+" must be regretting leaving army now!\n", tp);
  tp->set_max_headache(MAX(1000, tp->query_max_headache()));
  tp->set_headache(tp->query_max_headache());

  if(member_array(SOUL, tp->query_cmdsoul_list()) != -1)
    tp->remove_cmdsoul(SOUL);
  if(member_array(SOUL_E_NEW, tp->query_cmdsoul_list()) != -1)
    tp->remove_cmdsoul(SOUL_E_NEW);
  if(member_array(SOUL_E_OLD+text, tp->query_cmdsoul_list()) == -1)
    tp->add_cmdsoul(SOUL_E_OLD+text);
  tp->update_hooks();

  tp->remove_skill(SS_SHIELD);
  tp->remove_skill(SS_SMASH);

  skills = tp->query_all_skill_types();
  for(i=0; i<sizeof(skills); i++)
  {
    if((skills[i]<1000))
    {
      j = tp->query_skill(skills[i]);
      tp->set_skill( skills[i], j - random(MIN(j,20)) );
    }
  }
  tp->set_default_start_location(tp->query_def_start());
  TITLE_OBJ->remove_entry(tp->query_real_name());
  return 1;
}

int
leave(string str)
{
  int *skills, i;
  string text = TP->query_race_name();

  NF("Leave what? Army???\n");
  if(str != "army") return 0;

  return do_leave(TP);
}

int
list(string str)
{
  string guilds = TP->list_mayor_guilds();

  NF("List what? Guilds???\n");
  if(str != "guilds") return 0;

  if(guilds) write("You are member of the following guilds:\n" + guilds);
  else write("You have not joined any guild yet.\n");
  return 1;
}

int
gs_hook_already_meditate()
{
  write("You are already meditating. You can stop it by typing 'rise'.\n");
  return 1;
}

void
gs_hook_start_meditate()
{
  write("You sit down and start to meditate upon yourself.\n"+
	"You find yourself able to <estimate> your attributes "+
	"and <set> your learning preferences.\n"+
	"Just <rise> when you have finished meditating.\n");
  say(QCTNAME(this_player()) + " sits on the floor and starts to meditate.\n");
}

void
gs_hook_rise()
{
  write("Relaxed you rise from the floor.\n");
  say(QCTNAME(this_player()) + " rises from the floor.\n");
}

int 
gs_hook_catch_error(string str)
{
    write("You can't do that while meditating.\n");
    return 1;
}
