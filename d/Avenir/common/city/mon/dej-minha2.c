//-*-C++-*-
// file name:      /d/Avenir/common/city/mon/dej-minha.c
// creator(s):     Lilith May 2002
// last update:    
// purpose:	       A member of the Hegemon's Honour Guard. 
//                 guards the First gate, inside.
// note:           Based upon Jadestone Doll and the Shadow elves 
//                 from the holm.
// bug(s):
// to-do:		Not willing to fight while she is on duty.

#pragma strict_types

inherit "/lib/unique";

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/defeat";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";

#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/common/city/city.h"

#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

# define KILL_FILE	"/d/Avenir/log/deaths/dej"

/* Function prototypes */
string my_long();
void drop_unwanted(object what, object who);

int alarm_id, been_attacked, last_start_fight = time(), last_hit;
object pouch, sw1, sw2, knife;


/* This array of arrays could also have been done as a mapping */
mixed *everyone = ({
    ({ "Laughing Knives", "angular", 
       "dancing, steel-grey", "soot-black", 
       "First Maiden of the Thorn", ({"laughing", "knives"}), }),

    ({ "Luscious Chains", "aloof", 
       "luminous grey", "silvery-blonde", 
       "Second Maiden of the Thorn", ({"luscious", "chains"}), }),
  
    ({ "Gossamer Wing", "statuesque", 
       "pensive black", "curly brown", 
       "Second Maiden of the Lash", ({"gossamer", "wing"}), }),

    ({ "Topaz Fang", "glorious", 
       "feral yellow", "black", 
       "Mistress of the Black Flower", ({"topaz", "fang"}), }),

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
void
create_monster()
{
    /* If I'm not a clone, don't bother with the rest */
    if (!IS_CLONE)
        return;

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

    default_config_npc(random(50) + 120);

    set_knight_prestige(0);

    /* same as Jadestone Doll */

    set_skill(SS_DEFENCE, 95);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_AWARENESS, 92);
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
    add_prop(OBJ_M_NO_MAGIC_ATTACK, 
        "The Gods of Sybarus protect those who serve.\n");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

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
     set_act_time(4);
     add_act("emote tilts her head back and looks up at the Source.");
     add_act("sigh .");
     add_act("emote smiles mirthlessly, with a look in her eyes "+
        "that sends a shiver down your spine.");
     add_act("emote seems to be looking everywhere at once.");
     add_act("say My relief should be here soon. I'm looking "+
         "forward to a long hot bath.");
     add_act("smile reminisc");
     add_act("say Celebrate the Source.");
     add_act("emote absentmindedly traces the tattoo on her "+
         "chest.");
     add_act("emote tugs at one of her braids.");
     add_act("emote flicks her glorious hair back over her "+
         "shoulder.");

  set_cact_time(1);
      add_cact("glare mercilessly enemy");
      add_cact("coat longsword");
      add_cact("emote screams in rage!");
      add_cact("emote seems to be singing quietly to herself.");

    add_ask(({"bath", "melchior's bath"}),
        "say There is a bathhouse nearby. I'll be joining "+
        "Eldritch Thistle there as soon as my watch is over.",1);
    add_ask(({"sybarus","bazaar"}),
        "say It is over the bridge.",1);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}), 
        "say You have set foot upon the beginning of the path "+
        "to the City", 1);
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
    add_ask(({"lord high inquisitor", "inquisitor", "high inquisitor"}),
        VBFC_ME("inquis_ask"));
    add_ask(({"master", "Master"}), "say My master is the Hegemon.", 1);
    add_ask(({"jazur"}), VBFC_ME("jazur_ask"));
    add_ask(({"union","shadow union","shadow warrior"}), VBFC_ME("union_ask"));
    add_ask(({"dej-minha"}), VBFC_ME("past_ask"));
    add_ask(({"galerin", "galerin icu ra'let"}),
        "say He is none of your business", 1);
    add_ask("nochipa", "say She is an infidel priest of Alphum.", 1);
    add_ask(({"disk", "thin brass disk"}), "say It is a mystery to me.", 1);

    set_default_answer(VBFC_ME("what_me"));

    set_restrain_path("/d/Avenir/common/city/");
//  set_monster_home("/d/Avenir/common/city/");
    set_exp_factor(125); /* because she is so hard to kill  */
 
}

void
equip_me()
{
     seteuid(getuid());

     MONEY_MAKE_SC(random(25))->move(this_object());
     MONEY_MAKE_PC(1)->move(this_object());

     sw2 = clone_object(CITY +"obj/wep/d2ndsword");
     sw2->move(this_object());

     clone_object(CITY +"obj/worn/buskins")->move(this_object());
     clone_object(CITY +"obj/worn/filibeg")->move(this_object());
     clone_object(CITY +"obj/worn/harness")->move(this_object());
     clone_object(BAZAAR +"infidel/obj/phial")->move(this_object());
     command("wear all");
     command("coat longsword");


     // NB: she does not wield the sword unless attacked.
     pouch = clone_object(BAZAAR+"Obj/misc/gem_pouch.c");
     pouch->move(this_object());
     pouch->fill_pouch();
}

