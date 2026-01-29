/*
 *  IGARD_LIB + "igard_funcs.c"
 *
 *  Various functions common to Isengard rooms.
 *
 *  Last modified by Alto, 23 September 2001
 *
 *  Warning added - Updated by Varian, January 2021
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include "../igard_defs.h"

inherit IGARD_LIB + "ambush_funcs.c";
inherit IGARD_LIB + "tapestry_funcs.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"
#include "/d/Gondor/std/tell.c"

/*
 * This uses Gondor skill 118500 to see if the player was warned
 * or not. Varian 2020
 */
#define IGARD_WARN 118102

/* PROTOTYPES */

public string    sky_desc();
public int       sky_add_items();
public int       outside_add_items();
public int       wall_add_items();
public int       archer_attack();
public string    tunnel_long_desc();
public string    guardrm_long_desc();
public void      add_tunnel_tells();
public int       plain_add_items();
public int       guardrm_add_items();
public int       add_fire_tells();
public string    parapet_long_desc();
public int       parapet_add_items();
public int       add_parapet_tells();
public int       cross_walkway();
public int       move_player();
public int       walkway_add_items();
public string    archer_room_long_desc();
public int       archer_room_add_items();
public int       test_quest();

string           sky_text;
object           actor;

public string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        sky_text = " An ocean of stars blanket the deep night sky above "
          + "Isengard";
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
        sky_text = " The afternoon sun glares down upon the landscape.";
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

    TO->remove_item("mountain");
    TO->remove_item("peaks");
    TO->remove_item("cliff");
    TO->remove_item("foothills");

    add_item(({"mountain", "mountains", "misty mountains"}), "The "
        + "southern end of the great Misty Mountains can be seen to "
        + "the west and north. The mountains loom high into the "
        + "northwestern sky and seem harsh and unyielding. Snow-"
        + "capped peaks top their massive cliffs and slopes.\n");
    add_item(({"peaks", "snow-capped peaks"}), "The tops of the "
        + "mountains are covered with snow even in the middle of "
        + "the summer.\n");
    add_item(({"cliff", "cliffs", "face"}), "The face of the each "
        + "mountain is characterized by jagged cliffs and unscalable "
        + "heights.\n");
    add_item(({"foothills", "foothill"}), "The Wizard's Vale lies between "
        + "several of the southern Misty Mountains. Some of their foothills "
        + "fork to the west, north and east of Nan Curunir.\n");

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
            + "by the glaring light of the sun.\n");
        add_item(({"sun", "afternoon sun"}), "The afternoon sun glares "
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
            + "the pounding light of the sun directly overhead.\n");
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
outside_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"ground", "floor"}), "The ground here is very flat, "
        + "broken only by an occasional outcropping of black rock "
        + "from the knees of the Misty Mountains.\n");
    add_item(({"outcroppings", "outcropping", "projection", "projections"}),
        "Sudden large outcroppings of black rock project here and there "
        + "from the otherwise flat terrain of the landscape.\n");
    add_item(({"rock", "black rock", "stone", "black stone"}), "The rock of "
        + "the mountains is weathered and black.\n");
 
    return 1;
}


public int
tap_move()
{
    write("You move aside the tapestry and look behind.\n");
    test_quest();
    return 1;
}

public int
test_quest()
{
    return 1;
}

