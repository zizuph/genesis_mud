//-*-C++-*-
// file name:      /d/Avenir/common/city/mon/dej-minha3.c
// creator(s):     Lilith May-June 2003
// last update:    Lilith 04 Sept 2003 fixed bug with special attack.
//                 Lilith Oct 2021: moved crozier and bruising boots
//                  and set up a separate unarmed dej, dej5.
// purpose:	       A member of the Hegemon's Honour Guard. 
//                 Sparring dej-minha. The only ones who fight.
//                 She clones the khopesh. She is meant to be a
//                 challenge to any-level player that fights her.
//                 An attempt has been made to scale her so that 
//                 smaller players do not find her impossible to
//                 defeat.
// note:           Based upon Jadestone Doll and the Shadow elves 
//                 from the holm.
// bug(s):
// to-do:
#pragma strict_types

inherit "/lib/unique";

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/defeat";
inherit "/d/Avenir/inherit/emote_hook";
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

#define KILL_FILE	"/d/Avenir/log/deaths/dej"
#define DEBUG   1

int alarm_id, been_attacked, last_start_fight = time(), last_hit, who, me, o_stat;
object pouch, sw1, sw2, knife;
string attrib, eyes, hair, desc;

/* Function prototypes */
string my_long();
void drop_unwanted(object what, object who);
void react_spar(object actor, string adverb);

string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_desc()   {    return desc;      }
int    query_who()    {    return me;        }

void set_eyes(string str)   {    eyes = str;      }
void set_desc(string str)   {    desc = str;      }
void set_who(int who)       {    me = who;        }
void set_hair(string str)   {    hair = str;      } 



