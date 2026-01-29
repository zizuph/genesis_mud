/*
*Thimah, the Solace Shaman
*Created by Leia
*3/30/2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

/* Added revelation for OotS - Arman 2017 */

#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>
#include <tasks.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/lib/unique";
inherit "/d/Genesis/specials/resist";

inherit M_FILE

int intensity;
string damage_amount;
string how_str;
string how_str2; 

int arm_me()
{ 
    clone_object(T_JERKIN)->move(this_object());
    clone_object(T_BOOTS)->move(this_object());
    clone_object(T_BRACERS)->move(this_object());
    clone_object(T_GREAVES)->move(this_object());
    clone_object(T_CAP)->move(this_object());
    clone_unique(COMPLEX_STAFF, 5, SIMPLE_STAFF)->move(this_object());
    command("wield weapons");
    command("wear armours");
}

void create_krynn_monster()
{
	set_name ("thimah");
	set_gender(G_MALE);
	add_name("shaman");
	add_name("medicine-man");
	set_living_name("thimah");
	set_adj(({"muscular", "dark-skinned"}));
	set_title("the Nomadic Shaman");
	set_race_name("human");
	set_short("muscular dark-skinned male human");
	set_long("This human has obviously travelled great distances to come to the place he stands today. He is the youngest in a long-line of great Shamans that are nomadic to the plains of this area. Something must have drawn him here, to be this close to the town of Solace.\n");
	set_introduce(1);
	
    set_stats(({270, 290, 270, 215, 220, 240}));
	set_alignment(0);
	add_prop(CONT_I_VOLUME, 60000);
    add_prop(NPC_I_NO_LOOKS, 1);
	set_skill(SS_WEP_POLEARM, 90);
	set_skill(SS_DEFENCE, 75);
	set_skill(SS_PARRY, 75);
	set_skill(SS_AWARENESS, 100);
	set_skill(SS_BLIND_COMBAT, 65);
	add_prop(LIVE_I_SEE_INVIS, 100);
	add_prop(CONT_I_HEIGHT, 195);
	add_prop(CONT_I_WEIGHT, 75000);
	add_prop("_ranger_i_not_disarm", 1);
	set_introduce(1);
	
	arm_me();
    
    set_act_time(5);
    add_act("emote eyes you warily as you stand before him. You have a feeling he is taking a measure of your worth.");
    add_act("emote mumbles a few seemingly abstract words, and the fire glows a little brighter.");
    add_act("emote lifts the ladle from the bucket and slowly pours water onto the hot stone. As the steam rises his voice raises in a haunting chant.");
    add_act("emote breathes deeply, inhaling the hot steam that fills the tent.");
    
    set_chat_time(6);
    add_chat("Tlaah na. Ni no mahaja, melaka mo soma.");
    add_chat("There are terrible things at work in these lands. Unnatural things.");
    add_chat("I have been given a task to defend these lands from those who would harm it.");
    add_chat("Have you come to defend these lands as well?");
    add_chat("Hmm... Perhaps you may be able to aid me in this task.");
    
    add_ask(({"quest", "task", "help", "job"}), "@@quest_func@@");
    add_ask("filth", "@@qfilth@@");     
    add_ask("cleanse", "@@qcleanse");
    add_ask("ingredients", "@@qingredients@@");
    add_ask("powder", "@@qpowder@@"); 
    add_ask(({"gods","old gods","revelation","stories"}),"@@oots_revelation");
}

string
qfilth()
{
    TO->command("say It seems as though the armies nearby have been using it as a bathing spot as well as a spot to relieve themselves. The results are absolutely disgusting.");
    return "";
}

string
qcleanse()
{
    TO->command("say There is a potion that can be made that will completely cleanse the water. However, it requires certain ingredients to make.");
    return "";
}

string
qingredients()
{
    TO->command("say The ingredients are a special powder that only I can make, combined with a leaf from a vallenwood tree and pure water. The latter two ingredients can be found in the town of Solace. When you have found all of the ingredients, bring them here and offer them to me.");
    return "";
}   

string
qpowder()
{
    TO->command("say The powder requires three herbs that can be found on this continent. They are Angeltear, Fireweed, and Saskatoon.");
    return "";
}

string
oots_revelation()
{
    TO->command("say The Old Gods are long gone, but their stories live on.");
    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "ageofstarbirth"))
          {
            TP->catch_msg("\n\nAs you listen to the tales of creation from the shaman you " +
                    "are granted a divine revelation about the Age of Starbirth!\n\n\n");
            OOTS_ADD_REV(TP,"ageofstarbirth","enlightenment - the age of starbirth");  
          }
    }
    return "";
}
       
