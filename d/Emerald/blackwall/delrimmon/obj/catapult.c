/*
 *  /d/Emerald/blackwall/delrimmon/obj/catapult.c
 *
 *  This device will be strewn along the ledge of the western cliffs,
 *  originally used as a defense against intruders on the lake. Only
 *  one shall actually function.
 *
 *  Copyright May 1997 by Gorboth (Cooper Sherry)
 */
#pragma strict_types

inherit "/std/container.c";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

// Definitions
#define REQUIRED_STRENGTH    70     
#define LANDING_LOCS  ({ (DELRIMMON_DIR + "lakeside/w_shore1"),\
                         (DELRIMMON_DIR + "lakeside/w_shore2"),\
                         (DELRIMMON_DIR + "lakeside/w_shore3"),\
                         (DELRIMMON_DIR + "lakeside/w_shore4"),\
                         (DELRIMMON_DIR + "lakeside/w_shore5"),\
                             })

// Global Variables
int     Functioning = 0,  //  Is this a working catapult?
        Fired       = 0,  //  Has the catapult been fired?
        Loaded      = 0,  //  Is the catapult loaded?
        Msg_alarm   = 0,
        Msg_stage   = 0;
string  Function_msg;
mixed   Contents    = 0;  // What is loaded into the catapult?

// Prototypes
string  describe();
string  beam_desc();
string  lever_desc();
string  platform_desc();
string  basin_desc();
string  mechanism_desc();
string  ammo_desc();
mixed   catapult_try_remove();
mixed   catapult_try_insert();

public void    set_function_msg(string s) { Function_msg = s; }
public void    set_functioning(int i) { Functioning = i; }
public void    set_fired(int i) { Fired = i; }
public void    set_loaded(int i) { Loaded = i; }

/*
 * Function name:    create_container
 * Description  :    set up the contianer
 */
void
create_container()
{
    set_name("catapult");
    set_short("ancient catapult");
    add_name(({"device","weapon","structure"}));
    add_adj(({"ancient"}));
    set_long(describe);

    add_item(({"beam","arm","beams","arms"}), beam_desc);
    add_item(({"lever","levers","long lever","long levers"}),
             lever_desc);
    add_item(({"platform","platforms","large platform",
               "large platforms"}), platform_desc);
    add_item(({"basin","basins","metal basin","metal basins",
               "cupped metal basin","cupped metal basins",
               "cupped basin","cupped basins"}), basin_desc);
    add_item(({"mechanism","mechanisms","gear","gears",
               "spring","spring mechanism","iron spring"}),
               mechanism_desc);
    add_item(({"bundle","leather bundle"}), ammo_desc);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_VOLUME, 1000000);     // The catapult is massive,
    add_prop(CONT_I_MAX_VOLUME, 1001000); // yet can hold very little.
    add_prop(CONT_I_WEIGHT, 2000000);     // It weighs many tons,
    add_prop(CONT_I_MAX_WEIGHT, 2100000); // and can support some weight.

    add_prop(OBJ_M_NO_GET, BSN(
        "At over fifteen feet in length, and weighing many tons,"
      + " there is no chance of ever lifting this device."));
    add_prop(CONT_M_NO_REM, catapult_try_remove);
    add_prop(CONT_M_NO_INS, catapult_try_insert);

    FIX_EUID
} /* create_container */

/*
 * Function name: describe
 * Description  : This function returns a string message
 *                dependant upon the state of the catapult.
 * Arguments    : None
 * Returns      : string description for set_long()
 */
string
describe()
{
    string cat_desc;

    if (Functioning)
    {
        if (Fired)
        {
        cat_desc = "This structure seems to have been recently put to"
                 + " use after centuries of neglect. A large beam at its"
                 + " center has been shorn in two by what must have"
                 + " been a great force of motion. The stump of the beam"
                 + " now stands erect, its splintered end rising from"
                 + " a mechanism which has been ground to smithereens"
                 + " by recent violence. The"
                 + " entire structure is supported by a large platform"
                 + " which has been nearly rent in half by fresh cracks on"
                 + " its surface.";
        }

        else
        {
        cat_desc = "It is obvious from looking at this structure that"
                 + " it has remained unused for hundreds of years."
                 + " Despite the age and weathering, this device looks"
                 + " as if it has avoided damage to any of its major"
                 + " components over the centuries. A large beam at"
                 + " its center is locked in place by a mechanism"
                 + " which connects to a long lever. The entire catapult"
                 + " is supported by a large platform which now rests"
                 + " mostly beneath the dirt.";
        }
    }

    else
    {
        cat_desc = "This structure must once have been a powerful"
                 + " means of artillery. A large beam at its center"
                 + " stands erect from a platform which supports the"
                 + " entire machine. Below the beam is a mechanism which"
                 + " connects to a long lever at the side of the"
                 + " platform. Centuries of weather and neglect seem"
                 + " to have taken their toll on this weapon, as it is"
                 + " quite obviously beyond repair.";
    }

    return BSN(cat_desc);
} /* describe */

