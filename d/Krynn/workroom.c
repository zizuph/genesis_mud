/* The new Krynn workroom, after the last one blazed into
 * flames, and was completely destroyed. Don't play with
 * the matches, Gorret :)
 */
#pragma save_binary

inherit "/d/Krynn/std/room";
#include <stdproperties.h>
#include <std.h>
#include "/d/Krynn/common/defs.h"

/*prototype*/
int exam(string str);

/*variables*/
string *wiznames, *wizdesc;

void
load_board()
{
    object bb = clone_object("/std/board");
    bb->set_board_name("/d/Krynn/common/log/board_data");
    bb->set_silent(1);
    bb->set_num_notes(89);
    bb->set_show_lvl(0);
    bb->set_remove_rank(WIZ_ARCH);
    bb->set_remove_str("You are not allowed to remove notes here.");
    bb->move(TO);
}

void
create_room()
{
    set_short("The Krynn Workroom");
    set_long("You have entered the Krynn Workroom.\n" +
	     "Actually, this used to be Percy's workroom, and " +
	     "to prevent this room from being completely forgotten, " +
	     "it has been put to a new use. And anyway, the wizards " +
	     "of Krynn had to make a hasty exit from the old workroom " +
	     "as it blazed into flames after Gorret had played with " +
	     "the matches. Luckily, the board could be saved in time, too.\n" +
	     "You find yourself in a cosy room. A log fire burns" +
	     " merrily in the hearth and gives off a warming glow." +
	     " The floor is covered in a lovely soft plush carpet," +
	     " and the walls are made of the finest oak. Hanging on the" +
	     " walls are the portraits of many wizards who have " +
	     "contributed to Krynn (and Genesis) over the years. Over the fire" +
	     " place you can see a shadow where a picture used to hang.\n" +
	     "Several exits lead to other places in genesis. To the " +
	     "west, you will reach the Tower of Domains, and to " +
	     "the south is the private Krynn Graveyard Workroom.\n");
    
    INSIDE;
    add_prop(ROOM_I_LIGHT ,10);
    
    add_item(({"fireplace","shadow"}), 
	     "It looks like Percy took this picture from above the " +
	     "fireplace with him when he left.\n");
    add_exit("/d/Krynn/common/domain_entr","west");
    add_exit("/d/Krynn/solace/graves/wiz/wrkrm","south");
    add_exit("/d/Krynn/gnome/guild/joinroom", "gnome");
    add_exit("/d/Krynn/solamn/vin/room/courtyard", "vkeep");
    add_exit("/d/Krynn/solamn/palan/club/club3","kclub");
    
    seteuid(getuid(TO));
    restore_object("/d/Krynn/log/kwizs");
    add_item(({"picture", "portrait", "portraits", "pictures", "wizards", "wizard"}), "@@wizprint");
    
    load_board();
}

string
wizprint()
{
    int numpics;
    numpics = sizeof(wiznames);
    if (numpics > 1)
      write("There are " + numpics + " pictures, you can look at each of them.\n");
    else if (numpics == 1)
      exam("picture 1");
    else
      write("There are no pictures here, hmmm, try to paint one?\n");
    return "";
}

void
init()
{
    ::init();
    ADD("exam","examine");
    ADD("exam","exa");
    ADD("exam","look");
    ADA("clean");
}

int
clean(string str)
{
    if (!str)
      return 0;
    if (str != "graves")
      return 0;

    "/d/Krynn/solace/graves/controller"->dig_up_old_graves(400);
    write("Cleaning graves older than 400 days...\n");
    return 1;
}

int
exam(string str)
{
    int numpics, ok,whichpic;
    if (!str)
      return 0;
    
    numpics = sizeof(wiznames);
    if (numpics == 0)
      {
	  NF("Sorry, there are no pictures at the moment.\n");
	  return 0;
      }
    ok = sscanf(str, "picture %d", whichpic);
    if (!ok)
      ok = sscanf(str, "at picture %d", whichpic);
    if (!ok)
      ok = sscanf(str, "%d", whichpic);
    if (!ok)
      return 0;
    if (whichpic > numpics || whichpic < 1)
      {
	  NF("Which picture did you want to look at?\n");
	  return 0;
      }
    write("This is a picture of " + wiznames[whichpic-1] + ".\n");
    write(wizdesc[whichpic-1]);
    return 1;
}


wizcheck()
{
    if (this_player()->query_wiz_level())
        return 0;
    else
        return 1;
}

