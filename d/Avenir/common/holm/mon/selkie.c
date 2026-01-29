//-*-C++-*-
// selkie         /d/Avenir/common/holm/mon/selkie.c
// creator(s):    Lilith   04/09/97
// purpose:       This is a selkie. They look like seals and can
//                polymorph to human form. Very beautiful in human 
//                form, eyes are blue-green. Healing and curative 
//                powers, weather summoning. Live in cold waters.
// note:          hp healing = value/10  (npc loses mana 2*healed hp)
// last update:   Lilith  13 Nov 00
//                Zizuph  Aug 2021 moved to stat-based special.
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";
inherit "/d/Avenir/inherit/defeat";
inherit "/d/Genesis/specials/npc/stat_based_specials";
inherit "/lib/unique";

#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Genesis/gems/gem.h"
#include "../holm.h"
#include <ss_types.h>
#include <language.h>
#include <wa_types.h>

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif
#define  HEAL_LOG     "/d/Avenir/log/misc/healing"
#define  CHECK_PROP   "_Avenir_erinys_healed"

/* Create the npc */
void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("erinys");
    set_long("@@my_long@@");
    add_name(({"selkie","nymph", "sylph"}));
    set_race_name("human");
    set_adj(({"alluring", "slender"}));
    set_title("reis hep Hizarbin");
    set_gender(G_FEMALE);
    set_alignment(0);
    set_knight_prestige(100);   
    default_config_npc(100 + random(20));

    MAKE_SYBARITE;
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop("_cont_i_height", 210);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_skill(SS_DEFENCE, random(20) + 70);
    set_skill(SS_AWARENESS, random(30)+ 20);
    set_skill(SS_BLIND_COMBAT, random(20)+ 80);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_SNEAK, random(20) + 25);
    set_skill(SS_HIDE, random(20) + 25);
    set_all_attack_unarmed(60, 50);
    set_all_hitloc_unarmed(75);
    set_stat_extra(4, 100);  // WIS

    set_act_time(4);
      add_act("smile seductively");
      add_act("emote twines a long lock of hair between her fingers.");
      add_act("emote looks out into the dark sea.");
      add_act("say You have but to ask my help and I will give it.");
      add_act("say 'Tis a gift to be simple.");
      add_act("say One of my cousins dwells in the stream at the base "+
          "of the Spire. She's very angry. You should beware.");       
      add_act("say Pain has something not to be avoided in its gentle "+
          "beginning, and pleasure something to be savored in its exce"+
          "ssive ending.");
      add_act("say I have from my mother the gift of healing, and from "+
          "my father, the gift of the sea.");
      add_act("say Pain, pleasure, love, hatred--these are the first "+
          "things a child of Sybarus feels; If, when Reason comes, "+
          "they attach themselves to her, that is Virtue.");
      add_act("say Temperance is the plague of sensual pleasure, "+
          "yet intemperance is not its scourge--it is its seasoning.");      
      add_act("say Ah, men. Such shapely limbs and muscled torsos, "+
          "topped with heads of pudding.");
      add_act("say The fruit and goal of a Hunter's pursuit is the "+
          "pursuit itself.");
      add_act("say Poor infidels, who pass over what they possess "+
          "to be the slaves of hope and vain images, which simply "+
          "hasten their flight into the Hunter's net.");
      add_act("emote hums a beguiling tune.");
      add_act("emote smiles enchantingly.");

    set_cact_time(7);
      add_cact("glare mercilessly enemy");
      add_cact("say There is nothing so beautiful and just as to play "+
          "the man fitly. Why do you attack me?");
      add_cact("say I rest here and offer you no injury, yet you "+
          "attack me?");
      add_cact("say I offer Mother's gift of healing to all who come "+
          "to me, and this is how I am repaid?");
      add_cact("say It is not fitting that I should be assaulted here!");
      add_cact("say I am a healer, not a killer. Yet you force me to "+
          "strike at you!");
      add_cact("say The Holm is lawless, and all are fair game. What "+
          "a shame you do not know the value of impulse control.");

      add_ask("'aclolthayr'", VBFC_ME("aclo_ask"));
      add_ask(({"task", "job", "quest", "serve", "service"}),
          VBFC_ME("give_task"));
      add_ask(({"heal", "heal me", "healing", "help"}), 
          VBFC_ME("heal_ask"));
      add_ask(({"poison", "poisons", "cleanse", "cleanse me"}),
          VBFC_ME("poison_ask"));
      add_ask(({"hizarbin", "omatu", "omatu hizarbin", "father"}), 
          "say He is Omatu Hizarbin, Lord of the Waters, and my father. "+
          "He is also the generous patron of fishermen and sailors.", 1);
      add_ask(({"sachluph", "mother"}),
          "say My mother Sachluph shares the Eleventh hour with her "+
          "consort, my father. She is a great Lady. I learned my "+
          "healing arts from her.", 1);
      add_ask(({"water", "whirlpool","stream", "pool", "sea" }),
          "say Take care which water you sample without my Father's "+
          "blessing or leave, for you may risk His wrath", 1);
      add_ask(({"cousin", "wrath" }), "say Those who enter the waters "+
          "without leave are doomed to drown. My cousin is one who "+
          "seems to take perverse pleasure in her duty.", 1);
      add_ask(({"blessing", "leave" }), "say If you make an offering "+
          "at Hizarbin's altar, and it is accepted, you will be "+
          "blessed.", 1);
    set_default_answer(VBFC_ME("what_me"));

}

