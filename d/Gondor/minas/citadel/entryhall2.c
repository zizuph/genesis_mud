inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"

object guard1, guard2;

create_room()
{
  set_short("West end of the Entrance Hall in the White Tower");
  set_long("You are in the west end of the paved passage in the great halls\n"+
    "of the White Tower. To the west is a door of polished metal. Archways\n"+
    "of white stone lead north and south from here. The long and empty\n"+
    "passage leads east.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/minas/citadel/entryhall","east",0,0);
  add_exit("/d/Gondor/minas/citadel/n_stair","north","@@check_guard",0);
  add_exit("/d/Gondor/minas/citadel/s_stair","south","@@check_guard",0);
  clone_object("/d/Gondor/minas/obj/hall_door_out")->move(this_object());
  add_guards();
}

add_guards() {
  if (!guard1) {
    guard1 = clone_object("/d/Gondor/common/npc/citadel_guard");
    guard1->move(this_object());
    }
  if (!guard2) {
    guard2 = clone_object("/d/Gondor/common/npc/citadel_guard");
    guard2->move(this_object());
    }
}

reset_room()
{
  add_guards();
}

check_guard()
{
  if (present("guard",this_object())) {
    if (this_player()->query_wiz_level()) {
      present("guard")->command("bow "+this_player()->query_real_name());
      return 0;
      }
    present("guard")->command("say You are not allowed in there, "+
      ((this_player()->query_gender()==G_MALE) ? "sir" : "mylady")+".");
     return 1;
     }
  return 0;
}

