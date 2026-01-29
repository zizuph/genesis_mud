#pragma strict_types
//-*-C++-*-
// file name:      /d/Avenir/common/bazaar/NPCS/jadestone.c
// creator(s):     Ilyian May 1995
// purpose:	      Dej minha to hand out quests and Watch from the Hill.
// 
// revisions:   Lilith, May 2022
//                This file is no longer "jadestone" but rather
//                a quest npc. Jadestone Doll has been moved to
//                the Holm in reward for her 27 years of effort
//                in the Bazaar.
//                Keeping this filename since it may be referenced
//                in places I am unaware of.
// 
# include <composite.h>
# include <cmdparse.h>
# include <filter_funs.h>
# include <macros.h>
# include <money.h>;
# include <ss_types.h>
# include <language.h>
# include <stdproperties.h>
# include <wa_types.h>
# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/macros.h"
# include "/d/Avenir/include/paths.h"
# include "/d/Avenir/smis/sys/statserv.h"
# include "/d/Avenir/include/guilds.h"
# include "/d/Avenir/include/relation.h"

// This allows her to answer questions about the gods, etc.
inherit "/d/Avenir/common/gods/god_asks";
inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/defeat";
inherit "/d/Avenir/inherit/emote_hook";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/inherit/quest";

# define KILL_FILE	"/d/Avenir/log/deaths/baz_dej"
# define QUEST_FILE	"/d/Avenir/log/quest/jadeflower"
# define GROUP		0

# define FLOWER_BIT	15
# define FLOWER_EXP	500

# define LETTER_BIT    7
# define LETTER_EXP    1500

# define PLANS_BIT     9
# define PLANS_EXP     3000
# define PLANS_ID      "Avenir_infidel_plans"

# define NOCHIPA_BIT    10
# define NOCHIPA_EXP    5000

# define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))


string attrib, eyes, hair, desc;
int who, me, been_attacked, last_start_fight = time(), last_hit;

/* Function prototypes */

void test_flower_quest(object player);
void reward_flower_quest(object player);

void test_letter_quest(object player);
void reward_letter_quest(object player);
void give_letter_quest(object player);

void test_plans_quest(object player);
void reward_plans_quest(object player);

void give_nochipa_quest(object player);
void test_nochipa_quest(object player);
void reward_nochipa_quest(object player);

void give_token(object player);
void drop_unwanted(object what, object who);

void set_eyes(string str)   {    eyes = str;      }
void set_desc(string str)   {    desc = str;      }
void set_who(int who)       {    me = who;        }
void set_hair(string str)   {    hair = str;      } 

string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_desc()   {    return desc;      }
int    query_who()    {    return me;        }

string my_long();
string give_task();
string inquis_ask();
string jazur_ask();
string union_ask();
string past_ask();
string merc_ask();
string what_me();
string heal_me();

mixed *everyone = ({
    ({ "Steel Nightflower", "well-muscled", "alert black", 
       "honey-coloured", "Third Maiden of the Pearl", 
       ({"steel", "nightflower"}), }),

    ({ "Peridot Petal", "lithe", "serious green", 
       "chestnut-brown", "Mistress of the Thorn", 
       ({"peridot", "petal"}), }),

    ({ "Mink Martinet", "broad-shouldered",
       "mirthful dark", "glossy dark brown", 
       "Mistress of the Lash", ({"mink", "martinet"}), }),
});


/* 
 * set_morph sets the various attributes of the npc (from the *everyone 
 * array), making it unique. We can use this to 
 * set which npc we want or let it generate them randomly.
 */
void
set_morph(int who)
{
    mixed someone;
    someone = everyone[who];
    set_living_name(someone[0]);
    set_name(someone[0]);
    add_name(someone[5]);
    set_adj(({"faithful", someone[1] }));
    add_adj(({ someone[5] }));
    set_desc(someone[1]);    
    set_eyes(someone[2]);
    set_hair(someone[3]);
    set_title(someone[4]);
    set_who(who);
}


