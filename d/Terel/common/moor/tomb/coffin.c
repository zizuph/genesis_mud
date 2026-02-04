
/*
 * Coffin for entrance to "another world"
 *
 *  Make the player think they are dead but really we just move 
 *  them to another room.  
 */

// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room. This used to be an access to Sorgum's
//    workroom for mortals, back in the day ;)  I've modified it as an
//    alternate (and terrifying) route to get to Benton.
 
#include "/d/Terel/include/Terel.h"
#include "../local.h"
inherit TOMBDIR + "tomb_base";

/* prototype */
int do_dying(object tp);

// This is checked by tomb02 to see if player is allowed
// to enter this place, as a coffin only has room for one.
int is_occupied()
{
    object *op;
    int i;

    op = deep_inventory();
    for (i = 0; i < sizeof(op); i++)
        if (interactive(op[i])) return 1;
    return 0;
}

// Closing the lid makes the room dark, so lets make sure
// the light level resets when the player leaves the room.
void
light_room()
{
    add_prop(ROOM_I_LIGHT, 0);
	update_light(1);
	return 0;
}
    
void
create_room()
{
	::create_room();
    set_short("in coffin");
    set_long("You lie down in the coffin. It is not as comfortable " +
        "as it looked from the outside. You can feel sharp " +
        "spikes beneath the surface of the velvet that dig " +
        "painfully into your back. The velvet lining is covered " +
        "with odd looking bumps. At once you are overcome with " +
        "the powerful presence of death. The coffin lid beckons "+
        "to you.\n");
     add_item(({"bump", "bumps", "odd bumps"}), 
         "You take a closer look at the bumps and notice that they " +
         "are caused by sharp spikes just beneath the surface of the "+
		 "velvet.\n");  
    add_item(({"lid", "holes"}), "The lid has many holes in it. It can be closed.\n");		 

	 add_exit("tomb02", "exit", "@@light_room", 10);
	 add_exit("tomb02", "leave", "@@light_room", 10, 1); // non-ob
	 add_exit("tomb02", "open", "@@light_room", 10, 1); // non-ob
	 add_exit("tomb02", "out", "@@light_room", 10, 1); // non-ob
	 add_exit("tomb02", "up", "@@light_room", 10, 1); // non-ob	 
}

void
init()
{
     ::init();
     add_action("close_lid", "close");
}

// Close the coffin lid and start the movie sequence.
int 
close_lid(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }),
        " [the] [coffin] 'coffin' / 'lid'", str))
    {
        notify_fail("Close what? The coffin lid?\n");
        return 0;
    }
	
    add_prop(ROOM_I_LIGHT, -4);
    write("You close the lid. It is completely dark.\n\n" +
        "You cry out in agony as your body is pierced by sharp " +
        "spikes that emerge from beneath the velvet bottom of " +
        "the coffin. The spikes pass right through and " +
        "splinter the wood of the coffin lid above you.\n" +
        "You fear that your life may be slipping away.\n");     
    tell_room(TOMBDIR +"tomb02", 
        "The lid of the coffin shuts with a resounding " +
        "click.\nSuddenly the lid of the coffin is pierced by " +
        "blood-covered spikes.\nYou hear muffled screams of " +
        "agony followed by... silence.\n");
    TP->heal_hp(-(TP->query_max_hp() / 4)); 
    set_alarm(8.0, -1.0, &do_dying(TP));
    return 1;

}

// part 5
void
beyond_death(object tp) 
{ 
	if (!present(tp))
    {
        write("Your hands are shaking with adrenaline after your "+
            "brush with death.\n");		
        return;
    }		
	// If they haven't freaked out and left, reward them with a full heal
    tp->heal_hp(tp->query_max_hp());
	write("\nSuddenly your consciouness snaps back into your body!\n"+
        "You\n   have a terrifying\n           sensation of falling...\n"+
		"\n...And then you notice nothing hurts anymore!\n"+
        "\n   ...just in time to land hard on your bottom! Ouch!\n");
	tp->add_prop(COFFIN_ROUTE, 1);	
    tp->move_living("X", TOMBDIR + "tomb03");    
	light_room(); // lets reset the light for the next person.	
}

// part 4
void
at_death(object tp) 
{ 
	if (!present(tp))
    {
        write("Your hands are shaking with adrenaline after your "+
            "brush with death.\n");		
        return;
    }		
  
    write("\nNumbness... numbness creeps over you like a giant spider... "+
       "spreading from the wounds made by the spikes... "+
	   "\n\nYou can feel yourself floating away from your "+
       "body..."+
       "\n...You have a sudden conviction that after your death "+
       "you will once again be what you were before your birth...\n");  
    tp->heal_hp(-(tp->query_hp() / 5));
	set_alarm(10.0, -1.0, &beyond_death(tp));	
}

// part 3
void
near_death(object tp) 
{ 
	if (!present(tp))
    {
        write("Your hands are shaking with adrenaline after your "+
            "brush with death.\n");		
        return;
    }		
  
    write("\nThe pain is unbelievable... images of the life you "+
        "have lived flash into your mind's eye...\n"); 
    tp->heal_hp(-(tp->query_hp() / 5));
	set_alarm(10.0, -1.0, &at_death(tp));	
}

// part 2
void
do_dying(object tp)
{
	if (!present(tp))
    {
        write("Your hands are shaking with adrenaline after your "+
            "brush with death.\n");		
        return;
    }		
    
    write("You desperately attempt to cling to life and awareness, "+
        "but the spikes... have done... so... much... damage.\n"+
        "\nThe pain pushes your mind away from your body and you "+
        "feel yourself begin to lose consciousness...\n");
    tp->heal_hp(-(tp->query_max_hp() / 4));
	set_alarm(10.0, -1.0, &near_death(tp));
	return;
}
