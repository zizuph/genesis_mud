#pragma save_binary
#pragma strict_types

#include "../../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <files.h>
#include <composite.h>
#include <filter_funs.h>

inherit MIRKWOOD_STD_DIR + "room";
inherit MIRKWOOD_LIB_DIR + "movement";

void create_mirkwood_cave_room() 
{


}

nomask void create_mirkwood_room() 
{
    create_mirkwood_cave_room();
    set_movement_base_directory(MIRKWOOD_CENTRAL_FOREST_DIR);

    add_long(get_random_message(({
        "You are trapped deep within a dark cave, far beneath the mountains " +
        "in Mirkwood forest. Everywhere you look, thick strands of milky-grey " +
        "spider webs hang from the walls and ceiling, even covering " +
        "the dull grey stone of the floor beneath your feet. A strong, " +
        "fetid stench, a taste full of death and decay, seems to invade " +
        "your mouth and nose without mercy. Meanwhile, the sticky, silvery " +
        "lengths of web seem to tug possessively at your head, arms and " +
        "feet with every step you attempt to make. As your eyes dart around in " +
        "the darkness, what little light you can manage simply reflects " +
        "off the webs, leaving you unable to see much of anything else " +
        "aside from the threatening jet-black shadows. Every now and then, your " +
        "hear the soft, brittle crunch of a bone breaking beneath your feet " +
        "as you attempt to navigate the uneven floor of these caves.\n", 

        "You are clawing your way through a dark tunnel, deep in the " +
        "earth below the mountains of Mirkwood forest. Heavy, thick strands " +
        "of milky-grey spider webs are draped everywhere, hanging from the  " +
        "walls and ceiling. Even the dull grey of the stone floor beneath you " +
        "is mostly obscured with masses of web. An invasive stench floods your " +
        "senses at every turn, the unpleasant smell of death and decay, while the " +
        "occasional sound of ancient bones snapping comes from beneath your " +
        "feet when you happen to step on the piles of debris hidden on the floor." +
        "No matter which way you turn, silvery lengths of spiderwebs cling " +
        "tightly to every part of your body, attempting to wrap you within " +
        "their sticky embrace. Deep shadows, darker than night seem to " +
        "confuse your eyes in every direction, as what light you are able " +
        "to create down here seems to reflect brightly against the webs, " +
        "leaving everything else in ominous shadow. The faint, scuttling " +
        "sound of scratching and scraping echoes through the tunnels, " +
        "a reminder that you are not alone down here.",

        "You are currently standing in a deep, dark spider cave, far below the " +
        "rugged mountains which rise within the legendary Mirkwood forest." +
        "Reflections of shimmering light bounce off of the thick, silvery " +
        "spiderwebs, creating shadows that your eyes cannot pierce no matter " +
        "how hard you look. These webs cover everything in sight, from the " +
        "rough stone walls and ceiling to the unexpectedly uneven rocky floor " +
        "beneath your feet. Upon occasion, your feet fall upon a webby mass " +
        "of debris, often resulting in the unpleasant snapping of the brittle " +
        "bones of some unfortunate victim. The stale air of this tunnel is " +
        "filled with the fetid stench of death and decay, plaguing your nose " +
        "and mouth despite all of your attempts to avoid it. Milky-grey ropes " +
        "of spiderweb reach out as you pass, clinging uncomfortably to your " +
        "arms, legs and even head." ,

        "You find yourself in a dark cave, tucked deep below the stony crags " +
        "of the mountains of Mirkwood. All around you, thick ropes of milky-grey " +
        "spiderweb are hungrily grabbing every single part of your body as you " +
        "pass. These sticky, silvery webs shimmer brightly wherever the light " +
        "shines upon them, making it impossible for your eyes to penetrate the " +
        "ominous black shadows which hide behind. The sound of brittle bones " +
        "snapping as you step on the occasional web-covered pile of debris is a " +
        "little unsettling, but as these spiderwebs cover everything in sight, " +
        "it seems unavoidable. The fetid stench of death and decay seems to " +
        "constantly invade your senses, making your visit down here rather " +
        "unpleasant. Faint noises of someone, or something, scratching and " +
        "scraping against the stone echo through the tunnel, reminding you " +
        "that you are not alone down here.",

        "You are hidden in a deep, dark tunnel which rests far below the towering " +
        "heights of the mountains which rise up out of the legendary Mirkwood " +
        "forest. The brittle crackle of breaking bones comes from beneath your " +
        "feet as you occasionally step upon the piles of debris which are " +
        "scattered across the uneven stone floor. Sticky, silvery spiderwebs " +
        "shimmer brightly as light reflects off of them, forever concealing " +
        "endless black shadows behind. You can barely see the dull grey stone " +
        "of the rocky walls, ceiling or floor as everything in sight is blanketed " +
        "in thick, milky-grey ropes of spiderwebs. A strong stench of death " +
        "and decay sifts through the air, filling your mouth and nose with its " +
        "unpleasant taste. While echoing in the distance, you can occasionally hear " +
        "the sound of something scraping against the rocks and stone. It seems " +
        "that no matter where you attempt to go, yet another sticky spiderweb " +
        "is reaching out to clutch you in its hungry embrace.",

        "You find yourself in a deep, dark tunnel, far below the mighty " +
        "forest of Mirkwood and its mountains far above. A rancid smell " +
        "devestates your senses, assaulting your mouth and nose with " +
        "the constant stink of death and decay. It is very difficult " +
        "to see anything down here, as the light reflects so brightly " +
        "against the thick, silvery spiderwebs that you cannot see " +
        "anything else but thousands of ominous shadows. These webs " +
        "are thick, ropy lengths of a milky-grey colour that coat " +
        "absolutely everything in sight, from the ceiling to the walls " +
        "to the floor beneath your feet. They even cover the occasional " +
        "pile of debris, most of which emit the snapping of brittle bones " +
        "whenever you step on them. You find that the webs tangle you " +
        "up at every turn, clutching possessively at every part of your " +
        "body anytime you attempt to move anywhere. This does not seem " +
        "to make those scratching, scuttling sounds you hear echoing in " +
        "the distance seem any safer.",

    })), LIGHT_ALL);

    add_item_light(({"wall", "walls"}),
        "The walls here are absolutely covered in webbing, obviously " +
        "created by the massive spiders which live within these caves. " +
        "When you shine a light closer to the walls, you scrape away " +
        "some of the webbing to reveal a rugged stone wall with deep " +
        "scratches scattered all over.\n", LIGHT_ALL);
    add_item_light(({"ceiling", "up"}),
        "The ceiling is high above you here, too far away to examine " +
        "very closely. As best you can determine, it appears to be " +
        "rough, irregular stone much like the walls. Like the walls, " +
        "almost every inch appears to be covered in the spider webs " +
        "which constantly reach down, sticking to your head and " +
        "shoulders.\n", LIGHT_ALL);
    add_item_light(({"floor", "ground", "down"}),
        "The floor beneath your feet is covered in spider webs, but as " +
        "you scrape away some of the webbing for a closer look, you can " +
        "see that it is just rough, uneven stone covered with dirt. " +
        "There appear to be endless small rocks and stones scattered " +
        "everywhere, not to mention large lumps of web-covered debris.\n", LIGHT_ALL);
    add_item_light(({"web", "webs", "strand", "strands", "spiderweb", "spiderwebs", "webbing"}),
        "Everywhere you look, you see these sticky, silvery strands of spiderweb" +
        "shimmering in the light. Some of the webs are thicker, some are thinner, " +
        "some are almost white and some are camouflaged in the shadows. However, all " +
        "of them are a nuisance as they grab onto your arms and legs, " +
        "attmempting to hold you in place almost anytime you move.\n", LIGHT_ALL);
    add_item_light(({"rock", "rocks", "stones", "stone"}),
        "This passage seems to be a cave which has been dug right out " +
        "of the dull grey, bones of the mountains themselves. As a result, you " +
        "notice several smaller stones and rocks scattered around the " +
        "tunnel, mostly coated with sticky spiderwebs.\n", LIGHT_ALL);
    add_item_light(({"tunnel", "cave", "caves", "passageway", "passage"}),
        "You are trapped deep within a dark cave, far beneath the mountains " +
        "in Mirkwood forest. Everywhere you look, thick strands of " +
        "spider webs hang from the walls and ceiling, even covering " +
        "the floor. The webs seem to tug possessively at your head, arms and " +
        "feet with every step you attempt. As your eyes dart around in " +
        "the darkness, what little light you can manage simply reflects " +
        "off the webs, leaving you unable to see much of anything else " +
        "aside from the threatening shadows. Every now and then, your " +
        "hear the soft crunch of a bone breaking beneath your feet " +
        "as you attempt to navigate the uneven floor of these caves.\n", LIGHT_ALL);
    add_item_light(({"shadow", "shadows"}),
        "As you look around, light seems to reflect brightly from the " +
        "thousands of strands of spiderwebs which cover the tunnel around " +
        "you. However, behind every strand of webbing lurks an ominous " +
        "shadow, hiding its secrets from your prying eyes. As you " +
        "attempt to move your light around to see into the shadows, " +
        "the occasional glimmer catches your eyes by surprise. You can " +
        "only wonder if it was the reflection of yet another spiderweb, " +
        "or a hungry spider eyeing you as its prey.\n", LIGHT_ALL);
    add_item_light(({"bone", "bones", "remains", "debris", "lump", "lumps"}),
        "You stop to take notice of several mishapen lumps of various shapes " +
        "and sizes which are strewn all across the floor of the tunnel. While " +
        "many of these web-covered lumps are just rocks or stones, you " +
        "quickly come to understand that much of the debris is actually " +
        "composed of the bones and remains of spider victims.\n", LIGHT_ALL);
    add_item_light(({"scratch", "scratches"}),
        "There seem to be endless scratches which dig deep into the stone walls " +
        "of these caves. You cannot be certain if these scratches were " +
        "created by the spiders who use these passageways or by any of " +
        "their victims who were trying to claw their way out of these caves.\n", LIGHT_ALL);
    add_item_light(({"dust", "dirt"}),
    	"Mingled with the spider webs which cover the floor is a thick layer " +
        "of dirt and dust. The dirt seems to stick to the webbing, creating " +
        "an odd illusion of shadows which you continually step into as it " +
        "sticks to your feet, tripping you up.\n", LIGHT_ALL);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}