void
create_monster()
{
    /* If I'm not a clone, don't bother with the rest */
    if (!IS_CLONE)
        return;

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();

    /* Set my identity */
    set_morph(random(3));

    set_long(my_long);
	
    set_race_name("half-elf");
    add_name(({"shadow elf", "dej-minha", "dej", "minha",
       "_hilltop_dej_"}));
    set_gender(G_FEMALE);
    set_appearance_offset(0);
    default_config_npc(random(20) + 130);
    set_alignment(0);
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 50);
	
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_AWARENESS,    100);
	set_skill_extra(SS_AWARENESS, 50);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_ACROBAT,      100);
	
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_INVIS, 1 + random(10));
    add_prop(CONT_I_HEIGHT, 210);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(LIVE_M_ATTACK_THIEF, thief_fun);
    add_prop(LIVE_I_QUICKNESS, 125);
    add_prop(LIVE_I_SEE_DARK, 1);
	 
    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);

     set_act_time(20);
      add_act("emote tilts her head back and looks up at the Source.");
      add_act("sigh .");
      add_act("twinkle misch");
      add_act("say Once we find that Infidel hideout, there will be "+
              "a river of blood.");
      add_act("smile sweet");
      add_act("emote looks around with intense interest.");
      add_act("ponder");
      add_act("emote tugs on one of her braids.");
      add_act("say I need someone to deliver a letter for me.");
      add_act("say My last Narcissus has wilted.");
      add_act("whisper punisher Down there, do you see that?");
      add_act("emote scans the marketplace below.");
      add_act("emote pauses for a moment, and stares at a specific "+
              "area in the bazaar.");
      add_act("nod brief punisher");
      add_act("emote gestures emphatically at a guard.");
      add_act("emote presses her hand against her chest.");
      add_act("say I look forward to removing this shirt soon.");
      add_act("emote swiftly punches the air a few times.");
      add_act("emote does a few practice kicks.");
	  add_act("bounces on the balls of her feet, arms relaxed at her sides.");

  set_cact_time(4);
    add_cact(heal_me);
    add_cact("say This was one of the worst ideas you've had.");
    add_cact("say Leave, or you will force me to kill you.");
    add_cact("say You aren't very bright, are you?");
	
    add_ask(({"jadestone", "jadestone doll"}),
        "say For 27 years she stood on this hill and brought "+
        "infidels to justice. Today, she Hunts upon the Holm "+
        "as is her desire and the Hegemon's reward.",1);  
    add_ask(({"holm", "hunt"}), "The Holm is a place where those "+
        "consigned to death are sent, and then Hunted by those "+
        "who have earned access.", 1);		
    add_ask(({"bath", "melchior's bath"}),
        "say There is a bathhouse in the City. I'd like to "+
        "get there myself when this job is through.",1);
    add_ask(({"sybarus","bazaar"}),
        "say This is the bazaar island of Sybarus.",1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}), 
        "say I must finish my task before I can return to the City.",1);
    add_ask(({"task", "job", "quest", "help"}), give_task);
    add_ask(({"flower", "narcissus"}),
        "say I think I saw one growing in the bazaar green a while "+
        "back, but I was too busy at the time to notice exactly where.",1);
    add_ask(({"infidel", "infidels"}),
        "say The wretched Infidels have a hideout around here "+
        "somewhere, and the Hegemon has charged me with "+
        "finding it. Which is just what I intend to do.",1);
    add_ask(({"infidel hideout", "hideout"}),
        "say If I knew where it was, I wouldn't be standing "+
        "here, would I now?",1);
    add_ask(({"infidel plans", "plans", "planning"}),
        "say I need to know what the infidels plans are. Do you "+
        "think you can find something in their hideout?");        
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
        "say The Faithful serve the Will of the Gods.",1);
    add_ask(({"punisher"}),"nod brief punisher",1);
    add_ask(({"lord high inquisitor", "inquisitor", "high inquisitor"}),
        inquis_ask);
    add_ask(({"master", "Master", "hegemon", "lord commissioner"}), 
        "say I am a dej-minha and I serve here at the pleasure of "+
        "my master, the Hegemon of Sybarus.", 1);
    add_ask(({"jazur"}), jazur_ask);
    add_ask(({"union","shadow union","shadow warrior"}), union_ask);
    add_ask(({"past","history", "dej-minha"}), past_ask);
    add_ask(({"mercenary"}), merc_ask); 
    add_ask(({"mergula","warlord","legion","legion of darkness"}),
        "say You will need to find his headquarters on your "+
        "own. Last I heard, he was somewhere in the land of "+
        "Terel, east of Calathin.",1);
    add_ask(({"galerin", "galerin icu ra'let"}),
        "say He must be relaxing in the Baths after the Hunt.", 1);
    add_ask("nochipa", "say She is an infidel priest of Alphum.", 1);
    add_ask(({"disk", "thin brass disk"}), 
        "say It is a mystery to me.", 1);
	add_god_asks();
    set_default_answer(what_me);

    set_restrain_path("/d/Avenir/common/bazaar/");
    set_monster_home("/d/Avenir/common/bazaar/extr/hill");
 
    set_knight_prestige(-100);  

}

