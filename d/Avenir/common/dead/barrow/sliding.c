// file name:    sliding.c
// creator(s)    Lilith, Aug 2021
// last update:    
// purpose: room connecting the catacombs and the barrow
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/barrow_base";
#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"

int
do_in()
{
    object slide = find_object(BARROW+"slide");

    if(slide && sizeof(filter(all_inventory(slide), interactive)))
    {
        write("You cannot fit in there.\n");
        return 1;
    }
    write("You squeeze into the slit in the wall of the chute.\n");
    return 0;
}

void
create_barrow_room()
{
    set_short("slipping and sliding in a chute");
    set_long("Given the slant of this chute, it is difficult to "
	+"get your footing.\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "Darkness presses upon you "
      +"from all directions. The air smells of moisture "
	  +"and corpses. You can feel wind pushing past you.\n");
    // Swallowed by earth, the darkness is deep.
    add_prop(ROOM_I_LIGHT, -10);

    // In the event mortal doesn't get moved out of here
    // Lets give them some exits 
    add_exit(CRYPT+"crypt66","down");	
    add_exit(BARROW+"barrow15", "up");
    add_exit(CRYPT+"crypt66","out", 0, 0, 1);
    add_exit(BARROW+"slide","in", do_in, 0, 1);	
}

/*
*   Drop the player into the crypt.
*/
void
move_along(object tp)
{
    // Check to make sure they're still here.
    if (!present(tp)) return;

    tp->catch_msg("You land with a tremendous splash "
      +"in a pool of what you hope is water."
      +"\n");

    tp->add_panic(10);
    tp->move_living("M", CRYPT+"crypt66");
	STATSERV_LOG_EVENT("crypt", "Entered Crypt via BOGL");


}	

// If player is here for too long, move them along.
void 
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from);

    if(!interactive(ob)) return;
    set_alarm(5.0, 0.0, &move_along(ob));

}
