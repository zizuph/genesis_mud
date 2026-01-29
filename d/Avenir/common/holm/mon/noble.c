//-*-C++-*-
// file name:     
// creator(s):    Lilith    1/17/97
// purpose:       Shadow-elves on the Hunt
// note:          This file acts like 13 different npcs.
// last update:   Lilith   Jun 2002: Tried to make them a
//                   little easier, but mortals complained.
//                   Changed special attacks to test opponent
//                   stats so npc isn't scaled only for the 
//                   biggest of the big players.    
//                Lilith   Feb 2002: Fixed problem with
//                   items entering the inventory.
//                Lilith   13 Nov 00
//                tweaked sheathing a bit 
//                Lilith    9/7/98: Noticed that players
//                   who can blind the npcs were able to
//                   solo. Figured out why: specials did 
//                   not allow for partial success when
//                   blinded. Corrected.
//               Lucius, 7/7/2006: Players were filling nobles
//                   up with junk, rectified the code to prevent it.
//                   Made the Nobles no longer pull punches, they are
//                   supposed to be dangerous, not made easy for little
//                   players to bounce them (which is what they do).
//                   Also, changed the break_armour routine a bit, it's
//                   slightly more likely to break things now and I
//                   corrected the code a bit. Removed mtrig_follow
//                   since it's not used, OBJ_O_CLING should be managed
//                   if we want them to follow victims.
//               Lilith, 7/2/2021: Prevent imbued items from being
//                   broken.  They are valuable and akin to magical.
//               Zizuph, 1/5/2022: Prevent MAGIC_AM_MAGIC items from being
//                   broken.  Not all magical armours have the 
//                   OBJ_I_IS_MAGIC_ARMOUR properly set.
// bug(s):
// to-do:

#pragma strict_types

inherit "/d/Avenir/inherit/sybarite";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/lib/unique";

#include "/d/Avenir/include/guilds.h"
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "../holm.h"

#include <files.h>
#include <money.h>
#include <language.h>
#include <ss_types.h>
#include <composite.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

#define DEATH_LOG   "/d/Avenir/log/deaths/holm_noble"

/* I'm using functionpointers, so I'm prototyping this func */
string my_long();

/* This array of arrays could also have been done as a mapping */
mixed *everyone = ({
    ({ "hesrim", "icu", "Llin", ({ "resolute", "weary" }), 
       "stout and sad-faced", "cryptic and cinnamon-brown", "dark brown",
       "black lily on a field of yellow, bordered in crimson" }),
    ({ "rathan", "ini", "Sisaer", ({ "cryptic", "mercurial" }), 
       "slender and long-legged", "intense and cyan blue", "deep auburn",
       "wand and scourge on a field of blue, bordered in purple" }),
    ({ "veric", "ini", "Imsa-sa", ({ "cunning", "malevolent" }), 
       "thickset and towering", "suspicious and dark brown", "soot-black",
       "white and blue diagonal stripes, bordered in crimson" }),
    ({ "sornol", "dei", "F'niel", ({ "shrewd", "unpleasant" }), 
       "gaunt and narrow-faced", "keen and black", "chocolate-brown",
       "gold cup on a field of orange, bordered in green" }),
    ({ "kewjat", "dei", "Atrei", ({ "impassive", "menacing" }), 
       "stone-faced and muscular", "alert and deep gray", "soot-black",
       "blue and yellow chequers, bordered in crimson" }),
    ({ "plict", "ini", "Qasz", ({ "restless",  "smiling" }), 
       "tall and fine-boned", "inquisitive and very blue", "black",
       "white crescent on a field of black, bordered in purple" }),
    ({ "jerow", "icu", "Wer'a", ({ "angry", "bruised" }),
       "broad-shouldered and adolescent", "stony and black", "brown", 
       "blue flame on a field of white, bordered in green" }),
    ({ "jeuble", "dei", "Vyis", ({ "zealous", "noble" }),
       "young and fine-boned", "somber and cinnamon-brown", "deep auburn", 
       "gold cat on a field of brown, bordered in green" }),
    ({ "cimbra", "dei", "Cimron", ({ "charming", "dissolute" }), 
       "lean and well-muscled", "wistful and gray-green", "black",
       "white cygnet on a field of blue, bordered in crimson" }),
    ({ "ilavu", "icu", "Primdek", ({ "relaxed", "loose-limbed" }), 
       "stocky, yet loose-limbed", "smiling and grayish", "coal-black",
       "brown quarterstaff on a field of orange, bordered in green" }),
    ({ "trep", "dei", "Ummus", ({ "stoic", "blank-faced" }), 
       "sleek and graceful", "empty blue-black windows", "golden brown",
       "white pentacle on a field of black, bordered in crimson" }),
    ({ "hartsig", "ini", "Abun'ana", ({ "dangerous", "grinning" }), 
       "slim and fine-boned", "yellow, with an unnerving glint", "black",
       "gold brazier on a field of blue, bordered in purple" }),
         
});

