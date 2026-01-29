/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/ledge
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
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <tasks.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* the file for akugla */
#define    AKUGLA_FILE    ("/d/Emerald/blackwall/delrimmon/npc/captain")
#define    GROUND_ROOM    (DELRIMMON_DIR + "lakeside/caves/ante_room_new")

/* prototypes */
public void    reset_room();
public mixed   leave_chamber(object ob);
public void    heal_captain(object captain);
public void    query_space_available();
public string  long_desc();

/* global variables */
object   Ugluk_Npc;

public string  look_down();
public int prevent_leave_ledge();

/*
 * function name:        create_del_rimmon
 * description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a wide circular stone chamber");
    set_long(long_desc);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    // Impossible to hide
    add_prop(ROOM_I_HIDE, -1);

    add_prop(OBJ_S_WIZINFO, "This room has limited occupancy. Wizards, " +
             "please do not stay here hidden/invis unnecessarily.\n");

    add_item( ({ "ledge", "narrow ledge", "north", "north wall",
                 "northern wall", "wall to the north"}),
        &look_down() );
    add_item( ({ "edge", "carven edge", "edge of the ledge", }), BSN(
        "The edge of the narrow ledge is at least ten feet above the"
      + " floor of the cavern."));
    add_item( ({ "stone", "stones", "boulder", "boulders",
                 "stones and boulders", "pile", "pile of stones",
                 "pile of boulders", "pile of stones and boulders", }),
    BSN("Stones and boulders have been piled beneath a ledge which"
      + " protrudes from the northern wall such as to suggest"
      + " a way to climb up to the higher ground."));
    add_item( ({ "stairway", "make-shift stairway", "makeshift stairway",
                 "stairs", "formation" }), BSN(
        "It seems quite clear that whoever placed these stones meant"
      + " to create a way to climb up to the ledge."));
    add_item( ({ "wall", "walls", "cavern wall", "cavern walls" }), BSN(
        "The walls of this chamber rise high above to connect with"
      + " a vaulted ceiling. Facing north, south, east, and west,"
      + " they have been carved from the stone of the cliffs."));
    add_item( ({ "west", "west wall", "western wall",
                 "wall to the west", }), BSN(
        "The wall to the west is bare."));
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east", }), BSN(
        "A small passageway leads out through the eastern wall,"
      + " which is otherwise quite bare."));
    add_item( ({ "south", "south wall", "southern wall",
                 "wall to the south", }), BSN(
        "A great emblem has been carved in the wall to the south."));
    add_item( ({ "chamber", "room", "here", "cavern", "cave",
                 "wide chamber", "stone chamber",
                 "wide stone chamber", }), BSN(
        "This chamber is slightly rectagonal, running longer to the"
      + " north and south. A ledge to the north suggests that perhaps"
      + " this room was once used to hold some form of an audience."));
    add_item( ({ "ceiling", "vaulted ceiling", "high ceiling",
                 "up", "roof", "high vaulted ceiling", }), BSN(
        "The ceiling is vaulted high above. Sounds reverberate heavily"
      + " in this chamber, perhaps due to its concave shape. It may"
      + " be that the ceiling was so designed for acoustical reasons."));
    add_item( ({ "shape of the ceiling", "concave shape", }), BSN(
        "The concave shape of the ceiling creates a dramatic acoustic"
      + " in this room, especially for anyone standing on the"
      + " ledge along the northern wall."));
    add_item( ({ "stone of the cliff", "cliff", "cliffs", }), BSN(
        "While the cliffs themselves are not visible from these"
      + " depths, the stone of their foundation surrounds you here,"
      + " comprising the surface of the walls and floor."));
    add_item( ({ "down", "ground", "earth", "floor", }), BSN(
        "The floor is very smooth, and covered with a layer of"
      + " dust and small debris."));
    add_item( ({ "dust", "layer of dust", }), BSN(
        "The dust along the floor has been disturbed by many"
      + " footprints which travel all about the chamber."));
    add_item( ({ "print", "footprint", "footprints", "prints" }), BSN(
        "The footprints are everywhere. They are too numerous and"
      + " confused to be of any directional value."));
    add_item( ({ "debris", "small debris", "layer of debris",
                 "layer of small debris" }), BSN(
        "The debris consist mostly of bits of rock which have"
      + " fallen down from the ceiling high above."));
    add_item( ({ "rock", "bits", "bit of rock", "bits of rock" }), BSN(
        "It would seem that time has worn away the surface of the"
      + " ceiling some, and that the decay lies here at your feet."));
    add_item( ({ "layer of dust and debris",
                 "layer of debris and dust", }), BSN(
        "The layer of dust and debris on the floor must have built"
      + " up over many years of dereliction in these chambers."));
    add_item( ({ "shadow", "shadows", "long shadow",
                 "long shadows", }), BSN(
        "The long and smooth surfaces of the walls and floor of"
      + " this chamber allow shadows to cast long and thin shapes"
      + " across the stone."));
    add_item( ({ "surface", "surfaces", "surface of the walls",
                 "surfaces of the walls", "surface of the floor",
                 "surfaces of the floor",
                 "surface of the walls and floor",
                 "surfaces of the walls and floor", }), BSN(
        "The surfaces of the walls and floor are exceedingly smooth"
      + " in this chamber, bearing very few markings to tell of the"
      + " work that went into their shaping."));
    add_item( ({ "shape", "shapes", "shape of the shadows",
                 "shapes of the shadows", }), BSN(
        "The shapes of the shadows are long and thin."));
    add_item( ({ "perimeter", "perimeter of the walls",
                 "rectangular perimeter",
                 "rectangular perimeter of the walls", }), BSN(
        "This chamber is shaped as a large rectangle, with the"
      + " greater length of the room running north to south."));
    add_item( ({ "sky", "sun", "moon", }), BSN(
        "From within these caves, you have no view of the outside"
      + " sky."));

    set_no_exit_msg(({ "east", "north", "northeast", "south", "southeast" }),
        "You would need to climb down from the ledge before heading off " +
        "in that direction.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
        "The walls of the chamber rise to block your progress.\n");

    reset_room();
} /* create_del_rimmon */

