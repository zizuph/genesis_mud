inherit "/d/Genesis/ship/ship";


#define BSN(xx)  break_string(xx+"\n", 70)
#define SPARKLE  "/d/Genesis/start/human/town/pier5"
#define NAME	"Regina Marinus"
#define SHIP	"/d/Terel/mecien/valley/lake/"
#define PORT	"/d/Terel/mecien/valley/lake/"
#define NP "/d/Avenir/sood/"

void
create_ship()
{
    object cap;
    
    seteuid(getuid());
    set_cabin(SHIP + "m_cab");
    set_deck(SHIP +  "m_deck");
    cap=clone_object(SHIP + "m_cap");
    set_captain(cap);
    set_places_to_go(({PORT + "dock1",
		       PORT + "lake1",
		       PORT + "lake2",
		       PORT + "lake3",
		       PORT + "lake4",
		       PORT + "lake5",
		       PORT + "lake6",
		       PORT + "isle1",
		       PORT + "lake7",
                       PORT + "lake8"}));
    set_time_between_stops(({12,
			      4,
			      7,
			      9,
			      3,
			      5,
			      5,
			     12,
			      3,
                              8}));
    set_ticket_id("Lake Lidlor");
    set_name("ship");
    add_name("boat");
    set_adj(({"small", "white"}));
    set_short("small white ship");
    set_long(BSN(
   "A beautiful silver-white ship, its sails hang high in the " +
   "wind, wavering proudly, shining with a silver hue. " +
    "The edges of the ship are carved with intricate designs " +
    "that are fitted with silver inlaid. The prow of the ship " +
    "takes the shape of an angelic woman, beautiful and elegant, " +
    "crowned with a diadem of silver spirals. " +
    "Alongside the ship an inscription reads: " +NAME+ ".\n"
    ));
}