string
quest_func()
{
    if(TP->test_bit("krynn", GROUP, G_BIT))
    {
        TO->command("say You have done all you can for me. Go with the blessings of the earth.");
        return "";
    }
	    
    if(TP->test_bit("krynn", GROUP, E_BIT))
    {
        TO->command("say You have done enough already, by tainting the fountain and making the citizens of Solace sick! Get out of my sight!");
        return "";
    }
    TO->command("say Ah, you are a friend of the earth as well. I was sent here by the chieftan of my village to protect the land and the creatures that live here.");
    TO->command("say There are basic needs that all creatures share. One of these needs is for pure water. The citizens of Solace need a place to quench their thirst.");
    TO->command("say The town fountain has become over run with filth, and to drink from it makes one sick. However, I am not allowed near enough to it that I can cleanse it properly.");
    TO->command("say Therefore, I need your help in giving the citizens of Solace a clean source of water again.");
    find_object(ROOM2)->set_fountain_dirty(1);
    return "";
}

int
set_damage_amount(object enemy)
{
    int resist;
    
    switch(random(6))
    {
        case 0: damage_amount = "none";
                intensity = 0;
                break;
        case 1: damage_amount = "slight";
                intensity = 150;
                break;
        case 2: damage_amount = "moderate";
                intensity = 212;
                break;
        case 3: damage_amount = "good";
                intensity = 274;
                break;
        case 4: damage_amount = "very good";
                intensity = 336;
                break;
        case 5: damage_amount = "excellent";
                intensity = 400;
                break;
    }
    
    /* Modifies the intensity based on fire and magic resistance as according
     * to the new resist calculations. The basic resist was used so as not to
     * weigh stats and skills.
     */
    resist = spell_resist_basic(this_object(), enemy,
                                ({ SS_ELEMENT_FIRE }),
                                TASK_FORMIDABLE);
                                
    intensity = spell_resist_modify_value(intensity, resist);
}

int
special_attack(object enemy)
{
    mixed* hitresult;
    object ob;

    if (random(4)) 
    {
        /*
        tell_room(E(TO),"**Thimah failed random so no special**\n");
        */
        return 0;
    }

    if (!(ob = TO->query_attack())) 
    {
        /*     
        tell_room(E(TO),"**Thimah has no enemy so no special**\n");
        */
        return 0;
    }
    
    set_damage_amount(enemy);
            
    hitresult = ob->hit_me(intensity, MAGIC_DT, TO, -1);
    
    if (intensity == 0)
    {
        how_str = " but you feel no effect.\n";
        how_str2= " but there seems to be little effect.\n";
    }
    else if (intensity <= 150)
    {
        how_str = ". Your skin begins to tingle, and you feel your body heat rise!\n";
        how_str2 =". " + QCTNAME(ob) + "'s skin turns a slight shade of pink!\n";
    }
    else if (intensity <= 212)
    {
        how_str = ". Goosebumps raise on your skin, and sweat beads up on your arms!\n";
        how_str2 =". Sweat begins to bead up on " + QCTNAME(ob) + "'s arms!\n";
    }
    else if (intensity <= 274)
    {
        how_str = ". Your skin begins to itch, and sweat soaks your hair!\n";
        how_str2 =". Sweat soaks " + QCTNAME(ob) + "'s hair!\n";
    }
    else if (intensity <= 336)
    {
        how_str = ". Your skin feels like it is crawling. Sweat pours into your eyes!\n";
        how_str2 =". " + QCTNAME(ob) + " reaches up and wipes the sweat from " + HIS(ob) + " eyes!\n";
    }
    else
    {
        how_str = ". You scream in agony as your blood begins to boil!\n";
        how_str2 = ". " + QCTNAME(ob) + " howls in absolute agony!\n";
    }          
    
    ob->catch_msg(QCTNAME(TO) + " points his medicine stick at you, mumbling something inaudible under his breath" + how_str);
    tell_watcher(QCTNAME(TO) + " points his medicine stick at " + QCTNAME(ob) + how_str2, ob);

    if(ob->query_hp() <= 0)
    {
        ob->do_die(TO);
        write("A small tear rolls down " + QCTNAME(TO) + "'s cheek.\n");
    }
    
    return 1;
    
}