/*
 * Function name:    query_catapult_vars
 * Description  :    provides variable info for debugging
 * Returns      :    string -- the variable values
 */
string
query_catapult_vars()
{
    return "Catapult varable values:\n"
         + "------------------------\n"
         + " Functioning: " + Functioning + "\n"
         + " Fired: " + Fired + "\n"
         + " Loaded: " + Loaded + "\n"
    ;
} /* query_catapult_vars */

/*
 * Function name: catapult_try_remove
 * Description  : Prevents players from removing objects
 *                which are supposedly in flight.
 * Arguments    : None
 * Returns      : string if Fired, 0 otherwise
 */
mixed
catapult_try_remove()
{
    if (!sizeof(all_inventory(TO)))
        return 0;

    if (Fired)
    {
        return BSN("Whatever used to be in the basin is now flying"
             + " through the air towards the lake and quite out"
             + " of reach.");
    }

    return 0;
} /* catapult_try_remove */

/*
 * Function name: catapult_try_insert
 * Description  : determines whether the catapult is in a state
 *                capable of receiving objects into its
 *                inventory.
 * Arguments    : None
 * Returns      : string if Fired or !Functioning, 0 otherwise
 */
mixed
catapult_try_insert()
{
    if (Fired)
    {
        return BSN("The arm of this catapult has been shorn in two,"
          + " and there is no sign of the basin into which you might"
          + " have loaded such things.");
    }

    if (!Functioning)
    {
        return BSN("The arm of the catapult rises vertically from"
          + " the platform, making it impossible to keep such things"
          + " from sliding out of the basin.");
    }

    return 0;
} /* catapult_try_insert */

/*
 * Function name: catapult_contents
 * Returns      : a string message of the contents of the catapult
 */
string
catapult_contents()
{
    return COMPOSITE_LIVE(all_inventory(TO));
} /* catapult_contents */

/*
 * Function name:    enter_inv
 * Description  :    if the player put the special catapult ammunition
 *                   in the catapult, then we set Loaded to true
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("_em_shell"))
    {
        Loaded = 1;
        find_living("gorboth")->catch_msg("Ammunition loaded!\n");
    }

    return;
} /* enter_inv */

/*
 * Function name:    leave_inv
 * Description  :    since the catapult has been fired, we set the
 *                   value of Loaded to 0
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->id("_em_shell"))
    {
        Loaded = 0;
        find_living("gorboth")->catch_msg("Ammunition unloaded!\n");
    }

    return;
} /* leave_inv */

public int
load_catapult(string str)
{
    mixed   fail;
    object  obj;

    if (!strlen(str))
    {
        NFN0("What do you wish to load?");
    }

    if (!(parse_command(str, all_inventory(TP),
        "[the] [ancient] 'catapult' / 'device' 'with' %o", obj)))
    {
        // parse_command() failed
        NFN0("What do you wish to load with what?");
    }

    // check properties!
    if (fail = obj->query_prop(OBJ_M_NO_DROP))
    {
        if (!stringp(fail))
            fail = "You cannot load the "+obj->short()+", as it cannot"
                 + " be dropped!\n";
        NF(fail);
        return 0;
    }

    if (Fired)
    {
        NFN0("The arm of this catapult has been shorn in two,"
          + " and there is no sign of the basin into which you might"
          + " have loaded such things.");
    }

    if (!Functioning)
    {
        NFN0("The arm of the catapult rises vertically from"
          + " the platform, making it impossible to keep such things"
          + " from sliding out of the basin.");
    }

    switch(obj->move(TO))
    {
        case 0:
            break;
        case 1:
        case 8:
            NFN0("The " + obj->short() + " will not fit into the"
               + " basin of the catapult.");
            break;
        case 2:
            NFN0("The " + obj->short() + " can not be dropped.");
            break;
        case 3:
            NFN0("You will need to take it out of its current"
               + " container first.");
            break;
        default:
            NFN0("The state the catapult is in prevents it from"
              + " holding anything.");
            break;
    }

    TP->catch_msg("You load the basin of the catapult with the "
      + obj->short() + ".\n");
    tell_room(ENV(TO), QCTNAME(TP) + " loads the basin of the"
      + " catapult with " + LANG_ADDART(obj->short()) + ".\n", TP);

    return 1;
}

