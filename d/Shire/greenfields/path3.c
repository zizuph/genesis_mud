inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define EXIT1 GREEN_DIR + "path2","southeast",0,1
#define EXIT2 GREEN_DIR + "path4","north",0,1


void
create_er_room()
{

   area = "outside of";
   areaname = "Greenfields";
   land = "the Shire";
   areatype = 5;
   areadesc = "valley";
   grass = "green";


   extraline = "This twisty path is getting more rocky and rugged.  "+
   "Wagon-wheel marks mar the path into dual ruts leading on either "+
   "side of a relatively undisturbed center.  Over the hills to the northwest, "+
   "some smoke rises into the air, a sure sign of civilization.  Southeast "+
   "leads through more gentle hills.";

   add_item(({"path","marks","ruts","center","gravel"}),
   "The path is of mostly gravel now, and the ruts look recently made.  "+
   "The center of the path is undisturbed by the commotion of the wagons.\n");

   add_item(({"hills","hill"}),
   "The hills here are as jagged and rocky as the gravel on the path.  Wisps "+
   "of smoke rise from over the hills, in the distance.\n");

   add_item(({"smoke","wisps of smoke"}),
   "The smoke is from a rather large fire.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);

}


