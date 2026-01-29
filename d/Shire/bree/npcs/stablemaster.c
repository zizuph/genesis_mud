/*  
    copied from smitt.c

    This is Jonas Blackmun.  He's the stable-master of Calathin.
    He lives in /d/Terel/calathin/stable.c
 *
 *  Coded by trofast 4-1999
 *
 *  Modified for Bree's stable
 *  Finwe, May 2002
 */
inherit "std/monster";
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>

int alarm_id;

// function prototypes
public string   reply_corral();
int             come_back();
void            special_attack(object baddie);
void            create_monster();



/*
  Function:  reply_corral     
  Purpose:   reaction to add_ask about an horses in the corral
 */

public string
reply_corral()
{
object *horses;


//horses = filter(all_inventory(find_object(TOWN_DIR+"stable_corral.c")), &->id("shire_horse"));                       

if (sizeof(horses) == 0)
  {
    command("say Sorry, I don't have any horses for sale at the moment. "+
	    "Perhaps we can by some from the Rohirrim when they come by.");
    return "";
  }
else
  {
    command("say All the horses I have for sale are out in the corral right "+
	    "now.  There's "+COMPOSITE_LIVE(horses)+".  All fine steeds, "+
	    "well broken and trained for riding.  If you're interested "+
	    "in one, ask me about the price!  I can also tell you about "+
	    "the various types if you ain't a horseman.");
    command("ponder");
    command("say Also, every horse ain't for every body!  If you want,I can "+
	    "tell you which races might have trouble with different types "+
	    "of horses.");

    if (ENV(TO)->query_has_horses(TP))
      {
	command("peer "+TP->query_real_name());
	command("say Or did you mean to ask me about your horses?");
      }

    return "";

  }
}
/* Function: reply_my_horses
   Purpose:  Jonas will tell you what horses you have stabled
*/
string
reply_my_horses()
{
ENV(TO)->query_my_horses(TP);
return "";
}


/*
  Function:  reply_price     
  Purpose:   reaction to add_ask about the price of horses
 */

string
reply_price()
{
object *horses;
int i;
string reply="";

//horses=FIND_STR_IN_OBJECT("horses", find_object(TOWN_DIR+"stable_corral.c"));

if (!sizeof(horses))
  {
    command("say Price of what? I don't have any horses for sale at the moment.");
    return "";
  }

command ("emote looks out into the corral for any horses.");

for (i=0;i<sizeof(horses);i++)
  {
    reply=reply+TO->query_The_name(TP)+" says: The "+horses[i]->short()+
      " will cost you "+horses[i]->list_price()+" platinum coins.\n";
  }
write (reply);
say (reply);
command ("say It may seem like a lot, but remember you can always bring "+
	 "them back here to be stabled.");
return "";
}

/* 
Function:  reply_races
Purpose:   reaction to question about races
*/
string
reply_races()
{
  command("say First, I don't trust goblins or their kind. They tent to eat my horses when they get hungry.");

  command("emote frowns nervously.");

  command("say Next, hobbits, dwarves, gnomes are too small to ride a horse, though they can ride ponies. The larger dwarves can even ride mules, too.");

  command("say Naturally, anyone can lead horses.");
  command("smile");
    return "";
}

/* Function: reply_types
   Purpose:  reaction to add_ask about horse types
*/
string
reply_types()
{
  command("say Oh well, you know, a horse might be a stallion "+
	  "or a mare, a pony, filly or gelding, or even a mule.");
  return "";
}


/*
  Function:  reply_pony     
  Purpose:   reaction to add_ask about the pony horse type
 */
string
reply_pony()
{

  command("say My ponies may be young, but I won't sell one "+
	  "before it is well trained.  They may not carry much "+
	  "of a load, but they'll do their best to please.  I "+
	  "wouldn't recommend one for big folk, though.");
  return "";

}

/*
  Function:  reply_filly     
  Purpose:   reaction to add_ask about the filly horse type
 */
string
reply_filly()
{

  command("say A pretty filly is like a melody!");
  command("grin sheepishly");
  return "";

}


/*
  Function:  reply_mare     
  Purpose:   reaction to add_ask about the mare horse type
 */
string
reply_mare()
{
  command("say A Terel mare is as gentle as a lamb.");
  return "";

}

/*
  Function:  reply_gelding     
  Purpose:   reaction to add_ask about the gelding horse type
 */
string
reply_gelding()
{
  command("say A gelding is a male horse who's been gelded, well, "+
	  "that is to say, castrated, begging your pardon.  It makes "+
	  "them more gentle and content with work than a stallion.");
  return "";

}

/*
  Function:  reply_mule     
  Purpose:   reaction to add_ask about the mule horse type
 */