object sword;
int who, me, herb, alarm_id, disarm_id;
string attrib, eyes, hair, house, prefix, sigil;

string query_attrib() {    return attrib;    }
string query_eyes()   {    return eyes;      }
string query_hair()   {    return hair;      }
string query_house()  {    return house;     }  
string query_prefix() {    return prefix;    }  
string query_sigil()  {    return sigil;     }
int    query_who()    {    return me;        }

void set_attrib(string str) {    attrib = str;    }
void set_eyes(string str)   {    eyes = str;      }
void set_hair(string str)   {    hair = str;      }
void set_house(string str)  {    house = str;     }  
void set_prefix(string str) {    prefix = str;    }
void set_sigil(string str)  {    sigil = str;     }
void set_who(int who)       {    me = who;        } 

/* 
 * set_morph sets the various attributes of the npc (from the *everyone 
 * array), making it unique in 10+ different ways. We can use this to 
 * set which npc we want or let it generate them randomly.
 */
void
set_morph(int who)
{
    mixed someone;

    if (who < 0 || who >= sizeof(everyone))
       who = (random(sizeof(everyone)));

    someone = everyone[who];
    set_name(someone[0]);
    set_prefix(someone[1]);
    set_house(someone[2]);
    set_adj(someone[3]);    
    set_attrib(someone[4]);
    set_eyes(someone[5]);
    set_hair(someone[6]);
    set_sigil(someone[7]);
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

    set_race_name("shadow-elf");
    add_name(({"elf", "shadow elf", "noble", "shadow-elf"}));
    set_gender(G_MALE);
    set_long(my_long);
    
    /* When I intro, I will give my name, rank, and House. */
    set_title(query_prefix() +" "+ query_house());

    set_alignment(0);             /* Most npcs in Avenir are neutral */
    set_appearance_offset(-40);   /* Always the handsome devil ;) */
    set_knight_prestige(500);     /* Knights get prestige for killing me */
    set_random_move(15);          /* I wander around */

    default_config_npc(random(50) + 125);

    /* with all the special attacks, this guy is tough */
    set_exp_factor(150);

    set_skill(SS_2H_COMBAT,    80 + random(9));
    set_skill(SS_WEP_SWORD,    90 + random(9));
    set_skill(SS_AWARENESS,    99 + random(9));
    set_skill(SS_ACROBAT,      30 + random(25));
     //  set_skill(SS_UNARM_COMBAT, 20);   Removed unarmed combat Ibun 041222
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_WEP_KNIFE, 90);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 85);
    set_skill(SS_SNEAK, 45);
    set_skill(SS_HIDE, 45);
    set_all_attack_unarmed(30, 30);
    set_all_hitloc_unarmed(15);

    if (random(3))
        add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_prop(LIVE_I_SEE_INVIS, 1 + random(4));
    add_prop(LIVE_I_QUICKNESS, 25 + random(25));
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(LIVE_I_SEE_DARK, 3);
    add_prop(LIVE_O_ENEMY_CLING, 1);
    if (random(4))
        set_aggressive(1);     
    set_attack_chance(60);
    set_restrain_path(({"/d/Avenir/common/holm/","/d/Avenir/common/park/"}));

    /* Add this prop, since Rangers are using brawl as a test
     *  for whether or not this npc wields a magical falchion
     */
    add_prop("_ranger_i_not_disarm", 70);

    /* I will attack anything, even if it -is- bigger than me */
    add_prop(NPC_I_NO_FEAR, 1);

    /* So I can wield the falchion and by-pass the wield checks */
    add_prop("_soq_wielder", 1);

    /* I am a sybarite, so add the prop */
    MAKE_SYBARITE; 

    set_act_time(5);
      add_act("@@sheathe_it@@");
      add_act("sigh .");
      add_act("smile grim");
      add_act("emote flexes his wrists.");
      add_act("emote stands perfectly still while his eyes move restlessly "+
          "about.");
      add_act("emote seems to smell something on the air.");
      add_act("emote ignores you.");
      add_act("adjust baldric");
      add_act("emote stares into and beyond the bushes.");
      add_act("emote pours some oil onto a cloth and rubs it into his "+
          "dagger.");

    set_cact_time(3);
      add_cact("glare mercilessly enemy");
      add_cact("shout Thagrinus confound you!");
      add_cact("say Your head will make a fine trophy for Aclolthayr's altar.");
      add_cact("say I find the Hunt exhilerating!");
      add_cact("emote laughs the chilling laugh of one who has known "+
          "total fear and is no longer afraid of anything.");
      add_cact("emote shouts joyfully!");
      add_cact("say I drew first blood!");
      add_cact("say Yes! What fun! I shall finish you off forthwith, and "+
          "recommence my previous Hunt.");
      add_cact("emote raises his voice in a disturbing, ululating chant.");
      add_cact("emote dances swiftly and gracefully around you.");

    set_default_answer(VBFC_ME("what_me"));
      add_ask(({"Hunt", "Hunting", "hunt", "hunting"}), VBFC_ME("hunt_ask"));
      add_ask(({"Rule", "rule" }), VBFC_ME("rule_ask"));
      add_ask(({"aclolthayr"}), VBFC_ME("aclo_ask"));
      add_ask(({"holm", "park"}), "say That's where you are right now. "+
          "This place is the where the Hunt takes place, and where some "+
          "unusual creatures reside. If you're looking for a safe place "+
          "for a picnic, you'd better go elsewhere.", 1);
      add_ask(({"bath", "melchior's bath", "bathhouse"}),
          "say There is a bathhouse in the City. I'll be "+
          "soaking myself there when I've finished my Hunt.",1);
      add_ask(({"sybarus","bazaar"}),
          "say Its the main island, over yonder.",1);
      add_ask("city", "smile myst",1);
      add_ask(({"task", "job", "quest", "help"}),  VBFC_ME("give_task"));
      add_ask(({"infidel","infidels"}),
          "say Blasphemers, all of them! And what fine prey they make "+
          "for the Hunt.",1);
      add_ask(({"faithful","faithfuls","Faithful", "sybarite", "sybarites"}),
          "say We of Sybarus are the Faithful. We live to serve and "+
          "uphold the Pact, that the Source will always cast its illum"+
          "ination upon us.",1);


}

