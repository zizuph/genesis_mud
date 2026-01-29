/*
 *  /d/Shire/common/bree/npc/dwarf.c
 *
 *  A knowledgeable patron of the Prancing Pony.
 *
 *  Glaurung 4-98
 */

inherit "/d/Shire/std/monster";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <ss_types.h>

//** Prototypes **//
void beer_response(object o, object p);
void junk_response(object o, object p);
void coin_response();

void
create_shire_monster()
{
    set_name("gloin");
    set_race_name("dwarf");
    set_adj(({"wrinkled","white-bearded"}));
    set_long("This is one of the visitors to the Prancing Pony. He looks like "
        +"he wishes to appear unconcerned about other's affairs, but he is listening.\n");
    set_stats(({65,50,70,30,40,95}));
    set_alignment(100);
    set_introduce(1);
    set_skill(SS_WEP_AXE,70);
    set_skill(SS_PARRY,70);
    set_skill(SS_DEFENCE,60);
    set_gender(G_MALE);

    add_prop(CONT_I_WEIGHT, 60*1000);
    add_prop(CONT_I_HEIGHT, 120);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
    set_chat_time(3);	    
    add_act(({"emote takes out his tobacco.","emote stuffs his pipe with some tobacco.",
        "emote lights his pipe.","emote gets a big smile all over his face as he inhales some smoke from his fine pipe."}));
    add_chat("The fire could use some stoking, me thinks.");
    add_chat("Where the pick is sharp, the will is strong, and where the gold is good, the heart is warm.");
    add_chat("I'd be careful if I were you...lots of eyes and ears around.");
    add_chat("The shadow of the East has returned.");
    add_chat("Arthad owes me a beer!");

    set_act_time(5);
    add_act("emote drinks his stout beer.");
    add_act("smile sli");
    add_act("emote perks his ears up at the last bit of conversation.");
    add_act("emote stares at the fireplace a while.");
    
    set_cact_time(5);
    add_cact("knee all");
    add_cact("emote screams: STOP IT, or I'll get angry at you!");
     
    set_cchat_time(3);
    add_cchat("You think you are tough attacking a dwarf eh?");
    add_cchat("You stinking snob of an easterling!!");
    add_cchat("Alas! I'll have to kill you now.");

    add_ask("arthad", VBFC_ME("about_arthad"));
    add_ask("business", VBFC_ME("about_business"));
    add_ask(({"Last Bridge","last bridge","bridge"}), VBFC_ME("about_bridge"));
       
    add_equipment(({"/d/Shire/common/bree/wep/daxe",
        "/d/Shire/common/bree/arm/ltunic"}));
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(from))
        return;

    if (function_exists("create_coins", ob) == "/std/coins")
    {
        set_alarm(1.0, 0.0, coin_response);   
        return;
    }

    if (function_exists("set_alco_amount", ob) == "/std/drink")
    {
        set_alarm(1.0, 0.0, &beer_response(ob, from));
        return;
    }

    set_alarm(1.0, 0.0, &junk_response(ob, from));
}

void
beer_response(object ob, object from)
{
    int i, amt = ob->query_alco_amount();
    string race = from->query_race_name();

    command("emote takes a quick swig of the "+ob->short());
    switch (amt)
    {
        case 0:
            command("emote spits it back out on the floor!");
            command("say What is this weak orc-dung you've given to me!");
            if (race == "dwarf")
            {
                command("say Being a dwarf you should know better!");
                command("glare "+from->query_real_name());
            }

            else
            {
                command("say I don't know what you "+race+" flakes "+
                    "drink but we dwarves like it a litle stronger!");
                command("scold "+from->query_real_name());
            }
            command("emote throws the "+ob->short()+" across the room "+
                "hitting another patron!");
            // bar brawl? :)
            break;

        case 1..15:
            command("emote wrinkles up his nose");
            command("say I thought I asked for a beer?");
            command("say This tastes like flavored water to me!");
            command("emote leans back in his chair and crosses his arms");
            break;

        default:
            command("emote sits up straight and his eyes open wide");
            for (i = 0; i < 8; i++)
                command("burp");
            command("say Now that's more like it!");
            command("say More!");
    }

    ob->remove_object();
}       
                            
void
coin_response()
{
    command("say Thank ye!");
    command("say I'll save this for my next keg!.");
    command("emote laughs heartily");
}

void
junk_response(object ob, object from)
{
    command("say I'm no pack-rat silly "+from->query_race_name()+"!");
    if (objectp(present(from, ENV(TO))))
        command("give "+ob->query_name()+" to "+from->query_real_name());
    else
        command("drop "+ob->query_name());
}

void
attacked_by(object obj)
{
    ::attacked_by(obj);
    command("emote downs the last of his stout beer and rises from his seat");
    command("say to "+obj->query_real_name()+" You shouldn't mess wit' me, "+
         "I'm stronger than I look!");
    command("emote grips the hilt of his axe!");
}

string
about_arthad()
{
    command("say I'm lookin' for that rascal too!");
    command("say Laddie promised to buy me a beer when he come "+
        "from his business.");
    command("say Blast that troll-footed oaf for takin' his sweet time.");
    command("grumble");
    command("emote looks around for the nearest mug");
    return "";
}

string
about_business()
{
    command("say I don't rightly know what that orc-breathed "+
        "slow-poke is doin'....");
    command("emote grumbles about the beer owed to him");
    command("say He had some ass pullin' a large cart for him.");
    command("whisper "+TP->query_real_name()+" We last crossed "+
        "paths near the Last Bridge if that's any help to ya.");
    return "";
}

string
about_bridge()
{
    command("say Are ye daft "+(TP->query_gender() ? "lass" : "man")+
        "?...the _LAST_ Bridge!");
    command("point east");
    command("say Head eastward and you'll eventually come to it!");
    command("grumbles about newbies");
    return "";
}

string
about_beer()
{
    command("emote sits up straight");
    command("say You buying?");
    command("smile happily");
}
