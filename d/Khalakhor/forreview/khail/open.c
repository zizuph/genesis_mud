/*
 * base.c
 *
 * This file is the base room for the caverns beneath
 * the ruins of Castle Chimera.
 * It controls herbs available in each room, presence
 * of undead npc's, exit blocking, add_items in each
 * room, etc.
 * 
 * Khail - Feb 24/97
 */
#pragma strict_types

#include "defs.h"
#include <composite.h>

#define COMP_WORDS(x)  COMPOSITE_WORDS(x)
#define CAVE_HAS_WATER "_cave_has_water"
#define CAVE_IS_TUNNEL "_cave_is_tunnel"
#define CAVE_IS_CAVERN "_cave_is_cavern"

inherit STDROOM;
inherit HERBMASTER;

string pre_extra,
       post_extra,
       main;
string *dir_up,
       *dir_down,
       *dir_level;

public void reincarnate_corpse(object ob);

/*
 * Function name: reset_warriors
 * Description  : Attempts to reset any skeletal warriors
 *                that should be in this room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_warriors()
{
    int room;
    int undead;
    string foo;
    int i;
    object ob;
    object *uarr;

  /* Get the room number from the filename. */
    sscanf(file_name(TO), CAVERNS + "cav%d", room);

    if (!room)
        return;

    switch(room)
    {
      /* Place on skeletal warrior in these rooms. */
        case 3:
        case 6:
        case 7:
        case 8:
        case 18:
        case 25:
        case 28:
        case 30:
            undead = 1;
            break;

      /* Place 2 skeletal warriors in these rooms. */
        case 9:
        case 10:
        case 14:
        case 15:
        case 26:
        case 29:
        case 32:
            undead = 2;
            break;

      /* Place 3 skeletal warriors in these rooms. */
        case 5:
        case 21:
        case 33:
        case 34:
            undead = 3;
            break;

      /* Place 4 skeletal warriors in these rooms. */
        case 36:
            undead = 4;
            break;

      /* Place 5 skeletal warriors in these rooms. */
        case 12:
            undead = 5;
            break;

      /* No skeletal warriors in any unlisted rooms. */
        default:
        undead = 0;
    }
   
  /* Get a list of all skeletal warriors in this room. */
    uarr = filter(all_inventory(TO), &->id(SKELETAL_WARRIOR));

  /* If the number is less than should be here, replace as */
  /* necessary. */
    for (i = undead; i > sizeof(uarr); i--)
    {
        ob = clone_object(NPC + "ske_war");
        ob->arm_me();
        ob->move(TO);
    }
}

/*
 * Function name: reset_knights
 * Description  : Resets any death knights that are supposed to be
 *                in the room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_knights()
{
    int room;
    int undead;
    string foo;
    int i;
    object ob;
    object *uarr;

  /* Extract the room number from the filename. */
    sscanf(file_name(TO), CAVERNS + "cav%d", room);

    if (!room)
        return;

    switch(room)
    {
      /* These rooms contain 1 death knight. */
        case 12:
        case 29:
        case 33:
        case 36:
            undead = 1;
            break;
   
      /* No death knights in any other rooms. */
        default:
        undead = 0;
    }

  /* Get any death knights present in the room. */   
    uarr = filter(all_inventory(TO), &->id(DEATH_KNIGHT));

  /* Fill in knights as required. */
    for (i = undead; i > sizeof(uarr); i--)
    {
        ob = clone_object(NPC + "death_knight");
        ob->arm_me();
        ob->move(TO);
    }
}

/*
 * Function name: reset_lord
 * Description  : Resets the death lord in the appropriate room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_lord()
{
    object ob;
   
  /* There is only 1 death lord in 1 room of the caverns, so */
  /* the switch used with the warriors and knights is not */
  /* needed here. Simply see if a death lord is in the one */
  /* room he's supposed to be in. If not, put him there. */
    if (file_name(TO) == CAVERNS + "cav37" &&
        !present(DEATH_LORD, TO))
    {
        ob = clone_object(NPC + "death_lord");
        ob->arm_me();
        ob->move(TO);
    }
}

/*
 * Function name: reset_nasties
 * Description  : Resets the various 'nasty' npc's that are
 *                mainly here for looks, like the millepede and
 *                slimes.
 * Arguments    : count - Integer representing the number of times
 *                        reset_nasties has 'looped'.
 * Returns      : n/a
 */
