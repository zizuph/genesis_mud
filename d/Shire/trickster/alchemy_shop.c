/*
**    This is the shop where the Trickster obtain the Trickster
**    Mischief from the alchemist found in /d/Shire/Trickster/npc/alchemist.c
**    The alchemist takes care of all trading and money exchanges.
*/

#pragma save_binary

inherit "/d/Shire/room.c";
#include "/d/Shire/sys/defs.h"
#include "trickster.h"

#define ALCHEMIST TRICK_DIR + "npc/rumple"


/*  Prototypes */
void reset_room();

void
create_room()
{
    set_short("An alchemist's shop");
    set_long(
      "You have entered the Alchemist's shop in the Trickster " +
      "guild hall. The room is filled with bubbling noises coming from " +
      "multi-coloured, liquid-filled flasks.   There is a counter here " +
      "where the resident alchemist can usually be found sitting behind, serving " +
      "the needs of the Tricksters, when they come by and pay him a visit. " +
      "Torches cast long shadows in the room, giving it an unsettling " +
      "presence.  There is a sign against the counter providing some " +
      "instructions.\n");

    add_item("sign", "Read it silly.\n");
    add_item("instructions", "Read them silly.\n");
    add_cmd_item("instructions", "read", "@@my_sign@@");
    add_cmd_item("sign","read","@@my_sign@@");

    add_item("counter", "On this counter lies various alchemical " +
      "devices used for making the tools of mischief that the alchemist " +
      "hands out to the Tricksters, for a price of course.\n");

    add_item(({"torches", "torch", "shadow", "shadows"}),
      "The torches cast a sinister shadow in the room, along with the " +
      "strange noises coming from the bubbling flasks. The entire room " +
      "gives you a queer feeling.\n");

    add_item(({"flasks","mulit-colored flasks","multi-coloured flasks",
	"liquid-filled flasks","mulli-coloured liquid-filled flasks"}),
      "You wonder in amazement what strange potions these flasks " +
      "could contain, if they have the power make you grow, or shrink " +
      "or possibly the power to turn you into a newt!\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TRICK_DIR + "hallway","west",0,1);

    reset_room();
}

string
my_sign()
{
    return(
      "Welcome to the Tricksters Alchemy Shop!\n\n"+
      "This is where you can receive the various Trickster\n"+
      "Mischief from Rumple the alchemist, for a price of course.\n"+
      "\nYou will receive these objects in this order if you are\n"+
      "tricky enough to get your hands on them.\n\n"+
      "\tSneezepowder\tItchingpowder\tSmokebomb\n"+
      "\tStinksplash liquid\tand\tLaughing gas.\n"+
      "You can only have a maximum of 3 of each type at one time.\n\n"+
      "Disguise material can also be purchased here as well.\n"+
      "If you do not have a disguise kit, ask the alchemist here about one.\n\n"+
      "\tTo use this shop type: <outfit stick/kit>\n\n");
}

void
reset_room()
{

    if (!present("rumple",TO))
    {
	CLONE_NPC(ALCHEMIST);
    }
}
