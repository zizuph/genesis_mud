inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";
#include "../bazaar.h"

void
create_room()
{
    set_short("dance hall");
    set_long("A dark, smoke-filled room of uncertain dimensions. The "+
        "only illumination is the lanterns that rest on a square dais "+
        "positioned near the room's center. Encircling the stage is a "+
        "crowd of men avidly watching scantily-clad women undulate "+
        "provocatively. From a gallery on the north wall comes the "+
        "strange music which accompanies the dancers. There is a "+
        "curtained alcove to the north, and a circular stairwell leading "+
        "up.\n");

    add_item(({"dancer", "dancers"}),
        "There are three dancers on the stage. They are all wearing "+
        "thongs and pasties and a layer of oil on their skin.\n");
    add_item(({"first dancer", "first woman"}),
        "This woman is human. Her hair is very short and styled "+
        "in a spike. She is wearing a red thong covering her groin "+
        "and the pasties on her breasts glitter.\n");
    add_item(({"second dancer", "second woman"}),
        "This woman is elvish-looking, probably half-elven and half "+
        "human. Her hair is honey-brown in colour, and slightly "+
        "wavy. She is wearing a yellow thong and glittering gold "+
        "pasties on her breasts.\n");
    add_item(({"third woman", "third dancer"}),
        "This woman is human. She sways on the stage and has a  "+
        "blank look on her face. Her hair is very dark brown and "+
        "so long and thick it covers her body like a cloak.\n");
    add_item(({"lantern", "lanterns", "illumination"}),
        "They look like normal oil lanterns. The light they cast "+
        "is adequate to illuminate the women. but not much else.\n");
    add_item(({"dais", "stage"}),
        "It is square in shape and and raised knee-high above the "+
        "floor.  There are three women and some lanterns on the "+
        "stage.\n");
    add_item(({"men", "man"}),
        "There are men from all races and walks of life in here, "+
        "enjoying the entertainment provided by Icky Bod's Pub.\n");
    add_item(({"gallery", "north wall", "stairwell", "stairway"}),
        "The gallery is a balcony above the floor. There are musicians "+
        "in it, playing music and smoking. The stairwell leads up to it.\n");
    add_item(({"alcove", "curtain", "curtained alcove"}),
        "A curtain made of heavy brocaded silk separates an alcove from "+
        "The rest of the area. You find yourself wondering what is in "+
        "there.\n");

    set_tell_time(30);
    add_tell("A dancer stands over a lantern and shimmies.\n"+
        "The audience whistles appreciatively.\n");
    add_tell("Someone staggers down the stairs and bumps into "+
        "you, then pushes his way west.\n");
    add_tell("At a nearby table, two men discuss the attributes "+
        "of the dancers.\n");
    add_tell("An off-duty guard jeers drunkenly at the women.\n");
    add_tell("A dancer kneels on the stage and sways her hips "+
        "wildly.\n");
    add_tell("A richly-dressed merchant presses a coin into a "+
        "dancer's palm.\nShe "+
        "smiles and kisses him thoroughly in payment.\n");
    add_tell("There is a commotion on the other side of the room "+
        "as a goblin tries to pull one of the dancers off the stage.\n");
    add_tell("A gnome rises from his seat in a dark corner.\nAs "+
        "he brushes past you, your nose is assaulted with the "+
        "stenches of sweat and sex.\n");
    add_tell("A dwarf in a hooded cloak moans and collapses "+
        "against the wall.\n");
    add_tell("You watch as one dancer rubs oil on the other.\n"+
        "Their bodies gleam attractively in the lamplight.\n");
    add_tell("A man shouts: Where's Qalita?\nSeveral people point "+
        "toward the curtained alcove.\n");
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.

    add_prop(ROOM_M_NO_ATTACK, 
        "A troloby gives you an irritated look and says: Pleasure "+
        "only here! Take your business outside!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,
        "A troloby gives you an irritated look and says: "+
        "Your foul magic is useless in this room. Take your "+
        "business outside!");

    add_exit(INTR + "pub", "south", 0);
    add_exit(INTR + "alcove", "north",0);
	
}

int
up_message()
{
    write("A troloby steps out of the shadows.\nThe troloby says: "+
        "The gallery and Smoking Den are closed for a private party."+
        " Try again later.\n");
    return 1;
}

void
enter_inv (object ob, object from)
{
  ::enter_inv(ob, from);

  if (interactive(ob))
    start_room_tells();
} 
