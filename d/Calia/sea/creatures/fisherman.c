
/* 
   Npc fisherman to go in boats on surface of west Calia water area.

   Coded by Maniac, 2/8/96, partially adapted from Archidea's villager. 
 */ 

#pragma save_binary

inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"


#define FISHERMAN_ADJ1 ({ "tall", "short", "stout", "thin",   \
                          "long-legged", "thick-armed", "barrel-chested", \
                          "tanned", "weathered", "square-jawed",  \
                          "large", "young", "middle-aged" }) 

#define FISHERMAN_ADJ2 ({ "dark-haired", "red-haired", "brown-haired",  \
                          "blond-haired", "ginger-haired", "bald",  \
                          "grey-haired", "silver-haired", "blue-eyed", \
                          "green-eyed", "brown-eyed", "black-eyed",  \
                          "yellow-eyed" }) 

#define FISHERMAN_PRE ({ "tor", "mir", "lin", "gan", "tas", \
                         "pel", "bal", "wil", "vi", "ti", "han" }) 

#define FISHERMAN_POST ({ "xeres", "zonet", "ash", "ilath", \
                          "loche", "almer", "rhyl", "ippil", \
                          "ousch", "orren", "dylor", "usade" })

string *react_transfer = 
 ({ "say Hey, stop fingering my stuff!", 
    "say Oi! That's mine!", 
    "say Please put that down!", 
    "emote mutters something about private property.", 
    "grumble unhappily", 
    "frown", 
    "say This isn't finders keepers you know!", 
    "say Hands off!" }); 

string *react_row = 
  ({ "say Please stop that!", 
     "say Do you mind, this is my boat!", 
     "say Hey, I didn't say I wanted a joyride!", 
     "rolleyes", 
     "say Will you leave the oars alone please?", 
     "fume", 
     "say I wish people wouldn't do that!",  
     "say It's hard to do my job with you rowing my boat around!", 
     "despair" }); 

string *battle_emotes = 
    ({ "say May a sea-snake bite your off your ears!", 
       "say I hope you drown!", 
       "say May the great white shark take you!", 
       "say May the Elementals' fury smite you!", 
       "say We are peaceful folk, why do you bring violence here?",  
       "say Don't rock the boat!", 
       "emote looks very scared.", 
       "emote gnaws his nails in fear!", 
       "cry", 
       "whine" }); 


void 
arm_me() 
{
    seteuid(getuid()); 
    clone_object(SEA_ARMOURS+"sandals")->move(this_object());
    clone_object(SEA_ARMOURS+"trousers")->move(this_object());
    clone_object(SEA_WEAPONS+"fishknife")->move(this_object()); 
    command("wear all");
    command("wield all");
    MONEY_MAKE_CC(15 + random(15))->move(this_object());  
}


string
catch_fish()
{
     object e, f;

     e = environment(this_object()); 

     if (!e->query_inside_of_boat()) 
         return "";            

     command("emote hauls a net out of the water, dumps some wriggling " +
             "little fish into the boat, then throws the net back into " +
             "the water."); 
     seteuid(getuid()); 
     f = clone_object(SEA_OBJECTS+"little_fish");  
     f->set_heap_size(1 + random(3));
     f->move(e); 
}

string
fm_default_answer()
{
   command("say Maybe you should ask someone wiser than me about this.");
   return ""; 
}