/* This array of arrays could also have been done as a mapping */
mixed *everyone = ({
    ({ "Bloodstone Butterfly", "relaxed",
       "intense, chameleon grey", "spun-gold",
       "First Maiden of the Black Flower", ({"bloodstone", "butterfly"}), }),

    ({ "Harmonious Wasp", "tranquil", 
       "aloof, hazel", "wheat-coloured",
       "Second Maiden of the Black Flower", ({"harmonious", "wasp"}), }),

    ({ "Incandescent Breeze", "slender", 
       "observant, pale-green", "light brown", 
       "Second Maiden of the Pearl", ({"incandescent", "breeze"}), }),

    ({ "Dragonflower Vase", "numinous", "predatory, reddish-brown", 
       "reddish-brown", "Mistress of the Pearl", 
       ({"dragonflower", "vase", "dragon", "flower"}), }),
   
    ({ "Fatal Flechette", "willowy",
       "eager, bright blue", "glossy black",
       "Second Maiden of the Thorn", ({"fatal", "flechette"}), }),
 
    ({ "Alabaster Wand", "implacable", 
       "uncompromising, hazel-green", "white-blond",
       "Mistress of the Thorn", ({"alabaster", "wand"}), }),

    ({ "Crystal Starling", "patrician",
       "profound, pale grey", "greying",
       "Mistress of the Thorn", ({"crystal", "starling"}), }),

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

    default_config_npc(random(20) + 130);

    /* She is cunning, lets make sure others know it */
    set_stat_extra(SS_INT, 100);
    set_knight_prestige(0);

    /* same as Jadestone Doll */
    set_skill(SS_DEFENCE, 95);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_AWARENESS, 150);
    set_skill(SS_WEP_KNIFE, 99);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 85);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_ACROBAT, 100);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(CONT_I_HEIGHT, 210);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop("_live_m_attack_thief", "thief_fun");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_leftover("/d/Avenir/inherit/leftover", "trefoil tattoo",1, "", 0,0);
    add_item(({"chest", "breast", "tattoo", "trefoil tattoo", 
        "tattoo on dej-minha"}), "An irridescent ink has "+
        "been used to create a tattoo in the shape of a trefoil. It is "+
        "located on the upper-left side of her chest, over her heart.\n");
    add_item(({"hair", "braid", "braids", "twin braids", "hairstyle", 
        "hair on dej-minha", "hair on the dej-minha"}),
        "The hair on the sides of her head is braided close to the "+
        "scalp, directing the flow of hair down her back and out of "+
        "her way. This hairstyle is very attractive and enhances her "+
        "natural beauty.\n");
    set_act_time(2);
     add_act("@@sheathe_it@@");
     add_act("emote tilts her head back and looks up at the Source.");
     add_act("emote makes a practice lunge.");
     add_act("emote traces the tattoo on her chest.");
     add_act("emote tugs at one of her braids.");
     add_act("emote runs through a short series of combat moves.");
     add_act("emote bends at the waist and clasps her arms behind her "+
         "knees to get a good stretch.");   
     add_act("emote does ten quick push-ups.");
    set_chat_time(5);
     add_chat("Celebrate the Source. The Gods are smiling upon us "+
         "today.");
     add_chat("Almost time for my shift.");
     add_chat("I seem to have run out of sparring partners.");
     add_chat("I need a more challenging partner for sparring "+
         "than that bloated cha'gorta the Hegemon paired me with.");


  set_cact_time(1);
      add_cact("glare mercilessly enemy");
      add_cact("emote screams in rage!");
      add_cact("emote seems to be singing quietly to herself.");
      add_cact("get all from corpse");  
      add_cact("kill enemy");

    add_ask(({"bath", "melchior's bath"}),
        "say I was just there. I had to leave because it will be "+
        "my turn at the Gate soon.",1);
    add_ask(({"name", "your name", "house"}), 
        "say When I became dej-minha I renounced my name and my House, "+
        "that I would not have conflicting loyalties.", 1); 
    add_ask(({"title", "your title", "about title", "lash"}),
        "say My title reflects my status within the dej-minha. "+
        "I could tell you more, but those words would be the last "+
        "you would ever hear.\n", 1); 
    add_ask(({"task", "job", "quest", "help"}), VBFC_ME("give_task"));
    add_ask(({"infidel hideout", "hideout"}),
        "say I believe Jadestone Doll is looking for it. "+
        "Why don't you ask her about it?", 1);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
        "say The Faithful serve the Will of the Gods.",1);
    add_ask(({"master", "Master"}), "say My master is the Hegemon.", 1);
    add_ask(({"jazur"}), VBFC_ME("jazur_ask"));
    add_ask(({"union","shadow union","shadow warrior"}), VBFC_ME("union_ask"));
    add_ask(({"dej-minha"}), VBFC_ME("past_ask"));
    add_ask(({"lord high inquisitor", "inquisitor", "high inquisitor"}),
        VBFC_ME("inquis_ask"));
    add_ask(({"spar", "to spar", "sparring", "partner", "sparring partner",
        "about sparring", "challenge"}), VBFC_ME("spar_me"));
    add_ask(({"cha'gorta"}), 
        "say It is someone who talks too much. Depending "+
        "on context, it can be a gossip, a braggart, or a fool.", 1);

    set_default_answer(VBFC_ME("what_me"));

    add_emote_hook("spar", 1.0, react_spar);

    set_restrain_path("/d/Avenir/common/city/");
    set_monster_home("/d/Avenir/common/city/entry/e1");
    set_exp_factor(150); /* because she is so hard to kill  */
 
}

void
equip_me()
{
     seteuid(getuid());

    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_PC(5 + random(5))->move(this_object());

    sw1 = clone_unique((CITY +"obj/wep/khopesh"), 7, 
            (CITY +"obj/wep/d2ndsword"), 1, 33);
    sw1->move(this_object());
    sw2 = clone_object(CITY +"obj/wep/d2ndsword");
    sw2->move(this_object());
    clone_object(CITY +"obj/worn/buskins")->move(this_object());
    clone_object(CITY +"obj/worn/filibeg")->move(this_object());
    clone_object(CITY +"obj/worn/harness")->move(this_object());
    clone_object(CITY +"obj/worn/stocking")->move(this_object());
    clone_object(BAZAAR +"infidel/obj/phial")->move(this_object());
 
    command("wear all");

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
         "Her long "+ query_hair()+ " hair, free of any constraint save "+
         "twin braids at her temples, brushes against her waist.\n"+
         "Her "+ query_eyes() +" eyes are framed by high cheekbones "+
         "which compete for prominence with her pointed chin.\n"+
         "Upon her breast glitters a trefoil tattoo.\n"+
         "She seems to glow with confidence and power.\n"+
         "She has about her an alert, combative air.\n";
    return str;

}


