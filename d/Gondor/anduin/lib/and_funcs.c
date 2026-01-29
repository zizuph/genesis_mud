/*
 *  January 2003, Serif.
 */
/*
change water_add_items() to be lake reflections
add Nimrodel
add Celebrant
add Mirrormere
add Redhorn Pass
add Argonath
add base of the Rauros


Gnadnar's Anduin river code
Lorien
orcs in the field south of Lorien
Amon Lhaw ambushes
Tol Brandir quest
Parth Galen and Amon Hen
Cair Andros and defending NPCs (switch like ranger/orc camp) */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <tasks.h>
#include <ss_types.h>

#include "/d/Gondor/std/tell.c"
#include "/d/Gondor/defs.h"

/* Prototypes */

public string    forest_desc();
public string    mallorn_desc();
public string    path_desc();
public string    sky_desc();
public string    water_desc();

public int       drinkable();

public int       anorien_add_items();
public int       brownlands_add_items();
public int       celeb_add_items();
public int       hill_add_items();
public int       lorien_add_items();
public int       marsh_add_items();
public int       misty_add_items();
public int       mountain_add_items();
public int       nindalf_add_items();
public int       path_add_items();
public int       river_add_items();
public int       sky_add_items();
public int       vale_add_items();
public int       water_add_items();

string           mallorn_text;
string           path_text;
string           sky_text;
string           tree_text;
string           water_text;

object           actor;

int
blocked_path()
{
    write("You wander off the path but you find nothing of "
        + "interest.\n");
    return 1;
}

public int
drinkable()
{
    TO->add_prop(OBJ_I_CONTAIN_WATER, -1);
    return 1;
}

public int       
anorien_add_items()
{
    add_item(({"anorien", "Anorien", "field", "fields", "green fields", 
        "western banks"}), "The green fields of Anorien span into the "
        + "distance from the western banks of the river.\n");
    return 1;
} 

void
add_brownlands_tells()
{
    add_tell("You notice that the area is unusually quiet.\n");
}

public int       
celeb_add_items()
{
    add_item(({"field", "fields", "sparse field", "sparce fields"}), "Sparce "
        + "fields lie on either side of the river. On the west side, the land "
        + "is known as the Field of Celebrant.\n");
    add_item(({"field of celebrant", "Field of Celebrant"}), "The Field of "
        + "Celebrant was the site of an ancient battle. It lies on the far "
        + "shore of the river.\n");
    return 1;
} 

public int       
hill_add_items()
{
    add_item(({"hill", "hills", "emyn muil", "Emyn Muil"}), "To hills "
         + "of the Emyn Muil rise all around you on the eastern side "
         + "of the Anduin.\n");
    return 1;
} 

void
add_hill_tells()
{
    add_tell("A gentle breeze moves through the trees.\n");
}

public int       
marsh_add_items()
{ 
    TO->remove_item("grass");
    TO->remove_item("tall grass");
    TO->remove_item("air");
    TO->remove_item("humid air");
    TO->remove_item("humidity");
    TO->remove_item("ground");

    add_item(({"grass", "tall grass",}), "Tall grass grows here "
        + "and there.\n");
    add_item(({"ground"}), "The ground is very soggy here.\n");
    add_item(({"air", "stench", "humid air", "humidity"}), "The air is "
        + "moist and filled with the stench of damp decaying things.\n");
    add_item(({"swamp", "swamplands"}), "Swamplands stretch out around "
        + "the river.\n");
    return 1;
} 

void
add_marsh_tells()
{
    add_tell("A gentle breeze rustles the grass.\n");
}

public int       
misty_add_items()
{
    add_item(({"mountains", "misty mountains", "Misty Mountains", "peaks",
        "sharp peaks"}), "The sharp peaks of the Misty Mountains rise above "
        + "the land several leagues to the west.\n");
    return 1;
} 

public int       
mountain_add_items()
{
    add_item(({"mountain", "mountains"}), "A line of white-clad mountains "
        + "rises up several leagues to the southwest, while to the " 
        + "southeast, a group of dark peaks can be seen.\n");
    add_item(({"white mountains", "White Mountains", "ered nimrais",
        "Ered Nimrais", "line", "line of mountains", "white-clad mountains",
        "line of white-clad mountains"}), "The White Mountains rise "
        + "in snow-capped splendor above the land far to the southwest.\n");
    add_item(({"peaks", "dark peaks", "group", "group of dark peaks",
        "ephel duath", "Ephel Duath", "shadowy mountains", 
        "Shadowy Mountains", "mountains of shadow", "mordor", "Mordor"}), 
        "Far to the southwest, a group of dark peaks rises ominously above "
        + "the land.\n");
    return 1;
} 

