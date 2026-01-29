/*
 * modification by Stern feb 2000, removed the RoN application procedures
 * (put in comment //  so it can be put back easily)
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <mail.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/common/guild/north/lib/ranger_defs.h"

#define DID_INTRODUCE  "_did_intro_to_breeranger"
#define DID_VISIT_OLD_RANGER   "_did_visit_old_ranger"
#define HINTS ({ "hint1", "hint2", "hint3", "hint4", "hint5", })

int do_thank(object player);
int do_reward(object player);
void given_herb(object herb);
void do_give_back(object obj, object from);
int do_inform(string what); 

static  string *Hints = HINTS;
static  int     retreat_id;

void
create_dunadan()
{
    set_name("aradan");
    add_name("man");
    add_name("wolfeater");
    set_living_name("aradan");
    add_name("ranger");
    add_name("dunadan");
    set_race_name("human");
    set_dunedain_house("Aranarth");
    set_gender(G_MALE);
    set_long(BSN("This man seems to prefer to stay apart from all the "
      + "noise and ruckus that goes on here in the inn, sitting quietly "
      + "with his back to the wall in the far end of the room. His face "
      + "is partly hidden within the shadows of the hood of his grey cloak, "
      + "but he seems alert to everything that is happening."));

    set_adj("silent");
    set_adj("cloaked");
    set_stats(({ 134, 143, 141, 98, 101, 114 }));
    set_base_stat(SS_OCCUP, query_average_stat() + 10);
    set_tell_active(1);
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_PARRY,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_BRAWLING,100);
    set_skill(SS_AWARENESS,100);
    set_skill(SS_HERBALISM, 79);
    add_prop("_live_m_attack_thief", 1);
    add_prop(CONT_I_HEIGHT,207);
    add_prop(CONT_I_WEIGHT,97000);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"for task","for quest","for job","task","quest","job","for a task",
        "for a quest", "for a job",}),
  	  VBFC_ME("give_task"));
    add_ask(({"magic","about magic"}), VBFC_ME("ask_magic"));
    add_ask(({"ranger","rangers","rangers of the north","about ranger",
        "about rangers","about the rangers", "about the rangers of the north",}),
	  VBFC_ME("ask_rangers"));
//    add_ask(({"joining", "joining rangers", "join", "join rangers", 
//        "join the rangers", "joining the rangers", "joining the rangers of the north", }),
//         VBFC_ME("ask_join"));  
    add_ask(({"wolfeater","Wolfeater",}),
        VBFC_ME("ask_wolfeater"));
    add_ask(({"arnor", "fornost", "annuminas",}), VBFC_ME("ask_arnor"));
    add_ask(({"barliman", "butterbur", "barliman butterbur",}),
        VBFC_ME("ask_barliman"));
    add_ask(({"strider",}), VBFC_ME("ask_strider"));
    add_ask(({"estel",}), VBFC_ME("ask_estel"));
    add_ask(({"cloak", "grey cloak", "cloaks", "grey cloaks", 
        "about cloaks", "about grey cloaks",}), VBFC_ME("ask_cloaks"));
}

public string
introduce(object player = this_player())
{
    if ((player->query_npc()) || (TO->query_prop(OBJ_I_HIDE))
        || !CAN_SEE(TO, player))
        return "";
    if (player->query_guild_name_occ() == "Rangers of the North")
    {
        player->catch_msg(QCTNAME(TO) + " nods briefly at you in recognition.\n"
          + "Stealthily he lets you catch a glimpse of something shiny hidden "
          + "within his cloak, a star-shaped brooch like your own.\n");
        command("introduce me to " + TPQRN);
        command("whisper to " + TPQRN + " I'm also called Wolfeater around here.");
        return "";
    }

    player->add_prop(DID_INTRODUCE, 1);
    command("say to " + TPQRN + " Greetings, traveller. Pleased to meet you.");
    command("say to " + TPQRN + " People around here call me Wolfeater.");
    return "";
}

public void
add_introduced(string str)
{
    set_alarm(2.0, 0.0, &introduce(TP));
}

public int
trusted(object pl)
{
    if (IS_NRANGER(pl))
        return 3;
    else if (IS_DUNADAN(pl) && IS_GOOD(pl))
        return 2;
    else if (IS_RANGER(pl) || IS_GOOD(pl))
        return 1;
    else
        return 0;
}

string
default_answer() 
{ 
    string     gstr;

    gstr = (TP->query_gender() == 0 ? "mister" : "madam");

    switch(random(10))
    {
        case 0:
          command("say I am afraid I do not know what you are talking about, "
            + gstr + ".");
          break;
        case 1:
          command("say You are a very confusing person, " + gstr + ".");
          command("grin .");
          break;
        case 2:
          command("say I wouldn't know.");
          break;
        case 3:
          command("shrug");
          break;
        case 4:
          command("say Now why would you ask me about that?");
          command("chuckle .");
          break;
        case 5:
          command("peer . " + TP->query_real_name());
          break;
        case 6:
          command("say Don't look at me, I know nothing about that.");
          break;
        case 7:
          command("sigh");
          command("say Stop asking me questions I cannot answer.");
          break;
        case 8:
          command("shake");
          command("say I do not know, " + gstr + ". Now please leave me alone.");
          break;
        default:
          command("say What are you trying to ask me?");
          break;
    }
    return ""; 
}

void
arm_me(int dummy = 0)
{
    ::arm_me(0);
    seteuid(getuid(TO));
    clone_object(WEP_DIR + "dlsword")->move(TO);
    command("wield longsword");
    clone_object(ARM_DIR + "drcloak")->move(TO);
    command("wear cloak");
    clone_object(ARM_DIR + "dlboots")->move(TO);
    command("wear boots");
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
    if (!from)
        return;
    if (present("_herb_athelas_") == obj)
    {
        set_alarm(3.0, 0.0, &do_thank(from));
    }
    if (obj->id("herb"))
    {
        set_alarm(3.0, 0.0, &given_herb(obj));
        return;
    }
    set_alarm(3.0, 0.0, &do_give_back(obj, from));
}

int
do_thank(object player)
{
    object coin;
    if (environment(player) != environment())
    {
        command("say Oh well, I didn't even get the chance to thank the "
          + player->query_race_name()+".");
        return 1;
    }
    command("say Thank you!");
    command("say Here, I'll give you five gold coins for your trouble.");
    coin = clone_object("/std/coins");
    coin->set_heap_size(5);
    coin->set_coin_type("gold");
    coin->move(TO);
    command("give six gold coins to "+player->query_real_name());
    command("smile . " + player->query_real_name());
    return 1;
}

int
do_reward(object player)
{
  object book, coin;

  FIX_EUID

  if (ENV(player) != ENV(TO))
    {
      command("say Oh well, I didn't even get the chance to reward that "
        + player->query_race_name()+".");
      return 1;
    }
  if (trusted(player)) {
    command("say I thank you, friend Ranger!");
    command("say I suspect you would find a spellbook useful, I know I do.");
    book = clone_object(RANGER_DIR+"spells/rbook");
    player->catch_msg("He gives you a little brown book.\n");
    book->move(player,1);
    write_file(LOG_DIR+"new_book",player->query_name()+" given the new spellbook. "+ctime(time())+".\n");
    command("say There you are! There are no spells in it though.");
    command("say As you know, the spells of old are lost.");
    command("say We are hoping to locate the ancient lore, and restore");
    command("say it for our own good cause.");
    set_alarm(5.0, 0.0, &do_inform("magic"));
  }
  else {
    command("say I thank you, my friend!");
  }
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
    command("give " + OB_NAME(obj) + " to " +
        from->query_real_name());

    if (objectp(obj) && present(obj, TO))
        command("drop " + OB_NAME(obj));
}

void
given_herb(object herb)
{
    if (TO->query_skill(SS_HERBALISM) >= herb->query_id_diff())
        command("say Ah, it's " + 
		LANG_ADDART(herb->query_herb_name()) + 
		"! Thank you!");
    else
        command("say Hmm, I'm not sure what kind of herb this is. But thanks!");
}

public string
give_task()
{ 
    do_inform("task"); 
    return ""; 
}

public string
ask_arnor()
{
    do_inform("arnor");
    return "";
}

public string
ask_barliman()
{
    do_inform("barliman");
    return "";
}

public string
ask_strider()
{
    do_inform("strider");
    return "";
}

public string
ask_estel()
{
    do_inform("estel");
    return "";
}

public string
ask_cloaks()
{
    do_inform("cloaks");
    return "";
}

public string
ask_magic()
{ 
    if (trusted(TP)==3)
        do_inform("magic1"); 
    return ""; 
}

public string
ask_rangers()
{ 
    do_inform("ranger"); 
    return ""; 
}

public string
ask_spells()
{ 
    do_inform("spells"); 
    return ""; 
}

public string
ask_wolfeater()
{
    command("say That's what people call me, yes.");
    command("grin .");
    command("say All because of what happened to me one winter...");
    command("say I was only nineteen years old, and was attacked by a flock "
      + "of wolves up north.");
    command("say Alone, I was. And I killed all six of them.");
    command("chuckle .");
    command("say Others add to the tale by saying I then ate all the dead wolves.");
    command("chuckle again");
    command("say That's all a tall lie though.");
    command("smile . " + TPQRN);
    command("say I only ate one.");
    command("glitter");
    return "";
}


// public void
// do_mail_captain(object pl)
// {
//     string  captain;
//     string  rnd_txt;
// 
//     captain = (NORTH_MASTER)->query_captain();
//     rnd_txt = ONE_OF_LIST(({"I just had a conversation with a Dunadan",
//       "This eve I spoke with a Dunadan", "Today I met a fellow Dunadan",
//       "I was just approached by a Dunadan", "You may like to know that a Dunadan",}));
//     MAIL_READER->create_mail("A possible recruit",
//       "Wolfeater", captain, "Elessar,Gorboth",
//       "Greetings, Captain " + captain + "!\n" + rnd_txt
//       + " named " + pl->query_name() + " in the Prancing Pony.\n"
//       + CAP(PRONOUN(pl)) + " asked me questions about the Rangers, and seemed\n"
//       + "interested in serving our cause.\n"
//       + "For Arnor,\n   Aradan Wolfeater, in Bree.\n");
//     command("whisper to " + pl->query_real_name() + " I'll pass the word.");
//     command("smile . " + pl->query_real_name());
//     command("whisper to " + pl->query_real_name() + " No promises, but keep quiet "
//       + "about it.");
//     command("wink slight");
// }

// public void
// test_apply(object pl)
// {
//     /* Check for 40 avg stat, 5 questions */
//     if ((pl->query_average_stat() < 40)
//         || (pl->query_dunedain_level() < 50))
//     {
//         command("whisper to " + pl->query_real_name() + " Never mind, I "
//           + "can see that you are too young still.");
//         command("smile . " + pl->query_real_name());
//         command("whisper to " + pl->query_real_name() + " Come back some "
//           + "other time and talk to me. Good luck out there.");
//     }
//     else if (pl->query_guild_name_occ())
//     {
//          command("whisper to " + pl->query_real_name() + " Never mind, I "
//           + "can see you already have allegiances elsewhere.");
//         command("smile . " + pl->query_real_name());
//         command("whisper to " + pl->query_real_name() + " Good luck "
//           + "out there.");
//     }
//      else do_mail_captain(pl);
// }

