/* Name      : /d/Gondor/harondor/room/camp/base_tent.c
 * Purpose   : The file handling the general descriptions
 *             for the tents and the callouts can be found
 *             last in the file.
 * Created by: Sir Toby, Gondor Domain, 2006-02-28
 *
 *   Modified: 
 *
 */


inherit "/d/Gondor/std/room";

#include "/d/Gondor/std/tell.c"

void setup_tent()
{
    set_short("Inside a large canvas tent");
    set_long("The interior of this large tent is very sparse. To the left, just " +
             "inside the entrance, stands a wooden weapon rack. Along the left " +
             "canvas wall benches stand, opposite them on the right wall a few " +
             "beds have been placed. At the far end a table with a few wooden " +
             "stools can be seen. Behind you the only exit of the tent will take " +
             "you back outside into the desert heat. Inside the tent the temperature " +
             "is somewhat lower and refreshing.\n");

    add_item( ({"wooden weapon rack", "weapon rack", "rack", "wooden rack"}), "A plain wooden " +
              "weapon rack, it is empty. The sides have been lacquered in bright colours of " +
              "red, yellow and blue.\n");
    add_item( ({"bench", "benches", "wooden bench", "wooden benches"}), "The benches have a very " +
              "simple design of two crossed wooden planks standing on end at the neds and a long "+
              "sturdy plank on top. The plank have been lacquered with stripes in bright colours " +
              "red, yellow and blue.\n");
    add_item( ({"bed", "beds"}), "The beds are made up from wooden frames. Canvas have been stretched " +
              "onto the frames and bedrolls placed on top of that.\n");
    add_item( ({ "bedroll", "bedrolls" }), "The bedrolls clearly see a lot of hard use. " +
              "They are dirty beyond belief, and they smell very bad.\n");
    add_item( ({"table", "lacquered table", "lacquered wooden table", "sturdy table", 
                "sturdy lacquered table", "sturdy lacquered wooden table"}), "A sturdy wooden table, " +
              "laquered in yellow.\n");
    add_item( ({"stool", "stools", "wooden stool", "wooden stools"}), "The stools are very simple in " +
              "their constructions and the top of them are lacquered red.\n");

    add_cmd_item( ({ "bed", "beds", "bedroll", "bedrolls", "clothing", "clothes" }),
	              ({ "smell", "sniff", "inhale" }), 
                  "The bedrolls and the clothing both have the ripe "+
	              "aroma of sweaty, unwashed bodies.\n");
}

void setup_pavilion()
{
   set_short("Inside a small canvas pavilion");
   set_long("The interior of this small pavilion is very sparse, it offers nice cool shade during " +
            "the hot desert daytime though. To the left, just inside the entrance, stands a rack " +
            "for storing weapons when guards are on a break. There is a large square table in the " +
            "middle with benches placed on all sides.\n");

   add_item( ({"rack", "weapon rack", "wooden rack", "wooden weapon rack"}), "A plain wooden " +
            "weapon rack lacquerd on the sides in bright colours of red, yellow and blue.\n");
   add_item( ({"table", "square table", "large square table", "wooden table", "large square wooden table"}),
            "A large square wooden table, the top of it lacquered in a rich blue color.\n");
   add_item( ({"bench", "benches", "wooden bench", "wooden benches"}), "The benches have a very " +
            "simple design of two crossed wooden planks standing on end at the neds and a long "+
            "sturdy plank on top. The plank have been lacquered with stripes in bright colours " +
            "red, yellow and blue.\n");
}


/* The callouts to the tents */
public void add_harad_tent_tells()
{
    set_tell_time(180+random(30));
    add_tell("A breeze blows through the tent.\n");
    add_tell("From outside a rustle of activity can be heard.\n");
    add_tell("A Haradrim puts his head inside the tent and then leaves again.\n");
    add_tell("You notice movement from the corner of your eye somewhere from under a bed. " +
             "Perhaps only a desert rat startled by yourself.\n");

}
