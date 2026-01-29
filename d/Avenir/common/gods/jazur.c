//-*-C++-*-
// file name:    /d/Avenir/common/gods/jazur.c
// creator(s):   Lilith July 2004, based on Hizarbin
// revised:      Lilith Sep 1997:  Changes to prevent runtime errors.
// purpose:      
// note:                  
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

#include <ss_types.h>
#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"

#define DAMAGE    (query_max_hp() / 3)
#define HQRN(h)   h->query_real_name()

#define MOODS        5
#define MAGNANIMOUS  0
#define GOOD         1
#define INDIFFERENT  2
#define BAD          3
#define FURIOUS      4

int alarm_id, 
    mood;
string l_mood;
object shawl;
void set_shawl(object ob)  {    shawl = ob;     }  
void start_it();
string threat();
object query_haunted();

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("jazur");
    set_living_name("jazur");
    set_title("the Regent of the Twelfth Hour, Mistress of Passion");
    add_name(({"god", "lady", "goddess", "spirit being","avatar", 
        "mistress", "regent"}));
    set_adj("flame-wreathed");
    set_race_name("goddess");
    set_gender(G_FEMALE);
    set_long("@@my_long@@");
    set_stats(({160,160,160,140,140,150}));
 
    set_alignment(0);
    set_m_in("glides in");
    set_m_out("glides");
    set_mm_in("appears before you.");
    set_mm_out("simply disappears.");
    
    set_all_hitloc_unarmed(5);
    set_all_attack_unarmed(20, 11);
 
    set_skill(SS_DEFENCE, 30);
    set_skill(SS_WEP_CLUB, 50);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_default_answer(VBFC_ME("what_me"));

    MAKE_SYBARITE;    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(OBJ_I_LIGHT, 10);
    add_prop(OBJ_M_NO_ATTACK, "Uhmm...you don't have the intestinal "+
        "fortitude to do that!\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "Your pathetic magicks will not "+
        "prevail against her!\n");
    add_prop(LIVE_I_SEE_INVIS, 100);
    add_prop(LIVE_I_SEE_DARK, 100);
    
    set_chat_time(2);
    add_chat("@@threat");
    set_act_time(4);
    add_act("@@hurt_haunted");
    add_act("@@get_shawl");

    start_it();   

    seteuid(getuid(TO));

}

string
what_me()
{
    command("say Do not presume to ask me questions. I will not "+
        "answer them.");
    return "";
}

string 
query_exp_title()
{
   return "avatar";
}

string
my_long()
{
    string  str;

    str = "She is "+ LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    if (TP->query_met(query_real_name()))
    {
        str = query_name() +" is "+ LANG_ADDART(implode(query_adjs()," ")) 
            + " "+ query_race_name() +", presenting herself as:\n" 
            + query_name();
        if (strlen(query_title()))
            str += " "+ query_title() +",";
        str += " "+ query_exp_title() +", female "+ query_race_name() +".\n";
    }

     str += "She is wreathed in blue-black flames that flicker "+
            "enticingly at you.\n"+
            "Her hair is long and flowing, restrained only by the "+
            "circlet from which a small black sphere dangles "+
            "across her brow.\n"+
            "She is wearing a thin robe over an undeniably feminine "+
            "form.\n"+
            "She is wearing an ornate mekhala belted around her hips.\n"+
            "Her dark eyes are heavy-lided, lending her a deceptively "+
            "langorous air.\n"+
            "She looks like she is "+ l_mood +".\n";
    return str;
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
     return 1;
}
/*
void
end_it()
{
    object *people;    

    people = filter(all_inventory(ENV(TO)), interactive);  
    if (people)
    {
        command("say Enough! I will take what is mine!");
        command("introduce me");
        command("say Live in fear of my next visit, mortal!");
        command("emote points a finger at you and hooks it.");
        command("emote laughs as pain explodes inside your gut "+
            "and your own urine streams hotly down your leg.");
        people->heal_hp(-500);
        people->add_panic(500);
        people->run_away();
    }
    shawl->remove_object();
    remove_alarm(alarm_id);
    set_alarm(2.0, 0.0, &remove_object());
}
*/
void 
start_it()
{
    mood = random(MOODS);
    switch (mood)
    {
        case MAGNANIMOUS:
        {
            l_mood = "feeling very magnanimous";
        }
        case GOOD:
        {
            l_mood = "in a good mood";
        }     
        case INDIFFERENT:
        {
            l_mood = "indifferent towards you";
        }
        case BAD:
        {
            l_mood = "in a foul mood";
        }
        case FURIOUS:
        {
            l_mood = "extremely angry";
        }
    }

/*   
    int i;
    i = random(200) + 1800;
    alarm_id = set_alarm(itof(i), 0.0, end_it);
*/
}
void
move_to_haunted(object haunted)
{

    if (!present(haunted, environment(TO)))
    {
        if (haunted->query_prop(ROOM_I_IS))
            move_living("X", haunted);  
        else
            move_living("X", environment(haunted));
    }
}