public int
nindalf_add_items()
{
    add_item(({"nindalf", "Nindalf", "wetwang", "Wetwang", "great swamp"}),
        "The Nindalf, also known as Wetwant, lies damply around you, the "
        + "soggy result of the joining of the Mouths of the Entwash with "
        + "the waters of the Anduin.\n");
    marsh_add_items();
    return 1;
}

void
add_path_tells()
{
    add_tell("A gentle breeze rustles along the path.\n");
    add_tell("The gentle sounds of the river wash lightly over the "
        + "path.\n");
}

public string
path_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        path_text = " The path is treacherous by night";
        switch (clock->query_moon())
        {
        case "full":
            path_text += ", though the light of the full moon helps "
                + "a little."; 
            break;
        default:
            path_text += ".";
            break;
        }
        break;
    case "afternoon":
        path_text = " The light of the afternoon sun helps you "
            + "find secure footing as you pick your way along.";
        break;
    case "morning":
        path_text = " The light of the morning sun helps you "
            + "find secure footing as you pick your way along.";
        break;
    case "noon":
        path_text = " The light of the noon sun helps you "
            + "find secure footing as you pick your way along.";
        break;
    case "evening":
        path_text = " The light of the evening sun helps you "
            + "find secure footing as you pick your way along.";
        break;
    case "early morning":
        path_text = " The light of the early morning sun helps you "
            + "find secure footing as you pick your way along.";
        break;
    default:
        path_text = "";
        break;
    }
    return (path_text);
}

void
add_river_tells()
{
    add_tell("The river gurgles as it flows by.\n");
    add_tell("The river gurgles as it flows by.\n");
    add_tell("The moist scent of the river drifts on the air.\n");
}

public mixed
find_season(string str)
{
    object  clock = find_object(CLOCK);
    string  month = clock->query_month_s();

    switch (month)
    {
    case "December":
    case "January":
    case "February":
        return "winter";
    break;

    case "March":
    case "April":
    case "May":
        return "spring";
    break;

    case "June":
    case "July":
    case "August":
    case "September":
        return "summer";
    break;

    case "October":
    case "November":
        return "autumn";
    break;
    }
    return 1;
}

public mixed
leaf_colour(string str)
{
    object  clock = find_object(CLOCK);
    string  month = clock->query_month_s();

    switch (month)
    {
    case "November":
    case "December":
    case "January":
    case "February":
        return "golden leaves";
    break;

    case "March":
    case "April":
    case "May":
    case "June":
        return "green leaves and golden flowers";
    break;

    case "July":
    case "August":
    case "September":
    case "October":
        return "green and golden leaves";
    break;
    }
    return 1;
}

public string
mallorn_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string  month = leaf_colour(month);

    switch (time)
    {
    case "night":
        mallorn_text = ", their " + month + " shimmering even by the "
          + "dark of night";
        switch (clock->query_moon())
        {
        case "full":
            mallorn_text += ", seeming to embrace and drink in the pale "
                + "glow of the full moon"; 
            break;
        case "waxing crescent":
            mallorn_text += ", seeming to embrace and drink in the pale "
                + "glow of the crescent moon";
            break;
        case "waxing gibbous":
		    mallorn_text += ", seeming to embrace and drink in the pale "
                + "glow of the waxing moon"; 
		    break;
        case "waning gibbous":
		    mallorn_text += ", seeming to embrace and drink in the pale "
                + "glow of the waning moon"; 
		    break;
        case "waning crescent":
            mallorn_text += ", seeming to embrace and drink in the pale "
                + "glow of the waning crescent moon"; 
            break;
        default:
		    mallorn_text += " under the pale starlight";
            break;
        }
        break;
    case "afternoon":
        mallorn_text = ", their " + month + " shimmering in the sun";
        break;
    case "morning":
        mallorn_text = ", their " + month + " shimmering in the morning "
            + "light";
        break;
    case "noon":
        mallorn_text = ", their " + month + " resplendent under the full "
            + "noon sun";
        break;
    case "evening":
        mallorn_text = ", their " + month + " shimmering in the evening "
            + "light";
        break;
    case "early morning":
        mallorn_text = ", their " + month + " shimmering in the early "
            + "morning light";
        break;
    default:
		mallorn_text = "";
        break;
    }
    return (mallorn_text);
}

