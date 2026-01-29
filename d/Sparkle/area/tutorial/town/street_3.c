/*
 *  /d/Sparkle/area/tutorial/town/street_3.c
 *
 *  A road at the southern end of Greenhollow. This room
 *  teaches about mapping.
 *
 *  Created June 2005, by Cooper Sherry (Gorboth)
 *
 *  Revisions:
 *  	2020-05-07 Lucius: Report about sign not being visible but referenced.
 *  		Researching shows it was commented out but not the references.
 *  		Seems this is due to the map explosion and the magic map being
 *  		auto-given on character creation.
 *
 *  		I've gone ahead and commented out the rest of the sign+box bits.
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
// #define  TUTORIAL_CHAPTER    20  /* the chapter for the sign */

/* prototypes */
public void        create_silverdell();
/**
public int         get_map(string arg);
public void        init();
public void        hint(string arg);
**/


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("near some shops in the south of Greenhollow");
    set_long("The road which travels through Greenhollow bends here,"
      + " heading both northeast and west. This seems to be an area in"
      + " which merchants have built their businesses. Travelling"
      + " southeast will take you into the complex where you can"
      + " purchase weapons, armours, and general supplies.\n\n");

    add_road_items();
    add_outdoor_items();
    add_town_items();

    add_item( ({ "merchants", "business", "merchant", "businesses",
                 "shop", "shops", "complex", "three shops" }),
        "Three businesses rest beside the road here. To the east is"
      + " a weapon smith. To the southeast is a general store, and to"
      + " the south is an armourer.\n");
    add_item( ({ "weapon store", "weapons store", "weapon shop",
                 "weapons shop", "weapon smith", "weapons smith",
                 "smith", "east" }),
        "Just to the east of the road here, a weapon smith has set up"
      + " shop. Inside all manner of weapons are probably available for"
      + " purchase or sale. The entrance to the shop is southeast,"
      + " through the General Store.\n");
    add_item( ({ "store", "general store", "general shop", "southeast" }),
        "A general store stands to the southeast. Shops like this typically"
      + " carry general gear which is important for adventurers on their"
      + " travels. The store seems to be part of a larger complex which"
      + " includes both the weapon and armour dealers.\n");
    add_item( ({ "armourer", "armour shop", "armour store",
                 "armoury", "south" }),
        "The armourer is located to the south. In his shop you will find"
      + " protective armour to wear in your travels. The entrance to"
      + " the shop is southeast, through the General Store.\n");
/**
    add_item( ({ "box", "wooden box", "wood box", "small box",
                 "small wood box", "small wooden box" }),
        "A small wooden box is attached to the signpost. In it, you see"
      + " many old paper maps. Perhaps you should <get> one?\n");
    add_item( ({ "post", "signpost", "sign post" }),
        "The sign is mounted on a sturdy post. Attached to the signpost"
      + " is a small wooden box.\n");
    add_item( ({ "map", "maps", "paper map", "paper maps",
                 "old map", "old maps", "old paper map",
                 "old paper maps", "many old paper maps" }),
        "They are inside the box. Perhaps you should take one?\n");
**/
    prevent_attacks();
    reset_room();

    add_exit("street_4", "northeast");
    add_exit("general_store", "southeast");
    add_exit("street_1", "west");
} /* create_silverdell */


#if 0
/*
 * Function name:        get_map
 * Description  :        allow players to take a map from the box
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
get_map(string arg)
{
    object map;

    if (!strlen(arg))
    {
        return 0; /* let the mudlib handle it */
    }

    if (!parse_command(arg, ({}),
        "[the] [old] [paper] 'map' / 'maps' 'from' [the] [small]"
      + " [wooden] 'box'"))
    {
        if (parse_command(arg, ({}),
        "[the] [old] [paper] 'map' / 'maps'"))
        {
            write("The maps are inside the small wooden"
              + " box. I bet you can figure this out, but if you"
              + " need help, you can always type <hint> for"
              + " assistance.\n");
            return 1;
        }

        return 0; /* let the mudlib handle it */
    }

    if (present("_sparkle_magic_map", this_player()))
    {
        write("You've already received a copy. Type <i> to see a list of your"
          + " inventory. You can <exa map> to look at the map.\n");
        return 1;
    }

    map = clone_object("/d/Sparkle/std/obj/magic_map")->move(this_player());
    write("You take a map from the box. Aha! You've just added a new"
      + " item to your inventory. To see everything you are carrying, you"
      + " can type <i>. You can also <exa> anything you have in your"
      + " inventory.\n");

    return 1;
}
/* get_map */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(get_map, "take");
    add_action(get_map, "get");
    add_action(hint, "hint");
} /* init */


/*
 * Function name:        hint
 * Description  :        give the player a hint if they get stuck
 * Arguments    :        string - what the player typed
 * Returns      :        int 1
 */
public int
hint(string arg)
{
    write("Need a hint? No problem ... try <get map from box> and"
      + " you'll be just fine. Do yourself a favor, and be sure to"
      + " make good maps yourself!\n");

    return 1;
} /* hint */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
/*
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
*/
} /* reset_room */
#endif // No sign, no box, no hint
