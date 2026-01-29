inherit "/d/Shire/common/lib/rom";
#include "/d/Shire/common/defs.h";
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Shire/common/include/abbrevs.h"

#define FOUND_LEVER "_did_find_the_hidden_lever"
#define SKILL_NEED 40

object troll;
int open;

create_rom()
{
    set_short("Inside a secret tunnel.");
    set_long("You are walking in a dark and humid tunnel under the "
	+"trollshaws. Blood and guts is laying all over the floor "
	+"and it looks like there has been a lots of fighting in "
	+"here. The path is going downwards, quite steep infact. "
	+"On the wall is a torchstand with an outburned torch in it.\n");
		
	add_item(("torch"),"The torch looks like it has been here for ages.\n"); 
	
	add_item("wall","@@wall_long");
   	add_item("lever", "@@lever_long");
      	
	add_exit(TROLLSH_DIR + "stunnel1", "west", 0, 4);
	   	    
   	add_prop(ROOM_I_LIGHT, -2);
   	add_prop(ROOM_I_INSIDE,1);

   	add_prop(OBJ_I_SEARCH_TIME,4);
   	add_prop(OBJ_S_SEARCH_FUN, "search_wall");
   	troll = clone_object(TROLLSH_DIR + "npc/" + "ruletroll");
   	troll->move(TO);


}

reset_rom()
{
   if (!troll) 
   {
      troll = clone_object(TROLLSH_DIR + "npc/" + "ruletroll");
      troll->move(TO);
   }
}

lever_long()
{
   if (TP->query_prop(FOUND_LEVER))
      return "This is a lever, it looks like it can be moved in some way..\n";
      else
      return "Lever? You can see no lever in here..\n";
}

wall_long()
{
	if (TP->query_prop(FOUND_LEVER))
	return "The wall is black, and filled with blood. You can see a lever on the wall.\n";
	else
	return "The wall is black and looks smooth. Blood is trickling down from the wall...\n"; 
	
}

search_wall(what)
{
  if(what == "wall")
  {
    if(TP->query_skill(SS_AWARENESS) > SKILL_NEED)
    {
      TP->add_prop(FOUND_LEVER,1);
      return "Ha, lucky you, you found a lever!\n";
    }
    else { return 0; }
  }
  return 0;
}

init()
{
   ::init();
   add_action("pull_lever", "pull");
}

pull_lever(what)
{
    NF("What are you trying to do?\n");
    if(what != "lever")
        return 0;
    if (open)
    {
        write("You pull on the lever, but nothing happens. Perhaps this is "+
                                     "because the door is already open?\n");
        say(QCTNAME(TP) + " pulls on a lever but nothing happens.\n");
    }
    else
    {
        write("You pull on the lever and a secret passage is revealed!\n");
        say(QCTNAME(TP) + " pulls on a lever, revealing a secret passage!\n");
        add_exit(TROLLSH_DIR + "stunnel0","secret",0,2);
        open = 1;
        set_alarm(10.0,0.0,"close_door");
    }
    return open;
}

int close_door()
{
    tell_room(TO, "The secret passage suddenly disappears!\n");
    remove_exit("secret");
    call_other(TROLLSH_DIR + "tunnel0", "close_door");/* watch out !! this is part 
		of a recursive call, it might holdt the game */
/* i need the lever in this room to open the door here and in stunnel0 */
    open = 0;
    return open;
}

int open_door()
{
    tell_room(TO, "A secret passage suddenly appears!\n");
    add_exit(TROLLSH_DIR + "stunnel3","secret",0,2);
/* i need the lever in this room to close the door here and in stunnel0 */
    open = 1;
    return open;
}
query_open()
{
    return open;
}
