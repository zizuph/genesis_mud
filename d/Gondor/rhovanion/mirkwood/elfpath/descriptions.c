/* Common descriptions used in the old road rooms */

void add_location_long()
{
    add_long(get_random_message(({
        "You are traveling along the elven path " + 
        VBFC("location_desc") + " of Mirkwood. ",
        
        "You are walking on the elven path " +
        VBFC("location_desc") + " of Mirkwood. ",

        "You find yourself somewhere along the elven " +
        "path, which runs to the east and " +
        "to the west " + VBFC("location_desc") +
        " Mirkwood forest. ",

        "You are " + VBFC("location_desc") + " of Mirkwood " +
        "forest, where the elven runs in " +
        "a straight line east and west. ",

        "You are somewhere " + VBFC("location_desc") + " of " +
        "Mirkwood, following the elven path which " +
        "runs both and east and west from here. ",

        "You are on the elven path as it passes " +
        "along " + VBFC("location_desc") + " of " +
        "Mirkwood forest. ",

        "This part of the elven path is somewhere " +
        VBFC("location_desc") + " of Mirkwood. ",

        "Shadows have been draped all around you as you " +
        "follow the elven path here " + VBFC("location_desc") +
        " of Mirkwood forest. ",

        "Trees crowd overhead as the elven path tunnels itself " +
        "through them to both the east and west here " +
        VBFC("location_desc") + " of the legendary Mirkwood forest. ",

        "You are " + VBFC("location_desc") +
        " of Mirkwood forest, where you can see the elven " +
        "path stretching out to both the east and west. "
        })), LIGHT_ALL);
}