string
reply_mule()
{
  command("say If it be hard work you have in mind, a mule will "+
	  "do.  Okay, they might not be sleek and fast to impress the "+
	  "ladyfolk, but they impress me for sure.");
  command("chuckle");
  return "";

}

/*
  Function:  reply_stallion     
  Purpose:   reaction to add_ask about the stallion horse type
 */
string
reply_stallion()
{
  command("say You think you can handle it?  A Terel stallion is a "+
		  "handful and no mistake.");
  return "";

}

/*
  Function:  reply_riding     
  Purpose:   reaction to add_ask riding skill
 */
string
reply_riding()
{
    command ("laugh uproar");
    command ("say Oh my, I don't have the time nor interest in teaching "+
	 "tenderfeet to ride!  Come back when you've had a lesson or "+
	 "six.");
    command ("ponder");
    command ("say Hm, check down in Calathin, might be you can take one there.");
    command ("smile . all"); 
    return "";

}


/*
  Function:  come_back     
  Purpose:   allows Jonas to come back into the stable after
             checking whether his enemies are gone.
	     called from an alarm which is removed if he can
	     return from to the stable.
 */
int
come_back()
{

  object *enemy_list;
  object *room_list;
  object stable;
  int i;

//  stable=find_object (TOWN_DIR+"stable.c");

//  enemy_list=query_my_enemies();

  room_list=FILTER_LIVE ( all_inventory(stable) );

  for (i=0;i<sizeof(room_list);i++)
    {
      if (member_array(room_list[i], enemy_list))
	{ 
//        tell_room(TOWN_DIR+"stable.c", "Jonas peers suspiciously over the edge of the hayloft.\n"); 
	  return 1;
	}
    }

//  move_living("M",TOWN_DIR+"stable.c");
  command ("emote peers over the edge of the stable, and breaths "+
	     "a sigh of relief.");
  command("emote lowers the ladder and climbs down from the loft.");

  if (get_alarm(alarm_id)) remove_alarm(alarm_id);

  alarm_id=0;

  return 1;

}

/*
  Function;      special_attack
  Purpose:       to move Jonas into the attic of the stable whenever
                 he is attacked.  starts an alarm that will let him return
*/

void
special_attack(object baddie)
{
command("shout No you don't!");
command("emote scales the ladder to the hayloft and quickly pulls "+
	"it up after himself.");
// move_living("M",TOWN_DIR+"stable_stall.c");

alarm_id = set_alarm(2.0,600.0,&come_back() );

}



void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("keleran");
//    set_living_name("Jonas Blackmun");
    add_name("danver");
    set_race_name("human");
    set_title("Stable master of Bree"); 
    add_adj( ({"muscular", "tanned"}) );
    set_long("This is the stable master of Bree. He is responsible " +
        "for taking care of the horses that travellers bring in as " +
        "well as other steeds Breelanders bring in. His years of " +
        "caring for horses is evident by respect he shows these " +
        "proud animals.\n");

    default_config_npc(75);

    set_skill(SS_DEFENCE, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_UNARM_COMBAT, 40);
    set_skill(SS_ANI_HANDL, 30);
    set_skill(SS_RIDING, 30);
    set_hp(9999);

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);

    set_chat_time(20);
    add_chat("Only 2 gold extra for oats.");
    add_chat("You can stable your steeds here.");
    add_chat("If you need a steed, I can sell you one.");
    add_chat("Your horses will receive the best care around here.");

    set_act_time(15);
    add_act("emote pitches fresh hay into the stalls.");
    add_act("emote pitches old hay and manure out back.");
    add_act("emote sweeps the floor clean.");
    add_act("emote fills the bins with oats.");
    add_act("emote swats a passing fly.");

    add_prop(LIVE_I_QUICKNESS, 80);

    add_ask( ({"horse","horses","corral","horses for sale"}), 
	     reply_corral, 1);
    add_ask( ({"my horses","my horse","about my horses",
		 "about my horse"}), reply_my_horses,1);
    add_ask( ({"types", "various types"}), reply_types,1);
    add_ask( ({"pony", "ponies"}), reply_pony,1);
    add_ask( ({"mare", "mares"}), reply_mare,1);
    add_ask( ({"filly", "fillies"}), reply_filly,1);
    add_ask( ({"gelding", "geldings"}), reply_gelding,1);
    add_ask( ({"mule", "mules"}), reply_mule,1);
    add_ask( ({"stallion", "stallions"}), reply_stallion,1);
    add_ask( ({"riding"}), reply_riding,1);
    add_ask( ({"price","prices"}), reply_price,1);
    add_ask( ({"races","race"}), reply_races,1);
}
