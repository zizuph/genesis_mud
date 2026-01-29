#include "def.h"
inherit THIS_DIR+"room";

void add_stuff()
{
    add_item(({"tree", "trees", "forest"}), "The forest is"
      +" made up of tall, dense trees topped by dark, thick leaves."
      +"  It is oddly silent, as though all the woodland creatures had"
      +" been scared off.\n");
    add_item("leaves", "The leaves which top the trees are"
      +" lush and green, while dryer leaves cover the forest floor."
      +"\n");
    add_item("ground", "The ground is covered in places by a"
      +" thick blanket of fallen leaves.\n");
    add_item(({"log", "logs"}), "The occassional fallen log"
      +" lies here in the forest.\n");
    add_item(({"trunk", "trunks"}), "The trunks of these trees"
      +" are dark in color, and grow straight and tall.  They are topped"
      +" with thick green leaves.\n");
    add_item(({"bird", "birds", "creature", "creatures", "animal", "animals"}),
       "None of the usual woodland creatures are visible here;"
      +" perhaps something has scared them all away.\n");
    add_herbs();
}
