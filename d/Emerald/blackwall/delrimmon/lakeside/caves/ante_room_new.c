/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/ante_room.c
 *
 *  This room was used by Formandil and Maeltar to hold indoor meetings
 *  at the outposts. It was designed for a speaker to stand upon the
 *  ledge and speak to the assembly. In current times, it has become
 *  the brooding ground for the Captain of the Orcs who has come here
 *  at the behest of the Darklings to examine the area. This room
 *  has special combat locations. People standing on the ground cannot
 *  fight with people standing on the ledge, and vise-versa. It amounts
 *  to whomever feels up to tackling the orc captain needing to
 *  solo him one-on-one. The nice thing is, people can watch from
 *  below, a bit like a boxing match.
 *
 *  Copyright (c) October 2001, by Cooper Sherry (Gorboth)
 *
 *  Much thanks must go to Gnadnar, who supplied the original vision
 *  and coding assistance which made this room possible.
 *
 *  Updated Sept 1, 2004 to split the ledge into a separate room. The
 *  previous ledge implementation using Gondor chair code allowed a
 *  number of exploits which permitted more than one player to engage
 *  the captain at once. I would prefer to make the ledge a subloc
 *  within this room, but I'm afraid that may be exploitable as well,
 *  especially with guild special attacks, which may not properly
 *  check subloc access.
 *  -Shiva
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"

#define    NPC_FILE        (DELRIMMON_DIR + "npc/guardian_orc")
#define    LEDGE_ROOM      (DELRIMMON_DIR + "lakeside/caves/ledge")

public void    reset_room();
public string  look_at_ledge();

/* global variables */
object  *Npcs = allocate(3 + random(2));

/*
 * function name:        create_del_rimmon
 * description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a wide circular stone chamber");
    set_long("Long shadows are cast across the walls of this"
               + " wide stone chamber, its vaulted ceiling looming"
               + " high above the rectangular perimeter of the walls"
               + " which close in on all sides.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_item( ({ "ledge", "narrow ledge", "north", "north wall",
                 "northern wall", "wall to the north"}),
        &look_at_ledge());
    add_item( ({ "edge", "cavern edge", "edge of the ledge", }), 
        "The edge of the narrow ledge is at least ten feet above the"
      + " floor of the cavern.\n");
    add_item( ({ "stone", "stones", "boulder", "boulders",
                 "stones and boulders", "pile", "pile of stones",
                 "pile of boulders", "pile of stones and boulders", }),
        "Stones and boulders have been piled beneath a ledge which"
      + " protrudes from the northern wall such as to suggest"
      + " a way to climb up to the higher ground.\n");
    add_item( ({ "stairway", "make-shift stairway", "makeshift stairway",
                 "stairs", "formation" }), 
        "It seems quite clear that whoever placed these stones meant"
      + " to create a way to climb up to the ledge.\n");
    add_item( ({ "wall", "walls", "cavern wall", "cavern walls" }), 
        "The walls of this chamber rise high above to connect with"
      + " a vaulted ceiling. Facing north, south, east, and west,"
      + " they have been carved from the stone of the cliffs.\n");
    add_item( ({ "west", "west wall", "western wall",
                 "wall to the west", }), 
        "The wall to the west is bare.\n");
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east", }),
        "A small passageway leads out through the eastern wall,"
      + " which is otherwise quite bare.\n");
    add_item( ({ "south", "south wall", "southern wall",
                 "wall to the south", }), 
        "A great emblem has been carved in the wall to the south.\n");
    add_item( ({ "chamber", "room", "here", "cavern", "cave",
                 "wide chamber", "stone chamber",
                 "wide stone chamber", }), 
        "This chamber is slightly rectagonal, running longer to the"
      + " north and south. A ledge to the north suggests that perhaps"
      + " this room was once used to hold some form of an audience.\n");
    add_item( ({ "ceiling", "vaulted ceiling", "high ceiling",
                 "up", "roof", "high vaulted ceiling", }), 
        "The ceiling is vaulted high above. Sounds reverberate heavily"
      + " in this chamber, perhaps due to its concave shape. It may"
      + " be that the ceiling was so designed for acoustical reasons.\n");
    add_item( ({ "shape of the ceiling", "concave shape", }),
        "The concave shape of the ceiling creates a dramatic acoustic"
      + " in this room, especially for anyone standing on the"
      + " ledge along the northern wall.\n");
    add_item( ({ "stone of the cliff", "cliff", "cliffs", }), 
        "While the cliffs themselves are not visible from these"
      + " depths, the stone of their foundation surrounds you here,"
      + " comprising the surface of the walls and floor.\n");
    add_item( ({ "down", "ground", "earth", "floor", }), 
        "The floor is very smooth, and covered with a layer of"
      + " dust and small debris.\n");
    add_item( ({ "dust", "layer of dust", }), 
        "The dust along the floor has been disturbed by many"
      + " footprints which travel all about the chamber.\n");
    add_item( ({ "print", "footprint", "footprints", "prints" }), 
        "The footprints are everywhere. They are too numerous and"
      + " confused to be of any directional value.\n");
    add_item( ({ "debris", "small debris", "layer of debris",
                 "layer of small debris" }), 
        "The debris consist mostly of bits of rock which have"
      + " fallen down from the ceiling high above.\n");
    add_item( ({ "rock", "bits", "bit of rock", "bits of rock" }), 
        "It would seem that time has worn away the surface of the"
      + " ceiling some, and that the decay lies here at your feet.\n");
    add_item( ({ "layer of dust and debris",
                 "layer of debris and dust", }), 
        "The layer of dust and debris on the floor must have built"
      + " up over many years of dereliction in these chambers.\n");
    add_item( ({ "shadow", "shadows", "long shadow",
                 "long shadows", }), 
        "The long and smooth surfaces of the walls and floor of"
      + " this chamber allow shadows to cast long and thin shapes"
      + " across the stone.\n");
    add_item( ({ "surface", "surfaces", "surface of the walls",
                 "surfaces of the walls", "surface of the floor",
                 "surfaces of the floor",
                 "surface of the walls and floor",
                 "surfaces of the walls and floor", }), 
        "The surfaces of the walls and floor are exceedingly smooth"
      + " in this chamber, bearing very few markings to tell of the"
      + " work that went into their shaping.\n");
    add_item( ({ "shape", "shapes", "shape of the shadows",
                 "shapes of the shadows", }), 
        "The shapes of the shadows are long and thin.\n");
    add_item( ({ "perimeter", "perimeter of the walls",
                 "rectangular perimeter",
                 "rectangular perimeter of the walls", }), 
        "This chamber is shaped as a large rectangle, with the"
      + " greater length of the room running north to south.\n");
    add_item( ({ "sky", "sun", "moon", }), 
        "From within these caves, you have no view of the outside"
      + " sky.\n");

    add_exit(DELRIMMON_DIR + "lakeside/caves/barracks", "east",
             0, 1);

    set_no_exit_msg( ({ "north", "northeast", "southeast", "south",
                        "southwest", "west", "northwest" }),
        "The walls of the chamber rise to block your progress.\n");

    reset_room();
} /* create_del_rimmon */