public void
reset_nasties(int count)
{
    object ob;

    reset_euid();

  /* Only add a 'nasty' 50% of the time. */
    if (!random(count))
    {
      /* Randomly select one of three npc's to clone. */
        switch(random(3))
        {
            case 0:
                if (present("snake", TO))
                    break;
                ob = clone_object(NPC + "snake");
                tell_room(TO, capitalize(LANG_ADDART(ob->short())) +
                    " slithers into the room.\n");
                ob->move(TO);
                break;
            case 1:
                if (present("millepede", TO))
                    break;
                ob = clone_object(NPC + "millepede");
                tell_room(TO, capitalize(LANG_ADDART(ob->short())) +
                    " scuttles out of the shadows.\n");
                ob->move(TO);
                break;
            default:
                if (present("slime", TO))
                    break;
                ob = clone_object(NPC + "slime");
                tell_room(TO, capitalize(LANG_ADDART(ob->short())) +
                    " oozes out of a crack in the wall.\n");
                ob->move(TO);
        }
        if (!ob)
            return;
      /* Call this function again. This means that every time an */
      /* npc is cloned here, there's a 50% chance of a second, if */
      /* that's successful, a 50% chance of a third, etc. */
        set_alarm(0.0, 0.0, &reset_nasties(count + 1));
    }
}

/*
 * Function name: reset_room
 * Description  : What to do when the room is reset every half hour
 *                or so.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    reset_warriors();
    reset_knights();
    reset_lord();
    reset_nasties(10);
    set_searched(random(2));
    ::reset_room();
}

/*
 * Function name: block_exit
 * Description  : VBFC exit blocking function. This function
 *                tries to find any eldoral undead npc's in the
 *                room. If none are found, player is allowed
 *                through. If npc's are found, it loops though
 *                all those found, each having a chance to block
 *                the player. If none block, player gets through.
 * Arguments    : n/a
 * Returns      : 0 - Player may pass.
 *                1 - Exit blocked.
 */
public int
block_exit()
{
    object *arr;
    int i;

  /* Don't bother trying to block npc's */
    if (!interactive(TP))
        return 0;

  /* Get an array 'arr' of all skeletal warriors or death */
  /* knights in the room. */
    arr = filter(all_inventory(TO), &->id(SKELETAL_WARRIOR));
    arr += filter(all_inventory(TO)-arr, &->id(DEATH_KNIGHT));
    arr += filter(all_inventory(TO)-arr, &->id(DEATH_LORD));

  /* If we didn't find any warriors or knights, let player */
  /* pass. */
    if (!sizeof(arr))
        return 0;

  /* Give each warrior or death knight a chance to block. The */
  /* function to test is defined in them. */
    for (i = 0; i < sizeof(arr); i++)
    {
      /* If the current npc managed to block, break looping. */
        if (arr[i]->try_to_block(TP))
            break;
    }

  /* If 'i' equals the sizeof arr, then no npc's managed to */
  /* block, so return 0. If 'i' is less than the sizeof arr, */
  /* an npc blocked, so return 1. Note that blocking messages */
  /* are delivered by the try_to_block() fun in the npc's. */
    if (i == sizeof(arr))
        return 0;
    else
        return 1;
}

/*
 * Function name: create_cavern
 * Description  : Turns the room into a cavern.
 * Arguments    : mode - Integer representing what type of cavern to
 *                       turn this room into. Mode 1 = a small cavern.
 *                       Mode 2 = an average cavern. Mode 3 = a large
 *                       cavern. Mode 4 = a man-made cavern.
 * Returns      : n/a
 */
