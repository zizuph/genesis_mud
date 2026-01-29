inherit "/d/Gondor/common/lib/sky.c";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"


void
create_room()
{
    extraline ="You are standing north of the walls of Edoras. There is a little stream " +
        "coming out from a hole under the wall. The gates of Edoras are to the northeast.";
    set_short("By the stream");
    make_the_room();
    add_item("hole",BSN("This is a quite large hole. The stream that comes out " +
        "from it looks quite rapid, but you think you might be able to enter it."));
    add_item(({"stream","little stream"}), BSN(
        "This is a cold rapid stream, but it's not too deep."));
    add_item(({"herbs","grass","ground"}), BSN(
        "The ground is covered with short green grass and a few herbs. It is rather wet."));
    add_exit(EDORAS_DIR + "city_entr", "northeast",0);

    set_up_herbs( ({ HERB_DIR + "curugwath", HERB_DIR + "garlic", }),
                  ({ "grass", "ground", }), 6);
    set_drink_from(({"stream"}));
}

int
do_enter(string str)
{
   if (str == "hole")
   {
       write("You enter the little hole.\n");
       set_dircmd(str);
       TP->move_living("into the hole", EDORAS_DIR + "under_wall");
       return 1;
   }
   if (str == "stream" || str == "little stream")
   {
       write(BSN("You step out in the little stream, and become all wet. "
         + "If you'd like to go under the city wall you should enter the "
         + "hole instead."));
      say(QCTNAME(TP)+" takes a little bath.\n");
      return 1;
   }
   NF("Enter what?\n");
   return 0;
}

void
init()
{
   ::init();
   init_drink();

   add_action(do_enter, "enter");
}

