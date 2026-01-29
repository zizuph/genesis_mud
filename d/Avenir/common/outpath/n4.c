// file name:    n4
// creator(s):   Cirion, April 1996
// last update:  Denis, Aug'96: Destroyed nortwest going bug.
// purpose:      Tunnel for the newbie area.
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"

int pass_northeast();
int pass_northwest();
  
void create_room()
{
  set_short("shadowy tunnel");
  set_long("The uneven tunnel reaches a junction here, "
    +"continuing from the southwest to the northeast, "
    +"and a side tunnel breaking off to the northwest, "
    +"from where a terrible stench emanates. There "
    +"is a pale light coming from the northeast.\n");

  ACI(({"","air","here"}),({"smell","sniff"}),"The air smells "
    +"terrible, like the decay of some ancient beast.\n");

  add_item(({"wall","walls","rock"}),"The rock walls of this "
    +"tunnel are craggy and rough-hewn. To the northwest, "
    +"the tunnel seems to become smoother and more regular.\n");
  add_item(({"floor","ground"}),"The ground is cold and "
    +"rough, making your footing treacherous.\n");
  add_item(({"ceiling","roof"}),"The ceiling of the tunnel "
    +"is hidden in shadows.\n");
  add_item(({"shadow","shadows","darkness"}),"The shadows are "
    +"everywhere.\n");

  IN;
  IN_IN;
  remove_prop(ROOM_I_LIGHT);

  add_exit(OUTPATH+"n3", "southwest");
  add_exit(OUTPATH+"ledge1", "northeast", pass_northeast);
  add_exit(OUTPATH+"lair1", "northwest", pass_northwest);
}

int pass_northeast()
{
  write("You walk out onto a steep ledge.\n");
  TP->add_panic(LEDGE_PANIC);
  return 0;
}

int pass_northwest()
{
  if(!TP->query_prop("hold_my_nose"))
  {
    if(TP->query_stat(SS_DIS) > 55)
    {
      write("You manage to overcome the horrible stench and "
           +"go down the tunnel.\n");
      return 0;
    }

    TP->command("$gag");
    write("The smell is too awful, you cannot pass without " +
	  "holding your nose.\n");
    return 1;
   }

   TP->remove_prop("hold_my_nose");
   write("You walk down the tunnel, holding your nose shut "
        +"against the smell.\n");
   return 0;
}

void init()
{
  ::init();
  add_action("hold", "hold");
  add_action("hold", "shut");
  add_action("hold", "pinch");
}

int hold(string str)
{
  NF(CAP(QVB)+" what?\n");
  if(!parse_command(str, ({}), "[my] 'nose' [shut] / [closed]"))
    return 0;

  write("You "+QVB+" you nose closed against the smell.\n");
  say(QCTNAME(TP)+" "+QVB+"s "+POSSESS(TP)+" nose.\n");
  TP->add_prop("hold_my_nose", 1);
  return 1;
}

