#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";
inherit "/lib/library";

int kenderout = 0;


public int
library_exit_block()
{
   
    if (::library_exit_block())
    {
       
        write("You cannot leave with one of the books!\n");
        return 1;
    }
    
    if (this_player()->query_prop(ICOUCHSITTING))
    {
    	write("You must 'rise' from the couch first.\n");
    	return 1;
     }


     

    
    return 0;
}



 
void
create_nov_room()
{
                   
    set_name("In the living room");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("In the living room");
    set_long("This room has several couches and small coffee " +
    "tables, although you doubt much coffee is served here. You come " +
    "here to take a moment away from the necromantic studies. On the " +
    "south wall, you see a black bulletin board with " +
    "some notes on it. Three of the walls are lined with sturdy shelves to " +
    "hold the many heavy books. In the right corner of the room you see " +
    "a golden cage holding an excited kender. On the left side of the " +
    "room is an old stone fireplace, with a small fire burning, it could " +
    "use some stoking. On the middle of the floor is a big table " +
    "with chairs surrounding it, it looks like a game table of a sort.\n");
    
    add_item(({"game", "gametable"}),
        "You heard about these games before. The so called Magical games.\n");
        
    add_item(({"tables", "table"}),
        "These are small tables each with a lamp providing light for " +
        "reading. The tables has just enough room for a book or two.\n"); 
        
    add_item(({"couch", "couches"}),
        "The couches is spread out through the room, they are all constructed " +
        "precisely alike. With tall backs and soft materials, draped with " +
        "a red velvety fabric they make a comfortable sitting, perfect for reading.\n");          
        
    
    add_item(({"fireplace"}),
        "The fireplace is made out of stone, it has some wood placed in it. It " +
        "is lit. On top of the fireplace you see two skulls sitting " +
        "on the mantlepiece, looking at you.\n");  
        
    add_item(({"skull", "skulls", "mantlepiece"}),
        "Two human skulls rests next to eachother on the mantlepiece. For some reason, " +
        "you feel that they stare at you.\n");      

    add_item(({"cage"}),
        "The golden cage holds a kender most likely captured to investigate " +
        "its curiousity and courage, or perhaps it just happened to be " +
        "the nearest creature to be target for the torment and amusement " +
        "of the Necromancers. The cage is surrounded by a red transparent " +
        "light, burning anything that touches it. You see a rope hanging here " +
        "leading from a mysterious pouch hanging on the side of the cage up " +
        "through a pulley.\n");
        
    add_item(({"kender"}),
        "The energetic tortured kender looks excited to find out what is going to happen next.\n");
        
    add_item(({"fire"}),
        "Burning wooden logs pops and crackles in the fireplace, radiating a " +
        "flickering light and heat.\n");    
        
    add_item(({"books"}),
        "Many books rests in the sturdy shelves.\n");    
        
    add_item(({"shelf", "shelves"}),
        "Row after row of heavy dusty books occupy the sturdy shelves.\n");        
        
    add_item(({"rope"}),
        "The rope hangs here, leading from a mysterious pouch hanging on the side of the " +
        "cage up through a pulley.\n");    
        
    add_item(({"pouch"}),
        "It is a regular leather pouch just with a sign 'MYSTERIOUS POUCH' attached to it.\n");    


     

    add_exit(NOV_DIR + "temple/nccentral",   "southeast", library_exit_block);
    
    
    set_borrow_required(1);

    
    set_book_directory(NOV_DIR +"log/library/book_dir/");
    
    set_book_removal_directory(NOV_DIR +"log/library/book_dir/removed/");

    set_book_approval_directory(NOV_DIR +"log/library/book_dir/approval/");
    
    add_book_shelf(({ "general", "maps", "artifacts", "herblore", "stories", "guildlore", "misc" }));
    create_library();


    
    clone_object(NOV_DIR + "obj/nboard")->move(this_object());

    
}


public int
library_admin_access()
{
    /* We'll give admin access to council members of the occupational
     * guild "Some example guild"
     */
    if (this_player()->query_guild_member_lay(GUILDNAME) &&
        this_player()->query_skill(COUNCIL))
    {
        return 1;
    }

    /* We'll give admin access to wizards */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* No-one else has admin access */

    write("You do not have permission to do that.\n");
    return 0;
}

public int
library_write_access()
{
    /* We'll allow any member of the occupational guild "Some example guild"
     * to write books
     */
    if (this_player()->query_guild_member_lay(GUILDNAME))
    {
        return 1;
    }

    /* We'll allow wizards to write books */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* No-one else has permission to write books */
    write("You do not have permission to do that.\n");
    return 0;
}

void
wake_kender()
{
	tell_room(this_object(), "The kender wakes up again.\n");
	kenderout = 0;
}


int
do_pullr(string str)
{

       if (str != "rope")
       {
       	   return 0;
       	}
       	
       	if (kenderout == 1)
       {
       	   write("The kender is still passed out from its last " +
       	   "torment, you will have to wait a few minutes before you can have the pleasure again.\n");
 
       	   return 1;
       	}
       	
      write("As you pull the rope, the pouch gets close to the Kender, who " +
      "immediately reaches out for it, burning his right arm horribly as " +
      "he lets out a scream of pain, struggling to not let go of the " +
      "pouch until he passes out from the pain.\nYou let go of the rope " +
      "again with a satisfied smile on your face.\n");
      
      tell_room(environment(this_player()), "As "+QCTNAME(this_player())+" pulls the rope, the " +
      "pouch gets close to the Kender, who immediately reaches out for it, burning " +
      "his right arm horribly as he lets out a scream of pain, struggling to not let " +
      "go of the pouch until he passes out from the pain.\n"+QCTNAME(this_player())+" lets go " +
      "of the rope again with a satisfied smile on "+this_player()->query_possessive()+" face.\n",({this_player()}));
      
      kenderout = 1;
      set_alarm(120.0,0.0, &wake_kender());
      
      return 1;
}


int
do_csit()
{
	if (this_player()->query_prop(ICOUCHSITTING))
	{
		write("You are already sitting in the couch.\n");
		return 1;
	}
	
	write("You sit down in one of the comfortable couches.\n");
	
	tell_room(environment(this_player()), QCTNAME(this_player())+" sits down in one of " +
	"the couches, relaxing.\n", this_player());
	this_player()->add_prop(ICOUCHSITTING, 1);
	this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is sitting, relaxing in one of the couches");
	
	return 1;
}

int
do_crise()
{
	if (!this_player()->query_prop(ICOUCHSITTING))
	{
		write("But you arent sitting in the couch!\n");
		return 1;
	}
	
	write("You rise on your feet.\n");

	tell_room(environment(this_player()), QCTNAME(this_player())+" rises on "+this_player()->query_possessive()+" feet.\n", this_player());
	this_player()->command("stretch");
	this_player()->remove_prop(ICOUCHSITTING);
	this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
	
	return 1;
}


void
init()
{
    ::init();


    add_action(do_pullr,"pull");
    add_action(do_csit, "sit");
    add_action(do_crise, "rise");

    /* Add the library commands */
    init_library();
}
