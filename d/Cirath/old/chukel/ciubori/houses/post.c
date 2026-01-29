/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/post.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_room()
{
  	set_short("The post office of Ciubori");
  	set_long("You're standing inside the post-office of Ciubori. The room has white walls, "+
    		"roof and floor which makes it kind of boring. A clerk is sitting behid a "+
    		"couter. " + get_std_use());
  
  	add_item("clerk","The clerk is poking his nose. You wonder if he finds anything "+
    		"interesting.\n");
    		
    	INSIDE;
    		
  	add_exit(CIU_STR + "cstreet2", "east", 0, 1);
}

init()
{
  	::init();
  	post_init();
}

leave_inv(ob,to)
{
  	::leave_inv(ob,to);
  	post_leave_inv(ob,to);
}

void
mail_message(string new)
{
  	write("\nThere is" + new + " mail for you in the post office of Ciubori!\n"+
        	"(Norteast part of town at Crystal Street.)\n\n");
}
