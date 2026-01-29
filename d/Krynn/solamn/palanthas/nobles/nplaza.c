/* 
 * The Court d'Plaisiri in the Nobles quarter,
 * the heart of the Plaisir district.
 *
 * Mortis 12.2005
 *
 * Added disposal bin. - Mortis 9.2014
 * Made clues and add_items simpler - Mortis 3.2015
 */

/* #pragma strict_types */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

object dbin;

/* Prototypes */
int check_combat();

string
query_to_jail()
{
    return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
    string plaza = "  To the north is a large, two-story shop with ivy "
    + "entwined pillars.  A green-trimmed, white, silk banner hangs taut "
    + "diagonally between dark green bars high above it.  To the east is a "
    + "wide, one-story cafe with a green canopy overhanging white-enameled "
    + "iron chairs and tables.  An image of a mermaid, done in the old style "
    + "with white lines, is displayed on a tall, green column atop the "
    + "building.  South is a building of pristine marble done in classic "
    + "old style.  Chiseled into the marble above its entrance are the "
    + "words \"Laethorian Spa and Body\".\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    desc += "The pristine marble of the Court d'Plaisir and its buildings "
    + "glows in " + one_of_list(({"pale purple ", "soft pink ",
      "pale orange ", "grey and pink "})) + " hues as the sun peeks above "
    + "the mountains.  The air is rich with the smells of exotic fragrances, "
    + "herbs, and coffee borne on a cool, misty breeze from the bay." + plaza;
    break;

    case TOD_DAY:
    desc += "The pristine marble of the Court d'Plaisir and its buildings "
    + "gleams in the midday sun as nobles, bureaucrats, and visitors crowd "
    + "the plaza with the noisy murmurings of their servants and business "
    + "of the day, likely to be pampering.  The air is rich with the smells "
    + "of exotic fragrances, herbs, and coffee borne on a cool breeze from "
    + "the bay." + plaza;
    break;

    case TOD_TWILIGHT:
    desc += "The translucent marble of the Court d'Plaisir and its buildings "
    + "catches the last rays of the sun appearing to glow of its own accord "
    + "as the evening crowd comes out to walk, mingle, and relax at the "
    + "service establishments of the plaza.  The air is rich with the smells "
    + "of exotic fragrances, herbs, and coffee borne on a cool breeze from "
    + "the bay." + plaza;
    break;

    case TOD_NIGHT:
    desc += "The moon and stars shed pale light across the translucent "
    + "marble of the Court d'Plaisir and its buildings amplifying the "
    + "yellow glow of the street lamps.  Nobles and their servants still "
    + "come and go along with other varied citizens enjoying the services "
    + "of the plaza at all hours.  The air is rich with the smells of exotic "
    + "fragrances, herbs, and coffee borne on a cool, night breeze from the "
    + "bay." + plaza;
    break;

    default:
    break;
    }
    return desc;
}

void
reset_palan_room()
{
    if (!dbin)
    {
        dbin = clone_object(OBJ + "disposal_bin");
        dbin->move(TO);
    }
}

