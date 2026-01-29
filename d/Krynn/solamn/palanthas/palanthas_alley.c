/*
 * This module is designed to be inherited into my Palanthas
 * base files to add the <alley> command.  Standard usage will
 * be <alley north> or <alley n>.  Just <alley> will return all
 * available alleys one can take.
 *
 * add_alley("n", "north", NOBLE + "livery_stall");
 *
 * Mortis 10.2005
 */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

mapping alley_map;
string displaydir = "default";
int i;

void
add_alley(string shdir, string longdir, string avalue)
{
    if (!alley_map) {
        alley_map = ([ ]);
    }

    if (!shdir || !avalue)
        return;

    alley_map[shdir] = ({longdir, avalue});
	alley_map[longdir] = ({longdir, avalue});
//	alley_map[aitem] = ({shdir, longdir, aitem});

    if (!alley_map[displaydir]) { alley_map[displaydir] = ({}); }
	alley_map[displaydir] += ({longdir});

}

int
palanthas_alley(string dir)
{
	environment(this_player())->set_dircmd(dir);

	switch(dir)
	{

	case "north":
    case "n":
	  if (!alley_map || !alley_map["n"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the north.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "north", alley_map[dir][1], 0, 0); }
	break;
 	case "south":
	case "s":
	  if (!alley_map || !alley_map["s"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the south.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "south", alley_map[dir][1], 0, 0); }
	break;
	case "east":
	case "e":
	  if (!alley_map || !alley_map["e"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the east.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "east", alley_map[dir][1], 0, 0); }
	break;
	case "west":
	case "w":
	  if (!alley_map || !alley_map["w"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the west.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "west", alley_map[dir][1], 0, 0); }
	break;
	case "northeast":
	case "ne":
	  if (!alley_map || !alley_map["ne"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the northeast.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "northeast", alley_map[dir][1], 0, 0); }
	break;
	case "northwest":
	case "nw":
	  if (!alley_map || !alley_map["nw"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the northwest.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "northwest", alley_map[dir][1], 0, 0); }
	break;
	case "southeast":
	case "se":
	  if (!alley_map || !alley_map["se"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the southeast.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "southeast", alley_map[dir][1], 0, 0); }
	break;
	case "southwest":
	case "sw":
	  if (!alley_map || !alley_map["sw"])
	  { write("Which alley are you trying to enter?\n"); }
	  else { write("You enter the alley to the southwest.\n");
      this_player()->move_living("stepping into an alley to the "
	  + "southwest", alley_map[dir][1], 0, 0); }
	break;

    default:
	  if (!alley_map) { alley_map = ([ ]); }

      if (!alley_map[displaydir])
		{ alley_map[displaydir] = ({ }); }
	  
        
          i = sizeof(alley_map[displaydir]);
		
	  {
		switch(i)
		 {
		   case 0:
		   write("There are no alleys to take.\n");
		   break;
		   case 1:
		   write("There is an alley to the " + alley_map[displaydir][0]
			   + ".\n");
		   break;
		   case 2:
		   write("There are alleys to the " + alley_map[displaydir][0]
			   + " and " + alley_map[displaydir][1] + ".\n");
		   break;
		   case 3:
		   write("There are alleys to the " + alley_map[displaydir][0]
			   + ", " + alley_map[displaydir][1] + ", and "
		       + alley_map[displaydir][2] + ".\n");
		   break;
		   case 4:
		   write("There are alleys to the " + alley_map[displaydir][0]
			   + ", " + alley_map[displaydir][1] + ", and "
		       + alley_map[displaydir][2] + alley_map[displaydir][3] + ".\n");
		   break;
		   case 5:
           write("There are alleys to the " + alley_map[displaydir][0]
			   + ", " + alley_map[displaydir][1] + ", and "
		       + alley_map[displaydir][2] + alley_map[displaydir][3]
			   + alley_map[displaydir][4] + ".\n");
		   break;
		   case 6:
		   write("There are alleys to the " + alley_map[displaydir][0]
			   + ", " + alley_map[displaydir][1] + ", and "
		       + alley_map[displaydir][2] + alley_map[displaydir][3]
			   + alley_map[displaydir][4] + alley_map[displaydir][5] + ".\n");
		   break;
		   case 7:
		   write("There are alleys to the " + alley_map[displaydir][0]
			   + ", " + alley_map[displaydir][1] + ", and "
		       + alley_map[displaydir][2] + alley_map[displaydir][3]
			   + alley_map[displaydir][4] + alley_map[displaydir][5]
			   + alley_map[displaydir][6] + ".\n");
		   break;
		   case 8:
		   write("There are alleys to the " + alley_map[displaydir][0]
			   + ", " + alley_map[displaydir][1] + ", and "
		       + alley_map[displaydir][2] + alley_map[displaydir][3]
			   + alley_map[displaydir][4] + alley_map[displaydir][5]
			   + alley_map[displaydir][6] + alley_map[displaydir][7]
			   + ".\n");
		   break;
		   default:
		   write("Failure?  But how?!?\n");
		   break;
		 }
		 return 1;
	  }
    break;
    }
	
    return 1;
}

/*void
create_krynn_room()
{
	add_item(({alley_map[

  In base file, requires:
public void
init()
{
    ::init();  /* vitally important! never forget this line! 

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect
	add_action(do_alley, "alley");
}


/*
 * Function name:        do_alley
 * Description  :        allow the player to enter a hidden alley
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 *
public int
do_alley(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[the] 'air' / 'here' / 'area' [of] [the] [city]"))
    {
        return 0; /* the player used syntax we don't agree with 
    }

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
	 *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     


    palanthas_alley(this_player());
    return 1;
}
*/