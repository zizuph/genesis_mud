/* Base room for the maze leading to the room of the crystalline skulls.
 * If players get tired, lost, or can't solve it, they can jump into
 * the mist on the ceiling to get out.
 *
 * This file is based on the hard work of Cirion's Union guru quest
 * and Boriska's maze code.
 *
 * It always seemed a shame to me that such ingenious quest code 
 * not accessible to the general public, so I've modified it to
 * use in the Catacombs quests Cirion/Ilyian started but never finished.
 *
 * Lilith, May 2021
 *
 * Updates: Lilith Sep 2021: added some more add_items and add_cmd_items
 *          Lilith Mar 2022: typos fix
 */

inherit "/d/Avenir/common/map/map_room";
#include "defs.h"

#include <language.h>
#include <composite.h>


public mapping opp = 
    ([ "north" : "south", "east" : "west",
       "south" : "north", "west" : "east",
       "northwest" : "southeast", "northeast" : "southwest",
       "southeast" : "northwest", "southwest" : "northeast",
       "up" : "down", "down" : "up",
     ]);
	 
#if 1
public mapping way_out = 
([     13 : 4, 
	   12 : 3, 
	   11 : 2, 
	   10 : 1, 
	   9 : 5, 
	   8 : 7, 
	   7 : 8,
	   6 : 5, 
	   5 : 9, 
	   4 : 13, 
	   3 : 12, 
	   2 : 11, 
	   1 : 10 ]);
#endif


public string *words = ({ }), *wlist = WORDS;

public string
go_up()
{
    say(QCTNAME(TP) + " reaches up and is sucked into the mist, legs kicking!\n");
    write("You jump up and are sucked swiftly into the churning mist! "
		  + "It clings to your skin with a sickeningly cool moistness "
		  + "reminscent of a corpse's kiss.\n"
		  + "You feel yourself moving in an uncertain direction, "
		  + "only to surface suddenly on the edge of the well "
		  + "where this misadventure began.\n");
	
    TP->move_living("M", MASQ + "chalice", 1, 1);
	
    return "";
}

public void
create_maze() { }

public nomask void
create_room()
{
    string *dirs;

    ::create_room();

    dirs = query_exit_cmds();

    foreach(string dir: dirs)
    {
	    string wrd = one_of_list(wlist);
	    words += ({ wrd });
	    add_item(({dir +" door", dir +"ern door",
		    dir +" doorway", dir +"ern doorway", dir}),
	        "On the threshold of the " + dir + "ern doorway "
			+"is written the word: " +
	        CAP(wrd) + ".\n");
	    add_cmd_item(({dir +" door", dir +"ern door",
		    dir +" doorway", dir +"ern doorway",
		    dir +" word", dir +"ern word", dir}),
	        "read", "The word carved into the " + dir +
	        "ern threshold reads: "+ CAP(wrd) + ".\n");
		add_item(({dir +" threshold", dir +"ern threshold",
		    dir +" stone", dir +"ern stone",
		    dir}), "On the threshold of the " + dir + "ern doorway "
			+"is carved the word: " +
	        CAP(wrd) + ".\n");
		add_cmd_item(({dir +" threshold", dir +"ern threshold",
		    dir +" stone", dir +"ern stone",
		    dir +" word", dir +"ern word", dir}),
	        "read", "The word carved into the stone of the" + dir +
	        "ern threshold reads: "+ CAP(wrd) + ".\n");
			
     }
      
    set_short("dirt-walled room");
    set_long("The bare, dark walls of packed dirt make this room "
       + "seem strange, especially given that the floor is made of "
	   + "bones laid in intricate patterns that seem to dance "
	   + "before your eyes. Between the swirling mist overhead and the "
	   + "busy patterns underfoot, you find yourself feeling slightly "
	   + "disoriented. @@exits_desc@@ "     
	   + ((sizeof(dirs) > 1) ? "Into the stone threshold "
	   + "of each doorway, words have been carved." :
       "The doorway's stone threshold has letters carved into it.")
       + "\n");

    add_item(({"door","doors","doorway","doorways"}),
	"There "+ (sizeof(dirs) > 1 ?
	    "are "+ LANG_WNUM(sizeof(dirs)) +" doorways" :
	    "is one doorway") +" leading from the room to the "+
	COMPOSITE_WORDS(dirs) + ". Each has a stone threshold with some "+
	    "letters carved into it.\n");
    add_item("threshold", "Specify which threshold.\n");
    add_item(({"word","words", "letter", "letters"}),
	"Read the word on which threshold?\n");
    add_cmd_item(({"word","words", "letter", "letters"}),
	"read", "Read the word on which threshold?\n");
  
	add_item(({"bones", "pattern", "patterns", "pieces", "tile", "tiles"}), 
	   "Bones have been broken up into pieces, polished, and laid "
	 + "like tiles into the dirt floor in a disquieting pattern that looks "
	 + "like it has meaning - a meaning you are unable to fathom.\n");
	
	/* Lost or frustrated? There is always a way out. */
	add_item(({"ceiling","mist","river"}),
		"There is a thick river of churning mist flowing "
		+ "overhead, composed of a milky white substance "
		+ "that glows just enough to illuminate this place. "
		+ "It beckons to you, seeming to whisper into your "
		+ "mind some absurdity about it being a way out "
		+ "of this disquieting place.\n");

    add_cmd_item(({"mist","river","flow",
	    "into the mist","into mist", "in mist", "in the mist", 
		"up into mist", 
		"into the river","into river","in river", "in the river",
		"up into river", 
		"into the flow", "into flow", "in flow", "in the flow",
		"up into the flow"}),
	    ({ "enter", "swim", "climb", "jump", "leap", "reach" }),
		"@@go_up@@");

    set_noshow_obvious(1);
	add_prop(OBJ_S_WIZINFO, "If the player is lost in the maze "
	   +"they can enter the mist and it will take them to the "
	   +"very beginning. This should reset the prop that tracks "
	   +"the maze exits.\nPlayers need to keep track of the "
	   +"name of the gods on the thresholds they cross. "
	   +"This info will be needed once they make it out of "
	   +"the maze, which is just 12 rooms.\n");
	add_prop(ROOM_M_NO_TELEPORT_TO, 
	    "An angry goddess-figure wreathed in red-gold flames "
       +"appears to prevent you from doing that.\n");
	add_prop(ROOM_M_NO_MAGIC, "A loud voice crashes in your mind:\n"
	   +"    You!     Shall!     Not!     Cast!\n");
	
	IN;   
	IN_IN;

    create_maze();
}

