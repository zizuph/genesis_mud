/* The Manor's Garden I
 * Coded by Marisol (8/5/97)
 * Copyright (c) Marisol Ramos 1997*/
/* Modified by Marisol (07/23/98) to be used in the village of
 * Ovejuno in Emerald.*/

inherit "/std/room";
#pragma strict_types
#include "defs.h"
#include "/d/Emerald/sys/macros.h"
#define SCARABAE CASTLE_GARDEN_NPC + "g_scarabae"
#define SPARKFLY CASTLE_GARDEN_NPC + "g_sparkfly"
inherit CASTLE_GARDEN;

object scarabae;
object sparkfly;


int block_out();

void reset_room()
{
 if(!objectp(scarabae))
 {
  scarabae = clone_object(SCARABAE);
  scarabae->move(TO);
  scarabae->command ("emote crawls in.");
 }

  if(!objectp(sparkfly))
 {
 sparkfly = clone_object(SPARKFLY);
 sparkfly->move(TO);
 sparkfly->command("emote flies in.");
 }
}


void
create_emerald_garden()
{

    set_long("An old ruined garden lies in front of your eyes. "+
        "The grass has taken over an old path that runs "+
        "inside the enclosure. There is a rusty gate here. "+
        "At the left and right far corners of the garden are huge "+
        "rosebushes of different sizes and colors. On both sides of "+
        "the path, an array of tulips and irises struggle to "+
        "survive the suffocating grass and weeds. The air vibrates with "+
        "the buzzing of insects. Here and there, in between the plants, "+
        "a glint of metal shines and disappears.\n");


    add_item("plants",
        "Tulips and irises lay in the ground in a kaleidoscope of "+
        "shades and aromas. During the years of abandonment, "+
        "these plants have grown wild, creating a tapestry of "+
        "incredible beauty. The tulips and irises stems are "+
        "hidden under the grass, and only their bright flowers stick "+
        "out from it. There are sunny yellow tulips and velvety "+
        "purple irises mingling with the emerald grass.\n");

    add_item(({"yellow tulips", "tulips"}),
        "The tulip flowers are shaped like wine glasses. Their aroma "+
        "is sunny-like, warm and clean. The petals are golden like "+
        "liquid gold. Some of the flowers have fallen off "+
        "and are slowly decaying in the green grass.\n");

    add_item(({"purple irises", "irises"}),
        "The iris flowers look like exotic butterflies. Their aroma is "+
        "sweet like honey and grapes. The petals are long and elegant. "+   
        "Three long velvety purple petals and two soft purple sepals, "+
        "comprise this dainty flower. The whole flower looks like is "+
        "trying to fly away to the sky.\n");

    add_item("gate",
        "A baroque, rusty, iron gate adorned with a complicated "+
        "design of flowers and leaves. Vines and ivy cover it, "+
        "making almost impossible to see through it. There seems "+
        "to be a small apperture between the vines, ivy and bars. "+
        "Maybe you can wriggle out through it.\n");


    add_exit("castle_garden02", "west");
    add_exit("castle_garden03", "east");
add_exit("/d/Emerald/marisol/ovejuno/village_OV/castle_path/castle_path05.c", "south", block_out,5,1);

    reset_room();

}

int
block_out()
{
 write("You manage to wriggle out of the gate.\n");
 return 0;
}

int
do_wriggle(string str)
{
   if(!strlen(str) || !parse_command(str,({}), "'through' 'apperture'"))
   {
   notify_fail(capitalize(query_verb()) + " where?\n");
   return 0;
   }

    this_player()->command("$south");
   return 1;
}

void
init()
{
  ::init();
   add_action(do_wriggle, "wriggle");
}