string
my_long()
{
    string  str, poss;
    poss = TO->query_possessive(); 

    if (this_player()->query_gender() == G_MALE)
        str = "She is perhaps the loveliest woman you have ever seen.\n"+
              "She glows with an ethereal beauty that draws mind and\n"+
              "body to her, eclipsing everything else.\n";
    else
        str = "A creature of remarkable physical beauty who\n"+
              "repels you on a level you do not understand.\n";
    return str +"Her eyes are the gray-green of sea moss.\nHer "+
          "long dark hair clings to her torso, streaming water.\n"+
          "Fine, wavy blue lines are tattooed on her eyelids.\n";
//          "She is wearing a translucent, fringed shawl.\n";
}

/* **** add_ask answers, including quest assignment, if any **** */
string 
aclo_ask()
{
    if (!CAN_SEE(TO, TP))
    {
        command("shout Show thyself to me, or I shall seek "+
            "you when next you enter the waters of Sybarus!");
        return "";
    }
    command("say to "+ TP->query_real_name() +
        " Aclolthayr is the patron goddess of the Hunt. How is it "+
        "that you come to be here without knowing this?");
        return "";

}
          
string
what_me()
{
    if (!CAN_SEE(TO, TP))
        return "";

    if (this_player()->query_gender() == G_MALE)
    {
        switch (random(3))
        {
            case 0:
            {
                tell_room(ENV(TO), QCTNAME(TO) +"'s grey-green eyes "+
                    "are tinged with disappointment and sadness as "+
                    "she looks at "+ QCTNAME(TP) + ".\n", TP);
                TP->catch_msg(QCTNAME(TO) +"'s enchanting grey-green "+
                    "eyes are tinged with disappointment and sadness "+
                    "as she looks at you.\n");
            }
            break;
            case 1:
                command("whisper to "+  TP->query_real_name() +" If you "+
                    "do not know already, then perhaps the answer "+
                     "is beyond your comprehension.");
                break;
            case 2:
                command("say to "+  TP->query_real_name() +
                    " I had hopes you had more intelligence than other "+
                    "males of my experience. What a pity.");
                break;
        }
        return "";
    }
    switch (random(3))
    {
        case 0:
            command("ask "+ TP->query_real_name() +
                " Like all mortal women, you ask the wrong questions. "+
                "Do you not understand the perfect uselessness of "+
                "knowing the right answers to the wrong questions?");
            break;
        case 1:
            command("whisper to "+ TP->query_real_name() +" "+
               "I would tell you, but then it would rob you of the "+
               "satisfaction of learning it for yourself.");
            break;
        case 2:
            command("whisper to "+ TP->query_real_name() +" "+
                "There are some questions whose answers come when "+
                "the asker is ready.");
            break;
    }    
    return "";
}

string
give_task()
{
    command("sigh");
    command("say to "+ TP->query_real_name() +
        " You are not worthy of serving me...Yet.");
    return "";

}

string
heal_ask()
{
    if (objectp(query_attack()))
    {
        command("whisper to "+ TP->query_real_name() +" "+
            "I cannot concentrate upon healing when I'm fighting "+
            "for my life!");
        return "";
    }
    command("whisper to "+ TP->query_real_name() +" "+
        "Give me something and I will heal you in proportion to "+
        "its value. The higher the value, the better the healing.");
    command("whisper to "+ TP->query_real_name() +" "+ 
        "I will give you the gift of healing just the once, though, "+
        "so choose your item well.");
    return "";
}
    