void
get_shawl()
{
    object haunted = environment(shawl);

    if (present(shawl, environment(TO)))
    {
        set_alarm(2.0, 0.0 ,&command("get shawl"));
        return;
    }
    if (present("corpse", environment(TO)))
    {
        set_alarm(2.0, 0.0 ,&command("get shawl from corpse"));
        return;
    }
    if (present(haunted, environment(TO)))
    {
        if (living(haunted))
        {
            threat();
            return;
        }
        if (haunted->query_prop(CONT_I_CLOSED))
        {
            command("open "+ haunted->short());
            command("get shawl from "+ haunted->short());
            return;
        }
        else
        if (!command("get shawl from "+ haunted->short()))
            command("get "+ haunted->query_name());
        return;
    } 
    move_to_haunted(query_haunted());
    return;
}


string
threat()
{
    object haunted = query_haunted();
    if (!shawl)
    {
        remove_object();
        return "";
    }

    if (!haunted)
    {
        move_living("X", (environment(shawl)));
        get_shawl();
        return "";
    }

    move_to_haunted(query_haunted());

    switch (random(7))
    {
        case 0:
            add_chat("I have come for my daughter's shawl.");
            break;
        case 1:
            add_chat(" to "+ HQRN(haunted) +" It would not be wise to "+
                "disobey Me.");
            break;
        case 2:
            add_chat("T'would be a simple thing to "+
               "fill your lungs with water and watch you drown.");
            break;
        case 3:
            add_chat("I am a fair god, young one. I "+
                "do not delight in torment. But do not push Me.");
            break;
        case 4:
             add_chat(" to "+ HQRN(haunted) +" You have much to learn about the "+
                "Gods of Sybarus, if you think you can deny Me!");
            break;
        case 5:
            add_chat("Give Me the shawl...or die!");
            break;
        case 6:
            add_chat("Would you rather I took the shawl "+
                "from your corpse?");
            break;
        default:
            add_chat("The shawl. Now!");
            break;            
    }
    return "";
}     

void
hurt_haunted()
{
    object victim;
    victim = query_haunted();
    
    if (!present(victim, environment(TO)))
    {
        move_to_haunted(victim);
        return;
    }

    switch (random(3))
    {
        case 0:
        {
            victim->catch_msg(QCTNAME(TO) +" points a finger at you "+
                "menacingly.\nYou feel and intense, twisting pain "+
                "deep within your abdomen.\nOooohhh the pain!\n");
            tell_room(ENV(TO), QCTNAME(TO)+" points a finger menac" + 
                "ingly at "+ QCTNAME(victim) + ", whose face suddenly "+
                "contorts as though "+ PRONOUN(victim) +" is in "+
                "horrible pain!\n", victim);
            victim->heal_hp(-DAMAGE);
            if ((victim->query_hp() <= 0) && (!victim->query_ghost()))
                victim->do_die(TO);
            break;
        }
        case 1:
        {
            victim->catch_msg(QCTNAME(TO) +" extends a hand toward "+
                "you, then forms a fist with it.\nYour heart beats "+
                "frantically within your chest, then slows.\nYou feel "+
                "quite faint, as though you have lost a lot of blood.\n");
            tell_room(ENV(TO), QCTNAME(TO)+" extends a hand toward " + 
                QCTNAME(victim) +", then forms a fist with it.\n "+
                QCTNAME(victim) +" clutches at "+ POSSESS(victim) +
                " chest and looses all colour in "+ POSSESS(victim) +
                " face!\n",victim);
            victim->heal_hp(-DAMAGE);
            if ((victim->query_hp() <= 0) && (!victim->query_ghost()))
                victim->do_die(TO);
            break;          
         }
         case 2:
         {
            victim->catch_msg(QCTNAME(TO) +" claps his hands together"+
                ".\nYou fall to your knees as you are striken with "+
                "tremendous pain in your head, as though "+
                "it has been caught in a vise!\n");
            tell_room(ENV(TO), QCTNAME(TO)+" claps his hands together.\n" + 
                QCTNAME(victim) +" falls to "+ POSSESS(victim) +
                " knees and moans piteously.\n", victim);
            victim->heal_hp(-DAMAGE);
            if ((victim->query_hp() <= 0) && (!victim->query_ghost()))
                victim->do_die(TO);
            break;
        }
    } 
    return;
}

int
do_item_filter(object ob)
{
    if (!ob->id("sea_shawl"))
        return 0;
    else
       return 1;
}

