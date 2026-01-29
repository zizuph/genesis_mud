inherit "std/room";

create() {
  ::create();
    set_light(1);
    set_short("You are on a path that winds along side a dried out river");
    set_long("You are on a path that winds along side a dried out river. "+
	     "This once was the mighty Sirannon-river, which came goshing "+
	     "and foaming from the Misty Mountains. The path goes up, "+
	     "steeply to the east, where it meets some steps in the rock. "+
	     "To the north the path gets wider. A small footpath leads "+
	     "west towards a scree. The dried out river continues somewhat "+
	     "south.\n");
    add_item("river","This once was the Sirannon River.");
    add_item("path","Which path?");
    add_item("mountains,tops","The tops are covered in white.");
    add_item(({"east path","steps"}),
	     "It leads eastwards up to a higher level towards the Mountains.");
    add_item("north path","It gets wider there.");
    add_item(({"footpath","scree"}),
	     "Ah, that's interesting. Why not go west?");
    add_exit("players/rogon/avd1/wider","north");
    add_exit("players/rogon/avd1/scree","west");
    add_exit("players/rogon/avd1/steps","east");
    add_exit("players/rogon/path/path_n","south");
}
