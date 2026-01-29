#pragma strict_types
/*
 * ~/patron.c
 *
 * Patrons of the bath house
 *
 * Revisions:
 *   Lilith, Jul 2003: Created.
 *   Lucius, Jul 2017: Code Cleanups.
 *
 */
inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/log_asks";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>

#include "../bath.h"
#include "/d/Avenir/include/relation.h"

#define TO	this_object()
#define TP	this_player()

private mixed *everyone = ({
    ({ "undusi", "icu", "Ra'let", ({ "solemn", "attentive" }),
       "intense and cyan blue", "deep auburn",  "human",
       "fire lizard on a field of black, bordered in green"}),
    ({ "tristun", "icu", "Llin", ({ "impassive", "upright" }), 
       "suspicious and dark brown", "soot-black", "gnome",
       "black lily on a field of yellow, bordered in crimson" }),
    ({ "alurist", "ini", "Sisaer", ({ "grave", "thoughtful" }), 
       "indifferent and steely gray", "black", "dwarf",
       "wand and scourge on a field of blue, bordered in purple" }),
    ({ "twilis", "ini", "Imsa-sa", ({ "sombre", "gaunt" }), 
       "cryptic and cinnamon-brown", "dark brown", "human",
       "white and blue diagonal stripes, bordered in crimson" }),
    ({ "sten", "icu", "F'niel", ({ "shrewd", "gentlemanly" }), 
       "alert and deep gray", "soot-black", "gnome",
       "gold cup on a field of orange, bordered in green" }),
    ({ "lorael", "icu", "Atrei", ({ "solemn", "soft-spoken" }), 
       "keen and black", "chocolate-brown", "dwarf",
       "blue and yellow chequers, bordered in crimson" }),
    ({ "jontan", "ini", "Qasz", ({ "pensive",  "frowning" }),
       "somber and cinnamon-brown", "deep auburn",  "human",
       "white crescent on a field of black, bordered in purple" }),
    ({ "jilip", "icu", "Wer'a", ({ "serious", "fine-boned" }),
       "stony and black", "brown", "gnome",
       "blue flame on a field of white, bordered in green" }),
    ({ "tutal", "ini", "Vyis", ({ "grim", "scrupulous" }),
       "incredulous and very blue", "black", "goblin",
       "gold cat on a field of brown, bordered in green" }),
    ({ "cilka", "icu", "Cimron", ({ "somber", "distinguished" }), 
       "yellow, with an unnerving glint", "black", "dwarf",
       "white cygnet on a field of blue, bordered in crimson" }),
    ({ "ablin", "icu", "Primdel", ({ "dignified", "thoughtful" }), 
       "wistful and gray-green", "black", "half-elf",
       "brown quarterstaff on a field of orange, bordered in green" }),
    ({ "mielist", "ini", "Ummus", ({ "philosophical", "old" }), 
       "reflective blue-black windows", "golden brown", "half-elf",
       "white pentacle on a field of black, bordered in crimson" }),
    ({ "shumti", "ini", "Abun'ana", ({ "lovely", "grave" }), 
       "smiling and grayish", "coal-black",  "half-elf",
       "gold brazier on a field of blue, bordered in purple" }),
});

int who, me, alarm_id;
string attrib, eyes, hair, house, prefix, sigil, race;

string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_house()  {    return house;     }  
string query_prefix() {    return prefix;    }  
string query_sigil()  {    return sigil;     }
int    query_who()    {    return me;        }

void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
void set_house(string str)  {    house = str;     }  
void set_prefix(string str) {    prefix = str;    }
void set_sigil(string str)  {    sigil = str;     }
void set_who(int who)       {    me = who;        } 

public string my_long(void);

/* 
 * set_morph sets the various attributes of the 
 * npc, making it unique in 10 different ways.
 */