void
check_shawl(object tp)
{
    object *ashawl;
    object haunted = query_haunted();

    if (!present(tp, environment(TO)))
        return;

    ashawl = filter(all_inventory(tp), do_item_filter);
    if (!sizeof(ashawl))
        return;

    set_follow(HQRN(tp));
    switch(random(3))
    {
        case 0:
            command("say to "+ HQRN(haunted) +" I have come for the shawl "+
                "of Erinys.");
            break;
        case 1:
            command("say to "+ HQRN(haunted) +" Return the shawl to me, or die!");
            break;
        case 2:
            command("say to "+ HQRN(haunted) +" However it is that you came "+
                "by that shawl, it is not yours. Give it to me.");
            break;
    }
    return;
}
                            
public void
init_living()
{
    ::init_living();
    if (interactive(TP))
        set_alarm(1.0, 0.0, &check_shawl(TP));
} 

void
no_thanks(object obj,object from) 
{
    command("say Gifts should be offered at one of my altars.");
    command("give "+ obj->query_name() + " to " + from->query_real_name());
    return;
}

void
remove_me()
{
    object *ashawl;
    object haunted = query_haunted();

    ashawl = filter(deep_inventory(this_object()), do_item_filter);
    if (!sizeof(ashawl))
    {
        move_to_haunted(haunted);
        return;
    }
    tell_room(environment(this_object()),  QCTNAME(TO) +" becomes a "+
        "pulsing ball of water that suddenly explodes, showering you "+
        "with a hundred tiny droplets.\n");
    remove_object();
}

object
query_haunted()
{
    object haunted;
   
    if (!shawl)
    {
        remove_object();
        return 0;
    }

    haunted = environment(shawl);
    if (haunted->query_prop(ROOM_I_IS))
    {
        move_to_haunted(haunted);
    }        

    // He might have it in sack; in sack which is in sack, etc...
    while (haunted && (!living(haunted)))
        haunted = environment(haunted);

   // Note!!! it might return 0! 
   return haunted;
}
    
public void
enter_inv(object obj, object from)
{ 
    object *all;
    int i;

    ::enter_inv(obj, from);

    if (living(from))
    {
        if (obj->id("sea_shawl"))
        {
            command("say to "+ from->query_real_name() +" That was "+
                "wise of you.");
            set_alarm(2.0, 0.0, "remove_me");
            return;
        }
        else
        {
            set_alarm(2.0, 0.0, "no_thanks", obj, from);
            return;
        }
    }
    all = deep_inventory(this_object());
    for (i=0; i<sizeof(all); i++) 
    {
        if (all[i]->id("sea_shawl"))
        set_alarm(2.0, 0.0, "remove_me");
        return;
    }
    if (all[i]->id("sea_shawl"))
        set_alarm(2.0, 0.0, "remove_me");
    return;            
}

void
return_abuse(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    /* Play with Fire, get Burned! */
    command("say to "+ OB_NAME(actor) +" You paltry, pathetic dogcow!");
    actor->catch_msg("You feel a sharp pain behind your eyes.\n"+
        "Suddenly, blood erupts from your nose, spattering the ground.\n");
    tell_room(ENV(TO), "Blood suddenly begins pouring from "+ QCNAME(actor) +
        "'s nose, spattering the ground!\n", actor);
    actor->heal_hp(-DAMAGE);
    if ((actor->query_hp() <= 0) && (!actor->query_ghost()))
        actor->do_die(TO);
}

void
return_dis(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    /* Do the stuff. */
    command("say to "+ OB_NAME(actor) +" If you have no respect for "+
        "beings superior to yourself...");
    command("say to "+ OB_NAME(actor) +" I will be forced to teach "+
        "you.");
}
void
return_respect(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) || (environment(actor) != environment()))
	return;

    /* Do the stuff. */
    command("nod "+ OB_NAME(actor));
    command("say to "+ OB_NAME(actor) +" You are a good child.");
}

void
emote_hook(string emote, object actor, string adverb)
{
    /* See if we want to trigger on the emote. If so, call a little alarm
     * for the reaction function.
     */
    switch(emote)
    {
        case "caress":
        case "grope":
        case "fondle":
        case "lick":
        case "french": 
        case "tickle":
	      set_alarm(3.0, 0.0, &return_dis(actor, adverb) );
            return;
        
        case "poke":
        case "spit":
        case "kick":
        case "slap":
	      set_alarm(3.0, 0.0, &return_abuse(actor, adverb) );
            return;

        case "kiss":
        case "bow":
        case "grovel":
        case "curtsey":
            set_alarm(3.0, 0.0, &return_respect(actor, adverb) );
	      return;
    }
}

string 
race_sound()
{
    return "thunders";
}
