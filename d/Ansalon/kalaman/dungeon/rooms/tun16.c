#include "local.h"
#include <ss_types.h>

#define W_OTHER DROOM + "well3"

inherit DUNGEON_IN;

string get_grate_desc();

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL2);
   ::create_dungeon_room();

   set_long(get_long_desc() + " A possible exit might be to the west, where the " +
      "walls seem to be a bit less narrow. In the southeast a large and rusty " +
      "grating can be seen.\n");

   add_item(({"grating", "grate"}), get_grate_desc);
   add_item(({"steel bars", "bars", "rusty bars", "rusty steel bars"}),
      "The bars seems totally covered with rust and will probably not last many " +
      "more years down here.\n");
   add_exit("tun15", "west", 0, 5, 1);
}

init()
{
  ::init();

  add_action("open_grate", "open");
  add_action("close_grate", "close");
  add_action("enter_grate", "enter");
}

string
get_grate_desc()
{
   string text;
   text = "This is a quite large iron grating, made out of crude iron bars that " +
      "have been here for years, letting the rust eat into them quite badly. The "+
      "grate seems to rest upon three iron hinges. ";

   switch (DMASTER->query_status(S_WGRATE))
   {
      case 1:
        text += "The grating is open.";
      break; 
      default:
        text += "The grating is closed.";
   }

   return text + "\n";
}

 
int
open_grate(string str)
{
    notify_fail("Open what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }), "[the] [iron] / [rusty] 'grate' / 'grating'"))
    {
       if (!DMASTER->query_status(S_WGRATE))
       {

           if (TP->query_stat(SS_STR) < 60)
           {
              write("You pull the bars of the "+ str +" hard but you are unable " +
                    "to open it.\n");
              tell_room(ENV(TP), QCTNAME(TP) + " pulls the bars of the "+ str +" hard "+
                    "but seems unable to open it.\n", TP);
           }
           else
           {
              write("You open the "+ str +", it gives off a loud noise.\n");
              DMASTER->set_status(S_WGRATE, 1);
              tell_room(ENV(TP), QCTNAME(TP) + " opens the "+ str +".\n", TP); 
           }

           return 1;
       }
       else
       {
         write("The grating is already open.\n");
         return 1;        
       }

       return 0;
    } 

    return 0;
}

int
close_grate(string str)
{
    notify_fail("Close what?\n");

    if (!str) return 0;
 
    if (parse_command(str, ({ }), "[the] [iron] / [rusty] 'grate' / 'grating'"))
    {
       if (DMASTER->query_status(S_WGRATE))
       {
         write("You close the "+ str +", the rusty hinges trembles under the weight.\n");
         DMASTER->set_status(S_WGRATE, 0);
         tell_room(ENV(TP), QCTNAME(TP) + " closes the "+ str +", it squeeks as it closes.\n",
           TP);
         return 1; 
       }
       else
       {
         write("The grating is already closed.\n");
         return 1;        
       }
      
       return 0;
    }


    return 0;
}

int
enter_grate(string str)
{
    notify_fail("Enter what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] [rusty] 'grate' / 'grating'"))
    {
        if (DMASTER->query_status(S_WGRATE))
        {
           write("You enter through the grating into the darkness.\n");
           tell_room(ENV(TP), QCTNAME(TP) + " leaves through the open "+ str +" " +
                "and vanishes into the darkness.\n", TP);
           TP->move_living("M", W_OTHER, 1);
           tell_room(ENV(TP), QCTNAME(TP) + " arrives through the "+ str +" from " +
                "the other side.\n", TP);

           return 1;
        }
        else
        {
           write("The "+ str +" is closed.\n");
           tell_room(ENV(TP), QCTNAME(TP) + " bangs " + HIS(TP) + " head into the " +
                "massive steel bars of the "+ str +" making some rust to losen and " +
                "float downwards into the darkness.\n", TP);

           return 1;
        }
 
        return 0;
    }
  
    return 0;
}
