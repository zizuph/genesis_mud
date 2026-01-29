/* Common descriptions used in the old road rooms */

void add_location_long()
{
    add_long(get_random_message(({
        "You are traveling through heavy underbrush, somewhere " + 
        VBFC("location_desc") + " forest. ",
        
        "You are pushing your way through black trees and heavy brush " +
        "somewhere " +VBFC("location_desc") + ". ",

        "You find yourself in the middle of a small clearing " +
        "amidst the black trees of Mirkwood. You are not certain " +
        "exactly where, but you think you are south of the " +
        "old road, somewhere " +  VBFC("location_desc") + " forest. ",

        "You think you are " + VBFC("location_desc") + " " +
        "forest, somewhere south of the old road. ",

        "You are probably somewhere " + VBFC("location_desc") + " " +
        ", but it is difficult to tell in the middle of " +
        "the shadows created by the heavy forest. ",

        "As best you can determine, you are currently walking " +
        "somewhere " + VBFC("location_desc") + ", south of " +
        "the old road. ",

        "Dark shadows dance all around, making it difficult to " +
        "navigate properly, but you believe you are currently " +
        "somewhere " + VBFC("location_desc") + " forest. ",

        "Without being able to see the sky clearly, it is hard to " +
        "say for certain, but you believe you are currently somewhere " +
        VBFC("location_desc") + ". ",

        "You are attepmting to forge a path somewhere deep in the " +
        "wild tangles " + VBFC("location_desc") + " forest. ",

        "Pushing your way through the dark shadows somewhere " +
        VBFC("location_desc") + ", you find it increasingly " +
        "difficult to navigate properly. ",

        "It is difficult " +
        "to say precisely, but you suspect you are somewhere " +
        VBFC("location_desc") + ". ",

        "A small clearing in the forest has opened up beside you here. " +
        "However, the treetops still crowd the sky above you here, and " +
        "you can only guess that you are somewhere " +
        VBFC("location_desc") + ". ",

        "Shadows have been draped all around you as you " +
        "wander through the brush here, somewhere " + VBFC("location_desc") +
        " forest. ",

        "Trees crowd overhead, obscuring your view of the sky above. " +
        "Meanwhile, it appears that virtually everywhere you look, " +
        "the only option left is to attempt to continue to tunnel your " +
        "way through the underbrush here, somewhere " +
        VBFC("location_desc") + " forest. ",

        "You think you are " + VBFC("location_desc") +
        " forest, but it is difficult to judge since " +
        "all you can see is an endless line of trees and brush " +
        "in every direction.",

        "You find yourself in a small glade, deep within the confines " +
        "of the mighty Mirkwood forest. High above you, the " + VBFC("day_desc") +
        "is barely visible beyond the treetops looming overhead.",

        "Endless varities of thick bushes cling desperately to your " +
        "feet as you attempt to trudge your way through the black trees " +
        "of the legendary Mirkwood forest.",

        "You are walking through a shallow valley, somewhere " +
        VBFC("location_desc") + " forest, hidden behind thousands " +
        "of great black trees. ",

        "You are currently atop a small rise, surrounded by hundreds " +
        "of tall, black trees somewhere deep within Mirkwood forest. ",

        "You think you might be lost, somewhere deep within the " +
        "mysterious confines of the legendary Mirkwood forest. ",

        "Tall, black trees and dark shadows surround you somewhere " +
        VBFC("location_desc") + " forest. ",

        "You are finding travel difficult in this part of the forest, " +
        "as the underbrush is so thick and wild it impedes your " +
        "movement in all directions ",

        "Thick, rich foliage obscures your vision in all directions " +
        "as you are wandering here in the shadows, somewhere in " +
        "Mirkwood forest. ",

        "As best you can judge, you are stuck deep within the legendary " +
        "Mirkwood forest, somewhere south of the old road. ",

        "Branches and brush grab at your arms and legs as you attempt " +
        "to push your way through the trees somewhere " +
        VBFC("location_desc") + " forest. ",

        "The underbrush grabs at your ankles with every step here, " +
        "clinging possessively as you make your way through " +
        "the legendary Mirkwood forest. ",

        "You are " + VBFC("location_desc") + " forest, somewhere " +
        "south of the old road. ",

        "It is quite easy to get turned around here, but you are " +
        "reasonably certain that you are south of " +
        "the old road, somewhere " + VBFC("location_desc") + " forest. ",

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

        "Thick branches from the black trees of Mirkwood stretch " +
        "out in shadow, hanging above the dense undergrowth below. " +
        "The trees do an excellent job of preventing almost any " +
        VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + " above to reach you down here " +
        "on the forest floor. ",

        "You judge that it is probably sometime in the " +
        VBFC("day_desc") + " but as the tall, black trees of the " +
        "forest block out any of the " + VBFC("light_type") +
        "from penetrating to the forest floor, it is difficult " +
        "to be certain. ",

        "Thick, heavy underbrush huddles around the massive " +
        "trees of the forest here. It makes for difficult " +
        "travel as there is a distinct lack of paths or trails " +
        "this deep into Mirkwood. ",

        "Thick trunks of black trees obscure your view in every " +
        "direction, casting shadows everywhere you look. These " +
        "trees reach high above your head, climbing up to the " +
        VBFC("day_desc") + " sky, obscuring any hint of the " +
        VBFC("daylight_desc") + ". ",

        "High above, distant treetops block out light from the " +
        VBFC("day_desc") + " sky, covering you instead in dark " +
        "shadow. Elsewhere, the lush, green foliage from the dense " +
        "undergrowth blankets the forest floor. ",

        "Crowding around you in every direction, are the huge " +
        "trees that fill Mirkwood forest. A dense growth of " +
        "underbrush covers the forest floor, creeping up " +
        "the black bark of the trees, creating shadows that " +
        "loom ominously. ",

        "Peering past the dense undergrowth that grows so " +
        "abundantly, you see only the black bark of the " +
        "tall trees helping to cast infite shadows. This " +
        "part of the forest is quite dark, as the trees " +
        "effectively block any light from the " +
        VBFC("sun_moon") + " from shining down to the " +
        "forest floor. ",

        "The underbrush seems to be a little lighter here " +
        "when compared to what you have seen elsewhere in " +
        "Mirkwood. However, the trees are still tall and " +
        "black, preventing any light from filtering down " +
        "here to the forest floor. ",

        "As you pass through the underbrush here, you notice " +
        "the trees have gathered around to hover over a small " +
        "glen. This shallow valley feels a little more open, " +
        "but is still covered in shadow as the black trees " +
        "of Mirkwood still block the light from the " +
        VBFC("day_desc") + " sky above. ",

        "All around you, the thick undergrowth settles around " +
        "massive tree trunks, covered in a rough, black bark. " +
        "The trees are so tall that they block out any light " +
        "which might have been visible from the " + VBFC("day_desc") +
        " sky above. ",

        "As you look around, you strain your eyes to imagine " +
        "the " + VBFC("light_type") + " from the " + VBFC("day_desc") + 
        " " + VBFC("sun_moon") + " shining down upon the forest " +
        "floor. However, the massive trees of Mirkwood leave you " +
        "here in a world of shadow. There seem to be no trails " +
        "here, only the thick brush which grows haphazardly " +
        "everywhere in sight. ",

        "The " + VBFC("light_type") + " from the " + VBFC("day_desc") +
        " " + VBFC("sun_moon") + " seems to be heavily obscured " +
        "by the tall black trees which dominate your " +
        "view everywhere you look. ",

        "It seems that all you can see are the wide trunks of " +
        "the trees of the forest as they reach up to hide the " +
        VBFC("light_type") + " from reaching your eyes. " +
        "Across the forest floor, thick clumps of bushes and " +
        "brambles impede your progress in almost every " +
        "direction. ",

        "You push past the black trees of Mirkwood and find " +
        "yourself in a secluded grove where the underbrush " +
        "appears to be a little lighter than elsewhere in the " +
        "forest. Yet even here, the tall trees block the light " +
        "of the " + VBFC("sun_moon") + " from shining down. ",

        "Far above your head, thick treetops do their best to " +
        "ensure that very little of the " +
        VBFC("daylight_desc") + " can make its way down to you " +
        "on the forest floor. Instead, it feels like you will " +
        "never see anything but the black trees and the thick " +
        "underbrush that surrounds them. ",

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

        "The dense foliage of the thick underbrush which " +
        "carpets the forest floor here, makes it somewhat " +
        "difficult to walk in almost any direction. You " +
        "find that the forest is filled with shadows, " +
        "as the black trees all around you loom ominously. ",

        "Away from anything resembling a path or a trail, " +
        "you find yourself trudging through the thick bush, " +
        "attempting to move from one massive black tree to " +
        "another. The fact that almost no light from the " +
        VBFC("day_desc") + " does not make things any easier. ",

        "There are no paths or trails here, only a heavy " +
        "underbrush which covers the forest floor. Massive, " +
        "black trees stretch up far above you, leaving " +
        "the forest floor to be coated in endless shadows. ",

        "Devoid of anything resembling a path or a trail, " +
        "you wind your way past the great black trees of " +
        "Mirkwood with great difficulty. Heavy underbrush " +
        "grabs at your legs, making movement in all " +
        "directions extremely difficult. ",

        "Endless trees, covered in black bark, stretch out " +
        "before you. Reaching high up into the sky, these " +
        "trees manage to blot out most of the light from the " +
        VBFC("sun_moon") + " before it can reach down to " +
        "the thick underbrush which sprawls across the " +
        "forest floor. ",

        "You find passage very difficult amongst the black " +
        "trees and the thick underbrush, as there are no " +
        "signs of any trails or paths to make your journey " +
        "easier. The fact that the trees hide away most of " +
        "the light which shines down from the " +
        VBFC("sun_moon") +  " does not make things any " +
        "easier. ",

        "Reaching up out of the thick underbrush, endless " +
        "black trees rise tall towards the " + 
        VBFC("day_desc") + " sky above you, hiding away " +
        "most of the light from the " +
        VBFC("sun_moon") + ". There are no trails or " +
        "paths here, only shadows, and you find it very " +
        "difficult to move in almost every direction. ",

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

        "Small, glowing points of light appear in the shadows " +
        "around you, before slowing fading away. They almost make " +
        "you think that something is watching you, but it is " +
        "probably just a trick of the " + VBFC("daylight_desc") +
        " as it filters down into the dark bushes. Regardless, " +
        "you do find yourself with an urge to find a way out of " +
        "the forest. ",

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

        "On your left side, you can see some bushes " +
        "rustle, moving about as something conceals itself away " +
        "from any hint of the " + VBFC("day_desc") + " that could " +
        "have possibly penetrated the thick canopy of trees which " +
        "covers you. Yet no matter which way you go, the sounds of " +
        "movement seem to follow you. You seem to recall hearing " +
        "somewhere that it was dangerous to leave the path in " +
        "Mirkwood. ",

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

void add_path1()
{
     add_long(get_random_message(({

        "You are walking along a narrow path used by the woodsmen " +
        "of Mirkwood forest. ",

        "This narrow path which twists its way through the trees " +
        "somewhere " + VBFC("location_desc") + " forest, seems to be " +
        "mainly used by local woodsmen. ",

        "You are somewhere " + VBFC("location_desc") + " forest, " +
        "following a small path south of the old road. ",


        "You are currently on a dirt path somewhere " +
        VBFC("location_desc") + " forest which connects some " +
        "woodsmen villages to the old road. ",

    })), LIGHT_ALL);
}     

void add_path2()
{
     add_long(get_random_message(({

        "Tall black oak trees loom high above you, blocking out " +
        "the " + VBFC("daylight_desc") + " from penetraing the " +
        "ever-present gloom. Thick bushes gather around the base " +
        "of the trees, creating a barrier that seems to carefully " +
        "separate you from the forest proper. ",

        "On either side of the path, the black trees of Mirkwood " +
        "seem to loom menacingly over your head. Thick bushes and " +
        "brambles crowd the edge of the path, almost as if they are " +
        "attempting to conceal the ominous shadows that loom behind. ",

        "Thick bushes and brambles from the underbrush seem to reach " +
        "out eagerly towards the edge of the path, almost as if the " +
        "tall trees which arch overhead are attempting to reclaim this " +
        "part of the forest. ",

        "Long, leafy branches from the tall oak trees of Mirkwood " +
        "arch over your head, forming the appearance of a tunnel as " +
        "you walk along the path of the woodsmen. Thick underbrush " +
        "climbs up black tree trunks, the ragged brambles creating " +
        "a wall, encouraging you to stay upon the path. ",

})), ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));
}

void add_path3()
{
     add_long(get_random_message(({

        "Every now and then, you catch a glimpse of eyes glittering " +
        "in the shadows, as if following your every move yet unwilling " +
        "to venture upon the path you are walking along. ",

        "Dark shadows fill the woods beyond the path, with only the " +
        "faint hint of light penetrating the shadowy gloom. The " +
        "occasional rustle of the bushes is probably just local " +
        "wildlife and not anything more sinister. ",

        "Faint rustling sounds and fleetings glints of light " +
        "seem to lurk in the shadows beyond the safety of the " +
        "path, helping to remind you of the dangers of wandering " +
        "deeper into the woods. ",

        "Your eyes find it difficult to penetrate the gloom of the " +
        "forest, catching instead only the occasional shifting of " +
        "shadows and hearing the occasional rustling in the brush. " +
        "There is an everpresent feeling that Mirkwood itself is " +
        "watching you, waiting for you to leave the safety of the path. ",

})), ({ LIGHT_MIDDAY, LIGHT_BRIGHT }));   
}          