inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Sapphire Street");
  
  set_long(break_string(
           "You are standing on Sapphire Street in the central part of "+
           "Ciubori. West lies an entrance to a strange shop in a large building. "+
           "East is a crowded entrance to Ciubori Library. A quite popular place "+
           "here.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");

  OUTSIDE;

  add_exit(CIUBORI+"diamond/street3","north");
  add_exit(CIUBORI+"sapphire/street2","south");
  add_exit(CIUBORI+"market/ringshop","west");
  add_exit(CIUBORI+"market/library","east");
}
