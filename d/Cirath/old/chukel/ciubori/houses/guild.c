/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/guild.c
* Comments: edited by Luther Oct. 2001
*/


inherit "/std/room";
inherit "/d/Cirath/common/shiva_train";


#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"

#include "/d/Cirath/common/mobber.h"
#define NUM     sizeof(query_money_types(-1))
#define CLOSED  0       /* 1 = closed,   0 = open.  */

int closed;
object meditate;

void
reset_room()
{
    bring_room_mob("Errlog", CIU_NPC + "trainer.c", 1, 1);
}
 


void
create_room()
{ 
  	object board, box;
  	closed = CLOSED; 

  	set_short("Cirathian travellers guild");
  	set_long("This is the cirathian travellers guild, where tired travellers "+
    		"can rest a little and improve or even learn new skills. The room "+
    		"is cozy and anyone could feel comfortable here. There's a fireplace "+
    		"in one of the corners with a fire burning in it. The lights from "+
    		"the fire flickers on the walls of the guild. You feel that you should "+
    		"be able to meditate in this environment.\n");

  	INSIDE; 
  
  	clone_object(OBJ+"charity")->move(TO);

  	board = clone_object("/std/board");
  	board->set_board_name(CIU_BOA);
  	board->set_num_notes(20);  	/* Number of notes         */
 	board->set_anonymous(1);        /* You may write anonymous */
 	board->set_silent(0);           /* Make noise when reading */
  	board->set_show_lvl(0);  
  	board->set_remove_lvl(30);      /*Lords or higher  */
  	board->set_remove_str("You somehow failed.");
  	board->set_use_gedit(0);        /* Don't use that marvellous editor */
  	board->move(this_object());
  
  	add_exit(CIU_STR + "sstreet2", "west", 0, 1);
  	reset_room();
}

enter_inv(ob, from)
{
  	::enter_inv(ob, from);

  	if (!query_ip_number(ob) || !closed)
    		return;
  	if (ob->query_wiz_level()) 
    		write("\n\nWARNING!\nYou shouldn't be here. "+
          		"I'm doing some work on the guild.\n");
   	else {
     		write("The guild is closed. Come back later.\n");
     		ob->move(CIU_STR + "sstreet2");
  }
}