public void
create_cavern(int mode)
{
  /* All caverns have skullcap and angeltear by default. */
    add_herb_file(HERBPATH + "skullcap");
    add_herb_file(HERBPATH + "angeltear");

  /* Do nothing more if 'mode' not specified. */
    if (!mode)
        return;

    if (!main)
        main = "";

  /* Mode-customized room contents/description. */
    switch(mode)
    {
        add_prop(CAVE_IS_CAVERN, 1);
        case 1:
            set_short("a small cavern");
            main += "You are in a small cavern, a seemingly natural " +
                "formation which has turned the tunnels through " +
                "this place into a small room of sorts, cold and " +
                "wet as it is. ";
            add_item(({"walls", "wall"}),
                "The walls of this chamber appear to have been " +
                "formed naturally. They've been worn smooth, but their " +
                "surfaces are uneven, almost random in texture.\n");
            add_item(({"ceiling", "roof"}),
                "The ceiling of this chamber is high, but not high " +
                "enough to aleviate the nagging concern of its " +
                "stability.\n");
            add_item(({"floor", "ground"}),
                "Beneath you, smooth but uneven grey stone serves " +
                "as a floor for the cavern.\n");
            break;
        case 2:
            set_short("a cavern");
            main += "You've entered a respectable sized cavern " +
                "of some sort, which would seem to be a natural " +
                "formation judging from the rough uneveness in the " +
                "surfaces of the room. Its a refreshing change from " +
                "the tunnels, at the very least, the walls aren't " +
                "quite so close, nor the ceiling as low. ";
            add_item(({"walls", "wall"}),
                "The walls of this chamber appear to have been " +
                "formed naturally. They've been worn smooth, but their " +
                "surfaces are uneven, almost random in texture.\n");
            add_item(({"ceiling", "roof"}),
                "The ceiling of this chamber is high, but not high " +
                "enough to aleviate the nagging concern of its " +
                "stability.\n");
            add_item(({"floor", "ground"}),
                "Beneath you, smooth but uneven grey stone serves " +
                "as a floor for the cavern.\n");            
            break;
        case 3:
            set_short("a large cavern");
            main += "You have arrived in a massive cavern beneath " +
                "the ground, one of the largest you've seen. Apparently " +
                "a natural formation, judging by the smooth yet " +
                "random contours of the walls and ceiling, and " +
                "the large stalactites hanging from the ceiling. " +
                "The occasional sound of dripping water into a " +
                "pool of water breaks the silence in the cavern, " +
                "echoing through the shadows, reminding you there " +
                "are many things here you might not be seeing. ";
            add_item(({"walls", "wall"}),
                "The walls of this chamber appear to have been " +
                "formed naturally. They've been worn smooth, but their " +
                "surfaces are uneven, almost random in texture.\n");
            add_item(({"ceiling", "roof"}),
                "High above you, the roof of this huge cavern hangs " +
                "like a gaping jaw, horrible teeth of stalactites ready " +
                "to descend at a moment's notice. Water drips from the " +
                "stalactites steadily into pools of water on the ground.\n");
            add_item(({"floor", "ground"}),
                "The floor of the cavern is smooth, but uneven, and full " +
                "pits and depressions, a number of which contain pools of " +
                "water filled by dripping stalactites.\n");
            add_item(({"stalactites"}),
                "Stalactites hang low from the ceiling, long cones of " +
                "dense minerals, from which water drips continually down " +
                "into depressions in the stone beneath which now contain " +
                "small pools of water.\n");
            add_item(({"pools", "water", "pools of water", "depressions",
                "depression"}),
                "Many of the depressions on the floor contain pools of " +
                "clear water formed by water dripping down from the " +
                "stalactites on the ceiling.\n");
            add_herb_file(HERBPATH + "greenslime");
            add_prop(OBJ_I_CONTAIN_WATER, 1);
            add_herb_file(HERBPATH + "brownslime");
            break;
        case 4:
            set_short("a man-made cavern");
            main += "You have entered a huge chamber, initially you " +
                "believe it to be a natural formation, but a second " +
                "look around reveals lines much to straight and " +
                "angles much to sharp to have formed by the " +
                "results of wind and water. It appears to have been " +
                "here for ages, but this room was definately " +
                "excavated, or at the least shaped, by hand. ";
            add_item(({"walls", "wall"}),
                "Smooth and straight-edged, the walls are still cut " +
                "from solid stone, but it looks more like it was cut " +
                "by hammer and chisel, rather than by water and time.\n");
            add_item(({"ceiling", "roof"}),
                "It appears that whoever excavated this chamber had " +
                "little concern for the ceiling, as it still looks to " +
                "be a natural formation, despite the obvious work put " +
                "into smoothing the walls and ground.\n");
            add_item(({"ground", "floor"}),
                "The ground of the chamber has been nicely leveled off. " +
                "It is free of any pits or depressions of any kind, " +
                "and is actually much like the floor of a real room.\n");
            break;
        default:
            set_short("a wide cavern");
            main += "You've entered a wide, shadowy cavern deep " +
                "within the living stone of the island. The walls " +
                "and floor bear the swirling, smooth contours of " +
                "surfaces shaped and polished by moving water, " +
                "and their dampness leads you to wonder if for " +
                "some reason water still flows through here on " +
                "occasion today. ";
            add_item(({"walls", "wall"}),
                "The walls of this chamber appear to have been " +
                "formed naturally. They've been worn smooth, but their " +
                "surfaces are uneven, almost random in texture.\n");
            add_item(({"ceiling", "roof"}),
                "The ceiling of this chamber is high, but not high " +
                "enough to aleviate the nagging concern of its " +
                "stability.\n");
            add_item(({"floor", "ground"}),
                "Beneath you, smooth but uneven grey stone serves " +
                "as a floor for the cavern.\n");            
            break;
    }
}

