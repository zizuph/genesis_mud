 /*
   Wayreth.

   blackstudy.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 97/03/03
   By ...........: Kentari

 */

#pragma strict_types
#pragma no_clone


#include <stdproperties.h>
#include "/d/Krynn/wayreth/local.h"
inherit TOWERROOM;
#undef ADMIN
#define ADMIN "/d/Krynn/wayreth/guild/admin/admin.c"
#define BLACK ADMIN->query_conclave_head("black")

void
create_tower_room()

{
   set_short("The Study of the Head of the Order of the Black Robes");
    set_long("You are standing in the study of "+capitalize(BLACK)+", " +
             "the current Master of the Black Robes. The room " +
      "is clustered with all sorts of things. You see jars, " +
      "crates, boxes, tins, and scrolls all over the place. " +
      "Books lie piled on top of each other in stacks " +
      "and in the middle of this whole jumble is a large " +
      "oak desk with a highbacked chair facing towards you. " +
      "You are also able to detect a few shelves along the west " +
      "wall and from the ceiling hang four different sized " +
      "cages. The room is very chilly.\n");
   
   add_item(({"study", "room"}), "It is hard to get an idea of the " +
      "exact size of this room due to all the things taking " +
      "space. Only a few feet of open space is to be found on " +
      "the floor giving access to various parts of the room.\n");
   add_item("jars", "There are jars of all sorts of sizes and shapes. " +
      "Round ones and square ones, big ones and small ones, " +
      "blue ones and red ones, low ones and tall ones.\n");
   add_item("round jars", "In these jars are several different sorts " +
      "of insects. Among others you see cockroaches, grasshoppers, " +
      "beetles and small spiders crawling around.\n");
   add_item("corner", "In the far off corner you see a few paintings" +
      "leaning against the wall.\n");
   add_item("square jars", "These clear glass jars contain sparkling" +
      "powders of various colours.\n");
   add_item("big jars", "The big jars are made of terracotta and you " +
      "are unable to see what is inside of them. They are sealed " +
      "and there is no way you could open them without it" + 
      "showing.\n");
   add_item("small jars", "Many of the small jars are empty but in a " +
      "few of them you find rosepetals, sand, some sticky stuff " +
      "and a black thick liquid.\n");
   add_item("blue jars", "All the blue jars have little lables on them " +
      "and they are tightly sealed.\n");
   add_item("red jars", "These jars are all empty.\n");
   add_item("low jars", "Small pieces of bark lie in these jars. You " +
      "recognise birch and pine bark.\n");
   add_item("tall jars", "Long sticks of some yellowish colour stand " +
      "in these jars. They all seem the same and all jars are " +
      "full except one.\n");
   add_item(({"things", "jumble"}), "There are so many things lying " +
      "around in this study that it is hard to know where to " +
      "start looking if one was searching for something.\n");
   add_item("crates", "Several crates stand in the room. Obviously " +
            ""+capitalize(BLACK)+" has not the time to unpack them for you " +
      "notice a thick layer of dust on several of them.\n");
   add_item("boxes", "There are some small wooden boxes here and " +
      "there in the room and you notice that a couple of them " +
      "have small holes in them. As you go closer to examine " +
      "one of them you see a long claw sticking out of one of " +
      "the holes. You decide it best not to open the boxes.\n");
   add_item("tins", "These metal tins contain small seeds of " +
      "various sorts.\n");
   add_item("scrolls", "Some lie piled on the shelves and several " +
      "more lie scattered around the desk. You prudently decide " +
      "that since you are in the study of an Archmage you had " +
      "best let the scrolls lie where they are.\n");
   add_item(({"stacks", "books"}), "Old tomes bound in leather lie in " +
      "stacks all over the room. Some have titles in languages " +
      "you have never seen before and some have strange symbols " +
      "written with peculiar ink.\n");
   add_item(({"desk", "oak desk"}), "This large oak desk is littered " +
      "with scrolls and papers.\n");
   add_item("cages", "They are all made of sturdy metal wires.\n");
   add_item("first cage", "In this large cage you see a large coal-" +
      "black bird. Its beady eyes follow your movements with a " +
      "scrutinizing gaze.\n");
   add_item("second cage", "This small cage is filled with wood-wool. " +
      "You notice some furry little animal move about inside the " +
      "wool.\n");
   add_item("bird", "His coal-black feathers gleam as he slowly turns " +
      "his head towards you.\n");
   add_item("third cage", "This cage is empty.\n");
   add_item("fourth cage", "You see that this cage has been reinforced " +
      "with extra wire mesh. A rank odour emanates from the cage " +
      "and you understand why it is hanging so high up.\n"); 
   add_item("ceiling","The ceiling is made of stone and in each corner " +
      "hangs a sphere of dim glass radiating a soft light. There " +
      "are also four cages hanging at the back of the room.\n");
   add_item(({"wall", "walls"}), "The walls are made of stone.\n");
   add_item("paintings", "There are three paintings leaning against " +
      "the wall. You notice that they are all painted by Udhucair, " +
      "the famous Abanasinian artist.\n");
   add_item("first painting", "It depicts a beautiful stone mansion " +
      "with a garden at the side. Some mountains can be seen in the " +
      "background and threatening storm clouds are gathering in the " +
      "horizon.\n");
   add_item("second painting", "This picture is a portrait of a lady " +
      "dressed in a deep blue, almost black, velvet riding habit. Her " +
      "hair is dark brown and tied back with a black velvet ribbon. " +
      "Her features are delicate and her dark brown eyes are heavily " +
      "accentuated by her pale skin. At her side sits a majestic grey " +
      "wolfhound.\n");
   add_item("third painting", "This large portrait shows a knight in " +
      "full armour. His decorated breastplate showing it to be a " +
      "Solaminan armour of a Knight of the Crown. His face is very " +
      "weathered, his hair black, and his flat grey eyes seem to " +
      "follow you wherever you are in the room. At his feet lies a " +
      "heavy warhammer, gleaming with a dark glow and behind him in " +
      "shadows a pair of gleaming eyes can be seen.\n");
   add_item(({"shelves", "bookshelves"}), "Rows upon rows of leather " +
      "bound books line the shelves.\n");
   add_item(({"leather books", "tomes", "old books"}), "As you start " +
      "to look at the books you notice that there is a very thick " +
      "layer of dust upon them all. You decide it best not to stir " +
      "the dust for fear of sneezing and disturbing someone.\n");

    add_exit(WTOWER + "conclave","north",0);
}
public int
query_start_room()
{
     return 1;
}

static int
query_prevent_snoop() { return 1; }

