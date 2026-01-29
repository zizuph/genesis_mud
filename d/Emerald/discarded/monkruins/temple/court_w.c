inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    set_short("Western end of the Courtyard");
    set_long("   You are standing in the western end of the "+
             "courtyard. Only few figures of monks are "+
             "seen around, since due the hot sun the place is quite "+
             "warmed.\nThere is an old, bottomless well here.\n\n");

    add_exit(TEMPLE_DIR + "court_nw", "north", 0);
    add_exit(TEMPLE_DIR + "court_e", "east", 0);
    add_exit(TEMPLE_DIR + "court_sw", "south", 0);

    add_item("well", "It does not seem to have a bottom!\n" +
           "You notice a small bucket which you can fill with water.\n");
    add_item("bucket","It's used by monks to get water from well.\n");
}
 
init()
{
  ::init();
  add_action("do_fill","fill");
}
 
int
do_fill(string str)
{
 object i;
 
 if (str=="bucket with water")
  {
   if ((TP->query_prop("_ring_quest_")==1)
    && (TP->query_prop("_got_bag")!=1))
      if (TP->query_prop("_got_water")==1)
       {
        write("You fill the bucket with water and empty it " +
               "on the ground. Again nothing!\n");
        say(QCTNAME(TP)+" fills the bucket with water from the well and "+
             " empties it on the ground.\n");
        TP->add_prop("_got_water",2);
        return 1;
       }
     else
     if (TP->query_prop("_got_water")==2)
       {
        write("You fill the bucket with water and empty it " +
                "on the ground. A bag tumbles out of the bucket!\n");
        say(QCTNAME(TP) + " fills the bucket with water from the " +
                "well and empties it.\n");
        i=clone_object(TEMPLE_DIR + "obj/bag");
        i->move(ENV(TP));
        TP->add_prop("_got_bag",1);
        return 1;
       }
     else
       {
        write("You fill the bucket with water and empty it " +
               "on the ground. You look at the wet ground, but " +
               "only see mud. No luck this time!\n");
        say(QCTNAME(TP) + " fills the bucket with water from the well and empties it.\n");
        TP->add_prop("_got_water",1);
        return 1;
       }
   write("You fill the bucket with water, then drink from it " +
            "for a while. Ahh, it was refreshing!\n");
   say(QCTNAME(TP) + " fills the bucket with water from the well.\n");
        return 1;
     }
 NF("Fill what with what?\n");
 return 0;
}
