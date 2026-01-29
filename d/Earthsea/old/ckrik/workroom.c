inherit "/d/Earthsea/std/room";
#include "/sys/macros.h";
#include "/d/Roke/common/defs.h";
#include "/sys/stdproperties.h";

void
create_earthsea_room()
{
    set_long("This is Ckrik's workroom. A fireplace on the side of the" +
             " wall warms the room. You almost fall into a trance looking" +
             " at the leaping flames, there must be something unnatural about" +
             " the fire. You see a grand oak desk in the middle of the room." +
             " On top of the desk, in a corner, sits a picture of someone" +
             " winning a race. Set aside right next to the picture is" +
             " a pile of important looking documents. On the wall behind" +
             " the desk is a painting of a snow-capped peak surrounded by" +
             " lakes.  You notice that a sign is right below it.\n");

    set_short("Ckrik's Office");

    add_item(("desk"),
        ("It is made of extremely fine oak, fully adorned with fancy" +
         " carvings and brass trims. The desk is perfect for" +
         " this office.\n"));

    add_item(({"fireplace", "flame", "flames", "fire"}),
         ("Warm, welcoming heat radiates from the fireplace. Looking" + 
  	    " carefully you find that nothing is burning inside. You wonder" + 
          " what sort of magic is at work there.\n"));

    add_item(({"picture", "someone"}),
         ("You see a beautiful petite woman crossing the finish line" +
          " long ahead of all the other competitors. A caption sits" +
          " below the picture. It reads:\n\n" +
          "\tHanna Kim, 800 m, 2:15.7\n\n"));

    add_item(({"painting", "peak", "lake", "lakes"}),
         ("The peak majesticly rises above the crystal blue lakes." +
          " You awe at the heavenly scene and refuse to believe" +
          " that such a beautiful place exists.\n"));

    add_item(("sign"),
         ("Why don't you read it.\n"));

    add_cmd_item("sign", "read", "@@read_it@@");

    add_exit("/d/Earthsea/workroom", "esea", 0, 0);
    add_exit("/d/Genesis/wiz/domain", "tower");

}


string
read_it()
{
    return("You read:\n\n\tMammoth Lakes, California\n\n");
}
