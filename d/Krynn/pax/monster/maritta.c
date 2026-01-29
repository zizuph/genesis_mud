/*
   maritta.c
   ---------

   Coded ........: 95/01/19
   By ...........: Jeremiah

   Latest update : 95/07/28
   By ...........: Jeremiah


   This woman is a prisoner in Pax Tharkas. She is part of the quest 
   to free the prisoners. It's possible to ask her quetsions about the
   fortress. She will hint the player as to how he/she can make her 
   follow him/her. When she follows the player, she will give a few 
   hints on what to do next.

*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit M_FILE
inherit "/d/Krynn/std/act/gift";

void got_doll(object ob, object from);

void
create_krynn_monster()
{
    int i;

    set_name("maritta");
    set_race_name("human");
    set_long("She is a dark haired human. Her face is pale and wan. " +
      "She is dressed in old ragged clothes. She has a " +
      "resolute look on her face.\n"); 
    add_name("woman");
    set_adj("dark-haired");
    add_adj("pale");

    for (i = 0; i < 6; i++)
        set_base_stat(i,15 + random(10));

    set_all_attack_unarmed(10, 10);
    set_all_hitloc_unarmed(10);
    set_knight_prestige(-2);
    set_alignment(150);

    set_gender(G_FEMALE);

    set_default_answer("The woman says: I'm sorry, but I don't know " +
      "anything about that.\n");

    add_ask(({"about child", "about children", "about daughter"}), 
      VBFC_ME("child_hint"));
    add_ask(({"about husband", "about husbands", "about men", 
        "about spouse", "about spouses"}), VBFC_ME("husband_hint"));	
    add_ask(({"about nursemaid", "about nurse"}), VBFC_ME("nurse_hint"));
    add_ask(({"about dragon","about flamestrike","about Flamestrike"}), 
      VBFC_ME("dragon_hint"));
    add_ask("about courtyard", VBFC_ME("court_hint"));
    add_ask(({"about cave", "about caves"}), VBFC_ME("cave_hint"));
    add_ask(({"about lord", "about Lord", "about highlord"}), 
      VBFC_ME("lord_hint"));
    add_ask("about escape", VBFC_ME("escape_hint"));
    add_ask(({ "follow me", "follow" }), VBFC_ME("follow"));

    /* If you're on the right track Maritta will hint you on  ;) */
    
    add_ask(({"child", "children", "daughter", "husband", "husbands", "men",
                  "spouse", "spouses", "nursemaid", "nurse", "dragon",
                  "flamestrike", "Flamestrike", "courtyard", "cave",
                  "caves", "lord", "Lord", "highlord", "escape"}),
        "The dark-haired woman says: What do you want to " +
        "ask me about?\n");
    
    set_alarm(30.0,90.0,"give_hints");

    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);

    add_gift("pax_quest_doll", got_doll);
    seteuid(getuid(TO));
}

public int
ask_permission(object who)
{
    object child;

    child = present("girl",E(TO));

    if (who == query_follow())
    {
        command("emote kneels next to the girl.");
        command("say Yes dear, but we have to be silent when we leave.");
        command("emote smiles lovingly at the young girl.");
        command("smile " + OB_NAME(who));
        return 1;
    }
    
    command("say No!!, we're not dear ");
    return 0;
}

void
give_hints()
{
    if (!query_follow())
    {
        switch(random(4))
        {
        case 0 : 
            command("say I miss my husband, .. I guess we all miss " +
                "our spouses.");
            command("emote gestures at the other women in the room.");
            break;  
        case 1 :
            command("sigh");
            break;
        case 2 : 
            command("say I wish our children were here with us.");
            break;
        case 3 : 
            command("emote smiles sadly");
        }  
    }
}

child_hint()
{
    command("say The draconians are keeping our children in a room on " +
      "the next floor. They are smart, they know we won't try " +
      "to escape while they have our children. Thats why they keep " +
      "us separated. They have found a rather strange nursemaid for " +
      "our children.");

    return"";
}


husband_hint()
{
    command("say Our husbands, and the rest of the men, are being kept " +
      "in a cave in the far end of the fortress courtyard. They are " +
      "forced to work hard mining the iron ore from the mountain."); 

    return"";
}


nurse_hint()
{
    command("say The nursemaid is an old dragon, Flamestrike. The " +
      "children have become very fond of her. In fact, if you " +
      "were to hurt her, you'd have half the children ready " +
      "to tear you apart.");

    return "";
}


dragon_hint()
{
    command("say That poor old critter is more than half mad. Her own " +
      "children were killed in some great war, and now she's " +
      "got it in her head, that our children is her children. " +
      "Actually she's as much a prisoner as we are. " +
      "I don't know where the lord dug her up, but it was a " +
      "sorry thing to do, and I hope he pays for it someday.");

    return "";
}

court_hint()
{
    command("say The exit to the courtyard is on the level above this " +
      "one."); 

    return "";
}


cave_hint()
{
    command ("say Its an old cave in the southern end of the fortress " +
      "courtyard. The men are being held prisoners there while " +
      "they aren't working.");

    return "";
}


lord_hint()
{
    command("say The dragon highlord Verminaard, has his headquarters in " +
      "this fortress. He is a black cleric, and the leader of the " +
      "red dragon army. He is probably out inspecting his troops.");

    return "";
}


escape_hint()
{
    command("say If you ask me to follow you, I will, but you must get my " +
      "child and husband too.");

    return "";
}

follow()
{
    string who;

    if (query_follow())
        return "";
    
    if (!present(TP, E(TO)))
        return "";
    
    set_follow(TP);
    command("say Ok. I'll follow you. But you must free my family too.");

    return "";
}


int
got_doll(object what, object from)
{
    command("smile " + from->query_real_name());
    command("say Oh! this looks like my daughters doll.");
    
    if (what->query_blood_stains())
    {
        command("say I don't think she will like all those " +
            "blood stains though.");
    } else {
        command("say She will be very happy to get it back.");
    }
    
    command("give " + OB_NAME(what) + " to " + OB_NAME(from));
    return 1;
}

void
drop_unknown(object ob, object from)
{
    command("smile . " + OB_NAME(from));
    command("say Very interesting, but it's of no use to me.");
    command("give " + OB_NAME(ob) + " to " + OB_NAME(from));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    recieve_gift(ob, from);
}


int
compare_i_follow(string name)
{
    if (name == query_follow()->query_real_name())
    {
        command("emote nods at the tall man.");
        return 1;
    }
    
    command("emote shakes her head.");
    return 0;
}


public void
do_die(object killer)
{
    object girl;

    ::do_die(killer);

    girl = P("girl", E(TO));

    if (girl)
        girl->the_end();
}


void
the_end()
{
    command("emote leaves.");
    remove_object();
}