public int
wall_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"ring wall", "ringed wall"}), "You are standing inside "
        + "it!\n");
    add_item(({"rock", "black rock", "stone"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
    add_item(({"isengard", "fortification"}), "You are standing inside "
        + "its great ring wall.\n");
    add_item(({"wall", "walls"}), "The walls are made from black rock "
        + "quarried in the nearby mountains. They seem to have been "
        + "carved by the patient forces of nature rather than the hasty "
        + "hands of men.\n");
    add_item(({"ceiling", "roof"}), "The ceiling is smooth and solid "
        + "black rock. It seems unbreakable and timeless.\n");
    add_item(({"floor", "ground"}), "The floor here is made from black "
        + "rock and worn smooth by tens of thousands of booted feet over "
        + "many long years.\n");
    add_item(({"lantern", "massive lantern", "iron lantern", "lanterns",
        "massive lanterns", "iron lanterns"}), "Set into "
        + "small alcoves along the wall are massive lanterns of iron. "
        + "Each lantern has a large base filled with a pungent oil that "
        + "produces an unsavoury vapour when burned. As this place never "
        + "feels the light of day, the flickering firelight from each "
        + "lantern provides the only light to the room.\n");
    add_item(({"base", "bases"}), "Each lantern has a large base filled "
        + "with pungent fuel oil.\n");
    add_item(({"alcove", "small alcove", "alcoves", "small alcoves"}),
        "At intervals of twenty feet, pairs of alcoves have been cut into "
        + "the walls on either side. Within each alcove is set a massive "
        + "iron lantern.\n");
    add_item(({"crack", "cracks"}), "When you inspect the wall closely, "
        + "you discover several hairline cracks through which steam is "
        + "escaping. The origin of the steam remains a mystery for now, "
        + "but it is no doubt associated with sinister machinery concealed "
        + "behind the wall.\n");
    add_item(({"steam"}), "Small wisps of steam can be seen arising from "
        + "hairline cracks in the walls.\n");
    add_item(({"tapestry", "tapestries"}), "Hanging from one of the walls is a " 
        + tapestry_condition()
        + " tapestry. Its " + tapestry_colour() + " cloth has a "
        + tapestry_weave() + " weave that is shot through with "
        + tapestry_metal() + " thread. The tapestry looks rather "
        + tapestry_cleanliness() + ".\n");

    add_cmd_item(({"tapestry", "large tapestry"}), "move", &tap_move());
 
    return 1;
}


public int
plain_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"wall", "ring wall", "ringed wall"}), "A great wall "
        + "of black stone stands at least one hundred feet tall and "
        + "curves away almost as far as the eye can see in both "
        + "directions. It appears to be made "
        + "partly from the natural landscape but also by the hand of "
        + "Men. From here you can see that it entirely encircles the "
        + "plain.\n");
    add_item(({"landscape", "natural landscape", "terrain", "plain", 
        "great plain"}), "Here "
        + "inside the great ring wall of Isengard, the landscape is open "
        + "and slightly bowl-shaped. The great plain is bored and delved, "
        + "with many shafts driven deep into the ground and covered by "
        + "low mounds and domes of stone.\n");
    add_item(({"rock", "black rock"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
    add_item(({"roads"}), "Great roads, lined with mighty pillars, march "
        + "down from the ring wall to the tower in the center of the great "
        + "plain. When seen from atop the wall, the effect is that of a giant "
        + "spider lurking inside its den.\n");
    add_item(({"stones", "flat stones", "great flat stones", "stone-flag",
        "stone-flags", "flagstone", "flagstones"}), "The "
        + "flat and squared stones are made from the same black rock "
        + "used in the construction of the ring wall.\n");
    add_item(({"isengard", "fortification"}), "You are standing within "
        + "the massive ring wall of Isengard, overlooking the great "
        + "circular plain enclosed within. Many roads lead down from the "
        + "wall to a huge tower in the center of the plain.\n");
    add_item(({"shaft", "shafts"}), "From atop it is difficult to guess "
        + "how far they delve. There are many of them scattered across "
        + "the plain, and unwholesome steam rises from more than a few. "
        + "Most are covered with low mounds or domes of stone.\n");
    add_item(({"mound", "low mound", "mounds", "low mounds", "dirt"}), 
        "Many of the shafts are capped with low mounds of dirt. Nothing grows "
        + "on them, perhaps due to the noxious vapours seeping from "
        + "underground.\n");
    add_item(({"dome", "stone dome", "domes", "stone domes",
        "domes of stone"}), "Many of the shafts are capped with domes of "
        + "stone. The noxious odours permeating the air seem to have their "
        + "origin beneath these domes.\n");
    add_item(({"pillar", "pillars"}), "Giant pillars line the streets "
        + "leading from the ring wall down to the tower in the center of the "
        + "plain. They are made of various kinds of metal and joined by great "
        + "links of iron chain.\n");
    add_item(({"marble pillar", "marble pillars"}), "Some of the mighty "
        + "pillars are made from black marble, quarried in the Misty "
        + "Mountains.\n");
    add_item(({"copper pillar", "copper pillars"}), "Some of the mighty "
        + "pillars are made from dusky copper, mined beneath the Misty "
        + "Mountains.\n");
    add_item(({"iron pillar", "iron pillars"}), "Some of the mighty "
        + "pillars are made from rusted iron, mined beneath the Misty "
        + "Mountains.\n");
    add_item(({"chain", "links", "iron chain", "links of iron chain"}), 
        "Massive chains run along the great pillars from the ring wall "
        + "down to the tower in the center of the plain. When seen from "
        + "atop the wall, the roads resemble a giant spider lurking inside "
        + "its den.\n");
    add_item(({"tower", "mighty tower", "orthanc", "peak", "isle"}), 
        "In the center of the "
        + "plain there stands a tower of marvellous shape. It was fashioned "
        + "by the builders of old, who smoothed the Ring of Isengard, and "
        + "yet it seems a thing not made by the craft of men, but riven "
        + "from the bones of the earth in the ancient torment of the hills. "
        + "This is Orthanc, a peak and isle of rock, black and gleaming "
        + "hard. Four mighty piers of many-sided stone are welded into "
        + "one, but near the summit they open into gaping horns, their "
        + "pinnacles sharp as the points of spears, keen-edged as knives.\n");
    add_item(({"pier", "piers"}), "The tower Orthanc is made from "
        + "four mighty piers of many-sided stone, welded into one.\n");
    add_item(({"horn", "horns"}), "Four gaping horns open atop the mighty "
        + "tower, their pinnacles sharp as the points of spears, keen-edged "
        + "as knives.\n");
    add_item(({"pinnacle", "pinnacles"}), "The pinnacles of the gaping "
        + "horns are sharp as the points of spears, keen-edged as knives.\n");
    add_item(({"vent", "vents"}), "Here and there across the plain, steam "
        + "can be seen rising from the ground through open vents. Whatever "
        + "is below ground making such immense amounts of vapour is not "
        + "clear from your present vantage point.\n");
    add_item(({"steam", "vapour", "mist", "vapours", "mists"}), 
        "Steams and vapours rise from "
        + "numerous vents opening on the plain. As a result, it is nearly "
        + "impossible to see across its span, even though the ring "
        + "wall is only one mile in diameter.\n");
    add_item(({"horizon"}), "The horizon on the plain is dominated by the "
        + "ring wall and the mighty tower at its center.\n");
    add_item(({"gull", "gulls", "black gull", "black gulls"}), "Large black "
        + "gulls fly about the mighty tower at the center of the plain. They "
        + "turn and wheel about the massive piers of stone, darting in and "
        + "out of the gaping horns at the top.\n");
    return 1;
}


void
add_tunnel_tells()
{
    set_tell_time(120);

    add_tell("Dusky firelight flickers from the iron lanterns.\n");
    add_tell("A deep rumbling can be felt through the floor.\n");
    add_tell("Air moves through the tunnel from somewhere ahead.\n");
    add_tell("A gust of cool air pushes through the tunnel from somewhere "
        + "behind you.\n");
    add_tell("The tunnel suddenly grows quiet.\n");
    add_tell("Footsteps echo ahead in the tunnel.\n");
    add_tell("Footsteps echo from behind in the tunnel.\n");
    add_tell("Harsh voices come from somewhere nearby.\n");
    add_tell("The echoes of voices hang in the still air.\n");
    add_tell("Marching feet can be heard elsewhere in the ring wall.\n");
    add_tell("A rat scurries away into the shadows.\n");
    add_tell("Deep voices grumble in the distance.\n");
    add_tell("Tortured machinery squeals and rattles from below.\n");
    add_tell("Steam hisses through a crack in the wall.\n");
}


void
add_parapet_tells()
{
    set_tell_time(120);

    add_tell("Wind howls across the parapet.\n");
    add_tell("The great roar of wind is almost deafening.\n");
    add_tell("Angry voices can be heard shouting nearby.\n");
    add_tell("An eagle cries somewhere high above in the sky.\n");
    add_tell("The shrieking wind suddenly grows still.\n");
    add_tell("A gust of air nearly pushes you over the ramparts.\n");
    add_tell("You struggle to keep your footing in the strong gale.\n");
    add_tell("Booted feet can be heard approaching.\n");
    add_tell("A low rumbling arises from deep within Isengard.\n");
    add_tell("Somewhere in the distance a trumpet begins to bray.\n");
    add_tell("Roaring blasts of wind relentlessly hammer at you.\n");
    add_tell("Smoke and vapours rise from within Isengard.\n");
    add_tell("Tortured machinery squeals and rattles from below.\n");
}


string
tunnel_long_desc()
{
    return "This is a long underground tunnel within the great "
    + "ring wall of Isengard. The tunnel is extremely wide and could "
    + "accomodate an army in which twenty soldiers marched abreast. "
    + "Firelight flickers off the stone walls and floor from massive "
    + "iron lanterns set into small alcoves along the way. A tapestry "
    + "can be seen hanging from one of the walls. ";
}


public string
guardrm_long_desc()
{
    return "You have entered a small guardroom in which the only exit "
    + "is the doorway you came in. The room does not seem designed for comfort, "
    + "but rather for vigilance. A stone table rests in the middle of the "
    + "room, upon which you see evidence of meals eaten in haste. The black "
    + "stone walls are rough and unadorned save for storage racks for "
    + "pikes and swords. In the far corner or the room, a small fire provides "
    + "little illumination or warmth to your surroundings. ";
}


public string
parapet_long_desc()
{
    return "The view from here is breathtaking! You are standing on a "
    + "stone parapet one hundred feet above the Wizard's Vale, atop the "
    + "mighty ring wall of Isengard. A brisk wind howls over the wall, "
    + "battering the ramparts and making it extremely difficult to hold "
    + "your position behind them." + sky_desc() + " The southern Misty "
    + "Mountains loom in the western sky. ";
}



public int
parapet_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"wizard's vale", "vale", "valley", "nan curunir"}), 
        "Looking down from "
        + "the parapet, you see a broad valley spreading away into the "
        + "horizon. This is Nan Curunir, the Wizard's Vale, so named for "
        + "the inhabitant of the mighty tower Orthanc. Flowing out of it "
        + "to the south is the River Isen, which eventually finds its way "
        + "to the sea far away.\n");
    add_item(({"river", "river isen", "isen"}), "The River Isen has its "
        + "foundations here, in the Misty Mountains. It flows southwards "
        + "out of the Wizard's Vale on its long journey to the sea.\n");
    add_item(({"rock", "black rock", "stone"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
    add_item(({"rampart", "ramparts", "stone rampart", "stone ramparts",
        "spaces", "space"}),
        "The ring wall is lined with great stone ramparts, standing many "
        + "times the height of a man. The spaces between the ramparts "
        + "offer protection for archers to fire upon intruders at the "
        + "foot of the ring wall.\n");
    add_item(({"wall", "ring wall", "ringed wall"}), "You are atop "
        + "a great wall "
        + "of black stone that stands at least one hundred feet tall and "
        + "curves away almost as far as the eye can see in both directions. "
        + "It appears to be made "
        + "partly from the natural outcroppings of the Misty Mountains, but "
        + "also by the hand of Men.\n");
    add_item(({"rock", "black rock"}), "The great ring wall is made "
        + "from black rock, both natural and that quarried by the hands "
        + "of Men.\n");
    add_item(({"isengard", "fortification"}), "You are standing atop "
        + "the massive ring wall of Isengard, overlooking the Wizard's "
        + "Vale. Behind you, a huge tower stands in the center of the "
        + "fortification.\n");
    add_item(({"tower", "mighty tower", "orthanc", "peak", "isle"}), 
        "Behind you rises a tower of marvellous shape. It was fashioned "
        + "by the builders of old, who smoothed the Ring of Isengard, and "
        + "yet it seems a thing not made by the craft of men, but riven "
        + "from the bones of the earth in the ancient torment of the hills. "
        + "This is Orthanc, a peak and isle of rock, black and gleaming "
        + "hard. Four mighty piers of many-sided stone are welded into "
        + "one, but near the summit they open into gaping horns, their "
        + "pinnacles sharp as the points of spears, keen-edged as knives.\n");
    add_item(({"pier", "piers"}), "The tower Orthanc is made from "
        + "four mighty piers of many-sided stone, welded into one.\n");
    add_item(({"horn", "horns"}), "Four gaping horns open atop the mighty "
        + "tower, their pinnacles sharp as the points of spears, keen-edged "
        + "as knives.\n");
    add_item(({"pinnacle", "pinnacles"}), "The pinnacles of the gaping "
        + "horns are sharp as the points of spears, keen-edged as knives.\n");
    add_item(({"smoke", "vapour", "vapours", "plume", "plumes"}), "The "
        + "stink of sulphur is carried on the wind from the giant plumes "
        + "of smoke and vapours rising from within the fortification of "
        + "Isengard.\n");

    return 1;
}


public int
guardrm_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"exit"}), "It is the same doorway through which you "
        + "entered.\n");
    add_item(({"doorway"}), "Only one doorway leads into and out "
        + "of the room. There is no door set inside it, suggesting that "
        + "the people stationed here have need of hasty exit.\n");
    add_item(({"table", "stone table"}), "The stone table in the center "
        + "of the room appears to have been carved directly from the stone "
        + "of the floor. Half-eaten food is growing slowly cold upon its "
        + "surface.\n");
    add_item(({"half-eaten food", "food", "meat"}), "From the look of it, you "
        + "are probably better off not knowing what kind of meat that is.\n");
    add_item(({"rack", "racks", "storage rack", "storage racks", "stone racks",
        "stone rack"}), "There are several stone racks placed against the "
        + "walls. Some of them are tall and obviously designed for pikes, "
        + "whereas others are half the height of a man and designed to house "
        + "swords. All of the racks are presently empty.\n");
    add_item(({"fire", "small fire"}), "A small fire, not large enough to "
        + "be cheery, let alone provide enough warmth to heat the room "
        + "comfortably, burns in one corner of the room.\n");
    add_item(({"wood", "stack", "stack of wood", "tiny stack"}), "The small "
        + "fire is made from a tiny stack of wood.\n");
    add_item(({"corner"}), "In one corner of the room, a small fire burns.\n");
    return 1;
}


