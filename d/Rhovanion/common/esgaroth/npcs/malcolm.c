/*
 *		This is a test npc for the Smaug quest
 *
 * Contributors: Erane and Blackstaff
 * Last modified: Blackstaff 10 Feb 95
 *
 */

inherit "/std/monster";

#include "/d/Rhovanion/defs.h"
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#define SMAUG "/d/Rhovanion/QUESTS/private/SMAUG"

/*
 * Prototypes
 */

public void call_for_help(object ob);
public void return_introduce();
public string sod_off();
public void reject_gift(object ob, object from);
public void tell_me_lies(object ob, object from);
public void tell_me_quest(object ob, object from);

/*
 * GLobal variables
 */
static string *helped = ({ });
static string *herring = ({ });
static string *list_introduced = ({ });
public string assilant;
/*
 * Function name: create_monster
 * Description  : here we define the characteristics of the monster
 */ 

void
create_monster()
{
    seteuid(getuid(TO));
    set_name("malcolm");
    set_adj("silent");   		
    add_adj("haughty");		
    add_name("adventurer"); 
    add_name("drunk");     
    add_name("esg_quest_npc_malcolm");
    set_long("Although obviously very drunk, this fellow has the looks " +
	"and manners of a nobleman. He seldom speaks, but seems to regard " +
	"his friends with obvius displeasure of their state of beeing.\n");
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_hp(400);
    default_config_npc(50);

    set_base_stat(SS_STR, 45);
    set_base_stat(SS_CON, 70);
    set_base_stat(SS_DIS, 100);

    set_appearance(42);					
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENSE, 30);		
    set_skill(SS_UNARM_COMBAT, 35);
					
    seq_new("do_things");
    seq_addfirst("do_things", "@@arm_me");

    set_chat_time(12);
    add_chat("Really Dalkier, I wish you would sober up soon.");
    add_chat("Must you all behave like pigs ?");
    add_chat("Don't forget your vow of silence.");
    add_chat("Speak to Erane or Blackstaff about any bugs " +
	"or suggestions");
   	
    set_act_time(4);
    add_act("drink all");
    add_act("sniff");
    add_act("emote looks at his fellows and rolls his eyes in exasperation");
    
    set_cact_time(1);
    add_cact("slap " + assilant);
       
    trig_new("%w 'introduces' %s", "react_intro");
    
    add_ask(({"smaug","treasure", "quest"}), VBFC_ME("sod_off"));
}

/*
 * Function name: enter_inv
 * Description  : this function gets called every time an object
 *		  enters Dalkier's inventory
 *		  We decide how Dalkier reacts depending on the 
 *		  thing he receives...
 * Arguments	: object ob - the object that entered
 *		  object from - the object it came from
 */
public void
enter_inv(object ob, object from)
{
    if (ob->query_prop("_obj_i_my_obj"))
	return;

    if (!function_exists("create_drink", ob))
    {
	set_alarmv(2.0, 0.0, "reject_gift", ({ ob, from }));
	return;
    }

    /* setup so that he only helps for quest if you buy him stout
     * His prefered drink will be randomized eventually - Erane
     */
    if (ob->query_name() != "stout")
    {
	set_alarmv(2.0, 0.0, "tell_me_lies", ({ ob, from }));
	return;
    }

    set_alarmv(2.0, 0.0, "tell_me_quest", ({ ob, from }));
    helped += from->query_real_name();
    //save_object(SMAUG);
    return;
}

/*
 * Function name: reject gift
 * Description  : returns the gift to the player who gave it
 * Arguments	: object ob - the gift
 *		  object from - the player to return it to
 */
public void
reject_gift(object ob, object from)
{  
    TO->command("emote looks at the " + ob->query_name() + " with little " +
	"interest.\n");
    from->catch_msg(QCTNAME(TO) + " leans towards you and tells you: " +
	"\nI'd prefer a drink, if you don't mind.\n");
    say(QCTNAME(TO) + " leans towards " + QCTNAME(from) + " and tells " +
	HIM(from) + " something.\n");
    TO->command("smile brief");
    TO->command("give " + ob->query_name() + " to " + 
	from->query_real_name());
    return;
}

/*
 * Function name: tell_me_lies
 * Description  : start the red-herring command chain
 * Arguments	: object ob - the drink given
 *		  object from - the player to tell the lies to
 */
