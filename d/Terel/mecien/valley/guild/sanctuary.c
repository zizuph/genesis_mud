/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
set_short("Sanctuary");
set_long(
"Arising from a sunken floor, this majestic octagonal chamber\n"
+"glimmers and sparkles a brilliant aqua, its walls are layered\n"
+"with leaf-shaped plates. Four coiled pillars, in the shape of\n"
+"magnificent gilded emerald serpents, form a central square in\n"
+"the middle of the chamber. The serpents rise up into the domed\n"
+"ceiling, holding aloft a canopy of deep green.\n"
+"A circular garland surrounds the square, like a girdle of living\n"
+"colors these many hedges are potted in deep urns that are set\n"
+"into the sunken floor. Under the canopy, in the center of the\n"
+"square is a large cistern.\n"
);

add_item(({"hedges", "plants"}), 
  "These beautiful plants are a deep aqua color, they looks\n"
 + "to be evergreen in nature. They rise about three feet high\n"
  + "and form a hedge-like garland around the center of the\n"
  + "chamber, as if protecting it.\n");
add_cmd_item(({"hedge", "plant", "leaf"}), "pick",
  "A mysterious power forces you to stop.\n");
add_item(({"pots", "urns"}), 
  "They are gold colored, set deep into the floor and hold the hedges.\n");
add_item(({"golden figures", "figures", "statues"}),
  "These small golden figures are placed upon the rim of the great\n"
  + "cistern, standing like watchers over the water. They are angelic\n"
+ "figures, winged and virtuous looking. They hold swords aloft\n"
+ "that cross over the waters.\n");
add_item("cistern", "A large cistern, placed in the center of the square,\n"
+ "beneath the canopy. It is the central object of this place, everything\n"
+ "seemingly built around it. It is fashioned of a deep green stone and\n"
+ "stands about four feet high. It is octagonally shaped. Its sides\n"
+ "are carved with leaves and foliage designs, including tiny red\n"
+ "three-leaf flowers. A plate of gold tops the cistern and forms a rim,\n"
+ "from which water is taken. Two golden figures stand upon the rim, like\n"
+ "watchers over the water. The water in the cistern is pure.\n");
add_item(({"garland", "girdle"}), 
  "It is a circular group of potted plants, in the center of this\n"
  + "hedge is the square.\n");
add_item("square", "The center of the room, formed by four pillars.\n");
add_item(({"dome", "domed ceiling", "ceiling"}),
"It is a dim green, layered just like the walls.\n");
add_item("canopy", "This rich green canopy is silk, it hangs from the\n"
+ "pillars over the square. From it hang jewels, suspended by long\n"
+ "and fine golden chains.\n");
add_item("chains", "Long thin and finely crafted chains that hang from\n"
+ "the canopy, there are dozens. Large jewels are attached to the ends\n"
+ "of them.\n");
add_item("jewels", "Dozens of large glimmering jewels, they are suspended\n"
+ "from gold chains that hang from the canopy.\n");
add_item(({"sunken floor", "floor"}),
  "The floor, of some type of polished green marble, is set\n"
  + "so that it descends a bit to the center of the chamber.\n");
add_item(({"panel", "leaf-shaped plates", "plates", "walls"}),
 "The walls are coated with finely crafted panels of a mystical\n"
+ "green stone. These plate-like panels are shaped like large\n"
+ "leaves, giving the chamber the feel of some inner life. As if\n"
+ "living, these leaves seem to freshen the room, casting their\n"
+ "aqua glow throughout this bizarre place.\n");
add_item(({"pillars", "serpents"}),
 "Like tremendous and terrifying powers, these pillars shaped\n"
  + "into majestic serpents, emerald green and sparkling radiant,\n"
  + "seem almost divine themselves. They are carved from some\n"
  + "beautiful opaque emerald-like stone, their every detail is\n"
  + "perfectly designed. They appear not as serpents of nature,\n"
  + "but as heavenly creatures, gilded at every scale with a trim\n"
  + "of gold.\n");
add_cmd_item("vial", "fill", "@@fill_vial");

add_exit(PATH + "temple", "south", 0);
add_exit(PATH + "sacristy", "east", 0);

}

fill_vial(){
object vial, hw;
vial = present("mystic_vial", this_player());
if(vial){
if(this_player()->query_alignment()<100){
  write("The smell of the hedges is too strong for you to approach.\n");
  say(QCTNAME(this_player()) + " is repelled by the hedges.\n");
  return 1;
}
write("You place the vial within the cistern and fill it with the\n"
  + "sacred waters of the sanctuary.\n");
say(QCTNAME(this_player()) + " takes water from the cistern.\n");
vial->remove_object();
seteuid(getuid(this_object()));
hw=clone_object("/d/Terel/mecien/hw");
hw->move(this_player());
return 1;
}
}