public string
sky_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string  month = find_season(month);

    switch (time)
    {
    case "night":
        sky_text = " The " + month + " stars twinkle clearly "
          + "as they shine over the land";
        switch (clock->query_moon())
        {
        case "full":
            sky_text += ", surrounding the pale brightness of the full "
                + "moon and faintly illuminating "; 
            break;
        case "waxing crescent":
            sky_text += " as the crescent moon begins to rise, bathing "
                + "pale light onto ";
            break;
        case "waxing gibbous":
		    sky_text += " as the nearly full moon rises in the "
                + "west, faintly illuminating "; 
		    break;
        case "waning gibbous":
		    sky_text += ". The moon, slightly past full, casts a shimmering "
                + "glow over the area, faintly illuminating "; 
		    break;
        case "waning crescent":
            sky_text += ", as the moon tilts its sharp horns over the "
                + "landscape and faintly illuminates "; 
            break;
        default:
		    sky_text += ", but the moon cannot be seen, leaving only "
                + "the faintest light to illuminate ";
            break;
        }
        break;
    case "afternoon":
        sky_text = " The afternoon sun shines down upon ";
        break;
    case "morning":
        sky_text = " The morning sun is riding low in the eastern horizon, "
            + "softly lighting ";
        break;
    case "noon":
        sky_text = " The noon sun is directly overhead, reflecting now and "
            + "then off ";
        break;
    case "evening":
        sky_text = " The sun is sinking into the west, bathing the area "
           + "in deep orange light and casting shadows across ";
        break;
    case "early morning":
        sky_text = " The first rays of the sun are peeking over the eastern "
           + "horizon, sending shadows across ";
        break;
    default:
		sky_text = " The sky is obscured by gathering clouds above ";
        break;
    }
    return (sky_text);
}

public int
sky_add_items()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
    string  month = find_season(month);

    TO->remove_item("sky");
    TO->remove_item("night sky");
    TO->remove_item("afternoon sky");
    TO->remove_item("morning sky");
    TO->remove_item("noon sky");
    TO->remove_item("evening sky");
    TO->remove_item("early morning sky");
    TO->remove_item("clouds");
    TO->remove_item("gathering clouds");
    TO->remove_item("sun");
    TO->remove_item("stars");
    TO->remove_item("star");
    TO->remove_item("moon");
    TO->remove_item("full moon");
    TO->remove_item("nearly full moon");
    TO->remove_item("crescent moon");
    TO->remove_item("end");
    TO->remove_item("ends");

    switch (time)
    {
    case "night":
 
        add_item(({"star", "stars"}), "The stars twinkle faintly in the deep "
            + "night sky of " + month + ".\n");
        add_item(({"sky", "night sky"}), "The night sky is illuminated "
            + "faintly by the twinkling stars.\n");
        switch (clock->query_moon())
        {
        case "full":
            add_item(({"moon", "full moon"}), "The bright round moon shines "
                + "down from the night sky, its face slightly pale.\n"); 
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
            + "by the bright light of the " + month + " sun.\n");
        add_item(({"sun", "afternoon sun"}), "The afternoon sun shines "
            + "down brightly upon the landscape.\n");
        break;
    case "morning":
        add_item(({"sky", "morning sky"}), "The morning sky is lit "
            + "by the growing light of the " + month + " sun.\n");
        add_item(({"sun", "morning sun", "horizon", "eastern horizon"}), 
            "The morning sun rides low in the eastern horizon.\n");
        break;
    case "noon":
        add_item(({"sky", "noon sky"}), "The noon sky is illuminated by "
            + "the golden light of the " + month + " sun directly overhead.\n");
        add_item(({"sun", "noon sun"}), "The noon sun is directly overhead.\n");
        break;
    case "evening":
        add_item(({"sky", "evening sky"}), "The evening sky is lit "
            + "by the fading light of the sinking " + month + " sun.\n");
        add_item(({"sun", "evening sun", "horizon", "western horizon"}), 
            "The evening sun is sinking behind "
            + "the mountains in the west.\n");
        break;
    case "early morning":
        add_item(({"sky", "early morning sky"}), "The morning sky is lit "
            + "by the first rays of the rising " + month + " sun.\n");
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
vale_add_items()
{
    add_item(({"field", "fields", "green field", "green fields"}), "Green "
        + "fields spread out lushly on either side of the river.\n");
    add_item(({"tree", "trees", "stand", "stands", "stands of trees"}), 
        "Stands of trees rise here and there above the fields our along "
        + "the river.\n");
    return 1;
} 

void
add_vale_tells()
{
    add_tell("A gentle breeze moves through the fields.\n");
}

public string
water_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        water_text = " Some light from the stary night sky dances "
          + "on the swift-moving water";
        switch (clock->query_moon())
        {
        case "full":
            water_text += ", along with the pale glow from the full "
                + "moon."; 
            break;
        default:
            water_text += ".";
            break;
        }
        break;
    case "afternoon":
        water_text = " The light of the afternoon sun glimmers on "
            + "the rippling water.";
        break;
    case "morning":
        water_text = " The light of the morning sun glimmers on "
            + "the rippling water.";
        break;
    case "noon":
        water_text = " The light of the noon sun glimmers brightly on "
            + "the rippling water.";
        break;
    case "evening":
        water_text = " The light of the evening sun glimmers on "
            + "the rippling water.";
        break;
    case "early morning":
        water_text = " The light of the early morning sun glimmers on "
            + "the rippling water.";
        break;
    default:
        water_text = " The ripples waveringly reflect the sky.";
        break;
    }
    return (water_text);
}

