/*
 *  /d/Sparkle/std/room/stream_room.c
 *
 *  Some rooms in the game will want to have a flowing stream of some
 *  kind (fresh water, sewer, etc.) This room handles that sort of
 *  functionality.
 *
 *  Created February 2010, by Matthew Morin (Aeg)
 *                          & Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/std/room/room";
inherit "/d/Sparkle/lib/water_effects";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


/* Definitions */
#define  WILL_FLOAT                5
#define  DEEP_WATER                48


/* Global Variables */
public object   Underwater_Room;   /* A room to represent the area beneath
                                    * the surface of this stream if the
                                    * stream is deep enough.
                                    */
public string   Underwater_Path;   /* Pathname for the underwater room. */
public int      Stream_Depth;      /* How deep is the water in cm?  */
public float    Flow_Speed;        /* How fast is the current here?     */
public string   Stream_Name;       /* e.g. "stream", "channel", etc     */
public string   Downstream_Room;   /* Pathname for downstream room.     */
public string   Downstream_Dir;    /* The downstream direction.         */
public string   Upstream_Dir;      /* The upstream direction.           */
public int      Swim_Skill_Needed; /* Skill needed to swim here.        */


/* Prototypes */
public void        create_stream_room();
nomask void        create_sparkle();
public void        init();
public int         do_dive(string arg);
public void        enter_inv(object ob, object from);
public void        move_downstream(object ob);
public int         test_floatation(object obj);
public int         query_deep_water();

public void        set_underwater_path(string s) { Underwater_Path = s;   }
public object      query_underwater_room()       { return Underwater_Room;}
public void        set_stream_depth(int i)       { Stream_Depth = i;      }
public int         query_stream_depth()          { return Stream_Depth;   }
public void        set_flow_speed(float f)       { Flow_Speed = f;        }
public void        set_stream_name(string s)     { Stream_Name = s;       }
public string      query_stream_name()           { return Stream_Name;    }
public void        set_downstream_room(string s) { Downstream_Room = s;   }
public void        set_downstream_dir(string s)  { Downstream_Dir = s;    }
public void        set_upstream_dir(string s)    { Upstream_Dir = s;      }
public void        set_swim_skill(int i)         { Swim_Skill_Needed = i; }

/*
 * Function name:        create_stream_room
 * Description  :        dummy routine to be redefined by inheriting
 *                       files
 */
public void
create_stream_room()
{
    /* Temporary values, which will be overriden (if necessary) by
     * inheriting rooms.
     */
    set_stream_depth(182);      /* We'll have 6 feet deep be default. */
    set_flow_speed(5.0);        /* 5 seconds, and things float away. */
    set_stream_name("stream");
    set_downstream_room("");    /* Leave empty for now. */
    set_downstream_dir("");
    set_upstream_dir("");
    set_swim_skill(10);         /* Seems reasonable for general use. */
} /* create_stream_room */


/*
 * Function name:        create_sparkle
 * Description  :        set up the room with functionality for the
 *                       stream mechanics
 */
nomask void
create_sparkle()
{
    set_short("temporary stream room short");
    set_long("Temporary stream room long.\n\n");

    create_stream_room(); /* This will set the values in inheriting files */

    if (Stream_Depth >= DEEP_WATER)
    {
        if (strlen(Underwater_Path))
        {
            Underwater_Room = clone_object(Underwater_Path);
        }
        else
        {
            Underwater_Room = clone_object(
                "/d/Sparkle/std/room/underwater_room");
        }

        Underwater_Room->set_surface_room(this_object());
    }
} /* create_sparkle */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(do_dive, "dive");
    add_action(do_dive, "swim");
    add_action(do_dive, "jump");
} /* init */


/*
 * Function name:        do_dive
 * Description  :        allow players to dive under the water
 *                       if it is sufficiently deep
 * Arguments    :        string arg - what the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_dive(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[in] [into] [to] [the] 'water' / '" + Stream_Name + "'"))
    {
        notify_fail("Where do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (!query_deep_water())
    {
        notify_fail("Unless you want to hit your head on the bottom,"
          + " you won't. It just isn't deep enough here!\n");
        return 0;
    }

    if (this_player()->query_skill(SS_SWIM) < Swim_Skill_Needed)
    {
        write("You look doubtfully at the water, and think better"
            + " of it. You simply don't know how to swim well"
            + " enough to dare.\n");

        return 1;
    }

    write("You dive beneath the surface of the " + Stream_Name + "!\n");
    tell_room(this_object(), QCTNAME(this_player()) + " dives beneath the"
      + " surface of the " + Stream_Name + " with a splash!\n",
        this_player());
    douse_flames(this_player());

    this_player()->move_living("M", Underwater_Room, 0, 1);

    tell_room(Underwater_Room, QCTNAME(this_player()) + " bursts through"
      + " the surface above and floats down to join you.\n", this_player());

    return 1;
} /* do_dive */



