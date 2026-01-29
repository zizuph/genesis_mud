/*
 * The standard file for the guards of Helm's Deep
 *
 * March 1994 by Arren
 * The guards were first made in June 93, but are now modified
 * to inherit this file.
 *
 * changed to use show_hook()
 * -- gnadnar 11-nov-97
 *
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */

inherit "/std/monster";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/common/lib/logkill.c"

#undef WEP_DIR
#define WEP_DIR ROH_DIR + "horn/obj/"
#define WEP1 ROH_DIR + "horn/obj/long_sword"
#define WEP_ARRAY ({ "longspear", "fauchard", "m_fork", "glaive" })
#define ARM1 ROH_DIR + "edoras/obj/roshield"
#define ARM2 ROH_DIR + "horn/obj/b_coat_mail"
#define ARM3 ROH_DIR + "edoras/obj/rohelm"
#define ARM4 ROH_DIR + "horn/obj/mail_leggings"


public string	long_desc();
public string	give_func();

static  string  extra_desc;
static  int     guard_type;

void 
set_extra_desc(string x)
{
    extra_desc = x;
}

void 
set_guard_type(int i)
{
    guard_type = i;
}

void
create_monster()
{
    if (!IS_CLONE)
        return;
    set_name("guard");
    add_name("man");
    set_race_name("human");
    set_adj(({"tall", "Rohirrim"}));
    set_long(long_desc);
    set_pshort("tall Rohirrim guards");
    set_alignment(250+random(250));
    set_skill(SS_AWARENESS,30);
    set_skill(SS_ANI_HANDL,55);
    add_prop(CONT_I_HEIGHT,190); 
    add_prop(CONT_I_WEIGHT,70000);
    add_prop(CONT_I_VOLUME,70000);
    add_prop(NPC_M_NO_ACCEPT_GIVE, give_func);

    set_chat_time(10);
    add_chat("I hate orcs.");
    add_chat("Saruman is up to no good. I can feel it!");
    add_chat("Orcs are the most vile beasts! All should die!");
    add_chat("Who are you, and what are you doing in this land?");
    add_chat("There is trouble on all of our borders.");
    add_chat("What news from Gondor, stranger?");
    add_chat("Stormcrow is the herald of strange events.");
    add_chat("Plundering Orcs carry off our black horses!");
    add_chat("No foe has ever taken the Hornburg, if men defended it.");
    add_chat("I think I saw a glimpse of an orc on the wall this morning.");

    set_cchat_time(20);
    add_cchat("Intruder! Alert!");
    add_cchat("May your beard grow inwards and choke you!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"about orc", "orc", "about orcs", "orcs"}),VBFC_ME("ask_orc"));
    trig_new("%w 'hear' 'a' 'distant' 'and' 'somewhat' 'muffled' ''clonk'.\n'", 
    "react_clonk");

}

void 
init_living()
{
    ::init_living();
    add_action("report_orc", "report");
}


int 
react_bored(string who)
{
     set_alarm(1.0, 0.0, "be_bored", who);
     return 1;
}

int 
react_clonk(string who)
{
     set_alarm(1.0, 0.0, "clonk", who);
     return 1;
}

string 
long_desc()
{
    string desc;

    desc = "The Rohirrim guard is tall and long-limbed, with "+
    "long flaxen braids; his face is stern and keen. ";

    if (stringp(extra_desc))
        desc += extra_desc;

    return (desc + "\n");
}

void
arm_me()
{
    object wep, arm;
    object me = TO;

    FIX_EUID

    switch(guard_type)
    {
        case 1 :
            wep = clone_object(WEP_DIR + ONE_OF_LIST(WEP_ARRAY));
            wep->move(me);
            break;
        case 2 :
            wep = clone_object(WEP1);
            wep->move(me);
            arm = clone_object(ARM1);
            arm->move(me);
            break;
        case 3 :
            wep = clone_object(WEP1);
            wep->move(me);
            arm = clone_object(ARM1);
            arm->move(me);
            arm = clone_object(ARM4);
            arm->move(me);
            break;
         default :
            break;
    }

    arm = clone_object(ARM2);
    arm->move(me);
    arm = clone_object(ARM3);
    arm->move(me);
    command("wield all");
    command("wear all");
}

string
default_answer()
{
    return "The tall Rohirrim guard says: I'm on guard duty; don't "+
    "bother me unless you can show me something concerning "+
    "the security of the keep.\n";
}

string
ask_orc()
{
    START_QUEST(TP, "Spying Orc");
    return "The tall Rohirrim guard says: The orcs have become much "+
    "bolder lately. You'd better report to me if you find anything "+
    "suspicious.\n";
}

string 
give_func()
{
     command("say I don't take bribes.");
     command("frown");
     return " looks at you with disdain.\n";
}

/* Solamnian knight prestige */
query_knight_prestige() {return (-6);}

int
check_attack()
{
    object enemy;

    if(enemy = TO->query_attack())
    {
        if(enemy == TP)
            TO->command("say You horse-thief! Why should I be interested "+
            "in anything but your death?");
        else
            TO->command("say Help me kill this horse-thief instead!");
        return 0;
    }
    else 
        return 1;
}

public void
init_attack()
{
    if(query_attack()) return;
    if (IS_EVIL(TP))
    {
      set_alarm(2.0, 0.0, "do_attack", TP);
    }
} 

do_attack(object victim)
{
    if(query_attack()) return;
    if (!present(victim,ENV(TP))) return;
    command("kill "+victim->query_real_name());
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO, ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
    set_alarm(5.0, 0.0, "help_friend", attacker);
}
  
/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say Die, foul creature!");
        command("kill " + lower_case(ob->query_real_name()));
    }
}

