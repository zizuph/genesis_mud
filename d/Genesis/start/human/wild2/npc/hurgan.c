/*
 * /d/Genesis/start/human/wild2/npc/hurgan.c
 *
 * Blacksmith for the Forge in Sparkle
 *
 * Varian - March 2016
 *
 */

inherit "/std/monster.c";

#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"
#include "/d/Genesis/start/human/wild2/wild.h"

void

introduce_me();
arm_me();

int intro_id;

void
create_monster()
{
   
    set_name("hurgan");
    add_adj(({"strong","black-haired"}));
    set_title("the Master Blacksmith");
    set_long("This dwarf looks incredibly strong, probably the result of " +
        "being a blacksmith.\n");
    set_race_name("dwarf");
    set_gender(0);
   
    add_act("smile all");
    add_act("emote hammers away in the forge.");
    add_act("emote wipes some sweat from his brow.");
    add_act("emote washes some grime from his face.");
    add_act("emote stretches his back, rubbing life into tired muscles.");
    add_act("stretch");
    add_act("emote straightens his apron before going back to work");
    add_act("emote hammers away in the forge.");
    add_act("emote wipes some sweat from his brow.");
    add_act("emote hammers away in the forge.");
    add_act("emote wipes some sweat from his brow.");
    add_act("emote hammers away in the forge.");
    add_act("emote wipes some sweat from his brow.");
    add_act("emote gathers some more coal from a crate to fuel the forge.");
    add_act("emote removes his metal from the fire pit and moves it to " +
        "the anvil where he begins to hammer and shape it.");
    add_act("flex tired");
    add_act("emote frowns as he inspects his work");

    add_chat("I wonder when my next shipment of ore will arrive.");
    add_chat("Hello there, can I help you with anything?");
    add_chat("If you have a dull or worn weapon, I can probably help you " +
        "with that!");
    add_chat("The road to Larton is dangerous these days, I hope it " +
        "doesn't affect business!");
    add_chat("Did you hear about all of these bandits? First they start " +
        "ambushing honest travellers on the road to Larton, and now I hear " +
        "they have a secret hideout near Sparkle!");
    add_chat("If you ever heard that dwarven blacksmiths were the best in " +
        "all of Genesis, you heard right.");
    add_chat("Could you give me a hand and pump the bellows for me?");
    add_chat("I come from a long line of blacksmiths!");
    add_chat("My father had a forge right in the heart of Dwarfheim once " +
        "upon a time, but I felt that I would get more business out here " +
        "closer to human lands!");

    set_act_time(14);
    set_chat_time(25);   

    add_ask(({"task","tasks","help","job"}),VBFC_ME("ask_task"));
    add_ask(({"helper","apprentice"}),VBFC_ME("ask_apprentice"));
    add_ask(({"bree"}),VBFC_ME("ask_bree"));
    add_ask(({"grey havens", "havens", "shire", "middle-earth", "gondor",
        "rohan", "morgul", "minas morgul", "mirkwood"}),VBFC_ME("ask_shire"));
    add_ask(({"hobbit", "hobbits"}),VBFC_ME("ask_hobbit"));
    add_ask(({"ore","iron","iron ore","shipment"}),VBFC_ME("ask_ore"));
    add_ask(({"sharpen","dull","weapon","weapons","fix","mend",
        "repair"}),VBFC_ME("ask_fix"));
    add_ask(({"instruction", "instructions"}),VBFC_ME("ask_instruct"));
    add_ask(({"bandit", "bandits","ambush","hideout"}),VBFC_ME("ask_bandit"));
    add_ask(({"smith","blacksmith","smithy","black smith","father",
        "grandfather","trade","apprentices","learn","blacksmithing","smithing",
        "work"}),VBFC_ME("ask_smith"));
    add_ask(({"sparkle", "dark road", "road"}),VBFC_ME("ask_sparkle"));
    add_ask(({"dwarfheim","dwarf","dwarves"}),VBFC_ME("ask_dwarfheim"));
    add_ask(({"larton"}),VBFC_ME("ask_larton"));
    add_ask(({"goblins","humans","gnomes","elves","races","human","goblin",
        "gnome","elf"}),VBFC_ME("ask_race"));
    add_ask(({"genesis","lands","land","donut"}),VBFC_ME("ask_genesis"));
    add_ask(({"barrel","barrels"}),VBFC_ME("ask_barrel"));
    add_ask(({"forge","pit","fire","coal"}),VBFC_ME("ask_forge"));
    add_ask(({"bellows"}),VBFC_ME("ask_bellows"));
    add_ask(({"anvil"}),VBFC_ME("ask_anvil"));
    add_ask(({"workshop","tools"}),VBFC_ME("ask_tools"));
    add_ask(({"hammer","sledge", "sledge hammer",
        "sledgehammer"}),VBFC_ME("ask_hammer"));
    add_ask(({"duck","ducks"}),VBFC_ME("ask_duck"));

    set_default_answer(VBFC_ME("default_answer"));

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENCE, 100);

    set_stats(({ 250, 100, 160, 70, 70, 120}), 10);
   
    set_alignment(270);
   
    add_prop(OBJ_M_NO_ATTACK, "You are about to attack the blacksmith when " +
        "some strange force holds you back. Perhaps it is your conscience? " +
        "Perhaps magic? Whatever it is, something prevents you from " +
        "attacking him right now.\n");

    intro_id = 0;
    set_alarm(0.5,0.0,"arm_me");

}