public void
tell_me_lies(object ob, object from)
{
    herring=({"Torin lost his axe in the battle, it now lies somwhere at the base of lonely mountain. " +
	"I think it might be useful in your quest.\n" , "Find Durins boots, they will serve you well I think.\n" ,
	"It is rumored than when Bilbo was clubbed unconscious, he dropped his helmet. This helmet was magical " +
	"and would enable you to find the treasure more easily.\n","The bracers of the Elf king will enable you to endure " +
	"the chill of the lake.\n","Bard lost his bow in the battle, you had better find it if you wish to complete the quest.\n"});
    TO->command("thank " + from->query_real_name());
    TO->command("say Aaah, this looks tasty.");
    TO->command("emote sips " + HIS(TO) + " " + ob->query_short() + 
	".");
    from->catch_msg(herring[random(5)]);
}

/*
 * Function name: tell_me_quest
 * Description  : start telling the player info on the quest.
 *		  This officially begins the quest in the player
 *		  object
 */
public void
tell_me_quest(object ob, object from)
{
    from->catch_msg("Thanks! Now I'll explain the quest...\n");
}
    
/*
 * Function name: arm_me
 * Description  : give dalkier a weapon and let the gamedriver know
 *		  that it's not a gift from a player
 */
public void
arm_me()
{
    object item,armour;
    
    item = clone_object("/d/Rhovanion/common/weapons/lexstaff");	
    item->add_prop("_obj_i_my_obj", 1);
    item->move(TO);
    armour = clone_object("/d/Rhovanion/common/armours/brigadine");
    armour->add_prop("_obj_i_my_obj", 1);
    armour->move(TO);
    command("wear all");
}

/*
 * Function name: react_intro
 * Description  : initialize the replied introduction
 * Arguments	: string who - the string name of the player
 *		  who introduced
 *		  string dummy - the target of the intro
 *
 * Modified to a "smart" intro, originally written by Milan.
 */

void
react_intro(string who, string dummy) 
{
  who = TP->query_real_name();
  dummy = explode(dummy, " ")[0];
  if((dummy == "himself") || (dummy == "herself") || (dummy == "itself"))
    if(member_array(who, list_introduced) == -1)
      list_introduced += ({ who });
  call_out("return_introduce", 4);
}

void
return_introduce() 
{
 object *in_room;
 int i, met_me;
  in_room=FILTER_LIVE(all_inventory(environment()));
  met_me=1;
  for (i = 0; i < sizeof(in_room); i++) 
    if (!in_room[i]->query_met(TO->query_real_name())) met_me=0;
  if (!met_me) 
  {
     command("introduce me");
     command("bow");
  }
}

/*
 * Function name: sod_off
 * Description  : refuse the player quest info
 *		  This function needs to be altered - Erane
 */
public string
sod_off()
{
    command("whisper " + PO->query_real_name() + "I'm sorry, I have " +
	"taken a vow of secrecy with my companions.");
    TP->catch_msg(QCTNAME(TO) + " whispers to you:\n" +
	"I hope you understand... The prize is too great to " +
	"give away to strangers.\n");
    command("apologize " + PO->query_real_name());
    return "";
}

/*
 * Function name: call_for_help
 * Description  : makes an array of all livings, and then notifies party
 *                that he is under attack!
 * Arguments	: ob - the attacker.
 *		  
 */


void
call_for_help(object ob)
{

  object *arr = FILTER_LIVE(all_inventory(environment()));
  int i;
  write(sizeof(arr));
    for (i = 0; i < sizeof(arr); i++)
    if((arr[i]->query_real_name() == ("dalkier")) || (arr[i]->query_real_name() == ("lexor")) || (arr[i]->query_real_name() == ("taurek")))
	arr[i]->notify_ob_attacked_me(ob);
}


void 
attacked_by(object ob)
{
  ::attacked_by(ob);
  command("say We don't want to kill you. Leave now, and your life shall be spared!");
  assilant=ob->query_real_name();
  command("wield all");
  call_for_help(ob); /* naturally we call for help when attacked */
}


void
notify_ob_attacked_me(object ob)
{
    
    if(query_attack()) return;
    set_alarm(1.0, 0.0, "help_friend",ob);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        if(random(2)) command("grin at " + ob->query_real_name());
        command("kill " + ob->query_real_name());
        command("say You attacked my friend, you will die!");
	command("wield all");
	assilant=ob->query_real_name();
    }

}
      

    

    
  