void
arm_me()
{
     equip(({ 
        "/d/Avenir/common/obj/syb_coin",
        BAZAAR+"Obj/worn/jshirt",
        BAZAAR+"Obj/worn/jpants",
        BAZAAR+"Obj/worn/jboots",
        BAZAAR+"Obj/worn/jcirclet",
        BAZAAR+"Obj/worn/jgloves",
        }));

    clone_object(BAZAAR+"Obj/misc/j_letter")->move(this_object());
}

string
my_long()
{
    string  str;

    str = "She is a "+ query_desc() +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs(), " ")) 
            + " "+ query_race_name() +", presenting herself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " the "+ query_title() +",";
        str += " "+ query_exp_title() +", female "+ 
	        query_race_name() +".\n";
    }

    str += "She has the physical grace characteristic of shadow elves, "+
         "with the sturdier build of a human, revealing her half-elven "+
         "heritage.\n"+
         "Her skin is so pale as to be translucent, its whiteness tinted "+
         "blue in some places by her veins.\n"+
         "Her long "+ query_hair()+ " hair, free of any constraint save "+
         "twin braids at her temples, brushes against her waist.\n"+
         "Her "+ query_eyes() +" eyes are framed by high cheekbones "+
         "which compete for prominence with her pointed chin.\n"+
         "She seems to glow with grace and power.\n"+
         "She appears to be highly trained in the arts of unarmed combat.\n";
    return str;

}

void 
qleave()
{
    object rom;

    seteuid(getuid());
    rom = clone_object("/std/room");
    command("emote strides away, muttering something about "+
        "Melchior's Bathhouse.");
    move(rom);
    set_alarm(20.0, 0.0, &remove_object());
}


string
inquis_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say The Hegemon has charged me with wiping "+
        "out the infidel Nochipa and her followers.");
    command("emote smiles coldly, with a look in her eyes "+
        "that sends a shiver down your spine.");
    return "";
}

string
merc_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    if (IS_SYBARITE(TP))
    {
        command("ask "+ TP->query_real_name() +" Do I not "+
            "serve the Gods' Will, same as you?");
        command("whisper to "+ TP->query_real_name() +
            " You seek the favours of Jazur and are rewarded. "+
            "So it is with me.");
        command("whisper to "+ TP->query_real_name() +
            " I simply serve a different Master.");
    }       
    else
    {
        command("say I hear there are mercenaries in Sparkle, "+
            "if you are interested in joining them.");
    }
    return "";
}

string
union_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    if (IS_SYBARITE(TP))
    {
        command("whisper to "+ TP->query_real_name() +
            " You know well that I do not spread tales of the "+
            "Union or its exploits. When others ask, this is what "+
            "I say:");
    }
    command("say It is a Union of Shadow Warriors, bound to serve "+
        "the Nobles of Sybarus and the interests of Jazur, their "+
        "Patron.");
    command("say The Union is where I would be today I think, "+
        "had I not been called to serve as dej-minha.");
    return "";
}

string
jazur_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say Jazur is a multi-faceted goddess. She is Goddess of "+
        "the Twelfth Hour, as well as the Patron of the Shadow Union "+
        "and The Dancers of Veils.");
    command("say She rules over Passion and all it touches, from sensu"+
        "ality to rage.");
    return "";
}