void
add_fire_tells()
{
    set_tell_time(120);

    add_tell("The small fire flickers dimly in the corner.\n");
    add_tell("Flames dance in the corner.\n");
    add_tell("Shadows cast by the light of the fire dance on the walls.\n");
    add_tell("The fire hisses and pops.\n");
    add_tell("A spark pops from the fire in the corner.\n");
    add_tell("The wood in the fire settles in a shower of sparks.\n");
    add_tell("You feel a small amount of warmth from the fire.\n");
    add_tell("Pop! Some of the burning wood settles.\n");
}


int
archer_attack()
{
    int healed, health, pain, ouch;

    healed = TP->query_max_hp();
    health = TP->query_hp();
    pain = (healed/2);
    ouch = (health/2);
    actor = TP;

    write("Arrows fly into the area from somewhere nearby. Many skitter "
        + "harmlessly across the ground, but several of them find their "
        + "mark. Ouch!\n");
    tell_room(environment(actor), "Arrows fly into the area from somewhere "
        + "nearby. Many skitter harmlessly across the ground, but several of "
        + "them strike " + QTNAME(TP) + ".\n", 
        ({actor}));

    if (health <= pain)
    {
        TP->set_hp(ouch);
        return 1;
    }

    else
    {
    TP->set_hp(pain);
    }

    return 1;
}


