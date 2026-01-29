

#define PATH "/d/Terel/mountains/obj"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

static object hound;

reset_room()
{
    if (hound) return;
    hound=clone_object("/d/Terel/mountains/obj/hound");
    hound->move(this_object());
}

void
init()
{
    ::init();
    add_action("do_get", "get");
    add_action("do_get", "take");
    add_action("do_get", "pick");
}

create_room()
{
    object door, chest;

    set_short("Cellar");
    set_long(
      "This chamber is strange compared to the rest of the house, in that\n"
     +"its fashion is of high quality. The walls are fitted with ornamental\n"
     +"stones and the floor is covered by a mosaic.\n");

    add_prop(ROOM_I_INSIDE, 1);

    door = clone_object(PATH + "/cdoor2.c");
    door->move(this_object());
    door->set_key(55555);
    chest = clone_object(PATH + "/chest"); 
    chest->move(this_object());
    
    add_item(({"mosaic","floor"}),
   "It looks very ancient and worn, being of a woman in black with a child.\n");

    reset_room();
}

int
do_get(string str)
{
   string s;

   if (sscanf(str, "%s from chest", s) == 1 && hound && present(hound)) {
     s = this_player()->query_real_name();
     hound->command("growl at " + s);
     write("The "+hound->short()+" is in the way!\n");
     return 1;
   }
   return 0;
}
