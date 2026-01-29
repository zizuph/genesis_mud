/*
 * The Queen's closet in the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
#define MIRROR_ROOM	"/d/Emerald/telseron/castle/mirror_room.c"

int enter_passage(string str);
int reset_passage;      // flag to open and close passageway

 
void reset_room();
void
create_room()
{
    object door;
    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
    set_short("The Queen's closet");
    set_long("   As you stand in the Queen's closet, you know " +
        "she is a sophisticated dresser with a sense of style " +
        "and great taste. Tailors from all over the land take " +
        "great pride in their work when she wears their clothes. " +
        "Rows of elegant apparel and accessories are kept here. " +
        "The room is spacious and richly decorated as it also " +
        "doubles as the dressing room. A skylight encompases the " +
        "whole ceiling, filling the room with light. A deep " + 
        "luxurious carpet covers the floor. Assorted furniture " + 
        "can be seen here. Three full size mirrored surfaces are " +
        "set in a semi-circular oak stand. The room smells " +
        "pleasently.\n\n");
 
    add_item("clothes",
        "Rows of gowns, cloaks, hoses, undergarments, petticoats, " +
        "blouses, and pantsuits fill the shelves.\n");
    add_item("accessories",
        "You see necklaces, rings, bracelets, earrings, belts, " +
        "gloves, hatboxes, brooches, hair pins and clips, and " +
        "other assorted accesories stored on the shelves. Their " +
        "excellent craftsmanship is a testament to elven skill " +
        "when working gemstones for their pursposes. Many of the " +
        "accessories are inlaid with emeralds, diamonds, rubies, " +
        "amethyst, sapphires, topazes, pearls, and other valuable " +
        "materials. They are all worth a king's, or queen's, ransom.\n");
    add_item("furniture",
        "A vanity, chairs, stools, and a raised platform are spread " +
        "around the room.\n");
    add_item("gowns",
        "The gowns are all beautiful and arranged by colour and " +
        "style. You notice that the colours vary from the palest " +
        "yellow to deep red, gold, brown, and blue. Some gowns are " +
        "delicately patterned while others are plain. Some are " +
        "tastefully cut in the bodice, strapless, backless, and " +
        "formfitting. Some skirts are full while other are slit.\n");
    add_item("cloaks",
        "Various cloaks hang in the closet. Most are full length " +
        "and have attached hoods. They come in a variety of colours " +
        "to suit every occaison and taste of the Queen. Some are " +
        "fur-lined while others are made entirely of furs.\n");
    add_item("hoses",
        "These lovely items are made of a silky material. They " +
        "whisper as they glide across your skin. The colours are " +
        "vibrant and look too good to be real. Some have designs woven " +
        "into them while others are plain.\n");
    add_item("undergarments",
        "You notice camisoles, slips, underslips, corsets, garter " +
        "belts, other undergarments.\n");
    add_item("petticoats",
        "The petticoats are well cared for. They are pressed and " +
        "crisply starched.\n");
    add_item("blouses",
        "The blouses are light and airy. They are in a wide " +
        "variety of colours and designs.\n");
    add_item("pantsuits",
        "The Queen is a daring dresser for having pantsuits. " +
        "These are in dark colours and tailored for her. Some " +
        "are plain, plaids, and other tasteful designs.\n");
    add_item("necklaces",
        "The necklaces are beautiful and priceless. Some are long " +
        "and flowing while other necklaces are simple yet elegant.\n");
    add_item("rings",
        "Countless rings are here. Many of them match the necklaces, " +
        "bracelets, and earrings. They are beautiful and sparkle in " +
        "the light.\n");
    add_item("bracelets",
        "You notice rows of bracelets. The Queen seems to love " +
        "adorning her arms. Some are simple while other bracelets " +
        "are large yet elegant.\n");
    add_item("earrings",
        "The earrings are beautifully crafted. Some are large while " +
        "others are simple. They twinkle as the gems catch the light.\n");
    add_item("belts",
        "Various belts of different lengths and of different " +
        "materials. Many are fashioned of gold and silver, which " +
        "have been worked into beautiful designs. Other belts are " +
        "made of natural materials.\n");
    add_item("gloves",
        "You notice a wide variety of gloves. They accessorise the " +
        "Queen's apparel. Some are large and cover most of the arm " +
        "while others are small and cover only the hand and wrist. " +
        "They are made of may materials and come in a wide variety " +
        "of colours and designs.\n");
    add_item(({"hat", "hats", "hatboxes"}),
        "When you open the hatboxes, you see a wide variety of hats. " +
        "They all come in a variety of colours, sizes, and styles. " +
        "Some are plain while others are decorated with feathers, " +
        "gauze, lace, and other man");
    add_item("brooches",
        "These elegant pins are made of gold, silver, coral, " +
        "shell, mother of pearl, and other elegant materials. " +
        "Some are encrusted with gems while others are decorated " +
        "simply. Some even have small baubles hanging from them. " +
        "They are designed to be worn as ornaments for the " +
        "shoulders or throat and as ornaments for clothing. " +
        "Some have clasps while others are pins.\n"); 
    add_item("hair clips",
        "These are elegant combs that are designed to pull the " +
        "Queen's hair back from her lovely face. The are simple " +
        "in design but decorated with gems.\n");
    add_item("vanity",
        "This dressing table is one of the most important pieces " +
        "of furniture in the castle, or so the Queen thinks. It " +
        "large and made from oak. A mirror sits in front of the " +
        "vanity. The surface of the table is covered with small " +
        "bottles of makeup and perfumes, a hair brush and a comb.\n");
    add_item("bottles",
        "They are of cut crystal and hold various makeups and "+ 
        "perfumes.\n");
    add_item("makeup",
        "You see eyeliner, mascara, lipsticks, nail polishes, and " +
        "powders for the face.\n");
    add_item("perfume",
        "Different perfumes can be seen. Some fragrances you can " +
        "recognize, like some of the floral ones, but there are " +
        "other scents are unknown to you.\n");
    add_item("hair brush",
        "The hair brush is large and made of gold. The teeth are " +
        "fashioned of silver while the handle and back are inlaid " +
        "with ivory.\n");
    add_item("comb",
        "The comb is made of gold. It is inlaid with ivory.\n");
    add_item("mirror",
        "The mirror is made from a piece of polished steel. It " +
        "reflects everything in the room. As you look at it, you " +
        "see yourself.\n");
    add_item("camisoles",
        "You see many of them hanging here. They are sleeveless " +
        "and made of silk. The Queen has quite a selection here. " +
        "They come in various colours, white being the dominant. " +
        "Some are frilly, while others are plain.\n");
    add_item("underslips",
        "A collection of underslips are here. They are made of " +
        "cotton and are used often. They are worn under the " +
        "petticoats to protect the Queen from chafing.\n");
    add_item("slips",
        "Like the camisoles, these are primarily white. They are " +
        "worn to protect the Queen's delicate skin.\n");
    add_item("corsets",
        "These special undergarments are fashioned from strong " +
        "material. They have laces on the front that are cinched to " +
        "enhance the figure of the Queen and lift the bustline. " +
        "They are primarily black and white. Delicate laces decorate " +
        "the corsets.\n");
    add_item("garter belts",
        "These elastic bands are frilly and in many colours. They " +
        "hold up the hoses that the Queen wears.\n");

    reset_passage = 0;

   door = clone_object( TOWNSHIP_DIR + "castle/doors/mirror_room_in");
   door->move(this_object());

    add_exit( TCASTLE_DIR + "q_room", "southeast");
}
 
void
reset_room()
{
}

void
init()
{
     add_action("knock_wall", "knock");
     add_action("enter_passage","enter");
     add_action("touch_wall", "touch");
     ::init();
}
 
int touch_wall(string str)
{
    if (str=="door")
    {
        write("You touch the door, causing it to briefly glow with a " +
	"blue light.\n");
        say (QCTNAME(this_player()) + " touches the door, causing the wooden " +
           	"surface to briefly glow with a blue light.\n");
        tell_room(MIRROR_ROOM, "You feel a disturbance in the " +
	"room as the door glows for a moment.\n");
        return 1;
    }
    NF("Touch what?\n");
}

int knock_wall(string str)
{
    int chance;
 
    if( str == "on wall" || str == "wall")
        {
            chance = (random(5));
            if (chance !=1)          // wall doesn't open
            {
                write("You feel dumb knocking on a stone wall.\n");
                say (QCTNAME(this_player()) + " knocks on a stone wall.\n");
                if (reset_passage == 1)
                {
                    tell_room("q_closet", "The wall closes, hiding all " +
                        "traces of the secret passage.\n");
                    reset_passage = 0;
                }
            }
            else
            {
                write ("The wall opens up, revealing a secret " +
                    "passage.\n");
                reset_passage = 1;
            }
            return 1;
        }
        else
        {
            write ("Knock on what?\n");
            return 1;
        }
}
 
 
int
enter_passage(string str)
{
 
    if ((str == "passage" || str == "passageway") && reset_passage == 1)
    {
        write ("You step into a dark passage.\n");
        say (QCTNAME(TP) + " leaves into a dark passage.\n");
        TP->move_living( "M", TCASTLE_DIR + "mirror_room", 0, 0);
        tell_room( TCASTLE_DIR + "q_room",
            QCTNAME(TP) + " arrives from a secret passage.\n", TP);
        return 1;
    }
    else
    {
        write ("You run into a wall.\n");
        say (QCTNAME(TP) + " runs into a wall.\n");
        return 1;
    }
    reset_passage = 0;
   
}
