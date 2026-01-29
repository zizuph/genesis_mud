// B.I.P.S. (/d/Avenir/common/bazaar/post.c)
// creator(s):   Triana 1994
// last update:  Tepisch Nov 94
// purpose:      postal service            
// note:         updated to use Glindor's new /lib/post
// bug(s):
// to-do:  

inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include "/d/Avenir/common/bazaar/bazaar.h"

create_room()
{
     set_short("Bazaar Island Postal Service Center");
     set_long("This is the Main Office of the Bazaar Island Postal "+
         "Service.\nIt is very cold and rather silent here.  Stacks "+
         "of yellowing papers clutter the floor and crumble to dust "+
         "underfoot.  Near the center of the room is a stone counter,"+
	 " behind which cowers a shivering clerk.  On the counter " +
         "rests a bright red placard.\n"+
	 get_std_use());
   
     AI("counter","It looks to be cut from the same greyish "+
         "stone as the walls.\n");
     AI(({"placard","red placard","bright placard","bright red placard"}),
          "Now Available!\n"+
         "   Reliable foot messengers for hire upstairs.\n   Better " +
         "than pigeons or rats---much more intelligent!\n   Try one "+
         "Today. Satisfaction guaranteed.\n");

     ACI(({"placard","red placard","bright placard","bright red placard"}),
          "read", "            Now Available!\n"+
         "   Reliable foot messengers for hire upstairs.\n   Better " +
         "than pigeons or rats---much more intelligent!\n   Try one "+
         "Today. Satisfaction guaranteed.\n"); 
     AI("clerk", "He is better dressed than most of the peasants " +
          "running around in the marketplace, but still looks " +
          "shabby and under-fed.\n");
     AI(({"wall","walls"}), "The walls are cut from a rough greyish "+
          "stone.\n");
     AI(({"paper", "papers", "letters"}), "There are thousands of "+
          "old letters piled about in complete disarray.\n");
     AI("dust", "It is brownish-yellow and coats the floor. Your " +
          "every step stirs it up into the air.\n");
     AE("/d/Avenir/common/bazaar/extr/str3.c", "west", 0);
     AE("/d/Avenir/common/bazaar/intr/office.c", "up", "@@temp_block");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.
    add_prop(ROOM_M_NO_ATTACK, "You get a feeling that the goddes Nantur "+
	    "disapproves of fighting in this place.");
	add_prop(ROOM_M_NO_MAGIC_ATTACK, "You get a feeling that the goddess "+
	    "Nantur disapproves of fighting in this place.");


}

void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
}

int
temp_block()
{
   write("The stairs creak and groan as you walk up.\n");
  return 0;
}