public string
forest_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();

    switch (time)
    {
    case "night":
        tree_text = " Some light from the stary night sky bathes "
          + "the forest in soft light";
        switch (clock->query_moon())
        {
        case "full":
            tree_text += ", brightened by the pale glow from the full "
                + "moon."; 
            break;
        default:
            tree_text += ".";
            break;
        }
        break;
    case "afternoon":
        tree_text = " The light of the afternoon sun shines on "
            + "every leaf and tree.";
        break;
    case "morning":
        tree_text = " The light of the morning sun shines on "
            + "every leaf and tree.";
        break;
    case "noon":
        tree_text = " The light of the noon sun shines brightly on "
            + "every leaf and tree.";
        break;
    case "evening":
        tree_text = " The light of the evening sun shines on "
            + "every leaf and tree.";
        break;
    case "early morning":
        tree_text = " The light of the early morning sun shines on "
            + "every leaf and tree.";
        break;
    default:
        tree_text = " The ambient light shows off every leaf and "
            + "tree to good effect.";
        break;
    }
    return (tree_text);
}

public int       
brownlands_add_items()
{  
    TO->remove_item("bank");
    TO->remove_item("banks");
    TO->remove_item("muddy bank");
    TO->remove_item("muddy banks");

    add_item(({"ground", "land"}), "The ground here is bleak and barren.\n");
    add_item(({"path", "well-trodden path"}), "The path continues along "
        + "the eastern banks of the Anduin as the river flows from the "
        + "mountains in the north to the sea in the distant south." 
        + path_desc() + "\n");
    add_item(({"grass", "tall grass", "far shore"}), "Tall grass grows "
        + "on the far shore of the river in the area known as the Wold.\n");
    add_item(({"wold", "Wold", "rohan", "Rohan"}), "The area known as "
        + "the Wold, the easternmost reaches of the Kingdom of Rohan, lies "
        + "on the far shore of the river.\n");
    add_item(({"bank", "banks", "barren bank", "barren banks", "muddy bank",
        "muddy banks"}), "The banks of the river here are muddy and "
        + "barren.\n");
    return 1;
} 