string
poison_ask()
{
    if (objectp(query_attack()))
    {
        command("whisper to "+ TP->query_real_name() +" "+
            "I cannot concentrate upon healing when I'm fighting "+
            "for my life!");
        return "";
    }
    command("whisper to "+ TP->query_real_name() +" "+
        "I have not the talent for cleaning poisons. All I can do "+
        "is treat the symptoms.");
    return "";
}

void
not_desired(object obj, object from) 
{
    command("say This thing is hardly worth bothering about.");
    command("say You're wasting my time.");
    command("give "+ obj->query_name() +" to "+ OB_NAME(from));
    return;
}

void
too_tired(object obj, object from) 
{
    command("say I'm terribly sorry, but I'm too exhausted to "+
        "do any healing right now.");
    command("give "+ obj->query_name() +" to "+ OB_NAME(from));
    return;
}
    
int
check_heal(object obj, object from)
{
    int val, hp, mana, max_heal, heal;
    string str;

    val = obj->query_prop(OBJ_I_VALUE);
    mana = TO->query_mana();
    max_heal = 250;
    heal = val / 10;

    if (from->query_prop(CHECK_PROP))
    {
        command("say to "+ from->query_real_name() +" I've healed "+
            "you once already!");
        command("drop "+ obj->query_name());
        return 1;
    }

    if (heal > max_heal)
        heal = max_heal;

    if ((heal * 2) > mana)
    {
        command("say to "+ from->query_real_name() +" "+
            "I am a bit tired, but I will do my best "+
            "to heal you in a manner commensurate with the "+
            "value of this "+ obj->query_short());
        heal = mana / 2;
    }

    if (heal > 200)
        str = "a whole lot better";    
    if (heal > 150)
        str = "much better";
    if (heal > 100)
        str = "quite a bit better";
    if (heal > 50)
        str = "significantly better";
    if (heal > 0)
        str = "just the tiniest bit better";

    command("emote chants some words in an archaic language.");
    tell_room(ENV(TO), "As each word falls from her lips it forms "+
        "a rune in the air before you, then rapidly dissipates.\n"+
        QCTNAME(TO) +"'s hands begin to glow with a blue-green "+ 
        "light.\n");
    tell_room(ENV(TO), QCTNAME(TO) +" places her glowing hands "+
        "upon "+ QCTNAME(from) +"'s head.\nThe glowing blue-green "+
        "light seems to ripple down over "+ from->query_possessive()+
        " entire body, from head to toe.\n", TP);
    from->catch_msg(QCTNAME(TO) +" places her glowing hands upon "+
        "your head.\nAn incredible warmth flows over and through "+
        "you, and you think you feel "+ str +".\n");

    hp = from->query_max_hp() - from->query_hp();
    SCROLLING_LOG(HEAL_LOG, "Selkie given obj worth ("+ val +") by "+
        from->query_name() +": missing ("+ hp +"), healed ("+ heal +").");
    STATSERV_LOG_EVENT("holm", "Healed by Erinys");
    TO->heal_mana(-(heal * 2));
    from->add_prop(CHECK_PROP, 1);
    from->heal_hp(heal);    
    obj->remove_object();
}

public void
enter_inv(object obj, object from)
{ 
    int val, mana;
    ::enter_inv(obj, from);

    if (!living(from))
        return;

    if (obj->query_prop(OBJ_I_BROKEN))
    {
        set_alarm(2.0, 0.0, &not_desired(obj, from));
        return;
    }

    val = obj->query_prop(OBJ_I_VALUE);
    if (val < 150)
    {
        set_alarm(2.0, 0.0, &not_desired(obj, from));
        return;
    }

    mana = TO->query_mana();
    if (mana < 100)
        set_alarm(2.0, 0.0, &too_tired(obj, from));
    else
        set_alarm(2.0, 0.0, &check_heal(obj, from));
}

              
/* **************** Used in Special Attack function  *************** */
int
call_mist()
{
    object mist;
    if (!present("black_mist", environment(TO)))
    {
        command("emote raises her hands in the air and looks "+
           "out to sea.");
        command("emote chants some words in an archaic language.");
        tell_room(ENV(TO), "As each word falls from her lips it "+
            "forms a glowing rune in the air before you, then "+
            "rapidly dissipates.\nA black mist rises from the "+
            "surface of the dark sea and rolls swiftly in, "+
            "obscuring your sight.\n");
        mist = clone_object(HOLM_OBJ +"black_mist");
        mist->set_timer(40 + (random(20)));
        mist->move(ENV(TO), 1);
    }
    return 1;
}
    