/*
 * equip_me is called in the npc when it is cloned by the 
 * placer module.
 */
void 
equip_me()
{
    object armour, baldric, boots, cape, codpiece, dagger, oil, pouch, token;
    string *randboot;
    int i;

    seteuid(getuid());

    i = random(10);
    MONEY_MAKE_SC(i)->move(TO);
    MONEY_MAKE_PC(random(3))->move(TO);

    armour = clone_object(HOLM_OBJ + "armour");
    armour->move(TO);

    baldric = clone_object(HOLM_OBJ + "baldric"); 
    baldric->set_sigil(sigil);
    baldric->move(TO);     

    /* 3 chances in 10 of getting magical boots so long as there aren't
     * too many in the game.
     */   
    switch (i)
    {
        case 3:  boots = clone_unique(HOLM_OBJ +"m_boots1", 7, 
		     HOLM_OBJ +"boots", 1, 25); break;
        case 5:  boots = clone_unique(HOLM_OBJ + "m_boots2", 7,
		     HOLM_OBJ + "boots", 1, 25); break;
        case 7:  boots = clone_unique(HOLM_OBJ + "m_boots1", 7,
		     HOLM_OBJ + "boots", 1, 25); break;
        default: boots = clone_object(HOLM_OBJ + "boots");
                 break;
    }
    boots->move(TO);

    cape = clone_object(HOLM_OBJ +"cape");
    cape->move(TO);

    codpiece = clone_object(BAZAAR +"Obj/worn/codpiece");
    codpiece->move(TO);

    dagger = clone_object(HOLM_OBJ + "dagger");
    dagger->set_sigil(sigil);
    dagger->move(TO);

    if (i >= 5)
    {
        oil = clone_object(BAZAAR +"Obj/misc/wep_oil");
        oil->move(TO);
        token = clone_object("/d/Avenir/common/obj/syb_coin");
        token->move(TO);       
    }
    if (i < 5)
    {
        pouch = clone_object(HOLM_OBJ + "herb_pouch");
        pouch->fill_pouch();
        pouch->move(TO);
    }
    
    /* 15% chance of the falchion being magical. */
    sword = clone_unique(HOLM_OBJ + "falchion", 7,
	HOLM_OBJ + "falchion_nm", 1, 15);
    sword->move(TO);

    /* Wield the weapons seperately so the falchion is always 
       wielded in the left hand ;)  */
    command("wield dagger");
    command("wield falchion");
    command("wear all");
}

