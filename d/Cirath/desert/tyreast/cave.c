
inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/desert/defs.h"
#include "/d/Cirath/common/defs.h"

object box;
void
create_room()
 {
  set_short("Dim Cave");
  set_long("You are inside of a dim, dry cave.  You see the "
        +"occasional tattered rag or bone fragment among the "
	+"rocks, but there is not much else.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);
  add_exit(DESERT + "d19","west");
  set_alarm(1.0,0.0,"box_func");
}

void
box_func()
{
    box = clone_object(DES_OBJ + "box");
    box->move(this_object());
    set_alarm(1.0,0.0,"b_friend_func");

}

void
b_friend_func()
{
    int i;

    if (!box || present("dagger", box))
        return;

     for(i = 0; i < 1; i++)
        clone_object(DES_WEP +"b_friend")->move(box);
}


