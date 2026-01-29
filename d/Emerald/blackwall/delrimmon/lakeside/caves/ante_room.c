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
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.c";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"

/* indices for chair data */
#define    I_PATTERN        0
#define    I_CAPACITY       1
#define    I_OCCUPANTS      2
#define    I_PREP           3
#define    NPC_FILE        (DELRIMMON_DIR + "npc/guardian_orc")

/* names for our chair ... er ... ledge */
#define    CHAIR_NAME    "narrow ledge"
/* a check for our attack prevention */
#define    IS_ON_LEDGE(ob) (ob->query_prop(LIVE_S_SITTING))
/* the file for akugla */
#define    AKUGLA_FILE    ("/d/Emerald/blackwall/delrimmon/npc/captain")

/* prototypes */
public void    create_del_rimmon();
public string  sitting_on_chair(string name, object for_obj, int namesonly, int
definite = 1);
public int     do_sit(string arg);
public int     do_stand(string arg);
public void    stand_up(object tp, string name, int domsg);
public string  show_subloc(string subloc, object pl, object for_obj);
public void    my_sit_msgs(object pl, string prep, string name, int fighting);
public void    my_stand_msgs(object pl, string name, int fighting);
public int     no_hide(string arg);
public void    init();
public void    leave_inv(object ob, object dest);
public mixed   ledge_kill_check(object victim);
public void    enter_inv(object ob, object from);
public void    reset_room();
public mixed   leave_chamber();
public void    heal_captain(object captain);

/* global variables */
object   Ugluk_Npc;
object  *Npcs = allocate(3 + random(2));

public string  look_at(string arg);  /* VBFC for chairs */
/*
 * function name:        create_del_rimmon
 * description  :        set up the room with domain presets
 */