public string
standing_on_ground(object for_obj)
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

    occupants = GROUND_ROOM->query_occupants();

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

    return desc  + " on the ground below.\n";
}

public int
do_climb(string arg)
{
    string  name,
            vb,
            msg;

    if (!strlen(arg) ||
        (arg != "down" &&
         !parse_command(arg, ({}), "[down] [on] [to] [onto] [the] [stony] 'stones' / 'ground'")))
    {
        vb = capitalize(query_verb());
        notify_fail(vb + " where? " + vb + " down, perhaps?\n");
        return 0;
    }

    msg = " jumps down from the narrow ledge.\n";

    write("You jump down from the " + name + ".\n");
    say(({ this_player()->query_Met_name() + msg,
           "The " + this_player()->query_nonmet_name() + msg,
           "" }));

    tell_room(GROUND_ROOM, ({ this_player()->query_Met_name() + msg,
                              "The " + this_player()->query_nonmet_name() + msg,
                              "" }));

    this_player()->move_living("M", GROUND_ROOM, 1, 0);
    
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_climb, "climb");
}

public void
knock_off_ledge(object ob)
{
    int pct, dam;

    if (ob && present(ob) && query_space_available() < 0)
    {
        ob->catch_tell("Unable to move about the crowded ledge, you lose " +
                       "your footing and fall to the ground below.\n");
        tell_room(this_object(),
                  ({ "Unable to move about the crowded ledge, " +
                     ob->query_met_name() + " loses " + ob->query_possessive() +
                     " footing and falls to the ground below.\n",
                     "Unable to move about the crowded ledge, " +
                     ob->query_nonmet_name() + " loses " +
                     ob->query_possessive() + 
                     " footing and falls to the ground below.\n",
                     "Someone falls to the ground below.\n" }), ob, ob);
        tell_room(GROUND_ROOM,
                  ({ "Unable to move about the crowded ledge, " +
                     ob->query_met_name() + " loses " + ob->query_possessive() +
                     " footing and falls to the ground.\n",
                     "Unable to move about the crowded ledge, " +
                     ob->query_nonmet_name() + " loses " +
                     ob->query_possessive() +
                     " footing and falls to the ground.\n",
                     "Someone falls to the ground.\n" }), ob, ob);

        ob->move_living("M", GROUND_ROOM, 1, 0);

        pct = min(100, max(0, ob->resolve_task(TASK_DIFFICULT, ({ TS_DEX, SS_ACROBAT }))));

        dam = 400 * (100 - pct) / 100;

        if (dam > 0)
        {
            ob->heal_hp(-dam);
            if (ob->query_hp() <= 0)
            {
                ob->do_die(this_object());
            }
        }
    }
}

