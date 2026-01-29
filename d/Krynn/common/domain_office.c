/*
 * The entrance to Krynn from the domain tower
 */
#include <stdproperties.h>
#include <std.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Genesis/start/human/town/tower.h"
#include "/d/Krynn/common/warfare/warfare.h" 

#define MASTER "/d/Krynn/common/obj/krynn_disc"

inherit TOWER_OFFICE;
inherit WARFARE_MAP;

void
load_board()
{
    object bb = clone_object(MASTER);
    bb->move(TO);
}

void
create_tower_office()
{
    set_short("The Land of Krynn");
    set_long("You are standing on what appears to be the back " +
         "of a huge dragon! " +
         "From here you have a splendid view across all " +
         "of Krynn. You can see a lot of tiny spots down " +
         "there, Players enjoying the areas, battling the " +
         "evil Dragonarmies, and a few Wizards, who put " +
         "all their effort into expanding the world of " +
         "Krynn and making it an interesting place to be. " +
         "On one of the clouds next to you, someone has " +
         "affixed a sign. Far below you can see a raging battlefield, " +
         "of which you can examine for more detail.\n");
    add_item(({"sign","small sign"}),
         "Hanging from a cloud is a small sign. Perhaps " +
         "you should read it?\n");
    add_cmd_item(({"small sign","sign"}),"read","@@sign");
    add_item(({"cloud","clouds","wall","walls","ceiling"}),
         "Someone has beautifully painted these clouds onto the " +
         "walls and on the ceiling around you, and it looks " +
         "very real.\n");
    add_item(({"floor","dragon"}),
         "The floor under you looks just like a dragon's back. " +
         "You feel like you're soaring through the skies.\n");
    add_item(({"view"}),
         "You look down from the dragon and see landscape " +
         "between the clouds. Someone has painted all this very " +
         "realistically onto the floor, walls and ceiling.\n");
    add_item(({"battlefield", "raging battlefield"}), "You look down " +
         "from the back of the huge dragon at the armies battling each " +
         "other for control of Krynn!\n" +exa_warmap()); 

   reset_room(); // Lets get the board and so

    set_project_path("/d/Krynn/open/project/");
    add_tower_link("tower");


    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");
}

void
reset_room()
{
    object quest_orb;
    seteuid(getuid(this_object()));

    /*
     * This may seem like a strange construct, but I want the master object
     * to be in this room and this construct works, so let it be.
     */
    MASTER->teleledmingsanka();
    find_object(MASTER)->move(this_object(), 1);

    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Krynn");
        quest_orb->set_extra_line("The dark crystal orb is floating" +
                                 " before you, seemingly on the wind.");
        quest_orb->move(this_object(), 1);
    }    
}

string
sign()
{
    return "Upon the small sign you read:\n\n" +
    "wizards : Lists the wizards of the domain of Krynn.\n" +
    "projects <domain/wizard> : The projects of the domain/wizard.\n\n";
}

