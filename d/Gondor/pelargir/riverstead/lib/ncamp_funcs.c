/*******************************************************************************
 *  NCAMP + "ncamp_funcs.c"
 *
 *  Various functions common to Isengard rooms.
 *
 *  Last modified by Alto, 23 September 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../ncamp_defs.h"

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"

/* PROTOTYPES */

public string    sky_desc();
public int       sky_add_items();
public int       woods_add_items();
public void      add_woods_tells();
public int       hut_add_items();
public int       camp_add_items();
public int	 east_camp_add_items();
public int	 dock_add_items();
public void      add_camp_tells();
public void	 add_east_camp_tells();
public void	 add_dock_tells();
public void	 replace_humans(int i);

string           sky_text;
object           actor;
int		 defence_status;

public string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        sky_text = " An ocean of stars blankets the deep night sky above";
        switch (clock->query_moon())
        {
        case "full":
            sky_text += ", surrounding the pale brightness of the full moon."; 
            break;
        case "waxing crescent":
            sky_text += " as the crescent moon begins to rise.";
            break;
        case "waxing gibbous":
            sky_text += " as the nearly full moon rises over the horizon."; 
            break;
        case "waning gibbous":
            sky_text += ". The moon, slightly past full, casts a pale "
            + "glow over the area."; 
		          break;
        case "waning crescent":
            sky_text += " as the moon tilts its sharp horns over the dark "
              + "landscape."; 
            break;
        default:
            sky_text += ", but the moon cannot be seen.";
            break;
        }
        break;
    case "afternoon":
        sky_text = " The afternoon sun glows warmly in the sky.";
        break;
    case "morning":
        sky_text = " The morning sun is riding low in the eastern horizon.";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead.";
        break;
    case "evening":
        sky_text = " The sun is sinking into the western horizon, bathing "
          + "the area in deep orange light.";
        break;
    case "early morning":
        sky_text = " The first rays of sun are peeking over the eastern "
          + "horizon.";
        break;
    default:
        sky_text = " The sky is obscured by gathering clouds.";
        break;
    }
    return (sky_text);
}


public int
sky_add_items()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    
    TO->remove_item("sky");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("moon");
    TO->remove_item("end");

    switch (time)
    {
    case "night":
 
        add_item(({"star", "stars"}), "The stars blanket the deep night "
            + "sky.\n");
        add_item(({"sky", "night sky"}), "The night sky is illuminated by "
            + "numerous twinkling stars.\n");
        switch (clock->query_moon())
        {
        case "full":
            add_item(({"moon", "full moon"}), "The bright round moon shines "
                + "down from the night sky.\n"); 
            break;
        case "waxing gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has almost "
                + "reached its full phase and will likely peak within a "
                + "few days.\n"); 
            break;
        case "waning gibbous":
            add_item(({"moon", "nearly full moon"}), "The moon has passed "
                + "its full phase and grows increasingly less illuminating "
                + "with the passing of days.\n"); 
            break;
        case "waxing crescent":
        case "waning crescent":
            add_item(({"moon", "crescent moon"}), "The crescent moon hangs "
                + "low upon the horizon, its sharp ends dangling with the "
                + "tilt of its axis.\n");
            add_item(({"end", "ends"}), "The ends of the moon dangle "
                + "with the tilt of its axis.\n");
            break;
        default:
            break;
        }
        break;
    case "afternoon":
        add_item(({"sky", "afternoon sky"}), "The afternoon sky is lit "
            + "by the warm light of the sun.\n");
        add_item(({"sun", "afternoon sun"}), "The afternoon sun shines "
            + "down upon the landscape.\n");
        break;
    case "morning":
        add_item(({"sky", "morning sky"}), "The morning sky is lit "
            + "by the growing light of the sun.\n");
        add_item(({"sun", "morning sun", "horizon", "eastern horizon"}), 
            "The morning sun rides low in the eastern horizon.\n");
        break;
    case "noon":
        add_item(({"sky", "noon sky"}), "The noon sky is illuminated by "
            + "the gentle light of the sun directly overhead.\n");
        add_item(({"sun", "noon sun"}), "The noon sun is directly overhead.\n");
        break;
    case "evening":
        add_item(({"sky", "evening sky"}), "The evening sky is lit "
            + "by the fading light of the sinking sun.\n");
        add_item(({"sun", "evening sun", "horizon", "western horizon"}), 
            "The evening sun is sinking into "
            + "the western horizon.\n");
        break;
    case "early morning":
        add_item(({"sky", "early morning sky"}), "The morning sky is lit "
            + "by the first rays of the rising sun.\n");
        add_item(({"sun", "early morning sun", "morning sun", "horizon",
            "eastern horizon", "rays", "ray"}), "The early morning sun "
            + "is just peeking over the eastern horizon.\n");
        break;
    default:
        add_item(({"sky", "clouds", "gathering clouds"}), "The sky is "
            + "obscured by gathering clouds.\n");
        break;
    }
    return 1;
}