public void
set_morph(int who)
{
    mixed someone;

    if (who < 0 || who >= sizeof(everyone))
       who = random(sizeof(everyone));

    someone = everyone[who];
    set_name(someone[0]);
    set_prefix(someone[1]);
    set_house(someone[2]);
    set_adj(someone[3]);
    set_eyes(someone[4]);
    set_hair(someone[5]);
    set_race_name(someone[6]);
    set_sigil(someone[7]);
    set_who(who);
    set_gender(random(2));
}

public string
my_title(void)
{
    return query_prefix() +" "+ query_house();
}

/* Create the npc */
public void
create_monster(void)
{
    /* If I'm not a clone, don't proceed */
    if (!IS_CLONE)
        return;

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();

    /* You're all individuals! */
    set_morph(-1);

    set_long(my_long);
    add_name(({"patron","sybarite"}));
    set_title(my_title());
    set_alignment(0);
    set_appearance_offset(-10); // always the 'handsome' devils ;)
    default_config_npc(random(30) + 50);

    set_skill(SS_DEFENCE, 85);
    set_skill(SS_AWARENESS, 40 + random(25));
    set_skill(SS_WEP_KNIFE, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 85);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(35);

    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart", 1, "", 0, 0);

    add_prop(LIVE_I_SEE_INVIS, 1 + random(8));
    add_prop(LIVE_I_QUICKNESS, 50 + random(25));
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
    MAKE_SYBARITE; 

    set_act_time(20);
      add_act("sigh bliss");
      add_act("smile dream");
      add_act("emote looks into the mist.");
      add_act("emote inhales deeply.");
      add_act("swim");
      add_act("float");
      add_act("s lather");
      add_act("savour kahve");

    set_default_answer(VBFC_ME("what_me"));
     add_ask(({"holm", "park"}), "say That's where the Hunt takes "+
          "place.", 1);
      add_ask(({"bath", "melchior's bath", "bathhouse"}),
          "say I love this place.",1);
      add_ask(({"bazaar"}),
          "say Its past the Third Gate.",1);
      add_ask("city", "smile myst",1);
      add_ask(({"infidel","infidels", "prisoner", "prisoners", "criminals"}),
          "say Criminals don't live long in Sybarus",1);
      add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
          "say We of Sybarus are the Faithful. We live to serve and "+
          "uphold the Pact, that the Source will always cast its illum"+
          "ination upon us.",1);

    seteuid(getuid());
    clone_object(BATHOB +"soap")->move(this_object(), 1);
    clone_object(CITY +"obj/food/iced_coffee")->move(this_object(), 1);
}

public string 
query_exp_title(void)
{
    return "sybarite";
}

public string
my_long(void)
{
    string str = "This is "+ LANG_ADDART(implode(query_adjs(), " "))
	+" "+ query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting "+ 
            this_object()->query_objective() +"self as:\n" 
            + query_name();

        if (strlen(query_title()))
            str += " "+ query_title() +",";
   	    str += " "+ query_exp_title() +", "+ 
            query_gender_string() +" "+ 
            query_race_name() +".\n";
    }

    str += capitalize(this_object()->query_pronoun()) +" has the "+
         "dignity and presence characteristic of most sybarites of status.\n"+ 
         capitalize(this_object()->query_pronoun()) +" is wearing a "+
         "fluffy white towel marked with the escutcheon of "+ 
         this_object()->query_possessive() +" House: a "+ query_sigil() +".\n"+
         capitalize(this_object()->query_possessive()) +
         " "+ query_hair() +" hair is elaborately braided.\n"+
         capitalize(this_object()->query_possessive()) +" eyes are "+ 
         query_eyes() +".\n";

    return str;
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 */
public void
check_meet(object tp)
{
    alarm_id = 0;
    command("nod at "+ tp->query_real_name());
}

public void
init_living(void)
{
    ::init_living();

    if (interactive(TP) && CAN_SEE(TO, TP) && !alarm_id)
	alarm_id = set_alarm(4.0, 0.0, &check_meet(TP));
}

public string
what_me(void)
{
    command("say I'm trying to relax. Please, no questions...");
    return "";
}

public string
race_sound(void)
{
    return "says in a near-whisper";
}
