inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/ruins/defs.h"
#include <money.h>
#include <macros.h>

create_room()
{
  set_short("Shadowy Room");
  set_long("This room is lit only by a small oil-lamp. Shadows play "
	+"all over the walls, distorting your vision. The only item in "
	+"the room is a small golden goblet. Everything else is covered "
	+"in a blanket of shadows.\n");
  add_item(({"oil-lamp"}),"It provides the room with a little light.\n");
  add_item(({"goblet"}),"It is a small golden goblet that looks slightly "
	+"out of place here. It is glowing with a faint dweomer, what "
	+"it means is unknown to you. There are several symbols on the "
	+"side of the goblet.\n");
  add_item(({"symbols"}),"They are ancient symbols that seem to pattern "
	+"some sort of sentence. Maybe you should try to read it.\n");
  add_cmd_item("sentence","read","The glory of Bhaal can be gained "
	+"by those who drink the nectar of this goblet.\n");
  add_prop(ROOM_NO_TIME_DESC,1);
}
init()
{
  ::init();
    add_action("drink","drink");
    add_action("defy","defy");
  }
defy(string s)
{
  NF("Defy what? Bhaal?\n");
  if(s!="Bhaal")
    return 0;

  NF("You're no follower of Bhaal!\n");
  if(!present("bh_club",TP))
    return 0;
  present("bh_club",TP)->remove_object();

  write("You defy the god's power. Pain courses through your body as if "
	+"a reminder of the might of the gods.\n");
  say(QCTNAME(TP)+" defies the power of Bhaal.\n");
  return 1;
}
drink(string s)
{
        NF("Drink what?\n");
    if(s!="nectar")
    return 0;
  say(QCTNAME(TP)+" drinks the nectar from the goblet.\n");
  write("You recieve a pin that designates you as a servant of Bhaal.\n");
  write("To defy Bhaal, just return here and type 'defy Bhaal'.\n");
  clone_object("/d/Kalad/common/trade/sewers/bh_club")->move(TP);
  return 1;
}
