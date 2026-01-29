inherit "/std/room";
 
#include "/d/Emerald/defs.h"

int do_pull(string arg);
int do_push(string arg);
 
int pulled;
 
reset_room()
{
 remove_item("inscription");
 pulled = 0;
}
 
void create_room()
{
    object door;
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Prison cell");
    set_long("   You have entered one of the prison cells in the " +
             "dungeon. Its the only noticable feature is a bed.\n\n");

    add_item(({"wall","walls"}),"@@walls_desc");
    add_item("ceiling","It just hangs up there.\n");
    add_item("bed","It's small and made of iron.\n");
    add_item("floor","You notice few small scratches on the floor. "+
                "They end near bed legs.\n");
    door=clone_object(TEMPLE_DIR + "doors/celldoor1_b");
    door->move(this_object());
 
    set_alarm(1.0,0.0,reset_room);
}

string
walls_desc()
{
  if (pulled) return "There is an inscription on the one of them.\n";
  return "Every wall here is typical for dungeon style: it's strong "+
         "and rude.\n";
}
 
init()
{
 ::init();
 add_action(do_pull,"pull");
 add_action(do_push,"push");
}

int
do_push(string str)
{
  NF("Push what?\n");
  if (str!="bed") return 0;
  write("You try to push it, but with no success. Perhaps you " +
            "can pull it?\n");
  say(QCTNAME(TP) + " tries to push the bed, but with no success.\n");
  return 1;
}
 
int
do_pull(string str)
{
 int ran;
 string mes;
 
 if (str=="bed")
  {
   if (!pulled)
     {
       ran=random(3)+1;
       if (ran==1)
        { TP->add_prop("_ring_is_",ran);
          mes="northwest"; }
       if (ran==2)
        { TP->add_prop("_ring_is_",ran);
          mes="northeast"; }
       if (ran==3)
        { TP->add_prop("_ring_is_",ran);
          mes="southeast"; }
       if (ran==4)
        { TP->add_prop("_ring_is_",ran);
          mes="south"; }
       write("You pull the bed and find an inscription "+
                   "drawn on the wall!\n");
       say(QCTNAME(TP) + " pulls the bed.\n");
       pulled=1;
       add_item("inscription",("After some deciphering " +
                  "you managed to read some text: ... buried ... " +
                  "in the most " + mes + " corner of ... " +
                  "tunnel.\n"));
       return 1;
     }
   NF("Pull what?\n");
   return 0;
  }
 NF("Pull what?\n");
 return 0;
}