int
cross_walkway()
{
    /*
     * For some reason, query_enemy() sometimes returns a value even
     * when a player is not involved in a fight. Until I can figure out
     * a better solution, I am going to remove this check. This means
     * that a player can get away from a fight, but so far it looks like
     * Isengard is plenty dangerous without this additional encumbrance.
     *     -- Alto 23 August 2002
     */

    actor = TP;

//    if (!TP->query_enemy())
//    {
    write("Taking a deep breath, you brave the narrow stone walkway. "
        + "Fortunately, you keep your balance and do not tumble to your "
        + "death on the iron spikes below.\n\n");

    tell_room(environment(actor), QCTNAME(actor) + " takes a deep breath "
        + "and braves the narrow stone walkway. Fortunately, "
        + PRONOUN(actor) + " keeps " + POSSESSIVE(actor)
        + " balance and does not tumble to " + POSSESSIVE(actor)
        + " death on the iron spikes below.\n", 
        ({actor}));

    move_player();

    return 1;

//    }

//    write("\nYou start to cross the narrow stone walkway. "
//        + "You quickly realize, however, that turning away from your "
//        + "opponent will get you killed.\n\n");
//
//    tell_room(environment(actor), QCTNAME(actor) + " starts to cross "
//        + "the narrow stone walkway. "
//        + CAP(PRONOUN(actor)) + " quickly realizes, however, that turning " 
//        + "away from " + POSSESSIVE(actor)
//        + " opponent is more dangerous than crossing the walkway.\n", 
//        ({actor}));
//    return 1;
         
}

