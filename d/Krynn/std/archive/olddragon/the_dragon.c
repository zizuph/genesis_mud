/* Dragon by percy*/
/* Completely rewritten by Aridor, 5/95 */

#include "/d/Krynn/common/defs.h"
#include <filter_funs.h>

inherit "/std/callout";

string on_dragon_file, dragon_room_file;

void
rem_void()
{
    remove_call_out("go_void"); 
}

void
restart_void()
{
    rem_void();
    call_out("go_void",60);
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
    (on_dragon_file)->load_me();
    NF("It seems there is only room for two persons on the back of the dragon.\n");
    if (sizeof(FILTER_PLAYERS(all_inventory(find_object(on_dragon_file)))) > 1)
      return 0;
    restart_void();
    E(TO)->set_dircmd("dragon");
    TP->move_living("mounting the dragon", on_dragon_file);
    TP->add_prop(LIVE_O_KRYNN_DRAGON, E(TO));
    (dragon_room_file)->set_flying(1);
    return 1;
}

int
go_void()
{
    (on_dragon_file)->drop_all();
    (dragon_room_file)->take_off(0, VOID);
    return 1;
}

void
set_on_flying_dragon_room_path(string path)
{
    if (!dragon_room_file)
      dragon_room_file = path;
}

void
set_on_landed_dragon_room_path(string path)
{
    if (!on_dragon_file)
      on_dragon_file = path;
}
