/* Modified from Emerald by Gwyneth, Auguest 1999 */
/* For the kender entrance quest */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/kendermore/local.h"
inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/act/asking.c";

#define ODIR    "/d/Ansalon/private/entrance/obj/"

void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_age("young");
    set_colour("bronze");
    set_name("khalania");
    set_gender(G_FEMALE);
    set_long("Standing before you is one of the most magnificent " + 
        "creatures in all of Krynn -- a dragon! This one is young " + 
        "for its kind, and covered with bronze scales. Wisdom and " + 
        "cunning shine in her eyes.\n");
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_introduce(0);

    set_default_answer("The young dragon gives a great big yawn. She " + 
        "couldn't have heard a word you said.\n");
    add_ask(({"kender", "gusslehan", "gusslehan shadowpoker", "shadowpoker",
        "prisoner"}), "say Poor Gusslehan. Shunar locked him up when he " + 
        "found him poking around his workroom. I still have the half " + 
        "locket that he gave to me. He was only trying to help " + 
        "me I'm afraid.", 1);
    add_ask(({"help", "task", "job", "quest"}), "say Oh, I'm afraid the " + 
        "last kender that tried that got locked in the dungeon. His name " + 
        "was Gusslehan Shadowpoker, and was very friendly to me.", 1);
    add_ask(({"dungeon", "locked up", "locked"}), "say Shunar keeps his " + 
        "prisoners locked in the dungeon. Not even a kender can pick his " + 
        "way out of there, and the only key is in Shunar's care.", 1);
    add_ask(({"key", "keys"}), "say I've seen it before. It's a large " + 
        "skeleton key.", 1);
    add_ask("shunar", "say He is an evil man. He dabbles in alchemy and " + 
        "black magic. He's the one who trapped me here. I wish I had my " + 
        "freedom!", 1);
    add_ask(({"alchemy", "black magic", "magic"}), "say Shunar dabbles " + 
        "in alchemy and black magic, but he is a renegade mage.", 1);
    add_ask(({"trapped", "free", "freedom"}), "say Shunar has trapped me " + 
        "in my present form. I can " + 
        "no longer fit through the door to escape. There is a cure " + 
        "though.", 1);
    add_ask(({"cure", "escape"}), "say There is a certain potion hidden in " + 
        "Shunar's workroom. If I were to quaff that, the magic would be " + 
        "dispelled, and I could escape!", 1);
    add_ask("locket", "say Gusslehan gave me half of his locket. Don't you " + 
        "dare think of borrowing it!", 1);
    add_ask("workroom", "say It lies at the top of the south stairs.", 1);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

}

void
give_it_back(object ob, object from)
{
    string what, who;
    what = L(ob->query_short());
    who = from->query_real_name();
    command("give " + what + " to " + who);
    command("say That's not what I seek.");
}

void
accept_potion(object from)
{
    string who;
    object sil_locket;
    who = from->query_real_name();
    command("say You found it!");
    command("quaff potion");
    if (E(TO)->query_locket())
    {
        setuid();
        seteuid(getuid());
        sil_locket = clone_object(ODIR + "locket_left");
        command("emote takes the locket half from the table and presents " + 
            "it.");
        command("say Take this in thanks my friend!");
        sil_locket->move(from);
        E(TO)->change_locket();
    }
    command("wave goodbye");
    command("emote transforms into a spirited young elven woman as " + 
        "she disappears behind the tapestry.");
    remove_object();
}

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->id("_dragon_potion_"))
    {
        set_alarm(0.1,0.0,&accept_potion(from));
        return;
    }
    set_alarm(1.0,0.0, &give_it_back(ob, from));
}

