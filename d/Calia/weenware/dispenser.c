// OBJECT:  dispenser

/* Calia Domain

HISTORY

[99/10/31] Created by Uhclem from [D:\CALIA\WEENWARE\DISPENSE.DOC].

PURPOSE

A cheese fuzzie dispenser for the domain office in the Tower of Realms.
This object is only used on Halloween.

TO DO

Put in a function to humorously punish players who abuse (spit, kick, etc.)
this device.

*/

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

// GLOBAL VARIABLES

object This_Room;   /*  room where this (immobile) device resides  */
object Active_Player;   /*  player who most recently pulled the lever  */
string *Players = ({"x"});  /*  list of players who have gotten a fuzzie  */
string *Effects = ({}); /*  text for motion effects; loaded later  */
int In_Motion = 0;  /*  nonzero while parts are in motion  */

// FUNCTIONS

// Function:  load_effects()

/*

Purpose:  load the text into the effects array; this function scrambles
elements so that a great variety of effects are generated.

Arguments:  none

Returns:  nothing

*/

void
load_effects()

{

    Effects =
        ({
        "A rod suddenly thrusts out from the machinery, misses you" +
        " by only a hair's breadth, then just as suddenly" +
        " retracts back into its original position.\n",
        "A puff of black smoke emerges from the device, and" +
        " you detect the distinct scent of brimstone.\n",
        "One of the cables flies off its pulley and lashes" +
        " wildly around the room, then it reels back into the" +
        " depths of the machinery with a" +
        " high-pitched screeching noise.\n",
        "One of the oblong chambers resonates with a grisly sound," +
        " as if bones were being broken inside it - bones still in" +
        " use by their owner!\n",
        "The hundreds of perfectly-meshed gears spin wildly," +
        " propelling the rods and wheels with a smooth" +
        " but ominous buzz.\n",
        "Heat emanates from the round chambers, at first" +
        " agreeably warming but then growing until the innards" +
        " of the machine begin to glow a malevolent" +
        " shade of crimson.\n",
        "All the parts of the machine go through their" +
        " motions as if participating in a weird, diabolical" +
        " ballet, all the sharp surfaces gyrating wildly in a" +
        " tumult of sharp points and keen edges.\n",
        "The keen-edged spinning wheels fan out from the center" +
        " of the device, supported by the expanding structure" +
        " of wheels and cables, and they press you" +
        " back into an ever-diminishing corner of the room.\n",
        "Flames burst forth from somewhere within the machinery" +
        " and singe your eyebrows!\n",
        "The floor and walls shake as the vibrations" +
        " from the machinery increase in" +
        " frequency and intensity.\n",
        "The flames in the oil-lamps flicker as the gyrating" +
        " machinery whips up turbulent air currents" +
        " in the room.\n",
        "A thunderous, persistent pounding reverberates from" +
        " deep within the device, rattling everything in the" +
        " room - including your teeth!\n",
        "Some of the gears shift position, clash violently as" +
        " the metal teeth struggle to mesh, then" +
        " lock into perfect synchronization, producing a" +
        " deafening wail that continues to rise in" +
        " pitch and volume.\n",
        "Sharp, staccato snaps and knocks jolt the machinery," +
        " yet it continues to accelerate and move its" +
        " myriad parts in ever-broader arcs.\n",
        "The rods move in and out in apparently random patterns" +
        " and at blinding speed, unquestionably blinding to" +
        " anyone who stands too close!\n",
        "Plumes of acrid smoke billow from all sections of" +
        " the machinery, and the heat and vibrations build so" +
        " rapidly that it seems likely the device is" +
        " about to explode.\n"
        });

}

// Function:  figure_description()

/*

Purpose:  return a description that will be particularly unpleasant for the
player looking at the figures.

Arguments:  none

Returns:  a string of disturbing text

*/

string
figure_description()

{

    return
        "The many fine figures etched into the metal surface" +
        " depict scenes of torture and death so horrible that" +
        " you avert your eyes almost immediately. Among all of" +
        " the figures, one disturbing image in particular" +
        " haunts you: " +
        ({"an unfortunate", "a terrified", "a hapless"})[random(3)] +
        " " + this_player()->query_race_name() +
        " being " +
        ({"dismembered by razor-sharp metal wheels",
        "ground to bits by powerful metal gears",
        "agonizingly stretched across pulleys and cables",
        "perforated by sharp metal rods",
        "crushed in a small oblong metal chamber",
        "roasted in a large round metal chamber"})[random(5)] +
        ".\n";

}

