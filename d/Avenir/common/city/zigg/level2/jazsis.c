// Ziggurat  (jazur.c)
// creator(s):  Zielia + Lucius 2006
// last update:
// purpose:
// note:
// bug(s):
// to-do:

#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_ROOM;

#include "../obj/hair.h"

#define PROP_I_INSIDE    "_moved_past_curtains"

private static object altar;
private static int hour;

private void
find_altar(object ob)
{
    altar = ob;
}

public void
zig_room(void)
{
         /* Avtime events. */
    AVTIME->add_event(this_object());
    hour = AVTIME->get_avenir_hour();

    set_short("@@my_short");
    set_long("@@my_long");

    add_exit("sanctorium", "east",  "@@move_out");

    add_zigg();

    add_item(({"panel","curtain","veil","silk","panels","curtains","veils",
        "silks",}), "The panels cascade from ceiling to floor, a waterfall of "+
        "scarlet silk so thin it is almost translucent. Each curtain slightly "+
        "overlaps the ones a few paces behind it, creating a visual wall you "+
        "must wind through one layer at a time to advance. Behind the wall, "+
        "a soft light glows, filling the room with rosy luminence.\n");

    add_item(({"floor","ground",}), "The floor is made of perfectly smooth "+
        "black stone that has been polished to the point of being reflective.\n");

    add_item(({"ceiling","roof",}), "The ceiling is black and glossy, just "+
        "like the walls and floor. Beautiful panels of scarlet silk hang from "+
        "rods fastened to the stone.\n");

    add_item(({"wall","walls",}), "@@see_walls");

    add_object(ZIG_OBJ + "altar_jazsis", 1, find_altar);
}

public string
my_short(void)
{
    if (altar->id_altar_check(TP))
        return "Jazur and Sisera's Reliquary";
    else
        return "A dimly lit reliquary";
}

public string
my_long(void)
{
    string str;

    if (TP->query_prop(PROP_I_INSIDE))
    {
        write("You wander through the silk panels, passing through several "+
            "layers as you look around. ");
        say(QCTNAME(TP) +" wanders amongst the silk panels, looking around "+
            "with interest.\n");
        TP->remove_prop(PROP_I_INSIDE);
    }

    str =   "Scarlet panels of the finest light-weight silk hang from "+
            "the glossy black ceiling in a staggered pattern, curtaining the "+
            "altar from view and forcing you to wind your way between them "+
            "to move through the room. The light seems to emanate from the "+
            "center of the room, glowing behind the silk veils and staining "+
            "your sight with a ruddy glow.\n";

    if (altar->id_altar_check(TP))
        return "This is the altar room to Jazur and Sisera. "+ str;
    else
        return str;
}

public int
move_out(void)
{
    if (TP->query_prop(PROP_I_INSIDE))
    {
        write("You twist and dance your way between the silk curtains until "+
            "you reach the exit and pass through to the heart of the sanctorium.\n");
        say(QCTNAME(TP) +" weaves through the silk panels and passes out "+
            "the exit.\n");
        TP->remove_prop(PROP_I_INSIDE);
    }

    return 0;
}

public string
see_walls(string str)
{
    if (TP->query_prop(PROP_I_INSIDE))
    {
        write("You weave your way through the silk panels to examine the "+
            "outer wall. ");
        say(QCTNAME(TP) +" weaves "+ HIS(TP) +" way through the silk "+
            "panels to the examine outer wall.\n");
        TP->remove_prop(PROP_I_INSIDE);
    }

    return "The walls are made of black stone like "+
        "much of the Ziggurat. These walls seem more than polished though. "+
        "They look naturally slick and glossy, as though some intense heat "+
        "had transformed the stone into glass. You imagine they'd be cool "+
        "and slippery to the touch.\n";
}