/*
 * Function name: add_extras
 * Description  : Used to add additional 'standard' descriptions to
 *                the rooms.
 * Arguments    : which - Integer representing which available extra
 *                        to add. Currently, only extra is POOLS,
 *                        defined in the local defs.h/
 * Returns      : n/a
 */
public void
add_extras(int which)
{
    if (!which)
        return;

    if (!main)
        main = "";

    switch(which)
    {
      /* Add pools of water to the cavern. */
        case POOLS:
            main += "Scattered around the floor you notice several " +
                "small pools of cold, clear water, which has " +
                "trickled down through cracks in the stone from the " +
                "lake outside and settled into depressions in the " +
                "floor. ";
            add_item(({"pool","pools","water","depression","depressions"}),
                "Small depressions in the floor have collected " +
                "cold, murky water from the lake as it seeps through " +
                "the cracks in the stone.\n");
            add_prop(OBJ_I_CONTAIN_WATER, 1);
            add_herb_file(HERBPATH + "greenslime");
            add_herb_file(HERBPATH + "brownslime");
            add_prop(CAVE_HAS_WATER, 1);
            break;
        }
}

/*
 * Function name: create_base
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_base()
{
  /* Generate the slopes description for the long desc. */
    TO->create_slopes();

  /* Set the long desc. and default props.*/
    set_long(main + "\n\n");
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);

  /* setup herb support, specify no additional herbs to add */
  /* as they are already added in create_cavern() and add_extras() */
    setup_my_herbs(NO_HERB_FILES);
    reset_room();

  /* Load cav5.c if it isn't already loaded to get the zombies */
  /* moving. */
    if (!find_object(CAVERNS + "cav5") &&
        file_name(TO) != CAVERNS + "cav5")
        (CAVERNS + "cav5")->load_me();
}

/*
 * Function name: create_tunnel
 * Description  : Turns this room into a tunnel.
 * Arguments    : mode - Integer representing type of tunnel to create.
 *                       Mode 1 = a narrow tunnel.
 *                       Mode 2 = an average tunnel.
 *                       Mode 3 = a wide tunnel.
 * Returns      : n/a
 */
