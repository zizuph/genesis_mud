/*  recipy.c */
/*  janus 920831 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define GARD_DIR        JANUSDIR + "garden/"
#define ARM_DIR         JANUSDIR + "armor/"
#define WEP_DIR         JANUSDIR + "weapons/"

init()
{
    add_action("read", "read");
    ::init();
}

create_object()
{
  set_name("recipe");
  add_name("paper");
  set_adj("strange");
  set_long(break_string(
     "A detailed description for making a liquid that will pacify angry bugs.\n",70));
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,1);
  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_M_NO_DROP, 0);
  add_prop(OBJ_I_NO_GET, 0);
}

read(string what)
{
  if(what=="recipe"){
    write("Recipe for making a liquid that will pacify bugs\n"+
          "------------------------------------------------"+
          "\n"+
          "1 Totally Black flower "+
          "\n"+
          "1 Green Flower \n"+
          "1 Red fruit \n"+
          "1 Octarine flower \n"+
       "1 sprig of parsley \n"+
       "1 clove of garlic \n"+
          "Mix them all well together. Apply as a fine spray. \n"+
          "The bugs will become more peaceful for a limited time.\n");
       return 1;
  }
return 0;
}
