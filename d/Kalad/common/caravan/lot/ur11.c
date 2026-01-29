#include "../default.h"
inherit CVAN_ROOM;
object ob1, ob2, ob3;
public void
reset_room()
{
    if (!ob1)
    {
        ob1 = clone_object(NPC + "sknight");
        ob1->move(this_object(), 1);        
    }
    if (!ob2)
    {
        ob2 = clone_object(NPC + "ktinvgrd");
        ob2->move(this_object(), 1);
    }
    if (!ob3)
    {
        ob3 = clone_object(NPC + "ktinvgrd");
        ob3->move(this_object(), 1);
    }
    ob1->team_join(ob2);
    ob1->team_join(ob3);
}
void
create_cvan_room()
{


    add_prop(ROOM_I_INSIDE, 1);

    set_short("A magnificent altar room");
    set_long("You are within a magnificent altar room.\n"+
      "This large room is quite impressive. Although built underground, the "+
      "sheer size of it gives the illusion that it reaches into the very "+
      "heavens themselves. This room, unlike most others here, is made "+
      "entirely of red-veined marble, giving the impression that blood has "+
      "been stained upon the walls. Dominating the room is a grand altar, "+
      "located on the far east wall. A lit passage leads west.\n");

    add_item(({ "marble" }),
      "Smooth, and ice-cold to the touch, it gives this entire room the "+
      "appearance of having been the battleground for a bloody fight, in "+
      "which all sides lost.\n");

    add_item(({"altar", "small bier", "bier"}),
      "A small bier is visible, upon which offerings had been made to the god "
      +"of these knights. Towering behind the bier is a massive statue, "
      +"rising nearly to the ceiling. It appears this Altar is not used "
      +"any longer. Perhaps the order has moved.\n");
    
    add_item(({"statue"}),
      "The figure portrayed looks at first to be an elf. However, after "+
      "gazing more intently at the face, you can see that assumption was "+
      "incorrect.\n");

    add_item(({ "face" }),
      "It looks like the features of both an elf and some monstrosity from "+
      "the outer planes, combined into one grotesque parody of a face.\n");

    add_item(({ "walls" }),
      "Set within small depressions around the room are several torches, "+
      "providing an eerie illumination.\n");

    clone_object(CVAN + "door/urdoor2")->move(TO);
    clone_object(CVAN + "door/urdoor4")->move(TO);

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur9", "west");

    reset_room();
}

/*To set the "place offering" as an exit.

int
do_offering(string str)
{
    if (member_array(str, ({"offering", "offering on altar", "an offering",
    "an offering on altar"})) == -1)

    {
        notify_fail("Make/place an offering perhaps?\n");
        return 0;
    }

    write("You place an offering upon the altar and suddenly "+
       "feel ble.\n");
     say(QCTNAME(this_player())+" places an offering upon "+
       "the altar and disappears within it.\n");

    this_player()->move_living("M", "/d/Raumdor/guilds/thanar/room/entrance", 1, 0);

    say(QCTNAME(this_player())+" suddenly appears.\n");
    return 1;
}
void
init()
{
    ::init();
    add_action(do_offering, "place");
    add_action(do_offering, "make");
}*/