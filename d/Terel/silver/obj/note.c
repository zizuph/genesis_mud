/* File         : /d/Terel/silver_new/obj/note.c
 * Creator      : Pasqua
 * Date         : March 2006         
 * Purpose      : Note for Taurnil
 * Related Files: 
 * Comments     : How to get to the Goblincave
 * Modifications: 
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define TP   this_player()

public void
create_object()
{
    set_name("note");
    set_adj(({"newlywritten", "bloody"}));

    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
  
    set_long("A newlywritten bloody note, maybe you can read it.\n");
}

public int
do_read(string str)
{
  if (!id(str)) return 0;
  
  write("+----------------------------------------------------------+\n");
  write("| This, Is The Secret Note On How To Reach The Goblin Cave |\n");
  write("| In The Silver Forest. DO NOT SHARE THIS WITH ANYONE ELSE |\n");                                   
  write("|                                                          |\n");
  write("| First you crawl east then you walk eastward thrice.      |\n");
  write("| Then you go south twice and you have made it halfway,    |\n");
  write("| Now.. travel to the southeast thrice and you are there.  |\n");
  write("| As you will stand at the entrance now, you must figure   |\n");
  write("| what to do there.. study the bushes..                    |\n");
  write("|                                                          |\n");   
  write("|                            Thanks,                       |\n");
  write("|                            Taurnil of Calathin           |\n");
  write("+----------------------------------------------------------+\n");
  say(QCTNAME(TP) + " read the " + TP->query_possessive() +
      " " + short() + ".\n");
  return 1;
}

public void
init()
{
    ::init();
    add_action(do_read,"read");
}