int 
be_bored(string who)
{
     command("say Yes, yes.");
     command("yawn");
     return 0;
}

void 
give_horn(object discoverer)
{
     object horn;

     command("say You have found an orc spy!");
     command("say Unfortunately all our trackers are at River Isen.");
     command("say So please, help us to find him.");
     command("say Take this horn and blow it when you have found "+
     "his hide out.");
     if (!present("_helmsdeep_horn", discoverer))
     {
         discoverer->catch_msg(QCTNAME(TO) + " gives you a horn.\n");
         say(QCTNAME(TO) + " gives " + QTNAME(discoverer) + " a horn.\n");
         horn = clone_object(ROH_DIR + "horn/obj/horn");
         horn->add_name("_helmsdeep_horn");
         horn->move(discoverer);
     }
}

/*
 * Function name: show_hook
 * Description  : This hook is called whenever an item is 'shown' to this
 *                living. It is shown by this_player().
 * Arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    object discoverer = TP;

    if ( ENV(discoverer) != ENV(TO) || !objectp(ob) )
        return;

    if ( !ob->id("horse-lovers-map") && !ob->id("_helmsdeep_map") )
    {
    	command("say I'm on guard duty.");
	command("say Don't bother me unless you can show me something concerning "+
	    "the security of the keep.");
	return;
    }

    if (discoverer->test_bit("Gondor", GONDOR_GROUP, SPYING_ORC_BIT))
    {
        command("say Haven't we done this before!?!");
        return;
    }

    if (!check_attack())
        return;	/* msgs written in check_attack() */

    if(discoverer->query_prop(FOUND_ORC))
    {
        TP->add_prop(SHOWN_MAP, 1);
        if(discoverer->query_prop(MADE_REPORT))
            give_horn(discoverer);
        else
        {
            command("say You'd better report how you found this map.");
        }
    }
    else
    {
        command("say Yes, yes. That was a nice map.");
    }
    command("say We don't want maps of our fortress to circulate.");
    command("say Our enemies can use them against us.");
    command("say So I will take care of that map.");
    tell_room(ENV(TO), QCTNAME(TO) + " takes the map.\n");
    ob->remove_object();
    return 0;
}

int 
report_orc(string str)
{
    string dummy;

    if (TP->test_bit("Gondor", 1, 11))
    {
        command("say Haven't we done this before!?!");
        return 0;
    }

    if (!check_attack())
         return 1;
    if(!str)
    {
        NF("Report what?\n");
        return 0;
    }
    str = LOW(str);
    if((sscanf(str, "%sorc%s", dummy, dummy) > 0) || 
       (sscanf(str, "%sspy%s", dummy, dummy) > 0) )
    {
        if(TP->query_prop(FOUND_ORC))
        {
            TP->add_prop(MADE_REPORT, 1);
            if(TP->query_prop(SHOWN_MAP))
                give_horn(TP);
            else
            {
                command("say So you claim to have seen an orc here?");
                command("say I can't do anything unless you show me some "+
                "evidence.");
            }
        }
        else
        {
            command("say So you claim to have seen an orc in Helm's Deep?");
            command("say Somehow I don't trust you!");
            command("say You must find some evidence first.");
            return 1;
         }
    }
    else
    {
        command("say I don't understand what you are trying to report.");
        command("ponder");
    }
    return 1;
}

int 
clonk(string who)
{
    command("emote peers suspiciously around.");
    return 1;
}
