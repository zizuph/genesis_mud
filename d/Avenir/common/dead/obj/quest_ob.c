

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

#define TP this_player()

string exa_disk();

string *places = (({"/d/Avenir/common/dead/hill/cairn" , 
                       "The disk is gleaming blue and seems to be humming." ,
                    "/d/Avenir/cirion/workroom" ,
                       "The disk is glowing a with a pale blue light." }));

create_object()
{
   set_short("thin brass disk");
   set_pshort("thin brass disks");
   set_name("disk");
   set_pname("disks");
   add_name("_avenir_hours_amulet_");
   add_adj(({"thin","brass"}));

   set_long("It is a thin disk, its burnished brass surface smooth "
           +"and shiny. Around the edges of the disk are twelve "
           +"tiny symbold etched lightly into the metal. @@exa_disk@@\n");

   add_item(({"symbols","symbol"}), "There are twelve symbols, delicatley "
           +"etched into the brass and evenly "
           +"spaced along the edge of the disk, making it look almost "
           +"like the face of a tiny clock.\n");

   add_item("first symbol", "It is a red hand within a tiny octagon.\n");
   add_item("second symbol", "It is a rat within a circle.\n");
   add_item("third symbol", "It is a skull inside a goblet.\n");
   add_item("fourth symbol", "It is the outline of an eye.\n");
   add_item("fifth symbol", "It is a stylus within a square within a circle.\n");
   add_item("sixth symbol", "It is a trident within a circle.\n");
   add_item("seventh symbol", "It is a knife within a crescent.\n");
   add_item("eighth symbol", "It is a pentagram within a circle.\n");
   add_item("ninth symbol", "It is two crossed rods.\n");
   add_item("tenth symbol", "It is two wavy lines on either side of a "
                           +"triangle.\n");
   add_item("eleventh symbol", "It is a teardrop and a serpent.\n");
   add_item("twelfth symbol", "It is two opposing triangles.\n");

   add_prop( OBJ_I_VOLUME, 97);
   add_prop( OBJ_I_WEIGHT, 80);
   add_prop( OBJ_I_VALUE, 853);
}

string exa_disk()
{
   int mem;
   string where = file_name(environment(TP));

   mem = member_array(where, places);

   if(mem == -1)
      return "The disk is flat and lightless.";
   else
      return places[mem + 1];
}
   

string query_auto_load() { return MASTER + ":"; }

