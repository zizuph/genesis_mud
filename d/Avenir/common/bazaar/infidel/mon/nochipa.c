// Nochipa
// file name:	/d/Avenir/common/bazaar/NPCS/nochipa.c
// creator(s):	Ilyian May 1995
// last update: 
//      Lilith, Sept 2014: Added Maivia-related quest.
//      Lilith, Apr 2004: Added Jadestone quest.
//		Denis, May'97: Obsolete code update.
// purpose:
// note:
// bug(s):
// to-do: Downgrade her when Immortal opens,

#include "../infidel.h"
#include <money.h>;
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "/d/Avenir/common/dark/maivia_quests.h"

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";
inherit "/d/Avenir/inherit/quest";
inherit "/lib/unique";

#define WRITE_THIS_LOG(file, entry) ((file_size(file) > 90000) ? \
							(rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
							(write_file(file, ctime(time()) + ": " + entry + "\n")))
private void heal_me();
private void blind();
private void do_blind(object target);

static object hallor, bow;

static string *side = ({"left","right"});
static string *part = ({"knee","elbow","fist"});
static string *area = ({"stomach","chest","face"});

void
create_monster()
{
    set_name("nochipa");
    set_living_name("nochipa");
    set_name(({"nochipa Silve","nochipa","priestess","woman","human",
	       "nochipa silve", "infidel"}));
    set_title("Disciple of Alphum");
    set_short("white-robed fair-skinned human");
    set_race_name("human");
    set_adj("fair-skinned");
    add_adj("white-robed");
    set_gender(G_FEMALE);

    set_alignment(0);
    set_long("This tall woman seems to be a priestess of some sort. "+
	    "She is clothed in flowing white robes, and carries "+
	    "a small pouch at her belt. Her eyes are ocean-blue, and "+
	    "she moves with grace and confidence.\n");

    set_stats(({100,150,150,130,150,100}));
    set_knight_prestige(-1);  // don't kill her, Knights!

    set_all_hitloc_unarmed(70);
 
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 100);
	remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_act_time(4);
    add_act("emote intones a short prayer.");
    add_act("emote mumbles a strange incantation.");
    add_act("emote kneels before the altar and prays "
	   +"silently.");
    add_act("emote seems to be bathed in a white glow for a moment.");

    add_leftover(OBJ+"head","head",1,0,0,0);
	
	set_default_answer(VBFC_ME("what_me"));
	
	/* For Maivia-related quests */
	add_ask(({"[about] [the] 'letter' / 'scroll' [from] [maivia]"}),
			"say Oh? Do you have something for me?", 1);
	
	add_ask(({"task", "job", "quest", "help", "coin"}), 
			VBFC_ME("give_task"));
	

    seteuid(getuid());
    MAKE_INFIDEL;
}

void
arm_me()
{
    MONEY_MAKE_SC(random(25))->move(this_object());
    MONEY_MAKE_GC(1)->move(this_object());

    clone_object(OBJ+"nrobe")->move(this_object());
    clone_object(OBJ+"nsandals")->move(this_object());
    clone_object(OBJ+"nring")->move(this_object());
    clone_object(OBJ+"bronze_arrow")->move(this_object());
    bow = clone_unique((OBJ+"kesoit_bow"), 4, (OBJ+"yark_bow"));
    bow->move(this_object());
    clone_object(OBJ+"globe")->move(this_object());  
    clone_object(OBJ+"globe")->move(this_object());  
    clone_object(OBJ+"hist_ave")->move(this_object());  
    command("wear all");
}

void make_hallor()
{
    if (!present(hallor))
    {
        seteuid(getuid());
        hallor = clone_object(OBJ+"hallor");
        hallor->move(TO);
        command("wield all");
    }
}

void
attacked_by(object ob)
{
    ::attacked_by(ob);

    ENV(TO)->attacker(ob);
    ob->add_prop("_live_i_attacked_infidel_guard",1);
    if (!hallor)
    {
        set_alarm(4.0, 0.0 , &command("emote tilts her face upwards."));
        set_alarm(8.0, 0.0 ,
		&command("emote cries out: Alphum, send down "+
			 "the wrath of Hallor on these Pawns "+
                         "of the Inquisitors!"));
        set_alarm(12.0, 0.0 ,&command("emote holds her hands aloft, and within "+
				    "them suddenly appears an oaken cudgel."));
        set_alarm(13.0, 0.0, make_hallor);
     }
}

private void
heal_me()
{
    TO->heal_hp(random(200) + 300);
    command("emote cries out: Alphum, Lord of Doves, send me aid!");
    command("emote seems to grow stronger.");
}

