/*
 * barkeep1.c
 * A Barkeeper, changed by Ares, gives final Ferret Quest item to player.
 * 
 * Ares, July 2004
 * Updated by Mirandus, Feb 2015 to hopefully work more than once an arma
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include "/d/Ansalon/taman_busuk/sanction/ferrets/defs.h"

inherit AM_FILE
inherit "/d/Krynn/std/equip.c";


#define GOT_QUEST_ROCK "_i_found_rock"  
#define GOT_QUEST_COFFIN "_i_found_coffin"
#define GOT_QUEST_PAPER1 "_i_found_paper1"
#define GOT_QUEST_PAPER2 "_i_found_paper2"
#define GOT_QUEST_SHINY_OBJECT "_i_found_shinyobject"
#define GOT_QUEST_TAG "_i_found_tag"
#define GOT_QUEST_OLD_PAPER "_i_found_oldpaper"
#define GOT_A_TAG "_i_got_tag"

#define KALEN_PROP "_garren_prop_asked_kalen"
#define BARKEEP_PROP "_garren_prop_asked_barkeep"
#define MEETING_PROP "_garren_prop_asked_meeting"
#define GARREN_NOTE "_garren_quest_note"
#define PARCHMENT_PROP "_garren_prop_read_note"

// Prototypes
string kalen_response();
string meeting_response();


object tag;

void 
reset_krynn_monster()
{
   if (!objectp(tag) || environment(tag) != this_object())
   {
      tag = clone_object("/d/Ansalon/taman_busuk/sanction/ferrets/obj/silver_tag"); 
      tag->move(this_object(), 1);
   } 
}

void
create_krynn_monster()
{
    if (!IS_CLONE)
	return;

    set_name("barkeeper");
    set_short("portly barkeeper");
    set_long("A portly barkeeper. Having served patrons for many years, this "+
             "barkeeper can find success anywhere, even here in Sanction.\n");
    set_adj("portly");
    set_stats(({60,60,60,60,60,60}));

    add_ask(({"quest","quests","task","tasks"}),"say What you need help with? "
	+"Deanak or Kalen?", 1);
    add_ask(({" [about] 'deanak'","breeder"}), "say Old Deanak? He's a ferret "+
      "breeder that lives over by the Inn. He used to be a regular until a year ago "+
      "when he stopped coming in. He would always bring his ferrets here "+
      "to entertain the ladies.",1);
    add_ask(" [about] 'ladies'", "say The ladies loved Deanak and his ferrets. "+
      "He even let a few of them name the ferrets.",1);
    add_ask(({"ferret","ferrets"}), "say We don't sell ferrets here, old Deanak "+
      "near the Inn sells them.",1);
    add_ask(" [about] 'names'", "say Names of his old ferrets? Or the ladies? "+
      "My memory is just as bad as his, but I do remember that Deanak "+
      "came in here a few years ago and got so drunk he tried to tip me "+
      "with a ferret name tag, he thought it was a silver coin! To this day "+
      "he still thinks so, I bet ya.",1); 
    add_ask(" [about] 'tag'", "@@answer_tag@@" ,1);

    add_ask("kalen", kalen_response, 1);

    add_ask("meeting", meeting_response, 1);
    add_ask("friends", meeting_response, 1);
    
    set_act_time(5);
    add_act("emote wipes down the bar with a dirty rag.");
    add_act("emote warms his hands at the fireplace.");
    add_act("emote eyes you suspiciously.");
    add_prop(OBJ_M_NO_ATTACK, 1);
    
    reset_krynn_monster();

}

string
kalen_response()
{
    if(TP->query_prop(KALEN_PROP))
    {
        TP->add_prop(BARKEEP_PROP, 1);
        return "say Kalen comes here from time to time. I wish he would " +
               "do his business with the slave traders somewhere else. " +
               "If it wasn't for the increased sales when he is here, I would tell him to shove off. "+
               "Too bad you didn't come a few minutes earlier, he just took off after meeting up with his "+
               "usual 'friends'.";
    }
    return "say How about a beer?";
}

string
meeting_response()
{
    find_player("navarre")->catch_tell("Inside meeting response\n");
    
    if(TP->query_prop(BARKEEP_PROP))
    {
        find_player("navarre")->catch_tell("Yes, had barkeep prop\n");
        TP->add_prop(MEETING_PROP, 1);
        find_player("navarre")->catch_tell("Added the prop.\n");
        return "say Kalen talked to that cruel slave trader he always does business with. I think "+
               "they have some schemes brewing tonight, I saw them exchange notes before they left. " +
               "They think I am blind, but I see everything.";
    }
    return "say How about a beer?";
}

string
answer_tag()
{

    if (TP->test_bit("ansalon", 0, 5) || TP->query_prop(GOT_A_TAG)) 
    {
      command("say You don't need a tag, I gave you one already!");  
      return 0;  
    }
    else 
		if (!objectp(tag) || environment(tag) != this_object())
		{
			tag = clone_object("/d/Ansalon/taman_busuk/sanction/ferrets/obj/silver_tag"); 
			tag->move(this_object(), 1);
		} 

		command ("say I don't know why I've kept it all these years, gives me a "+
        "laugh every time I look at it though.  Here, you can have it.");
		say("The "+this_object()->query_short()+" gives "+QTNAME(TP)+" something.\n");
		TP->catch_tell("The "+this_object()->query_short()+" gives you a silver ferret tag.\n");
		TP->add_prop(GOT_A_TAG,1);
		tag->move(TP, 1);
		command("say There you go");
    
    

}