string
past_ask()
{
    int i;

    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    command("say The common-tongue translation of dej-minha "+
        "is \"honour guard\".");
    command("say We guard the Hegemon and his interests within "+
        "Sybarus.");
    command("smile proud");
    return "";
}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }


    switch(random(5))
    {
        case 0:
        { 
            command("growl");
            command("say You can't really be expecting me to answer that!");
            break;        
        }
        case 1:
        {
            command("say Thou art a fool, and more, the child of fools.");
            command("smile disdain");
            break;
        }
        case 2:
            command("emote smiles coldly, with a look in her eyes "+
               "that sends a shiver down your spine.");
            break;
        case 3:
        {
            command("say There are answers if you but ask the right questions!");
            command("smile enig");
            break;
        }
       case 4:
       {
           command("say Give me one good reason why I should answer "+
               "you.");
           command("smile slowly");
           break;
       }
    }
    return "";       
}

public void
thief_fun(object thief, object victim, object ob)
{
    been_attacked = 1;

    if (TP->query_prop(OBJ_I_INVIS))
    {
        set_alarm(1.5, 0.0, &command("say Cahor grants "+
				     "my deeper sight, fool."));
    }
    set_alarm(0.5, 0.0, &command("emote screams in rage!"));
    set_alarm(1.5, 0.0, &command("kill " + OB_NAME(TP)));
}

string 
query_exp_title()
{
    return "sybarite";

}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    ENV(TO)->being_killed(ob);
}

void
attack_object(object ob)
{
    ::attack_object(ob);
    ENV(TO)->being_killed(ob);
}


int query_not_attack_me(object who, int aid)
{
    mixed comm;
    // 1 in 4 attacks against her will fail.	
	if (random(4) == 0)
	{
    who->catch_msg(QCTNAME(this_object()) +" deftly twists away, "+
    "causing you to miss.\n");       
    comm = (({"emote grumbles.",
    "say to "+ OB_NAME(who) +" You aren't very bright, are you?",
    "say to "+ OB_NAME(who) +" This will take you all day.",
    "emote makes evading attacks look easy.",
    "emote seems to be enjoying the workout.",
    "say to "+ OB_NAME(who) +" Leave now, before you are cursed "+
    "by Plalgus!",
    }));                
    command(one_of_list(comm));
    return 1;
	}
	else 
	return 0;
}

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 * Note:            Defeated, not dead, per /d/Avenir/inherit/defeat.c
 */
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    command("shout I warned you! Plalgus will avenge me!");
    SCROLLING_LOG(KILL_FILE, TO->query_name() +" killed by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

    // Summoning Plalgus 
    WRATHOBJ->do_judge(killer); 
	
    ::do_die(killer);

}


/*
 *   Code relating to quests
 */
string
give_task()
{
    if (!TP->test_bit("Avenir",GROUP,FLOWER_BIT))
    {
        command("say If you want to be useful, you could try and find me "+
                "a black narcissus.");
	  return "";
    }
    if(!TP->test_bit("Avenir",GROUP,LETTER_BIT))
    {
        give_letter_quest(TP);
	  return "";
    }
    if(!TP->test_bit("Avenir",GROUP,PLANS_BIT))
    {
        command("say I need to know what those infidels plan "+
           "to do next. Find their hideout and see if you "+
           "can find out when they are planning.");
	  return "";
    }
    if(!TP->test_bit("Avenir",GROUP,NOCHIPA_BIT))
    {
        give_nochipa_quest(TP);
        return "";
    }
    else
    {
        command("say At this time I can't think of any way that "+
		"you could possibly be of help to me.");
	  return "";
    }
}

void
give_token(object player)
{
    object token;
    string str; 

    token = clone_object("/d/Avenir/common/obj/syb_coin");
    token->move(player);
    str = token->short();
    player->catch_msg(QCTNAME(TO) + " gets " + str + " from her "+
        "belt and gives it to you.\n");
    tell_room(ENV(TO), QCTNAME(TO) + " gives " 
        + str + " to " + QTNAME(player) + ".\n", ({ player }));
}

/* 
 *   Flower quest
 */ 
