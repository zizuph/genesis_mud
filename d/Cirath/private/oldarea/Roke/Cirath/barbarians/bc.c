inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/teradeth/defs.h"

sign()
{
  return("The sign reads:\n"+
        "northwest -> Training tent\n"+
        "norteast  -> 'bonk' tent  \n"+
        "southwest -> Elder's tent \n"+
        "southeast -> Sleeping tent\n");
}

void create_room()
{
  set_short("Middle of Barbarian Camp");
  set_long("You stand in the middle of the barbarian camp. There are\n"+
           "many tents around you. Two paths meets here, one in     \n"+
           "north-south direction, and the other in east-west       \n"+
           "direction. The air is full of dust and sand, making it  \n"+
           "hard to breathe and the heat is almost unbearable. It's \n"+
           "a sign here.\n");

  add_item((("sign")),"@@sign");
  add_item((("tents")),"The tents are large and made of leather./n");
  add_item((("tent")),"There's a lot of them you know...\n");
  add_item((("dust")),"The wind is whirling it up from the ground.\n");
  add_item((("sand")),"Of course it's sand in a desert, what did you think?\n");
  add_item(({"path","paths"}),"They are well-travelled...\n");
  add_item((("camp")),"You in the middle of it...The mighty Barbarian Camp!\n");
  add_cmd_item("sign","read","@@sign");

  add_exit("/d/Roke/teradeth/b1","northeast");
  add_exit("/d/Roke/teradeth/b2","northwest");
  add_exit("/d/Roke/teradeth/b3","southeast");
  add_exit("/d/Roke/teradeth/b4","southwest");

}
