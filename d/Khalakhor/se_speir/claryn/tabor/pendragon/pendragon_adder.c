/* 
 *  'adder' is a snake which reads
 *   the pendragon library data file
 *   and allows additions to be made
 *
 *   it also anticipates what
 *   ink colour is associated with
 *   a player name
 *
 *   mapping indices are time-based
 *   Wizard provides the mapping value
 *
 *  Vitwitch 09/2020
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <math.h>

#define PENDRAGON_PATH "/d/Khalakhor/se_speir/claryn/tabor/pendragon/"
#define PENDRAGON_LIBFILE "pendragon_librmap"

#define COLOUR_SEED 17

/* not armour... but useful funcs*/
inherit "/std/armour";

mapping librmap;

public void
get_library_data()
{
   int ind;
   seteuid(getuid());
   librmap = restore_map( PENDRAGON_PATH + PENDRAGON_LIBFILE );
   return;
}

public void
put_library_data()
{
   setuid();
   seteuid(getuid());
   save_map( librmap, PENDRAGON_PATH + PENDRAGON_LIBFILE );
   return;
}

//VW
int
find_ink_seed()
{
    int wizlvl;

    string testname;
    int nink, inkidx, testidx, iseed;
    // no first space in inks list
    string inks = "alizarin amaranth amber amethyst aquamarine azure black" +
                  " blue bronze cerulean chartreuse cinnabar cobalt copper" +
                  " crimson cyan emerald gold green harlequin jade magenta" +
                  " maroon olivine purple red ruby sapphire scarlet sepia" +
                  " silver turquoise ultramarine vermilion violet viridian";
    string *ink;

    testname = "goldbezie";
    testidx = 17; //gold

    wizlvl = this_player()->query_wiz_level();

    if (!wizlvl)
    {
        write("You are ignored.\n");
        return 0;
    }

    if (!testname) 
    {
        write("No name to ink?... HISSSS!...");
        return 0;
    }
 
    if (!strlen(testname)) 
    {
        write("No name to ink?... HISSSS!...");
        return 0;
    }

    ink = explode(inks, " ");
    nink = sizeof(ink);

    for (iseed=0;iseed<1000;iseed++)
    {
       inkidx = NAME_TO_RANDOM( testname, iseed, nink );
       if ( inkidx == testidx ) break;
    }

    write( "The random seed " + val2str(iseed) + " causes " + ink[inkidx]
       + " coloured ink to gather at the tips of the adder's fangs.\n" );

    return 1;
}

int
get_ink_name( string testname )
{
    int wizlvl;

    int nink, inkidx;
    // no first space in inks list
    string inks = "alizarin amaranth amber amethyst aquamarine azure black" +
                  " blue bronze cerulean chartreuse cinnabar cobalt copper" +
                  " crimson cyan emerald gold green harlequin jade magenta" +
                  " maroon olivine purple red ruby sapphire scarlet sepia" +
                  " silver turquoise ultramarine vermilion violet viridian";
    string *ink;

    wizlvl = this_player()->query_wiz_level();

    if (!wizlvl)
    {
        write("You are ignored.\n");
        return 0;
    }

    if (!testname) 
    {
        write("No name to ink?... HISSSS!...");
        return 0;
    }
 
    if (!strlen(testname)) 
    {
        write("No name to ink?... HISSSS!...");
        return 0;
    }

    ink = explode(inks, " ");
    nink = sizeof(ink);
    inkidx = NAME_TO_RANDOM( testname, COLOUR_SEED, nink );

    write( "The name " + testname + " causes " + ink[inkidx]
       + " coloured ink to gather at the tips of the adder's fangs.\n" );

    return 1;
}

int
add_it( string newdata )
{
   int wizlvl;
   string ind;

   wizlvl = this_player()->query_wiz_level();

   if (!wizlvl)
   {
       write("You are ignored.\n");
       return 0;
   }

   if (!newdata) 
   {
       write("Nothing to add?... HISSSS!...");
       return 0;
   }

   if (!strlen(newdata)) 
   {
       write("Nothing to add?... HISSSS!...");
       return 0;
   }

   ind = val2str(time());
   librmap[ind] = newdata;
   set_alarm(2.0,0.0,&put_library_data());

   write( newdata + " added to " +
     PENDRAGON_PATH + PENDRAGON_LIBFILE +
     " at index " + ind + " \n" );

   return 1;
}

int
dismiss_it( string str )
{
   int wizlvl;

   wizlvl = this_player()->query_wiz_level();

   if (!wizlvl)
   {
       write("You are ignored.\n");
       return 0;
   }
   if ( str=="adder" )
   {
      write("The adder unhinges its jaw and vanishes by swallowing itself.\n");
      remove_object();
      return 1;
   }

   return 0;
}

void
create_armour()
{
    if(!IS_CLONE)
	return;
 
    set_name( "adder" );
    set_short( "inky adder wearing a monocle" );
    set_long( "A woad adder wearing a monocle, with long fangs dripping"+
              " inks of many hues, coils about you.\n" );

    remove_adj("unworn");
    remove_adj("worn");
    set_af(this_object());

    add_prop(OBJ_I_NO_DROP,"You cannot drop the adder--" +
              " you must <dismiss> it.\n");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_STEAL,0);
    add_prop(OBJ_I_NO_BUY,0);
    add_prop(OBJ_I_NO_SELL,0);
    add_prop(OBJ_I_NO_GIVE,0);
    add_prop(OBJ_I_NO_MAGIC,0);

    get_library_data(); 
}

void
init()
{
   ::init();
    add_action("dismiss_it","dismiss");
    add_action("add_it","add");
    add_action("get_ink_name","inkname");
    add_action("find_ink_seed","inkseed");
}

