/*
 * /d/Gondor/guilds/rangers/npc/hathaldir.c
 * modification log: 
 * 30-Mar-2000 Stern : lowered the price for athalas 
 * 31-Mar-2002 Alto: moved and revised to fit new rangers code
 * 20-Mar-2007 Finwe: failed to load old ranger.h file. changed so it loads current file.
 */
inherit "/d/Gondor/common/lib/binbit.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
//#include "../rangers.h"
#include "/d/Gondor/guilds/rangers/rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";

#define DID_INTRODUCE          "_did_intro_to_hathaldir"
#define DID_VISIT_OLD_RANGER   "_did_visit_old_ranger"
#define HINTS ({ "hint1", "hint2", "hint3", "hint4", "hint5", })

int  do_thank(object player);
int  do_reward(object player);
void given_herb(object herb);
void do_give_back(object obj, object from);
int  do_inform(string what);

static string *Hints = HINTS;

void
create_ranger()
{
    set_name(({ "hathaldir", "man", "ranger", "dunadan" }));
    set_living_name("hathaldir");
    set_race_name("human");
    set_gender(G_MALE);
    set_long("This tall and stern-looking man has greying hair framing " +
        "his fair face, which displays the typical features of a Dunadan. " +
        "When he looks at you, there is a gleam of interest in his eyes, " +
        "as if he expects you are the person he was waiting for.\n");
    set_adj(({"middle-aged", "thoughtful" }));
    set_stats(({ 99, 113, 101, 76, 86, 104 }));
    set_base_stat(SS_OCCUP, query_average_stat() + 10);
    set_tell_active(1);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY,     100);
    set_skill(SS_DEFENCE,   100);
    set_skill(SS_BRAWLING,  100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_HERBALISM, 79);

    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(CONT_I_HEIGHT, 207);
    add_prop(CONT_I_WEIGHT, 97000);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_default_answer("say I'm afraid I don't know what you mean.");
    add_ask(({"for task", "for quest", "for job", "task", "quest", "job"}),
        &do_inform("task"));
    add_ask(({"magic", "about magic"}), &do_inform("magic1"));
    add_ask(({"ranger", "rangers", "about ranger", "about rangers"}),
        &do_inform("ranger"));
    add_ask(({"spells", "spell", "about spell", "about spells",
        "spellbook", "about spellbook", }), &do_inform("spells"));

    set_chat_time(4);
    add_chat("I was a Ranger of Gondor some years ago. I enjoyed that.");
    add_chat("The Rangers are a blessing to the Free Peoples.");
    add_chat("The times are tough.");
    add_chat("Evil is coming from the East now.");
    add_chat("I hope to discover where the lost Numenorean spells are.");
    add_chat("Orcs are minions of Evil - they should be disposed of!");
    add_chat("Those Southrons are Men of bad morals and without honour.");
    add_cchat("Stop that right now!");
    add_cchat("Go away, or I shall have to kill you!");
    add_cchat("I have a distaste for goblins and murderers!");
    add_cchat("I am quite capable of fighting you, you know!");
    set_cact_time(2);
    add_cact("brawl");
}

public void
introduce(object player)
{
    player->add_prop(DID_INTRODUCE, 1);

    command("say My name is Hathaldir. Pleased to meet you.");
    command("introduce me to " + OB_NAME(player));
}

public int
trusted(object pl)
{
    if (IS_RANGER(pl) && 
        ((present("ranger_spell_book", pl) &&
          pl->query_prop(DID_INTRODUCE)) ||
         (!present("ranger_spell_book", pl) &&
          pl->query_prop(DID_VISIT_OLD_RANGER))))
        return 1;
    else
        return 0;
}

