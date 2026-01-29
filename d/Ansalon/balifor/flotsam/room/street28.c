#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;
object door;
int    dAlarm_id1;

/*
* Prototypes
*/
void remove_door();

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("Alleyway");
   set_long("@@long_descr");
   
   add_item("vermin","You are not sure, but you think it was a " +
      "large rat. Glowing red eyes stare at you from the darkness, " +
      "giving you the impression that you are not wanted here. \n");
   add_item("garbage","You name it, if it smells bad, yur " +
      "standin' in it! \n");
   add_item("walls","On the dirt-crusted walls you can make out " +
      "graffiti tags and other slanderous scribble. You notice " +
      "something strange about the east wall.\n");
   add_item("east wall","Unlike the other walls, there seems to " +
      "be a clean patch of brickwork, in the shape of a door. There " +
      "is a small symbol of a yellow skull scrawled on this section " +
      "of wall. \n");
   add_item(({"symbol","yellow skull"}),"This symbol of the " +
      "yellow skull seems to have been carved into the wall, and by " +
      "the looks of things has been there for some time. \n");
   add_item("darkness","You look into the darkness, and you notice " +
      "it is looking back at you! Glowing red eyes snap open, and watch your every " +
      "movement. \n");
   add_item("scribble","Mostly tags and slander. You " +
      "could probably read some of it if you were interested in " +
      "that sort of thing... \n");
   add_exit(FROOM + "street27","north",0);
   add_exit(FROOM + "street30","west",0);
   
   
   add_cmd_item("scribble","read","@@read_graff");
   reset_flotsam_room();
}

string
long_descr()
{
   return tod_descr1() + "You stand in a dark alleyway. The filthy " +
   "main streets are nothing compared to this. Vermin skitter across " +
   "your feet and into the garbage, and the walls are covered with " +
   "scribble. The smell is almost unbearable. To the north the alley " +
   "opens up onto a main street, while to the west the alley continues " +
   "into the darkness. \n";
}

int
read_graff()
{
   write("You manage to make out something like DRACOS SMeG OFF! " +
      "GOBbOS ROCK!...Hmm, there is something about someone by " +
      "the name of Kitiara that has been scrubbed off... you " +
      "cannot make out what it said. \n");
   return 1;
}

init()
{
   ::init();
   ADA("search");
}

search(string str)
{
   if(str != "east wall")
      return 0;
   if(door)
      return 0;
   get_door();
   return 1;
}

get_door2()
{
   if (door)
      door->remove_object();
   
   if (dAlarm_id1)
      {
      remove_alarm(dAlarm_id1);
      dAlarm_id1 = set_alarm(20.0, 0.0, &remove_door());
   }
   else
      {
      dAlarm_id1 = set_alarm(20.0, 0.0, &remove_door());
   }
   
   door = clone_object(FOBJ + "secretdoora.c");
   door->move(TO);
   door->set_key(K_FLOTSAM);
   tell_room(TO,"A secret door opens in the east wall!\n");
}

remove_door2()
{
   door->remove_object();
   if (dAlarm_id1)
      {
      remove_alarm(dAlarm_id1);
      dAlarm_id1 = 0;
   }
}

get_door()
{
   get_door2();
   call_other(FROOM + "street29.c","get_door2");
}

remove_door()
{
   remove_door2();
   call_other(FROOM + "street29.c","remove_door2");
   tell_room(TO,"The secret door slams shut and becomes " +
      "unnoticeable again. \n");
}
