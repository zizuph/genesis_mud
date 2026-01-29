inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Monks bathroom");
	set_long("   This is the bathroom of the monastery. " +
           "There are some tubs with water and small sign " +
	"on the wall.\n\n");
    add_item(({"tubs","tub"}),"Tubs are filled with water. You can "+
             "probably wash yourself with the water from them.\n");
    add_item("sign","A small readable sign.\n");
    add_item(({"wall","walls"}),"There is a small sign on the wall.\n");
 
    add_exit(TEMPLE_DIR + "dormatory", "west", 0);
    set_alarm(1.0,0.0,reset_room);
}
 
void
reset_room()
{
 object soap;
 
 soap=present("soap");
 if (soap) return;
  else
   {
    soap=clone_object(TEMPLE_DIR + "obj/soap");
    soap->move(this_object());
    return;
   }
}
 
init()
{
 ::init();
 add_action("do_wash","wash");
 add_action("do_read","read");
}
 
int
do_read(string str)
{
 if (str=="sign")
  {
   write("It says: Keep things as you found them and don't take soap " +
         "with you, please.\n");
   say(QCTNAME(TP) + " reads the sign.\n");
   return 1;
  }
 NF("Read what?\n");
 return 0;
}
 
int
do_wash(string str)
{
 if ((str=="me") || (str=="myself") || (str=="face") || (str=="hands")
       || (str=="body") || (str=="legs") || (str=="head"))
   {
    write("Ahh, you feel yourself much better.\n");
    say(QCTNAME(TP) + " washes himself.\n");
    return 1;
   }
 NF("Wash what?\n");
 return 0;
}
