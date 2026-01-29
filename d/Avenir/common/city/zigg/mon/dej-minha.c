//-*-C++-*-
// file name:      /d/Avenir/common/city/zigg/mon/dej-minha.c
// creator(s):     Lilith May 2002
// last update:    Lucius, May 2007 - Guard for the Ziggurat.
// purpose:	       A member of the Hegemon's Honour Guard. 
//                 Placed in the Ziggurat. No combat for her.
// note:           Based upon Jadestone Doll and the Shadow elves 
//                 from the holm.
// bug(s):
// to-do:		Not killable while she is on duty.
#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/defeat";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/logrotate";

#include "zigg.h"
#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

/* Function prototypes */
public string my_long(void);
private void drop_unwanted(object what, object who);

private static int alarm;


/* This array of arrays could also have been done as a mapping */
mixed *everyone = ({
    ({
	"Feral Hunger", "tense", 
	"alert, honey brown", "blue-black", 
	"Mistress of the Talon", ({"feral", "hunger"}),
    }), ({
	"Onyx Claw", "finely-toned",
	"coal black", "shimmering black",
	"First Maiden of the Talon", ({"onyx", "claw"}),
    }), ({
	"Scathing Calm", "languid",
	"sleepy green", "platinum blond", 
	"Second Maiden of the Talon", ({"scathing", "calm"}),
    }),
});

string attrib, eyes, hair, desc;
int who, me;

string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_desc()   {    return desc;      }
int    query_who()    {    return me;        }

void set_eyes(string str)   {    eyes = str;      }
void set_desc(string str)   {    desc = str;      }
void set_who(int who)       {    me = who;        }
void set_hair(string str)   {    hair = str;      } 

/* 
 * set_morph sets the various attributes of the npc (from the *everyone 
 * array), making it unique . We can use this to 
 * set which npc we want or let it generate them randomly.
 */
void
set_morph(int who)
{
    mixed someone;

    if (who < 0 || who >= sizeof(everyone))
       who = (random(sizeof(everyone)));

    someone = everyone[who];
    set_living_name(someone[0]);
    set_name(someone[0]);
    add_name(someone[5]);
    set_adj(({"bare-breasted", someone[1] }));
    add_adj(({ someone[5] }));
    set_desc(someone[1]);    
    set_eyes(someone[2]);
    set_hair(someone[3]);
    set_title(someone[4]);
    set_who(who);
}

