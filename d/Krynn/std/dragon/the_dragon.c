/* Dragon by percy*/
/* Completely rewritten by Aridor, 5/95 */

#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>

string dragon_room_file;
int govoidalarm = 0;

void
restart_void()
{
    if (govoidalarm)
      remove_alarm(govoidalarm);
    govoidalarm = set_alarm(60.0,0.0,"go_void");
}

void
land()
{
    string room;
    room = (dragon_room_file)->query_place();
    TO->move(room, 1);
    tell_room(E(TO), "A dragon descends from the sky.\n");
    if (room != VOID)
      restart_void();
}

void
init_dragon()
{
    ADA("mount");
    ADA("kick");
}

int
kick(string str)
{
  if (str != "dragon")
    return 0;
  
  command("stare " + TP->query_real_name());
  command("say Watch your timing! First mount, then maybe you can kick me!\n");
  return 1;
}

int
mount(string str)
{
    NF("Mount who?\n");
    if (str != "dragon")
      return 0;
    /*if (TP->query_alignment() < -20)
      {
      write("The dragon refuses to let you mount because you are too evil.\n");
      return 1;
      }*/
    (dragon_room_file)->load_me();
    NF("The dragon doesn't seem to feel like carrying people, so he refuses to let you mount.\n");
    if (!dragon_room_file)
      return 0;
    NF("It seems there is only room for two persons on the back of the dragon.\n");
    if (sizeof(FILTER_PLAYERS(all_inventory(find_object(dragon_room_file)))) > 1)
      return 0;
    restart_void();
    E(TO)->set_dircmd("dragon");
    TP->move_living("mounting the dragon", dragon_room_file);
    TP->add_prop(LIVE_O_KRYNN_DRAGON, E(TO));
    (dragon_room_file)->set_flying(1);
    return 1;
}

int
go_void()
{
    govoidalarm = 0;
    (dragon_room_file)->drop_all();
    (dragon_room_file)->take_off(0, VOID);
    return 1;
}

void
set_on_dragon_room_path(string path)
{
    if (!dragon_room_file)
      dragon_room_file = path;
}

