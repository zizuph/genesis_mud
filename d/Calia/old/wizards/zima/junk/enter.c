inherit "/std/room";

create_room(){

set_short("Forest Path");
set_long(
"You are in a small forest, a path leads north-south. A large\n"
+ "evergreen bush stands next to the path.\n");

add_item("bush", "It is an evergreen, bright and beautiful.\n");
add_cmd_item("bush", "enter", "@@enter");

}

enter(){

this_player()->move_living("into the evergreen", "/d/Calia/zima/workroom");
return 1;
}