string
my_long()
{
    string  str;

    str = "She is a bare-breasted "+ query_desc() +" "+
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


string
inquis_ask()
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
        "Jazur and protect the interests of Sybarus.");
    command("say Had I not been called to serve as dej-minha, "+
        "I would probably have tried to become One with them.");
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
        "the City.");
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
            command("say Must you pester me with these ridiculous questions?");
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


void
thief_fun(object thief, object victim, object ob)
{
    been_attacked = 1;
    if (thief->query_prop(OBJ_I_INVIS))
        set_alarm(1.5, 0.0, &command("say Hiding will not spare you."));
    set_alarm(1.4, 0.0, &command("wield all"));
    set_alarm(1.0, 0.0, &command("emote screams in rage!"));
    set_alarm(1.8, 0.0, &command("kill " + thief->query_real_name()));
}

string 
query_exp_title()
{
    return "sybarite";
}


/*
 *   Code relating to quests
 */
string
give_task()
{

    command("say At this time I can't think of any way that "+
        "you could possibly be of use to me.");
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
    return;
}

void drop_unwanted(object what, object who)
{
    command("peer "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
        +who->query_real_name()))
        what->remove_object();  
    return;
}


/*
 * Masked:        Don't annoy her
 * Function name: emote_hook
 * Description  : Whenever an emotion is performed on this NPC, or when it
 *                is performed on in the room in general, this function is
 *                called to let the NPC know about the emotion. This way we
 *                can avoid the usage of all those costly triggers.
 * Arguments    : string emote - the name of the emotion performed. This
 *                    always is the command the player typed, query_verb().
 *                object actor - the actor of the emotion.
 *                string adverbs - the adverb used with the emotion, if there
 *                    was one. When an adverb is possible with the emotion,
 *                    this argument is either "" or it will contain the used
 *                    emotion, preceded by a " " (space). This way you can
 *                    use the adverb in your reaction if you please without
 *                    having to parse it further.
 */
public varargs void
emote_hook(string emote, object actor, string adverb = 0)
{
    string *offensive = ({ "kiss", "tickle", "nuzzle", "pat",
              "squeeze", "lick", "french", "finger", "bite", "fondle",
              "cuddle", "caress", "flirt", "grope", "hold",
              "hug", "nibble", "pinch", "pat", "spank", "slap",
              "snuggle" });

    if(member_array(emote, offensive) == -1)
        return;

    if(!interactive(actor))
        return;

    set_alarm(1.0, 0.0, &command(ONEOF(({"smile danger","frown", "snarl","swear","spit"}))));

    if(CAN_SEE(TO, actor))
    {
        set_alarm(3.0, 0.0, &command("say You cannot distract me "+
           "from my duty with your improper behaviour, "
             + actor->query_race_name() + "."));
    }
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

    if (!present(tp, environment(TO)))
        return;

    if (IS_INFIDEL(tp))
    {
        command("empty harness");
        command("wield all");
        command("kill "+ tp->query_real_name());
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
            command("say to "+ tp->query_real_name() +" I have "+
                "heard mention of your exploits.");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i == 1)
            command("smile puzzle "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +
                " Are you on the roster for the Ziggurat today?");
        return;
    }       
    else
    {
        if (i == 1)
           command("say You may pass because you have earned "+
               "a token.  Take care that you behave yourself.");
        if (i == 2)
           command("say Celebrate the Source, Outlander.");
        if (i == 5)
           command("say to "+ tp->query_real_name() +
               " No disturbing the peace, or I'll have you "+
               "strung up by your toes with weights hung from "+
               "your eyelids, so I can douse your eyes with phrynos "+
               "blood and watch you writhe.");
        return;
    }
}

void
init_living()
{
    ::init_living();

    /* If the living is a player and I can see him ... */
    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        /* Only one person, so as not to spam a team */
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }

    /* If the living is a sybarite npc .. */
    if (IS_SYBARITE(TP) && (!interactive(TP)))
    {
        team_join(TP);
        TP->set_leader(TO);
        return;
    }    
}  


/*
 *  None of this should be necessary, but just in case a mortal gets
 *  creative and somehow starts combat with her....
 *
 */
// Defeated, not dead, per /d/Avenir/inherit/defeat.c
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    foos -= ({ killer });
    killers = (foos)->query_name();

    SCROLLING_LOG(KILL_FILE, "Dej-minha "
            + "(" + (present("khopesh") ? "with khopesh" : "without khopesh")
            + "): Killed by " + killer->query_name()
            + "(" + killer->query_average_stat()
            + ") " + (sizeof(killers) ? "with "
            + COMPOSITE_WORDS(killers) : "alone") + " [fight duration: "
            + ((time() - last_start_fight)/60)
            + " min]");

    command("say You have bested me this time, fairly or not, "+
        "so you shall have that which you sought.");
    command("drop all");
    command("emote walks away.");
    STATSERV_LOG_EVENT("city", "Dej-minha defeated");

    ::do_die(killer);
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("empty harness");
    command("wield swords");
    command("coat sword");
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