void 
create_monster() 
{
    string *al1, *al2, *pn1, *pn2;  
    string a1, a2, n1, n2; 
    int slev, lev; 

    al1 = FISHERMAN_ADJ1; 
    al2 = FISHERMAN_ADJ2; 

    a1 = al1[random(sizeof(al1))];  
    a2 = al2[random(sizeof(al2))]; 

    pn1 = FISHERMAN_PRE; 
    pn2 = FISHERMAN_POST; 

    n1 = pn1[random(sizeof(pn1))]; 
    n2 = pn2[random(sizeof(pn2))]; 

    set_name(n1 + "-" + capitalize(n2)); 
    add_name(n1 + "-" + n2); 
    add_name("fisherman");
    set_gender(G_MALE);
    set_adj(({a1, a2}));
    set_race_name("human");
    set_long(capitalize(LANG_ADDART(a1)) + " " + a2 + " human. " +
             "He is one of the fishermen from the coastal village " +
             "nearby. He looks quite peaceful, but nevertheless " +
             "capable of taking care of himself.\n"); 

    set_act_time(2);

    add_act("emote wipes his hands free of fish guts."); 
    add_act("smile warmly"); 
    add_act(VBFC_ME("do_row")); 
    add_act("emote looks up at the sky happily.");
    add_act("emote looks down into the clear sea water."); 
    add_act(({"emote looks out to sea.",
              "say No storms on the horizon, Diabrecho sleeps."}));
    add_act("say Did you see any krougs around here?");
    add_act("say Calians are true friends of ours.");  
    add_act(VBFC_ME("catch_fish")); 

    set_default_answer(VBFC_ME("fm_default_answer")); 

    lev = random(11)+20; 
    slev = lev - 6; 

    set_base_stat(SS_STR, lev); 
    set_base_stat(SS_DEX, lev); 
    set_base_stat(SS_CON, lev); 
    set_base_stat(SS_WIS, lev); 
    set_base_stat(SS_INT, lev); 
    set_base_stat(SS_DIS, lev); 
    heal_hp(query_max_hp());

    set_skill(SS_WEP_KNIFE, slev);
    set_skill(SS_WEP_POLEARM, slev);
    set_skill(SS_PARRY, slev);
    set_skill(SS_DEFENCE, slev);

    set_alignment(random(20) + lev); 

    add_prop(CONT_I_WEIGHT, 65000);
    add_prop(CONT_I_VOLUME, 65000);
    add_prop(NPC_I_NO_RUN_AWAY, 1); 
}


int
special_attack(object victim)
{
    if (!random(6)) 
        command(battle_emotes[random(sizeof(battle_emotes))]); 

    return 0;
}


void
add_introduced(string str)
{
    set_alarm(2.0, 0.0, &command("introduce me")); 
}


void
react_small_neutral(object player)
{
       command("peer " + player->query_real_name()); 
}


void
react_med_neutral(object player)
{
   command("nod . " + player->query_real_name()); 
}


void
react_large_neutral(object player)
{
   command("bow deeply " + player->query_real_name()); 
}

void
react_small_evil(object player)
{
   command("glare " + player->query_real_name()); 
}


void
react_med_evil(object player)
{
   command("sulk"); 
}


void
react_large_evil(object player)
{
   command("cower"); 
}


void
react_small_good(object player)
{
    command("smile " + player->query_real_name()); 
}


void
react_med_good(object player)
{
    command("admire " + player->query_real_name()); 
}


void
react_large_good(object player)
{
    command("worship " + player->query_real_name()); 
}


void
owner_hook_enter_room(object player, object from)
{
    int al, avg;   

    if (!objectp(player)) 
        return;

    al = player->query_alignment(); 
    avg = player->query_average_stat(); 

    if ((al >= -200) && (al <= 200)) { 
         if (avg < 45)  { 
             set_alarm(1.0, 0.0, &react_small_neutral(player)); 
             return;
         }
         else if (avg < 90) { 
             set_alarm(1.0, 0.0, &react_med_neutral(player)); 
             return;
        }
        else {  
             set_alarm(1.0, 0.0, &react_large_neutral(player)); 
             return;
        }
    }
    else if (al < -200)  { 
         if (avg < 45)  { 
             set_alarm(1.0, 0.0, &react_small_evil(player)); 
             return;
         }
         else if (avg < 90) { 
             set_alarm(1.0, 0.0, &react_med_evil(player)); 
             return;
        }
        else {  
             set_alarm(1.0, 0.0, &react_large_evil(player)); 
             return;
        }
    }
    else if (al > 200) {  
         if (avg < 45)  { 
             set_alarm(1.0, 0.0, &react_small_good(player)); 
             return;
         }
         else if (avg < 90) { 
             set_alarm(1.0, 0.0, &react_med_good(player)); 
             return;
        }
        else {  
             set_alarm(1.0, 0.0, &react_large_good(player)); 
             return;
        }
    }
}



void
owner_hook_transfer(object ob, object old, object dest)
{
    string res;

    if (interactive(dest)) { 
        res = react_transfer[random(sizeof(react_transfer))]; 
        set_alarm(1.0, 0.0, &command(res)); 
    }
}


void
owner_hook_action(object ob, object player, string act)
{
    if (act[0..2] == "row") 
        set_alarm(1.0, 0.0, &command(react_row[random(sizeof(react_row))])); 
}