int
webs()
{
    write("Clawing your way past the sticky webs that hang in front of you, " 
        + "you move further down the tunnel inside these caves.\n");
    return 0;
}

int
escape()
{
    write("\nSpotting an exit, you quickly scramble up the rocky slope "
        + "beneath your feet and escape the caves below.\n\n");
    return 0;
}



int
do_burn(string str)
{
    if(!str || !strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    object *tools = PARSE_COMMAND(str, 0, 
        "[the] [spider] 'spiderweb' / 'spiderwebs' / 'web' / 'webs' 'with' %i");
    if (!sizeof(tools))
    {
        notify_fail(capitalize(query_verb()) + " what with what?\n");
        return 0;
    }

    object *fire_sources = filter(tools, &->query_prop(OBJ_I_HAS_FIRE));
    if (!sizeof(fire_sources))
    {
        if (sizeof(tools) == 1) 
        {
            write("Your " + tools[0]->short() + " is not on fire.\n");
        }
        else
        {
            write("None of " + COMPOSITE_DEAD(tools) + " holds a flame.\n");
        }

        return 1;
    }

    object torch = fire_sources[0];
    write("\nYou thrust your " + torch->short() + " towards a large, lumpy " +
        "patch of silvery spiderwebs in an effort to burn them away. " +
        "You watch with satisfaction as you see the various webs begin " +
        "to shrivel up and melt away when exposed to the flame.\n\nA " +
        "bright flash suddenly hurts your eyes and singes your skin as " +
        "some of the webs actually catch fire somehow! \n\nOuch! \n\nThat hurt!\n");
    
    this_player()->heal_hp(-300);

    object *can_see_in_room = FILTER_CAN_SEE_IN_ROOM(FILTER_LIVE(
        all_inventory(this_object())));

    object *cant_see_player = filter(can_see_in_room, 
        &not() @ &->check_seen(this_player()));
    object *others = can_see_in_room - cant_see_player - ({ this_player() });

    string message = " accidentically burns "
        + this_player()->query_objective() + "self while attempting to use "
        + torch->short() + " to remove some of the spiderwebs.\n";

    say(({ this_player()->query_met_name() + message,
           this_player()->query_unmet_name() + message,
           "", cant_see_player + ({ this_player() }) }));

    others->catch_msg("Suddenly some of the firewebs catch fire.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_burn, "burn");
    add_action(do_burn, "light");
}

int calculate_mirkwood_light()
{
    return 0;
}