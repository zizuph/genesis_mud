// file name:     ~Avenir/common/clubs/mummer/nygel.c
// creator(s):     Lilith Aug 1997
// last update:   
// purpose:       To provide 'colour' for Bazaar
// note:          The 'guild npc' for the Mummers of Sybarus,
//                a male-only street performers club.
// bug(s):
// to-do:                  

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/log_asks";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/clubs/mummer/mummer_club.h"
#include <macros.h>

#define L(str)  lower_case(str)
#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

string my_long();
int initiation(string str);
int expulsion(string str);
int restoration(string str);

string
thief_fun(object thief, object victim, object ob)
{
    set_alarm(1.0, 0.0, &command("glare angril "+
          thief->query_real_name()));
    set_alarm(3.0, 0.0, &command("say Now what "
         +"exactly are you trying to steal?"));
}

void
create_monster() 
{
    if (!IS_CLONE)
        return;

    set_name("nygel");    
    set_living_name("nygel");
    add_name(({"mummer", "man", "performer", "male"}));
    set_race_name("human");
    set_adj(({"entertaining", "dark-eyed"}));
    set_title("icu Atrei, the Mummer of Sybarus");
    set_long(my_long);

    set_gender(G_MALE);
    set_aggressive(0);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop("_live_m_attack_thief", "thief_fun");
    add_prop(CONT_I_WEIGHT, 50000);
    set_stats(({60, 75, 60, 50, 50, 40}));
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_CLUB, 40);
    set_alignment(0);

    set_act_time(4);
    add_act("mtip");
    add_act("flex");
    add_act("mcap");
    add_act("mflip");
    add_act("bow");
    add_act("dance all");
    add_act("msleeve");
    add_act("mstand");
    add_act("mtoe feathers");
    add_act("say Would you like to see me perform?");
    add_act("say Did you hear the one about the Seer, the Inquisitor "+
        "and the Shadow Warrior?");
    add_act("@@do_crowd@@");

    set_default_answer(VBFC_ME("what_me"));
    add_ask(({"city","forbidden city"}),
         "say The Forbidden City is the island where the Shadow Elves "+
         "live. It is a marvellous place. For those permitted to enter, "+
         "it is a great honour.",1);
    add_ask(({"zuggarat", "zugarat", "ziggurat", "pleasure palace"}),
         "say It is the Pleasure Palace at the center of the Forbidden City. "+
         "It is the place where every fantasy can be fulfilled..."+
         "for a price.", 1);
    add_ask(({"mummer", "mummers", "perform"}),
         "say I am a mummer of Sybarus. I can teach you my trade.", 1);
    add_ask(({"teach trade", "trade", "teach me", "teach"}),
         "say If you want me to teach you to be a Mummer, just type "+
         "<teach me>.", 1);
    add_ask(({"leave", "leave mummers", "leave club", "how to leave" }),
         "say If you want to leave the Mummer's of Sybarus, just "+
         "type <return cap>.", 1);
    add_ask(({"update membership", "restore", "restore me" }),
         "say If you need to update your membership in the Mummers of "+
         "Sybarus, just type <restore me>.", 1);
       
}

void
equip_me()
{
    object cloak, shirt, pants;
    seteuid(getuid()); 
    clone_object(GUILDOBJ)->move(this_object());
    cloak = clone_object(OBJ + "worn/mencloaks");
    cloak->create_tailored();
    cloak->move(this_object());
    shirt = clone_object(OBJ + "worn/menshirts");
    shirt->create_tailored();
    shirt->move(this_object());
    pants = clone_object(OBJ + "worn/menpants");
    pants->create_tailored();
    pants->move(this_object());
    clone_object("/d/Avenir/common/obj/feather")->move(this_object());
    clone_object("/d/Avenir/common/obj/feather")->move(this_object());
    clone_object("/d/Avenir/common/obj/feather")->move(this_object());
    clone_object("/d/Avenir/common/obj/feather")->move(this_object());
    clone_object(OBJ + "worn/pouch_belt")->move(this_object());
    command("wear all"); 
}                

void
do_crowd()
{
    command("emote peeks into his money pouch.");
    command("say Tough crowd today.");
}

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

    str += "He is quite the entertaining fellow, with the accoutre"+
         "ments of his mummer's trade swinging from his belt.\n"+
         "His dark orangy hair spikes out in all "+
         "directions from beneath his cap.\n"+
         "His dark eyes are sparkling merrily at you.\n";
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

    switch(random(4))
    {
        case 0:
        { 
            command("shrug sadly");
            command("say I am really just a simple mummer.");
            break;        
        }
        case 1:
        {
            command("say I have no idea. Truly.");
            command("shrug .");
            break;
        }
        case 2:
        {
            command("emote suddenly looks fearful.");
            command("say Go away, please.");
            break;
        }
    }
    return "";    
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
    if (!from)
        return;
 
    set_alarm(1.5,0.0,&command("thank " + from->QRN));
}

string 
query_exp_title()
{
    return "Sybarite";
}

/*
 * Function name: return_grope
 * Description  : When the NPC is groped, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_grope(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("frown");
    command("say to " + OB_NAME(actor) +" Just what kind of a "+
        "performer do you think I am?");
}

/*
 * Function name: return_poke
 * Description  : When the NPC is poked, this function is called after
 *                a small delay to give a reaction.
 * Arguments    : object actor  - the person acting on the NPC.
 *                string adverb - the possible adverb, in this function not
 *                                used.
 */