void add_tree_long()
{
    add_long(get_random_message(({
        "Immediately surrounding you are the many tall trees " +
        "towering high over your head, blocking out most of the " +
        "light from the " + VBFC("sun_moon") + ". ",

        "On either side of the path, the massive trees arch " +
        "their branches, blocking out " +
        "the " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + ". ",

        "Everywhere you look, on either side of the " +
        "path, all you seem to see are the tall, " +
        "black trees of Mirkwood. ",

        "The " + VBFC("light_type") + " from the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " seems to be heavily obscured " +
        "by the tall black trees which dominate your " +
        "view on both sides of the road. ",

        "All around you, dozens of imposing trees seem " +
        "to hide you away from the "  + VBFC("light_type") +
        " which undoubtedly shines outside the forest. ",

        "The tall, imposing trees of the great forest " +
        "which surround you here have shut you away " +
        "from the " + VBFC("daylight_desc") + ", as they " +
        "instead embrace you deep within their dark shadows. ",

        "An endless line of massive black trees " +
        "prevents you from seeing very far in " +
        "any direction, save where the safety of the " +
        "well-worn elven path tunnels away to the " +
        "east and west. ",
      
        "Towering high over your head, dozens of tall " +
        "black trees block out almost every last " +
        "bit of light from the " + VBFC("sun_moon") + ". ",
      })), ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
}

void add_emo_long()
{
    add_long(get_random_message(({
        "Perhaps it is just the reputation Mirkwood has, but " +
        "you are certain you can feel the massive trees of the " +
        "forest moving ever closer as they crowd the path. You " +
        "feel an almost uncontrollable urge to move just a " +
        "little bit faster. ",

        "Sudden sounds and fleeting glimpses of shadows " +
        "moving between the black trees of Mirkwood catch your " +
        "undivided attention. You wish you could see the " +
        VBFC("day_desc") +  " " + VBFC("sun_moon") + 
        " from here, if only to reassure yourself that you " +
        "will not be trapped in this opressive darkness " +
        "forever. ",

        "You have heard tales that at one time, this massive " +
        "forest was once known as Greenwood the Great. Yet, " +
        "as you peer around the shadows of the imposing black " +
        "trees which loom ominously over every inch of the " +
        "air above you, it is hard to imagine a more appropriate " +
        "name than Mirkwood. You cannot help but feel that the " +
        "sooner you leave this forest, the safer you will be. ",

        "On the both sides of the path, right beside you " +
        "yet hidden deep within the shadows of the " +
        "tall, black trees of Mirkwood forest; you can hear the " +
        "occasional snapping of twigs followed by brief glimpses " +
        "of what appear to be sinister, glowing eyes. It is " +
        "almost as if something in the forest is following you, " +
        "just waiting for you to step away from the safety of " +
        "the elf path. ",

        "On the north side of the path, right beside you " +
        "yet hidden deep within the shadows of the " +
        "tall, black trees of Mirkwood forest; you can hear the " +
        "occasional snap of a twig followed by a brief glimpse of " +
        "what appears to be a pair of sinister, glowing eyes. It " +
        "is almost as if something in the forest is following you, " +
        "just waiting for you to step away from the safety of " +
        "the elf path. ",

        "On the south side of the path, right beside you " +
        "yet hidden deep within the shadows of the " +
        "tall, black trees of Mirkwood forest; you can hear the " +
        "occasional snap of a twig followed by a brief glimpse of " +
        "what appears to be a pair of sinister, glowing eyes. It " +
        "is almost as if something in the forest is following you, " +
        "just waiting for you to step away from the safety of " +
        "the elf path. ",

        "It is around " + VBFC("day_desc") + ", or so you think. " +
        "It is hard to tell by the lack of " + VBFC("daylight_desc") +
        " which cannot penetrate the blanket of trees which loom " +
        "over your head. You feel a little nervous not being able " +
        "to tell, and the eerie feeling you have of being watched " +
        "does not seem to make it any better. You cannot wait to " +
        "get out of this place. ",

        "A shiver runs up your spine as you glance furitively around " +
        "in every conceivable direction. You cannot seem to shake " +
        "the unmistakable feeling that someone, or perhaps something, " +
        "is constantly observing you. Waiting for you. Every " +
        "single story you have heard about the dangers of Mirkwood " +
        "seems to be screaming in your brain and you feel the urge " +
        "to leave this forest as quickly as possible. ",

        "On the north side of the path, you can see the bushes " +
        "rustle and move about as something conceals itself away " +
        "from any hint of the " + VBFC("day_desc") + " that could " +
        "have possibly penetrated the thick canopy of trees which " +
        "covers you. No matter which way you go, the sounds of " +
        "movement seem to follow you. You seem to recall some " +
        "advice which suggests you should never leave the elf path " +
        "when travelling in Mirkwood, and right now, you can " +
        "understand exactly what they meant. ",

        "As you look around in this part of the great forest " +
        "of Mirkwood, you catch fleeting glimpses of sinister " +
        "looking eyes which glitter in the shadows of the black " +
        "trees. Your heart starts to beat just a little faster " +
        "as you wonder just who, or what, is out there watching " +
        "you so intently. ",
    })), ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
}

void add_long_spiders_close()
{
     add_long(get_random_message(({
        "As you examine the trees which surround you, a very " +
        "unsettling feeling descends upon you. Dozens of " +
        "massive spider webs seem to decorate every " +
        "branch and tree trunk.",

        "Draped haphazardly across the branches and bushes " +
        "that surround you are the scattered remains of " +
        "massive spider webs. It would probably not be " +
        "a good idea to examine them too closely or to " +
        "follow them into the woods beyond the path. ",

        "All around you, across the trees and undergrowth, " +
        "you can see thick clumps of webbing clinging to " +
        "almost every branch and bush. You get a little " +
        "nervous when you consider how big the spiders " +
        "would have to be to create webs like these.",

        "On both sides of the path, massive spider webs " +
        "have been casually draped between thick tree " +
        "trunks. Common sense tells you that wandering " +
        "off the elf path into Mirkwood forest would be very " +
        "dangerous here. ",

        "With increasing frequency, massive spider webs either " +
        "hang down from most of the branches here, or are strung " +
        "up between massive tree trunks. Logic tells you " +
        "that any spider big enough to spin such webs is " +
        "likely to be a dangerous threat to you. ",
      })), ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
}
