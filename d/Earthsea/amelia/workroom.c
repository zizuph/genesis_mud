inherit "/std/room.c";
#include <stdproperties.h>

int
query_prevent_snoop()
{
    return 1;
}

void
create_room()
{
    ::create_room();
    set_short("An eyrie");
    set_long("This looks like an eyrie, home of "+
      "creatures who fly. There is a window that "+
      "looks out over gulfs of air and light. Inside "+
      "you see herbs of all kinds, drying on the rafters, "+
      "and alembics, tubes, mortars and pestles, on a "+
      "long table against the wall.\n");
    add_prop(ROOM_I_LIGHT, 1);
    add_item((({"alembics", "tubes", "herbs", 
	  "mortars", "pestles"})),
      "This seems to be the room of a herbal "+
      "healer.\n");
    add_item("window",
      "The window looks out on the open air, far above "+
      "the cares of earth. Light filters through hazy "+
      "clouds. It makes you feel you are flying.\n");
}

void
init()
{
    object tp = this_player();
    ::init();
}

/*
int
poem(object tp)
{
    tp->catch_msg("Words drift silently through "+
      "your mind ... \n \n"+
      "     Only in silence the word,\n"+
      "     only in dark the light, \n"+
      "     only in dying life, \n"+
      "     bright the hawk's flight \n"+
      "     on the empty sky.\n");
    return 1;
}
*/
