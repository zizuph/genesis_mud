/*
 * Elrond's Hall
 * By Finwe, January 1998
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
 
inherit HOUSE_IN_BASE;
inherit "/d/Shire/std/room/room_tell";

object elrond;
 
void add_npcs();

void
create_house_room()
{
    set_short("The Hall of Elrond");
    set_long("You stand in the Hall of Elrond. It is where " +
        "Elrond holds meetings, counsels with travellers, and " +
        "hold banquets. The room is long; great windows on the " +
        "west wall flood the room with @@daylight_desc@@. At " +
        "one end is a dais with a great chair sitting in " +
        "the center.\n");
 
    add_item(({"paintings", "portraits"}),
        "On the wall you see paintings of all the Chieftains " +
        "of the Dunedain.\n");
    add_item("dais",
        "The platform is set at the south end of the room. It " +
        "is about knee high and upon it sits a great chair, " +
        "the seat of Elrond.\n");
    add_item(({"seat of elrond", "great seat of elrond", 
            "seat of Elrond"}),
        "The great chair is carved from an unknown wood. It is " +
        "large and almost appears to be a throne. The chair is " +
        "very solid looking yet look comfortable. It has a " +
        "high back and arm rests. The chair is polished dark. " +
        "Behind the chair, you notice a locked door.\n");
    add_item(({"door", "locked door"}),
        "The door is hidden behind the great chair. It is plain " +
        "looking with a silver doorknob set in the center of the " +
        "left end of the door. The door is locked.\n");
    add_item(({"doorknob", "silver doorknob"}),
        "The doorknob is ornate, fashioned from mithril and " +
        "polished to a lustrous shine. Between the knob and the " +
        "door is a small, golden rectangle plate.\n");
    add_item(({"golden plate", "small golden rectangle plate",
            "golden rectangle plate", "small plate", "plate",
            "small golden plate", "rectangle plate", 
            "small rectangle plate"}),
        "This plate protects the door and serves as a " +
        "decoration. The upper part of the plate is above " +
        "door. On it is a star with light emanating outwards. " +
        "On the bottom of the plate are the rays of the star " +
        "radiating out in all directions.\n");
    add_item(({"star", "radiating star"}),
        "The star has eight points and shines with a silver " +
        "radiance. It is fashioned in relief and very " +
        "lifelike, as if it was imbued with the light of " +
        "Elbereth.\n");
    add_item(({"ray", "rays"}),
        "The rays of the star radiate in all directions. " +
        "They are fashioned in relief and seem to glitter on " +
        "the surface of the plate. They look as if they shine " +
        "with the light of Elbereth.\n");
    add_item("floor",
        "You see a beautiful parquet hardwood floor. The " +
        "parquetry are dark maple and form diamond patterns, " +
        "contrasting with the light oak wood of the main floor. " +
        "Around the outside of the floor, at the " +
        "base of the walls, is a border of leaves made from " +
        "various dark woods.\n");
    add_item(({"parquetry", "dark maple", "maple"}),
        "The strips of wood are made from fine maple. The " +
        "grain is beautiful and the wood has been colored a " +
        "dark colour. It stands out beautifully against the " +
        "lighter colors of oak.\n"); 
    add_item(({"west window", "western window"}),
        "@@west@@ The mountains loom in the distance.\n");
    add_item(({"great chair", "chair"}),
        "The chair is where Elrond sits when he holds councils " +
        "or meets with people here. It is carved of fine " +
        "grained wood and dominates the room. Its warm color " +
        "contrasts nicely with the rest of the room.\n");
    add_item("dais",
        "The raised platform dominates the south end of the " +
        "room. It is made up of three tiers and holds a great " +
        "chair.\n");

    set_extra_window("@@window_position@@ set into the " +
        "west and south walls.");
    add_item(({"west windows", "western windows", "west window",
        "western windows"}), "@@west_down@@\n");
    add_item(({"south windows", "southern windows", "south window",
        "southern windows"}), "@@south_down@@\n");
 
    num_of_windows=6;
    reset_shire_room(); 
 
    add_exit(VALLEY_DIR + "d_cor03",  "north");
}
 
init()
{   
    ::init();
    add_action("go_up", "up");
    add_action("sit_down", "sit");
    add_action("open_door", "open");
    add_action("unlock_door", "unlock");
}
 
 
void
reset_shire_room()
{
    add_npcs();
}
int go_up(string str)


{
  write("You try to go up, but realize the door is locked.\n");
  SAY(" tries to sneak away.\n");
  return 1;
}
 
 
void
add_npcs()
{

    if(!objectp(elrond))
    {
        elrond = clone_object(RNPC_DIR + "elrond");
        elrond->set_restrain_path(({"/d/Shire/rivendell/room/valley",
                                    "/d/Shire/rivendell/room/forest"}));
        elrond->set_random_move(2);
        elrond->set_monster_home("/d/Shire/rivendell/room/valley/elrond_hall");
        elrond->move(TO);
    }
}

 
int sit_down(string str)
{
 
    switch(str)
    {
        case "down on throne": case "down on great chair":
        {
            write("You can't sit in Elrond's great chair. He " +
                "allows no one but himself to sit there.\n");
            say (QCTNAME(TP) + " tries to sit down in Elrond's " +
                "chair. Suddenly, " + HE_SHE(TP) + " realizes the " +
                "folly of " + HIS_HER(TP) + " action.\n");
            return 1;
            break;
        }
        default:  
        {
            write("Sit down on what, perhaps the great chair?\n");
            say(QCTNAME(TP) + " tries to sit down but falls on " 
                + HIS_HER(TP) + " bottom. " + CAP(HE_SHE(TP)) + 
                " stands up and dusts " + HIM_HER(TP) + 
                "self off.\n"); 
            return 1;
            break;
        }
    return 0;
    }
}
        

int open_door(string str)
{
    if (str == "door")
    {
        write("You can't do that. The door is locked.\n");
        say(QCTNAME(TP) + " tries to open Elrond's door, " +
            "but just rattles it instead.\n");
            return 1;
     }
}
 
int unlock_door(string str)
{
     {
        write("You can't do that. You don't have the key.\n");
        say(QCTPNAME(TP) + " tries to unlock Elrond's door, " +
            "but doesn't have a key.\n");
        return 1;
     }
/*
        {
            write( str + " what? You don't have a key and the " +
                "door is securely locked.\n");
            say(QCTPNAME(TP) + "tries to open a door but is " +
                "unsuccessful.\n");
            return 1;
            break;
        }
*/
    return 0;
}
