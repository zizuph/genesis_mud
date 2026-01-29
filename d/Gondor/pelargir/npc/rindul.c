/*
 * /d/Gondor/pelargir/npc/rindul.c
 *
 * This is the jeweller in Pelargir, located in 
 * /d/Gondor/pelargir/misc/jewel_shop.c
 * 
 * Coded by Gwyneth on November 10, 2000
 */

inherit "/d/Gondor/std/monster";

#include <const.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

public void
create_gondor_monster()
{
    set_name("rindul");
    set_living_name("rindul");
    set_adj(({"friendly", "talkative"}));
    set_gender(G_MALE);
    set_race_name("human");
    set_long("His dark hair contrasts sharply with his pale " +
        "ivory skin, and the constant smile on his lips greets " +
        "customers with genuine pleasure. He bustles around the " +
        "store, straightening displays and wiping away any smudge " +
        "of dirt he finds.\n");
    set_title("of Pelargir, Jeweller and Goldsmith");
    default_config_npc(75);
    set_alignment(130);

    set_equipment(({MINAS_DIR+ "obj/ctrousers", MINAS_DIR + "obj/ltunic"}));

    add_prop(OBJ_M_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 1);

    set_chat_time(13);
    add_chat("Diamonds are the hardest stones around, perfect " +
        "for a lovely ring for your special someone!");
    add_chat("Have you ever seen a ruby in full sunlight? They're " +
        "just stunning!");
    add_chat("I think sapphires look astounding on a necklace " +
        "made to grace a lovely woman's neck.");
    add_chat("Sometimes sapphires and rubies come with perfectly " +
        "symmetrical six-rayed stars. It is simply amazing to " +
        "watch them shift with the light.");
    add_chat("Alexandrite has a most intriguing characteristic of " +
        "changing from green to red by the light of a candle!");
    add_chat("The cat's-eye stone is highly prized by collectors " +
        "and gem connoisseurs.");
    add_chat("Nice red spinels can often be confused as rubies, " +
        "and blue spinels as sapphires."); 
    add_chat("Yellow topaz brings thoughts of sunshine and summer " +
        "to mind, but they make better necklaces than rings, being " +
        "a bit on the brittle side.");
    add_chat("Beryl usually has a milky green colour to it, but I " +
        "have seen a few red and golden beryls in my time.");
    add_chat("A nicely coloured pair of emeralds would dangle nicely " +
        "on a young lady's ears!");
    add_chat("Yellow beryl is sometimes known as heliodor, meaning " +
        "\"gift of the sun\".");
    add_chat("I think garnets look best with a cabochon cut.");
    add_chat("Many people find the mixed red and green of " +
        "tourmaline to be quite fascinating.");
    add_chat("Iolite changes colour depending on where the light is, " +
        "and has been used for navigating on cloudy days.");
    add_chat("Some people believe that amethysts can protect you " +
        "from getting drunk.");
    add_chat("Jade is ideal for carving works of art!");
    add_chat("Small peridots are can be arranged quite nicely in " +
        "intricate patterns in jewelry.");
    add_chat("White opals are often artificially coloured and " +
        "passed off as the extremely rare and valuable black opal.");
    add_chat("Fire opal is valued mainly by collectors as a curiousity.");
    add_chat("Moonstones have a rather soft and pleasing look to " +
        "them, don't you think?");
    add_chat("It wouldn't be very wise to use the soft tanzanite " +
        "gem in a ring, but it is very rare and prized for " +
        "other types of jewelry.");

    add_ask(({"help", "task"}), "say I'm always interested in " +
        "precious gems and gold and silver dust. I'd pay you well " +
        "for them.", 1);
    add_ask(({"gold", "gold dust"}), "say I'm sorry, I have more " +
        "customers who demand gold dust than I can supply! The " +
        "last batch I sold was to a golden-haired young man, " +
        "but he's not from around here.", 1);
    add_ask(({"man", "young man", "golden-haired man", 
        "golden-haired young man"}), "say He said he was under " +
        "orders from his superior officer.", 1);
    add_ask(({"superior officer", "officer"}), "say He didn't say much " +
        "more about it, I'm sorry.", 1);
    add_ask(({"silver", "silver dust" }), 
        "say I'm sorry, I have more customers who demand silver " +
        "dust than I can supply! The last batch I sold was to " +
        "a dark-skinned foreigner.", 1);
    add_ask(({"foreigner", "dark-skinned foreigner"}), "say I don't know " +
        "his name, but he's not from around here. He comes here " +
        "regularly, though, and buys silver dust and other pricey gems.", 1);
    add_ask(({"dust"}), "say Dust? What kind of dust are you " +
        "interested in?", 1);
    add_ask(({"minas tirith", "Minas Tirith", "cousin"}), "say My cousin " +
        "lives in Minas Tirith. We were apprentices together! He owns a " +
        "gem store too you know.", 1);

}

public void
introduce(string name)
{
    command("present me to " + name);
}

public void
add_introduced(string name)
{
    set_alarm(1.0, 0.0, &command("say A pleasure to meet you!"));
    set_alarm(2.0, 0.0, &introduce(name));
}

