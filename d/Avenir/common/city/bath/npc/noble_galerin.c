#pragma strict_types
/*
 * ~/noble_galerin.c
 *
 * NPC for the bath.
 * Jadestone Doll's letter quest
 *
 * Revisions:
 *   Lilith, Jan 1997: Created.
 *   Lilith, Nov 2004: Isolated from the other nobles for
 *   			making the quest completable off the Holm.
 *   Lucius, Jul 2017: Code Cleanups.
 *
 */
inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";

#include "../bath.h"
#include "/d/Avenir/include/relation.h"

#define TO	this_object()
#define TP	this_player()

#include <stdproperties.h>
#include <composite.h>
#include <money.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>

#define DEATH_LOG   "/d/Avenir/log/deaths/holm_noble"

public string my_long(void);

private mixed *everyone = ({
    ({ "galerin", "icu", "Ra'let", ({ "robust", "fastidious" }),
       "tall and well-formed", "indifferent and steely gray", "black",
       "fire lizard on a field of black, bordered in green",
    }),
});

string attrib, eyes, hair, house, prefix, sigil;

string query_attrib() {    return attrib;    }
string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_house()  {    return house;     }  
string query_prefix() {    return prefix;    }  
string query_sigil()  {    return sigil;     }

void set_attrib(string str) {    attrib = str;    }
void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
void set_house(string str)  {    house = str;     }  
void set_prefix(string str) {    prefix = str;    }
void set_sigil(string str)  {    sigil = str;     }


public void
set_morph(int who)
{
    mixed *someone = everyone[0];
    set_name(someone[0]);
    set_prefix(someone[1]);
    set_house(someone[2]);
    set_adj(someone[3]);    
    set_attrib(someone[4]);
    set_eyes(someone[5]);
    set_hair(someone[6]);
    set_sigil(someone[7]);
}

/* Create the npc */
public void
create_monster(void)
{
    if (!IS_CLONE)
        return;

    /* Lets make sure the sybarite stuff is initialized */
    ::create_sybarite();

    /* Set my identity */
    set_morph(0);

    set_race_name("shadow-elf");
    add_name(({"elf", "noble", "shadow-elf"}));
    set_gender(G_MALE);
    set_long(my_long);
    
    /* When I intro, I will give my name, rank, and House. */
    set_title(query_prefix() +" "+ query_house());

    set_alignment(0);             /* Most npcs in Avenir are neutral */
    set_appearance_offset(-40);   /* Always the handsome devil ;) */

    default_config_npc(random(50) + 125);

    set_skill(SS_2H_COMBAT,    80 + random(9));
    set_skill(SS_WEP_SWORD,    90 + random(9));
    set_skill(SS_AWARENESS,   100);
    set_skill(SS_ACROBAT,      30 + random(25));
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 85);
    set_skill(SS_SNEAK, 45);
    set_skill(SS_HIDE, 45);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(15);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_prop(LIVE_I_SEE_INVIS, 1 + random(4));
    add_prop(LIVE_I_QUICKNESS, 25 + random(25));
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(LIVE_I_SEE_DARK, 3);

    /* I am a sybarite, so add the prop */
    MAKE_SYBARITE; 

    set_act_time(15);
      add_act("emote rubs his sword arm.");
      add_act("sigh bliss");
      add_act("emote breathes deeply of the scented air.");
      add_act("emote flexes his wrists.");
      add_act("emote eyes you appraisingly.");
      add_act("emote puts one hand on the opposite shoulder "+
         "and rotates his arm, rubbing out a kink.");
      add_act("emote stands still for a moment, eyes closed.");
      add_act("say to dej Jadestone is going to be peeved that "+
         "we are in the baths together.");

    set_default_answer(VBFC_ME("what_me"));
      add_ask(({"jadestone", "jadestone doll", "jade" }),
          "Ah, the lovely Jade. She's very tempermental, isn't she?", 1);
      add_ask(({"Hunt", "Hunting", "hunt", "hunting"}), VBFC_ME("hunt_ask"));
      add_ask(({"Rule", "rule" }), VBFC_ME("rule_ask"));
      add_ask(({"aclolthayr"}), VBFC_ME("aclo_ask"));
      add_ask(({"holm", "park"}), "say It is the place where "+
          "the Hunt takes place, and where some "+
          "unusual creatures reside. If you're looking for a safe place "+
          "for a picnic, you'd better go elsewhere.", 1);
      add_ask(({"bath", "melchior's bath", "bathhouse"}),
          "say I enjoy soaking myself here when I've finished my Hunt.",1);
      add_ask(({"sybarus","bazaar"}),
          "say Its the main island, over yonder.",1);
      add_ask("city", "smile myst",1);
      add_ask(({"infidel","infidels"}),
          "say Blasphemers, all of them! And what fine prey they make "+
          "for the Hunt.",1);
      add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
          "say We of Sybarus are the Faithful. We live to serve and "+
          "uphold the Pact, that the Source will always cast its illum"+
          "ination upon us.",1);

    seteuid(getuid());
    MONEY_MAKE_SC(random(10))->move(TO);
    MONEY_MAKE_PC(random(3))->move(TO);
}

