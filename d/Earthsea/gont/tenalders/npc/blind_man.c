/*
* Coded by Amelia, October 1997
* Blind beggar, gives hints about priestesses
* as a response when someone gives him a coin
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember";

#include <stdproperties.h>
#include <macros.h>

public void
create_earthsea_monster()
{
    set_living_name("_blind_man_");
    set_name("ardrik");
    add_name(({"man", "beggar"}));
    set_race_name("human");
    set_adj(({"blind", "old"}));
    set_long("This is an old man who appears to be blind.\n");
    default_config_npc(30);
    set_random_move(60);
    set_restrain_path("/d/Earthsea/gont/tenalders/south_path/");
    set_m_out("dodders away");
    set_m_in("dodders in");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_equipment(({ "/d/Earthsea/gont/tenalders/arm/robe",
        "/d/Earthsea/gont/tenalders/wep/blind_stick" }));
    add_chat("Alms, alms for the poor!");
    add_act("emote holds out his hand in a begging gesture.");
    set_default_answer("The blind beggar asks you:  Alms, "+
        "alms for the poor?\n");
    set_act_time(60);
    set_chat_time(30);
    add_act("stare");
}

public void
respond_evil()
{
    command("say " +
        "She tried to make me one of her guard, but I was lucky to "+
        "escape!");
    command("tremble");
    command("say I only lost my sight ... it could have been "+
        "much worse!");
}

public void
respond_falls()
{
    command("point");
    command("say The Roaring Falls lie across a vast chasm "+
        "to the northeast.");
    command("say It is not a journey for the weak or feint of "+
        "heart!");
    command("nod wisely");
    command("emote puts out a hand in a begging gesture.");
    command("say Can you spare a few coppers, my friend?");
}

public void
respond_sisters()
{
    command("say There are three sisters, beautiful but "+
        "terrifying ... ");
    command("say One is blonde, one has hair of flaming "+
        "red, and the fiercest has hair the colour of a raven's wing!");
    command("say Beware the three sisters!");
    command("stare");
}

public void
respond_spell(object player)
{
    object to = this_object();

    if(!present(player, environment(to)))
        return;

    player->catch_msg(QCTNAME(to) + " whispers: " +
        " I found a very secret place in that cave ... to punish me "+
        "she ensured that I could never go back, by laying a "+
        "blindness spell upon me!\n");
    command("sigh");
    player->catch_msg(QCTNAME(to) + " whispers: " +
        " Not even the great wizard Ogion could cure it! And so... "+
        "you see me now.\n");
    command("emote stares at you with sightless eyes.");
}

public void
respond_tenar(object player)
{
    object to = this_object();

    if(!present(player, environment(to)))
        return;

    player->catch_msg(QCTNAME(to) + " whispers: " +
        " There is an old legend ... regarding the Talisman of "+
        "Tenar! They say...it is hidden somewhere beneath the "+
        "Roaring Falls. They say that the Talisman gives protection "+
        "against evil spells!\n");
    command("nod wisely");
    command("emote smacks his gums.");
}

public void
thank_you(object player)
{
    int ran = random(5);

    command("thank" + player->query_real_name());
    command("emote pockets the cash.");

    if(ran == 0)
        set_alarm(3.0, 0.0, &respond_falls());
    if(ran == 1)
        set_alarm(3.0, 0.0, &respond_evil());
    if(ran == 2)
        set_alarm(3.0, 0.0, &respond_sisters());
    if(ran == 3)
        set_alarm(3.0, 0.0, &respond_spell(player));
    if(ran == 4)
        set_alarm(3.0, 0.0, &respond_tenar(player));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(from))
    {
        if(function_exists("create_coins", ob) == "/std/coins")
        {
            set_alarm(2.0, 0.0, &thank_you(from));
        }

        set_alarm(0.0, 0.0, &ob->remove_object());
    }
}