int
move_player()
{
    write("Something is broken here. Please make a bugreport.\n");
    return 1; /* this is the dummy version */
}


int
walkway_add_items()
{
    add_item(({"walkway", "stone walkway", "narrow walkway", 
        "narrow stone walkway"}), "Before you there is a long narrow "
        + "walkway made of stone. It is wide enough for only one person "
        + "to cross at a time, and on either side a wide chasm opens.\n");
    add_item(({"chasm", "wide chasm", "edge", "chasms"}), "When you peer over "
        + "the edge of the wide chasm you see numerous metal spikes projecting "
        + "from below. They look lethal.\n");
    add_item(({"spike", "spikes", "metal spike", "metal spikes"}),
        "The spikes are made of some kind of metal, long rusted, but still "
        + "sharp enough to kill anyone falling from the narrow stone "
        + "walkway.\n");
    add_item(({"rust"}), "The metal spikes are covered in it, but they "
        + "still seem sturdy enough to impale if you fell upon them.\n");

    return 1;
}


public string    
archer_room_long_desc()
{
    return "This small stone room is not made for comfort and is in fact "
    + "rather cramped. The ceiling is very low and the walls are set extremely "
    + "close together. Scattered about the floor are numerous signs that "
    + "the room is used primarily by archers, including shreds "
    + "of grey feathers used for fletching, broken shafts of wood and flakes "
    + "of iron left from the sharpening of arrowheads. ";
}


