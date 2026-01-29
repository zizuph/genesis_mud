#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Narrow Street");
    set_long("You are travelling along a narrow street somewhere within "+
      "the Port District. The cobblestones underfoot are moist and covered "+
      "with a greenish grime. The road here bends, and travels northward "+
      "towards the base of a huge cliff and eastward into the distance. "+
      "A large wooden building lies to your west and south, while another "+
      "similar structure is to the northeast.\n");
    add_item(({"narrow street","street","road"}),"A small cobblestoned "+
      "roadway winding its way among the buildings of the district.\n");
    add_item(({"cobblestones","cobblestone"}),"The pavement is worn and cracked, "+
      "and seems to be covered in a thin film of moisture.\n");
    add_item(({"greenish grime","grime"}),"Rootless plants, such as moss "+
      "and lichen cover he pavement, apparently sustained by the constant "+
      "amount of water present.\n");
    add_item(({"base","huge cliff","cliff"}),"A towering sheer-faced "+
      "cliff that rises further to the north.\n");
    add_item(({"large wooden building","large building","wooden building","building"}),
      "A rather large structure made out of hardwood planks. It is most "+
      "likely some sort of warehouse. Immediately to the south is a large "+
      "sign hanging in front of it.\n");
    add_item(({"large sign","sign"}),"It has lots of legible words on it.\n");
    add_item(({"similar structure","structure"}),"It appears to be a smaller "+
      "version of the large wooden building.\n");
    add_exit(PORT + "s10", "north");
    add_exit(PORT + "s27", "east");
    add_exit(PORT + "s39", "south");
}

init()
{
    ::init();
    AA(read_sign,read);
}

string
sign()
{
    return "\n"+
    "                   %%%%%%%%%%%%%%%%%%%%%%%%\n"+
    "                   %         THE          %\n"+
    "                   %       HALFLING       %\n"+
    "                   %     B R E W E R Y    %\n"+
    "                   %     -------------    %\n"+
    "                   % The finest, tastiest %\n"+
    "                   %      beer ever!      %\n"+
    "                   %      ----------      %\n"+
    "                   % Est. 1304            %\n"+
    "                   %%%%%%%%%%%%%%%%%%%%%%%%\n";
}

