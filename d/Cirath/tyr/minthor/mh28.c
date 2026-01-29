inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    if (leader) return;
bring_room_team(TZ_MINTHOR+"npc/guard",1,2,TZ_MINTHOR+"npc/guard",1);
    leader->set_random_move(5);
    leader->set_restrain_path(({TZ_MINTHOR}));
   leader->set_monster_home(TZ_MINTHOR+"mh28");
}

void
create_room()
 {
  set_short("Top of Stairs");
  set_long("You have reached the top of the extravagant set of stairs. "
   +"Before you lays a beautifully decorated set of passages. The walls "
   +"are adorned in glowing spheres, and beautiful tapestries and paintings "
   +"hang on the walls. The floor is covered in what appears to some kind "
   +"of animal hide, but you are not sure exactly what kind it is. This "
   +"seems to be the most lived in part of the house, as it is the most "
   +"lavishly decorated you have seen yet.\n");
  add_item("hide","A strange hide covers the floor. It appears to be that "
   +"of some kind of animal, but you have never before seen this strange "
   +"kind of skin.\n");
  add_item(({"passage","passages"}),"They lead off in various directions, "
   +"and are decorated with some of the finest materials you have ever seen.\n");
  add_item(({"sphere","spheres"}),"They are what light the house.\n");
  add_item(({"tapestry","tapestries"}),"They are woven of what appears to be "
   +"a mixture of giant and halfling hair, and depict various adventured in "
   +"the history of Athas.\n");
  add_item(({"painting","paintings"}),"They depict various members of the "
   +"Minthor clan.\n");
  add_item("stairs","They lead downward, and are the most elaborate set of "
   +"stairs you have ever seen.  Carefully carved from obsidian, and lined "
+"with metal, they seem to be too expensive for a set of stairs.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
   add_exit(TZ_MINTHOR + "mh29","west", 0);
   add_exit(TZ_MINTHOR + "mh13","down", 0);
  set_alarm(1.1,0.0,"reset_room");
}
