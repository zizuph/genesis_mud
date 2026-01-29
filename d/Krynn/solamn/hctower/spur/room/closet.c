// don't forget to add door
// closet
// grace apr 1995

#include "../local.h"
inherit SPURRM;
#include <ss_types.h>
#define PASS ("/d/Krynn/solamn/hctower/spur/room/2hp1")

static int door_opened = 0;
static int tclose_alarm_id = 0;
void reset_spur_room();

void 
create_spur_room()
{

   SHORT("Inside the closet");
   LONG("This is a simple broom-closet, the walls of which "+
      "are made entirely of sweet-smelling pine. It seems "+
      "to be the place where all the cleaning supplies are "+
      "kept.\n");
   
    clone_object(SOBJ + "closet_b")->move(TO);

   AI("interior", "It is fragrant with the scent of pine.\n");
   ACI(({"air","fragrance", "scent"}), "smell", 
        "It smells strongly of sweet-pine sap.\n");
   AI(({"wall", "walls", "plane", "planes"}), 
        "A cursory examination shows that the walls are each "+
        "made from solid planes of wood that have been sanded "+
        "and lightly rubbed with oil.\n");

   add_search("wall", 3, "find_hp", 1);
   add_search("walls", 3, "find_hp", 1);
   add_search("backwall", 3, "find_hp", 1);
 
   DARK;
}

init()
{
    ::init();
    ADD("feel_me_up", "feel");
    ADD("feel_me_up", "touch");
}

  
mixed
find_hp(object searcher, string what)
{
        NF("The door is already opened.\n");
        if (door_opened)
          return 0;

        if (searcher->query_skill(SS_AWARENESS) > 25)
           {
              say(QCTNAME(searcher) + " discovers something unusual "+
                "about the back wall.\n");
              set_alarm(2.0, 0.0, "pass_found");  
              return "Your skilled fingers cause the back wall to "+
                "move.\n";

            }
        return 0;
}

void
pass_found()
{
    tell_room(TO, "With a puff of pine-scented air, the back wall " +
             "swings away, revealing a hidden passage.\n");
    door_opened = 1;
    tclose_alarm_id = set_alarm (20.0, 0.0, "pass_close", this_object);
    add_exit(PASS, "north", 0);
    call_other(PASS, "pass_up"); 
}   

void
pass_open()
{
    tell_room(TO, "With a puff of pine-scented air, the back wall " +
             "swings away, revealing a hidden passage.\n");
    door_opened = 1;
    tclose_alarm_id = set_alarm (20.0, 0.0, "pass_close", this_object);
    add_exit(PASS, "north", 0);
}   

void
pass_close()
{
   if (tclose_alarm_id)
     {
       remove_alarm (tclose_alarm_id);
       tclose_alarm_id = 0;
     }
   tell_room(PASS, "The wood swings quickly back into place, blocking the "+
             "archway once again.\n");

   door_opened = 0;
   remove_exit("north");
}


int
feel_me_up(string str)
{
    NF("Feel what?\n");
    if ((str == "wall") || (str == "walls") || (str == "back wall"))
       {  
           write("It feels very smooth and hard. There is something "+
                   "different about the back wall...perhaps you "+
                   "should examine it more thoroughly?\n");
           return 1;
        }
     if ((str == "me") || (str == "myself"))
        {
            write("Wow! That feels g-o-o-o-o-d!\n");
            say(QCTNAME(TP) + " seems to be playing with " 
                  + TP->query_objective() + "self in the closet.\n");
            return 1;
       }
   return 0;
}

void 
reset_spur_room()
{
   door_opened = 0;
   tclose_alarm_id = 0;
   remove_exit("north");
}
