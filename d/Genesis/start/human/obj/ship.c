#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";

#define CABIN	"/d/Genesis/start/human/town/ship/cabin"
#define DECK	"/d/Genesis/start/human/town/ship/deck"
#define CAPTAIN	"/d/Genesis/start/human/obj/captain"
#define STAND_DIR "/d/Shire/common/ship/"

void
create_ship()
{
    object cap;    
    seteuid(getuid());
    set_cabin(CABIN);
    set_deck(DECK);
    cap = clone_object(CAPTAIN);
    set_captain(cap);
    set_places_to_go(({
	"/d/Genesis/start/human/town/pier4",
                       STAND_DIR + "w1",
                       STAND_DIR + "w2",
                       STAND_DIR + "w3",
                       STAND_DIR + "w4",
                       STAND_DIR + "w5",
                       STAND_DIR + "w6",
        "/d/Shire/common/greyhaven/pier4",
                       STAND_DIR + "w6",
                       STAND_DIR + "w5",
                       "/d/Gondor/bay/openwater3",
                       "/d/Gondor/bay/openwater",
                       "/d/Gondor/bay/eshore2",
                       "/d/Gondor/anduin/mouth",
                       "/d/Gondor/anduin/pelargir",
	"/d/Gondor/pelargir/docks/dock1",
                       "/d/Gondor/anduin/pelargir",
                       "/d/Gondor/anduin/mouth",
                       "/d/Gondor/bay/eshore2",
                       "/d/Gondor/bay/openwater",
                       "/d/Gondor/bay/openwater3",
    }));

    set_time_between_stops(({
	18, 5, 6, 7, 4, 7, 6,
        18, 6, 7, 7, 6, 8, 5, 5,
/*	18, 5, 5, 8, 5, 7, 5, 9, 7, 5, 5, 5, 5, 5,   Line patched.  Styles. */ 
	18, 5, 5, 5, 7, 5,
    }));

    set_name("galleon");
    add_name("ship");
    add_adj("large");
    add_adj("transport");
    set_long(break_string("This is a large ocean-going transport galleon. " +
	"It's put here by the officials in Genesis to go between " +
	"the many harbours around the world. It's a well built ship, and " +
	"looks quite strong, but slow. You see the words: Circle Line, " +
	"written in the front of the ship." +
        "\n", 70));
}