/* This determines what I 'look' like */
string
my_long()
{
    string  str;

    str = "He is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
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
         "He is wearing a baldric marked with the escutcheon of his "+
         "House: a "+ query_sigil() +".\n";
    return str;
}


/*
 * check_meet enables the npc to greet players it
 * comes into contact with, according to guild.
 * See /d/Avenir/include/guilds.h for the guild defs.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(6);

    /* Reset. (See init_living) */
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    if (tp->query_met(query_real_name())) 
    {
        if (IS_SYBARITE(tp))
        {
            command("say to "+ tp->query_real_name() +
                " We meet again. How fares the Hunt?");
            return;
        }
        else 
        {   
            if (i == 1)
            {            
                command("say to "+ tp->query_real_name() +" You again!");
                command("draw falchion from baldric");
                command("wield all");
                command("kill "+ tp->query_real_name());
            }
        }
	return;
    }       

    if (IS_INFIDEL(tp))
    {
        command("draw falchion from baldric");
        command("wield all");
        command("kill "+ tp->query_real_name());
        command("shout Ar'sharah mas Infidel!");
        return;
    }

    occ = tp->query_guild_name_occ();
    switch(occ)
    {
        case OMONK:
            if (i == 0)
            {
                command("ask "+ tp->query_real_name() +" I've heard "+
                    "that you Monk hit below the belt. Is that "+
                    "true?");
                command("grin sad at "+tp->query_real_name());
            }
            if (i == 1)
            {
                command("say What is good or evil, but a matter of "+
                    "perspective?");
                command("say And what are Outlander Monk's, but fence-sitters?");
            }
            break;
        case OMYSTIC:
            if (i == 2)
            {
                command("say to "+ tp->query_real_name() +" My Ancients "+
                    "are older than yours!");
                command("emote belly-laughs.");
            }
            break;
        case OANGMAR:
            if (i == 2)
            {
                command("think whether or not he should hide the sheep");
                command("sneer "+ tp->query_real_name());
            }
            break;
        case OCALIA:
            if (i == 0)
                command("say Why, if it isn't one of Little Caliana's "+
                    "people.");
            break;
            if (i == 3);
            {
                command("ask "+ tp->query_real_name() +" Is it true "+
                   "that Caliana wears bunny slippers to bed and nothing "+
                   "else?");                 
                command("cackle glee");
                break;
            }
            if (i == 5)
                command("kill "+ tp->query_real_name());
            break;
        case OGLADIATOR:
            if (i == 4)
                command("say to "+ tp->query_real_name() +" Slave of Kalak, "+
                    "lick my boots!");
            break;
            if (i == 5)
                command("snicker at "+ tp->query_real_name());
            break;
        case ORANGER:
            if (i == 0)
            {
                command("say to "+ tp->query_real_name() +" Here's "+
                    "mud in your eye!");
                command("spit "+ tp->query_real_name());
                command("kill "+ tp->query_real_name());
                break;
            }
            if (i == 4)
            {
                command("say Rangers.");
                command("sneer contempt "+ tp->query_real_name());
                command("say You people are always scratching about in the "+
                    "dirt. Do you ever find anything? That's what I'd "+
                    "like to know...");
                command("kill "+ tp->query_real_name());               
            }
            break;
        case OMAGE:
            if (i == 2)
            {
                command("say to "+ tp->query_real_name() +" Gone and "+
                    "lost your head over Sauron, eh?");
                command("compliment "+ tp->query_real_name());       
                command("say I dare say, it might actually be an improv"+
                    "ment!");                  
                break;
            }
            if (i == 4)
                command("smile respect "+ tp->query_real_name());
            break;
        case OKNIGHT:
            if (i == 5)
            {
                command("say Ah, a Knight! Perhaps you could help me...");
                command("ask "+ tp->query_real_name() +" I've always "+
                    "wanted to know why someone of your minor -- yet not "+
                    "inconsiderable -- talents would take a wimp like "+
                    "Paladine as a Patron?");
                command("smile curi at " + tp->query_real_name());               
            }
            break;
        case OUNION:
            if (i == 0)           
                command("say to "+ tp->query_real_name() +" Celebrate "+
                    "the Source!");
            break;
            if (i == 4)
                command("say to "+ tp->query_real_name() +" Sirli, "+
                    "Amlis k'miasil!");
            break;
        case "OWOHS":
            if (i == 3)
            {
                command("say to "+ tp->query_real_name() +" Be careful "+
                   "little magic-user, or a nasty beast might eat "+
                   "you while you're sorting spell components.");
                command("grin sarcastic "+ tp->query_real_name());
            }
            break;
        default:
                command("say to "+ tp->query_real_name() +
                    " Sin'ur, you don't belong here! Leave!");
            break;
    }
}