void
return_hug(object actor, string adverb)
{
    /* Player is no longer in the room with us, or even no longer in the
     * game.
     */
    if (!objectp(actor) ||
	(environment(actor) != environment()))
    {
	return;
    }

    /* Do the stuff. */
    command("mflip "+ OB_NAME(actor));
    command("say Thank you! That warms my heart.");
}

/*
 * Function name: emote_hook
 * Description  : This hook is called whenever an emotion is performed on this
 *                NPC. If it is an emotion that we hook on, call a little
 *                alarm and then call the return function.
 * Arguments    : string emote  - the emotion performed.
 *                object actor  - the actor of the emotion.
 *                string adverb - the adverb used in the emotion.
 */
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
        case "french":
        case "lick":
        set_alarm(3.0, 0.0, &return_grope(actor, adverb) );
	  return;

        case "hug":
        case "kiss":
        case "dance":
        case "squeeze":
        case "cuddle":
        case "applaud":
        case "clap":
        case "admire":
        case "cheer":
	    set_alarm(3.0, 0.0, &return_hug(actor, adverb) );
        return;
    }
}

int
initiation(string str)
{
    object cap;
  
    NF("Teach who?\n");
    if (str != "me") 
        return 0;

    if (!TP->query_wiz_level() && 
       (TP->query_gender() == G_FEMALE))
    {
        command("say We only train males in this trade.");
        return 0;
    }

    if (objectp(cap = present(MUMMER_CAP, TP))) 
    {
        command("say You are a mummer already!\n");
        return 1;
    }

    if (QRACE(TP) == "hobbit") 
    {
        command("say You say you're a hobbit, but 'hobbits' no "+
            "longer exist.");
        command("say You're a deformed dwarf, I think.");
        command("say It looks like your deformity won't interfere "+
            "with your ability to be a good mummer, though.");
    }

    write("You have been accepted as a Mummer of Sybarus.\n");    
    SCROLLING_LOG(MUMMER_LOG, capitalize(TP->query_real_name())+ 
        " ("+ TP->query_race() +") became a Mummer.");
    clone_object(GUILDOBJ)->move(TP,1);
    write("Nygel gives you a Mummer's cap.\n");
    say(QCTNAME(TO) +" gives "+ QCTNAME(TP) +" a Mummer's cap.\n");
    TP->set_skill(MUMMER_SKILL, 1);
    return 1;
}

int
expulsion(string str)
{
    object cap;
    string name;
  
    NF("Return what?\n");
    if (!str || str != "cap") 
    return 0;

    cap = present(MUMMER_CAP, TP);
    if (TP->query_wiz_level())
    {
        write("You'll have to remove the cmdsoul manually.\n");
        if (objectp(cap)) 
            cap->remove_object();
        return 1;
    }        
    // does not work for wizards 
    if (!TP->remove_cmdsoul(MUMMER_SOUL)) 
    {
        if (objectp(cap)) 
            cap->remove_object();
        write("It doesn't seem you were a member anyway.\n");
        return 1;
    }
    else 
    {
        write("Nygel says to you: Pity! Well, you're welcome back any time.\n");
        cap = present(MUMMER_CAP, TP);
        if (objectp(cap)) 
        {
            cap->remove_object();
            write("You give the mummer's cap to Nygel.\n");
            say(QCTNAME(TP) + " is no longer a Mummer of Sybarus.\n");
            SCROLLING_LOG(MUMMER_LOG, capitalize(TP->query_real_name())+ 
                " returned his cap. <--");
        }

        // Do this just in case something goes wrong with the leave_env
        // in the cap. Want to make sure player m_in is reset.
        if (!TP->query_wiz_level())
            TP->set_m_in("arrives.");
        TP->remove_skill(MUMMER_SKILL);
        TP->update_hooks();
        return 1;
    }
}

int
restoration(string str)
{
    object cap;

    if (!str || str != "me" ) 
    {
        NF("Restore whom?\n");
        return 0;   
    } 
     

    cap = present(MUMMER_CAP, TP);
    if (!objectp(cap)) 
    {
        clone_object(GUILDOBJ)->move(TP,1);
        write("Nygel gives you a mummer's cap.\n");
    }

    command("You should have everything you need now.\n");
    return 1;       
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i;
    i = random(6);

    if (!present(tp, environment(TO)))
        return;

    if (tp->query_met(query_real_name()))
    {
        if (i = 0)
        {
            command("nod hap at "+ tp->query_name());           
            return;
        }
        if (i = 2)
        {
            command("greet "+ tp->query_name());           
            return;
        }
        if (i = 4)
        {
            command("admire "+ tp->query_name());           
            return;
        }
    }          
    if (i == 1)
    {
        command("introduce myself");
        command("say to "+ tp->query_name() +" Would you like me "+
            "to perform for you?");
        return;
    }
    if (i == 3)
    {
        command("introduce myself");
        return;
    }
    if (i == 5)
    {
        command("introduce myself");
        command("say I'm the best feather-juggler you'll ever see.");
        command("say Shall I demonstrate?");
        return;
    }
}

void
init_living()
{
    ::init_living();

    add_action(initiation, "teach");
    add_action(expulsion, "return");
    add_action(restoration, "restore");

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        set_alarm(2.0, 0.0, &check_meet(TP));
        return;
    }
}