/* This determines what I 'look' like */
public string
my_long(void)
{
    string str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
	query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting himself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", male "+ query_race_name() +".\n";
    }

    str += "He is "+ query_attrib() +", with the physical grace "+
         "characteristic of a shadow-elf. His skin is so pale as "+
         "to be translucent, its whiteness tinted blue in some places "+
         "by his veins.\nHis long hair is "+ query_hair() +" and tied "+
         "in a Hunter's braid.\nHis eyes are "+ query_eyes() +".\n"+
         "He is wearing a medallion bearing the escutcheon of his "+
         "House: a "+ query_sigil() +".\n";

    return str;
}


/* **** add_ask answers, including quest assignment, if any **** */
public string 
aclo_ask(void)
{
    if (CAN_SEE(TO, TP))
    {
        command("say to "+ TP->query_real_name() +
            " Aclolthayr is the patron goddess of the Hunt.");
        command("say to "+ TP->query_real_name() +
            " If you want to know anything more, you'll "+
            "have to find out for yourself.");
    }
    else
    {
	command("say Aclolthayr is the patron goddess of the Hunt.");
	command("say If you want to know anything more, you'll "+
	    "have to find out for yourself.");
    }
    return "";
}

private string *randstr1 = ({
    "rival", "servant", "House brother", "associate"
});
private string *randstr2 = ({
    "Commissioner", "Inquisitor", "Exectutioner"
});
          
public string
hunt_ask(void)
{
    string str1 = one_of_list(randstr1),
	   str2 = one_of_list(randstr2);

    if (IS_SYBARITE(TP))
    {
        if (CAN_SEE(TO, TP) && IS_SYBARITE(TP))
        {
            command("say to "+ TP->query_real_name() +
                " Are you on a Hunt? If so, remember the Rule.");
            command("say to "+ TP->query_real_name() +
                " Me, I'm looking forward to Hunting a former "+ str1 +" of mine. "+
                "The Lord "+ str2 +" stripped him of rank and "+
                "gave him the choice of execution or the Hunt.");
            command("say to "+ TP->query_real_name() +
                " He chose the Hunt, of course.");

            if (random(4))
            {
                command("say to "+ TP->query_real_name() +
                    " He's been leading me a merry chase, but I'll "+
                    "catch him. And when I do I'll offer his head as a "+
                    "trophy for Aclolthayr's altar.");
                command("grin");
            }
        }
    } 
    else
    {
	command("say A true Hunt involves intelligent prey.");
	command("say There is only one rule on the Holm: Everyone and "+
	    "everything is fair game.");
	command("say So you had best be careful, Outlander.");
    }
    return "";
}    

public string
rule_ask(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("say Interesting, indeed, that the air asks "+
            "questions without the voice of a God.");        
    }
    else
    {
	command("say to "+ TP->query_real_name() +
	    " As you know, a true Hunt involves intelligent prey.");
	command("say to "+ TP->query_real_name() +
	    " So there is only one rule on the Holm: Everyone and "+
	    "everything is fair game. In other words, there are no rules.");
	command("say to "+ TP->query_real_name() +
	    " Fortunately for you, I'm hunting someone else.");
	command("grin wick");
    }
    return "";
}

public string
what_me(void)
{
    if (!CAN_SEE(TO, TP))
    {
        command("say Interesting, indeed, that the air asks "+
            "questions without the voice of a God.");        
        command("say Reveal yourself, coward!");
    }
    else
    {
	command("say I'm not interested in conversation, Fool. Can't you "+
	    "see I'm busy?");
    }
    return "";
}

/* quest */
public void
test_letter_quest(object player)
{
    set_alarm (2.0, 0.0, &command("emote looks resigned."));
    set_alarm (4.0, 0.0, &command("emote opens the letter and "+
        "scans it quickly."));
    set_alarm (6.0, 0.0, &command("sigh"));
    set_alarm (8.0, 0.0, &command("say Wait a moment and I'll "+
        "give you my response."));
    set_alarm (10.0, 0.0, &command("emote motions to a bath "+
        "attendant, who brings him a charcoal "+
        "pencil."));
    set_alarm (12.0, 0.0, &command("emote writes something at "+
        "the bottom of the letter."));
    set_alarm (14.0, 0.0, &command("emote folds up the "+
        "letter and re-seals it."));
    clone_object(BAZAAR+"Obj/misc/m_letter")->move(this_object());
    set_alarm(16.0, 0.0, &command("give _letter_from_galerin to "
          +TP->query_real_name()));
    set_alarm (18.0, 0.0, &command("thank " +
        player->query_real_name()));
    set_alarm (14.0, 0.0, &command("say It would be wise to "+
        "return this to her quickly."));
}

public void 
drop_unwanted(object what, object who)
{
    command("eyebrow "+ who->query_real_name());

    if (!command("give "+ what->query_name() +
	    " to "+ who->query_real_name()))
    {
	what->remove_object();  
    }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
        return;

    if (obj->id("_letter_from_jadestone") &&
	this_object()->id("galerin"))
    {
	test_letter_quest(from);
	obj->remove_object();  
	return;
    }

    set_alarm(2.0, 0.0, &drop_unwanted(obj, from));
}