/*
 * Function name:   reconfig_me()
 * Description:     This function scales npc based on size of enemy
 * Arguments:       ob - attacker
 * Notes:           called through attacked_by or spar_me
 */
void
reconfig_me(object ob)
{
    int s, t;

    /* Lets try to stop resets in combat. */
    if (this_object()->query_hp() < this_object()->query_max_hp())
        return;

    /* Scale dej to opponent */
    s = ob->query_average_stat();
    o_stat = s;


    switch (s)
    {
        case 15..74:    t = (s / 6); break; /* 16% larger */
        case 75..144:   t = (s / 5); break; /* 20% larger */
        case 145..184:  t = (s / 4); break; /* 25% larger */
        case 185..500:  t = (s / 3); break; /* 33% larger */       
        default:        t = (s / 6); 
    }   

    default_config_npc(t + s);
    refresh_living();      

}

void
react_spar(object actor, string adverb)
{
    reconfig_me(actor);
    command("say Certainly, a sparring match sounds like just the thing.");
    command("spar "+ actor->query_real_name());     
    command("kill "+  actor->query_real_name());   
}

/* response to questions */
string
spar_me()
{

    if (!CAN_SEE(this_object(), this_player()))
    {
        command("say I do not answer those whom I cannot see.");        
        return "";
    }

    switch(random(4))
    {
        case 0:
        { 
            command("say Are you offering to be my next sparring "+
                "partner?");
            command("emote changes her posture to a more defensive "+
                "stance.");
            command("say Wonderful! I'll give you the advantage. "+
                "You may attack first.");
            command("spar " + this_player()->query_real_name());

            break;        
        }
        case 1:
        {
            command("say Do you really think you are capable of "+
                "sparring with me? I wouldn't want to kill you "+
                "accidentally.");
            command("smile disdain");
            break;
        }
        case 2:
        {
            command("emote smiles mirthlessly, with a look in her eyes "+
               "that sends a shiver down your spine.");
            command("spar " + this_player()->query_real_name());
            command("kill " + this_player()->query_real_name());
            break;
        }
        case 3:
        {
            command("say Excellent! I've just enough time before "+
            "my shift.");
            command("spar " + this_player()->query_real_name());
            command("say Ready?");
            command("kill " + this_player()->query_real_name());
            break;
        }
    }

    if (!objectp(query_attack()))
        reconfig_me(this_player());

    if (!been_attacked)
        reconfig_me(this_player());

    if (DEBUG)
    {
        SCROLLING_LOG(KILL_FILE, "Dej3 challenged by: " 
            + TP->query_name() +" ("+ TP->query_average_stat() +") "
            + "Dej ("+ TO->query_average_stat() +")");
    }
    return "";    
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
sheathe_it()
{
    if (sw1->query_wielded() != 0 && (!objectp(query_attack())))
    {
        been_attacked = 0;
        // reset her to 'normal'
        remove_prop(LIVE_I_QUICKNESS);
        default_config_npc(random(20) + 100);
        refresh_living();
        command("unwield all");
        command("fill harness");
    }
    if (sw1->query_held() != 0 && (!objectp(query_attack())))
    {
        been_attacked = 0;
        // reset her to 'normal'
        remove_prop(LIVE_I_QUICKNESS);
        default_config_npc(random(20) + 100);
        refresh_living();
        command("release all");
    }
}

void
thief_fun(object thief, object victim, object ob)
{
    been_attacked = 1;
    if (thief->query_prop(OBJ_I_INVIS))
        set_alarm(1.5, 0.0, &command("say Hiding will not spare you."));
    set_alarm(1.4, 0.0, &command("wield all"));
    set_alarm(1.4, 0.0, &command("hold all"));
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

    command("say At this time the only way that you could "+
        "possibly be of use to me is as a sparring partner.");
    command("smile challeng");
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

void 
drop_unwanted(object what, object who)
{
    command("peer "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
        +who->query_real_name()))
        what->remove_object();  
    return;
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
        command("hold all");
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


/* Add some magical resistance to even the playing field */
varargs mixed 
query_magic_protection(string prop, object what)
{
    if (what == this_object())
    {
        if (prop == MAGIC_I_RES_MAGIC)
        {
            tell_room(ENV(TO), QCTNAME(TO)+"'s spiral tattoo pulses "+
                "with irridescent light.\n", what);
            return ({ 25, 1});
        }
        if (prop == MAGIC_I_RES_POISON)
        {
            tell_room(ENV(TO), QCTNAME(TO)+"'s spiral tattoo pulses "+
                "with irridescent light.\n", what);
            return ({ 25, 1});
        }

    }
 
    return ::query_magic_protection(prop, what);
}


/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
    int s, t;

    ::attacked_by(ob);

    if (!been_attacked)
    {
        been_attacked = 1;
        set_alarm (0.5, 0.0, "command", "say Aliecis arus.");
        set_alarm (1.0, 0.0, "command", "empty harness");
        set_alarm (1.3, 0.0, "command", "coat longsword");
        set_alarm (1.5, 0.0, "command", "wield khopesh");
        set_alarm (2.0, 0.0, "command", "wield longswords");
        reconfig_me(ob);
    }
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

    if (query_hp() > 100)
        return 0;

    if (!killer)
        killer = previous_object();

    heal_hp(-100);
    command("emote glowers darkly.");
    SCROLLING_LOG(KILL_FILE, TO->query_name() +" killed by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));
    // This line is causing problems with call to do_die, so not logging   
    // STATSERV_LOG_EVENT("city", "Dej defeated");
    ::do_die(killer);

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
  
    tell_watcher("Swiftly, "+ short() +" body slams "+ QNAME(victim) + 
        ", who stumbles " + exit + "!\n", this_object(), victim);
  
    victim->catch_msg("You've been hit with a body slam! You stumble "+ 
        exit +"!\n");
  
    /* Move them, make peace with them */
    victim->move_living(exit, dest, 1);
//    TO->stop_fight(victim);
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

    // If we are sparring, I really don't want to kill you.
    if (victim->query_hp() < 500)
    {
        TO->stop_fight(victim);
        victim->stop_fight(TO);
        command("say to "+ victim->query_real_name() +
            " You're no match for me. Go! Nurse your wounds."); 
        return 1;
    }

    if (!sw1->query_wielded() && !sw1->query_held())
    {
        command("empty harness");
        command("wield khopesh");
        command("wield longswords");
        command("hold crozier");
    }

    // If we've got a team and the smallest one challenged her, reset.
    if (victim->query_average_stat() > o_stat)
        reconfig_me(victim);
    
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

    /* Scale attacks to opponent size, to be fair */
    s = victim->query_average_stat();
    switch (s)
    {
        case 15..75:    sInt = 2;  break;
        case 76..109:   sInt = 3;  break;
        case 110..130:  sInt = 4;  break;
        case 131..155:  sInt = 5;  break;
        case 156..180:  sInt = 7;  break;
        case 181..500:  sInt = 10;  break;
        default:        sInt = 2; 
    }   

    /* Most of these specials are in sybarite.c */
    switch (random(sInt))
    {
        case 0: command("emote seems to be holding back on her attacks.");
            if (sInt > 4)              
                command("smash");                
            return 1;
        case 2: command("emote seems to be holding back on her attacks.");
            return 0;        
        case 3: command("emote lunges for a perfect opening, but pulls "+
                "back at the last moment.");
        return 0;
        case 4: 
            if (sw1 && sw1->query_wielded())
            {
                command("pommel");
            }
            else
            {
                command("skick");
            }
            return 0;
        case 5: command("emote seems to be holding back on her attacks.");
            return 0;                 
        case 7: command("skick");
            return 1;
        case 8: command("emote seems to be holding back on her attacks. How insulting!");
            return 0;                 
        case 9: 
            if (sw1 && sw1->query_wielded())
            {
                command("pommel");
            }
            else
            {
                command("skick");
            }
            return 0;
        default: 
    }
    return 0;
}




void
init_living()
{

    if (query_attack())
        set_alarm(1.0, 0.0, &command("skick"));            

    /* If the living is a player and I can see him ... */
    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        /* Only one person, so as not to spam a team */
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
        if (!objectp(query_attack()))
            reconfig_me(TP);
        return;
    }
}  