/*
 * function name:        standing_on_ledge
 */
public string
standing_on_ledge(object for_obj)
{
    object  *occupants,
            *others;
    int      i;
    string  *names,
             desc = "";

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    setuid();
    seteuid(getuid());

    occupants = LEDGE_ROOM->query_occupants();

    if (sizeof(occupants) < 1)
    {
        return "";
    }
    else if (sizeof(occupants) == 1)
    {
        if (occupants[0] != for_obj)
        {
            desc = occupants[0]->query_Art_name(for_obj) + " is";
        }
        else
        {
            desc = "You are";
        }
    }
    else
    {
        if ((i = member_array(for_obj, occupants)) < 0)
        {
            names = occupants->query_art_name(for_obj);
        }
        else
        {
            others = exclude_array(occupants, i, i);
            names = others->query_art_name(for_obj) + ({ "you" });
        }
        desc = capitalize(COMPOSITE_WORDS(names)) + " are";
    }

    return desc + " standing on the narrow ledge.\n";
}

/*
 * function name:        do_climb
 * description  :        a redefinition of gnadnar's function so we
 *                       get the messages we want (long way again!)
 */
public int
do_climb(string arg)
{
    string msg;

    if (!strlen(arg))
    {
        notify_fail("Climb where?");
        return 0;
    }


    if ((arg != "up") &&
        !parse_command(arg, ({}), "[up] [on] [to] [onto] [the] [stony] 'stones' / 'ledge'"))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!this_player()->query_wiz_level() && 
        (this_player()->query_prop(OBJ_I_HIDE) ||
         this_player()->query_prop(OBJ_I_INVIS) ||
         this_player()->query_invis()))
    {
        write("You decide not to try, since that would " +
            "probably reveal your presence.\n");
        return 1;
    }

    if (present("_guardian_orc", this_object()))
    {
        write("One of the orcs jumps in front of you, barring"
                    + " your access to the ledge.\n");
        return 1;
    }

    setuid();
    seteuid(getuid());

    if (LEDGE_ROOM->query_space_available() < 1)
    {
        write("There is no room for you on the ledge.\n");
        return 1;
    }

    msg = " climbs up the stones to stand on the ledge.\n";

    write("You climb up the stones to stand on the ledge.\n");
    say(({ this_player()->query_Met_name() + msg,
           "The " + this_player()->query_nonmet_name() + msg,
           "" }));

    tell_room(LEDGE_ROOM, ({ this_player()->query_Met_name() + msg,
                             "The " + this_player()->query_nonmet_name() + msg,
                             "" }));

    this_player()->move_living("M", LEDGE_ROOM, 1, 0);


    return 1;
}

public void
init()
{
    ::init();

    add_action(do_climb, "climb");
}

/*
 * function name:        look_at
 * description  :        VBFC to describe ledge + occupants
 * returns      :        string -- the description
 */
public string
look_at_ledge()
{
    return "A narrow ledge protrudes from the northern wall of"
         + " the cavern, its carven edge raised perhaps ten"
         + " feet from the floor. Beneath it, a large pile of"
         + " stones and boulders lie heaped in a formation which"
         + " would suggest a make-shift stairway.\n" +
           standing_on_ledge(this_player());
}

/*
 * function name:        reset_room
 * description  :        clone some npcs to the room at resets
 */
public void
reset_room()
{
    object  emblem;

    if (!present("kot_emblem"))
    {
        emblem = clone_object(DELRIMMON_DIR + "obj/normal_emblem");
        emblem->set_emblem(
            "The emblem is great in size, spanning a large portion of"
          + " the southern wall. It depicts the symbol of Telberin -"
          + " a four-pointed star within a circular band.");
        emblem->set_too_high();
        emblem->move(this_object());
    }

    clone_npcs(Npcs, NPC_FILE, 0.0);
} /* reset_room */

public object *
query_occupants()
{
    return FILTER_LIVE(all_inventory(this_object()));
}
