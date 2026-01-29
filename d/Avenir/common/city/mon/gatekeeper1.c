// file name:	gatekeeper1.c
// creator(s):	Lilith Feb 2003
// last update:
// purpose:	      Gatekeeper for First Gate
//
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/include/paths.h"
# include "/d/Avenir/include/relation.h"
# include "/d/Avenir/include/macros.h"
# include "/d/Avenir/include/guilds.h"

# include <ss_types.h>
# include <money.h>
# include <macros.h>

inherit "/d/Avenir/inherit/monster";

#define NO_SYB_COIN 0

void do_sequence(string *seq);

void
create_monster()
{
    set_name("dahrol");
    add_name(({"keeper", "gatekeeper", "magician", "priest", "anchorite",
        "anchorite of salilus"}));
    set_living_name("Dahrol");
    set_title("icu Cha'rui, Anchorite of Salilus");
    set_race_name("human");
    set_adj("majestic");
    add_adj("priestly");
    set_long("He is a dignified fellow, who stands out "+
       "amongst all the martial types as a priest or cleric "+
       "of some sort.\n");

    set_stats(({95, 85, 90, 130, 130, 130}));
    set_alignment(0);
    set_knight_prestige(-1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    MAKE_SYBARITE;
    KILL_THIEF;

    set_skill(SS_DEFENSE, 90 );
    set_skill(SS_AWARENESS, 90);

    set_act_time(3);
      add_act("emote smoothes his robe.");
      add_act("emote has an inward-looking stare.");
      add_act("emote smiles to himself");
      add_act("emote appears to be rehearsing something in his mind.");
      add_act("emote stares up at the Source.");

    set_chat_time(10);
    set_cact_time(10);
      add_cact("shout Die for this! Die!");
      add_cact("snarl enemy");

    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
        "say There are two markets: the one for outlanders, and "+
        "the one for sybarites.  You passed through the bazaar "+
        "to get her. That one is for outlanders. The merchantile "+
        "pale what sybarites use most.", 1);
    add_ask(({"park","island", "holm", "Holm"}),
         "say The Holm of the Icondite is where the shadow-elves Hunt. "+
         "They're pretty particular about who they let on that island "+
         "and when, but then I expect you know that by now.",1);
    add_ask(({"gate","key", "first gate", "First Gate"}),
         "say I am the key to this gate. If you want me to open the "+
         "gate, you must give me proof that you have earned it: "+
         "a sybarun coin.",1);
    add_ask(({"coin", "sybarun coin", "token"}),
         "say The sybarun coin is a token which grants the bearer "+
         "(and usually only the bearer, mind you) access to restrict"+
         "ed areas of Sybarus, liek the Holm, or the City.\n");
    add_ask(({"open the gate","to open the gate","open gate","open "+
         "the gate","to open gate"}),
         "say If you have earned access to the City, you have upon "+
         "your person a sybarun coin. Give it to me and I shall "+
         "open the way for you, and you alone.", 1);
    add_ask(({"give me the key","give key"}),
         "shout I am the key!",1);
    add_ask(({"bath", "melchior's bath"}),
        "say It is just through the gate. A marvellous place.",1);
    add_ask(({"sybarus","bazaar"}),
        "say It is over the Bridge of Sighs.",1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}), 
        "say You stand just outside the gate to the Forbidden City.", 1);
    add_ask(({"name", "your name", "house"}), 
        "introduce myself", 1); 
    add_ask(({"task", "job", "quest", "help"}), VBFC_ME("give_task"));
    add_ask(({"infidel", "infidels"}),
        "say The wretched Infidels have a hideout somewhere "+
        "on Bazaar Island.",1);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
        "say The Faithful serve the Will of the Gods.",1);
    add_ask(({"master", "Master", "god", "God"}), 
        "say My master is Salilus.", 1);
    add_ask(({"salilus", "Salilus"}),
        "say Salilus is the God of the First Hour.", 1);
    add_ask(({"priest", "anchorite"}),
        "say I am an Anchorite of Salilus, a priest who has dedicated "+
        "his life to serving His Will.", 1);
    add_ask(({"union", "shadow union", "shadow warrior"}), 
        VBFC_ME("union_ask"));
    add_ask(({"dej-minha"}), 
        "say They are the Hegemon's. They answer only to him. "+
        "I would not cross the dej-minha, were I you.", 1);

    set_default_answer(VBFC_ME("what_me"));

}

public void
equip_me()
{
    seteuid(getuid());

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_CC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(this_object(), 1);
    command("wear all");
}