/*
 * function name:        leave_inv
 * description  :        mask parent to be sure that departing players
 *                       are removed from chair occupants
 * arguments    :        object ob -- the departing object
 *                       object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);

    if (living(ob))
    {
        leave_chamber(ob);
    }
} /* leave_inv */

/*
 * function name:        look_down
 * description  :        VBFC to describe ground + occupants
 * returns      :        string -- the description
 */
public string
look_down()
{
    return "A narrow ledge protrudes from the northern wall of"
         + " the cavern, its carven edge raised perhaps ten"
         + " feet from the floor. Beneath it, a large pile of"
         + " stones and boulders lie heaped in a formation which"
         + " would suggest a make-shift stairway.\n" +
           standing_on_ground(this_player());
}

public string
long_desc()
{
    return "Long shadows are cast across the walls of this"
               + " wide stone chamber, its vaulted ceiling looming"
               + " high above the rectangular perimeter of the walls"
               + " which close in on all sides.\n" + standing_on_ground(this_player());
}

/*
 * function name:        enter_inv
 * description  :        called when objects enter this container or
 *                       when an object has just changed its
 *                       weight/volume/light status. We use it here
 *                       to add a no_attack prop to livings.
 * arguments    :        ob: the object that has just entered this inv
 *                       from: the object from which it came
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->query_wiz_level())
    {
        ob->catch_tell("\nWARNING WARNING WARNING WARNING WARNING\nThis room has limited occupancy. Wizards, " +
                       "please do not stay here hidden/invis unnecessarily.\n\n");
    }
    else if (living(ob) && !ob->query_npc())
    {
        if (query_space_available() < 0)
        {
            set_alarm(1.0, 0.0, &knock_off_ledge(ob));
        }
    }

} /* enter_inv */

/*
 * function name:        reset_room
 * description  :        clone some npcs to the room at resets
 */
public void
reset_room()
{
    if (Ugluk_Npc)
    {
        // If Ugluk is alive, but isn't here, isn't fighting, and isn't being
        // controlled by a wizard, move him back.
        if (!present(Ugluk_Npc) &&
            !Ugluk_Npc->query_attack() &&
            !Ugluk_Npc->query_link_remote() &&
            !Ugluk_Npc->query_possessed())
        {
            Ugluk_Npc->move_living("home", this_object(), 1, 1);
        }

        return;
    }

    setuid();
    seteuid(getuid());

    Ugluk_Npc = clone_object(
        "/d/Emerald/blackwall/delrimmon/npc/captain");
    Ugluk_Npc->arm_me();
    Ugluk_Npc->move_living("down", this_object());
} /* reset_room */

public int
prevent_leave_ledge()
{
    // Block Akugla from using the exits, unless he's controlled by a wiz
    if (this_player()->id("del_rimmon_akugla") &&
        !this_player()->query_possessed() &&
        !this_player()->query_link_remote())
    {
        return 1;
    }

    return 0;
}

public void
leave_chamber(object ob)
{
    object akugla;

    if (ob->id("del_rimmon_akugla"))
    {
        return;
    }

    if (akugla = present("del_rimmon_akugla"))
    {
        if (!akugla->query_attack())
        {
            set_alarm(1.0, 0.0, &heal_captain(akugla));
        }
    }
} /* leave_chamber */


/*
 * Funtion name:        heal_captain
 * Description :        if players try the run/heal/return tactic
 *                      against the captain, he swigs some of his
 *                      healing brew to compensate for their stupid
 *                      cheater ways.
 * Arguments   :        object captain - the captain object
 */
public void
heal_captain(object captain)
{
    if (captain)
    {
        tell_room(this_object(), "The huge black orc captain takes a"
          + " small black vial from his belt, and downs its contents."
          + " He shatters the vial on the ground and grins with renewed"
          + " vigour.\n");

        captain->heal_hp(3000);
    }
} /* heal_captain */

public object *
query_occupants()
{
    return FILTER_LIVE(all_inventory(this_object()));
}

public int
query_space_available()
{
    return 1 - sizeof(FILTER_PLAYERS(all_inventory(this_object())));
}

