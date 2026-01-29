/*
 *  /d/Sparkle/area/city/obj/tent
 *
 *  This is the tent object that players enter to get to the auction house
 *
 *  Created April 2008, by Novo 
 *
 */
#pragma strict_types

inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("tent");

    set_short("large auction tent");

    set_long("A large canvas tent has been set up here. Though not"
      + " immensely tall, the long sheets which comprise its"
      + " sides stretch out to cover much of the surrounding area."
      + " The sturdy ropes which hold it all in place look very"
      + " much fixed in place, suggesting that this is no temporary"
      + " operation.\n");

    add_item( ({ "entrance", "large entrance", "flap", "front" }),
        "The tent has a large entrance, allowing you to enter.\n");
    add_item( ({ "canvas", "sides", "top" }),
        "The brown canvas covers both the sides and top of this "+
        "large tent.\n");

    add_item( ({ "sheet", "sheets", "long sheet", "long sheets" }),
        "The sides of the tent must extend over almost a quarter of"
      + " a city block!\n");
    add_item( ({ "area", "surrounding area" }),
        "The tent has crowded this area quite considerably.\n");
    add_item( ({ "rope", "ropes", "sturdy rope", "sturdy ropes" }),
        "The ropes are tethered to large iron hooks which have been"
      + " secured to the pavement by some strange magic.\n");
    add_item( ({ "hook", "hooks", "iron hook", "iron hooks", 
                 "large hook", "large hooks", "large iron hook",
                 "large iron hooks" }),
        "The hooks look marked by many days of weather and wear."
      + " They are held fast to the pavement by some unknown"
      + " magic.\n");
    add_item( ({ "magic", "strange magic", "unknown magic",
                 "strange unknown magic" }),
        "Hmmm ... probably the work of some freelance wizard. You"
      + " can get just about anything worked out for the right"
      + " price in this town.\n");
    add_item( ({ "pavement" }),
        "No doubt there was some argument over this at one time."
      + " You can just picture the owner of the tent insisting about"
      + " boosting commerce and economy, and insisting that a few"
      + " cracks in the pavement are surely not that large an issue,"
      + " with a very unimpressed civic zoning agent of Sparkle"
      + " insisting that no harm be done to city streets. In any"
      + " case, the hooks are held by magic. No damage was done to"
      + " the pavement.\n");
    add_item( ({ "operation" }),
        "You'll have to enter the tent to learn more about that.\n");
    add_item( ({ "temporary operation" }),
        "That it isn't.\n");
        
    add_prop(OBJ_M_NO_GET, "Surely, you jest.\n");
    add_prop(OBJ_I_WEIGHT, 100000000000);
    add_prop(OBJ_I_VOLUME, 100000000000);


    setuid();
    seteuid(getuid());
} /* create_object */


public int enter(string str)
{
    notify_fail("Enter what?\n");
    
    if (!strlen(str))
    {
        return 0;
    }
    
    if (!strlen(str) ||
        !parse_command(str, ({}),
        "[a] [the] [large] [canvas] [auction] 'tent'"))
    {
        return 0;
    }
    environment()->set_dircmd("tent");
    TP->move_living("entering the auction tent", 
            ROOM_DIR + "auction_house");
    
    find_player("novo")->catch_tell(
    TP->query_real_name()+" has entered the auction.\n");
    return 1;
    
}


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(enter, "enter");
} /* init */
