inherit "/std/room";

#define LOCKOUT
#ifdef LOCKOUT
inherit "/d/Emerald/common/guild/vamp/room/lockout";
#endif

void create_room()
{
  set_name("testroom");
}