void
arm_me()
{
    seteuid(getuid(TO));

    clone_object(WEP_DIR + "dlsword")->move(TO);
    clone_object(ARM_DIR + "drcloak")->move(TO);
    clone_object(ARM_DIR + "dlboots")->move(TO);
    clone_object(RANGERS_APP_EMBLEM)->move(TO, 1);

    command("wield longsword");
    command("wear all");
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);

    if (!objectp(from))
        return;

    if (present("_herb_athelas_") == obj)
    {
        if (present("ranger_spell_book", from) || !trusted(from))
            set_alarm(4.0, 0.0, &do_thank(from));
        else
            set_alarm(4.0, 0.0, &do_reward(from));
    }
    else if (obj->id("herb"))
        set_alarm(3.0, 0.0, &given_herb(obj));
    else
        set_alarm(3.0, 0.0, &do_give_back(obj, from));

    return;
}

int
do_thank(object player)
{
    object coin;

    if (environment(player) != environment())
    {
        command("say Oh well, I didn't even get the chance to thank the " +
            player->query_race_name() + ".");
        return 1;
    }

    command("say Thanks again for your help!");
    command("say Here, I'll give you some gold coins for your trouble.");
    command("say The kingsfoil will be useful for my potion-brewing.");
    MONEY_MAKE_GC(5);
    command("give gold coins to " + OB_NAME(player));
    command("wave");
    return 1;
}

int
do_reward(object player)
{
    object book;

    FIX_EUID

    if (ENV(player) != ENV(TO))
    {
        command("say Oh well, I didn't even get the chance to reward that " +
            player->query_race_name() + ".");
      return 1;
    }
    if (trusted(player))
    {
        command("say I thank you, friend Ranger!");
        command("say I suspect you will find a spellbook useful. I know I do.");
        clone_object(RANGERS_DIR+"spells/spellbook")->move(player, 1);
        player->catch_tell("He gives you a little brown book.\n");
        command("say There you are! There are no spells in it though.");
        command("say As you know, the spells of old are lost.");
        command("say We are hoping to locate the ancient lore, and restore " +
            "it for our own good cause.");
        set_alarm(5.0, 0.0, &do_inform("magic"));
    }
    else
        command("say I thank you, my friend!");

    command("say Now, good luck out there, and thanks again!");
    command("wave");
    return 1;
}

