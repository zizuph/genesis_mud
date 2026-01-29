inherit "/d/Gondor/lebennin/sroad/sroad.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

mapping	camp_enter = ([]);
int	test_west_exit();

void
create_road()
{
    set_extraline("The road is running along the west bank of "
     + "the mighty river Anduin. To the northeast the walls of "
     + "Pelargir upon Anduin "
     + "can be seen. The city cannot be very far from here.");

    add_exit(LEB_DIR + "sroad/sr2", "northeast", 0, 2);
    add_exit("/d/Gondor/lebennin/sroad/sr4", "southwest", 0, 0);
//    add_exit("/d/Gondor/clubs/nisse/room/entrance", "west", test_west_exit, 0,
//        test_west_exit);

    add_item(({"city","pelargir"}), BSN(
       "Pelargir upon Anduin, second largest city of Gondor and the "
     + "largest harbour of the realm is not far from here to the "
     + "northeast. The road will lead you to the city gates."));

//    add_prop(OBJ_S_SEARCH_FUN, "reveal_camp");
//    add_prop(OBJ_I_SEARCH_TIME, 1);
         
    add_anduin();
}

int
test_west_exit()
{
    if (!camp_enter[TP->query_real_name()] && !TP->query_wiz_level())
    {
        TP->catch_msg("There is no obvious exit west.\n");
        return 1;
    }
    
    return 0;
}

string
reveal_camp(object tp, string str)
{
    object player = this_player();

    if (str == "road")
    {
        camp_enter[TP->query_real_name()] = 1;
        return "You find a hidden exit that leads to the west.\n";
    }

    return 0;
}

int
block_exit()
{
   if (TP->query_wiz_level())
   {
      write("The road south is still closed for mortals!\n\n");
      return 0;
   }

   write("The road southwest is closed by order of the Steward of Gondor.\n");
   return 1;
}