void
test_flower_quest(object player)
{
    if(player->test_bit("Avenir",GROUP,FLOWER_BIT))
    {
        set_alarm (2.0, 0.0, &command("say Thanks again."));
        set_alarm (4.0, 0.0, &command("emote puts a ghostly "+
            "black flower in her hair."));
        return;
    }

    set_alarm (2.0, 0.0, &command("emote holds a ghostly black "+
        "flower under her nose."));
    set_alarm (5.0, 0.0, &command("say How with this rage "+
        "shall beauty hold a plea,"));
    set_alarm (8.0, 0.0, &command("say Whose action is no "+
        "stronger than a flower?"));
    //Shakespeare, Sonnet LXV
    set_alarm (9.0, 0.0, &command("smile warm " +
        player->query_real_name()));
    set_alarm (11.0, 0.0, &command("emote puts a ghostly black "+
        "flower in her hair."));
    reward_flower_quest(player);
}

void
reward_flower_quest(object player)
{
   reward_quest("Black Flower", player, GROUP, FLOWER_BIT, FLOWER_EXP);
   seteuid(getuid(TO));
   WRITE_THIS_LOG( QUEST_FILE, "gave the flower to the dej-minha and "+
       "was rewarded "+FLOWER_EXP+" exp.\n" );
   give_token(player);
}

/*
 * Letter to Galerin
 */
void
give_letter_quest(object player)
{
    if (!present("_letter_from_jadestone",TO))
    {
        command("say Well, I would have gotten you to deliver " +
		"a letter for me, but someone has already done it.");
        return;
    }
    set_alarm(2.0, 0.0, &command("ponder"));
    set_alarm(4.0, 0.0, &command("say Well, I do need someone " +
				 "to run a little errand for me..."));
    set_alarm(6.0, 0.0, &command("say Someone's	messages "
          +"have been coming to me instead of Jadestone Doll. "
          +"I need someone to run a letter over to him in the "
          +"Baths and I don't trust the orphan messengers with "
          +"it."));
    set_alarm(10.0, 0.0, &command("say Take this to Galerin icu "
          +"Ra'let at Melchior's Bath. He is tall and well-formed, "
          +"with indifferent and steely gray eyes."));
    set_alarm(12.0, 0.0, &command("give _letter_from_jadestone to "
          +TP->query_real_name()));
    set_alarm(14.0, 0.0, &command("say Hurry back with the "
          +"reply as well."));
    set_alarm(25.0, 0.0, &command("say Well, what are you waiting for?"));
    return;
}

void
test_letter_quest(object player)
{
    if(player->test_bit("Avenir",GROUP,LETTER_BIT))
    {
        set_alarm (2.0, 0.0, &command("say Hmm...thanks again."));
        set_alarm (4.0, 0.0, &command("emote reads the letter."));
        return;
    }

    set_alarm (2.0, 0.0, &command("emote opens the "
        +"white sealed letter."));
    set_alarm (4.0, 0.0, &command("emote studies the letter "
        +"carefully."));
    set_alarm (6.0, 0.0, &command("say Good. Now he knows that "
        +"Jadestone is on the Holm and will stop sending me "
        +"messages intended for her."));
    set_alarm (12.0, 0.0, &command("thank " +
        player->query_real_name()));
    set_alarm (14.0, 0.0, &command("emote folds up the "
        +"white letter."));
    set_alarm (11.0, 0.0, &reward_letter_quest(player));
    return;
}

void
reward_letter_quest(object player)
{
    reward_quest("Jadestone's Letter", player, GROUP, LETTER_BIT, LETTER_EXP);

    seteuid(getuid(TO));
 
    WRITE_THIS_LOG( QUEST_FILE, "delivered the letter "
        +"for jadestone and was rewarded "+LETTER_EXP+" exp.\n" );

    give_token(player);
    say(QCTNAME(player) + " got a nice reward.\n");

}


/*  Infidel Plans quest
 */
void
reward_plans_quest(object player)
{
   reward_quest("Infidel Plans", player, GROUP, PLANS_BIT, PLANS_EXP);
   seteuid(getuid(TO));
   WRITE_THIS_LOG( QUEST_FILE, "gave the plans to the dej-minha and "+
       "was rewarded "+PLANS_EXP+" exp.\n" );
   give_token(player);
    say(QCTNAME(player) + " got a nice reward.\n");
}

