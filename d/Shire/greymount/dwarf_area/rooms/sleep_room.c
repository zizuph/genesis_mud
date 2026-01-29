/*
** The Sleeping Room for the Meade and Mutton Inn
** Created By Leia
** March 1, 2006
*/


inherit "d/Shire/room.c";

#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"
#include "../defs.h"

create_room()
{
   set_short("Sleeping Room in the Meade and Mutton Inn");
   set_long("You have entered the sleeping room of the Meade and Mutton Inn. There are several beds about the room, all of which look equally comfortable. It is very dim here, thankfully, as it would be hard to sleep otherwise. You notice a slight, faint depression in one of the rock walls here. There is also a sign with further instructions for this room.\n");

   add_item(({"wall", "walls"}), "The walls here are hewed out of the stone of the mountain. On the west wall, a slight, faint depression can be seen. There is a sign above the depression that catches your eye.\n");

   add_item(({"west wall"}), "This wall has a slight, faint depression in it. There is also a sign above the depression.\n");
   
   add_item(({"bed","beds"}), "The beds are quite large and seem to be very clean. They look as though they would provide a very comfortable night's sleep.\n");
   
   add_item(({"depression", "slight depression", "faint depression", "slight, faint depression", "slight faint depression"}), "The depression looks like this:\n\n" + 
	"......    .....        ..... .....               ....... \n" +
	"... ...     ....        ....   ...              ......... \n" +
	"...  ...    .....      .....   ...             ........... \n" +
	"...   ...   ......    ......   ...     ....   ... .... .... \n" +
	"...    ...  ... ...  ... ...   ...    .....  ...  ....  .... \n" +
	"...    ...  ...  ......  ...   ...   ...... ...   ....   .... \n" +
	"...   ...   ...   ....   ...   ...  ... ...       ....    .... \n" +
	"...  ...    ...          ...   ... ...  ...       .... \n" +
	"... ...     ...          ...   ......   ...       .... \n" +
	"......      ...          ...   .....    ...       .... \n" +
	"......      ...          ...   ....     ...       .... \n" +
	"... ...     ...          ...            ...       .... \n" +
	"...  ...    ...          ...            ...       .... \n" +
	"...   ...   ...          ...            ...       .... \n" +
	"...    ...  ...          ...            ...       .... \n" +
	"...     ... ...          ...            ...       .... \n" +
	"...      ........        .....          .....     ...... \n\n" + "It looks as though it is some sort of carved out rune.\n");
	   
    add_item(({"sign"}), "It is a nicely made, surprisingly wooden sign. Perhaps you should read it?\n");

  add_exit(INN, "south", 0, 2,);

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

init()
{
  ::init();

    add_action("start","start");
    add_action("check_time","time");
    add_action("read_sign","read");
}

int start(string s)
{
  object ob;

  if(!(ob=present("inn_rune",TP)))
     {
       write("You don't have what you need to start in this location.\n");
       return 1;
     }
  NF("Start where?\n");
  if(s!="here") return 0;

  ob->remove_object();

  TP->set_temp_start_location(SLEEP);
     write_file("/d/Shire/log/hotel",TP->query_name()+" chose the "
     + "Meade and Mutton Inn as a temporary starting location on "
     + ctime(time()) + ".\n");

     write(BS("Noticing the depression in the wall, you place the rune inside of it. A pale silver light fills the room, bathing you in its glow. You feel pretty confident that you will awaken here after the next time you sleep.\n"));
  return 1;
   }

int
read_sign(string str)
{
   if(str != "sign")
     {
     write("You cannot make out the words to "+str+", it's too dark.\n");
      return 1;
      }
   write("In the dim light of the room, you can just barely make out the words: \n"+
         "To stay the night, type 'start here'\n");
     return 1;

}