/* **** add_ask answers, including quest assignment, if any **** */
string 
aclo_ask()
{
    if (CAN_SEE(TO, TP))
    {
        command("say to "+ TP->query_real_name() +
            " Aclolthayr is the patron goddess of the Hunt.");
        command("say to "+ TP->query_real_name() +
            " If you want to know anything more, you'll "+
            "have to find out for yourself.");
        return "";
    }
    command("say Aclolthayr is the patron goddess of the Hunt.");
    command("say If you want to know anything more, you'll "+
        "have to find out for yourself.");
    return "";
}
          
string
hunt_ask()
{
    string str1, str2;
    mixed randstr1, randstr2;
    randstr1 = ({ "rival", "servant", "House brother", "associate"});
    randstr2 = ({ "Commissioner", "Inquisitor", "Exectutioner" });
    str1 = (randstr1[random(sizeof(randstr1))]);
    str2 = (randstr2[random(sizeof(randstr2))]);
    if (IS_SYBARITE(TP))
    {
        if (CAN_SEE(TO, TP) && IS_SYBARITE(TP))
        {
            command("say to "+ TP->query_real_name() +
                " Are you on a Hunt? If so, remember the Rule.");
            command("say to "+ TP->query_real_name() +
                " Me, I'm Hunting a former "+ str1 +" of mine. "+
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
            return "";
        }
    } 
    command("say A true Hunt involves intelligent prey.");
    command("say There is only one rule on the Holm: Everyone and "+
        "everything is fair game.");
        command("say So you had best be careful, Outlander.");
    return "";
}    

string
rule_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say Interesting, indeed, that the air asks "+
            "questions without the voice of a God.");        
        return "";
    }
    command("say to "+ TP->query_real_name() +
        " As you know, a true Hunt involves intelligent prey.");
    command("say to "+ TP->query_real_name() +
        " So there is only one rule on the Holm: Everyone and "+
        "everything is fair game.");
    command("say to "+ TP->query_real_name() +
        " Fortunately for you, I'm hunting someone else.");
    command("grin wick");
    return "";
}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say Interesting, indeed, that the air asks "+
            "questions without the voice of a God.");        
        command("say Reveal yourself, coward!");
        return "";
    }
    command("say I'm not interested in conversation, Fool. Can't you "+
        "see I'm busy?");
    return "";
}

