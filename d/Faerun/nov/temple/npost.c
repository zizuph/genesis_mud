#include <files.h>
#include <mail.h>
#include <stdproperties.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";
inherit "/d/Genesis/lib/post";

 
void
create_nov_room()
{
    
                   
    set_name("Post office");
    add_name( ({ "room" }) );

    set_short("In the chamber of post delivery");
    set_long("A few skeletons are very busy here sorting through " +
    "the incoming and outgoing scrolls. You can't help but wonder " +
    "who summoned them, they seem under a strong spell of control. Their " +
    "work is done with extreme speed with what seems like everlasting " +
    "dedication. There is no doubt that if you were to hire one of them " +
    "to deliver a personal message, it would reach its destination.\n");

    add_exit(NOV_DIR +"temple/ncentral",   "northeast");
    
    setuid();
    seteuid(getuid());
    
        
    
}




/*public int
do_leash(string str) 
{
   object skeleton;

   if (this_player()->query_guild_name_lay() != GUILDNAME)      
   {
      write("Only necromancers may use skeletons as messengers.\n");
      return 1; 
   }

   if (str != "skeleton")
   {
      write("Hire what?\n");
      return 1;
   }
   
   
   skeleton = clone_object(NOV_DIR + "obj/skeleton");
   skeleton->set_owner(this_player());
   if(skeleton->move(this_player()))
   {
      NF("You cannot carry that much!\n");
      skeleton->remove_object();
      return 0;
   }
   write("You hire yourself a skeleton.\n");
   say(QCTNAME(this_player()) + " hires " + this_player()->query_objective()
     + "self a skeleton messenger.\n");
   return 1;
}*/






void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}

void
mail_message(string new)
{
    write("\nYou have" + new + " mail for you in Velsharoon's post office.\n\n");
}