string
ask_task()
{
    command("say Well, could you perhaps help me out by pumping the " +
        "bellows for me?");
    command("smile");
    command("say It has been a little difficult here since my last " +
        "apprentice left.");
    return "";
}

string
ask_apprentice()
{
    command("say I used to have an apprentice, but he left for some far-off " +
        "town named Bree to start working on his own.");
    return "";
}

string
ask_bree()
{
    command("say Bree is a small town just east of the Shire! If you wanted " +
        "to become a blacksmith yourself, I hear that they take on and " +
        "train many apprentices in the town of Bree! There " +
        "should be a ship leaving from Sparkle to take you there. I " +
        "believe they can take you to the Grey Havens, a port of some " +
        "reknown just west of the Shire.");
    return "";
}

string
ask_shire()
{
    command("say Well, I really don't know too much about other lands in " +
        "Genesis really, I have spent nearly my entire life near Dwarfheim!");
    command("emote tugs his beard in careful contemplation.");
    command("say But you see, there is this one land they call Middle-Earth " +
        "- which is a right funny name if you ask me!");
    command("chuckle");
    command("say The Shire, the Grey Havens, and even other places such " +
        "as Gondor are all found within Middle-Earth. Aside from a funny " +
        "little folk that call themselves Hobbits, most of whom live in " +
        "that Shire place, I really couldn't tell you anything more!");
    return "";
}

string
ask_hobbit()
{
    command("say Hobbits?");
    command("ponder");
    command("say I can't really say I know much about them to be honest! " +
        "They are a queer little folk who are even shorter than us Dwarves, " +
        "with round bellies and hairy feet! They do seem to know the value " +
        "of a fine meal and a good pipe mind you!");
    return "";
}

string
ask_ore()
{
    command("say I have been waiting for a shipment of iron ore to come " +
        "down from Dwarfheim! I hope it arrives soon.");
    return "";
}

string
ask_fix()
{
    command("say Well, I don't forge any new weapons, but I can certainly " +
        "help you our by trying to fix any of your weapons that might have " +
        "become dull or damaged.");
    command("emote points up at his wooden sign.");
    command("say Just read my sign there for more instructions.");
    return "";
}

string
ask_instruct()
{
    command("say Why don't you read my sign instead of asking me? It's all " +
        "there!");
    return "";
}

string
ask_bandit()
{
    command("say There are a lot of bandits out there these days! They have " +
        "been ambushing merchants when travel the Dark Road up to Larton. " +
        "In fact, I have heard it said that they are so bold now that they " +
        "have even established some sort of secret hideout just outside " +
        "of Sparkle!");
    return "";
}

string
ask_smith()
{
    command("say Smithing is the family trade you might say. My father " +
        "was a blacksmith, and my grandfather as well! If you ever wanted " +
        "to take up the trade yourself, I hear they are taking on lots of " +
        "apprentices in Bree!");
    return "";
}

string
ask_sparkle()
{
    command("say If you just follow the Dark Road south, all the way to " +
        "the crossroads, you can go east to the famous port of Sparkle!");
    return "";
}