/* Create the npc */
public void
create_monster(void)
{
    /* If I'm not a clone, don't bother with the rest */
    if (!IS_CLONE)
        return;

    setuid();
    seteuid(getuid());

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();

    /* Set my identity */
    set_morph(random(sizeof(everyone)));

    set_race_name("half-elf");
    add_name(({"shadow elf", "dej-minha", "dej", "minha"}));
    add_adj("bare-breasted");
    set_gender(G_FEMALE);
    set_long(my_long);
    set_appearance_offset(0);

    default_config_npc(random(50) + 140);
    set_knight_prestige(0);

    /* same as Jadestone Doll */
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_WEP_KNIFE, 99);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 85);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_SEE_INVIS, 1 + random(10));
    add_prop(CONT_I_HEIGHT, 210);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop("_live_m_attack_thief", "thief_fun");
    add_prop(LIVE_I_QUICKNESS, 125);
    add_prop(LIVE_I_SEE_INVIS, 50);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(OBJ_M_NO_ATTACK, 
        "The Gods of Sybarus protect those who serve.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 
        "The Gods of Sybarus protect those who serve.\n");

    add_leftover("/d/Avenir/inherit/leftover", "trefoil tattoo",1, "", 0,0);
    add_item(({"tattoo", "trefoil tattoo"}), "An irridescent ink has "+
        "been used to create a tattoo in the shape of a trefoil. It is "+
        "located on the upper-left side of her chest, over her heart.\n");
    add_item(({"hair", "braid", "braids", "twin braids", "hairstyle", 
        "hair on dej-minha", "hair on the dej-minha"}),
        "The hair on the sides of her head is braided close to the "+
        "scalp, directing the flow of hair down her back and out of "+
        "her way. This hairstyle is very attractive and enhances her "+
        "natural beauty.\n");

     set_act_time(20);
     add_act("sigh .");
     add_act("emote smiles with her lips but not her eyes.");
     add_act("stretch");
     add_act("say Celebrate the Source.");
     add_act("emote absentmindedly traces the tattoo on her "+
         "chest.");
     add_act("emote tugs at one of her braids.");

    add_ask(({"bath", "melchior's bath"}),
        "say There is a bathhouse near the First Gate. I look "+
	"forwards to a good soak after my shift.", 1);
    add_ask(({"sybarus","bazaar"}),
        "say It is over the bridge.", 1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}), 
        "say You have already gained entrance, use your feet and "+
	"explore should you wish to discover more.", 1);
    add_ask(({"name", "your name", "house"}), 
        "say When I became dej-minha I renounced my name and my House, "+
        "that I would not have conflicting loyalties.", 1); 
    add_ask(({"task", "job", "quest", "help"}), VBFC_ME("give_task"));
    add_ask(({"infidel", "infidels"}),
        "say The wretched Infidels have a hideout somewhere "+
        "on Bazaar Island.",1);
    add_ask(({"infidel hideout", "hideout"}),
        "say I believe Jadestone Doll is looking for it. "+
        "Why don't you ask her about it?", 1);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
        "say The Faithful serve the Will of the Gods.",1);
    add_ask(({"ziggurat", "Ziggurat", "pleasure palace"}),
        "say Thanks to the Hegemon's munificence you are free to explore "+
        "to this point, but to get by me you will need a sigil.",1);        
    add_ask(({"lord high inquisitor", "inquisitor", "high inquisitor"}),
        VBFC_ME("inquis_ask"));
    add_ask(({"master", "Master"}), "say My master is the Hegemon.", 1);
    add_ask(({"jazur"}), VBFC_ME("jazur_ask"));
    add_ask(({"union","shadow union","shadow warrior"}), VBFC_ME("union_ask"));
    add_ask(({"dej-minha"}), VBFC_ME("past_ask"));
    add_ask("nochipa", "say She is an infidel priest of Alphum.", 1);

    set_default_answer(VBFC_ME("what_me"));
}

public void
equip_me(void)
{
     clone_object(CITY +"obj/worn/buskins")->move(this_object());
     clone_object(CITY +"obj/worn/filibeg")->move(this_object());
     clone_object(CITY +"obj/worn/harness")->move(this_object());
     clone_object(CITY +"obj/wep/d2ndsword")->move(this_object());

     command("wear all");
     set_alarm(1.0, 0.0, &command("fill harness"));
}

public string
my_long(void)
{
    string str = "She is a bare-breasted "+ query_desc() +" "+
	query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is a bare-breasted "+ query_desc() 
            + " "+ query_race_name() +", presenting herself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " the "+ query_title() +",";
        str += " "+ query_exp_title() +", female "+ query_race_name() +".\n";
    }

    str += "She has the physical grace characteristic of shadow elves, "+
         "with the sturdier build of a human, revealing her half-elven "+
         "heritage.\n"+
         "Her skin is so pale as to be translucent, its whiteness tinted "+
         "blue in some places by her veins.\n"+
         "Her long "+ query_hair()+ " hair, free of any constraint save twin "+
         "braids at her temples, brushes against her waist.\n"+
         "Her "+ query_eyes() +" eyes are framed by high cheekbones "+
         "which compete for prominence with her pointed chin.\n"+
         "Upon her breast glitters a trefoil tattoo.\n"+
         "She seems to glow with confidence and power.\n"+
         "She has about her an alert, combative air.\n";

    return str;
}

public string
inquis_ask(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }

    command("emote smiles mirthlessly, with a look in her eyes "+
        "that sends a shiver down your spine.");
    return "";
}

public string
union_ask(void)
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
        "Jazur and protect the interests of Sybarus.");
    command("say Had I not been called to serve as dej-minha, "+
        "I would probably have tried to become One with them.");
    return "";
}

public string
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

public string
past_ask(void)
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
        "the City.");
    command("smile proud");
    return "";
}