// Function:  lever_description()

/*

Purpose:  return the current lever description.

Arguments:  none

Returns:  string

*/

string
lever_description()

{

    if (In_Motion)

    {

        return
            "If there was a lever here, it must have" +
            " disappeared into the machinery.\n";

    }

    else

    {

        return
            "Made of shiny black metal like the rest of the machinery," +
            " it offers no clue as to its function other than" +
            " the command PULL prominently etched on it.\n";

    }

}

// Function:  set_stationary_desc()

/*

Purpose:  set the long and short descriptions of the dispenser when it is at
rest.

Arguments:  none

Returns:  nothing

*/

void
set_stationary_desc()

{

    set_long("The massive pile of machinery is comprised" +
        " of hundreds, perhaps thousands of parts. Wheels," +
        " gears, pulleys, and rods connect an intricate structure" +
        " of round and oblong chambers, all made of burnished" +
        " black metal. Only one part gives a meager hint" +
        " about the device's purpose: a single lever projects" +
        " toward you, and on the end of it is etched the word PULL.\n");

    set_short("huge mysterious device");

    In_Motion = 0;

}

// Function:  set_moving_desc()

/*

Purpose:  set the long and short descriptions of the dispenser when it is in
motion.

Arguments:  none

Returns:  nothing

*/

void
set_moving_desc()

{

    set_long("The massive pile of machinery rumbles ominously" +
        " as its hundreds, perhaps thousands, of parts" +
        " go through their assigned motions. Wheels, gears," +
        " pulleys, and rods turn, twist, and slide" +
        " within an intricate structure of round and oblong" +
        " chambers, all made of burnished black metal.\n");

    set_short("huge rumbling device with hundreds of moving parts");

}

// Function:  operate_dispenser()

/*

Purpose:  provide all the effects of the device's operation.  The routine calls
itself repeatedly with an alarm until the dispensing process is complete.

Arguments:  none.

Returns:  nothing.

*/

void
operate_dispenser()

{

    string *stop_text =
        ({
        "The device screeches to a sudden halt," +
        " its whirling and gyrating parts all seizing at once" +
        " as if some monstrous force had surged into" +
        " the room and slammed into it at high speed.\n",
        "The device grinds slowly to a halt, the rumble" +
        " of its whirling and gyrating parts growing" +
        " fainter and fainter until the last few vibrations fade" +
        " away in a forbidding shudder, vaguely" +
        " like a death rattle.\n",
        "All of the gyrating parts of the machine come to an" +
        " abrupt stop and withdraw to their original" +
        " positions in unison, and the cacophony of sounds" +
        " just as abruptly gives way to a gravelike silence.\n",
        "Two gears shift position and lock together with one" +
        " of the cables caught between them! The" +
        " resulting screech nearly flattens you with its" +
        " piercing high pitch, and your ears continue to ring" +
        " long after the machinery grinds to a halt and" +
        " all is silent.\n",
        });

    object fuzzie;
    string player_name = Active_Player->query_name();
    int selector;

    if (In_Motion)

    {

        selector = random(sizeof(Effects));
        tell_room(This_Room, Effects[selector]);
        Effects -= ({Effects[selector]});
        In_Motion -= 1;
        set_alarm(6.0, 0.0, operate_dispenser);

    }

    else

    {

        tell_room(This_Room, stop_text[random(sizeof(stop_text))]);
            set_stationary_desc();

        if (member_array(player_name, Players) == -1)

        {

            fuzzie = clone_object("/d/Calia/weenware/fuzzie");

            /*
             *  If the player is patient and waits for his cheese fuzzie, it 
             *  will be delivered directly into his hands; otherwise it's up
             *  for grabs.    
             */

            if (environment(Active_Player) == This_Room)

            {

                fuzzie->move(Active_Player);

                write("A cheese fuzzie tumbles out of the device" +
                    " and into your hands!\n");

                tell_room(This_Room,
                    "A cheese fuzzie tumbles out of the device" +
                    " and into " + QTNAME(Active_Player) + "'s hands!\n",
                    ({Active_Player}));

            }

            else

            {

                fuzzie->move(This_Room);

                write("A cheese fuzzie tumbles out of the device" +
                    " and falls on the floor.\n");

            }

        }

        /*
         *  So what's the point of the Players array anyway?  It looks as if 
         *  it's designed so that no player can get two fuzzies in a row, but
         *  two players taking turns can get all they want.

         *  They can.  Other than preventing one player from going alone to the
         *  office and collecting a bunch of fuzzies for his friends, the only
         *  other purpose of the array is to record the names of people who
         *  abuse the dispenser by kicking it, slapping it, or spitting on it.
         *  Their names get added to the end of the array, and they can't get a
         *  fuzzie until someone else has cleared it.    
         */

        if (Players[0] != player_name);

        {

            Players -= ({Players[0]});

        }

        Players += ({player_name});

    }

}