/*
 * Function name:        enter_inv
 * Description  :        Called when objects enter this container or when
 *                       an object has just changed its weight/volume/light
 *                       status. In this case, we want to move anything
 *                       non-living to the proper room.
 * Arguments    :        ob: The object that just entered this inventory
 *                       from: The object from which it came.
 *
 * We want things that are "in" the stream to float downstream if they
 * are not living and have a weight to volume ratio that suggests
 * floatation.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from == Underwater_Room)
    {
        tell_room(this_object(), capitalize(ob->short()) + " appears"
          + " from beneath the surface.\n", ob);
    }
            
    if (!interactive(ob))
    {
        /* First lets see if it floats */
        if (!test_floatation(ob))
        {
            /* Okay, it doesn't float, now lets see if it is too tall
             * to sink beneath the surface. 
             */
            if (ob->query_prop(OBJ_I_VOLUME) > (Stream_Depth * 100))
            {
                /* Nope, this will sink beneath the surface. Now, if
                 * the room is deep enough, we move it to our underwater
                 * room. If not, we just add a message
                 */
                if (query_deep_water())
                {
                    if (objectp(Underwater_Room))
                    {
                        tell_room(this_object(), capitalize(ob->short())
                          + " disappears beneath the surface with a splash,"
                          + " and is gone from sight.\n");

                        ob->move(Underwater_Room);
                        return;
                    }
                }

                /* The water isn't deep. Lets just add a message. */
                tell_room(this_object(), capitalize(ob->short())
                  + " disappears beneath the surface with a slash, but"
                  + " remains visible at the bottom of the " + Stream_Name
                  + ".\n");
            }

            return;
        }

        /* It floats! So ... lets add the alarm. */                        

        set_alarm(Flow_Speed, 0.0, &move_downstream(ob, this_object()));
    }
} /* enter_inv */


/*
 * Function name:        move_downstream
 * Description  :        move floating items downstream
 * Arguments    :        object ob - the floating item to move
 */
public void
move_downstream(object ob)
{
    if (!objectp(Downstream_Room))
    {
        tell_room(this_object()), capitalize(ob->short()
          + " swirls around on the surface of the water, moving with"
          + " the current, but doesn't go anywhere.\n");
        return;
    }

    tell_room(Downstream_Room, capitalize(ob->short()) + " arrives from"
      + " the " + Upstream_Dir + ", floating on the surface of the " 
      + Stream_Name + ".\n");
    ob->move(Downstream_Room);
    tell_room(this_object(), capitalize(ob->short()) + " floats past"
      + " and disappears to the " + Downstream_Dir + ".\n");
} /* move_downstream */


/*
 * Function name:        test_floatation
 * Description  :        Test an object to see if it will float. We assume
 *                       that anything with a volume to weight ratio
 *                       greater than that defined by WILL_FLOAT is
 *                       sufficient to keep it on the surface.
 * Arguments    :        object obj - the object to test
 * Returns      :        int - 1: it floats
 *                             0: it does not float
 */
public int
test_floatation(object obj)
{
    int    weight,
           volume;

    if (!objectp(obj)) /* sanity check */
    {
        return 0; /* invalid object */
    }

    weight = obj->query_prop(OBJ_I_WEIGHT);
    volume = obj->query_prop(OBJ_I_VOLUME);

    if (volume / weight >= WILL_FLOAT)
    {
        return 1; /* It'll float! */
    }

    return 0; /* Doesn't float */
} /* test_floatation */


/*
 * Function name:        query_deep_water
 * Description  :        Determine if this room has water deep enough to
 *                       have there be a separate room for underwater
 *                       purposes.
 * Returns      :        int - 1: deep enough
 *                             0: not deep enough
 */
public int
query_deep_water()
{
    return Stream_Depth >= DEEP_WATER;
} /* query_deep_water */
