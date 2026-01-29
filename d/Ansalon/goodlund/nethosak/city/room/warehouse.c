#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit MITHAS_IN;

#define HAS_SEARCHED   "_I_searched_warehouse_floor"

void
create_mithas_room()
{
   set_short("Old warehouse");
   set_long("@@long_descr");

   add_exit(MROOM + "pier5","west","@@house_exit",0); 
   add_invis_exit(MROOM + "sea1","down","@@only_if_searched");

   add_search(({"floor","warehouse"}),10,"search_floor", 1);

   add_item(("floor"),"As you examine the floor boards closely, you "+
              "notice that they have been made out of oak wood, and even "+
              "though they are extremely old, they look quite sturdy.\n");

    add_item(("crates"), "The wooden crates have been looted years ago, "+
             "and you don't manage to find anything useable in any of them.\n");

    add_item(("trunks"), "The trunks have all been opened, and they are now "+
            "lying scattered all over the floor.\n");

    add_item(("mouse"), "With your keen eyes, you manage to see a small grey "+
          "mouse in the corner of the warehouse, it disappears quickly under "+
          "a loose floorboard.\n");

    add_item(("rat"), "You see a thick black rat slowly moving along the "+
          "northern wall of the warehouse, as it spots you it quickly disappears "+
          "under some crates.\n");

}

string
long_descr()
{ 
   return "This is a small wooden shack that is being used "+
          "as a warehouse for different goods, "+
          "before shipping them on some ships. The floor is "+
          "filled with crates and trunks, and sometimes you "+
          "manage to spot a big mouse or small rat running between "+
          "them. The exit to the west takes you back to the pier.\n";
}

int
house_exit()
{
   write("You leave the old warehouse.\n");
   return 0;
}

string
search_floor(object searcher, string what)
{
    if (this_player()->query_prop(HAS_SEARCHED))
    {
	return ("Your search reveals nothing special.\n");
    }
    if (!this_player()->query_prop(HAS_SEARCHED))
    {
	this_player()->add_prop(HAS_SEARCHED, 3);
	return ("After having searched the floor of the "+
                "warehouse carefully, you notice that "+
                "some of the floor boards are loose and "+
                "you might be able to go down through "+
                "them.\n");
    }
  return 0;
}

only_if_searched()
{
    if (this_player()->query_guild_name_lay() == "Pirate of the Bloodsea")
    {
      write("You leave through the loose floor boards.\n");
      say(QCTNAME(this_player()) + " moves some floor boards, and leaves down.\n");
      return 0;
    }

    if (this_player()->query_prop(HAS_SEARCHED))
    {
      write("You leave through the loose floor boards.\n");
      say(QCTNAME(this_player()) + " moves some floor boards, and leaves down.\n");
      return 0;
    }
    write("There is no obvious exit down.\n");
    return 1;
}