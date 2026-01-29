#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
inherit MITHAS_OUT;

#define HAS_FIXED_SECOND_STATUE   "_i_fixed_second_statue_ansalon"

object statue;

void 
reset_mithas_room()
{
   if(!objectp(statue))
   {
      statue = clone_object(MOBJ + "statue2");
      statue->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("At the gates to the Imperial Castle");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road53","east",0);
    add_exit(MROOM + "road52","west",0);
    add_exit(MROOM + "road60","north","@@enter_castle");   

    add_search(("statue"),8,"search_statue", 1);
    add_cmd_item(({"left horn"}),"attach","@@attach");
   
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+
   "You are standing next to a huge iron gate in the city of Nethosak. "+ 
   "The street looks very crowded, and both the minotaur citizen and the "+
   "guards wander in a steady stream into the castle. Some tall minotaurs "+
   "stand guard next to the gate and protects the castle from outsiders "+
   "and other troublemakers. The road continues to the north through the "+
   "gate and towards the castle and to the east and west. "+
   season_descr()+ "\n";

}

int
enter_castle()
{
    write("As you are about to enter the Imperial Castle, one of "+
          "the guards that stands next to the gate, stops you and "+
          "says: You don't look like a minotaur citizen nor a guard.\n"+
          "The minotaur guard point to the south.\n"+
          "You walk back to the main road.\n");
    return 1;
}


void
calculate_experience(object who)
{
    int xp_base = 15000;

    if(who->test_bit("ansalon", 0, 18))
    {
        this_player()->catch_msg("The statue comes alive and says: Are you trying "+
                                 "to cheat! You've already done this quest!\n"+
                                 "The statue hits you in the head with his "+
                                 "huge fist.\n");
        return;
    }

    if (this_player()->query_prop("_i_fixed_first_statue_ansalon")  &&
        this_player()->query_prop("_i_fixed_second_statue_ansalon") &&
        this_player()->query_prop("_i_fixed_third_statue_ansalon") &&
        this_player()->query_prop("_i_fixed_fourth_statue_ansalon"))
    {
        this_player()->catch_msg("Suddenly the statue comes alive!\n"+
          "The statue stares at you with cold eyes and says: Thank you mortal "+
          "you have restored us to our former glory and for that I'll reward you.\n"+
          "The statue touches you with it's hand, and suddenly you feel much more "+
          "experienced!\n");
        if(who->query_wiz_level())
        {
            who->catch_msg("xp : " + xp_base + "\n");
        }

        who->add_exp(xp_base, 0);
        who->set_bit(0, 18);
    }
    else if ((!this_player()->query_prop("_i_fixed_first_statue_ansalon"))  ||
        (!this_player()->query_prop("_i_fixed_second_statue_ansalon")) ||
        (!this_player()->query_prop("_i_fixed_third_statue_ansalon")) ||
        (!this_player()->query_prop("_i_fixed_fourth_statue_ansalon")))
    {
        TO->command("say But you have not repaired all the statues!.");
        return;
    }
    //A_QUEST_LOG("quest","Statue quest", who, xp_base);
    return;
}

int
attach()
{
    if (!this_player()->query_prop(HAS_SEARCHED_SECOND_STATUE))
    {
        write("Why would you want to attach something on a prefect statue?\n");
        return 1;
    }
    if (this_player()->query_prop(HAS_FIXED_SECOND_STATUE))
    {
        write("You have already fixed this statue.\n");
        return 1;
    }
    if(!P("left horn",this_player()))
    {
        write("You have nothing to attach on the statue!\n");
        return 1;
    }

    write("You carefully attach the left horn on the stone statue, "+
          "amazingly the horn fits perfectly.\n");
    P("left horn",this_player())->remove_object();
    this_player()->add_prop(HAS_FIXED_SECOND_STATUE, 4);
    calculate_experience(this_player());
    return 1;
}