public string
what_me(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       query_name() +" about: "+ query_question() +".\n");
#endif

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
            command("emote smiles mirthlessly, with a look in her eyes "+
               "that sends a shiver down your spine.");
            break;
        case 3:
        {
            command("say Enough questions! I'm on duty!");
            command("say Move along.");	
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
    if (thief->query_prop(OBJ_I_INVIS))
        set_alarm(1.5, 0.0, &command("say Hiding will not spare you."));

    set_alarm(1.4, 0.0, &command("wield all"));
    set_alarm(1.0, 0.0, &command("emote screams in rage!"));
    set_alarm(1.8, 0.0, &command("kill " + OB_NAME(thief)));
}

public string 
query_exp_title(void)
{
    return "sybarite";
}

/*
 *   Code relating to quests
 */
public string
give_task(void)
{

    command("say You are of no use to me.");
    command("say Begone!");
    return "";
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
        return;

    set_alarm(2.0, 0.0, &drop_unwanted(obj, from));
}

private void 
drop_unwanted(object what, object who)
{
    command("peer "+ who->query_real_name());
    if (!command("give "+what->query_name()+" to " + who->query_real_name()))
	what->remove_object();
}

/*
 * Masked:        Don't annoy her
 */
private static string *offensive = ({
	"kiss", "tickle", "nuzzle", "pat", "squeeze", "lick",
	"french", "finger", "bite", "fondle", "cuddle", "caress",
	"flirt", "grope", "hold", "hug", "nibble", "pinch",
	"pat", "spank", "slap", "snuggle",
});

public varargs void
emote_hook(string emote, object actor, string adverb, object *oblist,
           int attr, int target)
{
    if (!query_interactive(actor))
        return;

    if (attr & ACTION_OFFENSIVE)
	return;

    if (IN_ARRAY(emote, offensive))
        return;

    if (attr & ACTION_THREATENING)
	set_alarm(1.0, 0.0, &command("peer disapprov "+ OB_NAME(actor)));
    else if (!random(3))
	set_alarm(1.0, 0.0, &command(one_of_list(({"rolleyes","frown"}))));
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
private void
check_meet(object tp)
{

    alarm = 0;

    if (!present(tp, environment(TO)))
        return;

    if (IS_INFIDEL(tp))
    {
        command("shout How did you get in here, you Infidel scum?!");
        return;
    }

    int i = random(15);

    if (IS_UNION(tp))
    {
        if (i == 0)           
            command("say to "+ OB_NAME(tp) +" Celebrate "+
                "the Source!");
	else if (i == 2)
            command("greet "+ OB_NAME(tp));
	else if (i == 5)
            command("say to "+ OB_NAME(tp) +" I have "+
                "heard mention of your exploits.");
        return;
    }

    if (tp->query_prop(DANCER))
    {
        if (i == 1)
            command("smile puzzle "+ OB_NAME(tp));
	else if (i == 4)
            command("say to "+ OB_NAME(tp) +
                " You'll need a sigil before I can let you pass "+
		"to the dance parlour.");
    }       
    else
    {
        if (i < 4)
           command("say Only those with a valid sigil may yet "+
	       "pass further.");
	else if (i > 9)
           command("say to "+ OB_NAME(tp) +" Celebrate the Source!");
    }
}

public void
init_living(void)
{
    ::init_living();

    if (!alarm && CAN_SEE(TO, TP))
        alarm = set_alarm(2.0, 0.0, &check_meet(TP));
}  

/*
 *  None of this should be necessary, but just in case a mortal gets
 *  creative and somehow starts combat with her....
 *
 */
// Defeated, not dead, per /d/Avenir/inherit/defeat.c
public void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    command("say You have bested me this time, fairly or not, "+
        "so you shall have that which you sought.");
    command("drop all");
    command("emote walks away.");

    ::do_die(killer);
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("empty harness");
    command("wield swords");
}

/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 *                  If fail, the cause must produce explanatory text himself.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
public int 
query_not_attack_me(object who, int aid)
{
     object *enemies;

     /* This will block any and all attacks */
     who->catch_msg(QCTNAME(this_object()) +" is immune to your attack.\n");
     command("say At this time, in this place, there will be peace.");
     command("say If you are looking for a sparring match, try the arena.");
     enemies = this_object()->query_enemy(-1);
     who->stop_fight(enemies);
     enemies->stop_fight(this_object());

     return 1;
}
