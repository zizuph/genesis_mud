// /d/Avenir/common/outpost/secret/cv2_boardroom.c
/* 
 * /d/Faerun/guilds/vampires/rooms/cv1_boardroom.c
 *
 * Nerull 2021
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit VAMPIRES_STD_ROOM;


/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Boardroom");
    
    set_long("A stark contrast to the opulence of the entryway, this "
    +"service room does nothing but provide a media for information gathering "
    +"and sharing. More a cove than an actual room, there are only a "
    +"few items of real interest. There is a notice board affixed to "
    +"the far west wall that is neat and orderly. There is also a "
    +"large, gilded, iron cage sitting in a recess on the north "
    +"wall. The floor seems to be wrought from stone and polished "
    +"to a smooth luster and the walls are constructed of the same "
    +"dark mahogany as in other areas.\n");
    
    add_item(({"recess" }),
        "Set into the northern wall, this concave area houses a "
        +"large gilded cage.\n");

    add_item(({"north wall" }),
        "The walls are made from a polished, dark, "
        +"mahogany wood. This wall is recessed in the center, wherein "
        +"a cage resides.\n");
        
    add_item(({"south wall" }),
        "The wall is made from a polished, dark, mahogany wood.\n");
        
    add_item(({"west wall" }),
        "The wall is made from a polished, dark, mahogany wood. There "
        +"is a board on this wall.\n");
        
    add_item(({"east wall" }),
        "The wall is made from a polished, dark, mahogany "
        +"wood. Cut in its center is the doorway to the entryway.\n");

    add_item(({"walls"}),
        "The walls are made from a polished, dark, mahogany wood. "
        +"On the west wall is a board and recessed in the north wall "
        +"is a gilded cage.\n");
           
    add_item(({"doorway" }),
        "An opening cut into the middle of the east wall leading "
        +"into the entryway.\n");
                      
    add_item(({"cage" }),
        "This is a large iron cage, gilded for enhanced beauty. Inside "
        +"the cage, you can see an "
        +"inordinate amount of vampire bats that would likely deliver "
        +"messages for you. You can <borrow bat> if you need one.\n");
                      
    add_item(({"bat", "bats" }),
        "Long ears and even longer fangs, this vampire bat serves "
        +"as a messenger for its master. It is small with brown "
        +"fur and has wide, nearly translucent wings.\n");
                      
    add_item(({"ground", "floor" }),
       "The floor seems to be wrought from stone and polished "
       +"to a smooth luster.\n");
       
     add_item(({"ceiling", "roof" }),
       "The ceiling seems to be wrought from stone and polished "
       +"to a smooth luster.\n");
       
    room_add_object(VAMPIRES_GUILD_DIR + "boards/cv1_board");
    room_add_object(VAMPIRES_GUILD_DIR + "obj/cv1_rack");
                      

    add_exit(VAMPIRES_GUILD_DIR + "rooms/cv1_entryway", "east");
    
    reset_faerun_room();
}


public int
do_borrow(string str) 
{
   setuid();
   seteuid(getuid());
    
   object bat;
   
   if ((str != "bat") && (str != "vampire bat"))
   {
      notify_fail("Borrow what?\n");
      
      return 0;
   }
   
   bat = clone_object(VAMPIRES_GUILD_DIR + "obj/vampire_bat");
   
   if(bat->move(this_player()))
   {
      notify_fail("You cannot carry that much!\n");
      
      bat->remove_object();
      
      return 0;
   }
   
   write("You open the cage and borrow a vampire bat.\n");
   
   say(QCTNAME(this_player()) + " opens the cage and "
   +"borrows a vampire bat.\n");
   
   return 1;
}


public void
init()
{
    ::init();
    add_action(do_borrow, "borrow",0);
}