string
ask_dwarfheim()
{
    command("say Dwarfheim is the traditional homeland of the dwarves. I " +
        "came from there as a young lad myself you know! You could go visit " +
        "if you were of a mind you know! You just follow the golden brick " +
        "road north and find your way up to the highest waterfall! The " +
        "entrance to Dwarfheim is in a cave that opens up right beside that " +
        "waterfall!");
    command("smile wistfully");
    command("say Mind you, I hear that someone has been capturing the ducks " +
        "that swim in the river there! Why? I don't know. There are some " +
        "strange people out there these days.");
    return "";
}

string
ask_larton()
{
    command("say The town of Larton is up at the north end of the Dark " +
        "Road. Of course, you don't see many people come down from there " +
        "anymore, not with all these bandits around ambushing people on the " +
        "road!");
    return "";
}

string
ask_race()
{
    command("say There are all sorts of races wandering around the lands " +
        "of Genesis! Elves, gnomes, humans, goblins and goodness knows " +
        "what else! I don't have much to do with most of them mind you, I " +
        "just run my little smithy here.");
    return "";
}

string
ask_genesis()
{
    command("say Genesis is the name of all the lands around " +
        "us, you know, the entire world! They say our world looks like one " +
        "big donut, you know, a ring with lots of oceans and lands strung " +
        "out around it. At least, that is what they tell me!");
    return "";
}

string
ask_barrel()
{
    command("say Two of those barrels over there are filled with water, one " +
        "salted and the other clean, while the third is filled with olive " +
        "oil! I quench the hot metal in those barrels to cool it off and " +
        "make it hard.");
    return "";
}

string
ask_forge()
{
    command("say That is my forge over there. It looks a bit like a raised " +
        "stone fire pit, with a bunch of coal that I burn inside it. It is " +
        "raised up so that it is easier for me to heat the metal in the " +
        "fire, and I like to use coal because it burns so much hotter.");
    return "";
}

string
ask_anvil()
{
    command("say I use this anvil to hammer and shape the metal once I have " +
        "it hot enough!");
    return "";
}

string
ask_bellows()
{
    command("say The bellows sucks in air and pushes it out to feed the " +
        "fire and make it hotter! You work it by pumping the handles open " +
        "and closed.");
    return "";
}

string
ask_tools()
{
    command("say This workshop here is filled with all of my tools! " +
        "Everything I need to do the job of a blacksmith!");
    return "";
}

string
ask_hammer()
{
    command("say I wear a thick apron to protect me from sparks as I work " +
        "the metal, and this sledge hammer is specifically designed for " +
        "working the iron.");
    return "";
}

string
ask_duck()
{
    command("say Yeah, I heard that someone has been capturing ducks. " +
        "I even heard one traveller say that he saw someone else " +
        "using the duck in some dark rite of sacrifice!");
    command("laugh");
    command("say Isn't that absurd? Who would want to sacrifice a duck???");
    command("laugh");
    return "";
}

public string
default_answer()
{
   string  answer = one_of_list( ({
        "You know, I'm not really sure. Sorry, I can't help you with that.",
        "I don't know much about that!",
        "Hmm.... it sounds like you know more about that than I do!",
        "What? Can't say I know much about that, you will have to find " +
            "your answer elsewhere.",
        "Couldn't tell you much there, sorry!",
        "I'm just a simple blacksmith, those are questions for someone " +
            "more worldly than me!",
        "You know, I don't think I know enough to help you out there.",
        "I don't really think I have anything to tell you about that.",
        "Well! I don't think I have ever had anyone ask me that before! " +
            "Sorry, but I really just don't know anything about it." }) );
    command("emote scratches his beard in thoughtful contemplation.");
    command("say " + answer);
    return "";
}

arm_me()
{
    object hammer, apron;

    { setuid(); seteuid(getuid()); };

    hammer = clone_object(WILD_DIR + "wep/hammer.c");
    apron = clone_object(WILD_DIR + "arm/apron.c");

    hammer->move(TO);
    apron->move(TO);
   
    command("wear all");
    command("wield all");
}

void
add_introduced(string person)
{
    if (intro_id == 0) 
    {
        intro_id = set_alarm(4.0,0.0, introduce_me);
    }
}

void
allow_introductions() 
{
    intro_id = 0;
}

void
introduce_me()
{
    command("introduce me");

    set_alarm(15.0, 0.0, allow_introductions);
}