string
ammo_desc()
{
    string  ammo_txt;

    if (!Loaded)
    {
        ammo_txt = "You find no bundle.";
    }

    else
    {
        ammo_txt = "You see a tightly wrapped leather bundle in"
                 + " the cupped metal basin of the catapult.";
    }

    return BSN(ammo_txt);
}

string
beam_desc()
{
    string  beam_txt;

    if (Functioning)
    {
        if (Fired)
        {
            beam_txt = "The arm of the catapult has been reduced"
                     + " to nothing more than a splintered stump"
                     + " which rises from a now broken firing"
                     + " mechanism beneath it. There is no sign"
                     + " of the upper portion of the beam.";
        }

        else
        {
            beam_txt = "The arm of the catapult is rigidly locked"
                     + " into firing position, held soundly by"
                     + " a release mechanism at its base which"
                     + " seems to be connected to a long lever at"
                     + " the side of the weapon. Fixed at the end of"
                     + " the beam is a cupped metallic basin which looks"
                     + " large enough to hold a medium sized artillery"
                     + " shell.";
        }
    }

    else
    {
        beam_txt = "The arm of this catapult rises at nearly"
                 + " ninety degrees from the base of the platform."
                 + " Atop the long beam is fixed a cupped metal"
                 + " basin large enough to hold a medium sized"
                 + " artillery shell.";
    }

    return BSN(beam_txt);
}

string
lever_desc() 
{
    string  lever_txt;

    if (!Functioning || Fired)
    {
        lever_txt = "The lever rises at an angle from a slot near to the"
                  + " side of the platform which the catapult is mounted"
                  + " upon. It hangs loosely in place, and does not seem"
                  + " to be well connected to anything.";
    }

    else
    {
        lever_txt = "The lever rises from a slot near to the side of"
                  + " the platform which the catapult is mounted upon."
                  + " It looks to be fixed rigidly in place.";
    }

    return BSN(lever_txt);

}

string
platform_desc()
{
    string  platform_txt;

    if (Fired)
    {
        platform_txt = "What was perhaps once a firm and level surface"
                     + " area now droops heavily due to numerous deep"
                     + " and wide cracks in the surface of the thick"
                     + " wood. The platform extends beneath the entirety"
                     + " of the catapult, intended to both support its"
                     + " weight, and level its pitch of motion.";
    }

    else
    {
        platform_txt = "The platform which supports the catapult is"
                     + " composed of many thick beams of wood bound"
                     + " almost seamlessly together to form a firm and"
                     + " level surface for the artillery engine. Years"
                     + " of weather and neglect have left its surface"
                     + " marred, yet intact.";
    }

    return BSN(platform_txt);
}

string
mechanism_desc()
{
    string mechanism_txt;

    if (Functioning)
    {
        if (Fired)
        {
        mechanism_txt = "The mechanism housed beneath the beam has been"
                      + " recently destroyed by what would appear to"
                      + " have been an extremely violent motion of some"
                      + " kind. Freshly stripped gears lie ground to"
                      + " pieces amidst the remains of a thick iron"
                      + " spring mechanism.";
        }

        else
        {
        mechanism_txt = "The mechanism housed beneath the beam of this"
                      + " weapon is comprised of numerous gears set"
                      + " around a tightly bound spring mechanism. The"
                      + " thick iron of the spring mechanism as well"
                      + " as the metal of the gears has been corroded"
                      + " by years of weathering in both sun and rain.";
        }
    }

    else
    {
        mechanism_txt = "The mechanism housed beneath the beam of this"
                      + " weapon is comprised of numerous gears set"
                      + " around a loosely wrapped spring mechanism."
                      + " A thick coating of rust is layered over the"
                      + " thick metal of the iron spring, and coats"
                      + " the gears from top to bottom.";
    }

    return BSN(mechanism_txt);
}

string
basin_desc()
{
    string  basin_txt = "The basin fixed at the end of the beam on"
                      + " this catapult is cupped like a massive spoon,"
                      + " and looks as if it could hold a medium sized"
                      + " artillery shell.";

    if (sizeof(all_inventory(TO)))
    {
        basin_txt += " Resting within the basin is "
                   + catapult_contents() + ".";
    }

    if (Fired)
    {
        basin_txt = "You find no basin.";
    }

    return BSN(basin_txt);
}

int
check_strength(object actor)
{
    int     needed = REQUIRED_STRENGTH + (random(5) - 5);

    if (actor->query_stat(SS_STR) > needed)
        return 0;

    else return 1;
}

int
explosion(object actor)
{
    string  explosion_txt = "A thunderous boom echoes suddenly"
                          + " throughout the area.";

    tell_players_in_same_subdir(actor, BSN(explosion_txt));
    return 1;
}