public void
create_del_rimmon()
{
    set_short("a wide circular stone chamber");
    set_long(BSN("Long shadows are cast across the walls of this"
               + " wide stone chamber, its vaulted ceiling looming"
               + " high above the rectangular perimeter of the walls"
               + " which close in on all sides."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_chair(CHAIR_NAME,
        "[up] [on] [to] [onto] [the] [stony] 'stones' / 'ledge'",
        2, "on");

    add_item( ({ "ledge", "narrow ledge", "north", "north wall",
                 "northern wall", "wall to the north"}),
        &look_at(CHAIR_NAME) );
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

    add_exit(DELRIMMON_DIR + "lakeside/caves/barracks", "east",
             leave_chamber, 1);

    set_no_exit_msg( ({ "north", "northeast", "southeast", "south",
                        "southwest", "west", "northwest" }),
        "The walls of the chamber rise to block your progress.\n");

    reset_room();
} /* create_del_rimmon */

/*
 * function name:        sitting_on_chair
 * description  :        a redefine of gnadnar's so we get the text we
 *                       want (the looooong way round!)
 */
public string
sitting_on_chair(string name, object for_obj, int namesonly, int definite = 0)
{
    mixed   *chairptr;
    object  *occupants,
            *others;
    int      i,
             s;
    string  *names,
             desc;

    if (!strlen(name) ||
        !pointerp(chairptr = Room_chairs[name]) ||
        !(s = sizeof(occupants = chairptr[I_OCCUPANTS])))
    {
        return "";
    }

    if (!objectp(for_obj))
    {
        for_obj = this_player();
    }

    if (s == 1)
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

    if (!namesonly)
        desc += " standing " + chairptr[I_PREP] + " the " + name + ".\n";
    return desc;
} /* sitting_on_chair */

/*
 * function name:        do_sit
 * description  :        a redefinition of gnadnar's function so we
 *                       get the messages we want (long way again!)
 */
public int
do_sit(string arg)
{
    mixed   *indices,
            *chairptr;
    object  *occupants,
            *enemies,
             akugla,
            *guards,
             tp = this_player();
    int      cap,
             fighting = 0,        /* is there combat involved? */
             i,
             nchairs,
             s;

    if (!strlen(arg))
    {
        NFN0("Climb where?");
    }

    if (strlen(tp->query_prop(LIVE_S_SITTING)))
    {
        notify_fail("You are already standing on the ledge.\n");
        return 0;
    }

    if (tp->query_prop(OBJ_I_HIDE) ||
        tp->query_prop(OBJ_I_INVIS) ||
        tp->query_invis())
    {
        write(break_string("You decide not to try, since that would " +
            "probably reveal your presence.", 75) + "\n");
        return 1;
    }

    indices = m_indices(Room_chairs);
    if (!(nchairs = sizeof(indices)))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (present("_guardian_orc", this_object()) &&
        !tp->id("akugla"))
    {
        tp->catch_msg("One of the orcs jumps in front of you, barring"
                    + " your access to the ledge.\n");
        return 1;
    }

    s = strlen(arg);
    for (i = 0; i < nchairs; ++i)
    {
        chairptr = Room_chairs[indices[i]];
        if (!s ||
            arg == "up" ||
            arg == indices[i] ||
            parse_command(arg, ({}), chairptr[I_PATTERN]))
        {
            /* matched a chair ... is there room? */
            occupants = chairptr[I_OCCUPANTS];
            if (sizeof(occupants) < chairptr[I_CAPACITY])
            {
                if (tp->query_attack())
                {
                    enemies = tp->query_enemy(-1);
                    guards = filter(enemies, &->id("_guardian_orc"));

                    if (sizeof(guards))
                    {
                        tp->catch_msg(QCTNAME(guards[0]) + " jumps"
                            + " in front of the stair-like stones,"
                            + " pushing you back away from the ledge.\n");
                        return 1;
                    }

                    tp->stop_fight(enemies);
                    enemies->stop_fight(tp);
                    fighting = 1;
                }
                tp->set_no_show_composite(1);
                tp->add_subloc(SITTING_S_SUBLOC, this_object());
                tp->add_prop(LIVE_S_SITTING, indices[i]);
                chairptr[I_OCCUPANTS] += ({ tp });
                my_sit_msgs(tp, chairptr[I_PREP], indices[i], fighting);

                if (objectp(akugla = present("akugla", TO)))
                {
                    akugla->check_attack(TP);
                }
                return 1;
            }
            /* cannot say "the <name> is full", because
             * we don't know whether it should be "is full"
             * or "are full".
             */
            notify_fail("There is no room for you " + chairptr[I_PREP] +
                " the " + indices[i] + ".\n");
            return 0;
        }
    }
    notify_fail("Climb where?\n");
    return 0;
} /* do_sit */

/*
 * function name:        do_stand
 * description  :        a redefinition of gnadnar's func for message
 *                       purposes
 */
public int
do_stand(string arg)
{
    string  name,
            vb;

    if (strlen(arg) &&
        arg != "down")
    {
        vb = capitalize(query_verb());
        notify_fail(vb + " where? " + vb + " down, perhaps?\n");
        return 0;
    }
    if (!strlen(name = this_player()->query_prop(LIVE_S_SITTING)))
    {
        notify_fail("You are already on the ground.\n");
        return 0;
    }

    stand_up(this_player(), name, 1);
    return 1;
} /* do_stand */

/*
 * function name:        stand_up
 * description  :        a redefine of gnadnar's func for msg purposes
 */
public void
stand_up(object tp, string name, int domsg)
{
    int     fighting = 0;
    mixed  *chairptr;
    object *enemies,
           *akugla;

    if (tp->query_attack())
    {
        enemies = tp->query_enemy(-1);
        akugla = filter(enemies, &->id("del_rimmon_akugla"));

        if (sizeof(akugla))
        {
            set_alarm(1.0, 0.0, &heal_captain(enemies));
        }

        tp->stop_fight(enemies);
        enemies->stop_fight(tp);
        fighting = 1;
    }
    tp->unset_no_show_composite();
    tp->remove_subloc(SITTING_S_SUBLOC);
    tp->remove_prop(LIVE_S_SITTING);

    if (domsg)
    {
        my_stand_msgs(tp, name, fighting);
    }

    if (pointerp(chairptr = Room_chairs[name]))
    {
        chairptr[I_OCCUPANTS] -= ({ tp });
    }
    else
    {
        /* eeks. now what? well, let's see if it ever happens. */
        CHAIRS_LOG_ERR("no chair '" + name + "' for " +
            tp->query_name() + ".\n");
    }
} /* stand_up */

/*
 * function name:        show_subloc
 * description  :        a redefine of gnadnar's func for msg purposes
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string  name;
    mixed  *chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
        return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = Room_chairs[name]))
    {
        if (for_obj != pl)
        {
            return capitalize(pl->query_pronoun()) + " is standing " +
                chairptr[I_PREP] + " a " + name + ".\n";
        }
        return "You are standing " + chairptr[I_PREP] + " a " +
            name + ".\n";
    }
    return "";
} /* show_subloc */

/*
 * function name:        my_sit_msgs
 * description  :        we redefine the hook
 */
public void
my_sit_msgs(object pl, string prep, string name, int fighting)
{
    if (fighting)
    {
        write("You scramble up the stones, escaping the fight, to"
            + " stand " + prep + " the " + name + ".\n");
        say(QCTNAME(this_player()) + " scrambles up some stones"
          + " along the north wall, escaping the fight, to stand "
          + prep + " a " + name + ".\n");
        return;
    }

    write("You climb up the stones to stand " + prep + " the " + name +
          ".\n");
    say(QCTNAME(this_player()) + " climbs up the stones to stand " +
        prep + " a " + name + ".\n");
} /* my_sit_msgs */

/*
 * function name:        my_stand_msgs
 * description  :        we redefine the hook for our own msgs
 */
public void
my_stand_msgs(object pl, string name, int fighting)
{
    if (fighting)
    {
        write("You jump down from the " + name + ", escaping"
            + " the fight.\n");
        say(QCTNAME(this_player()) + " jumps down from the "
          + name + ", escaping the fight.\n");
        return;
    }

    write("You jump down from the " + name + ".\n");
    say(QCTNAME(this_player()) + " jumps down from the " +name+ ".\n");
} /* my_stand_msgs */

/*
 * function name:        no_hide
 * description  :        redefinition of gnadnar's func for msgs
 */
public int
no_hide(string arg)
{
    if (strlen(this_player()->query_prop(LIVE_S_SITTING)))
    {
        write("It's too difficult to " + query_verb() +
            " while you are up on this ledge.\n");
        return 1;
    }
    return 0;
} /* no_hide */

/*
 * function name:        init
 * description  :        mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();

    add_action(do_sit, "climb");
    add_action(do_stand, "down");
    add_action(do_stand, "d");
    add_action(no_hide, "hide");

    if (this_player()->query_wiz_level())
    {
        add_action(no_hide, "invis");
    }
} /* init */

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
    leave_inv_room_chairs(ob, dest);

    ob->remove_prop(OBJ_M_NO_ATTACK);
    ob->remove_prop(OBJ_M_NO_MAGIC_ATTACK);
} /* leave_inv */

/*
 * function name:        look_at
 * description  :        VBFC to describe ledge + occupants
 * arguments    :        string arg -- what's being looked at
 *                       null str -> it's the room
 * returns      :        string -- the description
 */
public string
look_at(string arg)
{
    return "A narrow ledge protrudes from the northern wall of"
         + " the cavern, its carven edge raised perhaps ten"
         + " feet from the floor. Beneath it, a large pile of"
         + " stones and boulders lie heaped in a formation which"
         + " would suggest a make-shift stairway.\n" +
           sitting_on_chair(CHAIR_NAME, this_player(), 0, 0);
} /* look_at */

/*
 * function name:        ledge_kill_check
 * description  :        persons on the ground cannot fight with
 *                       people on the ledge, and vise-versa
 * arguments:            arg -- what the player typed
 * returns      :        1 -- ok to attack, 0 -- not ok
 */
public mixed
ledge_kill_check(object victim)
{
    object  attacker = this_player();

//  if (victim->id("del_rimmon_akugla"))
//  {
//      if (victim->query_attack())
//      {
//          if (IS_ON_LEDGE(attacker) == IS_ON_LEDGE(victim))
//          {
//              return BSN("Your attempt to attack the orc captain fails.");
//          }

//          else if (IS_ON_LEDGE(victim))
//          {
//              return BSN("You cannot attack him from below the ledge.");
//          }

//          else
//          {
//              return BSN("You cannot attack him from up on the ledge.");
//          }
//      }
//  }

    if (IS_ON_LEDGE(attacker) == IS_ON_LEDGE(victim))
    {
        return 0;
    }

    if (IS_ON_LEDGE(victim))
    {
        return BSN("You cannot attack from below the ledge"
                 + " like this.");
    }

    if (IS_ON_LEDGE(attacker))
    {
        return BSN("You cannot attack them from up on this ledge.");
    }

    return 0;
} /* ledge_kill_check */

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

    if (living(ob))
    {
        if (!Ugluk_Npc->query_prop(LIVE_S_SITTING))
        {
            Ugluk_Npc->command("climb ledge");
        }

        ob->add_prop(OBJ_M_NO_ATTACK, &ledge_kill_check(ob));
        ob->add_prop(OBJ_M_NO_MAGIC_ATTACK, &ledge_kill_check(ob));
    }
} /* enter_inv */

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

    if (objectp(Ugluk_Npc))
    {
        return;
    }

    Ugluk_Npc = clone_object(
        "/d/Emerald/blackwall/delrimmon/npc/captain");
    Ugluk_Npc->arm_me();
    Ugluk_Npc->move_living("down", this_object());
    Ugluk_Npc->command("climb ledge");
    clone_npcs(Npcs, NPC_FILE, 0.0);
} /* reset_room */

/*
 * function name:        leave_chamber
 * description  :        a check to prevent players from escaping
 *                       the fight with akugla simply by running
 *                       east.
 * returns      :        1 -- prevent exit,
 *                       func check_sitting - let 'em go.
 */
public mixed
leave_chamber()
{
    object *enemies,
           *akugla;

    if (this_player()->id("del_rimmon_akugla"))
    {
        return 1;
    }

    if (IS_ON_LEDGE(TP))
    {
        enemies = TP->query_enemy(-1);
        akugla = filter(enemies, &->id("del_rimmon_akugla"));

        if (sizeof(akugla))
        {
            set_alarm(1.0, 0.0, &heal_captain(enemies));
        }
    }

    return check_sitting();
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
    tell_room(this_object(), "The huge black orc captain takes a"
      + " small black vial from his belt, and downs its contents."
      + " He shatters the vial on the ground and grins with renewed"
      + " vigour.\n");

    captain->heal_hp(3000);

    return;
} /* heal_captain */

