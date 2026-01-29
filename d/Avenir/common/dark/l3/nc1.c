// file name: ~Avenir/common/dark/l3/nc1.c
// creator(s):
// revision history:
//   - 29.03.95 Added traces add_item, added enter ability. -=Denis
// purpose:
// note: in this room imp does not appear just after the room loading,
//       but only at first reset_room(). this is not a bug, but a feature.
// bug(s):
// to-do:

#include "l3_defs.h"
inherit L3_ROOM;

#include "/d/Avenir/common/dark/dark.h"
#define PATH "/d/Avenir/common/dark/mon/"

void
create_room()   
{
  set_short("Small dark cavern");
  set_long(
"A dark gloomy cavern in the depths of tunnel system. The rough-hewn\n"+
"walls slope down to the dusty floor. There are some old bones in one\n"+
"of the corners. A small pool is in the cavern centre.\n");
// Should probably move this room due to mapping conflict
  add_exit("/d/Avenir/common/dark/l3/n4","southwest");

  add_prop(ROOM_I_LIGHT,0);
  add_prop(ROOM_I_INSIDE,1);
  
  add_item(({"wall","walls"}),
"The rough-hewn walls slope down to the dusty floor. A writing is\n"+
"inscribed upon one of them. Here and there cracks and traces of water\n"+
"can be seen.\n");

  add_item(({"floor","dust","dusty floor"}),
"Traces of tunnel creatures can be seen on the dusty floor.\n");

  add_item(({"bone","bones"}),
"You can see bones, mostly broken, in one of the cavern corners.\n"+
"Due to their condition you are unable to determine which race\n" +
"they belong to.\n");

  add_item(({"writing","inscription"}),
"There is an inscription on the cavern wall opposite to the exit.\n"+
"The unknown person, probably whom the bones belonged to, used a\n"+
"sharp edge of a sword or a dagger to create his last message...\n"+
"The inscription is very old, so some of it is unreadable.\n"); 

  add_item(({"pool","water","little pool"}),
"There is a little pool of fresh water in the center of the cavern. You\n"+
"can see nothing special about it. Also there are traces of water on\n"+
"the walls, which indicates the presence of underground river nearby.\n");
    
  add_item(({"traces","trace"}),
"There are some traces of water on the cavern walls.\n"+
"Looks like there is an underground river nearby.\n");
    
  add_prop(STATUES_IN_ROOM,random(1)+1);
}

void
init()
{
  ::init();
  add_action("read_writing","read");
  add_action("enter_pool","enter");
}

int
read_writing(string str)
{
  NF("Read what?\n");
  if(str=="writing"||str=="inscription")
    {
      write("You read the following:\n\n"+
"...yesterday they killed my brother. He died in the acid pool. He was\n"+
"screaming so that everyone in the tunnels heard him, but none was able\n"+
"to help, nobody was fast enough. Death and fear live among us. Everyone\n"+
"is simply waiting his fate and wondering how will he die. But what can we\n"+
"do? Maybe accepting their proposal will help? What is t ah rrf...\n");

      return 1;
    }
}


int
enter_pool(string str)
{
  NF("Enter what?\n");
    if(str=="pool"||str=="little pool")
    {
	write(
"You enter the waters and start searching the bottom of "+
"the pool trying to find something. The pool is very small and searching "+
"didn't take much time. However you find nothing valuable.\n");
	tell_room(environment(TP),
QCTNAME(TP)+" enters the pool and soon comes out disappointed.\n",TP);
        return 1;
      }
  }