private void
blind()
{
    object *inv, *live;
    int i;
 
    inv = ({});
    inv += all_inventory(ENV(TO));

    if (sizeof(inv)) 
    {
        live = FILTER_LIVE(inv);
        if (sizeof(live))
        {
            command("emote raises her hands above her head and "
                   +"cries out: Alphum, show these Faithful the "
                   +"power of your glory!");
            tell_room(ENV(TO), "A wind arises and with it the "+
                   "sound of doves.\n");
            for (i=0; i<sizeof(live); i++) 
            {
                //Let's not blind ourselves!
                if(live[i] != TO)
                   do_blind(live[i]);
            }
        }
    }
}
 
void
do_blind(object target)
{
    object blind_obj;

    if (present("blind_obj", target))
        return;
  
    if (target->query_prop("_live_i_see_invis") < 0)
        return;
  
    if (WIS(target) > 50 + random(100))
    {
        target->catch_msg("You manage to shut your eyes before "+
			  "your tears blind you.\n");
        return;
    }
  
    if (target->query_magic_res(MAGIC_I_RES_MAGIC) > random (50))
    {
        target->catch_msg("You resist the wind.\n");
        return;
    }
  
    if (target->query_magic_res(MAGIC_I_RES_LIFE) > random (20))
    {
        target->catch_msg("You resist the wind.\n");
        return;
    }

    target->catch_msg("Your eyes start to tear up, ruining your vision.\n");  
    blind_obj = clone_object(OBJ+ "blind_obj");
    blind_obj->move(target, 1);
    blind_obj->start_blind();
}

public int
special_attack(object enemy)
{
    string how;
    int damage, swing_type;
    mixed hitres;
    object me;
  
    if (random(10))
        return 0;

    switch(random(2))
    {
    case 0:
        heal_me();
	  return 0;
    case 1:
        blind();
        return 0;
    }
}


public void
do_die(object killer)
{
    killer->add_prop("_live_i_killed_infidel_guard", 1);
    command("sigh sadly");
    ::do_die(killer);
}

void not_wanted(object what, object who)
{
    command("frown "+who->query_real_name());
    if (!command("give "+what->query_name()+" to "
				 +who->query_real_name()))
        what->remove_object();  
}

string
give_task()
{
    if (!CAN_SEE(TO, TP))
    {
        command("emote looks around suspiciously");
        command("say The air speaks not in the voice of a "+
				"God.");
        return "";
    }
	command("say There is nothing you can do for me.");
	return "";

}

string
what_me()
{
    if (!CAN_SEE(TO, TP))
    {
        command("say What speaks from pure air?");        
        return "";
    }
    switch(random(4))
    {
        case 0:
            command("say I am but a humble servant of Alphum, I know little.");
            break;
        case 1:
            command("say Such questions I cannot answer for you.");
            break;
        case 2:
            command("laugh sadly");
            break;
        case 3:
            command("say You flatter me, thinking I would know that.");
            break;
    }
    return "";    
}


/* Maivia's scroll quest */
void
reward_maivia_quest(object player)
{
	
    reward_quest(QUEST_MAV3, player, M_GROUP, MBIT_NOCHIPA, MEXP_NOCHIPA);	
    WRITE_THIS_LOG(QUEST_LOG, "gave Maivia's scroll to Nochipa and "+
				   "was rewarded "+MEXP_NOCHIPA+" exp.\n" );
	STATSERV_LOG_EVENT("dark", "Maivia quests done");
    say(QCTNAME(player) + " got a nice reward.\n");
	
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
	
    if (!living(from))
        return;
	
    if (obj->id(M_N_O))
    {
		if (CHECK_QUEST_8(from))
		{
			set_alarm (1.0, 0.0, &command("say This isn't for me."));
			set_alarm (3.0, 0.0, &command("say You must be mistaken."));
			set_alarm (4.0, 0.0, &not_wanted(obj, from));
			return;
		}
		if (obj->query_prop(Q_OB_OPENED))
		{
			set_alarm (1.0, 0.0, &command("say This scroll is missing it's seal."));
			set_alarm (3.0, 0.0, &command("say I can't be sure it is authentic."));
			set_alarm (4.0, 0.0, &not_wanted(obj, from));
			return;
		}
		else
		{
		    set_alarm (2.0, 0.0, &command("emote smiles hopefully."));
			set_alarm (3.0, 0.0, &command("say I may save my people yet, and " +
		        "extract revenge on those who marked us."));
		    set_alarm (3.0, 0.0, &reward_maivia_quest(from));
		    return;
		}
    }
	
    set_alarm(0.1, 0.0, &not_wanted(obj, from));
}

/* end quest code */

