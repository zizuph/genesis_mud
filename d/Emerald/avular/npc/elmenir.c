/*
 * ELMENIR.c
 * Elmenir, the Avular Armour Smith
 * - Alaron JAN 2000
 */

#include "/d/Emerald/sys/macros.h"
#include "../defs.h"
#include "/d/Emerald/sys/faction.h"
#include <stdproperties.h>
#include <macros.h>

inherit STDDARKLING;
inherit "/d/Genesis/lib/intro";

string boy_or_girl();
string get_darkflame_info();

void
create_darkling()
{
    set_name("elmenir");
    set_adj("strong");
    add_adj("white-eyed");
    add_name(CREATURE_OF_VS_ID);
    set_title("Master ArmourSmith of Avular");

    set_long("This strong-looking armoursmith is about average height for "+
        "a darkling. He is wearing a heavy leather apron, yet no gloves. Even "+
        "more strange, is that his hands are fine, smooth, and delicate, without "+
        "a callous or sore visible that so many smiths have. Even though they have "+
        "pale, almost-white skin, most darklings have some kind of eye coloring. This "+
        "man, however, has none, his eyes a pure, smooth white. Even though he appears "+
        "to be busy, it looks as though he might not be too busy to speak with.\n");

    set_speak( ({
              "I'm afraid you won't find any armour that will fit you around here.",
              "Lightdwellers come into my forge and expect me to fix their armours. This "+
              "is not a lightdweller forge, I don't work on lightdweller armour. No one "+
              "seems to understand.",
              "Heh, I'll bet you're wondering how I manage to soften these metals without "+
              "heat from what you would call flame? I'll tell you no more than "+
              "its name: darkflame." }) );

    add_ask( ({"darkflame","the darkflame", "about darkflame",
               "about the darkflame", "what about the darkflame"}),
            "He turns to you and says: So, you want to know about darkflame, eh, @@boy_or_girl@@?\n"+
            "@@get_darkflame_info@@.\n");

    set_act_time(11);

    add_act("emote steps to the furnace, adjusting the glowing blue rocks with his "+
        "bare hands.");
    add_act("emote places a new rod of iron on the rack in the furnace.");
    add_act(
       ({"emote riffles through piles of tools on the shelves, finally finding "+
        "the tool he needs.",
        "emote chisels a small piece off of one of the rods on the rack in the "+
        "furnace."}));
    add_act("emote hammers on a thin sheet of metal.");
    add_act("emote takes a small knife and begins shaving soft pieces of metal "+
        "from a small helmet.");

    set_stats( ({ 80, 120, 120, 90, 95, 90 }) );

    set_monster_home(AVINSIDE+"forge1");
}

string
boy_or_girl()
{
    if (this_player()->query_gender() == 1)
        return "girl";
    else
        return "boy";
}

public void
introduce(object who)
{
    if ( QUERY_FACTION(who, FG_AVULAR_CITIZENS) < FACRANK_QUESTALLOW )
    {
        /* He will not call a VS creature a lightdweller, though the reaction is
         * still faction-driven. It will probably appear like a random reaction to
         * -most- players.
         */
        if (CREATURE_OF_VS(who))
        {
            command("say to " + OB_NAME(who) + " Get out of my forge and leave me be.");
        } else {
            command("say to "+OB_NAME(who)+" Get out of my forge and leave me be before "+
                "I call the guards, you disgusting lightdweller!");
        }
    }
    else {
        command("introduce myself to "+OB_NAME(who));
        command("say to "+OB_NAME(who)+" Welcome to my forge, "+capitalize(who->query_real_name()));
    }
}

public void
greet(object who)
{
    if ( QUERY_FACTION(who, FG_AVULAR_CITIZENS) < FACRANK_QUESTALLOW )
    {
        /* Prevent calling VS creatures lightdwellers */
        if (CREATURE_OF_VS(who))
        {
            command("say to " + OB_NAME(who) + " I have nothing to say to you.");
        } else {
            command("say to "+OB_NAME(who)+" You've been here before, so you should know that "+
                "lightdwellers like yourself are simply not welcome here.");
        }
    }
    else {
        command("say to "+OB_NAME(who)+" Welcome back.");
    }
}

public string
get_darkflame_info()
{
    string maininfo = "We darklings are beings of darkness, we "+
            "simply cannot bear the light, nor can we bear the bright glow from a "+
            "flaming furnace burning the lightdweller fuel. The darkflame is a flame of "+
            "pure darkness, that melts faster and deeper than anything your bright "+
            "blazes can do, but it gives no heat and no light. Beyond that, you must "+
            "ask the Mages, for they are the ones who gave us the darkflame";

    if ( QUERY_FACTION(this_player(), FG_AVULAR_CITIZENS) >= FACRANK_QUESTALLOW )
    {
        /* Don't want him accusing a VS creature of being a lightdweller. */
        if ( CREATURE_OF_VS(this_player()) )
        {
            return "I sense a strange connection with you that I cannot explain. Because "+
              "of this I will answer your question. " + maininfo;
        }
        else {
            return "Through your deeds you have proven yourself to be unlike the "+
                "rest of your lightdwelling brethren. You are not our enemy, and as such, "+
                "I will tell you of the darkflame. " + maininfo;
        }
    }
    else {
        return "Well, you'll not get me to reveal the secrets of the darklings to "+
            "a lightdweller like yourself. Perhaps you should prove yourself "+
            "worthy to the citizens of Avular to receive such a secret. If you "+
            "have done this, then and only then will I allow you to know of "+
            "the darkflame";
    }

}