// Function:  pull_lever(string str)

/*

Purpose:  pull the lever and (maybe) dispense a cheese fuzzie.

Arguments:  string containing "lever".

Returns:  1/0.

*/

int
pull_lever(string str)

{

    string player_pronoun;
    string player_objective;
    string player_possessive;
    int dis;

    if (!str || !wildmatch("*lever", str))

    {

        notify_fail("Pull what?\n");
        return 0;

    }

    if (In_Motion)

    {

        write("Do not attempt to touch the device while" +
            " it is in motion!\n");

    }

    else

    {

        Active_Player = this_player();
        player_pronoun = Active_Player->query_pronoun();
        player_objective = Active_Player->query_objective();
        player_possessive = Active_Player->query_possessive();
        dis = Active_Player->query_stat(SS_DIS);

        /*
         *  Convert raw dis value to 0-4 range.    
         */

        dis = (dis > 15) + (dis > 30) + (dis > 60) + (dis > 120);

        write(
            ({
            "You grow pale and faint at the sight of" +
            " the monstrous machinery, but, barely able to" +
            " lift your trembling hand, you manage to get a grip" +
            " on the lever and give it a gentle pull.\n",
            "You gingerly approach the mysterious device," +
            " reach for the lever, and hesitate a moment." +
            " Then, closing your eyes and clenching your buttocks," +
            " you give it a great pull with all of your might!\n",
            "You step forward, check the device carefully for" +
            " any booby traps or wires, then grasp the lever" +
            " with both hands, make a mental note of which" +
            " ancestor you'd like to meet first, then pull down as" +
            " hard as you can!\n",
            "You clasp both hands around the lever and, pausing" +
            " only a moment to check your footing (and escape" +
            " path), pull down with a smooth, quick stroke.\n",
            "You march directly toward the machine, grasp" +
            " the lever, and, throwing caution to the wind" +
            " (who knows, perhaps your life as well), you give" +
            " it a powerful pull!\n"})[dis]);

        tell_room(This_Room,
            QCTNAME(Active_Player) + " " +
            ({
            "grows pale and faint at the sight of the" +
            " monstrous machinery, but, barely able to" +
            " lift " + player_possessive +
            " trembling hand, " + player_pronoun + " manages to get" +
            " a grip on the lever and give it a nervous pull.\n",
            "gingerly approaches the mysterious device, reaches" +
            " for the lever, and hesitates a moment. Then," +
            " closing " + player_possessive +
            " eyes and clenching " + player_possessive +
            " buttocks, " + player_pronoun + " gives it a great" +
            " pull with all of " + player_possessive + " might!\n",
            "steps forward, checks the device" +
            " carefully for any booby traps or wires, then" +
            " grasps the lever with both hands, pauses for a" +
            " moment to consider the" +
            " consequences of " + player_possessive +
            " impending action, then pulls down as" +
            " hard as " + player_pronoun + " can!\n",
            "clasps both hands around the lever and," +
            " pausing only a moment to check something just" +
            " behind " + player_objective + ", pulls down with" +
            " a smooth, quick stroke.\n",
            "marches directly toward the" +
            " machine, grasps the lever, and with a look" +
            " of wanton disregard for " + player_possessive +
            " safety (and yours as well) gives it" +
            " a powerful pull!\n"})[dis],
            ({Active_Player}));

        In_Motion = random(3) + 2;

        if (sizeof(Effects) < In_Motion)

        {

            load_effects();

        }

        set_alarm(3.0, 0.0, operate_dispenser);

        set_moving_desc();

    }

    return 1;

}