public int
touch_walls(string str)
{
    if (str == "walls" || str == "wall")
    {
        if (TP->query_prop(PROP_I_INSIDE))
        {
            write("You weave your way through the silk panels to the outer "+
                "wall. ");
            say(QCTNAME(TP) +" weaves "+ HIS(TP) +" way through the silk "+
                "panels to the outer wall.\n");
            TP->remove_prop(PROP_I_INSIDE);
        }

        write("You press your hand against the glassy stone of the wall. "+
            "The wall is perfectly smooth and surprisingly warm. As you "+
            "press your hand to it, you feel an odd, faint thrumming, a "+
            "rhythmic vibration deep within the stone.\n");
        say(QCTNAME(TP) +" presses "+ HIS(TP) +" palm against the glossy "+
                "black stone of the wall.\n");
        return 1;
    }

    return 0;
}

public int
item_id(string str)
{
    if (::item_id(str))
    return 1;
    else
    return altar->item_id(str);
}

public void
hook_smelled(string what)
{
    switch(what)
    {
    default:
    if (strlen(what))
        return altar->hook_smelled(what);

        write("The air is scented with a wild, musky scent that is relaxing "+
            "and yet stimulating, almost arousing.\n");
    break;
    }
}

static void
f_revelry(int count)
{
    object *center = ({});
    object *outer = ({});
    object *sybarites = ({});
    object *outlanders = ({});

    foreach(object who : filter(all_inventory(), query_interactive))
    {
        if (who->query_prop(PROP_I_INSIDE))
        {
            center += ({who});
        }
        else
        {
            outer += ({who});
        }

        if (IS_SYBARITE(who))
        {
            sybarites += ({who});
        }
        else
        {
            outlanders += ({who});
        }
    }

    switch(++count)
    {
    case 1:
    tell_room(TO, "Suddenly the low flames in the braziers shoot up, blasting "+
        "you with a wave of intense heat and throwing off scintillating "+
        "blue and red sparks.\n", outer, TO);
    tell_room(TO, "Suddenly an intense wave of heat, like a hot wind rushes "+
        "from the center of the room, stirring the sheer silk panels.\n",
        center, TO);
    altar->set_unid_long("Two triangular braziers burn atop a black stone "+
        "altar The braziers are arranged tip to tip, their apexes kissing. "+
        "The western-most brazier is alight with a blue black flame. The "+
        "eastern one glows with a scintilating ruby fire which fumes faint, "+
        "fragrant smoke. The flames burn fiercely with Passionate heat, "+
        "soaring high and twisting around each other in a red and blue spiral.");
    altar->set_id_long("Two triangular braziers burn atop a black stone altar. "+
        "The braziers are arranged tip to tip, their apexes kissing. "+
        "Jazur's brazier is alight with a blue black flame. Sisera's "+
        "glows with a scintilating ruby fire which fumes faint, "+
        "fragrant smoke. The flames burn fiercely with Passionate heat, "+
        "soaring high and twisting around each other in a red and blue spiral, "+
        "symbolizing the union of Jazur and Sisera during the 12th hour.");
    break;
    case 2:
    tell_room(TO, "A familiar pang of desire clenches at your heart as "+
        "you realizes the 12th hour is upon you. ", outlanders, TO);
    tell_room(TO, "The heat sends odd shivers running through you, making you "+
        "feel both hot and chilled at the same time, almost feverish.\n", 0, TO);
    break;
    case 3:
    tell_room(TO, "A low pulsing sound teases your ears. So low it is more "+
        "of a vibration than a sound, it comes from the walls in a steady "+
        "rhythm, almost like a heartbeat.\n", 0, TO);
    break;
    case 4:
    tell_room(TO, "The flames continue to blaze, leaping, as though fueled "+
        "by something, and casting strange shadows on the scarlet panels.\n",
        outer, TO);
    tell_room(TO, "Some of the panels stir, moved by air currents that make "+
        "them billow in strange ways.\n", center, TO);
    break;
    case 6:
    tell_room(TO, "A strange whispering fills the chamber.\n", 0, TO);
    break;

    case 7:
    tell_room(TO, "The whispering around you is too indistict to understand "+
        "but seems almost musical.\n", sybarites, TO);
    tell_room(TO, "A melodic, ethereal voice whispers in your ear, speaking "+
        "in ancient Sybarite so you barely understand: This place is possessed "+
        "of pleasure, haunted by the Passion of hundreds come before. It "+
        "clings to the stone and is wakened by the flames. Join us in "+
        "our revels, Faithful one.\n", outlanders, TO);
    break;
    case 8:
    tell_room(TO, "The flames soar, reaching toward each other as they rise "+
        "ever higher.\n", outer, TO);
    tell_room(TO, "The panels billow strangely, not stirred by air, but as "+
        "though someone were behind them, pressing into them.\n", center, TO);
    break;
    case 9:
    tell_room(TO, "The heat makes you parched. It is so intense you can "+
        "barely withstand it.\n", outer, TO);
    tell_room(TO, "You see the outline of what looks like a man in one of "+
        "the panels: arms, legs head.\n", center, TO);
    break;
    case 11:
    foreach(object who : filter(center, query_interactive))
    {
        who->catch_tell("You feel as though your skin is about to "+
        "blister, your"+ HAIR(who) +" about to catch fire and "+
        "burn like a torch.\n");
    }
    tell_room(TO, "You see the curvaceous outline of what is definitely "+
        "a woman in the scarlet silk of a panel to your left.\n", center, TO);
    break;
    case 12:
    tell_room(TO, "Soft whispers continue all around you, accentuated "+
        "melancholy moans and longing sighs and the ever throbbing beat of "+
        "the walls.\n", 0, TO);
    break;
    case 13:
    tell_room(TO, "You hear a quiet giggle near your ear and then feel a "+
        "light, inviting caress on your forearm. The touch is strange, the "+
        "sensation is vivid and yet you feel as though it were something "+
        "remembered or perhaps dreamt. Even stranger, you have the unsettling "+
        "feeling it's someone else's dream or memory you just felt.\n", 0, TO);
    break;
    case 14:
    tell_room(TO, "The flames twist together, spriraling into a flickering "+
        "red and blue cone.\n", outer, TO);
    tell_room(TO, "The light is brighter now, more red, flooding through "+
        "the silk.\n", center, TO);
    case 16:
    tell_room(TO, "Frangrant smoke wafts around you, filling you "+
        "with its wild, erotic scent.\n", outer, TO);
    tell_room(TO, "You have the sensation of people moving all about you "+
        "unseen. Warm bodies brush against yours.\n", center, TO);
    break;
    case 17:
    tell_room(TO, "A sense of being in two times, "+
        "two people at once deepens as a euphoria that is yours and yet "+
        "not yours envelops you.\n", outer, TO);
    tell_room(TO, "The silk panel near you "+
        "blows, curling around an invisible leg. A hand presses into another "+
        "as though seeking something to hold onto.\n", center, TO);
    break;
    case 18:
    tell_room(TO, "The throbbing beat of the walls is faster now, reverberating "+
        "through you, matching the pounding drum of your heart.\n", 0, TO);
    break;
    case 19:
    tell_room(TO, "You feel slender fingers caress your cheek, cool against "+
        "your fire-warmed skin but all you see around you is flame and shadow, "+
        "silk and stone.\n", outer, TO);
    foreach(object who : filter(outer, query_interactive))
    {
        who->catch_tell("Phantom fingers run through your"+ HAIR(who) +
        ".\n");
    }
    break;
    case 21:
    tell_room(TO, "The flames nearly reach the ceiling now, twisting "+
        "and twining around each other.\n", outer + sybarites, TO);
    tell_room(TO, "The flames nearly reach the ceiling now, twisting "+
        "and twining around each other, symbolizing the union of Jazur "+
        "and Sisera.\n", outer + outlanders, TO);
    tell_room(TO, "The air is heavy with scented smoke now, tantalizing "+
        "you with its exotically musky and arousing fragrance.\n", center, TO);
    break;
    case 22:
    tell_room(TO, "The sensation of long fingernails scratching lightly down "+
        "your back, makes you tremble with the promise of pleasure or pain.\n",
         0, TO);
    break;
    case 23:
    tell_room(TO, "The whispering grows louder, becoming a chorus of "+
        "ecstatic chanting, repeating something in sybarite again and again.\n",
        sybarites, TO);
    tell_room(TO, "The whispering grows louder, becoming a chorus of "+
        "ecstatic chanting, repeating: Omlaus Sisera! Omlaus Jazur!\n",
        outlanders, TO);
    break;
    case 24:
    tell_room(TO, "You feel a faint tickle near your ear, like someone "+
        "breathing softly.\n", 0, TO);
    break;
    case 26:
    tell_room(TO, "A soft phantom mouth kisses the curve of your neck.\n",
        0, TO);
    break;
    case 27:
    tell_room(TO, "A low moaning sound fills the room, accompanied by a "+
        "building, swirling wind.\n", 0, TO);
    break;
    case 28:
    tell_room(TO, "The walls pulse rapidly and more forcefully, making the "+
        "room seem to tremble, to shudder climactically.\n", 0, TO);
    break;
    case 29:
    tell_room(TO, "Just as the flames are about to spread across the ceiling, "+
        "setting the silk curtains on fire and the room ablaze, they begin "+
        "to collapse in on themselves.\n", outer, TO);
    tell_room(TO, "The silk panels thash and swirl about you, whipped by wind "+
        "rising to an awesome gale before suddenly ebbing to a soft, lingering "+
        "breeze.\n", center, TO);
    altar->set_unid_long("Two triangular braziers burn atop a black stone altar "+
        "The braziers are arranged tip to tip, their apexes kissing. "+
        "The western-most brazier is alight with a blue black flame. The "+
        "eastern one glows with a scintilating ruby fire which fumes faint, "+
        "fragrant smoke.");
    altar->set_id_long("Two triangular braziers burn atop a black stone altar. "+
        "The braziers are arranged tip to tip, their apexes kissing. "+
        "Jazur's brazier is alight with a blue black flame. Sisera's "+
        "glows with a scintilating ruby fire which fumes faint, "+
        "fragrant smoke.");
    break;
    case 30:
    tell_room(TO, "A soft sigh of absolute contentment echoes through the "+
        "chamber and suddenly everything is once more still.\n", 0, TO);
    break;
    default:
        switch(random(5))
        {
        case 0:
        tell_room(TO, "The silk panels billow, uplifted by a current of "+
            "warm air.\n", 0, TO);
        break;
        case 1:
        tell_room(TO, "The walls pulse with a rhythmic beat, stirring "+
            "primal instincts within you.\n", 0, TO);
        break;
        case 2:
        tell_room(TO, "A trickle of sweat runs down your brow as the room "+
            "seems even hotter.\n", 0, TO);
        break;
        case 3:
        tell_room(TO, "Distantly, you hear a "+ one_of_list(({"woman", "man"}))+
            " moaning.\n", 0, TO);
        break;
        case 4:
        tell_room(TO, "Memories of carnal Passion tease your mind.\n", 0, TO);
        break;
        }
    break;
    }

    if (count < 30)
    {
        set_alarm(120.0, 0.0, &f_revelry(count));
    }

}

public int
avenir_event(int av_year, int av_week, int av_day, int av_hour)
{
    hour = av_hour;

    if (hour == 12)
    {
    set_alarm(0.0, 0.0, &f_revelry(0));
    }

    return 1;
}

public void
init(void)
{
    ::init();

    add_action( touch_walls, "touch");
    add_action( touch_walls, "feel" );

}