public void
create_tunnel(int mode)
{
  /* Do nothing if no mode specified. */
    if (!mode)
        return;

  /* Initialize 'main' var if necessary. */
    if (!main)
        main = "";

  /* Add tunnel description/contents as necessary. */
    switch(mode)
    {
      /* All tunnels have CAVE_IS_TUNNEL prop. */
        add_prop(CAVE_IS_TUNNEL, 1);

      /* Case 1 - a narrow tunnel. */
        case 1:
            set_short("a narrow tunnel");
            main += "You are in a narrow, fissure-like tunnel deep " +
                "in a series of caverns and catacombs. This " +
                "particular passage appears to be the remains " +
                "of a very small underground flume of some kind, " +
                "as the walls are polished almost perfectly smooth, " +
                "rounding together towards the ceiling and a " +
                "fairly muddy floor. ";
            add_item(({"walls", "wall"}),
                "The walls of this passage are rather tightly " +
                "shaped, and give you the impression of walking " +
                "through a pipe made from solid stone.\n");
            add_item(({"ceiling", "roof"}),
                "Looking up, you note this passage doesn't as much " +
                "have a ceiling as it does a point where the walls " +
                "curve together to meet.\n");
            add_item(({"ground", "floor"}),
                "The ground of this tunnel is quite unspectacular, " +
                "water-worn stone that is now covered in a loose " +
                "collection of muddy silt.\n");
            add_item(({"silt", "muddy silt"}),
                "The silt was probably part of a wall somewhere in " +
                "these caverns at some point in time, but gave way " +
                "to the effects of water ages ago.\n");
            break;

      /* Case 2 - an average tunnel. */
        case 2:
            set_short("a tunnel");
            main += "You are in a fairly narrow passage in the " +
                "cavern system, smoothly worn by time and water, " +
                "and almost perfectly tubular in shape. It's " +
                "not the greatest place for walking or fighting " +
                "in, but it's not as cramped as some of the " +
                "tunnels down here. ";
            add_item(({"walls", "wall"}),
                "The walls of this passage are rather tightly " +
                "shaped, and give you the impression of walking " +
                "through a pipe made from solid stone.\n");
            add_item(({"ceiling", "roof"}),
                "Looking up, you note this passage doesn't as much " +
                "have a ceiling as it does a point where the walls " +
                "curve together to meet.\n");
            add_item(({"ground", "floor"}),
                "The floor of this chamber is rather awkward to " +
                "travel across, as the tunnel is practically completely " +
                "tubular in shape. The end result is a highly curved " +
                "floor, with a patch only about a foot wide that can be " +
                "comfortably walked on.\n");
            break;

      /* Case 3 - a wide tunnel. */
        case 3:
            set_short("a wide tunnel");
            main += "You are in a wide tunnel through the stone " +
                "foundation of the island. Judging from the wavering " +
                "and gracefully curving walls and floor of " +
                "the passage, this is a natural formation, but " +
                "it feels much like walking down a man-made " +
                "corridor, the ground being comfortably smooth and " +
                "walls being far enough apart for four men to " +
                "walk abreast. ";
            add_item(({"ceiling", "roof"}),
                "High above you hangs the smoothly polished stone " +
                "that forms the roof of the passage. It looks quite " +
                "solid, but doesn't appear particularly interesting.\n");
            add_item(({"wall", "walls"}),
                "The walls of this passage are a comfortable distance " +
                "apart, and by some chance of nature are almost squared " +
                "with the ceiling and floor, making for quite comfortable " +
                "travel.\n");
            add_item(({"floor", "ground"}),
                "The ground here is made of the same cold stone as " +
                "everything else in these caverns, however by some chance " +
                "it's been smoothly polished by moving water, and the " +
                "ceiling seems free of the dripping water which normally " +
                "would create large pits in the floor.\n");
            break;
    }
}

/*
 * Function name: create_slopes
 * Description  : Adds information about which way the floor is 
 *                sloping to the 'main' variable.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_slopes()
{
    int i;
    string temp;
    string *temparr = ({});

    if (dir_up && sizeof(dir_up))
        temparr += ({"generally upwards to the " + COMP_WORDS(dir_up)});
    if (dir_down && sizeof(dir_down))
        temparr += ({"slightly downwards to the " + COMP_WORDS(dir_down)});
    if (dir_level && sizeof(dir_level))
        temparr += ({"straight across to the " + COMP_WORDS(dir_level)});

    if (!sizeof(temparr))
        return;
    else if (sizeof(temparr) == 1)
        temp = "The exit here leads " + COMP_WORDS(temparr) + ". ";
    else
        temp = "The exits here lead " + COMP_WORDS(temparr) + ". ";

    main += temp;
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Called in the room when another object enters
 *                it's inventory. Used here to watch for player
 *                corpses.
 * Arguments    : ob - Object pointer to the object entering
 *                     the room.
 *                from - Object pointer to the last environment
 *                       of 'ob'.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("corpse"))
    {
        set_alarm(5.0, 0.0, &reincarnate_corpse(ob));
    }
}

/*
 * Function name: reincarnate_corpse
 * Description  : Turns a corpse into a zombie of the player,
 *                if the corpse is from a player.
 * Arguments    : ob - Object pointer to the corpse to test.
 * Returns      : n/a
 */
public void
reincarnate_corpse(object ob)
{
    string name;

    name = ob->query_real_name();

    if (!find_player(name))
        return;

    (SPECIAL + "zombie_maker")->make_me_zombie(name);
    (SPECIAL + "zombie_maker")->animate_corpse(ob, name);
}