// Function:  enter_env(inv, from)

/*

Purpose:  used here to set the value of This_Room; called when this object
enters an environment.

Arguments:  none

Returns:  nothing

*/

void
enter_env(object env, object from)

{

    ::enter_env(env, from);
    This_Room = env;

}

// Function:  init()

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(pull_lever, "pull");

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("device");
    add_name("huge device");
    add_name("mysterious device");
    add_name("huge mysterious device");
    add_name("rumbling device");
    add_name("huge rumbling device");
    add_name("dispenser");

    /*
     *  Long and short descriptions are set by functions and vary depending on 
    whether the device is moving or not.  */

    set_stationary_desc();

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_M_NO_GET, "The device must be more than 100" +
        " times your weight. What will you try to do next -" +
        " take the whole tower?\n");

    add_prop(OBJ_I_VALUE, 10000000000);
    add_prop(OBJ_I_WEIGHT, 5000000000);
    add_prop(OBJ_I_VOLUME, 3000000000);

    /*
     *  ITEMS    
     */

    add_item(({"part", "parts"}),
        "The various wheels, gears, and rods are angled in all" +
        " directions, and you cannot hazard a guess as to which" +
        " way they will move if the machinery is set in" +
        " motion. They are, however, obviously made to" +
        " move freely, and many are razor-sharp.\n");

    add_item(({"pile", "pile of machinery", "machinery"}),
        "The massive device squats ominously before you, a" +
        " leviathan of black metal that may have come straight" +
        " from Hell's own forge.\n");

    add_item(({"wheel", "wheels"}),
        "The wheels have keenly sharpened edges, and they" +
        " are decorated with fine figures etched into" +
        " the black metal.\n");

    add_item(({"gear", "gears"}),
        "The many gears come in all sizes, all milled with" +
        " great precision so that they mesh perfectly. Fine" +
        " figures are etched into them wherever space allows.\n");

    add_item(({"pulley", "pulleys"}),
        "The pulleys are made of the same black metal as the" +
        " rest of the enormous device, and their" +
        " surfaces have painstakingly etched with fine" +
        " figures. They support strong cables that descend into" +
        " the bowels of the device.\n");

    add_item(({"cable", "strong cable", "cables", "strong cables", }),
        "The cables are looped around pulleys, but their" +
        " function is unclear since most of their length is" +
        " obscured by the machinery.\n");

    add_item(({"rod", "rods", "point", "sharp point",
        "points", "sharp points"}),
        "Many rods extend from the machine, all ending" +
        " in menacing sharp points. It strikes you as odd that," +
        " no matter where you stand in the room, they always" +
        " seem to be predominantly aimed in your direction.\n");

    /*
     *  Many thanks to Bishop for inventing my favorite unit of measurement. 
      
     */

    add_item(({"chamber", "chambers", "round chamber", "round chambers",
        "oblong chamber", "oblong chambers"}),
        "Some chambers are round, some are oblong, and their" +
        " sizes range from no bigger around than a gnome's" +
        " head to larger around than several dozen gnomes'" +
        " heads neatly stacked in a pyramid. Nothing about them" +
        " gives you any clue to their purpose other than" +
        " the fine figures etched into their surfaces.\n");

    add_item(({"metal", "black metal",
        "burnished black metal", "shiny black metal"}),
        "The metal gleams strangely, its surface utterly" +
        " black yet highly reflective, as if it were permeated" +
        " with some infernal magic.\n");

    add_item(({"figure", "fine figure", "surface",
        "figures", "fine figures", "surfaces"}),
        "@@figure_description@@");

    add_item(({"lever", "single lever"}),
        "@@lever_description@@");

    /*
     *  SET GLOBAL VARIABLE    
     */

    This_Room = environment();

    /*
     *  "uid" settings required for cloning cheese fuzzies.    
     */

    setuid();
    seteuid(getuid());

}