public int
woods_add_items()
{
    add_item(({"ground", "floor"}), "The ground here is relatively soft "
        + "and springy from the moss and humous of the woodland "
        + "floor. The smell of clean earth rises from it.\n");
    add_item(({"tree", "trees", "oak tree", "oak trees"}),
        "The trees are primarily species of oak. They cast a pleasant "
        + "shade over the path, and yet permit a view of the sky "
        + "over southern Gondor.\n");
    add_item(({"squirrel", "squirrels", "grey squirrel", "grey squirrels"}), 
        "Grey squirrels scamper about in the trees, chittering above "
        + "your head. Occasionally leaves and acorns fall to the ground "
        + "in their wake.\n");
    add_item(({"leaf", "leaves", "acorn", "acorns", "nut", "nuts"}),
        "The trees in this part of Gondor retain their leaves through "
        + "most of the year. There are also many clusters of acorns "
        + "to be seen in the trees. That must be why so many squirrels "
        + "live here.\n");
    add_item(({"root", "roots"}), "The strong roots of the oak trees "
        + "can be seen here and there, pushing up through the ground.\n");
    add_item(({"vine", "vines"}), "Long green and brown vines snake "
        + "across the ground here and there. Those crossing the path "
        + "catch your foot now and then.\n");
    add_item(({"path", "narrow path", "trail"}), "The path beneath "
        + "your feet twists "
        + "and turns its way through the trees. You get the distinct "
        + "impression it was made by animals but has since been used by "
        + "people.\n");
    add_item(({"moss", "green moss", "carpet", "carpet of moss"}),
        "A carpet of green moss covers the floor of the woodland.\n");
    add_item(({"humous", "soil"}), "The soil here is composed of rich "
        + "humous. It feels moist and is quite pungent.\n");

    return 1;
}

void
add_woods_tells()
{
    set_tell_time(120);

    add_tell("A squirrel chitters and barks from the trees above.\n");
    add_tell("A gentle breeze stirs the woodland air.\n");
    add_tell("The clean scent of damp earth fills your nostrils.\n");
    add_tell("An acorn bounces off your head.\n");
    add_tell("Birds chirp and sing somewhere in the distance.\n");
    add_tell("The chorus of cicadas rises in the woods around you.\n");
    add_tell("The breeze suddenly dies, leaving the woods still and quiet.\n");
    add_tell("The leaves on the trees rustle in a sudden breeze.\n");
    add_tell("A few leaves flutter to the ground.\n");
    add_tell("A salamander scurries off the path and disappears beneath "
        + "the roots of a tree.\n");
    add_tell("You startle a deer. It dashes away through the trees and is "
        + "quickly lost from sight.\n");
}

public int
hut_add_items()
{
    add_item(({"walls", "wall", "east wall", "west wall", "north wall", 
        "south wall", "wooden walls"}), "The walls of the hut are made "
        + "from rough-hewn wood, held together by pegs and mud.\n");
    add_item(({"peg", "pegs"}), "Large pegs of wood have been driven "
        + "into the boards that make up the walls of the hut. Without "
        + "them, it is doubtful the mud would be sufficient to hold "
        + "the walls up.\n");
    add_item(({"mud"}), "Mud slathered between the boards served as "
        + "sufficient mortar to hold the wall together. However, without "
        + "the pegs driven through them, the boards of the wall would "
        + "undoubtedly collapse.\n");
    add_item(({"board", "boards"}), "The boards making up the wall are "
        + "little more than rough-hewn timber from the nearby woodland.\n");
    add_item(({"window", "windows"}), "The windows of the hut are curtained "
        + "with coarse fabric and completely lack glass or shutter. The "
        + "relatively mild climate of southern Gondor requires neither.\n");
    add_item(({"floor", "ground"}), "The floor of the hut, like the walls, "
        + "has been constructed of rough-hewn timber.\n");
    add_item(({"timber", "rough-hewn timber"}), "The entire hut is composed "
        + "of timber cut from the nearby woodland and crudely milled by "
        + "the rustic craftsmen of the settlement.\n");
    add_item(({"door", "doorway", "entrance"}), "The door to the hut has "
        + "been thrown wide.\n");
    add_item(({"ceiling"}), "The ceiling of the room is supported by "
        + "several large beams of oak.\n");
    add_item(({"beams", "beams of oak"}), "The beams supporting the "
        + "ceiling are made from rough-hewn oak, much like the rest of "
        + "the hut.\n");
    add_item(({"curtain", "curtains", "fabric"}), "Threadbare fabric "
        + "covers the windows, fluttering in the gentle breeze. No glass "
        + "or pane can be seen behind the fabric.\n");
    
    return 1;
}