void
create_palan_room()
{
    SHORT("The Court d'Plaisiri");
    LONG("@@get_time_desc@@");

    ITEM(({"plaza", "court"}), "The court is busy at all hours providing "
    + "pleasurable services in the nobles quarter.  Have a <look> around.\n");
    ITEM(({"large two-story shop", "north shop", "two-story shop",
      "large shop"}), "The shop to the north is large with six marble "
    + "pillars rising to its second story.  Above the pillars hung taut "
    + "from dark green iron bars is a green and white silk banner.\n");
    ITEM(({"ivy", "pillars", "ivy entwined pillars"}), "Six tall, marble "
    + "pillars chiseled simply in the old style rise before the shop to "
    + "the north up to its second story.  Vines of cultured ivy spiral "
    + "up them, their leaves gently waving in the breeze.\n");
    ITEM(({"green-trimmed white silk banner", "banner", "silk banner",
      "green-trimmed banner", "white banner", "white silk banner"}),
      "The banner hangs taut diagonally between dark green bars high "
    + "above the pillars of the shop to the north.  Its bright, white "
    + "silk is trimmed with a border of green.  Upon it is the face of "
    + "a woman viewed from off center to her left as if she is turning "
    + "to look at you.  Her skin is pale, her eyes golden almonds, and "
    + "her very light, golden brown hair is highlighted blond and hanging "
    + "about her shoulders.  The tip of her ear pokes out from her shining "
    + "locks almost pointedly.  Lower on the banner \"Dienya\" is written "
    + "in the old style.\n");
    ITEM(({"dark green bars", "bars", "dark bars", "green bars"}), "Small "
    + "bars of painted, green iron hold taut a green and white silk banner "
    + "high above the pillars of the north shop.\n");
    ITEM(({"wide one-story cafe", "cafe", "wide cafe", "east cafe",
      "one-story cafe"}), "Outside the cafe to the east are white-enameled "
    + "iron chairs and tables under a long, green canopy.  Written in "
    + "green-bordered, white letters arcing across its wide windows are the "
    + "words \"The Mer-Cantile\".\n");
    ITEM(({"canopy", "green canopy"}), "A long, green canopy extends the "
    + "length of the cafe to the east.  Beneath it are several "
    + "white-enameled iron chairs and tables.\n");
    ITEM(({"white-enameled iron chair", "white-enameled iron chairs",
      "white-enameled iron table", "white-enameled iron tables",
      "iron chair", "iron chairs", "chair", "chairs", "white-enameled chair",
      "white-enameled chairs", "iron table", "iron tables", "table", "tables",
      "white-enameled table", "white-enameled tables"}), "Sturdy, curling, "
    + "white-enameled, wrought iron chairs and tables are arrayed beneath "
    + "the long, green canopy of the cafe to the east.  You may sit at them "
    + "if you like.\n");
    ITEM(({"image", "mermaid", "image of a mermaid"}), "Upon the tall, green "
    + "column rising from the east cafe is the image of a mermaid.  She is "
    + "done in the old style with white lines over the green of the column.  "
    + "Poised as if sitting on something, her left arm is raised welcomingly "
    + "as she smiles with her long hair somewhat concealing her breasts.\n");
    ITEM(({"tall green column", "tall column", "green column", "column"}),
      "A tall, four-sided green column rises from the top of the cafe to the "
    + "east.  On each of its sides is the image of a mermaid.\n");
    ITEM(({"spa", "laethorian spa", "south building"}), "South is a building "
    + "of pristine marble done in classic old style.  Chiseled into the "
    + "marble above its entrance are the words \"Laethorian Spa and Body\"."
    + "\n");
    ITEM(({"words", "chiseling", "chiselwork"}), "Chiseled in the old, clean "
    + "lines of the old style into the marble over the building to the south "
    + "are the words \"Laethorian Spa and Body\".\n");
    ITEM(({"se alley", "southeast alley", "se side street",
           "southeast side street"}), "A side street leads southeast between "
    + "buildings to an old door of dark oak in the rear of a modest estate."
    + "\n");
    ITEM("modest estate", "A modest and clean, two-story estate can be "
    + "glimpsed down a side street to the southeast.  Upon its old, rear "
    + "door of dark oak is carved \"Gui's Wine Cellar\".\n");
    ITEM(({"old door", "dark door", "oak door", "dark oak door"}), "Down an "
    + "<alley> to the southeast in the rear of a modest estate is an old door "
    + "of dark oak upon which is carved \"Gui's Wine Cellar\".\n");
    ITEM(({"ne shop", "northeast shop", "small shop"}), "A small shop sits "
    + "off the court to the northeast.  It is a simple, marble building with "
    + "a wooden plaque posted above its doorway. It's open if you would "
    + "like to enter.\n");
    ITEM(({"shop", "shops"}), "There are several shops around the court. You "
    + "could take a look at a particular one like the northeast shop.\n");
    ITEM(({"plaque", "wooden plaque"}), "It reads:  \"Jordesse Parfumerie\".\n");
    
    add_alley("se", "southeast", NOBLE + "vintner");

    EXIT(NOBLE + "fineclothing", "north", 0, 0);
    EXIT(NOBLE + "best_cafe", "east", "@@check_combat@@", 0);
    EXIT(NOBLE + "spa", "south", 0, 0);
    EXIT(NOBLE + "n08", "west", 0, 0);
    
    CMD(({"northeast shop","ne shop", "small shop"}),({"enter"}),
          "@@enter_parfumerie");
    CMD("shop", "enter", "Enter which shop? There are several in the "
        + "court.\n");
    
    set_tell_time(180);

    add_tell("@@get_tell_time@@" + "\n");

    add_smell("vampire", "Misty air blowing south off the bay mingles here "
    + "with the smells of a large city thick with men.  Your heightened "
    + "sense of smell picks up the dark, earthy aromas of coffees from the "
    + "east, stimulants and herbs being used in blends from the spa to the "
    + "south, exotic perfumes wafting in from a small shop northeast of you, "
    + "and human and other wines from an old door of dark oak down a side "
    + "street to the southeast.  Despite the plentitude of odours swirling "
    + "around you, they are all subdued by the scent of human blood "
    + "insipidly underlying it all.");
    add_smell("morgul", "Through the misty air blowing south off the bay and "
    + "strong presence of human odours in this plaza you detect something "
    + "you seek... no, it's just elf to the north.  You smell rich, dark "
    + "coffees being served in the cafe to the east, a blend of stimulants "
    + "and herbs being used in the spa south of you, and the smell of wine "
    + "coming from an old door of dark oak down a side street to the "
    + "southeast.");
    
    add_smell("human", "Misty air blowing south off the bay mingles here "
    + "with the familiar smells of food, wine, coffee, and people at their "
    + "business in the court.  A variety of fresh, rich coffee aromas wafts "
    + "in strongly from the east cafe, and from the spa to the south come "
    + "the smells of invigorating herbal blends.  Your nose catches a hint "
    + "of perfumes coming from a small shop to the northeast and the "
    + "smell of deep toned wines from an old door of dark oak down a side "
    + "street to the southeast.");
    add_smell("elf", "Misty air blowing south off the bay mingles here "
    + "with the distinctly human scents of food and drink.  Strong, fresh "
    + "coffee aromas waft in from the east cafe, and from the spa to the "
    + "south come the smells of a blend of stimulating, fresh herbs.  Your "
    + "keen nose detects fragrant and exotic perfumes coming from a small "
    + "shop to the northeast and the smell of human and other wines from "
    + "an old door of dark oak down a side street to the southeast.");
    add_smell("goblin", "Misty air blowing south off the bay mingles here "
    + "with hint of food and... Mmmmm, there's alcohol near towards the "
    + "southeast.  Flowery human smells come from the northeast, strong "
    + "coffee smells from the east cafe, and the stink of mixed up herbs "
    + "in the south spa.");
    add_smell("dwarf", "The misty air blowing south off the bay, though "
    + "strong with human smells is clean enough to breathe.  Your dwarven "
    + "nose picks up the smell of wine coming from the southeast alley, "
    + "overpowering flowery smells from the northeast shop, and rich, "
    + "fresh coffees from the east cafe.  A strange mix of stimulating "
    + "herbs comes from the spa south of you.");
    add_smell("hobbit", "Misty air blowing south off the bay mingles here "
    + "creating a pleasant swirling blend of perfumes, coffee, herbs, and "
    + "even wine!  The perfumes are coming from an out of the way small "
    + "shop to the northeast, the coffees from the east cafe, and the "
    + "wines from somebody's cellar down the side street to the southeast.  "
    + "The herbs are strong from the spa to the south making your head "
    + "buzz.");
    add_smell("gnome", "The misty air blowing south off the bay is good "
    + "enough to breathe at the moment as it mingles here with the many, "
    + "strong inviting human smells from the buildings of the court like "
    + "the herb stimulants from the spa to the south, flowery smells "
    + "from the northeast shop, and most importantly strong, fresh, rich, "
    + "aromatic coffee from the east cafe!");
    add_smell("minotaur", "Misty air blowing south off the bay mingles here "
    + "with the flowery perfumes used to mask the scent of humans in the "
    + "small shop to the northeast, the aroma of vine alcohol down the "
    + "southeast alley, strong coffees from the east cafe, and a blend of "
    + "herbs from the south spa that itch at your nose.");
    add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
    + "with the not unfamiliar smells of food, wine, coffee, and people at "
    + "their business in the court.  A variety of fresh, rich coffee aromas "
    + "wafts in strongly from the east cafe, and from the spa to the south "
    + "come the smells of invigorating herbal blends.  Your nose catches a "
    + "hint of perfumes coming from a small shop to the northeast and the "
    + "smell of deep toned wines from an old door of dark oak down a side "
    + "street to the southeast.");
    add_smell("halfelf", "Misty air blowing south off the bay mingles here "
    + "with the not unfamiliar smells of food, wine, coffee, and people at "
    + "their business in the court.  A variety of fresh, rich coffee aromas "
    + "in strong from the east cafe, and from the spa to the south come the "
    + "wafts smells of stimulating, fresh herbs.  Your keen nose catches a "
    + "hint of perfumes coming from a small shop to the northeast and the "
    + "smell of human and other wines from an old door of dark oak down a "
    + "side street to the southeast.");
    add_smell("orc", "Misty air blowing south off the bay mingles here "
    + "with the enticing smell of manflesh and what's that... a hint of "
    + "elf to the north?  The smell of drink comes to your nose from the "
    + "southeast alley, strong, dark coffee from the east cafe, strange "
    + "herbs from the south spa, and flowery smells from the northeast.");
    add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
    + "with the abundant odours of human flesh in this court like their "
    + "scent masking perfumes coming from the small shop in the northeast, "
    + "strong, dark coffees from the east cafe, and herb stimulants from the "
    + "south spa.  Your trained nose doesn't miss either the smell of "
    + "fermented grapes coming from an old door of dark oak down a side "
    + "street to the southeast.");
    add_smell("kender", "Ooooo!  You are almost overwhelmed as you catch a "
    + "whiff of the misty air blowing south off the bay mingling with "
    + "exciting herbal blends from the spa to the south, rich, aromatic "
    + "coffees and perhaps treats from the east cafe, exotic perfumes "
    + "from the northeast shop, sweet and happy varieties of wines from "
    + "the dark oak door down the side street to the southeast, and even "
    + "the strong odours of dyed cloth to the north!  Human cities are "
    + "certainly very rich with things to discover and places to explore.");
    add_smell("drow", "Jiv'elgg!  You focus hard to maintain composure "
    + "and keep from retching at the overwhelming stink of humans and "
    + "overdwellers in this crowded plaza.  Still you can pick out the "
    + "scents of human wines from the side street to the southeast, "
    + "herbs and stimulants from the spa to the south, rich, earthy "
    + "coffee aromas from the east cafe, and bizarre, posibbly poisonous "
    + "fauna from the northeast.");
    add_smell("noldor", "The scent of humans is strong in the "
    + "air along with the smells that accompany so many of their dwellings.  "
    + "Misty air blowing south off the bay mingles here with the distinctly "
    + "human scents of food and drink.  Strong, fresh coffee aromas waft in "
    + "from the east cafe, and from the spa to the south come the smells of "
    + "a blend of stimulating, fresh herbs.  Your keen nose detects fragrant "
    + "and exotic perfumes coming from a small shop to the northeast and "
    + "the smell of human and other wines from an old door of dark oak "
    + "down an alley to the southeast.");
    add_smell("unknown", "Misty air blowing south off the bay mingles here "
    + "with the familiar smells of food, wine, coffee, and people at their "
    + "business in the court.  A variety of fresh, rich coffee aromas wafts "
    + "in strongly from the east cafe, and from the spa to the south come "
    + "the smells of invigorating herbal blends.  Your nose catches a hint "
    + "of perfumes coming from a small shop to the northeast and the "
    + "smell of deep toned wines from an old door of dark oak down a side "
    + "street to the southeast.");

    reset_palan_room();
}