public int       
archer_room_add_items()
{
    add_prop(ROOM_M_NO_TELEPORT, 1);

    add_item(({"shreds", "feathers", "grey feathers", "feather", "grey feather",
        "fletching", "shred"}), "The small shreds of feathers look to have "
        + "come from the wings of a small bird, perhaps a mourning dove. "
        + "The manner in which they have been stripped suggests that these "
        + "are the shreds left over after the fashioning of arrow fletchings.\n");
    add_item(({"shaft", "shafts", "broken shaft", "broken shafts"}), "The "
        + "broken shafts of wood appear to be rejects left behind during the "
        + "crafting of arrows.\n");
    add_item(({"flake", "flakes", "iron", "flakes of iron", "flake of iron"}), 
        "Glittering in the low light of the room, small flakes of iron are "
        + "scattered about the floor. They are most likely the product of "
        + "sharpened arrowheads.\n");
    add_item(({"slot", "slots", "cross-shaped slot", "cross-shaped slots"}), 
        "The cross-shaped slots are carved in such a way that arrows can be "
        + "fired through them at almost any angle into the adjoining room, "
        + "but provide sufficient protection that almost no return-fire can "
        + "reach the archer standing behind them. You can see the adjoining "
        + "room when you peer through the slots.\n");

    return 1;
}

/*
 * Function name:        do_kill
 * Description  :        Warning for killing - Varian 2020
 */
int
do_kill(object ob, object to)
{
    if (this_player()->query_skill(IGARD_WARN) > 0 )
        return 0;

    write("You hesitate a moment, are you sure you are ready " +
        "to reveal your true intentions inside Isengard?\n");
    this_player()->set_skill(IGARD_WARN, 1);
    return 1;
}
/*do_kill*/

public void
init() 
{
    ::init();
    add_action(do_kill,      "kill");
}