string
give_task()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks around suspiciously");
        command("say The air speaks not in the voice of a "+
            "God.");
        command("say Show yourself, Coward, that I may eviscer"+
            "ate you with my dagger.");
        return "";
    }
    else     
    {
        command("frown");
        command("say The Holm is MY hunting-ground.");
        command("say What are you doing here?");
        command("get falchion from baldric");
        command("wield all");
        command("kill " + OB_NAME(TP));
        return "";
    }
}

/* *************** What we do when attacked ****************** */
void
sheathe_it()
{
    int i;
    i = random(10);

    if (sword->query_wielded() != 0 && (!objectp(query_attack())))
    {
        /* reset the disarm special attack */
        disarm_id = 0;
        
        if (i > 7)
            command("sheathe dagger in baldric");
    }
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);
    command("wield falchion");
    /* Lets try to disarm our opponents */
    if (!disarm_id)
        disarm_id = set_alarm(10.0, 0.0, &command("cdisarm"));       
}

/* **************** Used in Special Attack function  *************** */

void
break_worn(object victim)
{
    object *armours;

    if (!random(5))
	return;

    armours = victim->query_armour(-1);

    foreach(object arm : armours)
    {
	if (arm->query_ac() <= 5)
	    continue;

	if (arm->query_prop(MAGIC_AM_MAGIC))
	    continue;

	if (arm->query_prop(OBJ_I_IS_MAGIC_ARMOUR))
	    continue;

    if (arm->has_imbue_shadow())
        continue;

	victim->catch_msg(QCTPNAME(TO)+" leg moves so quickly "+
	    "it is a blur. He kicks your " + arm->short() + 
	    " with incredible force.\n");
	tell_room(ENV(TO), QCTNAME(TO)+" moves very quickly " + 
	    "and kicks "+ QTPNAME(victim) + " "+ arm->short() + 
	    " very hard!\n", victim);

	arm->remove_broken();
	return;
    }
}

/* Most of these specials are from the ~Avenir/inherit/sybarite.c */
int
special_attack(object victim)
{
    int s, t;

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	return 1;
    }

    /* To make things a little fairer to smaller players, 
     * lets pull our punches a bit, so to speak.
     *
     * Changed: Little bouncy players should know better
     *          than to be on the holm, it's _supposed_
     *          to be dangerous!
     *
    s = victim->query_average_stat();
    switch (s)
    {
        case 15..115:   t = 3; break;
        case 116..130:  t = 5; break;
        case 131..150:  t = 8; break;
        case 151..500:  t = 10; break;
        default:        t = 8; 
    }   
     */

    /* Most of these specials are in /d/Avenir/inherit/sybarite.c */
    switch (random(10))
    {
        case 0: command("cure");
            return 0;        
        case 1:
	    return 0;
        case 2: command("pommel");
            return 0;
        case 3: command("neck");
            return 0;
        case 4: command("skick");
            return 0;
        case 5: command("heal");
            return 1;
        case 6: break_worn(victim);
            return 0;
        case 7: command("cdisarm");
            return 0;
        case 8: command("skick");
            return 0;
        case 9: command("neck");
            return 0;
        default: 
    }
    return 0;
}

