/*
 * DHRAGAS.C
 * Dhragas, the Avular Weapon Smith
 * - Alaron JAN 2000
 */

#include "/d/Emerald/sys/macros.h"
#include "../defs.h"
#include "/d/Emerald/sys/faction.h"
#include <stdproperties.h>
#include <macros.h>

inherit STDDARKLING;
inherit "/d/Genesis/lib/intro";

string get_darkflame_info();

void
create_darkling()
{
    set_name("dhragas");
    set_adj("powerful");
    add_adj("dark-haired");
    add_name(CREATURE_OF_VS_ID);
    set_title("Master WeaponSmith of Avular");

    set_long("This unusually stocky, well-built darkling is slightly taller and "+
        "has much more physical strength than others of his kind. He is wearing a "+
        "heavy leather apron and thick black clothing underneath He sports the "+
        "typical dark hair and pale skin of the darklings Many, many hours working "+
        "with metals, shaping weapons, have given him unusually strong, thick arms.\n");

    set_speak( ({
            "If you're looking for lightdweller weapons, you'll have to look to a forge "+
            "somewhere in the light areas. I don't make those kinds of weapons.",
            "My weapons may be small by lightdweller standards, but a lightdweller "+
            "sword will break like a brittle twig when put against a blade of mine.",
            "If you're wondering how we manage to work the metals without heat or flame, "+
            "it is all made possible by the darkflame.",
            "If you really want to know more about darkflame, you could ask. If I'm not "+
            "too busy I might actually explain it to you."
              }) );

    add_ask( ({"darkflame","the darkflame", "about darkflame",
               "about the darkflame", "what about the darkflame"}),
            "He turns to you and says: Darkflame? You want to know about darkflame? "+
            "@@get_darkflame_info@@.\n");

    set_act_time(13);

    add_act("emote swings a test blade, testing it for weight and balance.");
    add_act("emote adjusts the glowing blue stones in the furnace with his bare hands.");
    add_act("emote searches through his shelves for a tool.");
    add_act("emote mutters something about people watching him work being distracting.");

    set_stats( ({ 140, 110, 90, 95, 115, 105 }) );

    set_monster_home(AVINSIDE+"forge2");
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
            command("say to " + OB_NAME(who) + " You have no business here.");
        } else {
            command("say to "+OB_NAME(who)+" Get away from me before "+
                "I call the guards, vile lightdweller!");
        }
    }
    else {
        command("introduce myself to "+OB_NAME(who));
        command("say to "+OB_NAME(who)+" Welcome to my forge, "+capitalize(who->query_real_name())+".");
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
            command("say to " + OB_NAME(who) + " Hmm. Why do you continue to waste my time by "+
                "repeating an introduction I already know?");
        } else {
            command("say to "+OB_NAME(who)+" You've been here before, so you should know that "+
                "lightdwellers like yourself are not welcome here!");
        }
    }
    else {
        command("say to "+OB_NAME(who)+" Welcome back, "+capitalize(who->query_real_name())+".");
    }
}

public string
get_darkflame_info()
{
    string maininfo = "The darkflame is a creation of the Mages from ages long past. I'm not "+
        "sure if even they know the secret of its making any longer. You see, as darklings, "+
        "we cannot abide the light of flame or sun. So, to do our work, and many other things, "+
        "we have been given the darkflame, which melts many times hotter than a flame furnace, "+
        "yet gives off neighther heat nor light. Beyond this, you would need to consult a "+
        "Mage for more information";

    if ( QUERY_FACTION(this_player(), FG_AVULAR_CITIZENS) >= FACRANK_QUESTALLOW )
    {
        /* Don't want him accusing a VS creature of being a lightdweller. */
        if ( CREATURE_OF_VS(this_player()) )
        {
            return "I feel a strange, almost kinship, with you that I cannot explain. Because "+
              "of this you will have your answer. " + maininfo;
        }
        else {
            return "Through your deeds you have proven yourself to be unlike the "+
                "rest of your lightdwelling brethren. You are not our enemy, and as such, "+
                "you will have your answer. " + maininfo;
        }
    }
    else {
        if ( CREATURE_OF_VS(this_player()) )
        {
            return "Despite this strange connection I feel to you, we cannot afford "+
                "to trust those who have not proven themselves worthy of our trust";
        } else {
            return "Well, you'll not get me to reveal the secrets of the darklings to "+
                "a lightdweller like yourself. Perhaps you should prove yourself "+
                "worthy to the citizens of Avular to receive such a secret. If you "+
                "have done this, then and only then will I allow you to know of "+
                "the darkflame";
        }
    }

}