/* 
 * The following large strings are the room emotes that vary depending
 * on what time of day you're in the plaza. 
 */

string
get_tell_time()
{
    string ttell = "";
    
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    ttell += one_of_list(({"The aroma of flavourful, fresh-brewed coffee "
    + "wafts on a cool morning breeze under your nose from the cafe to the "
    + "east.",
      "A pair of noble ladies share hushed gossip as they make their way "
    + "across the court with a retinue of servants in tow.",
      "White-clad streetwashers put the finishing touches on the court as "
    + "they sweep and scrub efficiently.",
      "A gathering of merchants walks past you discussing the details "
    + "of a shipment of cloth.",
      "A flock of pigeons flutters into the air from atop a nearby "
    + "building.",
      "A cool morning breeze off the bay ruffles banners and sways signs.",
      "A page walks unhurriedly past you.",
      "A small group of well-dressed ladies enters the spa to the south "
    + "with eager anticipation in their voices."}));

    break;

    case TOD_DAY:
    ttell += one_of_list(({"A path clears before a merchant leading a line "
    + "of packmen carrying large bolts of cloth into the shop to the north "
    + "under the midday sun.",
      "A knight, his squire marching behind him carrying several packs, makes "
    + "his way through the crowd on foot to the spa in the south.",
      "A few aesthetics in vigorous discussion make their way east "
    + "across the court into the cafe.",
      "A cloud passes across the sun for a moment.",
      "The clouds drift gently across the sky spreading their bulbous "
    + "shadows across the plaza.",
      "A page walks unhurriedly past you.",
      "A messenger jogs swiftly past you.",
      "A very well-dressed gentleman arrives in the court from the shop to "
    + "the north.\nA very well-dressed gentleman leaves west.",
      "A rosy-cheeked noble lady arrives in the court from the spa to the "
    + "south and enters the cafe east."}));

    break;

    case TOD_TWILIGHT:
    ttell += one_of_list(({"An official walks past you into the east cafe.",
      "An elegantly dressed lady escorted by a pair of chainmailed guards "
    + "enters a shop in the northeast of the court as she fans herself with "
    + "a small foldout fan.",
      "A grey cloaked female human bumps into your side and then is gone, just "
    + "another face in the crowd.",
      "The aroma of coffee with a hint of caramel wafts on a breeze under "
    + "your nose from the east cafe.",
      "A wide-eyed squire of Solamnia walks slowly across the court staring "
    + "at the well-dressed ladies of the court.",
      "A cloaked noble accompanied by a pair of knights and a "
    + "retinue of courtesans enter the spa to the south.",
      "A cool breeze off the bay ruffles banners and sways signs.",
      "A page walks unhurriedly past you.",
      "A messenger jogs swiftly past you."}));

    break;

    case TOD_NIGHT:
    ttell += one_of_list(({"A grey cloaked male human bumps into your side "
    + "and then is gone, just another face in the court under the stars.",
      "A constable looks you over slowly before nodding his head and "
    + "continuing on across the lamp-lit court.",
      "A reveler sings a tavern ditty about a kender, a deep pocket, "
    + "fumbling in the dark, and something you can't clearly make out as "
    + "his voice trails off into the night.",
      "Arriving from the spa to the south, a young woman helps a reveler "
    + "leaning on her shoulder cut a crooked path west across the court.",
      "A squire of Solamnia walks along slowly across the plaza pausing "
    + "to stare at the ladies of the court, a skin of wine in his hand.",
      "A moustachioed parliamentarian and a page walk through the court "
    + "carrying a bottle of wine you notice as they pass briefly beneath a "
    + "lit lamp post.",
      "Clouds pass briefly across the night sky overhead leaving only yellow "
    + "lamp light on the translucent white streets.",
      "A shadow passes over the roof of a nearby building.",
      "A messenger jogs swiftly past you.",
      "The lamp atop a tall, grey lamp post nearby flickers briefly in the chill "
    + "night breeze."}));

    break;

    default:
    break;
    }
    return ttell;
}