/* Lets make dying more interesting. */
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

    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Noble "+ TO->query_name() +" killed by "+ 
        killer->query_name() +"("+ killer->query_average_stat() +") "+ 
        (sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));
    STATSERV_LOG_EVENT("holm", "Noble died");

    switch(random(6))
    {
        case 0:
            command("emote gasps between blood-stained lips: You were a "+
                "worthy opponent. I die as I have always wanted, upon "+
                "the Hunt.");
            break;
        case 1:
            command("say Life is but a dream. Dying, I awaken.");
            break;
        case 2:
            command("emote struggles to speak. Blood bubbles from "+
                POSSESS(TO) +" lips, instead.");
            break;
        case 3:
            command("say I have brought my House honour in this, "+
                "my final act.");
            break;
        case 4:
            command("emote appears overcome with ecstacy.");
            command("shout She comes! Little Mother comes for me.");
            break;
        case 5:
            command("say I lived my life with Exuberance. May Jazur "+
                "judge that to be Beauty enough.");
            break;
    }

    command("smile "+ killer->query_name());

    ::do_die(killer);
}

/* When I run into a living, this func is called */
void
init_living()
{
    ::init_living();

    /* If the living is a player and I can see him ... */
    if (query_interactive(TP) && CAN_SEE(TO, TP))
    {
        /* Only one person, so as not to spam a team */
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
    } /* If the living is a sybarite npc .. */
    else if (IS_SYBARITE(TP))
    {
        team_join(TP);
        TP->set_leader(TO);
    }    
}  

/* quest */

void
test_letter_quest(object player)
{
    set_alarm (2.0, 0.0, &command("emote looks resigned."));
    set_alarm (4.0, 0.0, &command("emote opens the letter and "+
        "scans it quickly."));
    set_alarm (6.0, 0.0, &command("sigh"));
    set_alarm (8.0, 0.0, &command("say Wait a moment and I'll "+
        "give you my response."));
    set_alarm (10.0, 0.0, &command("emote pulls a charcoal "+
        "pencil from his pocket and writes something at the "+
        "bottom of the letter."));
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

/*
 * Changed to not give back, that is easily bypassed by simply
 * handing stuff over and leaving the room for a moment making
 * the extra codepath not worthwhile. Instead of dropping them
 * to the ground, we are mean and simply nuke it.
 */
void 
drop_unwanted(object what, object who)
{
    command("eyebrow "+ OB_NAME(who));
    what->remove_object();  
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
        return;

    if (obj->id("_letter_from_jadestone"))
    {
        if (this_object()->id("galerin"))
        {
            test_letter_quest(from);
            obj->remove_object();  
            return;
        }
    }
    else
    {
	if (query_prop("__avenir_cloak_disarm"))
	    return;

	if (IS_WEAPON_OBJECT(obj))
	    return;

	set_alarm(1.0, 0.0, &drop_unwanted(obj, from));
    }
}

/*
 * Function name: aggressive_attack
 * Description:   We are aggressive, let us attack
 * Arguments:     ob - the object to attack
 */
public void
aggressive_attack(object ob)
{
    if (!present(ob, environment(this_object())) ||
	!query_interactive(ob) ||
	!CAN_SEE(TO, ob) ||
	query_attack())
	return;

    set_alarm(itof(random(4)), 0.0, &command("kill " + OB_NAME(ob)));
}
