#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define HAS_FIXED_THIRD_STATUE   "_i_fixed_third_statue_ansalon"

inherit MITHAS_OUT;

object statue;
object citizen;
object citizen2;

void 
reset_mithas_room()
{
    if(!objectp(citizen))
    {
      citizen = clone_object(MNPC + "citizen");
      citizen->move(this_object());
   }
   if(!objectp(citizen2))
   {
      citizen2 = clone_object(MNPC + "citizen");
      citizen2->move(this_object());
   }
   if(!objectp(statue))
   {
      statue = clone_object(MOBJ + "statue3");
      statue->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Intersection in Nethosak");
    set_long("@@long_descr"); 
    
    add_item(({"forest"}), "The forest lies to the "+
          "east and it looks like it continues "+
          "southwards.\n");
    
    add_exit(MROOM + "road69","north",0);
    add_exit(MROOM + "road18","south",0);
    add_exit(MROOM + "road14","west",0);
    add_exit(MROOM + "road16","east",0);

    add_search(("statue"),8,"search_statue", 1);
    add_cmd_item(({"right horn"}),"attach","@@attach");
    
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing at an intersection "+
          "in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. A fresh "+
          "breeze blows in from the forest, making you feel "+
          "relieved. The road continues to north, south, east "+
          "and west. The road to the west takes you towards "+
          "the center of the city while going eastwards leads "+
          "into a small forest. " +season_descr()+ "\n";

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
    if (!this_player()->query_prop(HAS_SEARCHED_THIRD_STATUE))
    {
        write("Why would you want to attach something on a prefect statue?\n");
        return 1;
    }
    if (this_player()->query_prop(HAS_FIXED_THIRD_STATUE))
    {
        write("You have already fixed this statue.\n");
        return 1;
    }
    if(!P("right horn",this_player()))
    {
        write("You have nothing to attach on the statue!\n");
        return 1;
    }

    write("You carefully attach the right horn on the bronze statue, "+
          "amazingly the horn fits perfectly.\n");
    P("right horn",this_player())->remove_object();
    this_player()->add_prop(HAS_FIXED_THIRD_STATUE, 4);
    calculate_experience(this_player());
    return 1;
}

