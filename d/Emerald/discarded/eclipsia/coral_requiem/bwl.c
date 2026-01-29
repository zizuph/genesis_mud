/* Created by Kieryn */

#include "/d/Emerald/eclipsia/edefs.h"
#include "/d/Emerald/lib/bit.h"
#include <stdproperties.h>
#include "/d/Emerald/defs.h"

inherit WATER_ROOM;

void make_music(object ob);

create_room()
{
    object ob ;
   ::create_room();
	catch(call_other(ECLIPSIA_DIR + "coral_requiem/clone_handler", "??"));
   set_short("Underwater Conservatory");
   set_long("   Your wondering gaze travels around the room at the " +
      "breath-taking beauty surrounding you. The vast room is flanked " +
      "in the four corners with majestic columns of coral. " +
      "Your eyes are drawn upward, captivated by the colours of the " +
      "columns. The ceiling is endless, millions of tiny diamond-like " +
      "spots, sparkling and reflecting as the bright " +
      "light from the world above dances on the surface of the water. " +
      "In one corner of the room, you see a small shelter, under which " +
      "beautiful mermaids are floating and singing. Their voices blend in " +
      "perfect harmony. Multi-coloured fish swim past, just inches " +
      "from you. Seaweed sways with the gentle motion of the water " +
      "from the deep cracks in the large chunks of coral around the room. " +
      "In the centre of the room is a tall fountain, somehow carved from " +
      "the coral. Colourful bubbles float out and drift lazily with the " +
      "flow of the water. Along the wall the coral has worn away, " +
      "fashioning benches for all to relax and enjoy the surroundings. " +
      "As your eyes scan the room can see large black openings, caves. " +
      "They are leading off in many directions. You wonder where they " +
      "lead....\n\n");
   
   add_item(({ "columns", "column", "coral column", "coral columns",
            "majestic column", "tower", "towers", "majestic columns" }), "Your eyes " +
      "are drawn up the towers of brightly coloured coral. " +
      "The tops of the columns almost touch the surface of the " +
      "water above.\n");
   
   add_item(({"bench", "benches", "coral benches", "seat", "seats" }), 
      "Long benches reach along the back walls of the room. " +
      "They look very comfortable, a nice place to relax.\n");
   
   add_item("shelter","A small shelf-like protrusion juts out and partly " +
      "covers an area where mermaids are gathered, entertaining whomever " +
      "comes by.\n");
   
   add_item(({ "caves", "cave", "opening", "openings" }), "Large openings " +
      "in directions off from the room. Your curiousity is getting the " +
      "better of you....\n");
   
   add_item(({ "mermaid", "mermaids" }), "The beauty of the mermaids is " +
      "awe-striking, paling only in comparison to their " +
      "angelic voices.\n");
   
   add_item(({ "seaweed", "weeds" }), "Long strings of seaweed dance and " +
      "sway with the flow of the water.\n");
   
   add_item(({ "bubbles", "bubble", "colourful bubbles", "colour", "colours",
            "fountain", "large fountain" }),
      "Big bubbles float lazily with the flow of the water. The large " +
      "coral fountain is a minature version of the corner towers.\n");
   
   add_item("coral", "All around the room are chunks of coral. It is "+
      "brightly coloured and beautiful.\n");
   
   add_item("fish", "Fish of every size, shape and description swim and " +
      "play in the water all around you. Which is your favourite?\n");
   
   add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
   
   add_exit(CRDIR + "cr5", "north");
   add_exit(CRDIR + "cr21", "northwest");
   add_exit(CRDIR + "cr16", "west", "@@check_west_exit");
   add_exit(CRDIR + "cr6", "south", "@@check_south_exit");
   add_exit(CRDIR + "cr22", "southeast");
   add_exit(CRDIR + "cr11", "east");
    add_exit(MINE_DIR + "outside_beach", "up", "@@check_up_exit");
    ob = clone_object("/d/Emerald/eclipsia/obj/crboard");
    ob->move(TO);
}

check_west_exit()
{
   if(this_player()->query_prop("_coral_requiem_npc_"))
     {
	write("You dare not enter this part of the city.\n");
	/* this_player()->fun_message */
	return 1;
     }
	return 0;
}

check_south_exit()
{
   if(this_player()->query_prop("_coral_requiem_npc_"))
     {
	write("You dare not enter this part of the city.\n");
	/* this_player()->fun_message */
	return 1;
     }
	return 0;
}

check_up_exit()
{
   if(this_player()->query_prop("_coral_requiem_npc_"))
     {
	write("You don't want to leave the city.\n");
	/* this_player()->fun_message */
	return 1;
     }
    write("You notice the bubble of air surrounding you begin to "+
          "waver and pop, allowing the water to rush in against you!\n");
        write("You struggle against the downward current and swim "+
              "as hard as you can for the surface above ... \n\n"+
              "You splash up onto the surface and haul yourself "+
              "back up onto the sandbar ... \n\n");
    say(QCTNAME(TP)+" struggles with the downward current as "+
         TP->query_pronoun()+" swims up toward the surface.\n");
    tell_room(MINE_DIR + "outside_beach", QCTNAME(TP)+" splashes up to "+
              "the surface and hauls "+TP->query_objective()+"self "+
             "up onto the sandbar.\n", TP);
	return 0;
}

void surface(object ob)
{
   ob->catch_msg("You can't hold your breath any longer!\n");
   ob->move_living("toward the surface", CRDIR + "s1", 1);
}

void enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   
   make_music(ob);
   setuid();
   seteuid(getuid());
   
}
void
make_music(object ob)
{
   ob->catch_msg("\nAngelic voices meet your ears as you enter " +
      "the underwater conservatory...\n\n");
}
