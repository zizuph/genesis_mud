//-*-C++-*-
// file name:      /d/Avenir/common/city/mon/dej-minha4.c
// creator(s):     Lilith May 2002
// last update:    
// purpose:	       A member of the Hegemon's Honour Guard. 
//                 Placed in bath house. No combat for her.
// note:           Based upon Jadestone Doll and the Shadow elves 
//                 from the holm.
// bug(s):
// to-do:

#pragma strict_types

inherit "/lib/unique";

inherit "/d/Avenir/inherit/sybarite";
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


/* This array of arrays could also have been done as a mapping */
mixed *everyone = ({
    ({ "Eldritch Thistle", "stunning", 
       "penetrating, bright blue", "black", 
       "First Maiden of the Lash", ({"eldritch", "thistle"}), }),

    ({ "Carnelian Serpent", "sleek",
       "guileless violet", "golden brown",
       "Second Maiden of the Black Flower", ({"carnelian", "serpent"}), }),

    ({ "Radiant Smile", "radiant", 
       "intense, cyan blue", "red-gold", 
       "Mistress of the Pearl", ({"radiant", "smile"}),}),
         
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
 * array), making it unique in different ways. We can use this to 
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

    default_config_npc(random(50) + 140);
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
     add_act("emote tilts her head back and closes her eyes.");
     add_act("sigh content");
     add_act("emote smiles with her lips but not her eyes.");
     add_act("emote inhales deeply of the moist, scented air.");
     add_act("stretch");
     add_act("swim");
     add_act("float");
     add_act("dive");
     add_act("savor kahve");
     add_act("smile languid");
     add_act("emote hums a little tune under her breath.");
     add_act("emote dips a cloth in the water and washes "+
         "her face with it.");
     add_act("emote absentmindedly traces the tattoo on her "+
         "chest.");
     add_act("emote tugs at one of her braids.");

    set_default_answer(VBFC_ME("what_me"));

    set_restrain_path("/d/Avenir/common/city/");
//  set_monster_home("/d/Avenir/common/city/");
 
}

void
equip_me()
{
     seteuid(getuid());

     MONEY_MAKE_SC(random(25))->move(this_object());
     MONEY_MAKE_PC(3)->move(this_object());

     clone_object(CITY +"bath/obj/towel")->move(this_object());
     clone_object(CITY +"bath/obj/soap")->move(this_object());
     clone_object(CITY +"obj/food/iced_coffee")->move(this_object());

     command("wear all");
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
            command("say Can't you see I'm here to enjoy my bath?");
            break;        
        }
        case 1:
        {
            command("say Must you trouble me with such minor concerns "+
                "while I am about my bath?");
            command("smile disdain");
            break;
        }
        case 2:
            command("emote smiles mirthlessly, with a look in her eyes "+
               "that sends a shiver down your spine.");
            break;
        case 3:
        {
            command("say Ask me another question and I will have you "+
                "thrown out!");
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


static 
void tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

void 
heal_me()
{
    heal_hp(random(200) + 200);
    command("emote cries out: Shades of Sybarus, aid me in my "+
                "hour of need!");
    command("emote seems to become stronger.");
}

int 
special_attack(object enemy)
{
    object     me,
              *enemies;
    string     how;
    mixed     *hitres;
    int        damage, 
               swing_type, 
               pen,
               i, 
               con;
    string    *side = ({"left","right"}),
              *part = ({"knee","elbow","fist"}),
              *area = ({"stomach","chest","face"});

    // Cirion, Jan 2, 1998: Also log the amount of time
    // the fight lasted.
    if((last_hit + 500) < time())
        last_start_fight = time();

    last_hit = time();

    me = this_object();

    command("wield all");

    ENV(TO)->being_killed(enemy);

    if(random(4))
      return 0;

    con = query_attack()->query_stat(SS_CON);

    enemies = query_enemy(-1);

    if(sizeof(enemies) > 1)
      for(i=0;i<sizeof(enemies);i++)
      {
         if(present(enemies[i], ENV(TO)) && enemies[i]->query_stat(SS_CON) < con)
         {
           attack_object(enemies[i]);
           con = enemies[i]->query_stat(SS_CON);
         }
      }

    enemy = query_attack();
    pen = random(1500) + 100 - enemy->query_skill(SS_DEFENCE);
    swing_type = random(3);
    hitres = enemy->hit_me(pen, W_BLUDGEON, TO, -1);
    damage = hitres[0];

    how = "bumping";
    if (damage > 7)
        how = "grazing";
    if (damage > 12)         
        how = "hurting";
    if (damage > 25)
        how = "bashing";
    if (damage > 40)
        how = "smashing";
    if (damage > 60)
        how = "crushing";

    enemy->catch_msg(QCTNAME(me) + " swings her "
                  + side[random(2)] + " "
                  + part[swing_type] +" at you with great "
                 + "force, " + how + " your "
                  + area[swing_type]+".\n");
 
    /* Cirion: I am using query_combat_object()->tell_watcher(),   */
    /*         even through this should be define for livings. For */
    /*         some reason, it does not seem to be defined by her. */
    /*         I don't have time to fix it, so I will just patch   */
    /*         it.                                                 */
    query_combat_object()->tell_watcher(QCTNAME(me) + " swings her "
                  + side[random(2)] + " "
                  + part[swing_type] + " at "
                  + QTNAME(enemy) + " with great "
                  + "force, " + how
                  + " " + enemy->query_possessive()+ " "
                  + area[swing_type]+".\n", enemy);

    if(enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
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

    set_alarm(1.0, 0.0, &command(ONEOF(({"rolleyes","frown",}))));

    if(CAN_SEE(TO, actor))
    {
        set_alarm(3.0, 0.0, &command("say Get a room, you silly "+
            actor->query_race_name() + "."));
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
        command("shout How did you get in here, you Infidel scum?!");
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
            command("say to "+ tp->query_real_name() +" Care to "+
                "join me for a nice, quiet bath?");
        return;
    }
    if (tp->query_prop("_live_i_am_dancer_of_veils"))
    {
        if (i == 1)
            command("smile warm "+ tp->query_real_name());
        if (i == 4)
            command("say to "+ tp->query_real_name() +
                " Dancing must make you sore. Enjoy your bath.");
        return;
    }       
    else
    {
        if (i < 4)
           command("say to "+ tp->query_real_name() +
               " Take care that you behave yourself.");
        if (i > 9)
           command("say to "+ tp->query_real_name() +
               " Celebrate the Source, Outlander.");
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (CAN_SEE(TO, TP))
    {
        set_alarm(2.0, 0.0, &check_meet(TP));
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
     who->catch_msg(QCTNAME(this_object()) +" is immune to your attack.\n");
     command("say At this time, in this place, there will be peace.");
     return 1;
}
