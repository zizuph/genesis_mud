/*
 * Milan
 */

#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include "guild.h"
#include "/d/Rhovanion/defs.h"

#define SAVE_FILE   THIS_DIR+"S_C_PRIV"
#define VOTE_ROOM   (THIS_DIR+"vote")

private mapping authorized;
private mapping unauthorized;
static string *names;
static int alarm;

void
create_room()
{
  object board, book;
  int i, j;
  string *arr;

  set_short("Private room");
  set_long("This is the room for members of Angmar's Army. "+
           "Here you can discuss guild matters in privacy or leave a "+
           "message for other members. To the north is the big court "+
           "room while east is the entrance to the small store room. "+
           "Next to the entrance hangs a simple sign. To the south you "+
           "see yet another store room. It is a bit smaller than eastern "+
           "one and there is no sign hanging next to the entrance.\n");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_exit(THIS_DIR+"vote", "north");
  add_exit(THIS_DIR+"train", "west");
  add_exit(THIS_DIR+"store2", "south");
  add_exit(THIS_DIR+"store", "east","@@block_exit");

  add_item(({"sign","simple sign"}), "A simple sign with writing on it.\n");
  add_item("writing", "Can you read it?\n");
  add_cmd_item(({"sign","simple sign","writing"}), "read", "\n"+
      "            AUTHORIZED PERSONNEL ONLY!!!\n\n"+
      "  Unauthorized persons will be cooked and served as dinner!\n\n"+
      "  Soldiers can:\n"+
      "       'list authorized'\n"+
      "       'list removed authorizations'\n"+
      "       'who is <short desc>'\n"+
      "  Captain, lieutenants and council members can:\n"+
      "       'allow entry to <name>'\n"+
      "       'disallow entry to <name>'\n\n"+
      "                                    Dark Lord\n\n");

  seteuid(getuid());
  book = clone_object(THIS_DIR+"book");
  book->move(this_object());
  book->set_book_is_private(1);
  board = clone_object("/d/Rhovanion/lib/board");
  board->set_board_name("/d/Rhovanion/common/boards/shield_club_priv");
  board->set_num_notes(30);
  board->move(this_object());

  authorized = ([ ]);
  unauthorized = ([ ]);
  restore_object(SAVE_FILE);
  names = m_indexes(authorized);
  for(i=0; i<sizeof(names); i++)
    if(!(VOTE_ROOM->aa_member(names[i]))) 
      authorized = m_delete(authorized, names[i]);
  names = m_indexes(authorized);
  sort_array(names);
  arr = m_indexes(unauthorized);
  for(i=0; i<sizeof(arr); i++)
  {
    for(j=0; j<sizeof(unauthorized[arr[i]]); j++)
      if(!(VOTE_ROOM->aa_member(unauthorized[arr[i]][j])))
        unauthorized[arr[i]] -= ({ unauthorized[arr[i]][j] });
    if(!sizeof(unauthorized[arr[i]]))
    {
      unauthorized = m_delete(unauthorized, arr[i]);
    }
    else sort_array(unauthorized[arr[i]]);
  }
  save_object(SAVE_FILE);
}

string get_desc(string name)
{
  object ob = "/secure/master"->finger_player(LOW(name));
  string str = ob->query_nonmet_name();
  ob->remove_object();
  return str;
}

int block_exit()
{
  string name = TP->query_name();

  if ((name == "Milan") || (name == "Guild_cleaner")) return 0;
  if(member_array(name, names) != -1)
  {
    if (get_desc(name) != authorized[name])
    {
      write("Your description doesn't match our record. "+
            "Authorisation removed.\n");
      authorized = m_delete(authorized, name);
      names = m_indexes(authorized);
      sort_array(names);
      seteuid(getuid());
      save_object(SAVE_FILE);
      return 1;
    }
    return 0;
  }
  write("You decided that you do not want to be cooked and served as "+
        "a dinner after all.\n");
  return 1;
}

void init()
{
  ::init();
  add_action("allow","allow");
  add_action("disallow","disallow");
  add_action("list","list");
  add_action("who","who");
}

int allow(string str)
{
  string name, desc, *arr = explode(str, " ");
  int i;

  if((sizeof(arr) != 3) || (arr[0] != "entry") || (arr[1] != "to"))
  {
    NF("Allow what?\n");
    return 0;
  }
  name = CAP(arr[2]);
  if(!(VOTE_ROOM->aa_member(name)))
  {
    NF(name+" is not a member of the army.\n");
    return 0;
  }
  if((VOTE_ROOM->rank_no(TP) < 5) &&
     (member_array(TP->query_name(), VOTE_ROOM->query_council()) == -1) &&
     (TP->query_name() != "Milan"))
  {
    NF("You cannot do that!\n");
    return 0;
  }

  if(member_array(name, names) != -1)
  {
    write(name+" is already authorized to enter store room.\n");
    return 1;
  }
  desc = get_desc(name);
  authorized += ([ name:desc ]);
  names = m_indexes(authorized);
  sort_array(names);
  arr = m_indexes(unauthorized);
  for(i=0; i<sizeof(arr); i++)
    if(member_array(name, unauthorized[arr[i]]) != -1)
    {
      unauthorized[arr[i]] -= ({ name });
      if(!sizeof(unauthorized[arr[i]]))
        unauthorized = m_delete(unauthorized, arr[i]);
    }
  seteuid(getuid());
  save_object(SAVE_FILE);
  write("You authorize "+name+", "+desc+", to enter the store room.\n");
  return 1;
}