public void 
attacked_by(object ob)
{
    ::attacked_by(ob);
    set_alarm(2.0, 0.0 , &command("shout You DARE attack ME?!"));
}

/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
int 
query_not_attack_me(object who, int aid)
{
     /* This will block any and all attacks */
     who->catch_msg(QCTNAME(this_object()) +" is somehow immune to "+
         "your attack.\n");
     command("emote seems to be quite pleased with himself.");
     return 1;
}

void
do_sequence(string *seq)
{
    if (sizeof(seq) > 1)
        set_alarm(3.0, 0.0, &do_sequence(seq - ({ seq[0] })));

    command(seq[0]);
}

static void
destruct_coin(void)
{
    if (objectp(present("_sybarun_coin", this_object())))
        present("sybarun_coin", this_object())->remove_object();
}

void 
open_sez_me(object player)
{
        player->move_living("east", CITY +"public/courtyard", 1,0);
}

void
enter_inv(object to, object from)
{
    if (!to->id("_sybarun_token") && interactive(from))
    {
        set_alarm(1.0, 0.0, &command("eyebrow"));
	  set_alarm(3.0, 0.0, &command("drop "+to->query_name()));
	  ::enter_inv(to, from);
	  return;
    }

    ::enter_inv(to, from);

    if (!interactive(from))
	return;

    if (IS_INFIDEL(this_player()))
    {
        command("growl");
        command("say You have one of these, yet you are marked by "+
            "Plalgus? Did you think you could get by me??");
        command("shout Guards! We've an infidel on the loose!");
        return;
    }

    if (!NO_SYB_COIN)
    {
        set_alarm(3.0, 0.0, &do_sequence(({
                 "emote subtly smells the sybarun coin.",
                 "say How fortunate you are, to have such a token "+
                 "of approval.",
                 "emote pronounces a string of words and places "+
                 "his hand against the granite slab of the gate.",
                 "emote smiles at the hole that has suddenly appeared "+
                 "in the solid stone",
                 "emote waves his hand and the opening closes." 
                 })));
        set_alarm(15.0, 0.0, &open_sez_me(from));
    }
    
    set_alarm(2.0, 0.0, &destruct_coin());
}

/* default answer to questions */
string
what_me()
{

    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say My God speaks to me in another voice. "+
           "What trickery are you about, that you would ask "+
           "me questions when I cannot see whom I would asnwer?");        
        return "";
    }

    if (IS_INFIDEL(this_player()))
    {
        command("spit");
        command("say You dare to address me, you filthy infidel?");
        return "";
    }


    switch(random(5))
    {
        case 0:
        { 
            command("laugh .");
            command("say You can't really be expecting me to answer that!");
            break;        
        }
        case 1:
        {
            command("say I would not presume to offer an opinion on that.");
            command("smile tight");
            break;
        }
        case 2:
            command("say I am not the person to ask that of. I am but "+
            "a humble priest, a servant of Salilus.");
            break;
        case 3:
        {
            command("say It is the questions in life that motivate us. "+
               "Do you really want an answer to that?");
            command("frown");
            break;
        }
       case 4:
       {
           command("say Knowledge is Power. Why should I empower you?");
           command("wave air");
           break;
       }
    }
    return "";    
}

string
union_ask()
{
    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }
    if (IS_SYBARITE(this_player()))
    {
        command("whisper to "+ this_player()->query_real_name() +
            " I know nothing of your kind save what is known to all:");
    }
    command("say It is a Union of Shadow Warriors, bound to serve "+
        "Jazur and protect the interests of Sybarus.");
    return "";
}


/*
 *   Code relating to quests
 */
string
give_task()
{

    command("say That which I need done cannot be achieved by another.");
    command("say Ask again later, and perhaps I will have "+
        "need of you then.");
    return "";
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

    if (!present(tp, environment(this_object())))
        return;

    if (IS_INFIDEL(tp))
    {
        command("shout Guards! We have an infidel amongst us!");
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
            command("say to "+ tp->query_real_name() +" I have "+
                "heard mention of your exploits.");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i > 4)
            command("say to "+ tp->query_real_name() +
                " Are you on the roster for the Ziggurat today?");
        return;
    }       
    else
    {
        if (i > 5)
           command("say Celebrate the Source, Outlander.");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (CAN_SEE(this_object(), this_player()))
    {
        set_alarm(2.0, 0.0, &check_meet(this_player()));
        return;
    }
}  
