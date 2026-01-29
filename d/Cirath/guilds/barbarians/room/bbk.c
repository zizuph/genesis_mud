inherit "/std/room";
#include "defs.h"

void
create_room()
{
  set_short("Bonk tent");
	set_long("You are standing inside a tent in the barbarian "+
		"camp. This tent is known as the 'bonk' tent. It is "+
		"here that new barbarians begin their days in the herd. "+
		"The tent itself is quite dull. There is no furniture and "+
		"no decoration of any sort except a little sign.\n"+
		"It reads:\n"+
           "- follow crom, to join the mighty herd of barbarians.\n"+
           "- update membership, to update your membership.\n"+
           "- list guilds, to list your guilds.\n");
	   
  INSIDE;

  add_exit(BARB_ROOM +"br4", "south",0,1);

}

void
init()
{
    ::init();
    add_action("follow", "follow");
    add_action("list", "list");
    add_action("update","update");
    add_action("start" ,"start");
}

int
follow(string str)
{
  	object sh;
  	int i;
  	object *souls;

	NF("Follow who?\n");
  	if (str != "crom") return 0;

  	NF("Your allready a herder...\n");
  	if (IS_MEMBER(TP)) return 0;

  	NF("Your mind belongs to someone else.\n");
  	if (TP->query_guild_member_occ()) return 0;

	NF("Ha! A puny elf like you wanna join the MIGHTY herd of "+
            "barbarians. NO WAY!\n");
  	if (TP->query_race() == "elf") return 0;
  	
  	NF("What? A little halfling want to join us, be realistic!\n");
  	if (TP->query_race() == "hobbit") return 0;
  	
  	NF("No gnomes will enter this herd. Never!\n");
  	if (TP->query_race() == "gnome") return 0;
  	
  	NF("Barbarians don't accept fighter layman guilds.\n");
  	if (TP->query_guild_member("layman") && TP->query_guild_style("fighter")) return 0;
  	
  	NF("Barbarians don't accept mage layman guilds.\n");
  	if (TP->query_guild_member("layman") && TP->query_guild_style("mage")) return 0;
  	
  	NF("Barbarians don't accept cleric layman guilds.\n");
  	if (TP->query_guild_member("layman") && TP->query_guild_style("cleric")) return 0;
  
  	NF("You're too evil! Crom doesn't like evil beings!\n");
  	if (TP->query_alignment()<-550) return 0;

  	NF("Sorry, you are too holy. Try the monks instead, we don't "+
                  "want holy types in our herd.\n");
  	if (TP->query_alignment()>550) return 0;
  	
  	NF("The true herder is missing: Tell a wizard.\n");
  	if(!(sh=CO(GUILD_SHADOW))) return 0;

  	switch(sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME))
  	{
    	case 1: 
        	write(	"A huge barbarian guard walks up behind you and bonks you in the head "+
          		"with his HUGE fist.\n");
    		write("\nBONK!!!!!\n\n");

    		call_out("wake_up",4);
        	break;
    	case -4:
        	NF("Your other guilds won't let you throw away you freedom so "+
           		"easily. Or perhaps its that you don't have any already.\n");
        	return 0;
    	default:
        	NF("Couldn't join you...please notify a wizard.\n");
        	return 0;
  	}
   
    	TP->setup_skill_decay();
  	TP->clear_guild_stat(SS_OCCUP);

  	if (member_array(BARB_SOUL, TP->query_cmdsoul_list()) < 0)
    	{
        	TP->add_cmdsoul(BARB_SOUL);
        	TP->update_hooks();
    	}
    	
  	CO(BARB_OBJ + "bracelet.c")->move(TP, 1);
  	return 1;
}

int
list()
{
    
  string str;

  str = this_player()->list_major_guilds();
  if (str)
    write("You are a member of the following guilds.\n" + str);
  else
    write("You are not a member of any important guilds.\n");
    
  return 1;
}

int 
update(string str)
{
    	object sh;
    	int i;
  	object *souls;

    	NF("If you forget yourself, use <update membership>.\n");
  	if (str != "membership")
    		return 0;

  	NF("But you aren't a member!\n");
  	if (!IS_MEMBER(TP))
   		return 0;
    
    	TP->remove_guild_occ();    
       
        // Update shadow
        if (!(sh = CO(GUILD_SHADOW)) || 
      		sh->shadow_me(TP, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)   
       	{
         	write("Couldn't update your membership...please talk to a " +
          		"wiz immediately.\n");
    		return 1;
  	}
  
 	// Add our cmdsoul if it's missing.
  	seteuid(getuid(TO));
    	souls = TP->query_cmdsoul_list();
    	for (i = 0; i < sizeof(souls); i++)
    	if (souls[i] = BARB_SOUL)
          	TP->remove_cmdsoul(BARB_SOUL);
      	TP->add_cmdsoul(BARB_SOUL);
      
    
    	TP->update_hooks();
    
    	if (!present(BRAC_ID, TP))
      		
    		CO(BARB_OBJ + "bracelet.c")->move(TP);
    
    	write("Ok.\n");
    	return 1;
}

int
wake_up()
{
  write("You feel very dizzy when you open your eyes again. "+
	"You're not sure how much time has passed since the brutal attack. "+
	"Somehow you have a sense of greater strength and courage than you had before. "+
        "Suddenly you realizes that you're a member of the mighty herd. "+
        "Your dreams have come true.\n");
  say(QCTNAME(TP)+" joined the Mighty Barbarian Herd.\n\n");
  
  tell_room(TO,JM);
	tell_room("/d/luther/workroom",JM);
  
  write_file(BARBJOIN,TP->query_real_name()+" joined Barbarians "+
             extract(ctime(time()),4,15)+"\n");

  return 1;
}

int
start(string str)
{
    NF("Start where?\n");
    if (str != "here") return 0;

    NF("Only the Gladiators of Athas may sleep here.\n");
    if (!IS_MEMBER(TP)) return 0;

    TP->set_default_start_location(BARB_ROOM+"bbk");
    write("This shall be the place to rest your weary head.\n");
    return 1;
}