public string *messages = ({ 
             "You think you can hear footsteps somewhere nearby.\n",
             "A feeling of immense sadness settles over you.\n",
			 "You feel like you could lay down to rest for years.\n",
             "Your feet catch on the bone tiles underfoot.\n",
             "The swirling mist above seems to beckon to you.\n",
		     "The mist seems to condense on your clothes, yet you remain dry.\n",
			 "The weight of the dirt around you feels oppressive.\n",
             "The rich scent of fresh dirt wafts by.\n" });

public int
add_word(string exit)
{
    int which = member_array(exit, query_exit_cmds());

    if (!present(TP))
        return 1;

    if (which == -1 || which >= sizeof(words))
	return 0;

    /* Red herring messages */
    if (!random(20))
        write(one_of_list(messages));
	
    write("You cross the threshold into a "
        + "room much like the one you just left.\n");

    if (!strlen(words[which]))
      return 0;

 
    /* Add the word prop to the player */
    TP->add_prop(WORD_PROP, TP->query_prop(WORD_PROP) ?
	TP->query_prop(WORD_PROP) +" "+ words[which] : words[which]);
}



public varargs int
add_exit(string place, string cmd, mixed efunc, mixed tired, mixed non_obv)
{
    return ::add_exit(place, cmd, &add_word(cmd), tired, non_obv);
}


public string
exits_desc(void)
{
    string *dirs = query_exit_cmds();
    
    switch(sizeof(dirs))
    {
      case 0:
         return "There is no way out.";
      case 1:
         return "There is one doorway, to the "+ opp[dirs[0]] + ".";
      case 2:
         return (dirs[0] == opp[dirs[1]]) ?
           "Doorways on opposite ends of the room open up to the "
         + dirs[1] + " and the " + dirs[0] + "." :
           "There are two doorways in the " + dirs[0]
         + " and " + dirs[1] + " sides of the room.";
      case 3:
         return "Three doorways lead out to the "
         + COMPOSITE_WORDS(dirs) + ".";
      default:
         return "There are " + LANG_WNUM(sizeof(dirs))
         + " doorways leading out to the " 
		 + COMPOSITE_WORDS(dirs) + ".";
    }
}

#if 1
public mixed
out_dir()
{
    int   which, out, mem;

    sscanf(file_name(TO), MAZE + "maze%d", which);

    if(!which)
      return 0;

    out = way_out[which];

    if((mem = member_array(MAZE + "maze" + out,
       query_exit_rooms())) < 0)
      return 0;

    return query_exit_cmds()[mem];
}
#endif
