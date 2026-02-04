inherit "/d/Genesis/ship/cabin";

#define SHIP "/d/Terel/mecien/valley/lake/"

#define BSN(xx)  break_string(xx+"\n", 70)

void
create_cabin()
{
    set_short("The captain's cabin");
    set_long(BSN(
         "Beautiful and elegant, this cabin of white and silvery wood "
         +"shimmers in the light of a crystal lamp. The walls are covered "
         +"with charts and maps. Small silvery windows pierce the sides of "
         +"of the ship, through which prisms of light enter. A sextant and "
         +"compass are mounted on the upper wall. A long silver wood table "
         +"and desk fill the room." 
	 ));
    add_item("desk", "An elegant desk, framed in silver, certainly used in "
    +"navigations and drawing.\n");
    add_item("table", "It is a simple table, but of some unknown silver wood.\n");
    add_item(({"maps", "map", "chart", "charts"}), BSN("They are of distant lands "
    + "and unknown waters.")); 
    add_item(({"sextant", "compass"}), BSN("They are mystical looking, "
    +"engraved with strange symbols, fashioned of silver."));
    add_item("window", "Through the silvery windows you look out onto the waters.\n");
    add_item("lamp", BSN("A beautiful but simple crystal lamp."));
    add_exit(SHIP + "m_deck", "fore", 0);
}