public int
camp_add_items()
{
    add_item(({"ground", "floor", "road", "path"}), "The ground here "
        + "is bare and muddy in some places. There is almost no grass "
        + "growing between the huts, a sign that this area is heavily "
        + "traversed by the settlers dwelling in the village.\n");
    add_item(({"tree", "trees", "oak tree", "oak trees"}),
        "There are few trees growing within the settlement itself. Thick "
        + "stands of oak, however, can be seen to the west beyond the "
        + "settlement. There is also a forest growing on the far side "
        + "of the Anduin.\n");
    add_item(({"forest"}), "On the far side of the river can be seen "
        + "a dark forest. Every now and then you spy a swarthy figure "
        + "moving through the trees.\n");
    add_item(({"hut", "huts", "dwelling", "dwellings", "cabin",
        "cabins", "house", "houses"}), "The settlement is comprised of "
        + "numerous small huts made from rough-hewn timber. Few of "
        + "the dwellings look more than simple structures used only "
        + "to keep out the elements.\n");
    add_item(({"timber", "rough-hewn timber", "board", "boards"}),
        "The huts are built from timber crudely fashioned into boards "
        + "by local craftsmen.\n");
    add_item(({"river", "river anduin", "anduin"}), "The mighty river "
        + "Anduin flows along the eastern edge of the settlement. The "
        + "river is broad and wide here, making its rapid way down to "
        + "the Bay of Belfalas and from there onward to the Sea.\n");
    add_item(({"figure", "figures", "swarthy figure", "swarthy figures"}), 
        "On the far bank of the Anduin can be seen figures moving "
        + "through the trees. No doubt a large company of orcs is "
        + "mustering for an invasion of Gondor.\n");
    add_item(({"bank", "banks"}), "The bank of the Anduin is steep. "
        + "For many ages the mighty river has carved away the landscape.\n");
    add_item(({"water"}),
        "The water in the river is cool, clean and swift.\n");
    add_item(({"dirt", "mud", "muck"}), "The dirt beneath your feet is "
        + "damp in "
        + "most places. A reasonable amount of mud in its center ensures "
        + "you will leave this place sufficiently dirty about the "
        + "ankles.\n");
    add_item(({"smoke"}), "Smoke billows from the windows of some of the "
        + "huts. You sense that the settlement is in grave danger of "
        + "burning to the ground.\n");
    add_item(({"window", "windows"}), "None of the windows on "
        + "the huts are made of glass, and most are covered only "
        + "by tattered lengths of fabric. Some of the windows "
        + "presently have smoke pouring from them.\n");
    add_item(({"door", "doors"}), "Most of the huts have only a single "
        + "door.\n");
    add_item(({"horizon"}), "There it is, right between the sky and the "
        + "ground.\n");
    add_item(({"roof", "roofs"}), "The roofs of the huts are made from "
        + "rough-cut timber. Smoke can be seen rising from many of the "
        + "hut roofs.\n");
    add_item(({"fabric", "curtains"}), "The windows of the huts are "
        + "for the most part covered with frayed lengths of old fabric. "
        + "Here is southern Gondor, such coverings are generally "
        + "sufficient to keep out the mild chills of night.\n");

    return 1;
}

public int
east_camp_add_items()
{
    add_item(({"ground", "floor", "road", "path"}), "The ground here "
        + "is a morass of mud, muck and ash. It is littered with debris "
        + "from the huts that have burned and collapsed.\n");
    add_item(({"debris", "chunks", "chunks of wood"}),
        "Smoldering chunks of wood litter the ground.\n");
    add_item(({"hut", "huts", "dwelling", "dwellings", "cabin",
        "cabins", "house", "houses", "heap", "heaps"}), 
        "Though the huts to the "
        + "west are still standing, those here have burned to the "
        + "ground.\n");
    add_item(({"dock", "docks"}), "To the east you see several small "
        + "docks extending from the west bank of the Anduin. Each now "
        + "has several crude rafts tied to it.\n");
    add_item(({"raft", "rafts"}),
        "They are crude, made from rough cuts of wood tied together "
        + "at the ends. The men of Gondor would not make such awkward "
        + "crafts. No doubt these were used to transport invading orcs "
        + "from the far shore.\n");
    add_item(({"smoke"}), "Smoke rises from the smouldering heaps of "
        + "what were once the huts lived in by settlers.\n");
    remove_item(({"window", "windows"}));
    remove_item(({"door", "doors"}));
    add_item(({"horizon"}), "There it is, right between the sky and the "
        + "ground.\n");
    remove_item(({"roof", "roofs"}));
    remove_item(({"fabric", "curtains"}));
    add_item(({"spark", "sparks"}), "Sparks snap and pop in the fires "
        + "all around you.\n");
    add_item(({"fire", "flames", "flame", "fires"}), "This part of the "
        + "settlement was almost entirely destroyed by flames leaping "
        + "from hut to hut.\n");

    return 1;
}

