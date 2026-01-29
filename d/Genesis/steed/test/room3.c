inherit "/std/room";

create_room()
{
    object ship;
    object captain;
    
    set_short("Steed test room 3.");
    set_long("Steed test room 3. " +
        "There is a ship moving between room 3 and 4.\n");
    add_exit("/d/Genesis/steed/test/room2", "west");

    ship = clone_object("/d/Genesis/ship/ship");
    ship->set_places_to_go(({
        "/d/Genesis/steed/test/room4",
        "/d/Genesis/steed/test/room3"}));
    ship->set_ticket_id("__steed_test_ticket");
    ship->set_time_between_stops(({5, 5}));
    captain = clone_object("/d/Genesis/ship/captain");
    captain->set_name("captain");
    captain->set_price(3);
    captain->set_ticket("/d/Genesis/steed/test/ticket");
    ship->set_captain(captain);
    ship->set_deck(clone_object("/d/Genesis/ship/deck"));
    ship->set_cabin(clone_object("/d/Genesis/ship/cabin"));
    ship->start_ship(0);
}
