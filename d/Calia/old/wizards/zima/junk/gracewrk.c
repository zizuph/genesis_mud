/*GRACE WORKROOM*/

inherit "/std/workroom";

#define PATH "/d/Krynn/grace"

object tchest, pet;

void
create_workroom()
{

set_name("RomperRoom");
set_short("Grace's RomperRoom");

set_long(break_string(
     "A large, sunny room furnished in such a way as to "
   + "prevent Grace from injuring herself. The floor is "
   + "padded with thick carpeting and the mantelshelf has "
   + "been removed from above the grate. Huge pillows with "
   + "bright primary-coloured covers are scattered about the "
   + "floor. A miniature of Avenir sits in ominous glory in "
   + "a far corner, while a battered toy chest lies opposite. "
   + "Sunlight streams in through the south-facing windows, "
   + "highlighting the table and stool in the center of the "
   + "room.\n", 60));

add_item(({ "floor", "carpet", "carpeting" }), break_string(
    "The carpet is oatmeal coloured and so plush and thick "
  + "that you can feel your feet sinking into it.\n", 60));
add_item(({ "mantel", "mantelshelf", "stone" }), break_string(
    "The mantelshelf was removed after Grace bumped her head "
  + "on it and was knocked herself unconscious. All that "
  + "remains is a discoloured, rectangle-shaped patch of "
  + "stone above the grate.\n", 60));
add_item(("grate"), break_string(
    "A magical fire burns within, radiating "
  + "heat and light without consuming the logs. In this "
  + "way, Grace can avoid the possibility of singeing herself "
  + "by making it unnecessary to stock the fire.\n", 60));
add_item(("table"), break_string(
    "You notice that the table is oblong in "
  + "shape and looks very heavy, probably to prevent Grace "
  + "from tipping it over and injuring herself as she bumbles "
  + "about. It is very tidy, with just a small stack of "
  + "files and a fountain pen on its polished surface.\n", 60));
add_item(("files"), break_string(
    "Shuffling through her files, you see manilla"
  + "folders marked 'Avenir', 'Tepisch', 'Plugh', "
  + "'Sexual Enslavement', 'Foul Fred the Flame Monster' "
  + "and 'Misc. Toys'.\n", 60));
add_cmd_item("files", "read", "You're much too nosy. Shame on You!\n");
add_cmd_item("file", "read", "You're much too nosy. Shame on You!\n");
add_item(("stool"), break_string(
    "Made of the same wood as the desk, it has a "
  + "round seat and three legs. It looks uncomfortable.\n", 60));
add_item(("windows"), break_string(
    "The windows cover the entire south wall,"
  + "letting in the bright sunlight. The view is one of "
  + "mountains soaring to breathtaking heights. It occurs "
  + "to you that there should be snow on the peaks, but "
  + "the craggy summits are bare.\n", 60));
add_item(({"avenir", "miniature"}), break_string(
    "A magical miniature of the domain Avenir. It is "
  + "composed of several diverse areas, some of which "
  + "are rather amorphous. As more and more of the "
  + "domain is completed, the corresponding areas of "
  + "the miniature will solidify.\n", 60));
add_item(({"pillow", "pillows"}), break_string(
    "These pillows are large enough to lay on and "
  + "will comfortably seat two people. They will one "
  + "day soon be available for seating, when Grace "
  + "figures out how to make it so.\n", 60));

add_exit("/d/Krynn/solamn/guild/admin.c", "admin", 0);

}
int
add_stuff()
{
if(!pet)
   {
     pet=clone_object(PATH + "/creatures/quechua");
     pet->move(this_object());
   }
if(!tchest)
   {
         tchest=clone_object(PATH + "/obj/tchest");
        tchest->move(this_object());
 clone_object(PATH + "/obj/bslippers")->move(tchest);
   }
}

void
init()
{
::init();
write("Welcome to Romper Room.\n");
call_out("add_stuff",1);       
}