public int
dock_add_items()
{
    add_item(({"ground", "floor", "boards"}), "The floor of the dock "
        + "is made from the same rough-cut timber as the huts in "
        + "the village.\n");
    add_item(({"timber", "rough-cut timber"}), "It rocks precariously "
        + "beneath your feet.\n");
    add_item(({"rope"}),
        "The rafts are secured to the dock with knotted rope.\n");
    add_item(({"raft", "rafts", "crude raft", "crude rafts", "boat",
        "boats"}), "The rafts were obviously constructed in a hurry "
        + "and with little skill. It is surprising they stayed "
        + "afloat long enough to bear the orcs across the river.\n");
    add_item(({"river", "anduin", "river anduin"}), "The mighty "
        + "Anduin rushes by below and beyond the small dock. Its "
        + "great current causes the dock to rock dangerously back "
        + "and forth.\n");
    add_item(({"smoke"}), "Smoke rises from the smouldering heaps of "
        + "what were once huts lived in by settlers.\n");
    add_item(({"horizon"}), "There it is, right between the sky and the "
        + "ground.\n");
    add_item(({"hut", "huts", "ruin", "ruins"}), "To the west of the "
        + "dock can be seen the ruins of what were once simple "
        + "wooden huts.\n");
    add_item(({"settlement", "village", "camp", "town"}), "What is "
        + "left of the settlement can be seen to the west. Much of "
        + "it appears to be on fire from here.\n");

    return 1;
}


void
add_camp_tells()
{
    set_tell_time(120);

    add_tell("Coarse shouts can be heard near the river.\n");
    add_tell("Someone screams in the distance.\n");
    add_tell("From nearby you hear: 'To arms! To arms! We are under "
        + "attack!'\n");
    add_tell("Swords clash and ring somewhere nearby.\n");
    add_tell("A baby cries and is quickly hushed.\n");
    add_tell("You catch the scent of burning wood on the breeze.\n");
    add_tell("Harsh laughter can be heard beyond the huts.\n");
    add_tell("In the distance you hear: 'Kill 'em all! We feast on "
        + "manflesh tonight!'\n");
    add_tell("Someone cries out in pain.\n");
    add_tell("Smoke pours from the roof of a nearby hut.\n");
    add_tell("You hear cursing voices on the other side of the huts.\n");
}

void
add_east_camp_tells()
{
    set_tell_time(120);

    add_tell("Coarse shouts can be heard inside the village.\n");
    add_tell("Someone screams in the distance.\n");
    add_tell("From the west you hear: 'To arms! To arms! We are under "
        + "attack!'\n");
    add_tell("Swords clash and ring somewhere nearby.\n");
    add_tell("A dog howls in the distance.\n");
    add_tell("Smoke gets in your eyes, making them water.\n");
    add_tell("Harsh laughter can be heard to the west.\n");
    add_tell("In the distance you hear: 'Kill 'em all! We feast on "
        + "manflesh tonight!'\n");
    add_tell("Someone cries out in pain.\n");
    add_tell("A gentle breeze clears the smoke for a moment.\n");
    add_tell("A burning hut collapses to the ground, sending sparks "
        + "high into the air.\n");
    add_tell("Heat from the burning huts scorches your skin.\n");
    add_tell("Flames leap from the rubble of a nearby hut.\n");
}

void
add_dock_tells()
{
    set_tell_time(120);

    add_tell("Coarse shouts can be heard from the settlement.\n");
    add_tell("Someone screams in the distance.\n");
    add_tell("Swords clash and ring somewhere nearby.\n");
    add_tell("You catch the scent of burning wood on the breeze.\n");
    add_tell("Someone cries out in pain.\n");
    add_tell("The dock suddenly lurches in the current.\n");
    add_tell("A strong river breeze nearly topples you from the dock.\n");
    add_tell("The floor beneath your feet bobs up and down.\n");
    add_tell("The dock creaks alarmingly under your feet.\n");
    add_tell("A log floats by and quickly disappears from sight.\n");
    add_tell("Something falls into the water with a loud splash.\n");
}

public void
replace_humans(int i)
{
    if(i==0)
        {
            defence_status = 0;
            return;
        }
    else defence_status = 1;
    return;
}
