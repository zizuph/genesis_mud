inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <filter_funs.h>

#include "../../ctower.h"
 
void
make_pillar(string color)
{
    object ob;

    ob = clone_object(CTOWER_OBJ + "pillar");
    ob->set_color(color);
    ob->move(this_object(), 1);
}

void
ctower_reset()
{
    if (sizeof(FILTER_LIVE(all_inventory())))
    {
        return;
    }
  
    all_inventory()->remove_object();
  
    for_each(({ "red", "yellow", "blue", "green" }), make_pillar);

    clone_object(CTOWER_OBJ + "column")->move(this_object(), 1);
}
 
void
create_ctower_room()
{
    object ob;
   
    set_short("Crystal chamber");
   
    set_long("This is a huge chamber made entirely of "+
	"crystal.  Every color, shade and hue of crystal is represented "+
	"somewhere in this chamber.  At the four compass points are "+
	"pillars of transparent crystal about one meter in height and at "+
	"the center of the chamber is a column of crystal also about a "+
	"meter in height but made of a crystal that flickers with all of the "+
	"colors of the spectrum.\nA bright, corruscating portal lies on the " +
	"floor near the center of the room.\n");
   
    add_item(({"wall", "floor", "ceiling"}), "The wall is a melding of "+
	"myriad crystals and infinite colors.\n");
   
    add_item(({ "portal", "bright portal", "corruscating portal", 
	"bright corruscating portal" }), "The portal crackles with " +
	"energy, flashing with blinding color, and flooding the room " +
	"with magical energy.\n");
  
    add_exit(CTOWER_ROOM_FIN + "six3", "east");
    add_exit(CTOWER_ROOM_FIN + "six2", "west");
    add_exit(CTOWER_ROOM_FIN + "six1", "north");
    add_exit(CTOWER_ROOM_FIN + "six4", "south");
   
    setuid();
    seteuid(getuid());
   
    ctower_reset();
}

int enter(string str)
{
    if (str == "portal" || str == "corruscating portal" ||
	str == "bright portal" || str == "bright corruscating portal")
    {
	write("The portal is obviously unstable....  To enter it now " +
	    "would be suicide!\n");
	return 1;
    }
  
    notify_fail("Enter what?\n");
    return 0;
}

void init()
{
    ::init();
  
    add_action(enter, "enter");
}