/*
 * This function is what sets the room_tells a-workin.
 */

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

enter_parfumerie() 
{ 
  write("You enter the northeast shop Jordesse Parfumerie.\n"); 
  this_player()->move_living("entering a shop in the northeast of the court",
      NOBLE + "parfumerie", 1, 0);
  return ""; 
}

void 
init()
{    
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}

/* This checks whether the player has been in combat in the last 45 - 55s
 * and blocks entry to the Mer-Cantile Cafe east if so. It's a safe room,
 * so we don't want it abused.
 */
int
check_combat()
{
    if (time() - TP->query_combat_time() > (45 + random(11)))
    {
        return 0; // Proceed.
    }
    write("You must be peaceful for a minute before you may enter "
    + "this place of safety.\n");
    return 1; // Denied!
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting by a table! How do you "
                + "expect to sit in two places at once?\n");
                return 1;
        }
          
        if(str == "around table" | str == "around a table" | 
           str == "at table" | str == "at a table" | str == "by table" |
           str == "by a table" | str == "table" | str == "chair" |
           str == "chair around table" | str == "in chair around table" |
           str == "in a chair around a table" | str == "chair at table" |
           str == "in chair at table" | str == "in a chair at a table" |
           str == "chair by table" | str == "in chair by table" |
           str == "in a chair by a table" | str == "in chair") 
        {
                TP->catch_msg("You sit down in one of the white-enameled "
                + "iron chairs near a table outside the east cafe.\n");
                say(QCTNAME(TP) + " sits down in one of the white-enameled "
                + "iron chairs at a table by the east cafe.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a "
                + "white-enameled iron chair outside the east cafe");
                return 1;
        }
    
        else
        {
                TP->catch_msg("Where would you like to sit?  At a table?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up" || str != "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the table.\n");
                        say(QCTNAME(TP)+" stands up from the table.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }

        }
        
        else
        {
                TP->catch_msg("Stand?  Stand up?\n");
                return 1;
        }
        
        return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the table before leaving.\n");
                say(QCTNAME(TP) + " stands up from the table as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }

}