void
test_plans_quest(object player)
{
    if(player->test_bit("Avenir",GROUP,PLANS_BIT))
    {
        set_alarm (2.0, 0.0, &command("say Yes, I've seen these."));
        set_alarm (4.0, 0.0, &command("emote puts the papers in a pouch."));
        give_nochipa_quest(player);
        return;
    }

    set_alarm (2.0, 0.0, &command("emote examines the large bundle "+
        "of papers."));
    set_alarm (4.0, 0.0, &command("emote frowns and fondles her "+
        "knife."));
    set_alarm (6.0, 0.0, &command("emote shoots you a piercing look."));
    set_alarm (8.0, 0.0, &command("say These are just what I needed. "+
        "Thank you."));
    set_alarm (9.0, 0.0, &reward_plans_quest(player));
    set_alarm (11.0, 0.0, &give_nochipa_quest(player));

}

/* Nochipa quest.
 */

void 
go_to_hideout()
{
    string rom;
    rom = ("/d/Avenir/common/bazaar/infidel/stair1");
    move(rom);
    default_config_npc(300);
    refresh_living();      
}

void
give_nochipa_quest(object player)
{
    if(!player->test_bit("Avenir",GROUP,NOCHIPA_BIT))
    {
        set_alarm (3.0, 0.0, &command("say I will meet you upon "+
            "the stairs of the infidel hideout. Once there, proceed "+
            "slowly so that I may follow in your footsteps."));
        set_alarm (5.0, 0.0, &command("say Together we will slay "+
            "Nochipa, and a river of blood will flow."));
        set_alarm (3.0, 0.0, &command("say Whoever brings me "+
            "Nochipa's head will be amply rewarded."));
        set_leader(player);  
        set_follow(player->query_real_name());  
        set_alarm (8.0, 0.0, &command("emote leaves down."));
        set_alarm (8.5, 0.0, go_to_hideout);    
    }
}

void
reward_nochipa_quest(object player)
{
    reward_quest("Nochipa's Head", player, GROUP, NOCHIPA_BIT, NOCHIPA_EXP);

    WRITE_THIS_LOG( QUEST_FILE, "gave Nochipa's head to the dej-minha and "+
       "was rewarded "+NOCHIPA_EXP+" exp.\n" );
    say(QCTNAME(player) + " got a nice reward.\n");
    //set_alarm (4.0, 0.0, &give_catacombs_quest(player));
    set_alarm (10.0, 0.0, qleave);
}

void
test_nochipa_quest(object player)
{
    if(player->test_bit("Avenir",GROUP,NOCHIPA_BIT))
    {
        set_alarm (2.0, 0.0, &command("say Yes? This isn't Nochipa's head."));
        set_alarm (4.0, 0.0, &command("say You gave it to me some time ago."));
        return;
    }

    set_alarm (2.0, 0.0, &command("emote smiles triumphantly."));
    set_alarm (4.0, 0.0, &command("show full head"));
    set_alarm (6.0, 0.0, &command("say Mission accomplished."));
    set_alarm (8.0, 0.0, &command("say The Hegemon will be so pleased."));
    set_alarm (9.0, 0.0, &reward_nochipa_quest(player));
}


public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;
    if(obj->id("_this_is_narcissus_herb_"))
    {
        test_flower_quest(from);
            return;
    }
    if(obj->id("_letter_from_galerin"))
    {
        test_letter_quest(from);
            return;
    }
    if(obj->id("Avenir_infidel_plans"))
    {
        test_plans_quest(from);
            return;
    }
    if(obj->id("_head_of_nochipa"))
    {
        test_nochipa_quest(from);
            return;
    }
    set_alarm(0.1, 0.0, &drop_unwanted(obj, from));
}

void drop_unwanted(object what, object who)
{
    command("peer "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
        +who->query_real_name()))
/*  For some strange reason, npcs will drop all objects in their inventory,
 *  even if they cloned them. I've never been able to figure out why...I
 *  usually just work around it by removing objects if the player isn't
 *  there or visible.
 *      command("drop "+what->query_name());
 */
        what->remove_object();  
}


/* Players are killing her in the infidel hideout.
 * While I don't want to make it impossible to do 
 * so, I'd like to make them work a little harder 
 * for it :)  --Lilith
 */
