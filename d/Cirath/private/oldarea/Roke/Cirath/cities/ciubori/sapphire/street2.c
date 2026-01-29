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
           "You are standing on Sapphire Street which lies in the central part of Ciubori "+
           "You have large buildings on both sides of the street and you can enter a bank "+
           "to your west and 'Cirathian travellers guild' to the east.\n"
           ,60));  

  add_item("ciubori","The second largest city in Cirath.\n");
  add_item(({"house","houses","building","buildings"}),"The houses are neatly built "+
    "and very well-kept. The city looks very wealthy.\n");
  add_item("street","The street is made by bricked stones, neatly put together.\n");
  add_item("bank","The bank seems very well-protected with its steel doors.\n");

  OUTSIDE;

  add_exit(CIUBORI+"sapphire/street1","north");
  add_exit(CIUBORI+"ruby/street3","south");
  add_exit(CIUBORI+"market/bank","west");
  add_exit(CIUBORI+"market/guild","east");
}
