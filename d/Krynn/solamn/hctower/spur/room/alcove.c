
// alcove.c
// grace aug 1994

#include "../local.h"
inherit SPURRM;

int pcan;


create_spur_room()
{

   SHORT("Alcove");
   LONG("This alcove was small before you got into it.\n"+
	"Now the shelves have been upset and dozens of the "+
	"candles that have been blessed for the altar lay "+
	"at your feet. You hardly have room to move. South " +
	"from here is the chapel.\n");
   
   LIGHT;

   AE(ROOM + "chapel", "south", 0);

   AI(({"candles","candle"}), "@@candle");
   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"wax", "lumps"}), "The wax is stuck to the floor.\n");
   AI(({"shelves", "shelf"}), "@@shelf");
   ACI(({"candle","candles"}), 
     ({"put","put on shelf","put back", "return to shelf", "return", "set", "set on shelf"}),
     "@@do_good"); 
}


init()
{
    ::init();
    ADD("do_good", "pick up");
    ADD("do_good", "pick");
    ADA("get");
    ADD("get","take");
}

int
do_good()
{
   write("You pick the candles up and put them back on the "+
      "shelves. You hear a soft 'click' and the wall "+
      "slides back, revealing a hidden passageway.\n");
   say(QCTNAME(TP) + " disappears from view.\n");
   TP->move_living("through the secret passage", ROOM + "hp1", 1);
   return 1;
}  


string
shelf()
{
    if (pcan == 10)
      {
          write("All the candles have been gotten.\n");
          SAY(" looks at the empty shelves.");
          return "";
      }

    write("The shelves are empty except for a few candles.\n");
    SAY(" looks at the shelves.");
    return "";
}

string
candle()
{
    if (pcan == 10)
      {
          write("The lumps of wax at your feet bear little " +
             "resemblance to candles.\n");
          return "";
      }
    write("These candles are for burning on Paladine's altar, " +
           "not for floor wax!\n");
    SAY(" looks at the candles on the floor.");
    return "";
}

int
get(string str)
{
    NF("Get what?\n");
    if ((str == "candle") || (str == "candle from shelf") ||
        (str == "candles") || (str == "candle from floor"))
      {

          if (pcan == 10)
            {
                write("The candles have been ground into lumps of "+
                   "wax under your feet.\n");
                return 1;
            }

          clone_object(SOBJ + "pcandle")->move(TP);
          write("You get a candle from the floor.\n");
          SAY(" gets a candle from the floor.\n");
          pcan++;
          return 1;
      }
    return 0;
}