// public string
//  ask_join()
// {
//     if (trusted(TP) == 3)
//     {
//         command("whisper to " + TP->query_real_name() + " If you know somebody "
//           + "who would be worthy of being considered, either have them ask me "
//           + "about joining");
//         command("whisper to " + TP->query_real_name() + " or else you could "
//           + "talk to the Captain yourself.");
//         command("whisper to " + TP->query_real_name() + " Remember that only "
//           + "Dunedain may become Rangers of the North.");
//     }
//     else if (trusted(TP) == 2)
//     {
//         command("whisper to " + TP->query_real_name() + " Hmm. Are you saying "
//           + "that you would be interested in devoting your life to protecting "
//           + "these lands?");
//         command("eyebrow inquir " + TP->query_real_name());
//         test_apply(TP);
//     }
//     else
//     {
//         command("say Oh, all I ever did was travel around in this region, and "
//           + "people started calling me all sorts of things.");
//         command("say Ranger, ruffian, thief.... I did not have to join anything "
//           + "special to be awarded such reputations.");
//          command("smirk");
//     }
//     return "";
// }


int
do_inform(string what)
{
    string hint;

    switch (what)
    {
    case "magic1":
        command("say Ah - you are interested in magic, are you?");
        command("smile");
        command("say I thought you were.");
        command("think");
        set_alarm(6.0, 0.0, &do_inform("magic"));
        break;
    case "magic":
        command("say The magic of the Rangers is not powerful, since the");
        command("say powerful lore was lost with the North Kingdom.");
        command("say There are still spells left over, but they are few,");
        command("say and hard to find. My studies indicate there may be");
        command("say old scrolls with spells, hidden in the old ruins,");
        command("say in the places where the Faithful once lived.");
        command("think");
        if (!present("ranger_spell_book",TP)) 
        {
            command("say If you should manage to retrieve such a scroll,");
            command("say please return to me with it. I shall be most happy.");
        }
        break;
    case "spells":
        if (!present("ranger_spell_book",TP) && trusted(TP)==3) 
        {
            command("say The scholars of the Faithful Numenoreans did");
            command("say indeed know spells. They learned magic from the Elves.");
            command("say But this lore was lost. I have only few indications");
            command("say as to where there might be any left.");
            command("say You can perhaps help me with this, being a Ranger?");
            command("smile");
            command("say I'd like some other favour of you first though.");
            command("say Just ask me for a task if you will.");
        }
        else if (trusted(TP) == 3) 
        {
            command("say Yes, the spells. They intrigue me as well.");
            command("say For now, all I know is that there were scholars");
            command("say in most of the Dunedain settlements of old, and");
            command("say when these settlements were lost or ruined, the lore");
            command("say was also lost. Seek out the ruins and remnants of");
            command("say the ancient Dunedain settlements, both in the North,");
            command("say as well as here in the South Kingdom. Even Gondor");
            command("say has faced decline.");
            if (!sizeof(Hints))
                Hints = HINTS;
            hint = ONE_OF_LIST(Hints);
            Hints -= ({ hint });
            set_alarm(5.0, 0.0, &do_inform(hint));
        }
        else
        {
            command("say Spells? What are you talking about?");
            command("glare "+TP->query_real_name());
        }
        break;
    case "task":
/*
        if (!present("ranger_spell_book",TP) && IS_NRANGER(TP)) 
        {
            command("say Well....I need another leaf of kingsfoil for my potions.");
            command("say If you can get me one, I would be happy to reward you.");
            command("say The kingsfoil grows here in the Lebennin hills.");
        }
*/
        if (IS_NRANGER(TP)) 
        {
            command("whisper to " + TPQRN + " I don't have any jobs for you at this time.");
            command("whisper to " + TPQRN + " Maybe some other time?");
        }
        else
        {
            command("say I don't think there's anything you can help me with,");
            command("say though if you find any kingsfoil, I'd be happy to buy them from you.");
            command("smile .");
        }
        break;
    case "ranger":
        if (trusted(TP) == 3)
        {
            command("whisper to " + TPQRN + " Yes, friend, I am also a Ranger.");
            command("smile . " + TPQRN);
        }
        else if (trusted(TP) == 2 || trusted(TP) == 1)
        {
            command("say People around here would call me a Ranger indeed.");
            command("say Some even think I'm a thief or a ruffian.");
            command("say If they only knew.");
            command("chuckle .");
            command("say Old Barliman's hair would turn white if he knew the");
            command("say dangers we protect him and the Breelanders from.");
        }
        else
        {
            command("say Yes, that's what people around here call me.");
            command("eyebrow . " + TP->query_real_name());
            command("say Why do you ask?");
        }
        break;
    case "arnor":
        command("nod .");
        command("say I know a little about that... these lands used to be a part "
          + "of the ancient kingdom of Arnor.");
        command("say Wars a thousand years ago destroyed Arnor, including "
          + "its great cities Fornost and Annuminas.");
        command("dsmile");
        command("say Angmar was destroyed in return.");
        command("say Now these lands are only populated by the swarthy Northmen, and "
          + "the little people over in the Shire.");
        command("emote falls silent, staring at the wall.");
        break;
    case "gondor":
        command("smile .");
        command("say The South Kingdom ... we have lost touch with them centuries ago.");
        command("say They are facing the gravest threat, being the last fortress");
        command("say to resist the rising darkness from the East.");
        command("say We must all hope that Minas Tirith will last.");
        break;
    case "ithilien":
        command("nod");
        command("say Ithilien is far to the south, but I have never been there.");
        command("say It has been overrun by the darkness for centuries,");
        command("say and the South Kingdom never really attempted to retake it.");
        command("sigh .");
        break;
    case "herbs":
        command("say Herbs, you say? Oh yes, I know some herbs.");
        command("say There are a few kinds growing in the Chetwood forest,");
        command("say and I gather some for my own use now and then.");
        command("say It is possible to find herbs and tobacco in this area,");
        command("say and a few healing herbs, if you're lucky.");
        command("smile");
        break;
    case "shire":
        command("smile .");
        command("say The Shire is to the west of here.");
        command("say The hobbits there are blissfully unaware of the evils");
        command("say of the world, even more so than the Breelanders.");
        break;
    case "sauron":
    case "evil one":
        command("glare . " + TP->query_real_name());
        command("whisper " + TP->query_real_name() + " Don't ever mention that name!");
        command("emote whispers: He has spies everywhere!");
        break;
    case "orcs":
        command("eyebrow .");
        command("say The spawn of Morgoth.");
        command("spit");
        command("say They are servants of evil, and will never be able to "+
          "think of anything but evil deeds.");
        command("say There are smaller orcs and goblins innumerable in the Misty Mountains.");
        command("sigh");
        break;
    case "barliman":
        command("chuckle .");
        command("say Old Barliman is a friendly fellow, but blissfully ignorant "
          + "about the world outside his beloved little town of Bree.");
        command("say If he only knew the dangers....");
        if (trusted(TP) == 3)
        {
            command("whisper to " + TPQRN + " Of course, he does not know who "
              + "we Rangers are either, so be careful what you say around here.");
        }
        break;
    case "cloaks":
        if (trusted(TP) >= 2)
        {
            command("whisper to " + TPQRN + " All of us Rangers wear them.");
            command("whisper to " + TPQRN + " They are both useful and they are symbols.");
        }
        else
        {
            command("eyebrow .");
            command("say I wear this grey cloak to protect myself from the weather.");
            command("say Are you unfamiliar with the function of cloaks?");
            command("smirk");
        }
        break;
    case "strider":
    case "estel":
        if (trusted(TP) == 2)
        {
            command("whisper to " + TPQRN + " Of course I know Strider.");
            command("whisper to " + TPQRN + " Why do you ask?");
            command("peer search " + TPQRN);
            command("whisper to " + TPQRN + " Are you looking to join the Rangers?");
        }
        else if (trusted(TP) == 3)
        {
            command("whisper to " + TPQRN + " I have not seen the Chieftain lately.");
            command("whisper to " + TPQRN + " He is always off travelling, always for "
              + "our cause.");
        }
        else
        {
            command("eyebrow .");
            if (what == "strider")
                command("say Sounds like the name of another ... ruffian ... around here.");
            else if (what == "estel")
                command("say Sounds like an Elven name.");
            command("say What's it to you?");
        }
        break;
    case "rivendell":
    case "imladris":
        if (trusted(TP) > 0)
        {
            command("say The Halls of Elrond are near the foothills of the Misty Mountains.");
            command("say Only those pure of heart will find their way there, "
              + "and it is a most wonderful haven for rest and relaxation.");
            command("smile soft");
            command("say Mayhap you will find your way there some day too, friend!");
        }
        else
        {
            command("say Hmm?");
            command("say You have listened to some halfling's tall tale again?");
            command("chuckle quiet");
            command("say Don't think to hard of it, you're not likely to find it anyway.");
        }
        break;
    case "unknown":
        if (!random(4)) command("say Hmm. I don't think I quite understand.");
        break;
    }
    return 1;
}

