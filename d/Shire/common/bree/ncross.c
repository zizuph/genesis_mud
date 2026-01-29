inherit "/d/Shire/common/lib/rom";
 
#include "defs.h"
void make_npcs();
 
object sonic;
create_rom()
{
    set_short("North of the Great Eastroad");
    set_long("You are standing in an intersection north of the " +
        "Great Eastroad which is running through Bree. There " +
        "are two new buildings on each side of the road, both " +
        "of marvelous construction, but one smaller than the " +
        "other. On the building to the east a sign on the wall " +
        "says 'Bank of Bree' and on the western house a large " +
        "sign can be seen. The road continues north towards the " +
        "north gate of Bree and towards the main living area. " +
        "South you will come to the Great Eastroad.\n");
            
    add_item(({"west sign", "western sign"}), 
        "The sign read: Closed.\n");
            
    add_item(({"golden sign","east sign","eastern sign"}),
        "@@sign_long");
    
    add_item(({"buildings","building"}),
        "These building are of the most finest art. They are " +
        "build by someone who really know their profession. Big " +
        "strong oaks have been used in these houses, and they " +
        "who bought it did not want to save any money!\n");
            
    add_exit(BREE_DIR + "new_bank","east",0,2);
    add_exit(BREE_DIR + "smith_temp", "west", 0,2);
    add_exit(BREE_DIR + "middle","south",0,2);
    add_exit(BREE_DIR + "brroad1.c", "north", 0);
 
    make_npcs();
 
}
 
 
reset_room()
{ 
    make_npcs(); 
}
 
 
init()
{
    ::init();
    add_action("do_read","read",0);
    
}
 
 
do_read(str)
{
    if(!str || str == "")
        return 0;
    if(str == "sign" || str == "west sign");
    {
        write(long_sign());
        return 1;
    }
    return 0;
}
 
 
long_sign()
{
    return "The sign reads: Closed.\n";
}
 
 
void
make_npcs()
{
   if(!sonic)
   {
    sonic = clone_object(BREE_DIR + "npc/sonic.c");
    sonic->move(TO);
    tell_room(TO,capitalize(LANG_ADDART(sonic->query_nonmet_name())) + 
        " comes sobbing into the room.\n");
    }
}