void
do_give_back(object obj, object from)
{
    if (!objectp(obj) || !objectp(from))
        return;

    command("say You don't have to give me that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(from));

    if (objectp(obj) && present(obj, TO))
        command("drop " + OB_NAME(obj));
}

void
given_herb(object herb)
{
    if (TO->query_skill(SS_HERBALISM) >= herb->query_id_diff())
        command("say Ah, it's " + LANG_ADDART(herb->query_herb_name()) + 
        "! Thank you!");
    else
        command("say Hmm, I'm not sure what kind of herb this is. But thanks!");
}

int
do_inform(string what)
{
    string hint;

    switch (what)
    {
    case "hint1":
        command("say I have found an old diary, from the ancient North " +
            "Kingdom.");
        command("say It does not say much, but it mentions a Lieutenant of " +
            "the Army of Arnor, who was able to see in the dark of night.");
        command("say The diary shows no year or date, nor any names that " +
            "suggest any particular time, except sometime in the Third Age.");
        command("say My guess is, the Lieutenant is buried where most " +
            "lords were buried by custom, in Arnor ... ");
        command("sigh");
        command("say In the Barrow Downs. Be extremely careful there!");
        command("say They say the Dead are still awake, haunting the place.");
        command("shiver");
        break;
    case "hint2":
        command("say In the Great Library of Minas Tirith, in the White " +
            "Tower, I found a scroll telling of the House of Hurin, " +
            "the Stewards of Gondor, who also possessed a manor in Emyn " +
            "Arnen before the orcs came.");
        command("sigh");
        command("say Well, the scroll also mentioned a healer working " +
            "and practicing in the village by the Steward's manor.");
        command("say He was still healing people up until the Orcs overran " +
            "the village, and since then, nothing was heard of him.");
        command("ponder");
        command("say Emyn Arnen is south in Ithilien, and therefore " +
            "dangerous.");
        command("say If you want to search that place, I advise caution.");
        break;
    case "hint3":
        command("say Osgiliath was once the administrative centre of Gondor.");
        command("say The Royal Family lived there, in the Dome of Stars, " +
            "and with the King were scholars and advisors.");
        command("say Great lore was gathered in Osgiliath as well, the " +
            "library contained hundreds of books, most of them moved to " +
            "Minas Tirith after the Kin-strife in 1437-1447.");
        command("say A book I found in Minas Tirith reveals that there " +
            "were scrolls of magic in Osgiliath too, though lost when " +
            "Osgiliath was abandoned.");
        command("say Perhaps you can find out more about this. The library " +
            "was up on the first floor somewhere.");
        break;
    case "hint4":
        command("say The North Kingdom, Arnor, held more skill in magic " +
            "than Gondor.");
        command("say Better contact with the Elves was one reason, and from " +
            "what I have found in old writings, one of the things taught " +
            "by the First-born, was how to treat someone affected by poison.");
        command("say The Dunedain of Arnor also agreed to spread this " +
            "lore with their brethren in the South, and sent a courier " +
            "with such a scroll, as a token of goodwill and alliance.");
        command("say The courier never reached Minas Tirith.");
        command("say The Governor of Edoras at the time reported that " +
            "the courier was last seen passing the Firienwood bridge.");
        command("say This is more than 1000 years ago, so I don't consider " +
            "it likely that there is anything left to find.");
        command("say But the vales of the White Mountains may contain " +
            "many secrets, so it might be worth taking the risk.");
        break;
    case "hint5":
        command("say In the year 2002 of the Third Age, the Nine issued " +
            "forth from the Dark Land, and besieged ...." +
            "and, alas! conquered Minas Ithil.");
        command("sigh");
        command("say I am sure great Lore was lost there and then.");
        command("say Perhaps most significantly the prayer that allowed " +
            "for Elbereth to help scare undead beings away.");
        command("say Perhaps this is still hidden somewhere in the " +
            "Tower of Dark Sorcery.....");
        command("say I doubt this though, since several have tried to " +
            "locate it. Or perhaps someone did find it, but did " +
            "not make it back alive, so that the scroll of lore " +
            "was lost underways. Nobody knows.");
        command("shiver");
        break;
    case "magic1":
        command("say Ah - you are interested in magic, are you?");
        command("smile");
        command("say I thought you were.");
        command("think");
        set_alarm(6.0, 0.0, &do_inform("magic"));
        break;
    case "magic":
        command("say The magic of the Rangers is not powerful, since the " +
            "powerful lore was lost with the North Kingdom.");
        command("say There are still spells left over, but they are few, " +
            "and hard to find. My studies indicate there may be " +
            "old scrolls with spells, hidden in the old ruins, " +
            "in the places where the Faithful once lived.");
        command("think");
        if (!present("ranger_spell_book", TP)) 
            command("say If you should manage to retrieve such a scroll, " +
                "please return to me with it. I shall be most happy.");
        break;
    case "spells":
        if (!present("ranger_spell_book", TP) && trusted(TP)) 
        {
            command("say The scholars of the Faithful Numenoreans did " +
                "indeed know spells. They learned magic from the Elves.");
            command("say But this lore was lost. I have only few " +
                "indications as to where there might be any left.");
            command("say You can perhaps help me with this, being a Ranger?");
            command("smile");
            command("say I'd like some other favour of you first though.");
            command("say Just ask me for a task if you will.");
        }
        else if (trusted(TP)) 
        {
            command("say Yes, the spells. They intrigue me as well.");
            command("say For now, all I know is that there were scholars " +
                "in most of the Dunedain settlements of old, and " +
                "when these settlements were lost or ruined, the lore " +
                "was also lost.");
            command("say Seek out the ruins and remnants of the ancient " +
                "Dunedain settlements, both in the North, as well as here " +
                "in the South Kingdom. Even Gondor has faced decline.");
            if (!sizeof(Hints))
                Hints = HINTS;
            hint = ONE_OF_LIST(Hints);
            Hints -= ({ hint });
            set_alarm(5.0, 0.0, &do_inform(hint));
        }
        else
        {
            command("say Spells? What are you talking about?");
            command("glare " + OB_NAME(TP));
        }
        break;
    case "task":
        if (!present("ranger_spell_book", TP) && IS_RANGER(TP)) 
        {
            command("say Well....I need another leaf of kingsfoil for " +
                "my potions.");
            command("say If you can get me one, I would be happy to " +
                "reward you.");
            command("say The kingsfoil grows here in the Lebennin hills.");
        }
        else if (IS_RANGER(TP)) 
        {
            command("say I cannot think of any tasks to give you at this " +
                "time.");
            command("say I am busily trying to find traces of the ancient " +
                "lore wielded by scholars in Arnor and Gondor before the " +
                "North Kingdom fell, and the South Kingdom declined.");
            command("say If you can bring me anything that might help, I " +
                "would much appreciate it.");
        }
        else
        {
            command("say I don't think there's anything you can help me " +
                "with, though I can always use another kingsfoil.");
            command("smile");
        }
        break;
    case "ranger":
        command("say I was a Ranger of the Westlands.");
        command("say It was a good time. I enjoyed it very much.");
        command("say But through that guild, I learned to enjoy study, " +
            "in particular the Ancient Lore of Nature, studied " +
            "by the Elves, and by the Faithful Dunedain.");
        command("say Much lore was lost with the fall of Arnor, and with " +
            "the Decline of Gondor.");
        command("sigh");
        break;
    case "gondor":
        command("smile");
        command("say Gondor is the fairest land - second to Ithilien.");
        command("say The land holds much lore, but has lost a lot because " +
            "of the rising evil in the East.");
        command("say Minas Ithil fell, later also Ithilien and Osgiliath.");
        command("say The times ahead will be dark and heavy!");
        break;
    case "ithilien":
        command("sigh");
        command("say Ithilien! Ah....fair forests, fragrant flowers, " +
            "green meadows......");
        command("say But now it is taken by the enemy, and with that " +
            "we lost much lore.");
        command("say There were many scholars and a big library in " +
            "Minas Ithil, and in Osgiliath as well.");
        command("sniff");
        break;
    case "herbs":
        command("say Herbs, you say? Oh yes, I know some herbs.");
        command("say There are many kinds growing here in Lebennin, " +
            "and I gather some for my own use now and then.");
        command("say It is possible to find kingsfoil in this area, " +
            "and a few others, if you're lucky.");
        command("smile");
        break;
    case "shire":
        command("smile");
        command("say The Shire, you say? That is a place far up north.");
        command("say The Halflings live there, or hobbits, they call " +
            "themselves.");
        command("say The Rangers of the North are protecting them in secret.");
        break;
    case "sauron":
    case "evil one":
        command("stare");
        command("say Don't ever mention that name!");
        command("say He has spies everywhere!");
        break;
    case "orcs":
        command("growl");
        command("say I hate orcs! And I fear their numbers as well.");
        command("say They are servants of evil, and will never " +
            "be able to think of anything but evil deeds.");
        command("say There are orcs in Gondor even now!");
        command("sigh");
        break;
    case "rivendell":
    case "imladris":
    case "karningul":
        command("nod thoughtfully");
        command("say " + CAP(what) + " was founded in the year " +
            "1697 of the second age by Elrond as an elven refuge " +
            "when Eregion was overrun.");
        command("say " + CAP(what) + " has long been a center " +
            "of lore and wisdom.");
        break;
    case "unknown":
        if (!random(4)) command("say Hmm. I don't think I quite understand.");
        break;
    }
    return 1;
}

void
no_sentence(string what)
{
    if((what[strlen(what)-1..strlen(what)-1]) == " ")
        what = what[0..strlen(what)-2];

    command("peer " + OB_NAME(TP));
    command("say " + CAP(what) + "?");
    command("say What is that supposed to mean?");
    command("ponder " + what + ", life, the universe, and everything.");
    command("say Can't you talk in complete sentences, " +
        TP->query_race_name() +"?");
}
