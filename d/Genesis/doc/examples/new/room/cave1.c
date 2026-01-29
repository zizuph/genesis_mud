/*
 * cave1.c
 */

/*
 * This is a small cave. It's inside but light still shines in through
 * the big opening. A hermit it sitting here and a torch is laying
 * on the ground.
 */

inherit "/std/room";

#include "ex.h"			/* Include our definitions */
#include "/sys/stdproperties.h" /* This file holds the definition of most
				 * properties in the game. They are variables
				 * hold weights, volumes on objects and many
				 * other things. */

/*
 * The creation of the room
 */
void
create_room()
{
    set_short("A cave");

    /*
     * There is an efun called ) that can come in handy now and
     * then. It puts carrige returns into a string so you won't have to add
     * a lot of \n in the text.
     *
    set_long("You are standing in a cave. The light is " +
	"not very strong in here. You can see that someone uses this " +
	"cave regularly. The cave continues west where it's even " +
	"darker and east is a road." +
	"\n");
    /*
     * The last \n needs to be added, and 76 tells how many characters to 
     * print on each line.
     */

    add_item("road", "You don't get a good look on it from here.\n");
    add_item( ({ "cave", "small cave" }),
	"The cave is not very interesting apart from that it continues\n" +
	"further west. It's getting very dark in that direction.\n");

    /*
     * Since we have nothing special in mind for arguments 3 and 4 to
     * add_exit() we don't bother defineing them. They will get default
     * values.
     */
    add_exit(EX_ROOM + "cave2", "west");
    add_exit(EX_ROOM + "room1", "east");

    /*
     * This room is inside. Let's show that by setting the property holding
     * this information. add_prop() is used to add a property to an object.
     * It can be used to change values of properties to. query_prop() is the
     * function to call if you want to know the value of a porperty. If a
     * property has not been set, query_prop() will return 0.
     *
     * ROOM_I_INSIDE is defined in /sys/stdproperties.h  You can get info
     * about it with the man command, 'man ROOM_I_INSIDE'. There you see
     * that if the property is set to 1 it indicates an inside room. If
     * set to 0 then it's outside. So, if the property is not set, query_prop()
     * will return 0 and thus default is that all rooms are outside.
     *
     * To get a listing of all standard properties, you can either look 
     * through /sys/stdproperties.h or try 'man -k properties'. Warning,
     * they are very many.
     */
    add_prop(ROOM_I_INSIDE, 1);

    /*
     * Now, we want objects to be loaded into the room, but create_room()
     * is the only function that will be called at creation.
     *
     * It's good coding practice to clone objects last in the creation of
     * a room because if for some reason your objects wouldn't load. The
     * execution of your instruction will stop, but you have already added
     * exits to the room, and a player can leave the room. So, add exits
     * before objects.
     *
     */

    
    /* NPCs are added with add_npc which will also set up things so the npc
     * is cloned again when it dies and reset_room is called 
     * For objects there is add_object which clones the object again if it
     * leaves the room.
     */
    add_npc(EX_MON + "hermit");
    add_object(EX_OBJ + "torch");
}
