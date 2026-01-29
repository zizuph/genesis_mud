inherit "/std/object";

create_object() {
    set_short("basket of rotten fruit");
     set_name("fruit");
     set_adj("rotten");
}

init() {
    add_action("donut", "donut");
    ::init();
}

status
donut(string who) {
    int i;
    object whob;
    if (!who || !(whob = find_player(who))) {
	write ("Donut who ?\n");
	return 1;
    }

    tell_object(whob, "Suddenly, donuts start raining around you!\n");

    write ("Ok.\n");
    return 1;
}
