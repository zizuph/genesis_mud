/*
 * Lounge in the Union guildhall
 *  Lilith 2.10.2004
 *
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#define SEE_NORTH ({ \
    HALL +"_n1", HALL +"_n2", HALL +"_n3", \
    HALL +"_w2", HALL + "_w1", ROOM + "crossing" })

public int ishard;
public int query_ishard_num(void)	{ return ishard; }
public void set_ishard_num(int val)	{ ishard = val;  }

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return ", where you can see "+ COMPOSITE_LIVE(live);
}

public void
reset_room(void)
{
    object cushion;
    int size = NUM_ITEMS("_union_cushion");

    while(size < 8)
    {
	size++;
	cushion = clone_object(OBJ + "s_cushion");
	cushion->make_random();
	cushion->set_no_show_composite(1);
	cushion->move(TO, 1);
    }

    set_ishard_num(15);

    // Reset the table too.
    present("salon:table")->reset_container();
}

public void
union_room(void)
{
    set_short("salon of shadows");
    set_long("In sharp contrast to the stark simplicity of the rest "+
	"of the Halls of Shadow, this salon is opulently appointed. "+
	"It is spherical in shape, with a domed ceiling draped in "+
	"fluttering shadows. The floor, piled ankle-deep in plush "+
	"carpets and fur pelts, is a smooth slab of polished stone. "+
	"In the center of the room is a low table around which several "+
	"cushions have been strewn for lounging in comfort. The bluish "+
	"limestone walls are inset with massive panels of white granite "+
	"etched with luminous hollows. Two large tapestries stand "+
	"sentinel on either side of a statue of Jazur, the Patron of "+
	"the Shadow Union. Directly opposite the statue, a circular "+
	"entrance leads back into the main passage@@north_view@@.\n");

    add_item(({"floor","ground","slab"}),
	"What you can see of the floor, through the piles of "+
	"carpets, furs, and cushions, reveals that it is the "+
	"same blue limestone as the rest of the room.\n");
    add_item(({"carpet","carpets"}),
	"Gorgeous, thick carpets in an array of jewel-tones "+
	"cover most of the floor.\n");
    add_item(({"pelts","furs","fur","fur pelts"}),
	"Here and there are scattered the trophy pelts which "+
	"warriors have brought home: bicorn, panther, pahloor, "+
	"wolf, and yeti are some of those you recognize.\n");
    add_item(({"wolf", "wolf fur", "wolf pelt"}),
	"These wolf pelts are the golden brown colour of the "+
	"winged wolf native to the Utterdark.\n");
    add_item(({"yeti", "yeti fur", "yeti pelt"}),
	"These pelts were collected by warriors who were "+
	"successful in their hunt of the yeti on Icewall.\n");
    add_item(({"pahloor", "pahloor fur", "pahloor pelt"}),
	"These pelts are the rich black colour of the "+
	"elusive pahloor native to the Utterdark.\n");
    add_item(({"panther", "panther fur", "panther pelt"}),
	"These pelts are the silken gray colour of the "+
	"vicious panthers which roam the Holm.\n");
    add_item(({"bicorn", "bicorn fur", "bicorn pelt"}),
	"These pelts were taken as trophies by warriors "+
	"who fought the bicorns upon the Holm.\n");
    add_item(({"wall","walls","limestone"}),
	"The stone of the walls is soft and smooth, a pale blue "+
	"limestone that reflects the light.\n");
    add_item(({"statue", "jazur", "statue of jazur"}), "@@statue_desc");
    add_item(({"roof","ceiling", "shadow", "shadows", "dome"}),
	"The ceiling overhead is ornately carved. Shadows "+
	"seem to flutter and slide along the dome, "+
	"waving like pennants in a breeze.\n");
    add_item(({"white stone", "granite", "mica", "panel", "panels"}),
      "Hard and white, it is sprinkled with tiny crystals and mica "+
      "that twinkle in and magnify any available light. Hollows have "+
      "been carved into this stone at fairly regular intervals.\n");
    add_item(({"hall","corridor","north","hallway","passage",
	    "entrance", "circular entrance", "doorway"}),
	"Through the circular entrance you can see the hallway "+
	"that stretches off to the north@@north_view@@.\n");
    add_item(({"tapestry", "tapestries"}),
	"There are two, one on the right, and one on the left.\n");
    add_item(({"left tapestry", "trefoil", "trefoil tapestry",
	    "tapestry of a trefoil"}), "@@ltape@@");
    add_item(({"right tapestry", "flame", "sphere and flame",
	    "tapestry of a sphere"}), "@@rtape@@");
    add_item(({"map", "map of sybarus", "island" }),
	"It is a map of Sybarus, depicting each island glowing "+
	"under the light of the Source.\n");
    add_item(({"carvings", "carvings on the ceiling"}), "@@carved");
    add_item(({"hollow", "hollows", "light-hollow"}), "@@hollow_desc");

    add_cmd_item(({"wall","walls","stone","limstone"}), "touch",
	"It is smooth and soft.\n");
    add_cmd_item(({"floor","ground"}), "touch",
	"It is firm and smooth beneath its covering of carpets "+
	"and pelts.\n");
    add_cmd_item(({"tapestry","tapestries"}), "touch",
	"They are thick and heavy.\n");

    add_exit("hall_w2", "north");

    add_object(OBJ + "table_s", 1, &->reset_container());
    reset_room();
}

public string
statue_desc(void)
{
    string str;

    if (IS_MEMBER(TP))
    {
	str = "This is a statue of Jazur, Mistress of Passion, "+
	    "Regent of the 12th Hour, and your Patron. ";
    }
    else
    { 
	str = "Before you is a statue of Jazur, the patron goddess "+
	    "of the Shadow Union. ";
    }

    return str + "The statue is carved from a dark, purplish-red stone. "+
	"Her form as rendered by the talented sculptor is undeniably "+
	"feminine. She is wearing a thin robe belted at the hips with an "+
	"ornate mekhala. Her hair is long and flowing, restrained only by "+
	"the circlet from which a small black sphere dangles across her "+
	"brow. Her eyes are heavy-lidded, her mouth parted in an inviting "+
	"half-smile, lending a gloss of passion to an expression of savage "+
	"intensity. In her right hand she holds a knife, point down, over "+
	"her left palm, as though preparing to draw a cut into her hand.\n";
}

public string
carved(void)
{
    if (!present(SWAY_ID_ALL, TP))
    {
	return "You cannot see the detail of the carvings due "+
	    "to the dense shadows draping from the ceiling.\n";
    }

    return "In the altered state of the Sway, the carvings "+
	"gleam with fluid intensity, as though illuminated "+
	"from within.\n"+
	"   Beyond blood and flame destiny calls the proven ones\n"+
	"	to find the Tomb of Akram and the Altar of Jazur.\n";
}

public string
ltape(void)
{
    if (!present(SWAY_ID, TP))
    {
	return "The tapestry on the left depicts a Golden Trefoil "+
	    "super-imposed upon a map of the Sybarun Isles.\n";
    }

    return "The tapestry on the left depicts a Golden Trefoil "+
	"super-imposed upon a map of the Sybarun Isles.\n"+
	"In the altered state of the Sway, your deeper sight "+
	"tracks a luminous script.\n"+
	"   Thou art charged to defend Sybarus with a\n"+
	"   passion known only to those who serve Jazur.\n";
}

public string
rtape(void)
{
    if (!present(SWAY_ID, TP))
    {
	return "The tapestry on the right depicts a blue flame "+
	    "rising from a black sphere.\n";
    }

    return "The tapestry on the right depicts a blue flame "+
	"rising from a black sphere.\nIn the altered state of "+
	"the Sway, your deeper sight tracks a luminous script.\n"+
	"  The Passion of the Flame is all-encompassing,\n"+
	"      yet it does not consume the Sphere,\n"+
	"      that symbol of unity and perfection,\n"+
	"        of which you are a vital member.\n";
}

public void
do_cushion(object ob)
{
    if (present(ob))
	ob->set_no_show_composite(1);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (ob->id("cushion"))
	set_alarm(1.0, 0.0, &do_cushion(ob));
}

public string
hollow_desc(void)
{
    string str;

    switch(ishard)
    {
    case 0:
	str = "The hollows are completely dark and empty.\n";
	break;
    case 1..5:
	str = "Most of the hollows are empty, but there are a "+
	    "some which still give off light and contain "+
	    "shards of glowing crystal.\n";
	break;
    case 6..8:
	str = "Half of the hollows are dark and empty, but the "+
	    "rest contain small shards of glowing crystal.\n";
	break;
    case 9..12:
	str = "Light shines from most of the hollows. They "+
	    "contain small shards of glowing crystal.\n";
	break;
    case 13..15:
	str = "The hollows are all giving off light, filled as "+
	    "they are with small, glowing shards of crystal.\n";
	break;
    default:
	str = "The hollows give off a glowing light which comes "+
	    "from small shards of crystal.\n";
	break;
    }

    return "Hollows have been carved into the white granite. They "+
	"are located just above eye-level, so as not to cause "+
	"a glare. "+ str;
}

public int
do_get(string str)
{
    object shard;

    notify_fail("Get what from where?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({ }),
	    "[a] / [the] [small] [glowing] 'shard' / 'shards' / 'crystal' "+
	    "[from] [the] 'hollow'"))
	return 0;

    if (!ishard--)
    {
	write("There aren't any crystal shards left.\n");
	return 1;
    }

    write("You reach up into one of the hollows and take a glowing "+
	"crystal shard from it.\n");
    say(QCTNAME(TP) + " reaches up into one of the hollows and takes "+
	"a glowing crystal shard from it.\n");

    shard = clone_object(HOLM + "obj/shard");
    shard->set_volume(random(5) + 1);
    shard->move(TP, 1);

    return 1;
}

public int
do_pray(string str)
{
    notify_fail("Pray to who? Jazur?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({ }), "[to] / [before] [the] "+
	    "[statue] [of] [the] [goddess] 'jazur'"))
	return 0;

    write("You bow your head to the statue and pray to Jazur for "+
	"the gifts of passion and grace.\n");
    say(QCTNAME(TP) + " bows "+ TP->query_possessive() +" head "+
	"in prayer to Jazur.\n");

    if (present(SWAY_ID, TP))
    {
	TP->emote_adjust_union_virtue(US_GRACE, 5);
	write("Within the Sway, the voice of Jazur answers your prayer:\n"+
	    "   Of my essence I have given unto you.\n"+
	    "   Passion to draw blood without feeling pain.\n"+
	    "   Passion to seek perfection in all you pursue.\n"+
	    "   Passion to take pleasure as it comes.\n"+
	    "   Passion to know your other selves as I do.\n");
    }
    return 1;
}

public void
init(void)
{
    ::init();
    add_action(do_get,  "get");
    add_action(do_get,  "take");
    add_action(do_pray, "pray");
}