/* ***************** Punch attack ******************* */
void
scratch_em(object victim)
{

    // Choose power of hit based on mob stat size.
    mixed* hitresult = do_stat_based_attack(TO, victim, W_SLASH);
	
	// The attack was evaded
	if (intp(hitresult))
		return;

    int how;
    string *randhit = ({"face", "nose", "hand", "wrist"});
    mixed where;

    how = (random(sizeof(randhit)));    
    where = randhit[how];

    victim->catch_msg(QCTNAME(TO)+" lunges under your guard and "+
        "scratches you viciously on the " + where +" with her "+
        "fingernails.\n");
    tell_room(ENV(TO), QCTNAME(TO)+" lunges under "+ QCTNAME(victim) + 
        "'s guard and scratches "+ victim->query_objective() +
        " visciously on the " + where +" with her fingernails.\n", 
        victim);
}


int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	return 1;
    }

    switch (random(8))
    {
        case 0: scratch_em(victim);
            return 1;
        case 1: scratch_em(victim);
            return 1;
        case 2: call_mist();
            return 0;
        default: 
    }
    return 0;
}

void
check_meet(object tp)
{
    if (!present(tp, environment(TO)))
        return;

    if (IS_SYBARITE(tp) && tp->query_gender() == G_FEMALE)
    {
        switch(random(3))
        {
            case 0:
                command("say to "+ tp->query_real_name() +" "+
                    "Welcome, sister!");
                break;
            case 1:
                command("ask "+ tp->query_real_name() +" "+
                    "How does your Hunt fare this day?");
                break;
            case 2:
            {
                command("say to "+ tp->query_real_name() +" "+
                    "Jazur and Sisera have blessed you with grace "+
                    "and beauty.");
                command("smile at "+ tp->query_real_name());
            }
            break;
        }     
        return;
    }
    if (IS_SYBARITE(tp) && tp->query_gender() == G_MALE)
    {
        switch(random(3))
        {
            case 0:
                command("say to "+ tp->query_real_name() +" "+
                    "What a fine specimen of Sybarite manhood "+
                    "you are!");
                
                break;
            case 1:
                command("whisper to "+ tp->query_real_name() +" "+
                    "You make my heart flutter in my bosom.");
                break;
            case 2:
            {
                command("ask "+ tp->query_real_name() +" "+
                    "Would you follow me into the depths of the Sea "+
                    "if I promised you eternal happiness and life?");
                command("smile at "+ tp->query_real_name());
            }
            break;
        }     
        return;
    }
    if (tp->query_gender() == G_MALE)
    {
        switch(random(3))
        {
            case 0:
                command("smile sedu at "+ tp->query_real_name());
                break;
            case 1:
                command("ask "+ tp->query_real_name() +" "+
                    "I've heard that men from your land are quite "+
                    "virile. Is this true?");
                break;
            case 2:
                command("whisper to "+ tp->query_real_name() +" "+
                    "Serve the Gods in all you do, or die!");
                break;
        }
        return;
    }
}

void
init_living()
{
    ::init_living();

    if (interactive(TP) &&
        CAN_SEE(TO, TP))
	set_alarm(3.0, 0.0, &check_meet(TP));
}  

string race_sound()
{
    string  *sounds = ({ "croons", "speaks mellifluously", "sighs" });
    return sounds[random(sizeof(sounds))];
}

void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    object shawl;
    string *killers;

    if (query_hp() > 0)
        return 0;

    if (!killer)
        killer = previous_object();

    if (killer && ENV(TO) == environment(killer)) 
    {
        command("say You have driven me from my favorite perch!");
        command("say When I have healed I shall return to see "+
            "my Father's vengeance wrecked upon thee!");
    }
    tell_room(ENV(TO), QCTNAME(TO) + " launches herself into the "+
        "air and changes to a seal-like shape before your very "+
        "eyes!\nShe makes a graceful, twisting dive into the dark "+
        "water of the sea and disappears from view.\n");

    shawl = clone_unique("/d/Avenir/common/holm/obj/sea_shawl", 7,
        "/d/Genesis/gems/obj/pearl_black", 1, 30);
 
    shawl->move(ENV(TO));        


    STATSERV_LOG_EVENT("holm", "Erinys killed");
    ::do_die(killer);
}