int disallow(string str)
{
  string name, *arr = explode(str, " ");

  if((arr[0] != "entry") || (arr[1] != "to"))
  {
    NF("Disallow what?\n");
    return 0;
  }
  name = CAP(arr[2]);
  if(member_array(name, names) == -1)
  {
    NF(name+" is not authorized to enter the store room.\n");
    return 0;
  }
  if((VOTE_ROOM->rank_no(TP) < 5) &&
     (member_array(TP->query_name(), VOTE_ROOM->query_council()) == -1) &&
     (TP->query_name() != "Milan"))
  {
    NF("You cannot do that!\n");
    return 0;
  }

  authorized = m_delete(authorized, name);
  names = m_indexes(authorized);
  sort_array(names);
  if(member_array(TP->query_name(), m_indexes(unauthorized)) == -1)
  {
    unauthorized += ([ TP->query_name():({ name }) ]);
  }
  else
  {
    unauthorized[TP->query_name()] += ({ name });
    sort_array(unauthorized[TP->query_name()]);
  }
  seteuid(getuid());
  save_object(SAVE_FILE);
  write("You remove authorization of "+name+" to enter store room.\n");
  return 1;
}

int list(string str)
{
  int i;
  string *arr;

  if(str == "authorized")
  {
    write("List of authorized personnel:\n\n"+implode(names, ", ")+"\n");
    return 1;
  }
  if(str == "removed authorizations")
  {
    arr = m_indexes(unauthorized);
    if(!sizeof(arr)){ write("No one has removed any authorization.\n"); }
    else for(i=0; i<sizeof(arr); i++)
      write(arr[i]+" removed authorization of: "+
            implode(unauthorized[arr[i]], ", ")+"\n");
    return 1;
  }
  NF("List what?\n");
  return 0;
}

int who(string str)
{
  string desc, *arr = ({ });
  int i;

  if (!str || !sscanf(str, "is %s", desc)) return 0;

  for (i=0; i<sizeof(names); i++)
    if (authorized[names[i]] == desc)
      arr += ({ names[i] });
  if (!sizeof(arr))
  {
    write("There is no soldier with description '"+desc+
          "' authorized to enter the store room.\n");
    return 1;
  }
  write("Soldiers authorized into the store room with description '"+desc+
        "' are: "+implode(arr, ", ")+".\n");
  return 1;
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (!alarm && !living(ob))
    alarm = set_alarm(10.0, 0.0, "tidy_room");

  if(!living(ob) || ob->query_wiz_level() ||
     (ob->query_name() == "Guild_cleaner") ||
     ob->query_guild_member(GUILD_NAME)) return;

  ob->command("look");
  ob->catch_msg("A bunch of warriors come screaming at you!\n"+
        "They grab you and throw you out of their private room.\n");
  tell_room(THIS_DIR+"train", QCTNAME(ob)+" comes flying from the east and "+
                              "lands in one heap on the floor.\n");
  ob->move(THIS_DIR+"train");
  tell_room(TO, QCNAME(ob)+" arrives.\n"+
        "A bunch of warriors come screaming at "+QTNAME(ob)+"!\n"+
        "They grab "+HIM(ob)+" and throw "+HIM(ob)+" out.\n");
}

void
tidy_room()
{
  object cleaner;

  alarm = 0;
  seteuid(getuid());
  cleaner = clone_object("/std/monster");
  cleaner->set_name("guild_cleaner");
  cleaner->set_base_stat(SS_STR, 350);
  cleaner->set_base_stat(SS_DEX, 10);
  cleaner->set_base_stat(SS_CON, 150);
  cleaner->set_base_stat(SS_WIS, 10);
  cleaner->set_base_stat(SS_INT, 10);
  cleaner->set_base_stat(SS_DIS, 30);
  cleaner->set_pname("trolls");
  cleaner->set_race_name("troll");
  cleaner->set_adj(({"huge", "clumsy"}));
  cleaner->set_short("huge clumsy troll");
  cleaner->add_prop(LIVE_I_NEVERKNOWN, 1);
  cleaner->move(TO, 1);
  tell_room(TO, QCNAME(cleaner)+" arrives.\n");
  cleaner->command("get all");
  cleaner->command("sigh");
  cleaner->command("e");
  cleaner->command("drop all");
  cleaner->command("w");
  cleaner->command("say I have my orders... Keep this place tidy!");
  tell_room(TO, QCNAME(cleaner)+" leaves.\n");
  cleaner->remove_object();
}