string heal_me()
{
    string where;
    if (!wildmatch("/d/Avenir/common/bazaar/infidel/*", where))
    {
        refresh_living(); 
        command("emote cries out: Sachluph, aid me in my "+
                "moment of need!");
        command("emote seems to be in perfect health.");
    }
    return "";
}

/*
 * Function name:   do_push
 * Description:     Called from special_attack, used to reduce # of attackers.
 * Arguments:       victim / attacker
 */
private void
do_push (object victim)
{
    mixed enemies = query_enemy(-1); 
    string *exit_cmds;
    string exit, dest;
    int    ind;
  
    if (!environment() || !sizeof(enemies))
        return;

    exit_cmds = environment()->query_exit_cmds();
    if (!sizeof(exit_cmds))
        return;
  
    ind = random(sizeof(exit_cmds));
    exit = exit_cmds[ind];
    dest = (environment()->query_exit_rooms())[ind];
  
    say("Swiftly, "+ short() +" body slams "+ QNAME(victim) + 
        ", who stumbles " + exit + "!\n", ({ this_object(), victim }));
  
    victim->catch_msg("You've been hit with a body slam! You stumble "+ 
        exit +"!\n");
  
    /* Move them, make peace with them */
    victim->move_living(exit, dest, 1);
    victim->stop_fight(TO);

}

/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 * Most of these specials are from the ~Avenir/inherit/sybarite.c 
 */
int
special_attack(object victim)
{
    object     me,
              *enemies;
    int        i, con, s, sInt; 

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }
    
    // log the amount of time the fight lasted.
    if((last_hit + 500) < time())
    {
        last_start_fight = time();
    }
    last_hit = time();

    me = this_object();
    enemies = query_enemy(-1);
    con = query_attack()->query_stat(SS_CON);

    /* Focus on smallest person in a team */
    if(sizeof(enemies) > 1)
        for(i=0;i<sizeof(enemies);i++)
        {
            if(present(enemies[i], ENV(TO)) && enemies[i]->query_stat(SS_CON) < con)
            {
                attack_object(enemies[i]);
                con = enemies[i]->query_stat(SS_CON);
            }
        }

    /* Not only focus on the small one, but push big ones out of the way */
    if(sizeof(enemies) > 2)
        for(i=0;i<sizeof(enemies);i++)
        {
            if(present(enemies[i], ENV(TO)) && enemies[i]->query_stat(SS_CON) > con)
            {
                do_push(enemies[i]);
                con = enemies[i]->query_stat(SS_CON);
            }
        }

    /* Most of these specials are in sybarite.c */
    switch (random(3))
    {
        case 0: command("smash");                
          break;        
        case 1: heal_me();
          break;
        case 2: command("skick");
          break;
        default: break; 
    }
    return 0;
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(15);

    if (!query_attack())
	been_attacked = 0;

    if (!present(tp, environment(TO)))
        return;

    if (tp->id("nochipa"))
    {
        set_all_hitloc_unarmed(70);
		set_all_attack_unarmed(70, 70);
        command("say Nochipa Silve! For your blasphemy "+
            " you have been declared infidel.");
        command("kill spirit");
        command("kill nochipa");
        return;
    }  

    if (IS_INFIDEL(tp))
    {
        command("smile triumphantly");
        command("kill "+ OB_NAME(tp));
        command("shout Die, you Infidel scum!");
        return;
    }
    occ = tp->query_guild_name_occ();
    if (occ == OUNION)
    {
        if (i == 0)           
            command("say to "+ tp->query_real_name() +" Celebrate "+
                "the Source!");
        if (i == 2)
            command("greet "+ tp->query_real_name());
        if (i == 5)
            command("say to "+ tp->query_real_name() +" Thank "+
                "you for your efforts to protect Sybarus "+
                "from those Outlander scum.");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i == 1)
            command("smile "+ tp->query_real_name());
        if (i == 4)
            command("ask "+ tp->query_real_name() +
                " Keeping the masses entertained, are we?");
        return;
    }       
    else
    {
        if (i == 1)
           command("say Mascarvin's Paps! MORE Outlanders!");
        if (i == 5)
           command("say to "+ tp->query_real_name() +
               " Be careful here. I'm not Jadestone but "+
               "I am just as lethal.");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (query_attack())
	return;

    if (CAN_SEE(TO, TP))
    {
        set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}  
