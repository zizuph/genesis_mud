//-*-C++-*-
// file name:      outside.c
// creator(s):     Lilith June 2008
// last update:    Lilith Jan 2022: updated up exit to allow any player
//                    since Terel vamps no longer exist.
//                    This restablishes the circle connection between this area,
//                    and the forest, moors, etc -- and the mountain top.
// note: 
// bug(s):
// to-do:  add ability to climb avalanche as a back way out

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

public void create_vamp_room()
{

    set_short("yard buried by an avalanche");
    set_long("Outside an abandoned old mansion, standing in what remains "+
        "of a semi-circular yard that has been buried in rubble and snow. "+
        "The structure is of an ancient domus design that is quite inappro"+
        "priate to the current climate. Much of it has crumbled to ruins, "+
        "though part of the portico and some of the structure are intact. "+
        "To the northwest you can see a lake or pond, and the sheer walls "+
        "of a mountainside beyond. North is a door and a chimney, all "+
        "that can be seen of a building that is completely covered by a "+
        "rockslide. East is a grand little building made of granite, the "+
        "only structure on the property that appears to be undamaged by "+
        "time or the elements. There is a mosaic panel over the steps to "+
        "its entrance.\n");

    add_item(({"first building", "buried building", "north building", 
        "workshop", "shop"}), 
        "It is so buried under the rockslide that it is difficult "+
        "to determine the original size and shape of this building. "+
        "All that remains visible is a chimney and a door.\n");
    add_item(({"second building", "granite building", "grand building",
        "east building", "little building", "grand little building", 
        "mausoleum", "burial vault"}),
        "This grand little structure looks like it is a mausoleum or "+
        "burial vault intended to store the remains of the once "+
        "illustrious owners of the abandoned old mansion.\n");
    add_item(({"water", "lake", "pond"}), 
        "It is dark and choppy, and ringed with stones that have fallen "+
        "from the side of the mountain above it. It looks very cold, so "+
        "cold that it is unlikely anyone could survive in it for long.\n");
    add_item(({"chimney"}), 
        "It is a rather large chimney. It pokes up out of the rubble "+
        "like an accusing finger.\n");
    add_item(({"entrance", "steps", "doorway", "open doorway", 
        "open entryway", "entryway"}), 
        "There are steps leading up to the entrance of the little "+
        "granite building, which has no door.\n");
    add_item(({"mountain", "mountainside", "sheer walls", "avalanche", 
        "rockslide"}), 
        "The mountain appears to have lost a large portion of this side. "+
        "The area near the lake sports a sheer drop, whereas the area "+
        "near the mansion is concave and riddled with rubble and scree.\n");
    add_item(({"rubble", "rocks", "rock", "debris", "stones", "scree", "shale"}),
        "The remains of an avalanche that swept down the mountain and "+
        "devastated this holding.\n");
    add_item(({"snow", "ice"}),
        "Snow and ice are ever-present in this place. Watch your step.\n");
    add_item(({"panel", "mosaic", "mosaic panel"}),
        "This mosaic panel must have been quite vivid when it was first "+
        "put in place. Now it is faded and chipped, but for all that, it "+
        "plainly depicts two dragons with outstretched wings sheltering "+
        "the words:\n"+
        "        TIMAEUS   AVENCHIRIS   CALATHINI\n");
    add_item(({"domus", "structure", "ancient domus", "mansion"}),
        "A two-level mud-brick and plaster structure that seems to have "+
        "been built in a time when the weather was much warmer. The high "+
        "portico looks like it once went all the way around the mansion "+
        "but most of it lies in ruins. This place does not appear to "+
        "have been maintained in a long, long time.\n");
    add_item(({"ruins", "portico", "porch"}),
        "All that remains of a colonnaded portico that once surrounded "+
        "the building and extended toward the outlying buildings is a "+
        "small area still standing at the front of the mansion.\n");
    add_item(({"outlying buildings", "buildings" }),
        "There are two outlying buildings. One lies north, buried "+
        "under a pile of rubble, with only a door and a chimney visible. "+
        "The second lies east, a grand little granite structure with "+
        "and open entryway.\n");
    add_item(({"door", "buried door"}),
        "The door is partly ajar, wedged open by stones that also "+
        "prevent it from being closed entirely.\n");
    add_cmd_item(({"door", "buried door"}), ({"open", "unlock"}),
        "The door is already partly ajar and cannot be opened "+
        "any further due to the debris piled around it.\n");
    add_cmd_item(({"door", "buried door"}), ({"close", "lock"}),
        "The door is already partly shut and cannot be closed "+
        "any further due to the debris piled around it.\n");
    add_cmd_item(({"debris", "rocks", "stones"}), ({"move", "shift"}),
        "You begin moving some rocks around but soon stop when you "+
        "realize the futility of your efforts.\n");
    add_cmd_item(({"chimney"}), ({"climb", "enter"}),
        "You try to reach the chimney so you can climb it, but the "+
        "stones underfoot are so loose you cannot get purchase.\n");
  
    add_exit("porch",      "west"); 
    add_exit("mausoleum",  "east");
    add_exit("water_room", "northwest", 0, 1, 1); // invis exit
    add_exit("workshop",   "north", 0, 1, 1);  // invis exit 
    

    add_prop(ROOM_I_LIGHT,1);
    remove_prop(ROOM_I_INSIDE);
    
}

public int enter(string str)
{
    notify_fail("Enter what?\n");
    
    if (!strlen(str))
    {
        return 0;
    }
 
    if (parse_command(str,({})," [the] [granite] 'mausoleum' / 'crypt' / 'tomb' / "+
        "'building'"))
    {
        TP->move_living("into the granite building",
            ROOM_DIR+"mausoleum");
        return 1;
    }
    if (parse_command(str,({})," [the] [buried] 'workshop' / 'shed' / 'building' / "+
       "'shop'"))
    {
        TP->move_living("into the buried building",
            ROOM_DIR+"workshop");
        return 1;
    }

    if (parse_command(str,({})," [the] 'water' / 'lake' / 'pond'"))
    {
        TP->move_living("into the lake",
            ROOM_DIR+"water_room");
        return 1;
    }
    
    return 0;
}


int do_up(string str)
{
    notify_fail("What?\n");
    
    if (!strlen(str))
    {
        return 0;
    }

    if (parse_command(str,({})," [up] [the] 'avalanche' / 'rocks' / 'rockslide'"))
    {
/*        if (IS_VAMP(TP) || IS_BG(TP)) 
        {
            write("You try climbing over and through the avalanche. The stones "+
                "are so loose that you keep sliding backwards.\n\n");
            TP->move_living("up into the avalanche", ROOM_DIR +"avalanche1");
            return 1;
        }
*/	    
        if (TP->query_skill(SS_CLIMB) > 25)
        {
            write("You try climbing over and through the avalanche. The stones "+
                "are so loose that you keep sliding backwards.\n\n");
            TP->move_living("up into the avalanche", ROOM_DIR +"avalanche1");
            return 1;
        }
			
        write("You try climbing over and through the avalanche. The stones "+
            "are so loose that you keep sliding backwards.\n\n");
        say(QCTNAME(TP) +" tries to climb the avalanche, but only "+
            "succeeds in scattering a bunch of rocks and shale.\n");
        return 1;
    }
    
    return 0;
}

public void init()
{
    ::init();
    
    add_action(enter,"enter");
    add_action(do_up, "climb");
}