void
launch_missile(object actor)
{
    string  launch_txt;
    object  destination_room;

    destination_room = ONE_OF_LIST(LANDING_LOCS)->get_this_object();


find_living("gorboth")->catch_msg("launch_missle called.\n");
    switch(Msg_stage)
    {
        case 1:
            launch_txt   = "Years of neglect are wiped away in an"
                         + " instant as the great arm of the catapult"
                         + " swings forward with terrible force and"
                         + " speed,";

            if (sizeof(all_inventory(TO)))
            {
                launch_txt += " hurling " + catapult_contents()
                  + " high into the air, and";
            }

            launch_txt += " snapping off the upper portion of the"
                         + " beam, which flies off over the treetops in"
                         + " the direction of the lake shore.\n";
            tell_room(ENV(TO), BSN(launch_txt) );
            Fired = 1;
            destination_room->catapult_arm_landing(destination_room);
            destination_room->clone_catapult_orcs();
            break;
        case 6:
            if (!Loaded)
            {
                if (sizeof(all_inventory(TO)))
                {
                    tell_room(ENV(TO), BSN("The former contents of the"
                      + " metal basin arc downwards towards the surface"
                      + " of the lake, and plummet with a distant"
                      + " splash into the waters of Del Rimmon."));
                    all_inventory(TO)->remove_object();
                }
                break;
            }

            tell_room(ENV(TO), "The leather bundle soars in a high arcing"
                             + " motion far out over the lake in the"
                             + " direction of Ael Rannath.\n\n");
            break;
        case 9:
            if (!Loaded)
            {
                break;
            }

            tell_room(ENV(TO), "A thunderous boom echoes throughout the"
                             + " Blackwall Mountains as the bundle collides with"
                             + " the near side of Ael Rannath, sending"
                             + " a great plume of smoke into the air, and"
                             + " a cascade of small boulders showering"
                             + " down into the water of the lake"
                             + " below.\n");
            all_inventory(TO)->remove_object();
            explosion(TO);
            break;
        case 10:
        case 999:
            remove_alarm(Msg_alarm);
            Msg_alarm = 0;
            Msg_stage = 0;
            break;
        default:
            break;
    }

    Msg_stage++;
    return;
}

int
fire_catapult(object actor)
{
find_living("gorboth")->catch_msg("fire_catapult called.\n");
    if (!Msg_alarm || !sizeof(get_alarm(Msg_alarm)))
    {
find_living("gorboth")->catch_msg("if !Msg_alarm = true.\n");
        Msg_alarm = set_alarm(1.0, 2.0, &launch_missile(actor));
    }

    return 1;
}

int
pull_lever(string str)
{
    object  actor = this_player();

    if (!strlen(str))
        NFN0("Pull what?");

    if (str != "lever")
        NFN0("What do you wish to pull?");

    if (Fired || !Functioning)
    {
        write(BSN("The lever slides limply in its slot. Pulling"
           + " it seems to be of no use."));

        return 1;
    }

    if (check_strength(actor))
    {
        write(BSN("You pull with all your might upon the lever, but you"
            + " do not seem strong enough to move it."));
        say(QCTNAME(actor) + " strains to pull the long lever"
          + " of the catapult, but it will not budge.\n");

        return 1;
    }

    write(BSN("Mustering your strength, you strain mightily against"
            + " the rusted gears of the catapult and succeed in pulling"
            + " the long lever backwards."));
    say(QCTNAME(actor) + " strains mightily against the long lever"
          + " mounted on the side of the catapult, pulling it suddenly"
          + " backwards.\n");

    fire_catapult(actor);

    return 1;
}

int
repair_catapult(string str)
{
    if (!strlen(str))
        NFN0("Repair what?");

    if (str != "catapult")
        NFN0("What do you wish to repair?");

    if (!Functioning || Fired)
    {
        if (TP->query_race() == "gnome")
        {
            NFN0("Rubbing your hands with eager delight, you begin"
               + " to frantically mess with the inner workings of"
               + " the catapult. After a moment or two you realize"
               + " it is hopeless, and grumble to yourself about how"
               + " the designers should definately have included"
               + " more BellsAndWhistlesAndStuff.");
        }

        NFN0("To repair this catapult would require skills far beyond"
           + " anything you could ever hope to possess.");
    }

    write(BSN("Actually, this catapult seems to be in a generally"
            + " good condition."));
    return 0;
}

void
init()
{
    ::init();

    add_action(pull_lever, "pull");
    add_action(repair_catapult, "repair");
    add_action(repair_catapult, "fix");
    add_action(load_catapult, "load");
    add_action(load_catapult, "wiz_load");
}