void
return_to_inn()
{
    find_living("elessar")->catch_msg("Wolfeater returns to the Prancing Pony.\n");
    TO->move("/d/Shire/common/bree/front_room", 1);
    tell_room(ENV(TO), QCNAME(TO) + " strides in, looking around.\n");
    TO->command("sit in shadows");
}

void
retreat()
{
    retreat_id = 0;
    if (query_attack()->query_average_stat() >= (query_average_stat() - 25))
    {
        command("say I will fight you when the time is right.");
        tell_room(ENV(TO), QCTNAME(TO) + " then jumps out through "
          + "one of the windows and disappears.\n");
        find_living("elessar")->catch_msg("Wolfeater retreats from attacker "
          + query_attack()->query_name() + ".\n");
        TO->move_living("M", VOID);
        set_alarm(600.0, 0.0, return_to_inn);
    }
}

void
parry_before_retreat()
{
    tell_room(ENV(TO), QCTNAME(TO) + " draws his weapon and parries for "
      + "a little while, judging the opposition.\n");
    set_alarm(6.0, 0.0, retreat);
}

void
attacked_by(object ob)
{
    FIX_EUID;
    if (!retreat_id)
        retreat_id = set_alarm(2.0, 0.0, parry_before_retreat);
}

void
no_sentence(string what)
{
    if((what[strlen(what)-1..strlen(what)-1]) == " ")
    {
        what = what[0..strlen(what)-2];
    }
    command("peer " + TP->query_real_name());
    command("say " + CAP(what) + "?");
    command("say What is that supposed to mean?");
    command("ponder " + what + ", life, the universe, and everything.");
    command("say Can't you talk in complete sentences, " + TP->query_race_name() +"?");
}
