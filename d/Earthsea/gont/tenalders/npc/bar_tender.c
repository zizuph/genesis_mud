/*
* coded by Amelia, 4/20/97
* bringing back some of the old... Rhyn, nov '02
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/intro";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Earthsea/travellers/guild.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"
#include "defs.h"

#define WOOD_PROP "_killian_wood_prop_"
#define KNIFE_PROP "_killian_knife_prop_"
#define CARVING_KNIFE_ID "_killian_carving_knife_"
#define EMERALD "/d/Earthsea/gont/tenalders/obj/items/emerald"
#define BADGE "/d/Earthsea/travellers/obj/badge.c"
#define PLAYER_I_GOT_TRAVELLERS_BADGE "_player_i_got_travellers_badge"

public void
create_earthsea_monster()
{
    set_name("killian");
    set_living_name("_killian_");
    add_name(({"bar tender", "tender","bartender","gontishman"}));
    set_adj(({"small", "whiskered"}));
    set_race_name("human");
    set_width("lean");
    default_config_npc(30);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(OBJ_M_NO_ATTACK, "You feel it would be very "+
        "unwise to attack this man.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
        "harmlessly on thin air.\n");
    set_title("the Bartender, Former Carver of Gar, Rising Cartographer of the Travellers");
    set_act_time(60);
    set_chat_time(30);
    add_chat("Gont is famous for its goat-thieves, its "+
        "sea-pirates ... and its wizards!");
    add_act("emote wipes his nose with the bar cloth.");
    add_act("emote turns the spit over the fire.");
    add_act("emote straightens some glasses behind the counter.");
    add_chat("I don't aim to close down business, "+
        "just because of a few Kargs!");
    add_chat("I thought I had left Gar behind, but now I hear " +
        "that rascal Ashel is back in town!");
    add_chat("I'm glad I took over the place from my cousin Ezekiel, " +
        "but I do miss the old village a bit. And my beautiful carvings...");
    add_chat("What I wouldn't do for a nice little bit of wood " +
        "and a knife. But I haven't the time...");
    add_ask(({"help", "task", "quest", "job", "need", "knife", "wood"}),
        "The bartender sighs: Ever since I've taken over for my cousin, " +
        "I haven't had the time to do any carving. What I wouldn't do " +
        "for a good carving knife and a bit of soft wood...\n");
    add_ask(({"badge", "join travellers"}), 
        VBFC_ME("vouch_travellers"));
    add_ask(({"travellers"}), "The bartender laments nostalgically: " +
        "I was an active adventurer in my youth! " +
        "I even joined the Travellers guild at some point. Those " +
        "were fun times indeed!\n");
}

public void
vouch_travellers()
{
    object tp = this_player();
    string name = tp->query_real_name();
    string race = tp->query_race();
    if (race != "human")
    {
        command("hmm");
        command("whisper " + name + " I am sorry, but the current " +
            " guild policy forbids non-human members.");
        return;
    }
    if (QH_QUERY_QUEST_COMPLETED(tp, "killian_carving_task"))
    {
        if (race != "human")
        {
            command("hmm");
            command("whisper " + name + " I am sorry, but the current " +
                " guild policy forbids non-human members.");
            return;
        }
        if (tp->query_prop(PLAYER_I_GOT_TRAVELLERS_BADGE))
        {
            command("whisper " + name + " I already vouched for you " +
                "today.");
            return;
        }
        command("whisper " + name + " You know what, since you have helped " +
            "me before, I can vouch for your Travellers membership.");
        clone_object(BADGE)->move(this_object(), 1);
        command("give badge to " + name);
        tp->add_prop(PLAYER_I_GOT_TRAVELLERS_BADGE, 1);
        return;
    }
    command("whisper " + name + " I am sorry, but I do not trust you " +
        "enough. I barely know you!");
}

public void
reward_carving(object who)
{
    command("say Fantastic! A carving knife and a nice piece of wood!");
    command("say Let me give you something you might remember in return.");
    clone_object(EMERALD)->move(this_object(), 1);
    command("give emerald to " + who->query_real_name());

    if(QH_QUEST_COMPLETED(who, "killian_carving_task"))
    {
        command("say This is so wonderful! I can start carving again...");
        tell_room(environment(this_object()), "Just as the bartender " +
            "begins to take his knife to a piece of wood, a drunken " +
            "patron breaks a glass and begins yelling, and he is " +
            "called off to work before he gets a chance to whittle.\n");
        who->catch_tell("You feel a little more experienced.\n");
    }

    who->remove_prop(WOOD_PROP);
    who->remove_prop(KNIFE_PROP);
}

public void
enter_inv(object ob, object from)
{
    int wood = (ob->id(CARVE_OBJECT_ID) ? 1 : 0),
        knife = (ob->id(CARVING_KNIFE_ID) ? 1 : 0);

    ::enter_inv(ob, from);

    if(wood || knife)
    {
        ob->remove_object();

        if(wood)                 
        {
            set_alarm(1.0, 0.0, &command("say Oh wow! It's a " +
                "piece of wood!"));
        } else {
            if(!from->query_prop(ASHEL_KNIFE_PROP))
            {
                set_alarm(1.0, 0.0, &command("say Ack! " +
                    "Where did you get this??"));
                return;
            }

            set_alarm(1.0, 0.0, &command("say Oh wow! It's a " +
                "carving knife!"));
        }

        from->add_prop((wood ? WOOD_PROP : KNIFE_PROP), 1);

        if(from->query_prop(WOOD_PROP) && from->query_prop(KNIFE_PROP))
        {
            set_alarm(3.0, 0.0, &reward_carving(from));
        }

        return;
    }

    from->catch_msg(QCTNAME(this_object()) + " does not want that.\n");
    ob->move(from, 1);
}
