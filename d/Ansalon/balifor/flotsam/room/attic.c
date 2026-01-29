#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <ss_types.h>
#include <macros.h>

inherit FLOTSAM_IN;
object knight;

void
reset_flotsam_room()
{
    if(!objectp(knight))
    {
	knight = clone_object(FNPC + "knight");
	knight->arm_me();
	knight->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Inside the attic of a large manor house");
    set_long("@@long_descr");

    add_item("crates","These crates contain odd bits and ends, " +
      "clothing and other such stuff. After thoroughly " +
      "examining them, you find nothing of interest.\n");
    add_item("furniture","Old pieces of ordinary furniture " +
      "covered by sheets fill the room.\n");
    add_item(({"white sheets","sheets"}),"White sheets cover the " +
      "furniture in an effort to keep them protected.\n");
    add_item("dust","Dust covers everything. It must have been " +
      "a long time ago that the stuff up here was put in the attic.\n");
    add_item(({"box","small box"}),"A small box sits at the " +
      "back of the attic, and seems to be used as a makeshift " +
      "table. A burning candle sits on top of it.\n");
    add_item("candle","A pathetic candle burns sullenly " +
      "on the small box. \n");

    add_exit(FROOM + "rooftop2","out",0);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a small cramped attic of a " +
    "large deserted manor. Old wooden crates and furniture " +
    "covered with white sheets seem to fill the majority of the " +
    "space. Everything is covered in dust. On a small box stands " +
    "a pathetic candle that looks half burnt out.\n";
}
