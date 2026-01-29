inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/secure/std.h"
#include "shire_defs.h"
#include "defs.h"

// Prototypes
void mv_to_secret_room(object ob);

create_object()
{
  set_name(({"statue","statuette","statuette of nob nar"}));
  set_short("statuette of Nob Nar");
  set_pshort("statuettes of Nob Nar");
  set_long(break_string(
      "You are looking at the statuette of the Great Nob Nar, "
    + "founder of the glorious Hin Warrior Guild. If you want "
    + "to join this guild, read the book 'Commitment' in the library "
    + "across the hallway. Therein lies the solution to how to join. "
    + "It also reveals how to leave our Guild, and what it will cost "
    + "you.\n",70));

  add_prop(OBJ_M_NO_GET,"@@my_get");
}

init()
{
  ::init();
  add_action("do_pledge","pledge");
}

my_get()
{
  write("You are struck by a lightning bolt when you try to get the "
   +"statuette.\n");
  say(QCTNAME(this_player()) + " is struck by a lightning bolt for trying "
   +"to steal the statuette.\n");
  return 1;
}

/*
 * A player wants to join. Make sure he/she has read the 'Commitments' book
 * in the library by using a strange command ("pledge allegiance").
 */
do_pledge(str)
{
  object ob, *obs;
  int i;

  if (!interactive(this_player())) return 0;
  if (str != "allegiance")
  {
    notify_fail("Perhaps you mean 'pledge allegiance'?\n");
    return 0;
  }
  if (this_player()->query_guild_member(GUILD_TYPE) &&
    !this_player()->query_guild_member(GUILD_NAME))
  {
    notify_fail("You are already member of a guild that we despise!\n");
    return 0;
  }
  ob = clone_object(SHIRE_PIPE);
  if (!ob->join_to_guild_from_statue()) return 1;
  ob->move(this_player());
  say(QCTNAME(this_player()) + " joins the glorious Shire-guild!\n");
  write("Welcome new member! Bear our tokens with pride.\n");
  write_file("/d/Shire/log/hin_guild",this_player()->query_name()+" joined the Hin Warriors, on "+ctime(time())+".\n");
  obs = users();
  for (i = 0; i < sizeof(obs); i++)
  {
    if (!present("shire_pipe", obs[i])) continue;
    if (environment(obs[i]) == environment(this_player())) continue;
    obs[i]->catch_msg(this_player()->query_name() + " has joined our glorious "
      +"guild!\n");
  }
  set_alarm(1.0, 0.0, &mv_to_secret_room(this_player()));
  return 1;
}

mv_to_secret_room(ob)
{
  ob->move_living("through the forcefield", HIN_DIR + "rooms/secret_room");
}
