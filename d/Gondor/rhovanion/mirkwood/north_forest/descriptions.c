/* Common descriptions used in the old road rooms */

void add_location_long()
{
    add_long(get_random_message(({
        "You are traveling through heavy underbrush, somewhere " + 
        VBFC("location_desc") + " of Mirkwood. ",
        
        "You are pushing your way through black trees and heavy brush " +
        "somewhere " +VBFC("location_desc") + " of Mirkwood. ",

        "You find yourself in the middle of a small clearing " +
        "amidst the black trees of Mirkwood. You are not certain " +
        "exactly where, but you think you are north of the " +
        "elf path, somewhere " +  VBFC("location_desc") + " Mirkwood forest. ",

        "You think you are " + VBFC("location_desc") + " of Mirkwood " +
        "forest, somewhere north of the elven path. ",

        "You are probably somewhere " + VBFC("location_desc") + " of " +
        "Mirkwood, but it is difficult to tell in the middle of " +
        "the shadows created by the heavy forest. ",

        "Black trees blot out the " + VBFC("day_desc") + 
        "as they tower high over your head. It is difficult " +
        "to say, but you suspect you are somewhere " +
        VBFC("location_desc") + " of Mirkwood. ",

        "A small clearing in the forest has opened up beside you here. " +
        "However, the treetops still crowd the sky above you here, and " +
        "you can only guess that you are somewhere " +
        VBFC("location_desc") + " of Mirkwood. ",

        "Shadows have been draped all around you as you " +
        "wander through the brush here, somewhere " + VBFC("location_desc") +
        " of Mirkwood forest. ",

        "Trees crowd overhead, obscuring your view of the sky above. " +
        "Meanwhile, it appears that virtually everywhere you look, " +
        "the only option left is to attempt to continue to tunnel your " +
        "way through the underbrush here, somewhere " +
        VBFC("location_desc") + " of the legendary Mirkwood forest. ",

        "You think you are " + VBFC("location_desc") +
        " of Mirkwood forest, but it is difficult to judge since " +
        "all you can see is an endless line of trees and brush " +
        "in every direction. ",

        "You find yourself in a small glade, deep within the confines " +
        "of the mighty Mirkwood forest. High above you, the " + VBFC("day_desc") +
        "is barely visible beyond the treetops looming overhead. ",

        "Endless varities of thick bushes cling desperately to your " +
        "feet as you attempt to trudge your way through the black trees " +
        "of the legendary Mirkwood forest. ",
        })), LIGHT_ALL);
}

void add_tree_long()
{
    add_long(get_random_message(({
        "Immediately surrounding you are the many tall trees " +
        "towering high over your head, blocking out most of the " +
        "light from the " + VBFC("sun_moon") + ". ",

        "Tall, black trees create the oppressive darkness of " +
        "Mirkwood, obscuring your vision of the " + VBFC("day_desc") +
        "above, silently encouraging you to find the safety of a " +
        "path or road. ",

        "On every side, the massive trees arch " +
        "their branches, blocking out " +
        "the " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + ". ",

        "Everywhere you look, on every side, " +
        "all you seem to see are the tall, " +
        "black trees of Mirkwood. ",

        "The " + VBFC("light_type") + " from the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " seems to be heavily obscured " +
        "by the tall black trees which dominate your " +
        "view everywhere you look. ",

        "All around you, dozens of imposing trees seem " +
        "to hide you away from the "  + VBFC("light_type") +
        " which undoubtedly shines outside the forest. ",

        "The tall, imposing trees of the great forest " +
        "which surround you here have shut you away " +
        "from the " + VBFC("daylight_desc") + ", as they " +
        "instead embrace you deep within their dark shadows. ",

        "An endless line of massive black trees and thick " +
        "underbrush prevents you from seeing very far in " +
        "any direction. ",
      
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
        "forest moving ever closer as they crowd around you. You " +
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

        "Everywhere you turn your eyes, thousands of black shadows " +
        "hide within the inky darkness of the shadow. There seems " +
        "to be the persistent, uncomfortable feeling that someone " +
        "or something is patiently watching you. The longer you are " +
        "here in this forest, the greater your desire to escape " +
        "becomes. ",

        "You pause a brief moment to catch your breath and look " +
        "at the forest around you, judging it to be somewhere " +
        "around " + VBFC("day_desc") + " or so, but really, " +
        "how can you really be certain in a forest as deep and " +
        "dark as this one. There is a nervous tingle in your " +
        "spine that simply will not disappear the more time " +
        "you spend here. ",

        "Trapped within the dark gloom of the forest, you can hear the " +
        "occasional snapping of twigs followed by brief glimpses " +
        "of what appear to be sinister, glowing eyes. It is " +
        "almost as if something here is following you, " +
        "just waiting for you to be just a little less alert. ",

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

        "Off to your right, you can see the bushes " +
        "rustle and move about as something conceals itself away " +
        "from any hint of the " + VBFC("day_desc") + " that could " +
        "have possibly penetrated the thick canopy of trees which " +
        "covers you. No matter which way you go, the sounds of " +
        "movement seem to follow you. Perhaps this is why it is " +
        "said that you should never stray from the path in Mirkwood. ",

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
        "branch and tree trunk. ",

        "Draped haphazardly across the branches and bushes " +
        "that surround you are the scattered remains of " +
        "massive spider webs. It would probably not be " +
        "a good idea to examine them too closely. ",

        "All around you, across the trees and undergrowth, " +
        "you can see thick clumps of webbing clinging to " +
        "almost every branch and bush. You get a little " +
        "nervous when you consider how big the spiders " +
        "would have to be to create webs like these. ",

        "All around you, massive spider webs " +
        "have been casually draped between thick tree " +
        "trunks. Common sense tells you that wandering " +
        "any closer to these webs would be very dangerous. ",

        "With increasing frequency, massive spider webs either " +
        "hang down from most of the branches here, or are strung " +
        "up between massive tree trunks. Logic tells you " +
        "that any spider big enough to spin such webs is " +
        "likely to be a dangerous threat to you. ",
      })), ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
}
