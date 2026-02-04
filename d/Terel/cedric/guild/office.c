#pragma save_binary

inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

#define SBOARD          GUILD+"Master_board.c"

/*
* The Minstrel Guild Headquarters: The Guildmaster's office.  
* Here songs can be presented for approval by the Guildmaster.  
* Songs of QUALITY will perhaps be added to the songbooks of 
* Minstrels everywhere.
* Jorl 3/93
*/

void reset_room();

void
create_room()
{
   set_short("The Guildmaster's Office");
   set_long(BS("This stylish room is the office of the Guildmaster.  "
         + "Here the head minstrel can retire in comfort to take care of "
         + "guild business.  The Guildmaster keeps a board in here which "
         + "he reserves for important announcements concerning the guild. "
         + "A comfortable chair sits behind an imposing desk; to the south "
	 + "a closed door leads to a private office.\n"));
   
   add_item("door","It is a large door which leads to an inner office.\n");
   add_item("desk", BS("This is a well-oiled desk made of the finest "
         + "cherry.  There are some important-looking papers on the desk, "
         + "but the Master probably wouldn't like you rifling through them!\n"));
   add_item("chair", BS("This is the Guildmaster's favorite chair.  "
         + "It sets quite high, in order to allow the Master to see over the "
         + "top of the desk.  It looks like as if it would be very relaxing to while "
         + "away the hours in such a chair...if you too were a gnome.\n"));
   
   add_exit(GUILD+"auditorium", "northeast");
   add_exit(GUILD+"checkout", "northwest");
   add_prop(ROOM_I_INSIDE, 1);
   reset_room();

#if 0
    setuid();
    seteuid(getuid());
    clone_object("/d/Terel/cedric/guild/vote")->move(this_object(), 1);
#endif
}

void
reset_room()
{
    /* This makes sure the board is present.*/
   
    object  board;
   
    if (!present("board", TO()))
    {
	board = clone_object(SBOARD);
	board->move(TO());
    }
}
void
init()
{
    add_action("enter","enter");
    ::init();
}

public int
enter(string str)
{
   if(!str || str != "door")
      {
      return_fail("You can only enter the door.\n");
   }
   else
      {
      if(TP()->query_real_name()==GUILDMASTER
	 || TP()->query_real_name()==ASSISTANT
	 || TP()->query_special_title(TP()->query_real_name()))
         {
	     TP()->move_living("retiring to the inner office.",
			       GUILD+"pri_office.c",1,0);
	     return 1;
	 }
      else
         return_fail("This is a private office.  Please do not disturb.\n");
   }
}

void
purge_tickets(object killer)
{
    int 	i;
    object 	ticket, *bins;
    object	storerm;
        
    while (ticket = present("minstrel_claim_ticket", killer))
    {
	ticket->self_destruct();
    }
    
    storerm = STOREROOM->this_room();
    bins = all_inventory(storerm);
    for (i=0;i<sizeof(bins);i++)
    {
	if (bins[i]->query_label() == killer->query_real_name())
	{
	    bins[i]->move(TO());
	    bins[i]->set_long(bins[i]->long() + "A small note attached "
			      + "to the bin explains that " 
			      + killer->query_name() + " was foolish "
			      + "enough to leave weapons in our care while "
			      + "plotting evil towards the Minstrels.\n");
	}
    }
}

    

void
mc_died(object killer)
{
    object ob;
    seteuid(getuid());
    
    ob = clone_object(GUILDOBJ+"poster");
    ob->set_post(killer, "Kyrsis");
    tell_room(TO(), "Funny, you didn't notice that poster on the wall when you "
    + "entered the room.\n");
    ob->move(TO());
    ob->add_prop(OBJ_M_NO_GET, "The poster is securely fastened to the wall.\n");
    /* Get rid of all the killer's claim tickets */
    purge_tickets(killer);
}

void
rm_died(object killer)
{
    object ob;
    seteuid(getuid());
    
    ob = clone_object(GUILDOBJ+"poster");
    ob->set_post(killer, "the Rumor Monger");
    tell_room(TO(), "Funny, you didn't notice that poster on the wall when you "
    + "entered the room.\n");
    ob->move(TO());
    ob->add_prop(OBJ_M_NO_GET, "The poster is securely fastened to the wall.\n");
    /* Get rid of all the killer's claim tickets */
    purge_tickets(killer);
}

void 
minstrel_died(object killer, object killed)
{
    object ob;
    seteuid(getuid());

    if (!interactive(killer)) return;
    ob = clone_object(GUILDOBJ+"poster");
    ob->set_post(killer, killed->query_name());
    tell_room(TO(), "Funny, you didn't notice that poster on the wall when you "
    + "entered the room.\n");
    ob->move(TO());
    ob->add_prop(OBJ_M_NO_GET,
	"The poster is securely fastened to the wall.\n");

    /* Get rid of all the killer's claim tickets */
    purge_tickets(killer);
    
}