public int     
lorien_add_items()
{
    object  clock = find_object(CLOCK);
    string  month = clock->query_month_s();

    add_item(({"lorien", "Lorien", "golden wood", "Golden Wood"}), 
         "The land of Lorien, the Golden Wood, lies on the far shore.\n");

    TO->remove_item("leaf");
    TO->remove_item("leaves");
    TO->remove_item("flower");
    TO->remove_item("flowers");
    TO->remove_item("green leaf");
    TO->remove_item("green leaves");
    TO->remove_item("golden leaf");
    TO->remove_item("golden leaves");
    TO->remove_item("golden flower");
    TO->remove_item("golden flowers");
    TO->remove_item("tree");
    TO->remove_item("trees");
    TO->remove_item("green tree");
    TO->remove_item("green trees");
    TO->remove_item("tall tree");
    TO->remove_item("tall trees");
    TO->remove_item("mallorn tree");
    TO->remove_item("mallorn trees");
    TO->remove_item("forest");
    TO->remove_item("golden tree");
    TO->remove_item("golden trees");
    TO->remove_item("green forest");
    TO->remove_item("golden forest");
    TO->remove_item("green and golden leaves");
    TO->remove_item("green and golden forest");

    switch (month)
    {
    case "November":
    case "December":
    case "January":
    case "February":
        add_item(({"leaf", "golden leaf", "leaves", "golden leaves"}), 
            "Golden leaves adorn the the forest." + forest_desc() + "\n");
        add_item(({"tree", "trees", "mallorn tree", "mallorn trees", 
            "golden tree", "golden trees", "tall tree", "tall trees",
            "forest", "golden forest", "display"}), "The tall golden trees "
            + "of the forest are resplendent with golden leaves. They grow "
            + "thickly, forming a dense but beautiful display." 
            + forest_desc() + "\n");
    break;
    case "March":
    case "April":
    case "May":
    case "June":
        add_item(({"leaf", "green leaf", "leaves", "green leaves"}), 
            "Green leaves adorn the the forest, highlighted here and "
            + "there by golden flowers." + forest_desc() + "\n");
        add_item(({"tree", "trees", "mallorn tree", "mallorn trees", 
            "golden tree", "golden trees", "tall tree", "tall trees",
            "forest", "golden forest"}), "The tall golden trees of the "
            + "forest are resplendent with green leaves. They grow "
            + "thickly, forming a dense but beautiful display." 
            + forest_desc() + "\n");
        add_item(({"flower", "flowers", "golden flower", "golden flowers"}),
            "Golden flowers peek here and there over the green leaves "
            + "of the tall trees." + forest_desc() + "\n");
    break;
    case "July":
    case "August":
    case "September":
    case "October":
        add_item(({"leaf", "golden leaf", "leaves", "golden leaves", 
            "green leaf", "green leaves", "green and golden leaves"}), 
            "Green and golden leaves adorn the the forest." 
            + forest_desc() + "\n");
        add_item(({"tree", "trees", "mallorn tree", "mallorn trees", 
            "golden tree", "golden trees", "tall tree", "tall trees",
            "forest", "golden forest", "green forest", "green tree",
            "green trees"}), "The tall golden trees of the forest are "
            + "resplendent with green and golden leaves. They grow "
            + "thickly, forming a dense but beautiful display." 
            + forest_desc() + "\n");
    break;
    }
    return 1;
}

public int       
path_add_items()
{
    add_item(({"path", "well-trodden path"}), "The path continues along "
        + "the eastern banks of the Anduin as the river flows from the "
        + "mountains in the north to the sea in the distant south." 
        + path_desc() + "\n");
    add_item(({"grass", "tall grass",}), "Tall grass grows lushly all "
        + "about.\n");
    add_item(({"ground", "signs", "faint signs"}), "The ground shows faint "
        + "signs that a few people have passed this way with the last few "
        + "days.\n");
    add_item(({"air", "scent", "humid air", "humidity"}), "The air is "
        + "moist and soothing, smelling freshly of green growing things.\n");
    return 1;
} 

public int
river_add_items()
{
    TO->remove_item("river");
    TO->remove_item("mighty river");
    TO->remove_item("anduin");
    TO->remove_item("Anduin");
    TO->remove_item("mighty anduin");
    TO->remove_item("mighty Anduin");
    TO->remove_item("flow");
    TO->remove_item("swift flow");
    TO->remove_item("bank");
    TO->remove_item("banks");

	add_item(({"river", "mighty river", "anduin", "Anduin", "mighty anduin",
        "mighty Anduin", "flow", "swift flow"}), "The mighty Anduin flows " 
        + "here on its way from the mountains in the north toward the sea "
        + "in the distant south." + water_desc() + "\n");
    add_item(({"bank", "banks"}), "The banks of the Anduin tilt down from "
        + "the path into the waters of the river.\n");
    return 1;
}

public int
water_add_items()
{
    TO->remove_item("water");
    TO->remove_item("river water");
    TO->remove_item("waters");

    add_item(({"water", "river water", "waters"}), "The waters of the "
        + "Anduin flow swift and deep." + water_desc() + "\n");
    return 1;
}

